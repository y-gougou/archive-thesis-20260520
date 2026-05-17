import argparse
import contextlib
import csv
import json
import math
import random
import re
import shutil
import warnings
from collections import Counter, defaultdict, deque
from dataclasses import dataclass
from pathlib import Path

import numpy as np
import torch
import torch.nn as nn
import torch.nn.functional as F
from sklearn.metrics import (
    accuracy_score,
    classification_report,
    confusion_matrix,
    f1_score,
    precision_score,
    recall_score,
)
from torch.utils.data import DataLoader, Dataset

from models import build_model

try:
    import matplotlib

    matplotlib.use("Agg")
    import matplotlib.pyplot as plt
except ModuleNotFoundError:
    plt = None


FEATURE_COLUMNS = [
    "odom_vx",
    "odom_vy",
    "odom_wz",
    "wheel_speed0",
    "wheel_speed1",
    "wheel_speed2",
    "imu_ax",
    "imu_ay",
    "imu_az",
    "imu_gx",
    "imu_gy",
    "imu_gz",
    "current0",
    "current1",
    "current2",
]

LABEL_MAP = {
    "normal": 0,
    "wheel_slip": 1,
    "drive_abnormal": 2,
    "shaft_eccentricity": 3,
}
LABEL_NAMES = {value: key for key, value in LABEL_MAP.items()}
MODEL_NAMES = [
    "sage_cnn",
    "sage_no_diff",
    "sage_no_saf",
    "sage_no_diff_gate",
    "cwcnn_fa",
    "normal_cnn",
    "mlp",
    "lstm",
    "bilstm",
]

WINDOW_SIZE = 50
STEP_SIZE = 10
INPUT_SHAPE = [1, 15, 50]
INPUT_LAYOUT = "batch,channel,time"


@dataclass(frozen=True)
class CsvRecord:
    path: Path
    csv_file: str
    label: int
    label_name: str
    speed: str
    run_index: int


class WindowDataset(Dataset):
    def __init__(self, x, y, augment=False, noise_std=0.02, scale_range=(0.95, 1.05)):
        self.x = torch.from_numpy(x).float()
        self.y = torch.from_numpy(y).long()
        self.augment = augment
        self.noise_std = float(noise_std)
        self.scale_range = scale_range

    def __len__(self):
        return int(self.y.shape[0])

    def __getitem__(self, index):
        x = self.x[index].clone()
        y = self.y[index]
        if self.augment:
            scale = torch.empty((x.shape[0], 1)).uniform_(*self.scale_range)
            noise = torch.randn_like(x) * self.noise_std
            x = x * scale + noise
        return x, y


def parse_args():
    parser = argparse.ArgumentParser(description="Run three-stage robot fault diagnosis experiments.")
    parser.add_argument(
        "--mode",
        choices=["paper_main_vx05", "paper_generalization", "deployment_robust", "all"],
        required=True,
    )
    parser.add_argument("--data_root", type=Path, default=Path("../shuju0517"))
    parser.add_argument("--main_results", type=Path, default=Path("results_paper_main_vx05"))
    parser.add_argument("--output_dir", type=Path, default=None)
    parser.add_argument("--models", nargs="+", default=MODEL_NAMES)
    parser.add_argument("--epochs", type=int, default=30)
    parser.add_argument("--runs", type=int, default=5)
    parser.add_argument("--batch_size", type=int, default=64)
    parser.add_argument("--lr", type=float, default=0.001)
    parser.add_argument("--weight_decay", type=float, default=1e-5)
    parser.add_argument("--seed", type=int, default=42)
    parser.add_argument("--num_workers", type=int, default=0)
    parser.add_argument("--smoke", action="store_true", help="Run sage_cnn for 1 epoch and 1 run.")
    parser.add_argument("--require_figures", action="store_true")
    return parser.parse_args()


def ensure_dirs(root):
    for name in ["splits", "summaries", "figures", "checkpoints", "logs"]:
        (root / name).mkdir(parents=True, exist_ok=True)


def write_json(path, data):
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", encoding="utf-8") as f:
        json.dump(data, f, ensure_ascii=False, indent=2)


def write_csv(path, rows, fieldnames):
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", newline="", encoding="utf-8-sig") as f:
        writer = csv.DictWriter(f, fieldnames=fieldnames)
        writer.writeheader()
        writer.writerows(rows)


def set_seed(seed):
    random.seed(seed)
    np.random.seed(seed)
    torch.manual_seed(seed)
    if torch.cuda.is_available():
        torch.cuda.manual_seed_all(seed)


def identify_label(path):
    text = f"{path.parent.name}_{path.name}".lower().replace(" ", "_")
    if "wheel_slip" in text:
        return LABEL_MAP["wheel_slip"], "wheel_slip"
    if "drive_abnormal" in text or "drive_fault" in text or "drive_fault" in text:
        return LABEL_MAP["drive_abnormal"], "drive_abnormal"
    if "shaft_eccentricity" in text or "shaft_eccentric" in text:
        return LABEL_MAP["shaft_eccentricity"], "shaft_eccentricity"
    if "normal" in text:
        return LABEL_MAP["normal"], "normal"
    raise ValueError(f"Cannot identify label from {path}")


def parse_speed(path):
    match = re.search(r"vx(0\.\d+)", path.name.lower())
    if not match:
        raise ValueError(f"Cannot identify speed from {path.name}")
    return match.group(1)


def parse_run_index(path):
    match = re.search(r"run(\d+)", path.name.lower())
    return int(match.group(1)) if match else -1


def discover_records(data_root):
    records = []
    for path in sorted(data_root.rglob("*.csv")):
        label, label_name = identify_label(path)
        records.append(
            CsvRecord(
                path=path.resolve(),
                csv_file=path.name,
                label=label,
                label_name=label_name,
                speed=parse_speed(path),
                run_index=parse_run_index(path),
            )
        )
    if not records:
        raise FileNotFoundError(f"No CSV files found under {data_root}")
    return records


def split_records(records, ratios, seed, require_each_split=True):
    rng = random.Random(seed)
    splits = {"train": [], "val": [], "test": []}
    by_label = defaultdict(list)
    for record in records:
        by_label[record.label].append(record)

    for label, label_records in sorted(by_label.items()):
        ordered = sorted(label_records, key=lambda item: (item.speed, item.run_index, item.csv_file))
        rng.shuffle(ordered)
        n = len(ordered)
        if require_each_split and n < 3:
            raise ValueError(f"Label {label} has only {n} files; cannot create train/val/test split.")

        n_train = max(1, int(round(n * ratios[0])))
        n_val = max(1 if require_each_split else 0, int(round(n * ratios[1])))
        n_test = n - n_train - n_val
        if require_each_split and n_test < 1:
            n_train = max(1, n_train - (1 - n_test))
            n_test = 1
        while n_train + n_val + n_test > n:
            if n_train > 1:
                n_train -= 1
            elif n_val > 1:
                n_val -= 1
            else:
                n_test -= 1
        while n_train + n_val + n_test < n:
            n_train += 1

        splits["train"].extend(ordered[:n_train])
        splits["val"].extend(ordered[n_train : n_train + n_val])
        splits["test"].extend(ordered[n_train + n_val :])

    for split_name in splits:
        splits[split_name] = sorted(splits[split_name], key=lambda item: (item.label, item.speed, item.run_index, item.csv_file))
    assert_no_leakage(splits)
    return splits


def assert_no_leakage(splits):
    seen = {}
    for split_name, records in splits.items():
        for record in records:
            key = str(record.path)
            if key in seen:
                raise ValueError(f"CSV leakage: {record.csv_file} appears in {seen[key]} and {split_name}")
            seen[key] = split_name


def csv_rows_for_records(records):
    rows = []
    for record in records:
        rows.append(
            {
                "csv_file": record.csv_file,
                "path": str(record.path),
                "label": record.label,
                "label_name": record.label_name,
                "speed": record.speed,
                "run_index": record.run_index,
            }
        )
    return rows


def save_split_files(split_dir, splits):
    fields = ["csv_file", "path", "label", "label_name", "speed", "run_index"]
    for split_name, records in splits.items():
        write_csv(split_dir / f"{split_name}_files.csv", csv_rows_for_records(records), fields)


def read_split_file(path):
    records = []
    with path.open("r", newline="", encoding="utf-8-sig") as f:
        reader = csv.DictReader(f)
        for row in reader:
            records.append(
                CsvRecord(
                    path=Path(row["path"]),
                    csv_file=row["csv_file"],
                    label=int(row["label"]),
                    label_name=row["label_name"],
                    speed=row["speed"],
                    run_index=int(row["run_index"]),
                )
            )
    return records


def read_csv_dicts(path):
    with path.open("r", newline="", encoding="utf-8-sig") as f:
        reader = csv.DictReader(f)
        rows = list(reader)
        fieldnames = reader.fieldnames or []

    non_empty = []
    empty_rows = 0
    for row in rows:
        if all((value is None or str(value).strip() == "") for value in row.values()):
            empty_rows += 1
        else:
            non_empty.append(row)

    if "sample_id" in fieldnames:
        try:
            sample_ids = [int(float(row.get("sample_id"))) for row in non_empty]
            non_empty = [row for _, row in sorted(zip(sample_ids, non_empty), key=lambda item: item[0])]
        except (TypeError, ValueError):
            pass
    return fieldnames, non_empty, empty_rows


def numeric_value(row, column):
    raw = row.get(column, "")
    try:
        return float(raw)
    except (TypeError, ValueError):
        return np.nan


def load_record_windows(record, log_rows, window_size=WINDOW_SIZE, step_size=STEP_SIZE):
    fieldnames, rows, empty_rows = read_csv_dicts(record.path)
    missing = [column for column in FEATURE_COLUMNS if column not in fieldnames]
    if missing:
        log_rows.append(
            {
                "csv_file": record.csv_file,
                "level": "skip",
                "message": f"missing feature columns: {missing}",
                "bad_rows": "",
                "empty_rows": empty_rows,
            }
        )
        return [], [], []
    if not rows:
        log_rows.append({"csv_file": record.csv_file, "level": "skip", "message": "empty csv", "bad_rows": "", "empty_rows": empty_rows})
        return [], [], []

    features = np.asarray([[numeric_value(row, column) for column in FEATURE_COLUMNS] for row in rows], dtype=np.float32)
    finite_mask = np.isfinite(features).all(axis=1)
    bad_count = int((~finite_mask).sum())
    if bad_count:
        bad_ratio = bad_count / max(len(rows), 1)
        level = "skip" if bad_ratio > 0.2 else "warn"
        log_rows.append(
            {
                "csv_file": record.csv_file,
                "level": level,
                "message": "NaN/Inf in core feature columns",
                "bad_rows": bad_count,
                "empty_rows": empty_rows,
            }
        )
        if level == "skip":
            return [], [], []
        features = features[finite_mask]
        rows = [row for row, keep in zip(rows, finite_mask) if keep]
    elif empty_rows:
        log_rows.append(
            {
                "csv_file": record.csv_file,
                "level": "info",
                "message": "dropped all-empty rows",
                "bad_rows": 0,
                "empty_rows": empty_rows,
            }
        )

    if features.shape[0] < window_size:
        log_rows.append(
            {
                "csv_file": record.csv_file,
                "level": "skip",
                "message": f"not enough rows for window_size={window_size}",
                "bad_rows": bad_count,
                "empty_rows": empty_rows,
            }
        )
        return [], [], []

    windows, labels, meta = [], [], []
    for start in range(0, features.shape[0] - window_size + 1, step_size):
        end = start + window_size
        windows.append(features[start:end].T)
        labels.append(record.label)
        meta.append(
            {
                "csv_file": record.csv_file,
                "path": str(record.path),
                "label": record.label,
                "label_name": record.label_name,
                "speed": record.speed,
                "run_index": record.run_index,
                "window_index": len(windows) - 1,
                "window_start_row": start,
                "window_end_row": end - 1,
            }
        )
    return windows, labels, meta


def build_windows(records, logs):
    all_x, all_y, all_meta = [], [], []
    for record in records:
        x, y, meta = load_record_windows(record, logs)
        all_x.extend(x)
        all_y.extend(y)
        all_meta.extend(meta)
    if not all_x:
        return np.empty((0, 15, 50), dtype=np.float32), np.empty((0,), dtype=np.int64), []
    x_array = np.stack(all_x).astype(np.float32)
    y_array = np.asarray(all_y, dtype=np.int64)
    if x_array.shape[1:] != (15, 50):
        raise ValueError(f"Expected X shape [N, 15, 50], got {x_array.shape}")
    return x_array, y_array, all_meta


def fit_scaler(x_train):
    flat = x_train.transpose(0, 2, 1).reshape(-1, x_train.shape[1])
    mean = flat.mean(axis=0).astype(np.float32)
    std = flat.std(axis=0).astype(np.float32)
    near_zero = std < 1e-8
    std[near_zero] = 1.0
    return mean, std, near_zero


def transform_x(x, mean, std):
    return ((x - mean.reshape(1, -1, 1)) / std.reshape(1, -1, 1)).astype(np.float32)


def softmax_numpy(logits):
    shifted = logits - np.max(logits, axis=1, keepdims=True)
    exp = np.exp(shifted)
    return exp / exp.sum(axis=1, keepdims=True)


def class_distribution(y):
    return dict(sorted(Counter(int(v) for v in y.tolist()).items()))


def compute_metrics(y_true, y_pred, probs=None):
    metrics = {
        "accuracy": accuracy_score(y_true, y_pred) if len(y_true) else 0.0,
        "precision": precision_score(y_true, y_pred, average="macro", labels=[0, 1, 2, 3], zero_division=0) if len(y_true) else 0.0,
        "recall": recall_score(y_true, y_pred, average="macro", labels=[0, 1, 2, 3], zero_division=0) if len(y_true) else 0.0,
        "macro_f1": f1_score(y_true, y_pred, average="macro", labels=[0, 1, 2, 3], zero_division=0) if len(y_true) else 0.0,
    }
    normal = np.asarray(y_true) == 0
    fault = np.asarray(y_true) != 0
    pred = np.asarray(y_pred)
    metrics["normal_false_alarm_rate"] = float(np.mean(pred[normal] != 0)) if normal.any() else 0.0
    metrics["fault_miss_rate"] = float(np.mean(pred[fault] == 0)) if fault.any() else 0.0
    if probs is not None and len(probs):
        metrics["mean_confidence"] = float(np.max(probs, axis=1).mean())
    return metrics


def per_class_report_text(y_true, y_pred):
    return classification_report(
        y_true,
        y_pred,
        labels=[0, 1, 2, 3],
        target_names=[LABEL_NAMES[i] for i in range(4)],
        digits=4,
        zero_division=0,
    )


def evaluate_model(model, x, y, batch_size, device):
    loader = DataLoader(WindowDataset(x, y), batch_size=batch_size, shuffle=False)
    model.eval()
    logits_list = []
    with torch.no_grad():
        for batch_x, _ in loader:
            batch_x = batch_x.to(device)
            logits = model(batch_x)
            if isinstance(logits, tuple):
                logits = logits[0]
            logits_list.append(logits.cpu().numpy())
    logits = np.concatenate(logits_list, axis=0) if logits_list else np.empty((0, 4), dtype=np.float32)
    probs = softmax_numpy(logits) if logits.size else np.empty((0, 4), dtype=np.float32)
    pred = np.argmax(probs, axis=1) if probs.size else np.empty((0,), dtype=np.int64)
    metrics = compute_metrics(y, pred, probs)
    return metrics, pred, probs


def train_one_epoch(model, loader, criterion, optimizer, device):
    model.train()
    total_loss = 0.0
    total = 0
    for batch_x, batch_y in loader:
        batch_x = batch_x.to(device)
        batch_y = batch_y.to(device)
        logits = model(batch_x)
        if isinstance(logits, tuple):
            logits = logits[0]
        loss = criterion(logits, batch_y)
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()
        total_loss += float(loss.item()) * batch_x.size(0)
        total += batch_x.size(0)
    return total_loss / max(total, 1)


def plot_curves(rows, path, require_figures=False):
    if plt is None:
        message = f"matplotlib is not installed; skipping figure {path}"
        if require_figures:
            raise RuntimeError(message)
        print(message)
        return
    if not rows:
        return
    epochs = [row["epoch"] for row in rows]
    fig, axes = plt.subplots(1, 2, figsize=(10, 4))
    axes[0].plot(epochs, [row["train_loss"] for row in rows], marker="o")
    axes[0].set_xlabel("Epoch")
    axes[0].set_ylabel("Train Loss")
    axes[1].plot(epochs, [row["val_accuracy"] for row in rows], marker="o", label="Val Accuracy")
    axes[1].plot(epochs, [row["val_macro_f1"] for row in rows], marker="s", label="Val Macro F1")
    axes[1].set_ylim(0.0, 1.05)
    axes[1].legend()
    fig.tight_layout()
    path.parent.mkdir(parents=True, exist_ok=True)
    fig.savefig(path, dpi=200)
    plt.close(fig)


def plot_confusion(cm, path, title, require_figures=False):
    if plt is None:
        message = f"matplotlib is not installed; skipping figure {path}"
        if require_figures:
            raise RuntimeError(message)
        print(message)
        return
    fig, ax = plt.subplots(figsize=(7, 6))
    image = ax.imshow(cm, cmap="Blues")
    fig.colorbar(image, ax=ax)
    names = [LABEL_NAMES[i] for i in range(4)]
    ax.set_xticks(np.arange(4))
    ax.set_yticks(np.arange(4))
    ax.set_xticklabels(names, rotation=30, ha="right")
    ax.set_yticklabels(names)
    ax.set_xlabel("Predicted")
    ax.set_ylabel("True")
    ax.set_title(title)
    threshold = cm.max() / 2.0 if cm.size and cm.max() > 0 else 0
    for i in range(4):
        for j in range(4):
            ax.text(j, i, str(cm[i, j]), ha="center", va="center", color="white" if cm[i, j] > threshold else "black")
    fig.tight_layout()
    path.parent.mkdir(parents=True, exist_ok=True)
    fig.savefig(path, dpi=200)
    plt.close(fig)


def plot_bar_summary(rows, metric, path, title, require_figures=False):
    if plt is None:
        message = f"matplotlib is not installed; skipping figure {path}"
        if require_figures:
            raise RuntimeError(message)
        print(message)
        return
    if not rows:
        return
    labels = [row["model"] for row in rows]
    values = [float(row[f"{metric}_mean"]) for row in rows]
    fig, ax = plt.subplots(figsize=(max(8, len(labels) * 1.1), 5))
    ax.bar(labels, values)
    ax.set_ylim(0.0, 1.05)
    ax.set_ylabel(metric)
    ax.set_title(title)
    ax.tick_params(axis="x", rotation=30)
    fig.tight_layout()
    path.parent.mkdir(parents=True, exist_ok=True)
    fig.savefig(path, dpi=200)
    plt.close(fig)


def save_dataset_check(path, mode, split_data, mean=None, std=None, scaler_source="train"):
    rows = []
    for split_name, (records, x, y, meta) in split_data.items():
        file_counts = Counter(record.label for record in records)
        speed_file_counts = Counter(record.speed for record in records)
        window_counts = Counter(int(label) for label in y.tolist())
        speed_window_counts = Counter(row["speed"] for row in meta)
        rows.append(
            {
                "mode": mode,
                "split": split_name,
                "file_count": len(records),
                "label_file_counts": json.dumps(dict(sorted(file_counts.items())), ensure_ascii=False),
                "speed_file_counts": json.dumps(dict(sorted(speed_file_counts.items())), ensure_ascii=False),
                "x_shape": list(x.shape),
                "y_shape": list(y.shape),
                "label_window_counts": json.dumps(dict(sorted(window_counts.items())), ensure_ascii=False),
                "speed_window_counts": json.dumps(dict(sorted(speed_window_counts.items())), ensure_ascii=False),
                "has_nan": bool(np.isnan(x).any()) if x.size else False,
                "has_inf": bool(np.isinf(x).any()) if x.size else False,
                "scaler_source": scaler_source,
                "near_zero_std_channels": "" if std is None else json.dumps([FEATURE_COLUMNS[i] for i, value in enumerate(std) if value < 1e-8], ensure_ascii=False),
            }
        )
    write_csv(
        path,
        rows,
        [
            "mode",
            "split",
            "file_count",
            "label_file_counts",
            "speed_file_counts",
            "x_shape",
            "y_shape",
            "label_window_counts",
            "speed_window_counts",
            "has_nan",
            "has_inf",
            "scaler_source",
            "near_zero_std_channels",
        ],
    )


def prepare_split_data(splits, log_rows):
    data = {}
    for split_name, records in splits.items():
        x, y, meta = build_windows(records, log_rows)
        if x.shape[0] == 0:
            raise ValueError(f"No windows generated for split {split_name}")
        data[split_name] = (records, x, y, meta)
    return data


def save_artifacts(run_dir, splits, mean, std):
    save_split_files(run_dir / "splits", splits)
    np.save(run_dir / "scaler_mean.npy", mean)
    np.save(run_dir / "scaler_std.npy", std)
    write_json(run_dir / "feature_columns.json", FEATURE_COLUMNS)
    write_json(run_dir / "label_map.json", LABEL_MAP)


def run_training(
    model_name,
    run_index,
    run_dir,
    x_train,
    y_train,
    x_val,
    y_val,
    x_test,
    y_test,
    args,
    deployment=False,
):
    set_seed(args.seed + run_index - 1)
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    dropout = 0.4 if deployment else 0.0
    model = build_model(model_name, input_channels=15, num_classes=4, dropout=dropout).to(device)
    if hasattr(model, "input_transpose_log"):
        print(f"{model_name}: {model.input_transpose_log}")
        write_json(run_dir / "input_layout_log.json", {"input_transpose": model.input_transpose_log})

    criterion_kwargs = {}
    if deployment:
        criterion_kwargs["label_smoothing"] = 0.05
    criterion = nn.CrossEntropyLoss(**criterion_kwargs)
    optimizer = torch.optim.Adam(
        model.parameters(),
        lr=args.lr,
        weight_decay=1e-4 if deployment else args.weight_decay,
    )
    train_loader = DataLoader(
        WindowDataset(x_train, y_train, augment=deployment),
        batch_size=args.batch_size,
        shuffle=True,
        num_workers=args.num_workers,
    )

    best_val = -1.0
    best_epoch = 0
    patience = 10 if deployment else args.epochs
    patience_left = patience
    logs = []
    best_path = run_dir / "best_model.pth"
    run_dir.mkdir(parents=True, exist_ok=True)

    for epoch in range(1, args.epochs + 1):
        train_loss = train_one_epoch(model, train_loader, criterion, optimizer, device)
        val_metrics, _, _ = evaluate_model(model, x_val, y_val, args.batch_size, device)
        logs.append(
            {
                "epoch": epoch,
                "train_loss": train_loss,
                "val_accuracy": val_metrics["accuracy"],
                "val_macro_f1": val_metrics["macro_f1"],
            }
        )
        print(
            f"[{model_name} run {run_index:02d}] epoch {epoch:03d}/{args.epochs} "
            f"loss={train_loss:.6f} val_acc={val_metrics['accuracy']:.6f} val_f1={val_metrics['macro_f1']:.6f}"
        )
        if val_metrics["macro_f1"] > best_val:
            best_val = val_metrics["macro_f1"]
            best_epoch = epoch
            patience_left = patience
            torch.save(
                {
                    "epoch": epoch,
                    "model_name": model_name,
                    "model_state_dict": model.state_dict(),
                    "best_val_macro_f1": best_val,
                    "label_map": LABEL_MAP,
                    "feature_columns": FEATURE_COLUMNS,
                    "input_shape": INPUT_SHAPE,
                    "input_layout": INPUT_LAYOUT,
                },
                best_path,
            )
        elif deployment:
            patience_left -= 1
            if patience_left <= 0:
                print(f"[{model_name} run {run_index:02d}] early stopping at epoch {epoch}")
                break

    write_csv(run_dir / "training_log.csv", logs, ["epoch", "train_loss", "val_accuracy", "val_macro_f1"])
    plot_curves(logs, run_dir / "training_curves.png", args.require_figures)

    checkpoint = torch.load(best_path, map_location=device, weights_only=False)
    model.load_state_dict(checkpoint["model_state_dict"])
    val_metrics, _, _ = evaluate_model(model, x_val, y_val, args.batch_size, device)
    test_metrics, test_pred, test_probs = evaluate_model(model, x_test, y_test, args.batch_size, device)
    cm = confusion_matrix(y_test, test_pred, labels=[0, 1, 2, 3])
    plot_confusion(cm, run_dir / "confusion_matrix.png", f"{model_name} run {run_index:02d}", args.require_figures)
    (run_dir / "classification_report.txt").write_text(per_class_report_text(y_test, test_pred), encoding="utf-8-sig")
    np.save(run_dir / "test_probs.npy", test_probs)
    np.save(run_dir / "test_pred.npy", test_pred)

    result = {
        "model": model_name,
        "run_id": run_index,
        "best_epoch": best_epoch,
        "best_val_macro_f1": best_val,
        "val_accuracy": val_metrics["accuracy"],
        "val_macro_f1": val_metrics["macro_f1"],
        "test_accuracy": test_metrics["accuracy"],
        "test_precision": test_metrics["precision"],
        "test_recall": test_metrics["recall"],
        "test_macro_f1": test_metrics["macro_f1"],
        "normal_false_alarm_rate": test_metrics["normal_false_alarm_rate"],
        "fault_miss_rate": test_metrics["fault_miss_rate"],
        "checkpoint_path": str(best_path),
    }
    return result, model, cm


def aggregate_rows(rows, group_key="model"):
    grouped = defaultdict(list)
    for row in rows:
        grouped[row[group_key]].append(row)
    summary = []
    for key, values in sorted(grouped.items()):
        out = {group_key: key, "runs": len(values)}
        for metric in ["test_accuracy", "test_precision", "test_recall", "test_macro_f1", "best_val_macro_f1"]:
            numbers = np.asarray([float(row[metric]) for row in values], dtype=float)
            out[f"{metric}_mean"] = numbers.mean()
            out[f"{metric}_std"] = numbers.std(ddof=0)
        summary.append(out)
    return summary


def write_report(path, title, body_rows, extra_lines=None):
    lines = [f"# {title}", ""]
    if extra_lines:
        lines.extend(extra_lines)
        lines.append("")
    if body_rows:
        best = max(body_rows, key=lambda row: float(row.get("test_macro_f1_mean", row.get("test_macro_f1", 0))))
        lines.append(f"Best by Macro F1: `{best.get('model', best.get('speed', 'unknown'))}`.")
        lines.append("")
    lines.append("Generated files in this result directory are the source of truth for tables, figures, splits, and checkpoints.")
    path.write_text("\n".join(lines) + "\n", encoding="utf-8")


def run_paper_main(records, args):
    root = args.output_dir or Path("results_paper_main_vx05")
    ensure_dirs(root)
    vx05 = [record for record in records if record.speed == "0.5"]
    all_rows = []
    log_rows = []
    first_splits = None
    best_cm = None
    best_result = None

    for model_name in args.models:
        for run_id in range(1, args.runs + 1):
            splits = split_records(vx05, ratios=(0.7, 0.1, 0.2), seed=args.seed + run_id - 1)
            if first_splits is None:
                first_splits = splits
                save_split_files(root / "splits", first_splits)
            run_dir = root / "checkpoints" / model_name / f"run_{run_id:02d}"
            save_split_files(root / "splits" / model_name / f"run_{run_id:02d}", splits)
            split_data_raw = prepare_split_data(splits, log_rows)
            mean, std, _ = fit_scaler(split_data_raw["train"][1])
            save_artifacts(run_dir, splits, mean, std)
            split_data = {}
            for split_name, (split_records_, x, y, meta) in split_data_raw.items():
                split_data[split_name] = (split_records_, transform_x(x, mean, std), y, meta)
            save_dataset_check(run_dir / "dataset_check_report.csv", "paper_main_vx05", split_data_raw, mean, std)
            result, _, cm = run_training(
                model_name,
                run_id,
                run_dir,
                split_data["train"][1],
                split_data["train"][2],
                split_data["val"][1],
                split_data["val"][2],
                split_data["test"][1],
                split_data["test"][2],
                args,
                deployment=False,
            )
            all_rows.append(result)
            if best_result is None or result["test_macro_f1"] > best_result["test_macro_f1"]:
                best_result = result
                best_cm = cm

    write_csv(root / "logs" / "data_cleaning_log.csv", log_rows, ["csv_file", "level", "message", "bad_rows", "empty_rows"])
    write_csv(root / "summaries" / "all_runs.csv", all_rows, list(all_rows[0].keys()))
    summary = aggregate_rows(all_rows)
    write_csv(root / "summaries" / "main_vx0.5_summary.csv", summary, list(summary[0].keys()))
    plot_bar_summary(summary, "test_macro_f1", root / "figures" / "model_comparison_macro_f1.png", "paper_main_vx05 Macro F1", args.require_figures)
    if best_cm is not None:
        plot_confusion(best_cm, root / "figures" / "best_model_confusion_matrix.png", "Best paper_main_vx05", args.require_figures)
    write_report(
        root / "report_paper_main_vx05.md",
        "paper_main_vx05 Report",
        summary,
        ["主工况结果仅使用 vx0.5 文件级 train/val/test。", "模型选择基于 validation Macro F1。"],
    )
    return root


def load_run_artifacts(run_dir):
    mean = np.load(run_dir / "scaler_mean.npy")
    std = np.load(run_dir / "scaler_std.npy")
    with (run_dir / "feature_columns.json").open("r", encoding="utf-8") as f:
        feature_columns = json.load(f)
    with (run_dir / "label_map.json").open("r", encoding="utf-8") as f:
        label_map = json.load(f)
    if feature_columns != FEATURE_COLUMNS:
        raise ValueError(f"feature_columns mismatch in {run_dir}")
    if label_map != LABEL_MAP:
        raise ValueError(f"label_map mismatch in {run_dir}")
    return mean, std


def evaluate_checkpoint(model_name, checkpoint_path, x, y, args):
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    checkpoint = torch.load(checkpoint_path, map_location=device, weights_only=False)
    model = build_model(model_name, input_channels=15, num_classes=4).to(device)
    model.load_state_dict(checkpoint["model_state_dict"])
    return evaluate_model(model, x, y, args.batch_size, device)


def run_generalization(records, args):
    root = args.output_dir or Path("results_paper_generalization")
    ensure_dirs(root)
    main_root = args.main_results
    vx03 = sorted([record for record in records if record.speed == "0.3"], key=lambda item: (item.label, item.run_index, item.csv_file))
    vx07 = sorted([record for record in records if record.speed == "0.7"], key=lambda item: (item.label, item.run_index, item.csv_file))
    write_csv(root / "splits" / "test_vx0.3_files.csv", csv_rows_for_records(vx03), ["csv_file", "path", "label", "label_name", "speed", "run_index"])
    write_csv(root / "splits" / "test_vx0.7_files.csv", csv_rows_for_records(vx07), ["csv_file", "path", "label", "label_name", "speed", "run_index"])

    rows = []
    log_rows = []
    for model_name in args.models:
        model_root = main_root / "checkpoints" / model_name
        if not model_root.exists():
            print(f"Skipping {model_name}: missing {model_root}")
            continue
        for run_dir in sorted(model_root.glob("run_*")):
            run_id = int(run_dir.name.split("_")[-1])
            mean, std = load_run_artifacts(run_dir)
            test_vx05 = read_split_file(run_dir / "splits" / "test_files.csv")
            for speed_name, speed_records in [("vx0.5", test_vx05), ("vx0.3", vx03), ("vx0.7", vx07)]:
                x_raw, y, meta = build_windows(speed_records, log_rows)
                x = transform_x(x_raw, mean, std)
                metrics, pred, _ = evaluate_checkpoint(model_name, run_dir / "best_model.pth", x, y, args)
                cm = confusion_matrix(y, pred, labels=[0, 1, 2, 3])
                plot_confusion(cm, root / "figures" / f"confusion_matrix_{model_name}_run_{run_id:02d}_{speed_name}.png", f"{model_name} {speed_name}", args.require_figures)
                rows.append(
                    {
                        "model": model_name,
                        "run_id": run_id,
                        "speed": speed_name,
                        "test_accuracy": metrics["accuracy"],
                        "test_precision": metrics["precision"],
                        "test_recall": metrics["recall"],
                        "test_macro_f1": metrics["macro_f1"],
                        "normal_false_alarm_rate": metrics["normal_false_alarm_rate"],
                        "fault_miss_rate": metrics["fault_miss_rate"],
                    }
                )

    if not rows:
        raise FileNotFoundError(f"No paper_main checkpoints found under {main_root}")
    write_csv(root / "logs" / "data_cleaning_log.csv", log_rows, ["csv_file", "level", "message", "bad_rows", "empty_rows"])
    write_csv(root / "summaries" / "generalization_all_runs.csv", rows, list(rows[0].keys()))

    summary = []
    grouped = defaultdict(list)
    for row in rows:
        grouped[(row["model"], row["speed"])].append(row)
    for (model_name, speed), values in sorted(grouped.items()):
        out = {"model": model_name, "speed": speed, "runs": len(values)}
        for metric in ["test_accuracy", "test_precision", "test_recall", "test_macro_f1"]:
            numbers = np.asarray([float(row[metric]) for row in values], dtype=float)
            out[f"{metric}_mean"] = numbers.mean()
            out[f"{metric}_std"] = numbers.std(ddof=0)
        summary.append(out)
    write_csv(root / "summaries" / "generalization_all_summary.csv", summary, list(summary[0].keys()))
    for speed in ["vx0.3", "vx0.7"]:
        speed_rows = [row for row in summary if row["speed"] == speed]
        write_csv(root / "summaries" / f"generalization_{speed}_summary.csv", speed_rows, list(summary[0].keys()))
    write_report(
        root / "report_paper_generalization.md",
        "paper_generalization Report",
        summary,
        [
            "test_vx0.5 是论文主测试集；vx0.3 和 vx0.7 只用于跨速度泛化测试。",
            "若泛化性能下降，解释为速度变化导致传感器分布偏移。",
        ],
    )
    return root


def postprocess_predictions(meta, y, probs, window_count=5, confirm_count=4, warning_threshold=0.6, fault_threshold=0.8):
    raw_pred = np.argmax(probs, axis=1)
    y_post = []
    vote_pred = []
    avg_pred = []
    by_csv = defaultdict(list)
    for index, row in enumerate(meta):
        by_csv[row["csv_file"]].append(index)
    for _, indices in sorted(by_csv.items()):
        label_queue = deque(maxlen=window_count)
        prob_queue = deque(maxlen=window_count)
        for index in indices:
            label_queue.append(int(raw_pred[index]))
            prob_queue.append(probs[index])
            if len(label_queue) < window_count:
                continue
            y_post.append(int(y[index]))
            counts = Counter(label_queue)
            chosen, count = counts.most_common(1)[0]
            vote_pred.append(chosen if chosen != 0 and count >= confirm_count else 0)
            avg_prob = np.mean(np.stack(list(prob_queue), axis=0), axis=0)
            best_fault = int(np.argmax(avg_prob[1:]) + 1)
            avg_pred.append(best_fault if avg_prob[best_fault] >= fault_threshold else 0)
    return raw_pred, np.asarray(y_post, dtype=np.int64), np.asarray(vote_pred, dtype=np.int64), np.asarray(avg_pred, dtype=np.int64)


def export_deployment_model(root, best, args):
    export_dir = root / "export"
    export_dir.mkdir(parents=True, exist_ok=True)
    run_dir = Path(best["run_dir"])
    checkpoint_path = Path(best["checkpoint_path"])
    shutil.copyfile(checkpoint_path, export_dir / "best_model.pt")
    for name in ["scaler_mean.npy", "scaler_std.npy", "feature_columns.json", "label_map.json"]:
        shutil.copyfile(run_dir / name, export_dir / name)

    config = {
        "input_shape": INPUT_SHAPE,
        "input_layout": INPUT_LAYOUT,
        "window_size": WINDOW_SIZE,
        "step_size": STEP_SIZE,
        "feature_columns": FEATURE_COLUMNS,
        "label_map": LABEL_MAP,
        "normal_label": 0,
        "postprocess": {
            "method": "probability_moving_average",
            "window_count": 5,
            "warning_threshold": 0.6,
            "fault_threshold": 0.8,
            "confirm_count": 4,
        },
        "selected_by": "highest_val_macro_f1",
        "model": best["model"],
        "run_id": best["run_id"],
        "onnx_exporter": "torch_export_dynamo",
        "onnx_opset_version": 18,
    }
    write_json(export_dir / "inference_config.json", config)

    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    checkpoint = torch.load(checkpoint_path, map_location=device, weights_only=False)
    model = build_model(best["model"], input_channels=15, num_classes=4, dropout=0.0).to(device)
    try:
        model.load_state_dict(checkpoint["model_state_dict"])
    except RuntimeError:
        model = build_model(best["model"], input_channels=15, num_classes=4, dropout=0.4).to(device)
        model.load_state_dict(checkpoint["model_state_dict"])
    model.eval()
    dummy = torch.zeros(tuple(INPUT_SHAPE), dtype=torch.float32, device=device)
    with (export_dir / "onnx_export.log").open("w", encoding="utf-8") as export_log:
        with contextlib.redirect_stdout(export_log), contextlib.redirect_stderr(export_log):
            with warnings.catch_warnings():
                warnings.filterwarnings("ignore", category=FutureWarning)
                torch.onnx.export(
                    model,
                    dummy,
                    export_dir / "best_model.onnx",
                    input_names=["input"],
                    output_names=["logits"],
                    opset_version=18,
                    dynamo=True,
                    external_data=False,
                    report=False,
                    verify=False,
                )
    print(f"ONNX export finished: {export_dir / 'best_model.onnx'}")


def run_deployment(records, args):
    root = args.output_dir or Path("results_deployment_robust")
    ensure_dirs(root)
    (root / "export").mkdir(parents=True, exist_ok=True)
    all_rows = []
    post_rows = []
    log_rows = []
    first_splits = None

    for model_name in args.models:
        for run_id in range(1, args.runs + 1):
            splits = split_records(records, ratios=(0.7, 0.15, 0.15), seed=args.seed + 1000 + run_id - 1)
            if first_splits is None:
                first_splits = splits
                save_split_files(root / "splits", first_splits)
            run_dir = root / "checkpoints" / model_name / f"run_{run_id:02d}"
            save_split_files(root / "splits" / model_name / f"run_{run_id:02d}", splits)
            split_data_raw = prepare_split_data(splits, log_rows)
            mean, std, _ = fit_scaler(split_data_raw["train"][1])
            save_artifacts(run_dir, splits, mean, std)
            split_data = {}
            for split_name, (split_records_, x, y, meta) in split_data_raw.items():
                split_data[split_name] = (split_records_, transform_x(x, mean, std), y, meta)
            save_dataset_check(run_dir / "dataset_check_report.csv", "deployment_robust", split_data_raw, mean, std)
            result, model, cm = run_training(
                model_name,
                run_id,
                run_dir,
                split_data["train"][1],
                split_data["train"][2],
                split_data["val"][1],
                split_data["val"][2],
                split_data["test"][1],
                split_data["test"][2],
                args,
                deployment=True,
            )
            result["run_dir"] = str(run_dir)
            all_rows.append(result)

            test_metrics, _, probs = evaluate_model(model, split_data["test"][1], split_data["test"][2], args.batch_size, torch.device("cuda" if torch.cuda.is_available() else "cpu"))
            raw_pred, y_post, vote_pred, avg_pred = postprocess_predictions(split_data["test"][3], split_data["test"][2], probs)
            vote_metrics = compute_metrics(y_post, vote_pred)
            avg_metrics = compute_metrics(y_post, avg_pred)
            post_rows.append(
                {
                    "model": model_name,
                    "run_id": run_id,
                    "raw_accuracy": test_metrics["accuracy"],
                    "raw_macro_f1": test_metrics["macro_f1"],
                    "majority_accuracy": vote_metrics["accuracy"],
                    "majority_macro_f1": vote_metrics["macro_f1"],
                    "prob_avg_accuracy": avg_metrics["accuracy"],
                    "prob_avg_macro_f1": avg_metrics["macro_f1"],
                    "raw_normal_false_alarm_rate": test_metrics["normal_false_alarm_rate"],
                    "raw_fault_miss_rate": test_metrics["fault_miss_rate"],
                    "majority_normal_false_alarm_rate": vote_metrics["normal_false_alarm_rate"],
                    "majority_fault_miss_rate": vote_metrics["fault_miss_rate"],
                    "prob_avg_normal_false_alarm_rate": avg_metrics["normal_false_alarm_rate"],
                    "prob_avg_fault_miss_rate": avg_metrics["fault_miss_rate"],
                    "postprocess_windows": len(y_post),
                }
            )
            avg_cm = confusion_matrix(y_post, avg_pred, labels=[0, 1, 2, 3]) if len(y_post) else np.zeros((4, 4), dtype=int)
            plot_confusion(cm, run_dir / "confusion_matrix_raw.png", f"{model_name} raw", args.require_figures)
            plot_confusion(avg_cm, run_dir / "confusion_matrix_postprocessed.png", f"{model_name} postprocessed", args.require_figures)

    write_csv(root / "logs" / "data_cleaning_log.csv", log_rows, ["csv_file", "level", "message", "bad_rows", "empty_rows"])
    write_csv(root / "summaries" / "all_runs.csv", all_rows, list(all_rows[0].keys()))
    write_csv(root / "summaries" / "postprocess_summary.csv", post_rows, list(post_rows[0].keys()))
    summary = aggregate_rows(all_rows)
    write_csv(root / "summaries" / "deployment_summary.csv", summary, list(summary[0].keys()))
    plot_bar_summary(summary, "test_macro_f1", root / "figures" / "deployment_model_comparison_macro_f1.png", "deployment_robust Macro F1", args.require_figures)

    best = max(all_rows, key=lambda row: float(row["best_val_macro_f1"]))
    export_deployment_model(root, best, args)
    write_report(
        root / "report_deployment_robust.md",
        "deployment_robust Report",
        summary,
        [
            f"Exported model follows highest val_macro_f1 rule: {best['model']} run {int(best['run_id']):02d}.",
            "Postprocess metrics skip the first N-1 windows within each CSV and are simulated per CSV in order.",
        ],
    )
    return root


def apply_smoke_defaults(args):
    if args.smoke:
        args.models = ["sage_cnn"]
        args.epochs = 1
        args.runs = 1
    for model_name in args.models:
        if model_name not in MODEL_NAMES:
            raise ValueError(f"Unknown model {model_name}; valid models: {MODEL_NAMES}")


def main():
    args = parse_args()
    apply_smoke_defaults(args)
    if args.require_figures and plt is None:
        raise RuntimeError("matplotlib is required for formal figures but is not installed.")
    records = discover_records(args.data_root)
    if args.mode in {"paper_main_vx05", "all"}:
        main_root = run_paper_main(records, args)
        args.main_results = main_root
    if args.mode in {"paper_generalization", "all"}:
        run_generalization(records, args)
    if args.mode in {"deployment_robust", "all"}:
        run_deployment(records, args)


if __name__ == "__main__":
    main()
