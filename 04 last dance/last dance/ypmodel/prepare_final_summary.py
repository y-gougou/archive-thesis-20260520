import argparse
import csv
import json
import shutil
import subprocess
import sys
from pathlib import Path

import numpy as np

try:
    import matplotlib

    matplotlib.use("Agg")
    import matplotlib.pyplot as plt
except ModuleNotFoundError as exc:
    raise SystemExit("matplotlib is required to prepare final figures.") from exc


ROOT = Path(__file__).resolve().parent
OUT = ROOT / "results_final_summary"
TABLES = OUT / "tables"
FIGURES = OUT / "figures"
REPLAY = OUT / "replay"
DEPLOY_CHECK = OUT / "deployment_check"

MAIN = ROOT / "results_paper_main_vx05"
GEN = ROOT / "results_paper_generalization"
DEPLOY = ROOT / "results_deployment_robust"
DEFAULT_DESKTOP_MODEL = Path(r"D:\projects\01 ROS\turn_on_wheeltec_robot\desktop\models\sage_cnn")
DESKTOP_MODEL = DEFAULT_DESKTOP_MODEL

FEATURES = [
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
LABEL_MAP = {"normal": 0, "wheel_slip": 1, "drive_abnormal": 2, "shaft_eccentricity": 3}
LABEL_ORDER = ["normal", "wheel_slip", "drive_abnormal", "shaft_eccentricity"]

MAIN_MODELS = [
    "sage_cnn",
    "sage_no_saf",
    "normal_cnn",
    "sage_no_diff",
    "sage_no_diff_gate",
    "bilstm",
    "lstm",
    "cwcnn_fa",
    "mlp",
]
ABLATION_MODELS = ["sage_cnn", "sage_no_diff", "sage_no_saf", "sage_no_diff_gate"]
GEN_MODELS = ["sage_cnn", "sage_no_saf", "sage_no_diff_gate"]
DEPLOY_MODELS = ["sage_cnn", "sage_no_saf", "normal_cnn", "bilstm"]


def parse_args():
    parser = argparse.ArgumentParser(description="Prepare final frozen tables, figures, replay outputs, and reports.")
    parser.add_argument(
        "--desktop_model_dir",
        type=Path,
        default=DEFAULT_DESKTOP_MODEL,
        help="Desktop ONNX model package directory containing model_manifest.json.",
    )
    return parser.parse_args()


def read_csv(path):
    with path.open("r", newline="", encoding="utf-8-sig") as f:
        return list(csv.DictReader(f))


def write_csv(path, rows, fieldnames=None):
    path.parent.mkdir(parents=True, exist_ok=True)
    rows = list(rows)
    if fieldnames is None:
        fieldnames = list(rows[0].keys()) if rows else []
    with path.open("w", newline="", encoding="utf-8-sig") as f:
        writer = csv.DictWriter(f, fieldnames=fieldnames)
        writer.writeheader()
        writer.writerows(rows)


def load_json(path):
    with path.open("r", encoding="utf-8") as f:
        return json.load(f)


def value(row, key):
    return float(row[key])


def fmt(number, digits=4):
    return f"{float(number):.{digits}f}"


def fmt_pm(mean, std):
    return f"{fmt(mean)} ± {fmt(std)}"


def row_for(rows, model):
    for row in rows:
        if row["model"] == model:
            return row
    raise KeyError(model)


def rows_for_models(rows, models):
    lookup = {row["model"]: row for row in rows}
    return [lookup[model] for model in models if model in lookup]


def plot_bar(path, rows, title, ylim):
    labels = [row["model"] for row in rows]
    values = [value(row, "test_macro_f1_mean") for row in rows]
    errors = [value(row, "test_macro_f1_std") for row in rows]
    fig, ax = plt.subplots(figsize=(10, 5.2), dpi=180)
    bars = ax.bar(labels, values, yerr=errors, capsize=3, color="#326f9b", edgecolor="#27313a", linewidth=0.6)
    ax.set_title(title)
    ax.set_ylabel("Macro F1")
    ax.set_ylim(*ylim)
    ax.grid(axis="y", alpha=0.25)
    ax.tick_params(axis="x", rotation=25)
    for bar, score in zip(bars, values):
        ax.text(bar.get_x() + bar.get_width() / 2, score + 0.006, fmt(score, 3), ha="center", va="bottom", fontsize=8)
    fig.tight_layout()
    path.parent.mkdir(parents=True, exist_ok=True)
    fig.savefig(path)
    plt.close(fig)


def plot_generalization(path, rows):
    speeds = ["vx0.3", "vx0.5", "vx0.7"]
    lookup = {(row["model"], row["speed"]): row for row in rows}
    x = np.arange(len(speeds))
    width = 0.25
    colors = {"sage_cnn": "#2f6f9f", "sage_no_saf": "#d08c2f", "sage_no_diff_gate": "#6b7280"}
    fig, ax = plt.subplots(figsize=(9.2, 5.2), dpi=180)
    for index, model in enumerate(GEN_MODELS):
        offset = (index - 1) * width
        vals = [value(lookup[(model, speed)], "test_macro_f1_mean") for speed in speeds]
        errs = [value(lookup[(model, speed)], "test_macro_f1_std") for speed in speeds]
        ax.bar(x + offset, vals, width, yerr=errs, capsize=3, label=model, color=colors[model])
        for xpos, val in zip(x + offset, vals):
            ax.text(xpos, val + 0.008, fmt(val, 3), ha="center", fontsize=7)
    ax.set_xticks(x)
    ax.set_xticklabels(speeds)
    ax.set_ylim(0.68, 1.02)
    ax.set_ylabel("Macro F1")
    ax.set_title("Cross-speed Generalization Macro F1")
    ax.grid(axis="y", alpha=0.25)
    ax.legend()
    fig.tight_layout()
    path.parent.mkdir(parents=True, exist_ok=True)
    fig.savefig(path)
    plt.close(fig)


def plot_postprocess(path, rows):
    labels = [row["method"] for row in rows]
    macro_f1 = [value(row, "macro_f1") for row in rows]
    false_alarm = [value(row, "normal_false_alarm_rate") for row in rows]
    miss = [value(row, "fault_miss_rate") for row in rows]
    x = np.arange(len(rows))
    width = 0.26
    fig, ax = plt.subplots(figsize=(9, 5.2), dpi=180)
    ax.bar(x - width, macro_f1, width, label="Macro F1", color="#2f6f9f")
    ax.bar(x, false_alarm, width, label="Normal false alarm", color="#c7534f")
    ax.bar(x + width, miss, width, label="Fault miss", color="#d08c2f")
    ax.set_xticks(x)
    ax.set_xticklabels(labels)
    ax.set_ylim(0.0, 1.05)
    ax.set_title("Deployment Postprocess Comparison (SAGE-CNN run_03)")
    ax.grid(axis="y", alpha=0.25)
    ax.legend()
    for xpos, val in zip(x - width, macro_f1):
        ax.text(xpos, val + 0.015, fmt(val, 3), ha="center", fontsize=8)
    fig.tight_layout()
    path.parent.mkdir(parents=True, exist_ok=True)
    fig.savefig(path)
    plt.close(fig)


def make_postprocess_table(post_summary):
    run = next(row for row in post_summary if row["model"] == "sage_cnn" and row["run_id"] == "3")
    return [
        {
            "model": "sage_cnn",
            "run_id": "3",
            "method": "raw",
            "accuracy": run["raw_accuracy"],
            "macro_f1": run["raw_macro_f1"],
            "normal_false_alarm_rate": run["raw_normal_false_alarm_rate"],
            "fault_miss_rate": run["raw_fault_miss_rate"],
        },
        {
            "model": "sage_cnn",
            "run_id": "3",
            "method": "majority_vote",
            "accuracy": run["majority_accuracy"],
            "macro_f1": run["majority_macro_f1"],
            "normal_false_alarm_rate": run["majority_normal_false_alarm_rate"],
            "fault_miss_rate": run["majority_fault_miss_rate"],
        },
        {
            "model": "sage_cnn",
            "run_id": "3",
            "method": "probability_moving_average",
            "accuracy": run["prob_avg_accuracy"],
            "macro_f1": run["prob_avg_macro_f1"],
            "normal_false_alarm_rate": run["prob_avg_normal_false_alarm_rate"],
            "fault_miss_rate": run["prob_avg_fault_miss_rate"],
        },
    ]


def copy_or_regenerate_confusion_matrix():
    dst = FIGURES / "fig_sage_cnn_main_confusion_matrix.png"
    main_runs = [row for row in read_csv(MAIN / "summaries" / "all_runs.csv") if row["model"] == "sage_cnn"]
    best_by_val = max(main_runs, key=lambda row: float(row["best_val_macro_f1"])) if main_runs else None
    candidates = []
    if best_by_val is not None:
        run_id = int(best_by_val["run_id"])
        candidates.append(MAIN / "checkpoints" / "sage_cnn" / f"run_{run_id:02d}" / "confusion_matrix.png")
    candidates.extend(
        [
            MAIN / "figures" / "best_model_confusion_matrix.png",
            FIGURES / "sage_cnn_main_vx05_confusion_matrix.png",
        ]
    )
    for src in candidates:
        if src.exists():
            shutil.copyfile(src, dst)
            return
    raise FileNotFoundError("Could not find SAGE-CNN main-condition confusion matrix.")


def select_replay_files():
    rows = read_csv(DEPLOY / "splits" / "test_files.csv")
    selected = {}
    preferred = {
        "normal": "normal_vx0.5_run03.csv",
        "wheel_slip": "wheel_slip_B_vx0.3_run01.csv",
        "drive_abnormal": "drive_abnormal_B_alpha0.3_vx0.5_run01.csv",
        "shaft_eccentricity": "shaft_eccentricity_C_vx0.5_run06.csv",
    }
    for row in rows:
        label = row["label_name"]
        if label in preferred and row["csv_file"] == preferred[label]:
            selected[label] = Path(row["path"])
    for row in rows:
        selected.setdefault(row["label_name"], Path(row["path"]))
    missing = [label for label in LABEL_ORDER if label not in selected]
    if missing:
        raise RuntimeError(f"Missing replay source CSV for classes: {missing}")
    return selected


def run_replays():
    selected = select_replay_files()
    for label, csv_path in selected.items():
        output_dir = REPLAY / label
        cmd = [
            sys.executable,
            str(ROOT / "replay_inference.py"),
            str(csv_path),
            "--export_dir",
            str(DESKTOP_MODEL),
            "--output_dir",
            str(output_dir),
        ]
        subprocess.run(cmd, cwd=str(ROOT), check=True)
    return selected


def deployment_check_report():
    DEPLOY_CHECK.mkdir(parents=True, exist_ok=True)
    required = [
        "model_manifest.json",
        "sage_cnn_selected_best_model.onnx",
        "scaler.json",
        "feature_config_used.json",
        "realtime_sage_cnn_guard_config.json",
    ]
    files = {name: (DESKTOP_MODEL / name).exists() for name in required}
    manifest = load_json(DESKTOP_MODEL / "model_manifest.json")
    feature_config = load_json(DESKTOP_MODEL / "feature_config_used.json")
    guard = load_json(DESKTOP_MODEL / "realtime_sage_cnn_guard_config.json")
    checks = {
        "required_files_present": all(files.values()),
        "feature_order_fixed_15": feature_config.get("features") == FEATURES,
        "label_order_fixed": manifest.get("labels") == LABEL_ORDER and feature_config.get("label_map") == LABEL_MAP,
        "input_shape_1_15_50": manifest.get("input_shape") == [1, 15, 50],
        "majority_vote_n5_confirm4": guard.get("vote_window_size") == 5 and guard.get("vote_required_count") == 4,
    }
    lines = [
        "# Deployment Config Check Report",
        "",
        f"Desktop model package: `{DESKTOP_MODEL}`",
        "",
        "## Required Files",
        "",
    ]
    for name, ok in files.items():
        lines.append(f"- `{name}`: {'OK' if ok else 'MISSING'}")
    lines.extend(
        [
            "",
            "## Configuration Checks",
            "",
        ]
    )
    for name, ok in checks.items():
        lines.append(f"- `{name}`: {'OK' if ok else 'FAILED'}")
    lines.extend(
        [
            "",
            "## Fixed Feature Order",
            "",
            ", ".join(FEATURES),
            "",
            "## Label Order",
            "",
        ]
    )
    for label, index in LABEL_MAP.items():
        lines.append(f"- {index}: {label}")
    lines.extend(
        [
            "",
            "## Postprocess",
            "",
            "- method: majority_vote",
            f"- N: {guard.get('vote_window_size')}",
            f"- confirm_count: {guard.get('vote_required_count')}",
            "",
            f"Overall status: {'PASS' if all(checks.values()) else 'CHECK NEEDED'}",
            "",
        ]
    )
    report_path = DEPLOY_CHECK / "deployment_config_check_report.md"
    report_path.write_text("\n".join(lines), encoding="utf-8")
    return checks, report_path


def md_table(rows, columns):
    header = "| " + " | ".join(title for title, _ in columns) + " |"
    sep = "| " + " | ".join("---" for _ in columns) + " |"
    body = ["| " + " | ".join(str(func(row)) for _, func in columns) + " |" for row in rows]
    return "\n".join([header, sep, *body])


def replay_summary_rows():
    rows = []
    for label in LABEL_ORDER:
        path = REPLAY / label / "replay_summary.json"
        if path.exists():
            data = load_json(path)
            rows.append(
                {
                    "class": label,
                    "window_count": data.get("window_count", 0),
                    "mean_raw_confidence": data.get("mean_raw_confidence", 0),
                    "raw_counts": data.get("raw_counts", {}),
                    "majority_counts": data.get("majority_counts", {}),
                }
            )
    return rows


def write_final_report(main_rows, ablation_rows, gen_rows, deploy_rows, post_rows, replay_files, deploy_checks):
    sage_main = row_for(main_rows, "sage_cnn")
    sage_no_saf = row_for(main_rows, "sage_no_saf")
    gen_lookup = {(row["model"], row["speed"]): row for row in gen_rows}
    replay_rows = replay_summary_rows()
    report = f"""# Final Experiment Summary

## 1. Dataset And Preprocessing

The final experiment materials use the fixed four-class label order: `0 normal`, `1 wheel_slip`, `2 drive_abnormal`, `3 shaft_eccentricity`. The input feature order is fixed to 15 channels:

`{", ".join(FEATURES)}`

The unified input layout is `[N, 15, 50]`, namely batch/channel/time. The scaler, feature order, and label map are kept consistent with the deployed desktop ONNX package.

## 2. Main-condition Diagnosis Results

The paper main experiment is `paper_main_vx05`, and the paper main model is SAGE-CNN. The fixed main-condition result for SAGE-CNN is:

- Accuracy = 0.9803
- Macro F1 = 0.9647

{md_table(main_rows, [
    ("Model", lambda r: r["model"]),
    ("Accuracy", lambda r: fmt_pm(r["test_accuracy_mean"], r["test_accuracy_std"])),
    ("Macro F1", lambda r: fmt_pm(r["test_macro_f1_mean"], r["test_macro_f1_std"])),
])}

The main-condition Macro F1 bar chart is `figures/fig_main_macro_f1_bar.png`, and the SAGE-CNN confusion matrix is `figures/fig_sage_cnn_main_confusion_matrix.png`.

## 3. Ablation Study

{md_table(ablation_rows, [
    ("Model", lambda r: r["model"]),
    ("Accuracy", lambda r: fmt_pm(r["test_accuracy_mean"], r["test_accuracy_std"])),
    ("Macro F1", lambda r: fmt_pm(r["test_macro_f1_mean"], r["test_macro_f1_std"])),
])}

SAGE-CNN and `sage_no_saf` show very close main-condition performance: SAGE-CNN Macro F1 is {fmt(sage_main["test_macro_f1_mean"])}, while `sage_no_saf` Macro F1 is {fmt(sage_no_saf["test_macro_f1_mean"])}. This should be described as comparable performance, not as a forced superiority claim. The clearer drop in `sage_no_diff` and `sage_no_diff_gate` supports the contribution of the temporal-difference module.

## 4. Cross-speed Generalization

{md_table(gen_rows, [
    ("Model", lambda r: r["model"]),
    ("Speed", lambda r: r["speed"]),
    ("Accuracy", lambda r: fmt_pm(r["test_accuracy_mean"], r["test_accuracy_std"])),
    ("Macro F1", lambda r: fmt_pm(r["test_macro_f1_mean"], r["test_macro_f1_std"])),
])}

For SAGE-CNN, Macro F1 is {fmt(gen_lookup[("sage_cnn", "vx0.3")]["test_macro_f1_mean"])} at vx0.3, {fmt(gen_lookup[("sage_cnn", "vx0.5")]["test_macro_f1_mean"])} at vx0.5, and {fmt(gen_lookup[("sage_cnn", "vx0.7")]["test_macro_f1_mean"])} at vx0.7. The vx0.7 decrease is best explained as speed-condition distribution shift in the sensor signals, rather than model failure. The `sage_no_saf` result is also retained because it is competitive, especially on vx0.7.

## 5. Deployment Robustness And Postprocessing

The default deployed model is SAGE-CNN run_03. The candidate model is `sage_no_saf run_03`.

{md_table(deploy_rows, [
    ("Model", lambda r: r["model"]),
    ("Accuracy", lambda r: fmt_pm(r["test_accuracy_mean"], r["test_accuracy_std"])),
    ("Macro F1", lambda r: fmt_pm(r["test_macro_f1_mean"], r["test_macro_f1_std"])),
])}

{md_table(post_rows, [
    ("Method", lambda r: r["method"]),
    ("Accuracy", lambda r: fmt(r["accuracy"])),
    ("Macro F1", lambda r: fmt(r["macro_f1"])),
    ("Normal false alarm", lambda r: fmt(r["normal_false_alarm_rate"])),
    ("Fault miss", lambda r: fmt(r["fault_miss_rate"])),
])}

Majority vote is recommended for real-car deployment, with `N=5` and `confirm_count=4`. It substantially reduces normal false alarms and stabilizes the alarm output while keeping the missed-fault rate acceptable.

## 6. Replay Validation

Replay validation was run with the desktop ONNX package at:

`{DESKTOP_MODEL}`

Each CSV was replayed independently, and the postprocess queues were reset per file.

{md_table(replay_rows, [
    ("Class", lambda r: r["class"]),
    ("Windows", lambda r: r["window_count"]),
    ("Mean confidence", lambda r: fmt(r["mean_raw_confidence"])),
    ("Replay CSV", lambda r: replay_files[r["class"]].name),
])}

Each replay directory contains `prediction_timeline.csv`, `prediction_timeline.png`, and `replay_summary.json`.

## 7. Desktop Deployment Check

Deployment package check result: {'PASS' if all(deploy_checks.values()) else 'CHECK NEEDED'}.

The checked package contains `model_manifest.json`, `sage_cnn_selected_best_model.onnx`, `scaler.json`, `feature_config_used.json`, and `realtime_sage_cnn_guard_config.json`. The manifest input shape is `[1, 15, 50]`, the label order is fixed, and the realtime guard config uses majority vote with `N=5`, `confirm_count=4`.

See `deployment_check/deployment_config_check_report.md` for details.

## 8. Final Recommendations

Use SAGE-CNN as the paper main model and report the main-condition result as Accuracy = 0.9803 and Macro F1 = 0.9647. Use SAGE-CNN run_03 as the default deployment model. Keep `sage_no_saf run_03` as a candidate for continued vehicle replay comparison. For real-car testing, enable majority vote by default with `N=5` and `confirm_count=4`.
"""
    (OUT / "report_final_experiment_summary.md").write_text(report, encoding="utf-8")


def main():
    global DESKTOP_MODEL
    args = parse_args()
    DESKTOP_MODEL = args.desktop_model_dir.resolve()

    for path in [TABLES, FIGURES, REPLAY, DEPLOY_CHECK]:
        path.mkdir(parents=True, exist_ok=True)

    main_summary = read_csv(MAIN / "summaries" / "main_vx0.5_summary.csv")
    gen_summary = read_csv(GEN / "summaries" / "generalization_all_summary.csv")
    deploy_summary = read_csv(DEPLOY / "summaries" / "deployment_summary.csv")
    post_summary = read_csv(DEPLOY / "summaries" / "postprocess_summary.csv")

    main_rows = rows_for_models(main_summary, MAIN_MODELS)
    ablation_rows = rows_for_models(main_summary, ABLATION_MODELS)
    gen_rows = [row for row in gen_summary if row["model"] in GEN_MODELS]
    gen_rows.sort(key=lambda r: (GEN_MODELS.index(r["model"]), r["speed"]))
    deploy_rows = rows_for_models(deploy_summary, DEPLOY_MODELS)
    post_rows = make_postprocess_table(post_summary)
    label_rows = [{"label": index, "class_name": name} for name, index in LABEL_MAP.items()]

    write_csv(TABLES / "table_main_model_comparison.csv", main_rows)
    write_csv(TABLES / "table_ablation.csv", ablation_rows)
    write_csv(TABLES / "table_generalization.csv", gen_rows)
    write_csv(TABLES / "table_deployment_robust.csv", deploy_rows)
    write_csv(TABLES / "table_postprocess.csv", post_rows)
    write_csv(TABLES / "table_label_map.csv", label_rows, ["label", "class_name"])

    plot_bar(FIGURES / "fig_main_macro_f1_bar.png", main_rows, "Main-condition Macro F1", (0.86, 1.0))
    copy_or_regenerate_confusion_matrix()
    plot_bar(FIGURES / "fig_ablation_macro_f1_bar.png", ablation_rows, "Ablation Macro F1", (0.90, 1.0))
    plot_generalization(FIGURES / "fig_generalization_macro_f1.png", gen_rows)
    plot_postprocess(FIGURES / "fig_postprocess_comparison.png", post_rows)

    replay_files = run_replays()
    deploy_checks, _ = deployment_check_report()
    write_final_report(main_rows, ablation_rows, gen_rows, deploy_rows, post_rows, replay_files, deploy_checks)
    print(f"Final summary prepared: {OUT}")


if __name__ == "__main__":
    main()
