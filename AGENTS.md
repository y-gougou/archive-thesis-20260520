# AGENTS.md

本文件为 AI 编程助手提供整个代码仓库的概览、构建方式、开发规范及跨项目关联信息。

---

## 项目概述

本仓库是 **燕山大学本科毕业设计** 的完整代码集合，围绕 **WHEELTEC R550PLUS 三全向轮机器人** 展开，涵盖底层嵌入式固件、传感器系统、ROS 上位机控制、Web/桌面监控、数据采集以及基于深度学习的故障诊断。

仓库按功能划分为 4 个子项目：

| 目录 | 名称 | 定位 |
|------|------|------|
| `01 ROS/` | ROS 机器人控制与数据采集 | ROS Noetic 上位机包，负责底盘通信、传感器融合、Web 控制、数据落盘 |
| `02 4CH-Current/` | 四通道电流传感器系统 | STM32F103 电流采集固件 + Python 上位机 + ROS 驱动 + 标定工具 |
| `03 omi_car/` | 全向轮小车底盘固件 | STM32F4 嵌入式控制程序（FreeRTOS），负责电机 PID、IMU、通信 |
| `04 last dance/` | 故障诊断深度学习研究 | PyTorch 时序分类项目（SAGE-CNN），包含训练、消融、部署 ONNX |

---

## 仓库结构

```
.
├── 01 ROS/
│   └── turn_on_wheeltec_robot/      # ROS1 catkin 包
├── 02 4CH-Current/
│   ├── Firmware/                     # STM32F103 电流采集固件
│   ├── HostApp/                      # PySide6 上位机（uv 管理）
│   ├── ROS/                          # ROS Noetic 驱动包
│   └── Tools/                        # 标定与辅助工具
├── 03 omi_car/
│   ├── USER/                         # 入口与中断
│   ├── BALANCE/                      # 运动控制核心
│   ├── HARDWARE/                     # 外设驱动
│   ├── HUB_DRIVER/                   # 轮毂电机驱动
│   ├── MPU6050/                      # IMU 驱动
│   ├── AutoRecharge/                 # 自动充电
│   ├── FreeRTOS/                     # FreeRTOS v9.0.0
│   ├── CORE/                         # 启动文件
│   └── FWLIB/                        # STM32 标准库
└── 04 last dance/
    └── last dance/
        ├── shuju0517/                # 原始传感器 CSV 数据集
        └── ypmodel/                  # 模型定义、训练脚本、结果目录
```

---

## 子项目详解

### 01 ROS — `turn_on_wheeltec_robot`

**技术栈**：ROS1 Noetic、C++14、Python 3、catkin、rosbridge、Electron、ONNX Runtime

**构建方式**：
```bash
cd ~/catkin_ws                         # catkin 工作空间根目录
catkin_make                            # 编译 C++ 节点
source devel/setup.bash
```

`CMakeLists.txt` 编译 4 个 C++ 可执行节点：
- `wheeltec_robot_node` — 底盘串口通信、里程计、IMU 发布
- `heading_bridge_node` — IMU 航向角标准化
- `cmd_vel_web_adapter_node` — Web 控制安全适配层（心跳、急停、限速、死区）
- `current_reader_node` — 电流传感器串口读取

**Python 节点**（`scripts/` 目录）：
- `data_collector.py` — 16 通道数据落盘 CSV
- `current_reader.py` — 电流传感器读取（Python 版）
- `cmd_vel_web_adapter.py` — Web 适配器（Python 版，含 PID 巡航）
- `web_dashboard_server.py` — HTTP 服务（Web 页面 + CSV API）
- `fault_injector.py` — 故障注入实验控制
- `core/` 子目录包含共享工具库（PID、CSV、串口、参数读取等）

**关键启动文件**：
- `turn_on_wheeltec_robot.launch` — 底盘 + IMU + 里程计
- `web_control.launch` — Web 控制入口（rosbridge + 网页服务 + 适配器）
- `data_collector.launch` — 数据采集（带 `fault_label` 参数）
- `mapping.launch` / `navigation.launch` — 2D SLAM / 导航

**串口设备**：
| 设备 | 默认路径 | 波特率 |
|------|----------|--------|
| 底盘控制器 | `/dev/ttyCH343USB0` | 115200 |
| 电流传感器 | `/dev/ttyUSB0` | 115200 |

**Web 端口**：
| 服务 | 端口 |
|------|------|
| Web 控制面板 | `http://<robot_ip>:8000` |
| rosbridge WebSocket | `ws://<robot_ip>:9090` |

**数据采集**：采集 16 通道数据（位置 3 + 速度 3 + 加速度 3 + 角速度 3 + 电压 1 + 电流 3），默认输出到 `/home/wheeltec/R550PLUS_data_collect/log`。

**文档**：`README.md`、`CLAUDE.md`、`last readme.md`、`docs/` 子目录包含协议规范、桌面应用构建指南、故障推理说明等。

---

### 02 4CH-Current — 四通道电流传感器

**技术栈**：STM32F103C8T6（Cortex-M3）、HAL、Keil MDK-ARM / EIDE、Python 3.10+、PySide6、PyTorch、ROS Noetic

#### Firmware/
- **MCU**：STM32F103C8T6，72 MHz，CubeMX 配置（`4CH-Current.ioc`）
- **IDE**：Keil MDK-ARM（`MDK-ARM/4CH-Current.uvprojx`）或 EIDE（VS Code 扩展）
- **外设**：ADC1（4 通道）+ DMA、I2C1（OLED）、USART1/2
- **源码**：`Core/Src/` 与 `Core/Inc/`，包含 ADC 驱动、双级滤波（EMA + 滑动平均）、UART 协议、OLED 显示
- **电流计算**：基于 INA282 高侧采样，`I = (Vadc - 1.65V) / (50 * 0.005Ω)`
- **协议模式**（`uart_protocol.h` 中编译时切换）：
  - `0`：自定义二进制协议
  - `1`：FireWater 文本协议（`$CURRENT,ch0,ch1,ch2*XX\r\n`，当前默认）

> **注意**：当前固件默认使用 FireWater 文本协议，而 `HostApp/protocol.py` 和 `ROS/scripts/sensor_node.py` 仅实现了二进制协议解析器，两者存在协议不匹配。

#### HostApp/
- **包管理器**：uv（Astral）
- **入口**：`src/ch4_current/main.py`
- **依赖**：`pyserial`、`PySide6>=6.6.0`、`pyqtgraph>=0.13.3`、`numpy>=1.24.0`
- **构建命令**：
  ```bash
  cd "02 4CH-Current/HostApp"
  uv sync
  uv run ch4-current
  uv run black src/
  uv run ruff check src/
  uv run mypy src/
  ```

#### ROS/
- 包名 `ch4_current_sensor`
- 发布话题 `/current_data`（自定义 `CurrentData.msg`：4 路电流 + 4 路原始 ADC）
- 启动：`roslaunch ch4_current_sensor sensor.launch port:=/dev/ttyUSB0`

#### Tools/
- `calibration_tool.py` — Tkinter 标定工具，通过线性最小二乘计算增益与偏置，输出可直接粘贴到 `current_types.h` 的 C 宏定义
- `requirements.txt` — 标定工具依赖（`pyserial`、`numpy`、`matplotlib`）

**文档**：`电流传感器总结文档_0516.md`、`AGENTS.md`、`CLAUDE.md`、`HostApp/README.md`、`Tools/README_Calibration.md`

---

### 03 omi_car — 全向轮小车底盘固件

**技术栈**：STM32F40_41xxx（Cortex-M4 + FPU）、FreeRTOS v9.0.0、STM32 标准外设库（SPL）、EIDE / Keil AC5

**构建方式**：
- 使用 VS Code + EIDE 扩展，或 Keil MDK-ARM
- 编译器：AC5，C99，优化等级 2，启用 microLIB 与硬件 FPU
- 调试器：JLink（8000 kHz）或 STLink（4000 kHz，SWD）
- VS Code 任务：`build`、`flash`、`build and flash`、`clean`
- 清理 Keil 生成物可运行 `keilkilll.bat`

**目录组织**：
| 目录 | 职责 |
|------|------|
| `USER/` | `main.c`（FreeRTOS 任务创建）、中断处理、时钟配置 |
| `BALANCE/` | 核心运动控制：`balance.c`（100Hz 控制循环）、`control.c`（PID）、`filter.c`（卡尔曼滤波）、`system.c/h`（全局初始化与状态） |
| `HARDWARE/` | 外设驱动：LED、OLED、电机、编码器、ADC、CAN、DMA、定时器、串口、PS2、按键 |
| `HUB_DRIVER/` | 轮毂电机 UART（Modbus RTU）与 CAN 驱动 |
| `MPU6050/` | I2C 软件模拟驱动、MPU6050 读取与姿态解算 |
| `AutoRecharge/` | 红外寻的自动充电逻辑 |
| `FreeRTOS/` | FreeRTOS 内核与 ARM_CM4F 移植层 |
| `CORE/` | 启动汇编 `startup_stm32f40_41xxx.s` 与 CMSIS 头文件 |
| `FWLIB/` | STM32F4xx 标准外设库 |

**FreeRTOS 任务**（在 `main.c` 中创建）：
1. `Balance_task`（优先级 4）— 100Hz 运动控制、PID、PWM 输出
2. `MPU6050_task`（优先级 3）— 100Hz IMU 读取 + 卡尔曼滤波
3. `show_task`（优先级 3）— OLED 显示
4. `led_task`（优先级 3）— LED 状态指示
5. `pstwo_task`（优先级 4）— PS2 手柄读取
6. `data_task`（优先级 4）— USART3/USART1/CAN 数据发送

**关键常量**：
- `CONTROL_DELAY = 750` — 开机约 10 秒延时，等待 IMU 稳定后才允许运动
- `CAR_NUMBER = 7` — 支持 7 种车型选择
- 车辆模式：`Omni`（1，三全向轮）、`Mec`（0，四麦轮）

**全局状态**：几乎所有重要变量都在 `BALANCE/system.h` 中以 `extern` 声明，在 `BALANCE/system.c` 中定义。

**文档**：`README.md`、`AGENTS.md`、`小车底盘总结文档_0516.md`、`更新记录.txt`

---

### 04 last dance — 故障诊断深度学习

**技术栈**：Python 3.11、PyTorch、NumPy、scikit-learn、matplotlib、ONNX Runtime、joblib

**项目定位**：基于多传感器时序数据的机器人故障分类研究，使用 SAGE-CNN（Source-Aware Gradient-Enhanced CNN）模型。

**目录结构**：
```
04 last dance/last dance/
├── shuju0517/                          # 原始 CSV 数据集（4 类故障）
│   ├── normal/
│   ├── drive fault/
│   ├── wheel_slip/
│   └── shaft eccentricity/
└── ypmodel/                            # 代码与实验结果
    ├── models/                         # 网络定义
    │   ├── sage_cnn.py                 # 主模型
    │   ├── sage_cnn_ablation.py        # 消融变体
    │   ├── cwcnn_fa_baseline.py        # 基线模型
    │   └── comparison_models.py        # 对比模型（CNN/MLP/LSTM/BiLSTM）
    ├── preprocess_fault_dataset.py     # CSV → NPY 滑动窗口 + 归一化
    ├── train_sage_cnn_ablation.py      # 训练器
    ├── run_experiments.py              # 三阶段实验入口
    ├── replay_inference.py             # 单文件回放推理
    ├── realtime_sage_cnn_guard.py      # 部署守卫（静态门控 + 投票）
    ├── freeze_results.py               # 生成最终图表与报告
    ├── prepare_final_summary.py        # 高级汇总
    ├── results_paper_main_vx05/        # 阶段一：主实验（vx=0.5）
    ├── results_paper_generalization/   # 阶段二：跨速度泛化
    ├── results_deployment_robust/      # 阶段三：部署鲁棒性 + ONNX 导出
    ├── results_final_summary/          # 冻结最终结果
    ├── selected_sage_cnn_model/        # 选中的最优模型与 scaler
    └── README_final_sage_cnn.md        # 完整项目文档
```

**数据流程**：
1. 原始 CSV（15 通道：里程计 3 + 轮速 3 + IMU 6 + 电流 3）
2. `preprocess_fault_dataset.py`：滑动窗口（`window_size=50`，`step_size=10`），去头尾 5 秒，Scaler 拟合
3. 训练 SAGE-CNN（输入 `[N, 15, 50]`，输出 4 类 logits）
4. 导出 ONNX，部署时通过 `realtime_sage_cnn_guard.py` 做后处理（静态门控、低置信度保护、滑动窗口投票）

**三阶段实验命令**：
```bash
cd "04 last dance/last dance/ypmodel"
python run_experiments.py --mode paper_main_vx05 --require_figures
python run_experiments.py --mode paper_generalization --main_results results_paper_main_vx05 --require_figures
python run_experiments.py --mode deployment_robust --require_figures
```

**文档**：`README_final_sage_cnn.md`（中文，最权威的项目说明）

---

## 跨项目关联与数据流

整体系统存在清晰的“底层 → 中间件 → 应用 → 算法”链路：

```
03 omi_car (STM32F4 固件)
    │ 串口 115200
    ▼
01 ROS (wheeltec_robot_node)
    │ 发布 /odom, /imu, /wheel_speed, /PowerVoltage
    ▼
02 4CH-Current (电流传感器)
    │ 串口 115200 → 发布 /current_data
    ▼
01 ROS (data_collector.py)
    │ 时间同步 → 落盘 CSV
    ▼
04 last dance (preprocess + train)
    │ 滑动窗口 → SAGE-CNN 训练 → ONNX 导出
    ▼
01 ROS (桌面端 Electron + ONNX Runtime 推理)
```

- **03 omi_car** 是底盘运动控制核心，通过串口与 ROS 节点通信。
- **02 4CH-Current** 提供电流监测，电流数据汇入 ROS 话题后被采集为 CSV。
- **01 ROS** 承担中间件角色：硬件抽象、传感器融合、Web 控制、数据落盘。
- **04 last dance** 读取 ROS 采集的 CSV，训练故障诊断模型，最终 ONNX 模型可回流到 01 ROS 的桌面端进行实时推理。

---

## 构建与测试命令速查

### 01 ROS
```bash
# 编译
cd ~/catkin_ws && catkin_make && source devel/setup.bash

# 启动底盘
roslaunch turn_on_wheeltec_robot turn_on_wheeltec_robot.launch

# 数据采集
roslaunch turn_on_wheeltec_robot data_collector.launch fault_label:=0

# Web 控制（需禁用冲突节点）
roslaunch turn_on_wheeltec_robot web_control.launch start_base:=false start_current_reader:=false start_data_collector:=false

# 数据处理流水线
python process_pipeline.py --csv "/path/to/file.csv"
```

### 02 4CH-Current
```bash
# 固件：用 Keil 打开 MDK-ARM/4CH-Current.uvprojx 编译，或用 EIDE

# 上位机
cd "02 4CH-Current/HostApp" && uv sync && uv run ch4-current

# ROS 驱动
catkin_make
roslaunch ch4_current_sensor sensor.launch port:=/dev/ttyUSB0 baudrate:=115200

# 标定工具
cd "02 4CH-Current/Tools" && pip install -r requirements.txt && python calibration_tool.py
```

### 03 omi_car
```bash
# 使用 VS Code + EIDE 扩展
# 命令面板：eide.project.build（构建）
# 命令面板：eide.project.uploadToDevice（烧录）
# 或运行 VS Code 任务：build / flash / build and flash / clean

# 清理 Keil 生成物
keilkilll.bat
```

### 04 last dance
```bash
cd "04 last dance/last dance/ypmodel"

# 数据预处理
python preprocess_fault_dataset.py --data_dir ../shuju0517 --output_dir ./datasets

# 运行完整实验
python run_experiments.py --mode paper_main_vx05 --require_figures
python run_experiments.py --mode deployment_robust --require_figures

# 回放推理
python replay_inference.py --csv ../shuju0517/normal/xxx.csv --model results_deployment_robust/export/best_model.onnx

# 部署守卫测试
python test_realtime_sage_cnn_guard.py
```

---

## 代码风格与开发规范

### Python（01 ROS、02 HostApp、04 last dance）
- 缩进：4 空格
- 02 HostApp 使用 Black 格式化、Ruff 检查、MyPy 类型检查
- 命名：`snake_case`（函数/变量）、`PascalCase`（类）、`UPPER_SNAKE_CASE`（常量）
- 01 ROS 的 Python 节点未配置严格的格式化工具，保持与现有代码风格一致即可
- 04 last dance 为研究代码，无严格 lint 配置，以可读性和可复现性优先

### C/C++（01 ROS C++ 节点、02 Firmware、03 omi_car）
- 01 ROS C++：遵循 ROS 社区风格，节点类封装，回调函数清晰
- 02 Firmware：HAL 风格，`Core/Inc/*.h` 声明，`Core/Src/*.c` 实现
- 03 omi_car：传统 SPL 嵌入式风格，全局变量集中管理，任务函数以大写驼峰命名（如 `Balance_task`）
- 部分文件名大小写不统一（如 `LED.C` 与 `led.h`），修改时保持原样

### 注释语言
- 01 ROS：中文为主
- 02 4CH-Current：中英混合
- 03 omi_car：中英混合（大量中文注释）
- 04 last dance：中文为主

---

## 测试策略

| 子项目 | 测试方式 | 说明 |
|--------|----------|------|
| 01 ROS | 硬件在环测试 | 节点运行依赖实际机器人硬件；可用 `rostopic hz`、`rosnode list` 验证 |
| 02 Firmware | 硬件验证 | 无单元测试，需在实际电流板上验证 ADC 值、UART 输出、OLED 显示 |
| 02 HostApp | pytest（推荐补充） | 当前无提交测试集，建议在 `HostApp/tests/` 补充协议解析、串口错误处理测试 |
| 03 omi_car | 硬件在环 | 裸机嵌入式代码，无单元测试；验证方式为实际电机响应、OLED 显示、串口打印 |
| 04 last dance | 脚本级验证 | 通过 `run_experiments.py` 的固定随机种子保证可复现；`test_realtime_sage_cnn_guard.py` 测试部署守卫逻辑 |

---

## 安全注意事项

1. **机器人运动安全**
   - 01 ROS 的 `cmd_vel_web_adapter` 是安全关键层：包含心跳超时（默认 1.0s）、指令超时（0.5s）、急停（`/web/estop`）、速度死区与限速
   - 修改任何超时、限速、死区参数时，必须在硬件上验证急停响应
   - 03 omi_car 的 `CONTROL_DELAY`（约 10 秒）是 IMU 稳定等待，不建议随意缩短

2. **固件烧录安全**
   - 03 omi_car 使用 Keil AC5 / EIDE 烧录，烧录前确认 scatter 文件地址（ROM 0x08000000）正确
   - 避免在机器人悬空或轮子在桌面上时烧录后立即启动电机

3. **数据安全**
   - 数据集路径 `/home/wheeltec/R550PLUS_data_collect/log` 在 01 ROS 中多处硬编码，修改时注意同步
   - 04 last dance 的 CSV 包含原始传感器数据，无个人隐私信息，但涉及实验设备参数

4. **协议不匹配风险**
   - 02 4CH-Current 的固件默认 FireWater 协议与 HostApp/ROS 节点的二进制解析器不匹配，联调前务必在 `uart_protocol.h` 中统一协议模式

5. **环境隔离**
   - 02 HostApp 使用 `uv` 管理依赖，不要混用系统 Python 与虚拟环境
   - 04 last dance 无虚拟环境配置，建议在独立 conda/venv 中运行，避免与系统 PyTorch 冲突

---

## 快速参考

| 问题 | 对应位置 |
|------|----------|
| 底盘不转 / 串口无数据 | 检查 `03 omi_car` 固件是否烧录，串口路径是否为 `/dev/ttyCH343USB0` |
| Web 页面打不开 | 确认 `web_dashboard_server.py` 已启动，端口 8000 未被占用 |
| 电流数据缺失 | 检查 02 固件协议模式与 ROS/HostApp 是否一致 |
| 数据集处理失败 | 查看 `01 ROS/scripts/process_pipeline.py` 的 `--csv` 参数与输出路径 |
| 模型推理结果异常 | 确认 04 的 scaler 与训练时一致，输入窗口大小为 50 |

---

## 作者

杨鹏 — 燕山大学本科毕业设计
