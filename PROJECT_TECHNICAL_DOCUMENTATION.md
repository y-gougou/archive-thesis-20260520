# WHEELTEC R550PLUS 全向轮机器人 — 项目技术文档

> **版本**：v1.0  
> **作者**：杨鹏（燕山大学本科毕业设计）  
> **生成日期**：2026-05-18  
> **说明**：本文档基于当前工作区实际源码自动生成，涵盖 4 个子项目的完整架构、模块关系、数据流与接口定义。

---

## 目录

1. [项目架构总览](#1-项目架构总览)
2. [01 ROS — 上位机控制与数据采集](#2-01-ros--上位机控制与数据采集)
3. [02 4CH-Current — 四通道电流传感器](#3-02-4ch-current--四通道电流传感器)
4. [03 omi_car — 全向轮底盘固件](#4-03-omi_car--全向轮底盘固件)
5. [04 last dance — 故障诊断深度学习](#5-04-last-dance--故障诊断深度学习)
6. [跨项目数据流与接口定义](#6-跨项目数据流与接口定义)
7. [关键参数速查表](#7-关键参数速查表)
8. [已知问题与风险清单](#8-已知问题与风险清单)

---

## 1. 项目架构总览

本仓库为 **WHEELTEC R550PLUS 三全向轮机器人** 的完整毕设代码集合，按功能划分为 4 个子项目，形成清晰的 **"底层 → 中间件 → 应用 → 算法"** 链路。

### 1.1 系统架构图

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                              应用层（算法）                                   │
│  ┌─────────────────────────────────────────────────────────────────────┐   │
│  │  04 last dance — SAGE-CNN 故障诊断                                  │   │
│  │  • PyTorch 训练 → ONNX 导出 → Electron 桌面端实时推理                │   │
│  └─────────────────────────────────────────────────────────────────────┘   │
├─────────────────────────────────────────────────────────────────────────────┤
│                              中间件层（ROS）                                  │
│  ┌─────────────────────────────────────────────────────────────────────┐   │
│  │  01 ROS — turn_on_wheeltec_robot                                   │   │
│  │  • 底盘通信 (wheeltec_robot_node)                                   │   │
│  │  • Web/Electron 控制面板 (cmd_vel_web_adapter + HTTP Server)        │   │
│  │  • 传感器融合与数据落盘 (data_collector → CSV)                      │   │
│  │  • 航向桥接 (heading_bridge_node)                                  │   │
│  └─────────────────────────────────────────────────────────────────────┘   │
├─────────────────────────────────────────────────────────────────────────────┤
│                              传感器层                                         │
│  ┌─────────────────────────┐    ┌─────────────────────────────────────────┐│
│  │  02 4CH-Current          │    │  外部 IMU (如 FDI N100)                 ││
│  │  • STM32F103 电流采集    │    │  • /n100/imu (sensor_msgs/Imu)         ││
│  │  • FireWater 协议输出    │    │                                         ││
│  └───────────┬─────────────┘    └─────────────────────────────────────────┘│
├──────────────┼──────────────────────────────────────────────────────────────┤
│                              底层控制层                                       │
│  ┌─────────────────────────────────────────────────────────────────────┐   │
│  │  03 omi_car — STM32F4 底盘固件 (FreeRTOS)                           │   │
│  │  • 电机 PID / 运动学解算 / 增量 PI                                   │   │
│  │  • MPU6050 IMU + 卡尔曼滤波                                         │   │
│  │  • 故障注入（电机增益衰减）                                          │   │
│  │  • 自动回充 / PS2 手柄 / 航模遥控                                    │   │
│  └─────────────────────────────────────────────────────────────────────┘   │
└─────────────────────────────────────────────────────────────────────────────┘
```

### 1.2 目录结构

```
.
├── 01 ROS/
│   └── turn_on_wheeltec_robot/          # ROS1 Noetic catkin 包
├── 02 4CH-Current/
│   ├── Firmware/                         # STM32F103C8T6 固件 (HAL)
│   ├── HostApp/                          # PySide6 上位机 (uv 管理)
│   ├── ROS/                              # ROS Noetic 驱动包
│   └── Tools/                            # 标定与辅助工具
├── 03 omi_car/
│   ├── USER/                             # FreeRTOS 入口与中断
│   ├── BALANCE/                          # 运动控制核心
│   ├── HARDWARE/                         # 外设驱动
│   ├── HUB_DRIVER/                       # 轮毂电机驱动
│   ├── MPU6050/                          # IMU 驱动
│   ├── AutoRecharge/                     # 自动回充
│   ├── FreeRTOS/                         # FreeRTOS v9.0.0
│   ├── CORE/                             # 启动文件
│   └── FWLIB/                            # STM32 标准库
└── 04 last dance/
    └── last dance/
        ├── shuju0517/                    # 原始 CSV 数据集
        └── ypmodel/                      # 模型、训练、部署代码
```

---

## 2. 01 ROS — 上位机控制与数据采集

**技术栈**：ROS1 Noetic、C++14、Python 3、catkin、rosbridge、Vite+React、Electron、ONNX Runtime

### 2.1 目录树

```
01 ROS/turn_on_wheeltec_robot/
├── CMakeLists.txt
├── package.xml
├── docs/                              # 技术文档
│   ├── PROTOCOL.md                    # 串口通信协议逆向文档
│   ├── FAULT_INFERENCE.md             # 桌面端 ONNX 推理文档
│   ├── DESKTOP_APP.md                 # Electron 桌面端架构
│   ├── DESKTOP_BUILD_AND_TEST.md      # 桌面端构建与测试
│   └── 代码实现说明.md                 # 毕设级完整实现说明
├── include/                           # C++ 头文件
│   ├── wheeltec_robot.h
│   ├── heading_bridge_node.h
│   ├── cmd_vel_web_adapter_node.h
│   └── current_reader_node.h
├── src/                               # C++ 源码
│   ├── wheeltec_robot.cpp
│   ├── Quaternion_Solution.cpp
│   ├── heading_bridge_node.cpp
│   ├── cmd_vel_web_adapter_node.cpp
│   └── current_reader_node.cpp
├── scripts/                           # Python 节点与工具库
│   ├── core/                          # 共享工具库
│   │   ├── csv_utils.py
│   │   ├── ros_params.py
│   │   ├── serial_utils.py
│   │   ├── control_utils.py
│   │   ├── time_utils.py
│   │   └── file_api.py
│   ├── data_collector.py
│   ├── web_dashboard_server.py
│   ├── cmd_vel_web_adapter.py
│   ├── current_reader.py
│   ├── fault_injector.py
│   └── build_fault_dataset.py
├── launch/                            # 启动文件
│   ├── turn_on_wheeltec_robot.launch  # 底盘主启动
│   ├── web_control.launch             # Web 控制入口
│   ├── data_collector.launch          # 数据采集
│   ├── fault_injection.launch         # 故障注入实验
│   ├── mapping.launch                 # 2D SLAM
│   └── navigation.launch              # 2D 导航
├── web/                               # Web 控制面板 (Vite+React)
│   ├── src/
│   │   ├── main.jsx
│   │   ├── components/                # React 组件
│   │   └── hooks/                     # 自定义 Hooks
│   └── dist/                          # 构建产物
├── desktop/                           # Electron 桌面端
│   ├── main.js / preload.js
│   ├── inference-service.js           # ONNX 推理服务 (JSON-RPC)
│   ├── model-converter-service.js
│   ├── inference/onnxruntime/         # C++ ONNX Runtime 后端
│   ├── models/sage_cnn/               # 模型包 (ONNX + scaler + manifest)
│   └── renderer/                      # 前端渲染层
├── urdf/                              # 机器人模型 (40+ 车型)
└── map/                               # 预置地图
```

### 2.2 C++ 节点

#### 2.2.1 `wheeltec_robot_node`（底盘核心）

| 项 | 内容 |
|---|---|
| **源码** | `src/wheeltec_robot.cpp` + `src/Quaternion_Solution.cpp` |
| **功能** | 底盘串口通信、里程计积分、IMU 发布、故障注入接收 |
| **订阅话题** | `/cmd_vel` (Twist)、`/target_angle` (Float32)、`/target_angle_reset` (Empty)、`/chassis/heading_deg` (Float32)、`/chassis/fault_config` (Float32MultiArray) |
| **发布话题** | `/odom` (Odometry, ~20Hz)、`/imu` (Imu, ~20Hz)、`/PowerVoltage` (Float32, ~2Hz)、`/wheel_speed` (Float32MultiArray, ~20Hz) |
| **串口参数** | `/dev/ttyCH343USB0`, 115200 |
| **协议** | 13B 发送帧 (BCC XOR), 30B 接收帧；帧头 `0x7B`, 帧尾 `0x7D` |
| **关键参数** | `usart_port_name`, `serial_baud_rate`, `odom_x/y_scale`, `odom_z_scale_positive/negative` |

#### 2.2.2 `heading_bridge_node`（航向桥接）

| 项 | 内容 |
|---|---|
| **功能** | 外部 IMU 四元数 → 航向角，unwrap 处理，零点归零 |
| **订阅** | `/n100/imu` (Imu, 参数 `imu_topic` 可改)、`/web/heading_zero` (Empty)、`/web/heading_offset` (Float32) |
| **发布** | `/chassis/heading_deg` (Float32)、`/web/heading_status` (String, latched) |
| **参数** | `imu_topic`=/n100/imu, `heading_zero_offset`=0.0, `publish_rate`=30.0 |

#### 2.2.3 `cmd_vel_web_adapter_node`（Web 控制安全适配器）

| 项 | 内容 |
|---|---|
| **功能** | 浏览器/桌面端与底盘之间的安全层：心跳超时、急停、限速、死区、定速巡航 PID |
| **订阅** | `/cmd_vel_web` (Twist)、`/web/heartbeat` (Empty)、`/web/estop` (Bool)、`/web/cruise_cmd` (Twist)、`/web/cruise_enable` (Bool)、`/odom` (Odometry) |
| **发布** | `/cmd_vel` (Twist)、`/web/control_status` (String, latched)、`/web/cruise_status` (String, latched) |
| **安全参数** | `heartbeat_timeout`=1.0s, `cmd_timeout`=0.5s, `max_linear_x/y`=0.4, `max_angular_z`=1.0, `linear_deadband`=0.02, `angular_deadband`=0.03 |
| **响应曲线** | `response_exponent`=0.70, `min_linear_ratio`=0.20 |

#### 2.2.4 `current_reader_node`（电流传感器读取）

| 项 | 内容 |
|---|---|
| **功能** | 读取 FireWater 文本协议，发布电流数据 |
| **协议格式** | `$CURRENT,ch0,ch1,ch2*XX\r\n` |
| **订阅** | `/web/current_reader_config` (String) |
| **发布** | `/current_data` (Float32MultiArray)、`/web/current_reader_status` (String) |
| **串口参数** | `/dev/ttyUSB0`, 115200 |

### 2.3 Python 节点

| 脚本 | 功能 |
|---|---|
| `data_collector.py` | 以 `/odom` 为触发源，16 通道数据落盘 CSV（~39 列） |
| `web_dashboard_server.py` | HTTP 静态文件 + REST API（list/preview/download/dataset build），端口 8000 |
| `cmd_vel_web_adapter.py` | Python 版 Web 安全适配器（与 C++ 版功能对等） |
| `current_reader.py` | Python 版电流传感器读取（FireWater 协议） |
| `fault_injector.py` | 接收 Web JSON 故障配置，转换为 `/chassis/fault_config` |
| `build_fault_dataset.py` | CSV → NPY 数据集构建（滑动窗口 + 归一化） |

### 2.4 Web / Electron 前端

| 模块 | 技术栈 | 端口/入口 |
|---|---|---|
| Web 控制面板 | Vite + React + rosbridge | `http://<robot_ip>:8000` |
| rosbridge WebSocket | `rosbridge_server` | `ws://<robot_ip>:9090` |
| Electron 桌面端 | Electron + ONNX Runtime C++ | 独立应用，本地推理 |

### 2.5 文档清单

| 文档 | 说明 |
|---|---|
| `docs/PROTOCOL.md` | 串口协议逆向：底盘二进制协议(13B/30B)、电流传感器 ASCII 协议、校验算法、固件对照 |
| `docs/FAULT_INFERENCE.md` | 桌面端故障诊断：ONNX Runtime C++ 后端、JSON-RPC 协议、模型包格式、导出/编译/打包流程 |
| `docs/DESKTOP_APP.md` | Electron 桌面端架构：启动方式、ROS 通信、HTTP API、SQLite 数据库、国际化 |
| `docs/DESKTOP_BUILD_AND_TEST.md` | 桌面端构建与测试指南 |
| `docs/代码实现说明.md` | 毕设级完整实现说明：数据采集架构、Web 遥控面板、安全机制、预处理、前端拓展方向 |

---

## 3. 02 4CH-Current — 四通道电流传感器

**技术栈**：STM32F103C8T6 (Cortex-M3)、HAL、Keil MDK-ARM / EIDE、Python 3.10+、PySide6、ROS Noetic

### 3.1 目录树

```
02 4CH-Current/
├── Firmware/                          # STM32F103C8T6 固件
│   ├── Core/
│   │   ├── Inc/
│   │   │   ├── adc.h
│   │   │   ├── current_filter.h       # 双重滤波器接口
│   │   │   ├── current_types.h        # 常量、校准参数
│   │   │   ├── uart_protocol.h        # 协议定义（含模式切换）
│   │   │   └── usart.h
│   │   └── Src/
│   │       ├── adc.c                  # ADC1+DMA 四通道
│   │       ├── current_filter.c       # EMA + 滑动平均
│   │       ├── main.c                 # 主循环
│   │       ├── uart_protocol.c        # 二进制 / FireWater 协议
│   │       └── usart.c
│   ├── MDK-ARM/                       # Keil 工程
│   ├── Drivers/                       # STM32 HAL 库
│   └── 4CH-Current.ioc                # CubeMX 配置
├── HostApp/                           # PySide6 上位机
│   ├── src/ch4_current/
│   │   ├── main.py
│   │   ├── gui.py                     # 主窗口与 pyqtgraph 图表
│   │   ├── protocol.py                # 二进制协议解析器
│   │   └── serial_comm.py             # 串口通信线程
│   └── pyproject.toml                 # uv 配置
├── ROS/                               # ROS Noetic 驱动包
│   └── ch4_current_sensor/
│       ├── msg/CurrentData.msg        # 自定义消息
│       ├── scripts/sensor_node.py     # ROS 节点
│       └── launch/sensor.launch
└── Tools/
    ├── calibration_tool.py            # Tkinter 标定工具
    └── README_Calibration.md
```

### 3.2 固件核心逻辑

#### 3.2.1 电流计算流程

```
ADC_RAW (12bit, 0~4095)
    │
    ▼
Vadc = (RAW / 4095) × 3.3V
    │
    ▼
I = (Vadc - 1.65V) / (50 × 0.005Ω)   [INA282 公式]
    │
    ▼
I_cal = I × CAL_GAIN + CAL_OFFSET    [线性校准]
    │
    ▼
EMA(α=0.02) → MovingAvg(15pt)        [双重滤波]
    │
    ▼
g_current_values[4] → OLED / UART
```

#### 3.2.2 主循环时序 (`main.c`)

| 任务 | 周期 | 说明 |
|---|---|---|
| ADC 处理 | DMA 完成中断触发 | 四通道扫描 + DMA 循环传输 |
| UART 发送 | 10ms (100Hz) | 通过 USART2 发送电流数据 |
| OLED 刷新 | 1000ms | 显示 4 路电流值 |
| LED 心跳 | 500ms | 运行状态指示 |

#### 3.2.3 协议模式

在 `Firmware/Core/Inc/uart_protocol.h` 中定义：

```c
#define UART_PROTOCOL_TYPE   1   // 0=自定义二进制, 1=FireWater文本
```

**当前固件默认设置为 `1`（FireWater 文本协议）。**

| 协议 | 格式 | 说明 |
|---|---|---|
| 自定义二进制 (Type 0) | `0xAA 0x55 | CMD | LEN | DATA | XOR | 0x0D 0x0A` | 帧头 + 命令 + 长度 + 数据 + 校验 + 帧尾 |
| FireWater 文本 (Type 1) | `$CURRENT,ch0,ch1,ch2*XX\r\n` | ASCII，仅 3 通道 (M2/M3/M4)，XOR 校验 |

⚠️ **协议不匹配风险**：固件默认 FireWater，但 `HostApp/protocol.py` 和 `ROS/scripts/sensor_node.py` **仅实现了二进制协议解析器**。联调前必须在 `uart_protocol.h` 中统一协议模式。

### 3.3 上位机 (HostApp)

| 文件 | 功能 |
|---|---|
| `main.py` | PySide6 应用入口 |
| `gui.py` | 主窗口：串口选择、pyqtgraph 实时曲线、CSV 记录 |
| `protocol.py` | **仅二进制协议解析**：帧头 `0xAA55`、XOR 校验、尾 `0x0D0A` |
| `serial_comm.py` | 串口连接、后台读取线程、帧分发回调 |

**构建命令**：
```bash
cd "02 4CH-Current/HostApp"
uv sync
uv run ch4-current
```

### 3.4 标定流程 (`Tools/calibration_tool.py`)

1. 通过串口连接，读取 FireWater 文本数据
2. 输入万用表真实电流值作为参考
3. 采集校准点（推荐：0A、0.5A、1.0A、2.0A、3.0A）
4. NumPy 最小二乘拟合：`reference = GAIN × measured + OFFSET`
5. 生成 C 宏 `CAL_CHx_GAIN` / `CAL_CHx_OFFSET`，粘贴到 `current_types.h`

---

## 4. 03 omi_car — 全向轮底盘固件

**技术栈**：STM32F40_41xxx (Cortex-M4 + FPU)、FreeRTOS v9.0.0、STM32 标准外设库 (SPL)、EIDE / Keil AC5

### 4.1 目录树

```
03 omi_car/
├── USER/
│   ├── main.c                         # FreeRTOS 任务创建、启动调度器
│   └── stm32f4xx_it.c                 # 中断处理
├── BALANCE/                           # 核心运动控制
│   ├── system.h / system.c            # 全局变量中心、硬件初始化
│   ├── balance.c / balance.h          # 100Hz 主控制循环
│   ├── control.c / control.h          # 旧版两轮平衡车控制（遗留）
│   ├── filter.c / filter.h            # 卡尔曼滤波
│   ├── show.c / show.h                # OLED 显示任务
│   └── robot_select_init.c / .h       # 车型选择初始化
├── HARDWARE/                          # 外设驱动
│   ├── motor.c / motor.h              # TIM8 PWM (arr=16799)
│   ├── encoder.c / encoder.h          # TIM2/3/4/5 正交编码器
│   ├── usartx.c / usartx.h            # USART1/3/UART4，数据协议，故障注入
│   ├── adc.c / adc.h                  # 电池电压、车型选择 ADC
│   ├── can.c / can.h                  # CAN1 总线
│   ├── LED.C / LED.H                  # RGB LED + 蜂鸣器
│   ├── pstwo.c / pstwo.h              # PS2 手柄 SPI
│   └── ...
├── HUB_DRIVER/                        # 轮毂电机驱动
│   ├── HubDriver.c / HubDriver.h      # UART Modbus RTU
│   └── HubDriverCan.c / HubDriverCan.h # CAN SDO (CANopen 风格)
├── MPU6050/                           # IMU
│   ├── MPU6050.c / mpu6050.h          # MPU6050 读取 + 任务
│   └── I2C.c / I2C.h                  # 软件模拟 I2C
├── AutoRecharge/                      # 自动回充
│   ├── AutoRecharge.c / AutoRecharge.h
├── FreeRTOS/                          # FreeRTOS v9.0.0
├── CORE/                              # 启动汇编 + CMSIS
├── FWLIB/                             # STM32 标准外设库
└── ...
```

### 4.2 FreeRTOS 任务表

| 序号 | 任务名称 | 优先级 | 周期/频率 | 功能描述 | 所在文件 |
|:----:|----------|:------:|:---------:|----------|----------|
| 1 | `Balance_task` | **4** | 100 Hz (10ms) | **核心运动控制**：编码器读取 → 偏航角融合 → 控制源仲裁 → 运动学解算 → 增量 PI → PWM 输出 → 自检 | `BALANCE/balance.c` |
| 2 | `MPU6050_task` | **3** | 100 Hz (10ms) | **IMU 数据采集**：I2C 读取 MPU6050，前 7500ms 零偏校准，卡尔曼滤波 | `MPU6050/MPU6050.c` |
| 3 | `show_task` | **3** | 10 Hz (100ms) | **OLED 显示**：电压采集、低电压报警、多页刷新、APP 数据回显 | `BALANCE/show.c` |
| 4 | `led_task` | **3** | 500ms 闪烁 | **LED 状态指示**：RGB 颜色（红/黄/紫） | `HARDWARE/LED.C` |
| 5 | `pstwo_task` | **4** | 100 Hz (10ms) | **PS2 手柄读取**：SPI 时序，解析 16 按键 + 4 摇杆 | `HARDWARE/pstwo.c` |
| 6 | `data_task` | **4** | 20 Hz (50ms) | **数据通信**：打包传感器数据 → USART1/3 + CAN 发送 | `HARDWARE/usartx.c` |

> 另有 `start_task`（优先级 1），创建上述 6 个任务后自删除。

### 4.3 全局状态与关键变量

#### 4.3.1 核心控制变量（定义于 `BALANCE/system.c`，声明于 `system.h`）

| 变量名 | 类型 | 说明 |
|--------|------|------|
| `Flag_Stop` | `u8` | 急停标志；启动前 IMU 校准时置 1，完成后置 0 |
| `Car_Mode` | `u8` | 车型模式（ADC 分压读取），决定运动学参数 |
| `Move_X/Y/Z` | `float` | 目标速度指令，来自 ROS/APP/PS2/航模 |
| `MOTOR_A` ~ `MOTOR_D` | `Motor_parameter` | 四路电机状态：Encoder, Target, Motor_Pwm, Velocity_KP/KI |

#### 4.3.2 航向角控制变量

| 变量名 | 说明 |
|--------|------|
| `Target_Angle` | 目标偏航角（度） |
| `Current_Angle` | 当前偏航角（经零偏补偿或外部航向融合） |
| `Yaw_Zero_Offset` | 偏航角零点偏移 |
| `Angle_KP/KI/KD` | 0.05 / 0.0 / 1.80 |
| `External_Heading_Enable/Valid` | 外部航向（ROS IMU 航向桥）使能与有效性 |
| `External_Heading_Angle` | 外部输入的绝对航向角 |

#### 4.3.3 故障注入变量（毕业设计实验用）

| 变量名 | 说明 |
|--------|------|
| `Fault_Enable` | 故障使能总开关 |
| `Fault_Type` | 故障类型（`DRIVE_ABNORMAL_FAULT = 1`） |
| `Fault_Wheel_Mask` | 故障轮掩码（A=0x01, B=0x02, C=0x04） |
| `Fault_Alpha_A/B/C` | 各轮目标速度衰减系数（0~1.0） |

> 故障配置通过 **USART3** 接收特定协议帧（`FAULT_CONFIG_MODE = 4`），由 `Apply_Fault_Config()` 解析，在 `balance.c` 的 `Drive_Motor()` 中按掩码衰减目标速度。

#### 4.3.4 关键常量

| 常量名 | 值 | 说明 |
|--------|-----|------|
| `CONTROL_DELAY` | 750 | 启动延时（约 10 秒，100Hz 计数），IMU 零偏稳定 |
| `CAR_NUMBER` | 7 | 支持车型数量 |
| `Omni` / `Mec` | 1 / 0 | 编译时运动学模式选择（**当前为 Omni**） |
| `X_PARAMETER` | `sqrt(3)/2` | 全向轮 X 方向分配系数 |
| `Y_PARAMETER` | `0.5` | 全向轮 Y 方向分配系数 |
| PWM 限幅 | ±16800 | 对应 TIM8 ARR=16799 |

### 4.4 控制源标志位（互斥）

| 标志位 | 说明 |
|--------|------|
| `PS2_ON_Flag` | PS2 手柄控制中 |
| `APP_ON_Flag` | 手机 APP 蓝牙控制中 |
| `Remote_ON_Flag` | 航模遥控器控制中 |
| `CAN_ON_Flag` | CAN 总线控制中 |
| `Usart_ON_Flag` | ROS/上位机串口控制中 |
| `Allow_Recharge` | 自动回充模式使能 |

### 4.5 数据流与控制流

```
MPU6050_task ──(I2C)──► MPU6050 ──► accel[3]/gyro[3] ──► filter.c ──► angle / yaw_angle
     │
Balance_task ──► encoder.c ──► MOTOR_A/B/C.Encoder ──► 增量 PI ──► Set_Pwm() ──► motor.c ──► 电机
     │
Balance_task ──► Drive_Motor(Vx,Vy,Vz) ──► 运动学解算 ──► MOTOR_A/B/C.Target
     │
usartx.c (USART1/3 中断) ──► 接收 ROS/上位机指令 ──► Move_X/Y/Z / Target_Angle / 故障配置
     │
data_task ──► 打包 Send_Data ──► USART1_SEND / USART3_SEND / CAN_SEND ──► 上位机
```

---

## 5. 04 last dance — 故障诊断深度学习

**技术栈**：Python 3.11、PyTorch、NumPy、scikit-learn、matplotlib、ONNX Runtime、joblib

### 5.1 目录树

```
04 last dance/last dance/
├── shuju0517/                          # 原始 CSV 数据集（4 类故障）
│   ├── normal/                         # 17 个文件
│   ├── drive fault/                    # 17 个文件
│   ├── wheel_slip/                     # 19 个文件
│   └── shaft eccentricity/             # 10 个文件
└── ypmodel/
    ├── models/
    │   ├── sage_cnn.py                 # SAGE-CNN 主模型
    │   ├── sage_cnn_ablation.py        # 消融变体
    │   ├── cwcnn_fa_baseline.py        # CWCNN-FA 基线
    │   ├── comparison_models.py        # 对比模型（CNN/MLP/LSTM/BiLSTM）
    │   └── __init__.py                 # build_model() 工厂函数
    ├── preprocess_fault_dataset.py     # CSV → NPY 滑动窗口 + 归一化
    ├── train_sage_cnn_ablation.py      # 严格协议训练
    ├── run_experiments.py              # 三阶段统一实验入口
    ├── replay_inference.py             # 单文件回放推理
    ├── realtime_sage_cnn_guard.py      # 部署守卫（静态门控 + 投票）
    ├── test_realtime_sage_cnn_guard.py # 守卫单元测试
    ├── freeze_results.py               # 最终图表与报告生成
    ├── prepare_final_summary.py
    ├── selected_sage_cnn_model/        # 选中模型与 scaler
    ├── results_paper_main_vx05/        # 阶段一：主实验（vx=0.5）
    ├── results_paper_generalization/   # 阶段二：跨速度泛化
    ├── results_deployment_robust/      # 阶段三：部署鲁棒性 + ONNX 导出
    └── results_final_summary/          # 冻结最终结果
```

### 5.2 模型架构 — SAGE-CNN

**输入**：`[N, 15, 50]`（batch, channel, time）

**15 通道顺序**：
```
 0-2:  odom_vx, odom_vy, odom_wz
 3-5:  wheel_speed0, wheel_speed1, wheel_speed2
 6-11: imu_ax, imu_ay, imu_az, imu_gx, imu_gy, imu_gz
12-14: current0, current1, current2
```

**输出**：4 类 logits → Softmax
- 0: normal
- 1: wheel_slip
- 2: drive_abnormal
- 3: shaft_eccentricity

**前向流程**：
1. **差分增强**：拼接原始 + 一阶差分 + 二阶差分 → `[N, 45, 50]`
2. **投影**：1×1 Conv1d 降维 → `[N, 15, 50]`
3. **源感知动态融合** (`SourceDynamicFusion`)：按 4 类传感器来源（odom/wheel/imu/current）生成动态权重，加权缩放
4. **Conv1d 特征提取**：4 层 Conv1d（第 1 层 kernel=7，其余 kernel=3），BN + ReLU
5. **FA 特征重标定** (`FALayer`)：通道级注意力 + 残差
6. **全局池化 + 分类**：AdaptiveAvgPool1d → Linear(15→60) → ReLU → Dropout → Linear(60→4)

### 5.3 基线与消融对比

| 模型 | 差分增强 | 源感知融合 | FA 层 | Conv 类型 |
|---|---|---|---|---|
| SAGE-CNN | ✓ | ✓ | ✓ | 普通 Conv1d |
| CWCNN-FA | ✗ | ✗ | ✓ | Depthwise Conv |
| w/o Diff | ✗ | ✓ | ✓ | 普通 Conv1d |
| w/o SAF | ✓ | ✗ | ✓ | 普通 Conv1d |
| w/o Diff+SAF | ✗ | ✗ | ✓ | 普通 Conv1d |

### 5.4 数据预处理流程

1. 读取 15 维特征列 + timestamp
2. 去头尾各 5 秒（`trim_start/end_sec`）
3. 丢弃 NaN/Inf 行
4. 滑动窗口：`window_size=50`, `step_size=10`
5. 按 run 划分：`run05` 为 test，其余 train
6. MinMax / Standard Scaler 归一化

### 5.5 三阶段实验

| 阶段 | 模式 | 数据范围 | 核心目的 |
|---|---|---|---|
| 一 | `paper_main_vx05` | 仅 vx0.5 | 横向模型对比、模块消融 |
| 二 | `paper_generalization` | vx0.5→vx0.3/vx0.7 | 跨速度泛化测试 |
| 三 | `deployment_robust` | 全速度混合 | 数据增强 + 早停 + ONNX 导出 |

**阶段三特殊配置**：
- dropout=0.4, weight_decay=1e-4
- 数据增强：`scale_range=(0.95,1.05)`, `noise_std=0.02`
- Label Smoothing 0.05
- 早停 patience=10

### 5.6 部署守卫 (`realtime_sage_cnn_guard.py`)

| 机制 | 条件 | 动作 |
|---|---|---|
| 静止门控 | odom 线速度 < 0.08 且 角速度 < 0.08 且 轮速 < 0.08，连续 5 个窗口 | 强制输出 `normal_static` |
| 低置信度保护 | top1 概率 < 0.70 或 top1-top2 间隔 < 0.15 | 不更新稳定标签 |
| 模糊保护 | top2 恰好为 wheel_slip 和 shaft_eccentricity 且间隔 < 0.15 | 保持上一稳定标签 |
| 滑动窗口投票 | 队列长度 5，某非 normal 标签出现 ≥3 次 | 更新为稳定标签 |

---

## 6. 跨项目数据流与接口定义

### 6.1 完整数据链路

```
03 omi_car (STM32F4 固件)
    │ 串口 115200 (/dev/ttyCH343USB0)
    ▼
01 ROS (wheeltec_robot_node)
    │ 发布 /odom, /imu, /wheel_speed, /PowerVoltage
    ▼
02 4CH-Current (电流传感器)
    │ 串口 115200 (/dev/ttyUSB0) → current_reader_node → /current_data
    ▼
01 ROS (data_collector.py)
    │ 时间同步 → 落盘 CSV (/home/wheeltec/R550PLUS_data_collect/log)
    ▼
04 last dance (preprocess → train)
    │ 滑动窗口 → SAGE-CNN 训练 → ONNX 导出
    ▼
01 ROS (Electron 桌面端 + ONNX Runtime 推理)
```

### 6.2 ROS Topic 接口总表

| Topic | 类型 | 发布者 | 订阅者 | 说明 |
|-------|------|--------|--------|------|
| `/odom` | `nav_msgs/Odometry` | wheeltec_robot_node | data_collector, cmd_vel_web_adapter | ~20Hz 里程计 |
| `/imu` | `sensor_msgs/Imu` | wheeltec_robot_node | data_collector | ~20Hz IMU |
| `/PowerVoltage` | `std_msgs/Float32` | wheeltec_robot_node | data_collector | ~2Hz 电池电压 |
| `/wheel_speed` | `std_msgs/Float32MultiArray` | wheeltec_robot_node | data_collector | ~20Hz 轮速 |
| `/current_data` | `std_msgs/Float32MultiArray` | current_reader_node | data_collector | 电流数据 |
| `/cmd_vel` | `geometry_msgs/Twist` | cmd_vel_web_adapter | wheeltec_robot_node | 安全层输出 |
| `/cmd_vel_web` | `geometry_msgs/Twist` | Web/Electron | cmd_vel_web_adapter | Web 原始指令 |
| `/chassis/heading_deg` | `std_msgs/Float32` | heading_bridge_node | wheeltec_robot_node | 航向角 |
| `/chassis/fault_config` | `std_msgs/Float32MultiArray` | fault_injector | wheeltec_robot_node | 故障注入配置 |
| `/web/estop` | `std_msgs/Bool` | Web/Electron | cmd_vel_web_adapter | 急停 |
| `/web/heartbeat` | `std_msgs/Empty` | Web/Electron | cmd_vel_web_adapter | 心跳 |
| `/web/collection_enable` | `std_msgs/Bool` | Web/Electron | data_collector | 采集启停 |

### 6.3 串口设备与协议

| 设备 | 路径 | 波特率 | 协议 | 数据帧 |
|------|------|--------|------|--------|
| 底盘控制器 | `/dev/ttyCH343USB0` | 115200 | 二进制 | 发送 13B / 接收 30B，帧头 `0x7B`，帧尾 `0x7D`，BCC XOR |
| 电流传感器 | `/dev/ttyUSB0` | 115200 | FireWater 文本 | `$CURRENT,ch0,ch1,ch2*XX\r\n` |

### 6.4 Web / HTTP 端口

| 服务 | 端口 | 说明 |
|------|------|------|
| Web 控制面板 | `8000` | HTTP 静态文件 + REST API |
| rosbridge WebSocket | `9090` | Web 浏览器 ↔ ROS 桥接 |

---

## 7. 关键参数速查表

### 7.1 运动控制参数

| 参数 | 值 | 位置 | 说明 |
|------|-----|------|------|
| `CONTROL_DELAY` | 750 | `03 omi_car/BALANCE/balance.h` | IMU 稳定等待（约 10s） |
| `Angle_KP/KI/KD` | 0.05/0.0/1.80 | `03 omi_car/BALANCE/system.h` | 航向角 PID |
| `Velocity_KP/KI` | 300/300 | `03 omi_car/BALANCE/system.h` | 速度环 PI |
| PWM 限幅 | ±16800 | `03 omi_car/HARDWARE/motor.c` | TIM8 ARR=16799 |
| `max_linear_x/y` | 0.4 m/s | `01 ROS` launch / C++ 参数 | 线速度限速 |
| `max_angular_z` | 1.0 rad/s | `01 ROS` launch / C++ 参数 | 角速度限速 |
| `heartbeat_timeout` | 1.0 s | `01 ROS` launch / C++ 参数 | 心跳超时 |
| `cmd_timeout` | 0.5 s | `01 ROS` launch / C++ 参数 | 指令超时 |

### 7.2 传感器参数

| 参数 | 值 | 位置 | 说明 |
|------|-----|------|------|
| 里程计频率 | ~20 Hz | `01 ROS/wheeltec_robot_node` | 由 STM32 发送频率决定 |
| 电流采样率 | 100 Hz | `02 4CH-Current/Firmware/main.c` | UART 发送周期 10ms |
| 电流滤波 EMA α | 0.02 | `02 4CH-Current/Firmware/current_filter.c` | 指数移动平均 |
| 电流滑动平均窗口 | 15 点 | `02 4CH-Current/Firmware/current_filter.c` | 第二级滤波 |
| INA282 增益 | 50 | `02 4CH-Current/Firmware/current_types.h` | 放大器增益 |
| 采样电阻 | 5 mΩ | `02 4CH-Current/Firmware/current_types.h` | Rshunt |
| 电流量程 | ±6.6 A | 计算值 | `(1.65V)/(50×0.005Ω)` |

### 7.3 深度学习参数

| 参数 | 值 | 说明 |
|------|-----|------|
| `window_size` | 50 | 滑动窗口长度（对应 2.5s @20Hz） |
| `step_size` | 10 | 滑动窗口步长 |
| 输入形状 | `[N, 15, 50]` | batch, channel, time |
| 输出类别 | 4 | normal / wheel_slip / drive_abnormal / shaft_eccentricity |
| 训练学习率 | 0.001 | Adam |
| 权重衰减 | 1e-5 ~ 1e-4 | 主实验 / 部署阶段 |
| 随机种子 | 42 | 固定，保证可复现 |
| 模型选择指标 | 验证集 Macro F1 | 统一标准 |
| 静止门控阈值 | 0.08 | 线速度/角速度/轮速均值 |
| 低置信度阈值 | 0.70 | top1 概率 |
| 模糊间隔阈值 | 0.15 | top1-top2 概率差 |
| 投票窗口长度 | 5 | 滑动窗口投票 |

---

## 8. 已知问题与风险清单

| # | 问题 | 影响范围 | 严重程度 | 建议措施 |
|---|------|----------|----------|----------|
| 1 | **协议不匹配**：02 固件默认 FireWater (Type 1)，但 HostApp 和 ROS 节点仅实现了二进制 (Type 0) 解析器 | `02 4CH-Current` | 🔴 高 | 联调前在 `uart_protocol.h` 中统一协议模式为 `0` 或 `1`；若保持 FireWater，需重写 `protocol.py` 和 `sensor_node.py` |
| 2 | **通道映射差异**：固件 FireWater 模式仅发送 3 通道 (M2/M3/M4)，但标定工具期望 4 通道；01 ROS 的 `current_reader` 也按 3 通道解析 | `02 4CH-Current` / `01 ROS` | 🟡 中 | 确认电流板与 ROS 节点的通道映射一致；M1（PA0）硬件未连接 |
| 3 | **标签映射不一致**：`preprocess_fault_dataset.py` 与 `run_experiments.py` 的故障类别顺序不同 | `04 last dance` | 🟡 中 | 使用 `run_experiments.py` 作为统一入口（顺序：0:normal, 1:wheel_slip, 2:drive_abnormal, 3:shaft_eccentricity） |
| 4 | **急停安全关键**：修改 `cmd_vel_web_adapter` 的任何超时、限速、死区参数后，必须在硬件上验证急停响应 | `01 ROS` | 🔴 高 | 任何参数变更后，进行物理急停测试 |
| 5 | **烧录安全**：03 omi_car 烧录后若 `CONTROL_DELAY` 被缩短，IMU 可能未稳定即启动电机 | `03 omi_car` | 🔴 高 | 保持 `CONTROL_DELAY=750`；烧录时确保机器人悬空或轮子离地 |
| 6 | **数据路径硬编码**：`/home/wheeltec/R550PLUS_data_collect/log` 在 01 ROS 中多处硬编码 | `01 ROS` | 🟢 低 | 修改时注意同步所有引用位置 |
| 7 | **滤波器延迟**：EMA(α=0.02) + 15 点滑动平均，总输出对阶跃响应有约数百毫秒延迟 | `02 4CH-Current` | 🟢 低 | 故障诊断时需考虑电流相位滞后 |
| 8 | **control.c 遗留文件**：`03 omi_car/BALANCE/control.c` 为旧版两轮平衡车代码，与当前全向轮项目并存但不直接参与主控制 | `03 omi_car` | 🟢 低 | 清理时注意编译链中是否仍有引用 |

---

## 附录：构建与运行速查

### 01 ROS
```bash
cd ~/catkin_ws && catkin_make && source devel/setup.bash
roslaunch turn_on_wheeltec_robot turn_on_wheeltec_robot.launch
roslaunch turn_on_wheeltec_robot data_collector.launch fault_label:=0
roslaunch turn_on_wheeltec_robot web_control.launch start_base:=false start_current_reader:=false start_data_collector:=false
```

### 02 4CH-Current
```bash
# 固件：Keil 打开 MDK-ARM/4CH-Current.uvprojx 编译，或 EIDE
# 上位机
cd "02 4CH-Current/HostApp" && uv sync && uv run ch4-current
# ROS 驱动
catkin_make
roslaunch ch4_current_sensor sensor.launch port:=/dev/ttyUSB0 baudrate:=115200
# 标定
cd "02 4CH-Current/Tools" && pip install -r requirements.txt && python calibration_tool.py
```

### 03 omi_car
```bash
# VS Code + EIDE 扩展
# 命令面板：eide.project.build / eide.project.uploadToDevice
# 或运行任务：build / flash / build and flash / clean
keilkilll.bat  # 清理 Keil 生成物
```

### 04 last dance
```bash
cd "04 last dance/last dance/ypmodel"
python preprocess_fault_dataset.py --data_dir ../shuju0517 --output_dir ./datasets
python run_experiments.py --mode paper_main_vx05 --require_figures
python run_experiments.py --mode deployment_robust --require_figures
python replay_inference.py --csv ../shuju0517/normal/xxx.csv --model results_deployment_robust/export/best_model.onnx
```

---

> **文档结束**。本文件基于当前工作区源码实际状态生成，如需更新，请重新运行代码梳理流程。
