# Deployment Config Check Report

Desktop model package: `D:\projects\01 ROS\turn_on_wheeltec_robot\desktop\models\sage_cnn`

## Required Files

- `model_manifest.json`: OK
- `sage_cnn_selected_best_model.onnx`: OK
- `scaler.json`: OK
- `feature_config_used.json`: OK
- `realtime_sage_cnn_guard_config.json`: OK

## Configuration Checks

- `required_files_present`: OK
- `feature_order_fixed_15`: OK
- `label_order_fixed`: OK
- `input_shape_1_15_50`: OK
- `majority_vote_n5_confirm4`: OK

## Fixed Feature Order

odom_vx, odom_vy, odom_wz, wheel_speed0, wheel_speed1, wheel_speed2, imu_ax, imu_ay, imu_az, imu_gx, imu_gy, imu_gz, current0, current1, current2

## Label Order

- 0: normal
- 1: wheel_slip
- 2: drive_abnormal
- 3: shaft_eccentricity

## Postprocess

- method: majority_vote
- N: 5
- confirm_count: 4

Overall status: PASS
