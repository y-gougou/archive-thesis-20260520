import csv
import json
import argparse
from collections import Counter, deque
from pathlib import Path

import numpy as np
import torch
import onnxruntime as ort

try:
    import matplotlib

    matplotlib.use("Agg")
    import matplotlib.pyplot as plt
except ModuleNotFoundError:
    plt = None

from models import build_model
from run_experiments import FEATURE_COLUMNS, INPUT_LAYOUT, INPUT_SHAPE, LABEL_MAP, STEP_SIZE, WINDOW_SIZE


def parse_args():
    parser = argparse.ArgumentParser(description="Replay one CSV through the exported robot fault diagnosis model.")
    parser.add_argument("csv_file", type=Path, help="Single raw CSV file to replay.")
    parser.add_argument("--export_dir", type=Path, default=Path("results_deployment_robust/export"))
    parser.add_argument("--manifest", type=Path, default=None, help="Optional desktop model_manifest.json.")
    parser.add_argument("--output_dir", type=Path, default=None)
    parser.add_argument("--device", default="cuda" if torch.cuda.is_available() else "cpu")
    return parser.parse_args()


def load_json(path):
    with path.open("r", encoding="utf-8") as f:
        return json.load(f)


def read_csv_rows(path):
    with path.open("r", newline="", encoding="utf-8-sig") as f:
        reader = csv.DictReader(f)
        rows = [row for row in reader if not all((value is None or str(value).strip() == "") for value in row.values())]
        fieldnames = reader.fieldnames or []
    if "sample_id" in fieldnames:
        try:
            sample_ids = [int(float(row.get("sample_id"))) for row in rows]
            rows = [row for _, row in sorted(zip(sample_ids, rows), key=lambda item: item[0])]
        except (TypeError, ValueError):
            pass
    return fieldnames, rows


def numeric(row, column):
    try:
        return float(row.get(column, ""))
    except (TypeError, ValueError):
        return np.nan


def build_windows_from_csv(csv_file, feature_columns, window_size, step_size):
    fieldnames, rows = read_csv_rows(csv_file)
    missing = [column for column in feature_columns if column not in fieldnames]
    if missing:
        raise ValueError(f"Missing feature columns in {csv_file}: {missing}")
    if len(rows) < window_size:
        raise ValueError(f"{csv_file} has {len(rows)} rows, fewer than window_size={window_size}.")

    features = np.asarray([[numeric(row, column) for column in feature_columns] for row in rows], dtype=np.float32)
    finite_mask = np.isfinite(features).all(axis=1)
    if not finite_mask.all():
        bad_count = int((~finite_mask).sum())
        bad_ratio = bad_count / max(len(rows), 1)
        if bad_ratio > 0.2:
            raise ValueError(f"Severe NaN/Inf in core features: {bad_count} rows ({bad_ratio:.1%}).")
        features = features[finite_mask]
        rows = [row for row, keep in zip(rows, finite_mask) if keep]
    if features.shape[0] < window_size:
        raise ValueError("Not enough finite rows after dropping NaN/Inf rows.")

    windows = []
    meta = []
    for start in range(0, features.shape[0] - window_size + 1, step_size):
        end = start + window_size
        windows.append(features[start:end].T)
        start_sample = rows[start].get("sample_id", "")
        end_sample = rows[end - 1].get("sample_id", "")
        meta.append(
            {
                "window_index": len(windows) - 1,
                "window_start_row": start,
                "window_end_row": end - 1,
                "window_start_sample_id": start_sample,
                "window_end_sample_id": end_sample,
            }
        )
    x = np.stack(windows).astype(np.float32)
    if x.shape[1:] != (len(feature_columns), window_size):
        raise ValueError(f"Expected [N,{len(feature_columns)},{window_size}], got {x.shape}")
    return x, meta


def softmax(logits):
    shifted = logits - np.max(logits, axis=1, keepdims=True)
    exp = np.exp(shifted)
    return exp / exp.sum(axis=1, keepdims=True)


def load_model(export_dir, device, model_name):
    checkpoint = torch.load(export_dir / "best_model.pt", map_location=device, weights_only=False)
    state = checkpoint["model_state_dict"] if isinstance(checkpoint, dict) and "model_state_dict" in checkpoint else checkpoint
    for dropout in (0.0, 0.4):
        model = build_model(model_name, input_channels=15, num_classes=4, dropout=dropout).to(device)
        try:
            model.load_state_dict(state)
            model.eval()
            return model
        except RuntimeError:
            continue
    raise RuntimeError("Could not load best_model.pt with supported dropout settings.")


def run_model(model, x, mean, std, device, batch_size=256):
    x_norm = ((x - mean.reshape(1, -1, 1)) / std.reshape(1, -1, 1)).astype(np.float32)
    outputs = []
    with torch.no_grad():
        for start in range(0, x_norm.shape[0], batch_size):
            batch = torch.from_numpy(x_norm[start : start + batch_size]).float().to(device)
            logits = model(batch).detach().cpu().numpy()
            outputs.append(logits)
    logits = np.concatenate(outputs, axis=0) if outputs else np.empty((0, 4), dtype=np.float32)
    probs = softmax(logits)
    pred = np.argmax(probs, axis=1).astype(np.int64)
    return pred, probs


def run_onnx_model(manifest_path, x, mean, std):
    manifest = load_json(manifest_path)
    model_path = Path(manifest["model_path"])
    if not model_path.is_absolute():
        model_path = manifest_path.parent / model_path
    x_norm = ((x - mean.reshape(1, -1, 1)) / std.reshape(1, -1, 1)).astype(np.float32)
    session = ort.InferenceSession(str(model_path), providers=["CPUExecutionProvider"])
    input_name = session.get_inputs()[0].name
    input_shape = session.get_inputs()[0].shape
    fixed_batch = input_shape[0] if input_shape and isinstance(input_shape[0], int) else None
    if fixed_batch == 1:
        outputs = [session.run(None, {input_name: x_norm[index : index + 1]})[0] for index in range(x_norm.shape[0])]
        output = np.concatenate(outputs, axis=0) if outputs else np.empty((0, 4), dtype=np.float32)
    else:
        output = session.run(None, {input_name: x_norm})[0]
    probs = softmax(output.astype(np.float32))
    pred = np.argmax(probs, axis=1).astype(np.int64)
    return pred, probs


def postprocess(raw_pred, probs, config):
    post_cfg = config["postprocess"]
    window_count = int(post_cfg.get("window_count", 5))
    confirm_count = int(post_cfg.get("confirm_count", 4))
    fault_threshold = float(post_cfg.get("fault_threshold", 0.8))
    label_queue = deque(maxlen=window_count)
    prob_queue = deque(maxlen=window_count)
    majority = []
    prob_avg = []
    for index, pred in enumerate(raw_pred):
        label_queue.append(int(pred))
        prob_queue.append(probs[index])
        if len(label_queue) < window_count:
            majority.append("")
            prob_avg.append("")
            continue
        chosen, count = Counter(label_queue).most_common(1)[0]
        majority.append(chosen if chosen != 0 and count >= confirm_count else 0)
        avg_prob = np.mean(np.stack(list(prob_queue), axis=0), axis=0)
        best_fault = int(np.argmax(avg_prob[1:]) + 1)
        prob_avg.append(best_fault if avg_prob[best_fault] >= fault_threshold else 0)
    return majority, prob_avg


def write_timeline(path, meta, raw_pred, probs, majority, prob_avg, id_to_label):
    fields = [
        "window_index",
        "window_start_row",
        "window_end_row",
        "window_start_sample_id",
        "window_end_sample_id",
        "raw_pred",
        "raw_label",
        "majority_pred",
        "majority_label",
        "prob_avg_pred",
        "prob_avg_label",
        "prob_normal",
        "prob_wheel_slip",
        "prob_drive_abnormal",
        "prob_shaft_eccentricity",
    ]
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", newline="", encoding="utf-8-sig") as f:
        writer = csv.DictWriter(f, fieldnames=fields)
        writer.writeheader()
        for row, raw, prob, maj, avg in zip(meta, raw_pred, probs, majority, prob_avg):
            output = dict(row)
            output.update(
                {
                    "raw_pred": int(raw),
                    "raw_label": id_to_label[int(raw)],
                    "majority_pred": maj,
                    "majority_label": id_to_label[int(maj)] if maj != "" else "",
                    "prob_avg_pred": avg,
                    "prob_avg_label": id_to_label[int(avg)] if avg != "" else "",
                    "prob_normal": float(prob[0]),
                    "prob_wheel_slip": float(prob[1]),
                    "prob_drive_abnormal": float(prob[2]),
                    "prob_shaft_eccentricity": float(prob[3]),
                }
            )
            writer.writerow(output)


def plot_timeline(path, raw_pred, majority, prob_avg, id_to_label):
    if plt is None:
        return
    x = np.arange(len(raw_pred))
    majority_numeric = np.asarray([np.nan if value == "" else int(value) for value in majority], dtype=float)
    prob_numeric = np.asarray([np.nan if value == "" else int(value) for value in prob_avg], dtype=float)
    fig, ax = plt.subplots(figsize=(12, 4.8), dpi=160)
    ax.step(x, raw_pred, where="post", label="raw", color="#6b7280", alpha=0.75)
    ax.step(x, majority_numeric, where="post", label="majority vote", color="#2f6f9f", linewidth=2)
    ax.step(x, prob_numeric, where="post", label="probability moving average", color="#c7534f", linewidth=2)
    ax.set_xlabel("Window index")
    ax.set_ylabel("Predicted class")
    ax.set_yticks(sorted(id_to_label))
    ax.set_yticklabels([id_to_label[index] for index in sorted(id_to_label)])
    ax.grid(axis="y", alpha=0.25)
    ax.set_title("Prediction Timeline")
    ax.legend(loc="upper right")
    fig.tight_layout()
    path.parent.mkdir(parents=True, exist_ok=True)
    fig.savefig(path)
    plt.close(fig)


def write_replay_summary(path, csv_file, raw_pred, majority, prob_avg, probs, config, labels):
    def counts(values):
        filtered = [int(value) for value in values if value != ""]
        return {labels[index]: int(filtered.count(index)) for index in sorted(labels)}

    summary = {
        "csv_file": str(csv_file),
        "window_count": int(len(raw_pred)),
        "raw_counts": counts(raw_pred),
        "majority_counts": counts(majority),
        "probability_moving_average_counts": counts(prob_avg),
        "mean_raw_confidence": float(np.max(probs, axis=1).mean()) if len(probs) else 0.0,
        "postprocess": config["postprocess"],
    }
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(summary, ensure_ascii=False, indent=2), encoding="utf-8")


def load_desktop_package(manifest_path):
    manifest = load_json(manifest_path)
    base = manifest_path.parent
    feature_config_path = Path(manifest["feature_config_path"])
    if not feature_config_path.is_absolute():
        feature_config_path = base / feature_config_path
    scaler_path = Path(manifest["scaler_path"])
    if not scaler_path.is_absolute():
        scaler_path = base / scaler_path
    guard_path = base / "realtime_sage_cnn_guard_config.json"

    feature_config = load_json(feature_config_path)
    scaler = load_json(scaler_path)
    feature_columns = feature_config["features"]
    label_map = feature_config["label_map"]
    labels = manifest["labels"]
    if feature_columns != FEATURE_COLUMNS:
        raise ValueError("Desktop feature_config_used.json does not match the fixed 15-feature order.")
    if label_map != LABEL_MAP:
        raise ValueError("Desktop feature_config_used.json does not match the fixed label map.")
    expected_labels = ["normal", "wheel_slip", "drive_abnormal", "shaft_eccentricity"]
    if labels != expected_labels:
        raise ValueError(f"Desktop manifest labels mismatch. Expected {expected_labels}, got {labels}")
    if manifest.get("input_shape") != INPUT_SHAPE:
        raise ValueError("Desktop manifest input_shape does not match [1,15,50].")
    if scaler.get("type") != "standard":
        raise ValueError(f"Expected standard scaler for current deployment, got {scaler.get('type')}")
    mean = np.asarray(scaler["mean"], dtype=np.float32)
    std = np.asarray(scaler["scale"], dtype=np.float32)
    guard = load_json(guard_path) if guard_path.exists() else {}
    config = {
        "input_shape": INPUT_SHAPE,
        "input_layout": INPUT_LAYOUT,
        "window_size": int(feature_config.get("window_size", WINDOW_SIZE)),
        "step_size": int(feature_config.get("step_size", STEP_SIZE)),
        "postprocess": {
            "method": "majority_vote",
            "window_count": int(guard.get("vote_window_size", 5)),
            "warning_threshold": 0.6,
            "fault_threshold": 0.8,
            "confirm_count": int(guard.get("vote_required_count", 4)),
        },
        "model": "sage_cnn",
    }
    return config, feature_columns, label_map, mean, std


def main():
    args = parse_args()
    export_dir = args.export_dir.resolve()
    csv_file = args.csv_file.resolve()
    output_dir = args.output_dir or Path("replay_outputs") / csv_file.stem
    output_dir = output_dir.resolve()

    manifest_path = args.manifest.resolve() if args.manifest else None
    if manifest_path is None and (export_dir / "model_manifest.json").exists():
        manifest_path = export_dir / "model_manifest.json"

    if manifest_path is not None:
        config, feature_columns, label_map, mean, std = load_desktop_package(manifest_path)
    else:
        config = load_json(export_dir / "inference_config.json")
        feature_columns = load_json(export_dir / "feature_columns.json")
        label_map = load_json(export_dir / "label_map.json")
        if feature_columns != FEATURE_COLUMNS:
            raise ValueError("feature_columns.json does not match the fixed 15-feature order.")
        if label_map != LABEL_MAP:
            raise ValueError("label_map.json does not match the fixed label map.")
        if config.get("input_shape") != INPUT_SHAPE or config.get("input_layout") != INPUT_LAYOUT:
            raise ValueError("inference_config input shape/layout does not match [1,15,50] batch,channel,time.")
        mean = np.load(export_dir / "scaler_mean.npy").astype(np.float32)
        std = np.load(export_dir / "scaler_std.npy").astype(np.float32)

    x, meta = build_windows_from_csv(csv_file, feature_columns, int(config.get("window_size", WINDOW_SIZE)), int(config.get("step_size", STEP_SIZE)))
    if manifest_path is not None:
        raw_pred, probs = run_onnx_model(manifest_path, x, mean, std)
    else:
        model = load_model(export_dir, torch.device(args.device), config.get("model", "sage_cnn"))
        raw_pred, probs = run_model(model, x, mean, std, torch.device(args.device))
    majority, prob_avg = postprocess(raw_pred, probs, config)
    id_to_label = {value: key for key, value in label_map.items()}

    write_timeline(output_dir / "prediction_timeline.csv", meta, raw_pred, probs, majority, prob_avg, id_to_label)
    plot_timeline(output_dir / "prediction_timeline.png", raw_pred, majority, prob_avg, id_to_label)
    write_replay_summary(output_dir / "replay_summary.json", csv_file, raw_pred, majority, prob_avg, probs, config, id_to_label)
    print(f"Replay complete: {output_dir}")


if __name__ == "__main__":
    main()
