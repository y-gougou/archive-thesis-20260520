import csv
import json
import math
import shutil
from pathlib import Path

import numpy as np

try:
    import matplotlib

    matplotlib.use("Agg")
    import matplotlib.pyplot as plt
except ModuleNotFoundError as exc:
    raise SystemExit("matplotlib is required to freeze figures. Install it before running this script.") from exc


ROOT = Path(__file__).resolve().parent
OUT = ROOT / "results_final_summary"
TABLES = OUT / "tables"
FIGURES = OUT / "figures"
REPORT = OUT / "report_final_experiment_summary.md"

MAIN = ROOT / "results_paper_main_vx05"
GEN = ROOT / "results_paper_generalization"
DEPLOY = ROOT / "results_deployment_robust"

LABELS = ["normal", "wheel_slip", "drive_abnormal", "shaft_eccentricity"]
ABLATION_MODELS = ["sage_cnn", "sage_no_diff", "sage_no_saf", "sage_no_diff_gate"]
DEPLOY_COMPARE_MODELS = ["sage_cnn", "sage_no_saf"]


def read_csv(path):
    with path.open("r", newline="", encoding="utf-8-sig") as f:
        return list(csv.DictReader(f))


def write_csv(path, rows, fieldnames):
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", newline="", encoding="utf-8-sig") as f:
        writer = csv.DictWriter(f, fieldnames=fieldnames)
        writer.writeheader()
        writer.writerows(rows)


def f(row, key):
    return float(row[key])


def fmt(value, digits=4):
    return f"{float(value):.{digits}f}"


def fmt_pm(mean, std):
    return f"{fmt(mean)} ± {fmt(std)}"


def find_row(rows, model):
    for row in rows:
        if row["model"] == model:
            return row
    raise KeyError(model)


def plot_bar(path, rows, metric_key, std_key, title, ylabel, color="#4477aa", ylim=None):
    labels = [row["model"] for row in rows]
    values = [f(row, metric_key) for row in rows]
    errors = [f(row, std_key) for row in rows] if std_key else None
    fig, ax = plt.subplots(figsize=(10, 5.4), dpi=160)
    ax.bar(labels, values, yerr=errors, color=color, edgecolor="#1f2933", linewidth=0.6, capsize=3)
    ax.set_title(title)
    ax.set_ylabel(ylabel)
    ax.set_ylim(*(ylim or (0.0, 1.0)))
    ax.grid(axis="y", alpha=0.25)
    ax.tick_params(axis="x", rotation=25)
    for index, value in enumerate(values):
        ax.text(index, value + 0.01, fmt(value, 3), ha="center", va="bottom", fontsize=8)
    fig.tight_layout()
    path.parent.mkdir(parents=True, exist_ok=True)
    fig.savefig(path)
    plt.close(fig)


def plot_generalization(path, rows):
    models = DEPLOY_COMPARE_MODELS
    speeds = ["vx0.3", "vx0.5", "vx0.7"]
    lookup = {(row["model"], row["speed"]): row for row in rows}
    x = np.arange(len(speeds))
    width = 0.34
    fig, ax = plt.subplots(figsize=(8, 5.2), dpi=160)
    colors = {"sage_cnn": "#2f6f9f", "sage_no_saf": "#d08c2f"}
    for offset, model in zip([-width / 2, width / 2], models):
        values = [f(lookup[(model, speed)], "test_macro_f1_mean") for speed in speeds]
        errors = [f(lookup[(model, speed)], "test_macro_f1_std") for speed in speeds]
        ax.bar(x + offset, values, width, yerr=errors, label=model, color=colors[model], capsize=3)
        for xpos, value in zip(x + offset, values):
            ax.text(xpos, value + 0.012, fmt(value, 3), ha="center", fontsize=8)
    ax.set_xticks(x)
    ax.set_xticklabels(speeds)
    ax.set_ylim(0.65, 1.02)
    ax.set_ylabel("Macro F1")
    ax.set_title("Cross-speed Generalization Macro F1")
    ax.grid(axis="y", alpha=0.25)
    ax.legend()
    fig.tight_layout()
    path.parent.mkdir(parents=True, exist_ok=True)
    fig.savefig(path)
    plt.close(fig)


def plot_postprocess(path, row):
    labels = ["Raw", "Majority vote", "Probability avg"]
    values = [f(row, "raw_macro_f1"), f(row, "majority_macro_f1"), f(row, "prob_avg_macro_f1")]
    false_alarm = [
        f(row, "raw_normal_false_alarm_rate"),
        f(row, "majority_normal_false_alarm_rate"),
        f(row, "prob_avg_normal_false_alarm_rate"),
    ]
    x = np.arange(len(labels))
    width = 0.35
    fig, ax = plt.subplots(figsize=(8.5, 5), dpi=160)
    ax.bar(x - width / 2, values, width, label="Macro F1", color="#2f6f9f")
    ax.bar(x + width / 2, false_alarm, width, label="Normal false alarm", color="#c7534f")
    ax.set_xticks(x)
    ax.set_xticklabels(labels)
    ax.set_ylim(0.0, 1.05)
    ax.set_title("Deployment Postprocess Comparison (sage_cnn run_03)")
    ax.grid(axis="y", alpha=0.25)
    ax.legend()
    for xpos, value in zip(x - width / 2, values):
        ax.text(xpos, value + 0.015, fmt(value, 3), ha="center", fontsize=8)
    for xpos, value in zip(x + width / 2, false_alarm):
        ax.text(xpos, value + 0.015, fmt(value, 3), ha="center", fontsize=8)
    fig.tight_layout()
    path.parent.mkdir(parents=True, exist_ok=True)
    fig.savefig(path)
    plt.close(fig)


def markdown_table(rows, columns):
    header = "| " + " | ".join(title for title, _ in columns) + " |"
    sep = "| " + " | ".join("---" for _ in columns) + " |"
    body = []
    for row in rows:
        body.append("| " + " | ".join(str(func(row)) for _, func in columns) + " |")
    return "\n".join([header, sep, *body])


def main():
    TABLES.mkdir(parents=True, exist_ok=True)
    FIGURES.mkdir(parents=True, exist_ok=True)

    main_summary = read_csv(MAIN / "summaries" / "main_vx0.5_summary.csv")
    main_runs = read_csv(MAIN / "summaries" / "all_runs.csv")
    gen_summary = read_csv(GEN / "summaries" / "generalization_all_summary.csv")
    deploy_summary = read_csv(DEPLOY / "summaries" / "deployment_summary.csv")
    post_summary = read_csv(DEPLOY / "summaries" / "postprocess_summary.csv")

    main_sorted = sorted(main_summary, key=lambda row: f(row, "test_macro_f1_mean"), reverse=True)
    ablation_rows = [find_row(main_summary, model) for model in ABLATION_MODELS]
    gen_compare = [row for row in gen_summary if row["model"] in DEPLOY_COMPARE_MODELS]
    deploy_sorted = sorted(deploy_summary, key=lambda row: f(row, "test_macro_f1_mean"), reverse=True)
    deploy_compare = [find_row(deploy_summary, model) for model in DEPLOY_COMPARE_MODELS]
    post_default = next(row for row in post_summary if row["model"] == "sage_cnn" and row["run_id"] == "3")
    post_candidate = next(row for row in post_summary if row["model"] == "sage_no_saf" and row["run_id"] == "3")

    write_csv(TABLES / "paper_main_model_comparison.csv", main_sorted, main_sorted[0].keys())
    write_csv(TABLES / "ablation_sage_results.csv", ablation_rows, ablation_rows[0].keys())
    write_csv(TABLES / "generalization_sage_cnn_vs_sage_no_saf.csv", gen_compare, gen_compare[0].keys())
    write_csv(TABLES / "deployment_model_comparison.csv", deploy_sorted, deploy_sorted[0].keys())
    write_csv(TABLES / "deployment_postprocess_default_vs_candidate.csv", [post_default, post_candidate], post_default.keys())

    plot_bar(
        FIGURES / "paper_main_macro_f1_bar.png",
        main_sorted,
        "test_macro_f1_mean",
        "test_macro_f1_std",
        "Paper Main vx0.5 Model Comparison",
        "Macro F1",
        color="#3d6f9f",
        ylim=(0.84, 1.0),
    )
    plot_bar(
        FIGURES / "ablation_macro_f1_bar.png",
        ablation_rows,
        "test_macro_f1_mean",
        "test_macro_f1_std",
        "SAGE-CNN Ablation Macro F1",
        "Macro F1",
        color="#5a8f5a",
        ylim=(0.88, 1.0),
    )
    plot_generalization(FIGURES / "generalization_macro_f1_vx03_vx05_vx07.png", gen_compare)
    plot_postprocess(FIGURES / "deployment_postprocess_macro_f1_false_alarm.png", post_default)

    sage_runs = [row for row in main_runs if row["model"] == "sage_cnn"]
    main_best_run = max(sage_runs, key=lambda row: f(row, "best_val_macro_f1"))
    best_cm_src = MAIN / "checkpoints" / "sage_cnn" / f"run_{int(main_best_run['run_id']):02d}" / "confusion_matrix.png"
    best_cm_dst = FIGURES / "sage_cnn_main_vx05_confusion_matrix.png"
    if best_cm_src.exists():
        shutil.copyfile(best_cm_src, best_cm_dst)

    manifest = {
        "paper_main_model": "sage_cnn",
        "paper_main_best_run_by_val_macro_f1": int(main_best_run["run_id"]),
        "default_deployment_model": "sage_cnn",
        "default_deployment_run": 3,
        "default_export_dir": str((DEPLOY / "export").resolve()),
        "candidate_deployment_model": "sage_no_saf",
        "candidate_deployment_run": 3,
        "candidate_checkpoint": str((DEPLOY / "checkpoints" / "sage_no_saf" / "run_03" / "best_model.pth").resolve()),
        "recommended_realtime_postprocess": {"method": "majority_vote", "window_count": 5, "confirm_count": 4},
        "fixed_feature_count": 15,
        "label_order": LABELS,
    }
    with (OUT / "deployment_candidate_manifest.json").open("w", encoding="utf-8") as fobj:
        json.dump(manifest, fobj, ensure_ascii=False, indent=2)

    sage_main = find_row(main_summary, "sage_cnn")
    sage_no_saf_main = find_row(main_summary, "sage_no_saf")
    sage_deploy = find_row(deploy_summary, "sage_cnn")
    saf_deploy = find_row(deploy_summary, "sage_no_saf")
    gen_sage = [row for row in gen_summary if row["model"] == "sage_cnn"]
    gen_saf = [row for row in gen_summary if row["model"] == "sage_no_saf"]

    report = f"""# Final Experiment Summary

## 1. Main-condition Diagnosis Results

The paper main experiment is fixed to `paper_main_vx05`, where training, validation, and test data all come from the vx0.5 main operating condition. The paper main model is fixed as `sage_cnn`.

{markdown_table(main_sorted, [
    ("Model", lambda r: r["model"]),
    ("Accuracy", lambda r: fmt_pm(r["test_accuracy_mean"], r["test_accuracy_std"])),
    ("Macro F1", lambda r: fmt_pm(r["test_macro_f1_mean"], r["test_macro_f1_std"])),
    ("Val Macro F1", lambda r: fmt_pm(r["best_val_macro_f1_mean"], r["best_val_macro_f1_std"])),
])}

`sage_cnn` reaches Accuracy {fmt_pm(sage_main["test_accuracy_mean"], sage_main["test_accuracy_std"])} and Macro F1 {fmt_pm(sage_main["test_macro_f1_mean"], sage_main["test_macro_f1_std"])} on the vx0.5 test set. This result is the recommended paper main result. The copied SAGE-CNN confusion matrix is `figures/sage_cnn_main_vx05_confusion_matrix.png`, and the main Macro F1 comparison is `figures/paper_main_macro_f1_bar.png`.

## 2. Ablation Study

The ablation analysis compares the full SAGE-CNN against three variants: removing temporal difference features, removing source-aware fusion, and removing both difference and gate-related components.

{markdown_table(ablation_rows, [
    ("Model", lambda r: r["model"]),
    ("Accuracy", lambda r: fmt_pm(r["test_accuracy_mean"], r["test_accuracy_std"])),
    ("Macro F1", lambda r: fmt_pm(r["test_macro_f1_mean"], r["test_macro_f1_std"])),
])}

The full `sage_cnn` and `sage_no_saf` are very close on vx0.5: `sage_cnn` Macro F1 is {fmt(sage_main["test_macro_f1_mean"])}, while `sage_no_saf` Macro F1 is {fmt(sage_no_saf_main["test_macro_f1_mean"])}. Therefore, the result should be described objectively as comparable performance rather than as a strict gap. Removing temporal-difference information causes a clearer decrease, which supports the value of temporal gradient features for this dataset.

## 3. Cross-speed Generalization

Models trained on vx0.5 were evaluated directly on vx0.3 and vx0.7 without retraining or recalculating the scaler.

{markdown_table(gen_compare, [
    ("Model", lambda r: r["model"]),
    ("Speed", lambda r: r["speed"]),
    ("Accuracy", lambda r: fmt_pm(r["test_accuracy_mean"], r["test_accuracy_std"])),
    ("Macro F1", lambda r: fmt_pm(r["test_macro_f1_mean"], r["test_macro_f1_std"])),
])}

For `sage_cnn`, Macro F1 changes from {fmt(next(r for r in gen_sage if r["speed"] == "vx0.5")["test_macro_f1_mean"])} at vx0.5 to {fmt(next(r for r in gen_sage if r["speed"] == "vx0.3")["test_macro_f1_mean"])} at vx0.3 and {fmt(next(r for r in gen_sage if r["speed"] == "vx0.7")["test_macro_f1_mean"])} at vx0.7. The decrease at vx0.7 should be interpreted as a speed-condition distribution shift in sensor signals, not as model failure. `sage_no_saf` performs better than `sage_cnn` at vx0.7 in this fixed evaluation, which suggests that the source-aware fusion module may be more tuned to the main speed condition and should be discussed carefully.

## 4. Deployment Robustness And Postprocessing

The default deployment export remains `sage_cnn run_03`, selected by the highest validation Macro F1 rule. `sage_no_saf run_03` is retained as a candidate checkpoint for replay or vehicle-side comparison.

{markdown_table(deploy_compare, [
    ("Model", lambda r: r["model"]),
    ("Accuracy", lambda r: fmt_pm(r["test_accuracy_mean"], r["test_accuracy_std"])),
    ("Macro F1", lambda r: fmt_pm(r["test_macro_f1_mean"], r["test_macro_f1_std"])),
    ("Val Macro F1", lambda r: fmt_pm(r["best_val_macro_f1_mean"], r["best_val_macro_f1_std"])),
])}

For the default deployment model `sage_cnn run_03`, realtime postprocessing gives:

{markdown_table([
    {"method": "raw", "accuracy": post_default["raw_accuracy"], "macro_f1": post_default["raw_macro_f1"], "false_alarm": post_default["raw_normal_false_alarm_rate"], "miss": post_default["raw_fault_miss_rate"]},
    {"method": "majority_vote", "accuracy": post_default["majority_accuracy"], "macro_f1": post_default["majority_macro_f1"], "false_alarm": post_default["majority_normal_false_alarm_rate"], "miss": post_default["majority_fault_miss_rate"]},
    {"method": "probability_moving_average", "accuracy": post_default["prob_avg_accuracy"], "macro_f1": post_default["prob_avg_macro_f1"], "false_alarm": post_default["prob_avg_normal_false_alarm_rate"], "miss": post_default["prob_avg_fault_miss_rate"]},
], [
    ("Method", lambda r: r["method"]),
    ("Accuracy", lambda r: fmt(r["accuracy"])),
    ("Macro F1", lambda r: fmt(r["macro_f1"])),
    ("Normal False Alarm", lambda r: fmt(r["false_alarm"])),
    ("Fault Miss", lambda r: fmt(r["miss"])),
])}

The recommended realtime default is majority vote with `N=5` and `confirm_count=4`. It gives a strong Macro F1 improvement while keeping the fault miss rate low. Probability moving average is useful when false alarms must be minimized more aggressively, but it can increase missed fault windows.

## 5. Replay / Vehicle Validation Suggestions

Use `replay_inference.py` to evaluate one CSV at a time. Each CSV should reset the postprocessing queue and generate both `prediction_timeline.csv` and `prediction_timeline.png`. For vehicle or replay validation, first run representative normal files and boundary-normal files to estimate false alarms, then run light, medium, and obvious fault files to estimate delay and miss rate. The deployment decision should prioritize stable alarms over single-window accuracy.

Recommended next validation order:

1. Replay known normal CSV files and inspect whether majority vote suppresses transient false alarms.
2. Replay each fault type at vx0.3, vx0.5, and vx0.7 and check detection continuity.
3. Compare default `sage_cnn run_03` with candidate `sage_no_saf run_03` on the same replay set.
4. Keep `sage_cnn run_03` as the default export unless replay evidence clearly favors the candidate model.
"""
    REPORT.write_text(report, encoding="utf-8")
    print(f"Frozen results written to {OUT}")


if __name__ == "__main__":
    main()
