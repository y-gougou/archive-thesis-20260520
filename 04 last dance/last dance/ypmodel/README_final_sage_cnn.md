# SAGE-CNN 最终工程说明

本文档对应当前 `ypmodel` 工程的最终论文主线版本。当前主模型正式命名为 **SAGE-CNN**，中文名为 **源感知差分增强卷积神经网络**。

## 1. 最终模型定位

**SAGE-CNN** 的英文全称为：

> Source-Aware Gradient-Enhanced Convolutional Neural Network

模型面向三全向轮机器人四分类故障诊断任务，输入为 15 维多传感器时序信号，输出为 4 类状态：

| 标签 | 类别 |
|---:|---|
| 0 | normal |
| 1 | drive_abnormal |
| 2 | wheel_slip |
| 3 | shaft_eccentricity |

本文最终不再把原始 CWCNN-FA 作为论文主模型。当前主模型保留 FA 层作为特征重标定与结构完整性模块，同时引入差分增强和源感知融合，并采用普通 Conv1d 学习不同传感器通道之间的交互关系。

## 2. 多传感器融合体现

当前输入通道顺序固定为：

```text
odom_vx, odom_vy, odom_wz,
wheel_speed0, wheel_speed1, wheel_speed2,
imu_ax, imu_ay, imu_az, imu_gx, imu_gy, imu_gz,
current0, current1, current2
```

SAGE-CNN 将 15 个通道显式划分为四类传感器来源：

| 来源 | 通道范围 | 物理含义 |
|---|---|---|
| odom | 0-2 | 里程计速度与角速度 |
| wheel | 3-5 | 三个轮子的轮速 |
| imu | 6-11 | IMU 加速度与角速度 |
| current | 12-14 | 三个电机电流 |

模型中的多传感器融合主要体现在三个层面：

1. **输入层融合**：模型直接接收里程计、轮速、IMU、电流四类传感器组成的统一时序窗口。
2. **源感知融合**：`SourceDynamicFusion` 按传感器来源计算统计上下文，并为不同来源生成动态权重。
3. **普通 Conv1d 融合**：最终主模型使用 `groups=1` 的普通一维卷积，使卷积核可以在不同传感器通道之间学习耦合关系。

因此，SAGE-CNN 不只是把多类传感器数据简单拼接，而是在模型结构中显式引入了来源划分、动态权重和跨通道卷积融合。

## 3. 当前工程结构

```text
ypmodel/
  preprocess_fault_dataset.py
  train_sage_cnn_ablation.py
  README_final_sage_cnn.md
  dataset_four_class_0517/
  models/
    __init__.py
    cwcnn_fa_baseline.py
    sage_cnn.py
    sage_cnn_ablation.py
```

文件说明：

| 文件 | 作用 |
|---|---|
| `models/sage_cnn.py` | SAGE-CNN 正式主模型定义 |
| `models/sage_cnn_ablation.py` | SAGE-CNN 模块级消融模型定义 |
| `models/cwcnn_fa_baseline.py` | 保留 FA 层与原始 CWCNN-FA 基础模块，供主模型复用 |
| `models/__init__.py` | 模型注册入口 |
| `train_sage_cnn_ablation.py` | 严格协议训练脚本，用于主模型和模块级消融 |
| `preprocess_fault_dataset.py` | 数据预处理脚本 |

## 4. 模型注册名称

当前训练脚本同时支持横向模型对比和模块级消融：

| 命令行名称 | 论文含义 | 说明 |
|---|---|---|
| `sage_cnn` | SAGE-CNN 主模型 | 正式论文主模型 |
| `baseline` | SAGE-CNN 主模型别名 | 兼容“以主模型为 baseline 做消融”的表述 |
| `cwcnn_fa` | CWCNN-FA | 原始参考基线模型 |
| `normal_cnn` | 普通 1D CNN | 所有通道拼接后使用普通 Conv1d |
| `mlp` | MLP | 展平时间窗口后使用多层全连接 |
| `lstm` | LSTM | 测试循环网络时序建模能力 |
| `bilstm` | BiLSTM | 测试双向循环网络时序建模能力 |
| `sage_depth_2` - `sage_depth_6` | 卷积层数实验 | 只改变 SAGE-CNN 中普通 Conv1d 层数 |
| `sage_fa_pos_0` - `sage_fa_pos_4` | FA 位置实验 | 只改变 FA 层在 4 层 Conv1d 中的插入位置 |
| `sage_no_diff` | 去差分增强 | 验证一阶/二阶差分特征贡献 |
| `sage_no_saf` | 去源感知融合 | 验证传感器来源动态融合贡献 |
| `sage_no_diff_gate` | 去差分增强和源感知融合 | 验证动态变化增强与多源门控融合贡献 |

## 5. 实验协议

当前实际完成的三阶段实验（`run_experiments.py`）采用**分层随机划分**：

1. 先按故障标签（4 类）分层；
2. 每层内按 `(speed, run_index, csv_file)` 排序后，用固定种子随机打乱；
3. 按比例切分为训练集 / 验证集 / 测试集。

具体比例：
- **主实验（`paper_main_vx05`）**：`70% / 10% / 20%`（train / val / test）
- **部署鲁棒性（`deployment_robust`）**：`70% / 15% / 15%`（train / val / test）

每轮运行使用不同的随机种子（`seed = base_seed + run_id - 1`），保证 5 次独立运行的可复现性。模型 checkpoint 只根据验证集 Macro F1 选择，测试集仅用于最终报告。

> 注：`train_sage_cnn_ablation.py` 支持按 run 编号固定的严格协议（默认 run04 作为验证集），但当前已生成的实验结果全部来自 `run_experiments.py` 的分层随机入口。

## 6. 建议重跑实验

### 6.0 三阶段统一实验入口

新数据集实验建议优先使用统一入口：

```powershell
python run_experiments.py --mode paper_main_vx05 --require_figures
python run_experiments.py --mode paper_generalization --main_results results_paper_main_vx05 --require_figures
python run_experiments.py --mode deployment_robust --require_figures
```

快速联调可使用：

```powershell
python run_experiments.py --mode paper_main_vx05 --smoke --output_dir results_smoke_paper_main_vx05 --require_figures
python run_experiments.py --mode paper_generalization --smoke --main_results results_smoke_paper_main_vx05 --output_dir results_smoke_paper_generalization --require_figures
python run_experiments.py --mode deployment_robust --smoke --output_dir results_smoke_deployment_robust --require_figures
```

统一入口使用新的标签映射：`0 normal, 1 wheel_slip, 2 drive_abnormal, 3 shaft_eccentricity`。统一保存的输入格式为 `[N, 15, 50]`，即 `batch/channel/time`。

### 6.1 语法检查

```powershell
python -m py_compile train_sage_cnn_ablation.py models\__init__.py models\sage_cnn.py models\sage_cnn_ablation.py
```

### 6.2 查看命令行

```powershell
python train_sage_cnn_ablation.py --help
```

### 6.3 Smoke test

```powershell
python train_sage_cnn_ablation.py --data_dir dataset_four_class_0517 --save_dir results_sage_cnn_smoke\sage_cnn --model sage_cnn --epochs 1 --runs 1
```

Smoke test 通过后可删除 `results_sage_cnn_smoke`。

### 6.4 正式实验

建议新结果统一输出到：

```text
results_sage_cnn_ablation_5runs/
```

横向对比建议运行：

```powershell
python train_sage_cnn_ablation.py --data_dir dataset_four_class_0517 --save_dir results_sage_cnn_ablation_5runs\sage_cnn --model sage_cnn --epochs 30 --runs 5
python train_sage_cnn_ablation.py --data_dir dataset_four_class_0517 --save_dir results_sage_cnn_ablation_5runs\cwcnn_fa --model cwcnn_fa --epochs 30 --runs 5
python train_sage_cnn_ablation.py --data_dir dataset_four_class_0517 --save_dir results_sage_cnn_ablation_5runs\normal_cnn --model normal_cnn --epochs 30 --runs 5
python train_sage_cnn_ablation.py --data_dir dataset_four_class_0517 --save_dir results_sage_cnn_ablation_5runs\mlp --model mlp --epochs 30 --runs 5
python train_sage_cnn_ablation.py --data_dir dataset_four_class_0517 --save_dir results_sage_cnn_ablation_5runs\lstm --model lstm --epochs 30 --runs 5
python train_sage_cnn_ablation.py --data_dir dataset_four_class_0517 --save_dir results_sage_cnn_ablation_5runs\bilstm --model bilstm --epochs 30 --runs 5
```

模块级消融建议运行：

```powershell
python train_sage_cnn_ablation.py --data_dir dataset_four_class_0517 --save_dir results_sage_cnn_ablation_5runs\sage_no_diff --model sage_no_diff --epochs 30 --runs 5
python train_sage_cnn_ablation.py --data_dir dataset_four_class_0517 --save_dir results_sage_cnn_ablation_5runs\sage_no_saf --model sage_no_saf --epochs 30 --runs 5
python train_sage_cnn_ablation.py --data_dir dataset_four_class_0517 --save_dir results_sage_cnn_ablation_5runs\sage_no_diff_gate --model sage_no_diff_gate --epochs 30 --runs 5
```

## 7. 论文表格建议

论文实验部分建议组织为五组结果：

1. 横向模型对比：`CWCNN-FA`、`1D CNN`、`MLP`、`LSTM`、`BiLSTM`、`SAGE-CNN`。
2. 模块级消融：`SAGE-CNN`、`w/o Diff`、`w/o SAF`、`w/o Diff+SAF`。
3. 复杂度分析：参数量、可训练参数量、推理时间。
4. 卷积层数影响实验：比较 2-6 层普通 Conv1d 对诊断性能的影响。
5. FA 位置影响实验：比较 FA 层放在 Conv1 前、Conv1 后、Conv2 后、Conv3 后、Conv4 后的性能差异。

模块级消融表建议使用：

| 模型 | 特征重标定与结构完整性模块 | 差分增强 | 源感知融合 | 普通 Conv1d | 说明 |
|---|---|---|---|---|---|
| SAGE-CNN | yes | yes | yes | yes | 最终主模型 |
| w/o Diff | yes | no | yes | yes | 去除显式一阶/二阶差分增强 |
| w/o SAF | yes | yes | no | yes | 去除源感知融合 |
| w/o Diff+SAF | yes | no | no | yes | 同时去除差分增强和源感知融合 |

其中 Diff 表示差分增强，SAF 表示 Source-Aware Fusion，即源感知融合。

## 8. 当前清理状态

旧预处理数据、旧实验结果、旧 selected 权重和缓存已经清理。当前可用于重跑实验的数据目录为 `dataset_four_class_0517`，由 `../shuju0517` 生成。

本次预处理结果：

- 训练窗口：6752，类别分布 `{0: 1968, 1: 1860, 2: 2210, 3: 714}`。
- 测试窗口：462，类别分布 `{0: 85, 1: 147, 2: 143, 3: 87}`。
- `shaft_eccentricity_C_vx0.3_run02.csv` 删除了 1 行 NaN/Inf 坏数据。
- 缩放后训练集和测试集均无 NaN/Inf。

下一轮正式 SAGE-CNN 主模型结果建议输出到 `results_sage_cnn_ablation_5runs\sage_cnn`。完成 5 次运行后，再从 SAGE-CNN 结果中按验证集 Macro F1 选择最终权重并重建 `selected_sage_cnn_model`。

## 9. 写作表述建议

可在论文方法章节中描述为：

> 针对三全向轮机器人故障诊断中多源传感器信号耦合关系复杂的问题，本文提出源感知差分增强卷积神经网络 SAGE-CNN。该模型首先基于输入信号构造一阶和二阶时序差分特征，以增强故障状态变化信息；随后根据里程计、轮速、IMU 和电流四类传感器来源进行源感知动态融合；最后通过普通一维卷积学习跨传感器通道的联合特征，并结合特征重标定与结构完整性模块稳定特征表达，实现多传感器融合故障诊断。

消融实验部分可描述为：

> 为验证 SAGE-CNN 中差分增强和源感知融合模块的有效性，本文以完整 SAGE-CNN 作为 Baseline，分别去除差分增强、去除源感知融合，以及同时去除差分增强与源感知融合进行对比。完整模型中的 FA 层作为特征重标定与结构完整性模块保留，不单独作为模块级消融项。所有实验均采用相同的数据划分、训练轮数和模型选择策略，仅改变待验证模块，以保证对比结果具有可解释性。

## 10. 实车部署稳定化

当前离线数据全部来自 `straight_0.5ms` 工况，没有静止正常样本。为了避免小车静止时出现域外输入误判，工程中新增 `realtime_sage_cnn_guard.py` 作为部署侧轻量包装层。该包装层不改变 SAGE-CNN 主模型权重，而是在模型前后增加静止状态门控、低置信度判断、滑动窗口投票和 wheel_slip/shaft_eccentricity 模糊保护。

默认配置文件为：

```text
realtime_sage_cnn_guard_config.json
```

实车程序建议调用方式：

```python
from realtime_sage_cnn_guard import SAGECNNRealtimeGuard

guard = SAGECNNRealtimeGuard.from_config_file("realtime_sage_cnn_guard_config.json")
result = guard.predict_window(raw_window)  # raw_window shape: [15, 50]
```

`raw_window` 必须使用未归一化的原始 15 通道窗口。守护层会先基于原始 odom 与 wheel_speed 判断是否静止；非静止窗口再使用 `selected_sage_cnn_model/strict_scaler.pkl` 归一化并送入 SAGE-CNN。旧 `selected_sage_cnn_model` 已清理，需在新数据集训练完成后重新生成。

输出结果包含：

```text
raw_model_label, raw_model_prob, stable_label, stable_prob,
is_static, is_low_confidence, ambiguous_slip_eccentricity,
top2_labels, top2_probs
```

其中 `stable_label` 是推荐给实车界面或上层控制逻辑使用的稳定诊断结果。若 `is_static=True`，默认显示为 `normal_static`，在四分类统计中可映射为 `normal`。
