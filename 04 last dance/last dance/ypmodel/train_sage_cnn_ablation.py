import argparse
import csv
import json
import random
import shutil
from collections import Counter
from pathlib import Path

import joblib
import numpy as np
import torch
import torch.nn as nn
from sklearn.metrics import (
    accuracy_score,
    classification_report,
    confusion_matrix,
    f1_score,
    precision_score,
    recall_score,
)
from sklearn.preprocessing import MinMaxScaler, StandardScaler
from torch.utils.data import DataLoader, TensorDataset

from models import build_model

try:
    import matplotlib

    matplotlib.use("Agg")
    import matplotlib.pyplot as plt
except ModuleNotFoundError:
    plt = None


LABEL_NAMES = {
    0: "normal",
    1: "drive_abnormal",
    2: "wheel_slip",
    3: "shaft_eccentricity",
}

EXPECTED_FEATURES = [
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

MODEL_CHOICES = [
    "baseline",
    "sage_cnn",
    "cwcnn_fa",
    "normal_cnn",
    "mlp",
    "lstm",
    "bilstm",
    "sage_depth_2",
    "sage_depth_3",
    "sage_depth_4",
    "sage_depth_5",
    "sage_depth_6",
    "sage_fa_pos_0",
    "sage_fa_pos_1",
    "sage_fa_pos_2",
    "sage_fa_pos_3",
    "sage_fa_pos_4",
    "sage_no_diff",
    "sage_no_saf",
    "sage_no_diff_gate",
]


def parse_args():
    parser = argparse.ArgumentParser(
        description="Train SAGE-CNN and module-level ablations with a strict train/validation/test protocol."
    )
    parser.add_argument("--data_dir", type=Path, required=True)
    parser.add_argument("--save_dir", type=Path, required=True)
    parser.add_argument("--model", choices=MODEL_CHOICES, default="sage_cnn")
    parser.add_argument("--epochs", type=int, default=30)
    parser.add_argument("--batch_size", type=int, default=64)
    parser.add_argument("--lr", type=float, default=0.001)
    parser.add_argument("--weight_decay", type=float, default=1e-5)
    parser.add_argument("--runs", type=int, default=5)
    parser.add_argument("--seed", type=int, default=42)
    parser.add_argument("--num_workers", type=int, default=0)
    parser.add_argument("--val_run_index", type=int, default=4)
    parser.add_argument(
        "--keep_preprocessed_scaler",
        action="store_true",
        help=(
            "Use the scaler already baked into the preprocessed dataset. By default the script "
            "inverts the saved preprocessing scaler and refits a new scaler on the strict "
            "training split only."
        ),
    )
    return parser.parse_args()


def set_seed(seed):
    random.seed(seed)
    np.random.seed(seed)
    torch.manual_seed(seed)
    if torch.cuda.is_available():
        torch.cuda.manual_seed_all(seed)


def load_dataset(data_dir):
    required = ["X_train.npy", "y_train.npy", "X_test.npy", "y_test.npy", "feature_config.json"]
    missing = [name for name in required if not (data_dir / name).exists()]
    if missing:
        raise FileNotFoundError(f"Missing required dataset files in {data_dir}: {missing}")

    x_train = np.load(data_dir / "X_train.npy")
    y_train = np.load(data_dir / "y_train.npy")
    x_test = np.load(data_dir / "X_test.npy")
    y_test = np.load(data_dir / "y_test.npy")
    with (data_dir / "feature_config.json").open("r", encoding="utf-8") as f:
        feature_config = json.load(f)
    return x_train, y_train, x_test, y_test, feature_config


def class_distribution(y):
    return dict(sorted(Counter(int(v) for v in y.tolist()).items()))


def check_dataset(x_train, y_train, x_test, y_test, feature_config):
    print("Dataset check")
    print(f"X_train.shape = {x_train.shape}")
    print(f"X_test.shape = {x_test.shape}")
    print(f"y_train.shape = {y_train.shape}")
    print(f"y_test.shape = {y_test.shape}")
    print(f"y_train class distribution = {class_distribution(y_train)}")
    print(f"y_test class distribution = {class_distribution(y_test)}")
    print(f"X_train has NaN = {bool(np.isnan(x_train).any())}")
    print(f"X_train has Inf = {bool(np.isinf(x_train).any())}")
    print(f"X_test has NaN = {bool(np.isnan(x_test).any())}")
    print(f"X_test has Inf = {bool(np.isinf(x_test).any())}")
    print(f"feature_config features = {feature_config.get('features')}")
    print(f"feature_config input_shape = {feature_config.get('input_shape')}")

    if x_train.shape[1:] != (15, 50) or x_test.shape[1:] != (15, 50):
        raise ValueError(f"Expected X shape [N, 15, 50], got {x_train.shape} and {x_test.shape}")
    if sorted(np.unique(y_train).tolist()) != [0, 1, 2, 3]:
        raise ValueError("y_train must contain labels 0, 1, 2, 3")
    if sorted(np.unique(y_test).tolist()) != [0, 1, 2, 3]:
        raise ValueError("y_test must contain labels 0, 1, 2, 3")
    if np.isnan(x_train).any() or np.isnan(x_test).any():
        raise ValueError("Dataset contains NaN")
    if np.isinf(x_train).any() or np.isinf(x_test).any():
        raise ValueError("Dataset contains Inf")
    if feature_config.get("features") != EXPECTED_FEATURES:
        raise ValueError("feature_config features do not match the expected 15-channel order")
    if feature_config.get("input_shape") != [15, 50]:
        raise ValueError("feature_config input_shape must be [15, 50]")

    print("Dataset check passed")
    print(
        "多源融合说明：本数据集的多源融合首先体现在样本级融合：将 odom、wheel_speed、IMU、current 四类传感器源在同一时间窗口内组织为 [15, 50] 的多通道时间序列样本。"
    )


def train_one_epoch(model, loader, criterion, optimizer, device):
    model.train()
    total_loss = 0.0
    total_samples = 0
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
        total_samples += batch_x.size(0)
    return total_loss / max(total_samples, 1)


def evaluate(model, loader, device):
    model.eval()
    all_pred = []
    all_true = []
    with torch.no_grad():
        for batch_x, batch_y in loader:
            batch_x = batch_x.to(device)
            logits = model(batch_x)
            if isinstance(logits, tuple):
                logits = logits[0]
            pred = torch.argmax(logits, dim=1).cpu().numpy()
            all_pred.append(pred)
            all_true.append(batch_y.numpy())

    y_true = np.concatenate(all_true)
    y_pred = np.concatenate(all_pred)
    return {
        "accuracy": accuracy_score(y_true, y_pred),
        "precision": precision_score(y_true, y_pred, average="macro", zero_division=0),
        "recall": recall_score(y_true, y_pred, average="macro", zero_division=0),
        "f1": f1_score(y_true, y_pred, average="macro", zero_division=0),
        "y_true": y_true,
        "y_pred": y_pred,
    }


def plot_confusion_matrix(cm, class_names, save_path):
    if plt is None:
        print(f"matplotlib is not installed; skipping confusion matrix plot: {save_path}")
        return
    fig, ax = plt.subplots(figsize=(7, 6))
    image = ax.imshow(cm, cmap="Blues")
    fig.colorbar(image, ax=ax)
    ax.set_xticks(np.arange(len(class_names)))
    ax.set_yticks(np.arange(len(class_names)))
    ax.set_xticklabels(class_names, rotation=30, ha="right")
    ax.set_yticklabels(class_names)
    ax.set_xlabel("Predicted Label")
    ax.set_ylabel("True Label")
    ax.set_title("Confusion Matrix")
    threshold = cm.max() / 2.0 if cm.size and cm.max() > 0 else 0
    for i in range(cm.shape[0]):
        for j in range(cm.shape[1]):
            ax.text(j, i, str(cm[i, j]), ha="center", va="center", color="white" if cm[i, j] > threshold else "black")
    fig.tight_layout()
    fig.savefig(save_path, dpi=200)
    plt.close(fig)


def read_meta_run_indices(path):
    run_indices = []
    with path.open("r", newline="", encoding="utf-8-sig") as f:
        reader = csv.DictReader(f)
        for row in reader:
            run_indices.append(int(row["run_index"]))
    return np.asarray(run_indices, dtype=np.int64)


def split_train_validation(data_dir, x_train_full, y_train_full, val_run_index):
    meta_path = data_dir / "meta_train.csv"
    if not meta_path.exists():
        raise FileNotFoundError(f"Missing meta file for strict split: {meta_path}")
    run_indices = read_meta_run_indices(meta_path)
    if run_indices.shape[0] != x_train_full.shape[0]:
        raise ValueError(
            f"meta_train rows ({run_indices.shape[0]}) do not match X_train samples ({x_train_full.shape[0]})"
        )

    val_mask = run_indices == val_run_index
    train_mask = ~val_mask
    if not val_mask.any():
        raise ValueError(f"No validation samples found for run_index={val_run_index}")
    if not train_mask.any():
        raise ValueError("No training samples left after validation split")

    return (
        x_train_full[train_mask],
        y_train_full[train_mask],
        x_train_full[val_mask],
        y_train_full[val_mask],
        run_indices[train_mask],
        run_indices[val_mask],
    )


def reshape_for_scaler(x):
    return x.transpose(0, 2, 1).reshape(-1, x.shape[1])


def restore_from_saved_scaler(x, saved_scaler):
    n, c, t = x.shape
    flat = reshape_for_scaler(x)
    restored = saved_scaler.inverse_transform(flat).reshape(n, t, c).transpose(0, 2, 1)
    return restored.astype(np.float32)


def transform_with_scaler(x, scaler):
    n, c, t = x.shape
    flat = reshape_for_scaler(x)
    scaled = scaler.transform(flat).reshape(n, t, c).transpose(0, 2, 1)
    return scaled.astype(np.float32)


def refit_scaler_on_strict_train(data_dir, scaler_name, x_train, x_val, x_test):
    scaler_path = data_dir / "scaler.pkl"
    if not scaler_path.exists():
        raise FileNotFoundError(f"Missing saved preprocessing scaler: {scaler_path}")

    saved_scaler = joblib.load(scaler_path)
    raw_train = restore_from_saved_scaler(x_train, saved_scaler)
    raw_val = restore_from_saved_scaler(x_val, saved_scaler)
    raw_test = restore_from_saved_scaler(x_test, saved_scaler)

    strict_scaler = MinMaxScaler() if scaler_name == "minmax" else StandardScaler()
    strict_scaler.fit(reshape_for_scaler(raw_train))
    return (
        transform_with_scaler(raw_train, strict_scaler),
        transform_with_scaler(raw_val, strict_scaler),
        transform_with_scaler(raw_test, strict_scaler),
        strict_scaler,
    )


def save_strict_log(path, rows):
    fieldnames = ["epoch", "train_loss", "val_accuracy", "val_precision", "val_recall", "val_f1"]
    with path.open("w", newline="", encoding="utf-8-sig") as f:
        writer = csv.DictWriter(f, fieldnames=fieldnames)
        writer.writeheader()
        writer.writerows(rows)


def plot_strict_curves(rows, save_path):
    if plt is None:
        print(f"matplotlib is not installed; skipping training curve plot: {save_path}")
        return
    epochs = [row["epoch"] for row in rows]
    train_loss = [row["train_loss"] for row in rows]
    val_f1 = [row["val_f1"] for row in rows]
    val_accuracy = [row["val_accuracy"] for row in rows]

    fig, axes = plt.subplots(1, 2, figsize=(10, 4))
    axes[0].plot(epochs, train_loss, marker="o", linewidth=1)
    axes[0].set_xlabel("Epoch")
    axes[0].set_ylabel("Train Loss")
    axes[0].set_title("Training Loss")

    axes[1].plot(epochs, val_accuracy, marker="o", linewidth=1, label="Val Accuracy")
    axes[1].plot(epochs, val_f1, marker="s", linewidth=1, label="Val Macro F1")
    axes[1].set_xlabel("Epoch")
    axes[1].set_ylabel("Metric")
    axes[1].set_ylim(0.0, 1.05)
    axes[1].set_title("Validation Metrics")
    axes[1].legend()

    fig.tight_layout()
    fig.savefig(save_path, dpi=200)
    plt.close(fig)


def save_split_config(path, feature_config, train_runs, val_runs, scaler_refit):
    config = dict(feature_config)
    config["strict_protocol"] = {
        "selection_metric": "validation_macro_f1",
        "train_run_indices": sorted(set(int(v) for v in train_runs.tolist())),
        "validation_run_indices": sorted(set(int(v) for v in val_runs.tolist())),
        "test_run_indices": [5],
        "scaler_refit_on_strict_train": bool(scaler_refit),
        "note": "Best checkpoint is selected on validation data; test data is used only for final reporting.",
    }
    with path.open("w", encoding="utf-8") as f:
        json.dump(config, f, ensure_ascii=False, indent=2)


def save_strict_report(path, model_name, val_metrics, test_metrics, class_names, cm):
    report = classification_report(
        test_metrics["y_true"],
        test_metrics["y_pred"],
        labels=[0, 1, 2, 3],
        target_names=class_names,
        digits=4,
        zero_division=0,
    )
    with path.open("w", encoding="utf-8-sig") as f:
        f.write("Strict SAGE-CNN experiment report\n\n")
        f.write(f"Model: {model_name}\n")
        f.write("Selection metric: validation Macro F1\n\n")
        f.write("Validation metrics at selected checkpoint:\n")
        f.write(f"Accuracy: {val_metrics['accuracy']:.6f}\n")
        f.write(f"Macro Precision: {val_metrics['precision']:.6f}\n")
        f.write(f"Macro Recall: {val_metrics['recall']:.6f}\n")
        f.write(f"Macro F1: {val_metrics['f1']:.6f}\n\n")
        f.write("Final test metrics:\n")
        f.write(f"Accuracy: {test_metrics['accuracy']:.6f}\n")
        f.write(f"Macro Precision: {test_metrics['precision']:.6f}\n")
        f.write(f"Macro Recall: {test_metrics['recall']:.6f}\n")
        f.write(f"Macro F1: {test_metrics['f1']:.6f}\n\n")
        f.write("Classification Report:\n")
        f.write(report)
        f.write("\n\nConfusion Matrix:\n")
        f.write(np.array2string(cm))
        f.write("\n")
    return report


def run_single_experiment(
    run_id,
    args,
    x_train,
    y_train,
    x_val,
    y_val,
    x_test,
    y_test,
    feature_config,
    train_runs,
    val_runs,
    device,
):
    run_dir = args.save_dir / f"run_{run_id:02d}"
    run_dir.mkdir(parents=True, exist_ok=True)
    set_seed(args.seed + run_id - 1)

    save_split_config(run_dir / "feature_config_used.json", feature_config, train_runs, val_runs, not args.keep_preprocessed_scaler)
    shutil.copyfile(args.data_dir / "meta_train.csv", run_dir / "meta_train_source.csv")
    shutil.copyfile(args.data_dir / "meta_test.csv", run_dir / "meta_test_source.csv")

    train_dataset = TensorDataset(torch.from_numpy(x_train).float(), torch.from_numpy(y_train).long())
    val_dataset = TensorDataset(torch.from_numpy(x_val).float(), torch.from_numpy(y_val).long())
    test_dataset = TensorDataset(torch.from_numpy(x_test).float(), torch.from_numpy(y_test).long())
    train_loader = DataLoader(train_dataset, batch_size=args.batch_size, shuffle=True, num_workers=args.num_workers)
    val_loader = DataLoader(val_dataset, batch_size=args.batch_size, shuffle=False, num_workers=args.num_workers)
    test_loader = DataLoader(test_dataset, batch_size=args.batch_size, shuffle=False, num_workers=args.num_workers)

    model = build_model(args.model, input_channels=15, num_classes=4).to(device)
    criterion = nn.CrossEntropyLoss()
    optimizer = torch.optim.Adam(model.parameters(), lr=args.lr, weight_decay=args.weight_decay)

    best_val_f1 = -1.0
    best_epoch = 0
    log_rows = []
    best_model_path = run_dir / "best_model.pth"

    for epoch in range(1, args.epochs + 1):
        train_loss = train_one_epoch(model, train_loader, criterion, optimizer, device)
        val_metrics = evaluate(model, val_loader, device)
        log_rows.append(
            {
                "epoch": epoch,
                "train_loss": train_loss,
                "val_accuracy": val_metrics["accuracy"],
                "val_precision": val_metrics["precision"],
                "val_recall": val_metrics["recall"],
                "val_f1": val_metrics["f1"],
            }
        )
        print(
            f"[{args.model} run {run_id:02d}] Epoch {epoch:03d}/{args.epochs} | "
            f"train_loss={train_loss:.6f} | val_accuracy={val_metrics['accuracy']:.6f} | "
            f"val_f1={val_metrics['f1']:.6f}"
        )

        if val_metrics["f1"] > best_val_f1:
            best_val_f1 = val_metrics["f1"]
            best_epoch = epoch
            torch.save(
                {
                    "epoch": epoch,
                    "model_state_dict": model.state_dict(),
                    "optimizer_state_dict": optimizer.state_dict(),
                    "best_val_f1": best_val_f1,
                    "feature_config": feature_config,
                    "label_names": LABEL_NAMES,
                    "model_name": args.model,
                    "selection_metric": "validation_macro_f1",
                },
                best_model_path,
            )

    save_strict_log(run_dir / "training_log.csv", log_rows)
    plot_strict_curves(log_rows, run_dir / "training_curves.png")

    checkpoint = torch.load(best_model_path, map_location=device, weights_only=False)
    model.load_state_dict(checkpoint["model_state_dict"])
    final_val_metrics = evaluate(model, val_loader, device)
    final_test_metrics = evaluate(model, test_loader, device)
    class_names = [LABEL_NAMES[i] for i in range(4)]
    cm = confusion_matrix(final_test_metrics["y_true"], final_test_metrics["y_pred"], labels=[0, 1, 2, 3])
    plot_confusion_matrix(cm, class_names, run_dir / "confusion_matrix.png")
    report = save_strict_report(
        run_dir / "classification_report.txt",
        args.model,
        final_val_metrics,
        final_test_metrics,
        class_names,
        cm,
    )

    print(f"[{args.model} run {run_id:02d}] best_epoch={best_epoch}, best_val_macro_f1={best_val_f1:.6f}")
    print(f"[{args.model} run {run_id:02d}] Test Accuracy={final_test_metrics['accuracy']:.6f}")
    print(f"[{args.model} run {run_id:02d}] Test Macro F1={final_test_metrics['f1']:.6f}")
    return {
        "run_id": run_id,
        "best_epoch": best_epoch,
        "best_val_f1": best_val_f1,
        "val_accuracy": final_val_metrics["accuracy"],
        "val_precision": final_val_metrics["precision"],
        "val_recall": final_val_metrics["recall"],
        "val_f1": final_val_metrics["f1"],
        "test_accuracy": final_test_metrics["accuracy"],
        "test_precision": final_test_metrics["precision"],
        "test_recall": final_test_metrics["recall"],
        "test_f1": final_test_metrics["f1"],
        "report": report,
        "cm": cm,
    }


def main():
    args = parse_args()
    args.save_dir.mkdir(parents=True, exist_ok=True)
    set_seed(args.seed)

    x_train_full, y_train_full, x_test, y_test, feature_config = load_dataset(args.data_dir)
    check_dataset(x_train_full, y_train_full, x_test, y_test, feature_config)
    x_train, y_train, x_val, y_val, train_runs, val_runs = split_train_validation(
        args.data_dir,
        x_train_full,
        y_train_full,
        args.val_run_index,
    )

    strict_scaler = None
    if args.keep_preprocessed_scaler:
        print("Using the scaler already stored in the preprocessed dataset.")
    else:
        print("Refitting scaler on strict training split only.")
        x_train, x_val, x_test, strict_scaler = refit_scaler_on_strict_train(
            args.data_dir,
            feature_config.get("scaler", "minmax"),
            x_train,
            x_val,
            x_test,
        )

    print("Strict split check")
    print(f"X_train_strict.shape = {x_train.shape}")
    print(f"X_val.shape = {x_val.shape}")
    print(f"X_test.shape = {x_test.shape}")
    print(f"train run indices = {sorted(set(int(v) for v in train_runs.tolist()))}")
    print(f"validation run indices = {sorted(set(int(v) for v in val_runs.tolist()))}")
    print(f"y_train_strict class distribution = {class_distribution(y_train)}")
    print(f"y_val class distribution = {class_distribution(y_val)}")
    print(f"y_test class distribution = {class_distribution(y_test)}")
    print(f"strict scaler refit = {not args.keep_preprocessed_scaler}")
    if strict_scaler is not None:
        joblib.dump(strict_scaler, args.save_dir / "strict_scaler.pkl")

    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    print(f"Using device: {device}")
    print(f"Selected model: {args.model}")

    run_results = []
    for run_id in range(1, args.runs + 1):
        run_results.append(
            run_single_experiment(
                run_id,
                args,
                x_train,
                y_train,
                x_val,
                y_val,
                x_test,
                y_test,
                feature_config,
                train_runs,
                val_runs,
                device,
            )
        )

    summary_path = args.save_dir / "summary_runs.csv"
    fieldnames = [
        "run_id",
        "val_accuracy",
        "val_precision",
        "val_recall",
        "val_f1",
        "test_accuracy",
        "test_precision",
        "test_recall",
        "test_f1",
        "best_epoch",
        "best_val_f1",
    ]
    with summary_path.open("w", newline="", encoding="utf-8-sig") as f:
        writer = csv.DictWriter(f, fieldnames=fieldnames)
        writer.writeheader()
        for row in run_results:
            writer.writerow({k: row[k] for k in fieldnames})

    if args.runs > 1:
        print("Strict summary across runs")
        for metric in ["test_accuracy", "test_precision", "test_recall", "test_f1"]:
            values = np.array([row[metric] for row in run_results], dtype=float)
            print(f"{metric}: {values.mean():.6f} +/- {values.std(ddof=0):.6f}")
    print(f"Saved strict summary to: {summary_path.resolve()}")


if __name__ == "__main__":
    main()
