# deployment_robust Report

Exported model: `sage_no_saf` run 03.

Model selection rationale: Ablation experiments show that SAF (Source-Aware Fusion) achieves comparable performance to the full SAGE-CNN on in-distribution data (paper_main_vx05 test macro_f1: 0.9646 vs 0.9647), but SAGE-CNN w/o SAF demonstrates superior cross-speed generalization and stability in deployment_robust evaluation (test macro_f1: 0.9344±0.0170 vs 0.9283±0.0262). Therefore, the deployment model was switched from the originally exported `sage_cnn` to `sage_no_saf` run 03 (val_macro_f1=0.9886) for better real-world robustness.

Postprocess metrics skip the first N-1 windows within each CSV and are simulated per CSV in order.

Best average Test Macro F1 by model family: `sage_no_saf`.

Generated files in this result directory are the source of truth for tables, figures, splits, and checkpoints.
