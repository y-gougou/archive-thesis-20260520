# Final Experiment Summary

## 1. Dataset And Preprocessing

The final experiment materials use the fixed four-class label order: `0 normal`, `1 wheel_slip`, `2 drive_abnormal`, `3 shaft_eccentricity`. The input feature order is fixed to 15 channels:

`odom_vx, odom_vy, odom_wz, wheel_speed0, wheel_speed1, wheel_speed2, imu_ax, imu_ay, imu_az, imu_gx, imu_gy, imu_gz, current0, current1, current2`

The unified input layout is `[N, 15, 50]`, namely batch/channel/time.

**Split strategy**: Stratified random split by fault label. Within each class, CSV files are sorted by `(speed, run_index, filename)` and then shuffled with a fixed seed before splitting. The split ratios are `70% / 10% / 20%` (train/val/test) for the main experiment and `70% / 15% / 15%` for deployment robustness. Each of the 5 independent runs uses a different seed (`base_seed + run_id - 1`).

**Normalization**: StandardScaler (Z-score, mean subtraction and division by std) is fitted on the training split only and then applied to validation and test splits.

The scaler, feature order, and label map are kept consistent with the deployed desktop ONNX package.

## 2. Main-condition Diagnosis Results

The paper main experiment is `paper_main_vx05`, and the paper main model is SAGE-CNN. The fixed main-condition result for SAGE-CNN is:

- Accuracy = 0.9803
- Macro F1 = 0.9647

| Model | Accuracy | Macro F1 |
| --- | --- | --- |
| sage_cnn | 0.9803 ± 0.0054 | 0.9647 ± 0.0096 |
| sage_no_saf | 0.9807 ± 0.0096 | 0.9646 ± 0.0193 |
| normal_cnn | 0.9721 ± 0.0129 | 0.9463 ± 0.0250 |
| sage_no_diff | 0.9691 ± 0.0168 | 0.9409 ± 0.0345 |
| sage_no_diff_gate | 0.9658 ± 0.0130 | 0.9301 ± 0.0353 |
| bilstm | 0.9597 ± 0.0117 | 0.9273 ± 0.0183 |
| lstm | 0.9578 ± 0.0169 | 0.9233 ± 0.0276 |
| cwcnn_fa | 0.9490 ± 0.0127 | 0.9011 ± 0.0313 |
| mlp | 0.9450 ± 0.0126 | 0.8997 ± 0.0139 |

The main-condition Macro F1 bar chart is `figures/fig_main_macro_f1_bar.png`, and the SAGE-CNN confusion matrix is `figures/fig_sage_cnn_main_confusion_matrix.png`.

## 3. Ablation Study

| Model | Accuracy | Macro F1 |
| --- | --- | --- |
| sage_cnn | 0.9803 ± 0.0054 | 0.9647 ± 0.0096 |
| sage_no_diff | 0.9691 ± 0.0168 | 0.9409 ± 0.0345 |
| sage_no_saf | 0.9807 ± 0.0096 | 0.9646 ± 0.0193 |
| sage_no_diff_gate | 0.9658 ± 0.0130 | 0.9301 ± 0.0353 |

SAGE-CNN and `sage_no_saf` show very close main-condition performance: SAGE-CNN Macro F1 is 0.9647, while `sage_no_saf` Macro F1 is 0.9646. This should be described as comparable performance, not as a forced superiority claim. The clearer drop in `sage_no_diff` and `sage_no_diff_gate` supports the contribution of the temporal-difference module.

## 4. Cross-speed Generalization

| Model | Speed | Accuracy | Macro F1 |
| --- | --- | --- | --- |
| sage_cnn | vx0.3 | 0.8675 ± 0.0270 | 0.8493 ± 0.0303 |
| sage_cnn | vx0.5 | 0.9803 ± 0.0054 | 0.9647 ± 0.0096 |
| sage_cnn | vx0.7 | 0.8206 ± 0.0681 | 0.7783 ± 0.0774 |
| sage_no_saf | vx0.3 | 0.8593 ± 0.0830 | 0.8456 ± 0.0920 |
| sage_no_saf | vx0.5 | 0.9807 ± 0.0096 | 0.9646 ± 0.0193 |
| sage_no_saf | vx0.7 | 0.8952 ± 0.0316 | 0.8665 ± 0.0432 |
| sage_no_diff_gate | vx0.3 | 0.8325 ± 0.0624 | 0.8163 ± 0.0701 |
| sage_no_diff_gate | vx0.5 | 0.9658 ± 0.0130 | 0.9301 ± 0.0353 |
| sage_no_diff_gate | vx0.7 | 0.8249 ± 0.0252 | 0.7588 ± 0.0449 |

For SAGE-CNN, Macro F1 is 0.8493 at vx0.3, 0.9647 at vx0.5, and 0.7783 at vx0.7. The vx0.7 decrease is best explained as speed-condition distribution shift in the sensor signals, rather than model failure. The `sage_no_saf` result is also retained because it is competitive, especially on vx0.7.

## 5. Deployment Robustness And Postprocessing

The default deployed model is SAGE-CNN run_03. The candidate model is `sage_no_saf run_03`.

| Model | Accuracy | Macro F1 |
| --- | --- | --- |
| sage_cnn | 0.9639 ± 0.0149 | 0.9283 ± 0.0262 |
| sage_no_saf | 0.9706 ± 0.0064 | 0.9344 ± 0.0170 |
| normal_cnn | 0.9633 ± 0.0202 | 0.9271 ± 0.0365 |
| bilstm | 0.9597 ± 0.0144 | 0.9128 ± 0.0267 |

| Method | Accuracy | Macro F1 | Normal false alarm | Fault miss |
| --- | --- | --- | --- | --- |
| raw | 0.9840 | 0.9634 | 0.0466 | 0.0020 |
| majority_vote | 0.9964 | 0.9909 | 0.0046 | 0.0031 |
| probability_moving_average | 0.9936 | 0.9870 | 0.0000 | 0.0094 |

Majority vote is recommended for real-car deployment, with `N=5` and `confirm_count=4`. It substantially reduces normal false alarms and stabilizes the alarm output while keeping the missed-fault rate acceptable.

## 6. Replay Validation

Replay validation was run with the desktop ONNX package at:

`D:\projects\01 ROS\turn_on_wheeltec_robot\desktop\models\sage_cnn`

Each CSV was replayed independently, and the postprocess queues were reset per file.

| Class | Windows | Mean confidence | Replay CSV |
| --- | --- | --- | --- |
| normal | 101 | 0.9396 | normal_vx0.5_run03.csv |
| wheel_slip | 175 | 0.9650 | wheel_slip_B_vx0.3_run01.csv |
| drive_abnormal | 175 | 0.9720 | drive_abnormal_B_alpha0.3_vx0.5_run01.csv |
| shaft_eccentricity | 97 | 0.9683 | shaft_eccentricity_C_vx0.5_run06.csv |

Each replay directory contains `prediction_timeline.csv`, `prediction_timeline.png`, and `replay_summary.json`.

## 7. Desktop Deployment Check

Deployment package check result: PASS.

The checked package contains `model_manifest.json`, `sage_cnn_selected_best_model.onnx`, `scaler.json`, `feature_config_used.json`, and `realtime_sage_cnn_guard_config.json`. The manifest input shape is `[1, 15, 50]`, the label order is fixed, and the realtime guard config uses majority vote with `N=5`, `confirm_count=4`.

See `deployment_check/deployment_config_check_report.md` for details.

## 8. Final Recommendations

Use SAGE-CNN as the paper main model and report the main-condition result as Accuracy = 0.9803 and Macro F1 = 0.9647. Use SAGE-CNN run_03 as the default deployment model. Keep `sage_no_saf run_03` as a candidate for continued vehicle replay comparison. For real-car testing, enable majority vote by default with `N=5` and `confirm_count=4`.
