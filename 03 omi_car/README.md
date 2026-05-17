# WHEELTEC 全向轮小车项目

## 项目概述

这是一个基于 STM32F4xx 的全向轮小车项目，使用 FreeRTOS 实时操作系统，采用 EIDE (Embedded IDE) 进行开发，支持 JLink 调试。

**品牌**: WHEELTEC  
**版本**: V3.5  
**更新时间**: 2021-01-29  
**官方网站**: wheeltec.net  
**淘宝店铺**: shop114407458.taobao.com  
**速卖通**: https://minibalance.aliexpress.com/store/4455017

## 硬件信息

- **MCU**: STM32F40_41xxx (Cortex-M4 with FPU)
- **内存布局**: 
  - ROM: 0x08000000 (512KB)
  - RAM: 0x20000000 (128KB)
- **调试器**: JLink (8000 kHz 速度)
- **传感器**: MPU6050 (I2C 接口)
- **电机驱动**: 支持 UART 和 CAN 接口的轮毂电机
- **遥控器**: PS2 手柄支持

## 软件架构

### 核心组件
- **实时操作系统**: FreeRTOS
- **外设驱动**: STM32 Standard Peripheral Library
- **工具链**: Keil AC5 via EIDE VS Code 扩展
- **编译模式**: C99，优化等级 2，启用 microLIB

### 主要功能模块
1. **平衡控制**: 核心运动控制逻辑
2. **IMU 数据处理**: MPU6050 数据读取和处理
3. **电机控制**: PID 算法实现
4. **通信接口**: USART、CAN 总线通信
5. **自动回充**: 自动充电功能

## 目录结构

```
├── USER/           # 主应用程序 (main.c, 中断处理)
├── BALANCE/        # 核心平衡和控制逻辑 (system.c, balance.c, control.c)
├── HARDWARE/       # 外设驱动 (LED, OLED, 电机, 编码器, PS2 等)
├── SYSTEM/         # 系统工具 (delay, sys, usart)
├── CORE/           # 启动汇编文件
├── FWLIB/          # STM32 标准外设库
├── FreeRTOS/       # FreeRTOS 内核和移植层
├── HUB_DRIVER/     # 轮毂电机驱动 (UART 和 CAN 接口)
├── MPU6050/        # IMU 传感器驱动 (I2C 接口)
├── AutoRecharge/   # 自动回充功能
├── .eide/          # EIDE 项目配置
└── .vscode/        # VS Code 任务配置
```

## 关键文件

- `USER/main.c`: 程序入口点 - 创建 FreeRTOS 任务
- `BALANCE/system.h`: 主包含文件，包含所有头文件和全局变量定义
- `BALANCE/balance.c`: 核心平衡控制逻辑
- `BALANCE/control.c`: 电机控制和 PID 算法实现
- `.eide/eide.yml`: 项目配置文件（工具链、内存布局、包含路径）

## FreeRTOS 任务

在 `main.c` 中创建的 FreeRTOS 任务：

1. **Balance_task**: 车辆运动控制任务 (优先级: BALANCE_TASK_PRIO)
2. **MPU6050_task**: IMU 数据读取任务 (优先级: MPU6050_TASK_PRIO)
3. **show_task**: OLED 显示任务 (优先级: SHOW_TASK_PRIO)
4. **led_task**: LED 闪烁任务 (优先级: LED_TASK_PRIO)
5. **pstwo_task**: PS2 手柄读取任务 (优先级: PS2_TASK_PRIO)
6. **data_task**: USART3、USART1 和 CAN 数据发送任务 (优先级: DATA_TASK_PRIO)

## 重要常量

- `CONTROL_DELAY`: 750 (启动后 10 秒延迟才允许移动)
- `CAR_NUMBER`: 7 (支持的车型数量)
- 电机结构: `Motor_parameter` 包含编码器、转速、PWM、目标值和 PID 参数
- 车型模式: `Omni` (1) 为全向轮模式，`Mec` (0) 为麦克纳姆轮模式

## 构建和烧录

### 使用 EIDE 扩展
- **构建**: 使用 EIDE 扩展命令 `eide.project.build`
- **烧录**: 使用 EIDE 扩展命令 `eide.project.uploadToDevice`

### 使用 VS Code 任务
- **构建**: VS Code 任务 "build"
- **烧录**: VS Code 任务 "flash"
- **构建并烧录**: VS Code 任务 "build and flash"
- **清理**: VS Code 任务 "clean" 或运行 `keilkilll.bat`

## 开发注意事项

- **无单元测试**: 这是裸机嵌入式代码，验证基于硬件测试
- **构建产物**: 输出在 `build/` 目录（已 gitignore）
- **Keil 产物**: 使用 `keilkilll.bat` 清理 Keil 生成的文件
- **大小写敏感**: 某些文件大小写混合（如 `LED.C` vs `led.h`）
- **语言**: 代码注释为中英文双语

## 配置详情

### 编译器配置
- **C 语言标准**: C99
- **优化级别**: Level 2
- **浮点硬件**: 单精度浮点
- **预处理器定义**: 
  - `STM32F40_41xxx`
  - `USE_STDPERIPH_DRIVER`
  - `__FPU_PRESENT=1`
  - `__TARGET_FPU_VFP`
  - `ARM_MATH_CM4`
  - `__CC_ARM`

### 包含路径
- CORE
- SYSTEM/delay, SYSTEM/sys, SYSTEM/usart
- USER
- HARDWARE/LED
- FWLIB/inc
- FreeRTOS/include, FreeRTOS/portable/RVDS/ARM_CM4F
- BALANCE
- HARDWARE
- HUB_DRIVER
- MPU6050
- AutoRecharge
- .cmsis/include

## 快速参考

- **程序入口**: `USER/main.c:main()` → `systemInit()` → 创建 FreeRTOS 任务
- **全局状态**: 所有主要变量在 `BALANCE/system.h` 中声明
- **电机控制**: 参见 `BALANCE/control.c` 中的 PID 和速度控制
- **IMU 数据**: `MPU6050/MPU6050.c` 处理 I2C 通信
- **轮毂电机**: `HUB_DRIVER/HubDriver.c` (UART) 和 `HubDriverCan.c` (CAN)

## 更新日志

### 2023.12.04
1. 小车电压测量逻辑更新
2. 新增自动回充功能
3. 新增 APP 按键开启自动回充功能: 第1排第2个按键
4. 自动回充时改变 RGB 灯颜色: 红-普通状态；黄-开启自动回充；紫-正在充电
5. 自动回充功能与普通小车源码合并：与上位机通信逻辑更新
6. 自动回充逻辑更新：新增访问自动回充特征码功能、新增在线检测自动回充装备是否在线功能、新增逻辑发送是否开启自动回充功能、发送接收到的红外个数功能

### 2023.09.27
1. 优化了航模遥控数据采集内容

### 2023.08.21
1. 新增小车在非斜坡时，PWM 残留自动清除功能
2. 自检逻辑更新，相比之前更灵敏，误判率低，仍可通过急停开关跳过自检

## 接线说明

详细的接线信息请参考项目中的 `全向轮小车接线说明.pdf` 文件。

## 故障排除

1. **构建失败**: 检查 EIDE 配置和工具链设置
2. **烧录失败**: 确认 JLink 连接和速度设置
3. **电机不转**: 检查电机驱动连接和 PWM 配置
4. **IMU 数据异常**: 检查 MPU6050 I2C 连接
5. **通信问题**: 检查 USART 和 CAN 总线配置

## 许可证

版权所有 © WeiHong Co.Ltd (WHEELTEC)  
保留所有权利