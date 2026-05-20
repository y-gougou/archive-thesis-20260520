import argparse
import csv
import json
import re
from collections import Counter
from datetime import datetime
from pathlib import Path

import joblib
import numpy as np
from sklearn.preprocessing import MinMaxScaler, StandardScaler


MODEL_FEATURES = [
    "odom_vx", "odom_vy", "odom_wz",
    "wheel_speed0", "wheel_speed1", "wheel_speed2",
    "imu_ax", "imu_ay", "imu_az",
    "imu_gx", "imu_gy", "imu_gz",
    "current0", "current1", "current2",
]

LABEL_MAP = {
    "normal": 0,
    "wheel_slip": 1,
    "drive_abnormal": 2,
    "shaft_eccentricity": 3,
}

META_FIELDS = [
    "csv_file",
    "run_id",
    "run_index",
    "fault_label",
    "fault_name",
    "motion_mode",
    "window_start_index",
    "window_end_index",
    "window_start_time",
    "window_end_time",
    "split",
]


def parse_args():
    parser = argparse.ArgumentParser(
        description="Preprocess four-class robot fault CSV data for CWCNN-FA."
    )
    parser.add_argument("--input_dir", type=Path, required=True)
    parser.add_argument("--output_dir", type=Path, required=True)
    parser.add_argument("--window_size", type=int, default=50)
    parser.add_argument("--step_size", type=int, default=10)
    parser.add_argument("--scaler", choices=["minmax", "standard"], default="minmax")
    parser.add_argument("--trim_start_sec", type=float, default=5.0)
    parser.add_argument("--trim_end_sec", type=float, default=5.0)
    parser.add_argument(
        "--drop_bad_rows",
        action="store_true",
        help="Drop rows containing NaN or Inf in model features instead of raising an error.",
    )
    return parser.parse_args()


def identify_label_from_filename(filename):
    name = filename.lower()
    if "drive_abnormal" in name or "drive_fault" in name:
        return LABEL_MAP["drive_abnormal"], "drive_abnormal"
    if "wheel_slip" in name:
        return LABEL_MAP["wheel_slip"], "wheel_slip"
    if "shaft_eccentricity" in name or "shaft_eccentric" in name:
        return LABEL_MAP["shaft_eccentricity"], "shaft_eccentricity"
    if "normal" in name:
        return LABEL_MAP["normal"], "normal"
    raise ValueError(f"Cannot identify fault class from filename: {filename}")


def parse_run_index(filename):
    match = re.search(r"run(\d+)", filename.lower())
    if not match:
        print(f"WARNING: cannot parse run index from filename: {filename}")
        return None
    return int(match.group(1))


def split_from_run_index(run_index, filename):
    if run_index is None:
        print(f"WARNING: assigning file without run index to train split: {filename}")
        return "train"
    return "test" if run_index == 5 else "train"


def read_csv_rows(path):
    with path.open("r", newline="", encoding="utf-8-sig") as f:
        reader = csv.DictReader(f)
        rows = list(reader)
        fieldnames = reader.fieldnames or []
    if not rows:
        raise ValueError(f"CSV is empty: {path}")
    return fieldnames, rows


def numeric_column(rows, column):
    values = []
    for row in rows:
        raw = row.get(column, "")
        try:
            values.append(float(raw))
        except (TypeError, ValueError):
            values.append(np.nan)
    return np.asarray(values, dtype=np.float64)


def estimate_sampling_frequency(timestamps, rows):
    record_rates = []
    for row in rows:
        try:
            value = float(row.get("record_rate", "nan"))
        except ValueError:
            value = np.nan
        if np.isfinite(value) and value > 0:
            record_rates.append(value)

    finite_ts = timestamps[np.isfinite(timestamps)]
    if finite_ts.size >= 2:
        diffs = np.diff(finite_ts)
        positive_diffs = diffs[diffs > 0]
        if positive_diffs.size > 0:
            median_dt = float(np.median(positive_diffs))
            if median_dt > 0:
                timestamp_freq = 1.0 / median_dt
                if timestamp_freq > 2.0 or not record_rates:
                    return timestamp_freq

    if record_rates:
        return float(np.mean(record_rates))
    return None


def check_and_extract_file(path, drop_bad_rows):
    fieldnames, rows = read_csv_rows(path)
    missing = [feature for feature in MODEL_FEATURES if feature not in fieldnames]
    if missing:
        raise ValueError(f"{path.name} is missing model feature columns: {missing}")
    if "timestamp" not in fieldnames:
        raise ValueError(f"{path.name} is missing required timestamp column")

    label, label_name = identify_label_from_filename(path.name)
    run_index = parse_run_index(path.name)
    split = split_from_run_index(run_index, path.name)

    features = np.column_stack([numeric_column(rows, col) for col in MODEL_FEATURES])
    timestamps = numeric_column(rows, "timestamp")
    bad_feature_mask = ~np.isfinite(features).all(axis=1)
    bad_timestamp_mask = ~np.isfinite(timestamps)
    bad_mask = bad_feature_mask | bad_timestamp_mask

    if bad_mask.any():
        bad_count = int(bad_mask.sum())
        if not drop_bad_rows:
            raise ValueError(
                f"{path.name} contains {bad_count} rows with NaN/Inf in model features or timestamp. "
                "Use --drop_bad_rows to drop them."
            )
        rows = [row for row, bad in zip(rows, bad_mask) if not bad]
        features = features[~bad_mask]
        timestamps = timestamps[~bad_mask]
        print(f"WARNING: dropped {bad_count} bad rows from {path.name}")

    has_nan = bool(np.isnan(features).any())
    has_inf = bool(np.isinf(features).any())
    if has_nan or has_inf:
        raise ValueError(f"{path.name} still contains invalid values after checking")

    run_id = rows[0].get("run_id") or path.stem
    motion_mode = rows[0].get("motion_mode", "")
    current_valid_ratio = None
    if "current_valid" in fieldnames:
        current_valid = numeric_column(rows, "current_valid")
        current_valid_ratio = float(np.nanmean(current_valid)) if current_valid.size else None

    current_age_max = current_age_mean = None
    if "current_age" in fieldnames:
        current_age = numeric_column(rows, "current_age")
        finite = current_age[np.isfinite(current_age)]
        if finite.size:
            current_age_max = float(np.max(finite))
            current_age_mean = float(np.mean(finite))

    current_reused_max = current_reused_mean = None
    if "current_reused_count" in fieldnames:
        reused = numeric_column(rows, "current_reused_count")
        finite = reused[np.isfinite(reused)]
        if finite.size:
            current_reused_max = float(np.max(finite))
            current_reused_mean = float(np.mean(finite))

    frequency = estimate_sampling_frequency(timestamps, rows)

    info = {
        "path": path,
        "csv_file": path.name,
        "rows": rows,
        "features": features.astype(np.float32),
        "timestamps": timestamps.astype(np.float64),
        "fault_label": label,
        "fault_name": label_name,
        "run_id": run_id,
        "run_index": run_index,
        "split": split,
        "motion_mode": motion_mode,
        "current_valid_ratio": current_valid_ratio,
        "current_age_max": current_age_max,
        "current_age_mean": current_age_mean,
        "current_reused_max": current_reused_max,
        "current_reused_mean": current_reused_mean,
        "sampling_frequency": frequency,
    }
    return info


def trim_single_file(file_info, trim_start_sec, trim_end_sec, window_size):
    before_rows = int(file_info["features"].shape[0])
    timestamps = file_info["timestamps"]

    start_time = float(np.nanmin(timestamps)) + trim_start_sec
    end_time = float(np.nanmax(timestamps)) - trim_end_sec

    if end_time < start_time:
        keep_mask = np.zeros_like(timestamps, dtype=bool)
    else:
        keep_mask = (timestamps >= start_time) & (timestamps <= end_time)

    file_info["features"] = file_info["features"][keep_mask]
    file_info["timestamps"] = file_info["timestamps"][keep_mask]
    file_info["source_indices"] = np.arange(before_rows, dtype=np.int64)[keep_mask]
    after_rows = int(file_info["features"].shape[0])
    file_info["rows_before_trim"] = before_rows
    file_info["rows_after_trim"] = after_rows

    print(
        f"{file_info['csv_file']}: trim rows {before_rows} -> {after_rows} "
        f"(label={file_info['fault_label']} {file_info['fault_name']}, split={file_info['split']})"
    )

    if after_rows <= window_size:
        print(
            f"WARNING: {file_info['csv_file']} has {after_rows} rows after trimming, "
            f"not enough for window_size={window_size}; skipping file."
        )
        file_info["skip"] = True
    else:
        file_info["skip"] = False
    return file_info


def generate_windows(file_info, window_size, step_size):
    x_list = []
    y_list = []
    meta_list = []

    features = file_info["features"]
    timestamps = file_info["timestamps"]
    source_indices = file_info["source_indices"]
    total_rows = features.shape[0]

    for start in range(0, total_rows - window_size + 1, step_size):
        end = start + window_size
        window = features[start:end].T
        x_list.append(window)
        y_list.append(file_info["fault_label"])
        meta_list.append({
            "csv_file": file_info["csv_file"],
            "run_id": file_info["run_id"],
            "run_index": "" if file_info["run_index"] is None else file_info["run_index"],
            "fault_label": file_info["fault_label"],
            "fault_name": file_info["fault_name"],
            "motion_mode": file_info["motion_mode"],
            "window_start_index": int(source_indices[start]),
            "window_end_index": int(source_indices[end - 1]),
            "window_start_time": float(timestamps[start]),
            "window_end_time": float(timestamps[end - 1]),
            "split": file_info["split"],
        })

    print(f"{file_info['csv_file']}: generated {len(x_list)} windows")
    return x_list, y_list, meta_list


def fit_transform_scaler(x_train, x_test, scaler_name):
    scaler = MinMaxScaler() if scaler_name == "minmax" else StandardScaler()

    train_for_fit = x_train.transpose(0, 2, 1).reshape(-1, x_train.shape[1])
    scaler.fit(train_for_fit)

    def transform(x):
        n, c, t = x.shape
        flat = x.transpose(0, 2, 1).reshape(-1, c)
        scaled = scaler.transform(flat).reshape(n, t, c).transpose(0, 2, 1)
        return scaled.astype(np.float32)

    return transform(x_train), transform(x_test), scaler


def write_meta(path, rows):
    with path.open("w", newline="", encoding="utf-8-sig") as f:
        writer = csv.DictWriter(f, fieldnames=META_FIELDS)
        writer.writeheader()
        writer.writerows(rows)


def save_feature_config(path, args, train_samples, test_samples):
    config = {
        "features": MODEL_FEATURES,
        "num_features": len(MODEL_FEATURES),
        "window_size": args.window_size,
        "step_size": args.step_size,
        "scaler": args.scaler,
        "trim_start_sec": args.trim_start_sec,
        "trim_end_sec": args.trim_end_sec,
        "num_classes": 4,
        "label_map": LABEL_MAP,
        "input_shape": [len(MODEL_FEATURES), args.window_size],
        "train_samples": int(train_samples),
        "test_samples": int(test_samples),
        "created_time": datetime.now().isoformat(timespec="seconds"),
    }
    with path.open("w", encoding="utf-8") as f:
        json.dump(config, f, ensure_ascii=False, indent=2)


def print_class_distribution(name, y):
    counts = Counter(int(v) for v in y.tolist())
    print(f"{name} class distribution: {dict(sorted(counts.items()))}")


def main():
    args = parse_args()
    if args.window_size <= 0 or args.step_size <= 0:
        raise ValueError("--window_size and --step_size must be positive")

    csv_files = sorted(args.input_dir.rglob("*.csv"))
    if not csv_files:
        raise FileNotFoundError(f"No CSV files found under {args.input_dir}")

    print(f"Found {len(csv_files)} CSV files")
    print(f"Model features ({len(MODEL_FEATURES)}): {MODEL_FEATURES}")

    train_x, train_y, train_meta = [], [], []
    test_x, test_y, test_meta = [], [], []
    train_files, test_files = [], []

    for csv_path in csv_files:
        info = check_and_extract_file(csv_path, args.drop_bad_rows)
        print(
            f"{csv_path.name}: class={info['fault_label']} {info['fault_name']}, "
            f"run_index={info['run_index']}, split={info['split']}, "
            f"sampling_freq≈{info['sampling_frequency']}"
        )
        if info["current_valid_ratio"] is not None:
            print(f"  current_valid ratio={info['current_valid_ratio']:.4f}")
        if info["current_age_max"] is not None:
            print(
                f"  current_age max={info['current_age_max']:.6f}, "
                f"mean={info['current_age_mean']:.6f}"
            )
        if info["current_reused_max"] is not None:
            print(
                f"  current_reused_count max={info['current_reused_max']:.6f}, "
                f"mean={info['current_reused_mean']:.6f}"
            )

        info = trim_single_file(info, args.trim_start_sec, args.trim_end_sec, args.window_size)
        if info["skip"]:
            continue

        x_list, y_list, meta_list = generate_windows(info, args.window_size, args.step_size)
        if info["split"] == "train":
            train_x.extend(x_list)
            train_y.extend(y_list)
            train_meta.extend(meta_list)
            train_files.append(info["csv_file"])
        elif info["split"] == "test":
            test_x.extend(x_list)
            test_y.extend(y_list)
            test_meta.extend(meta_list)
            test_files.append(info["csv_file"])
        else:
            raise ValueError(f"Unknown split: {info['split']}")

    if not train_x:
        raise ValueError("No training windows generated")
    if not test_x:
        raise ValueError("No test windows generated")

    x_train = np.stack(train_x).astype(np.float32)
    y_train = np.asarray(train_y, dtype=np.int64)
    x_test = np.stack(test_x).astype(np.float32)
    y_test = np.asarray(test_y, dtype=np.int64)

    print(f"Train files: {train_files}")
    print(f"Test files: {test_files}")
    print(f"Raw X_train.shape: {x_train.shape}")
    print(f"Raw X_test.shape: {x_test.shape}")
    print_class_distribution("y_train", y_train)
    print_class_distribution("y_test", y_test)
    print(f"Raw X_train has NaN: {bool(np.isnan(x_train).any())}")
    print(f"Raw X_train has Inf: {bool(np.isinf(x_train).any())}")
    print(f"Raw X_test has NaN: {bool(np.isnan(x_test).any())}")
    print(f"Raw X_test has Inf: {bool(np.isinf(x_test).any())}")

    print(f"Using scaler: {args.scaler}")
    x_train, x_test, scaler = fit_transform_scaler(x_train, x_test, args.scaler)

    print(f"Scaled X_train.shape: {x_train.shape}")
    print(f"Scaled X_test.shape: {x_test.shape}")
    print(f"Scaled X_train has NaN: {bool(np.isnan(x_train).any())}")
    print(f"Scaled X_train has Inf: {bool(np.isinf(x_train).any())}")
    print(f"Scaled X_test has NaN: {bool(np.isnan(x_test).any())}")
    print(f"Scaled X_test has Inf: {bool(np.isinf(x_test).any())}")

    args.output_dir.mkdir(parents=True, exist_ok=True)
    np.save(args.output_dir / "X_train.npy", x_train)
    np.save(args.output_dir / "y_train.npy", y_train)
    np.save(args.output_dir / "X_test.npy", x_test)
    np.save(args.output_dir / "y_test.npy", y_test)
    write_meta(args.output_dir / "meta_train.csv", train_meta)
    write_meta(args.output_dir / "meta_test.csv", test_meta)
    joblib.dump(scaler, args.output_dir / "scaler.pkl")
    save_feature_config(args.output_dir / "feature_config.json", args, len(y_train), len(y_test))

    print(f"Saved outputs to: {args.output_dir.resolve()}")


if __name__ == "__main__":
    main()
