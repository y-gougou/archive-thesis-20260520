# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## 项目概述

R550PLUS 三全向轮机器人 ROS 包，包含传感器数据采集、Web 控制、定速巡航和 Electron 桌面端监控功能。

## 构建

```bash
cd ~/catkin_ws          # catkin 工作空间根目录
catkin_make             # 编译 C++ 节点 wheeltec_robot_node
source devel/setup.bash
```

仅修改 Python 脚本时无需重新编译。修改 C++ 源码（`src/` 下）或 `CMakeLists.txt` 后需要 `catkin_make`。

## 目录结构

```
turn_on_wheeltec_robot/
├── src/                              # C++ 底盘节点
│   ├── wheeltec_robot.cpp            # 串口通信、里程计、IMU 发布
│   ├── wheeltec_robot.h              # 类定义、串口协议常量
│   └── Quaternion_Solution.cpp       # IMU 四元数解算
├── include/                          # C++ 头文件
│   ├── wheeltec_robot.h
│   └── Quaternion_Solution.h
├── scripts/                          # Python 节点
│   ├── core/                         # 共享工具库
│   │   ├── control_utils.py          # PID、clamp、zero twist
│   │   ├── csv_utils.py              # CSV 写入、run id
│   │   ├── file_api.py               # CSV 文件列表和安全查找
│   │   ├── ros_params.py             # 类型化 ROS 参数读取
│   │   ├── serial_utils.py           # 串口 open/retry/校验
│   │   └── time_utils.py             # 时间戳和格式化
│   ├── cmd_vel_web_adapter.py        # Web 控制安全适配器 + PID 巡航
│   ├── current_reader.py             # 电流传感器串口读取
│   ├── data_collector.py             # 数据采集（CSV 16 通道）
│   ├── heading_bridge.py             # N100 IMU 航向标准化
│   ├── web_dashboard_server.py       # Web 页面服务 + CSV API
│   ├── fault_injector.py             # 故障注入控制
│   ├── build_fault_dataset.py        # 故障数据集构建
│   ├── send_mark.py                  # 手柄标记发送
│   └── node_ping.py                  # 节点连通性检测
├── launch/                           # 启动文件
│   ├── turn_on_wheeltec_robot.launch # 底盘 + IMU + 里程计
│   ├── web_control.launch            # Web 控制主入口
│   ├── data_collector.launch         # 数据采集
│   ├── fault_injection.launch        # 故障注入
│   ├── navigation.launch             # 导航
│   ├── mapping.launch                # SLAM 建图
│   └── include/                      # 子 launch 文件
│       ├── base_serial.launch        # 底盘串口 + heading bridge
│       └── ...
├── config/                           # 导航参数配置
│   ├── costmap_car/                  # 各车型 costmap 参数
│   ├── costmap_common/               # 通用 costmap 参数
│   └── nav_common/                   # 导航规划器参数
├── map/                              # 地图文件
│   ├── WHEELTEC.yaml
│   └── WHEELTEC.pgm
├── web/                              # React + Vite Web 前端
│   ├── src/
│   └── package.json
├── desktop/                          # Electron 桌面端
│   ├── main.js                       # 主进程
│   ├── preload.js                    # 安全 IPC 桥
│   ├── app-config.json               # 应用品牌配置
│   ├── db/database.js                # SQLite 本地数据库
│   ├── renderer/                     # 渲染进程（app.js, charts.js 等）
│   ├── assets/                       # 图标资源（icon.ico, icon.png）
│   ├── scripts/sync-app-name.js      # 品牌同步脚本
│   └── electron-builder.yml          # 打包配置
├── docs/                             # 文档
│   ├── DESKTOP_APP.md                # 桌面端开发文档
│   ├── PROTOCOL.md                   # 串口协议文档
│   └── 代码实现说明.md               # 实现细节
├── CMakeLists.txt
└── package.xml
```

## 节点架构与数据流

```
浏览器/桌面端 --(rosbridge WS:9090)--> rosbridge_websocket
  |                                          |
  | /cmd_vel_web                       /web/heartbeat, /web/estop
  v                                          |
cmd_vel_web_adapter.py (PID + 安全超时) -----|
  |
  | /cmd_vel (40Hz)
  v
wheeltec_robot_node (C++) --[串口]--> STM32 下位机
  |
  | /odom, /imu, /PowerVoltage (20Hz)
  v
data_collector.py --[CSV]--> datasets/

current_reader.py --[串口 ttyUSB0]--> /current_data (~5-6Hz)

heading_bridge.py: /n100/imu -> /chassis/heading_deg -> wheeltec_robot_node
```

`cmd_vel_web_adapter.py` 是 Web 控制的核心安全层：接收 `/cmd_vel_web`，经过心跳检测、急停、限速、死区处理后发布到 `/cmd_vel`。巡航模式下通过 PID 闭环控制速度。

## 启动命令

**推荐方式（单命令启动）：**

```bash
roslaunch turn_on_wheeltec_robot web_control.launch
```

**分步启动（多终端）：**

```bash
# 终端 1：底盘控制
roslaunch turn_on_wheeltec_robot turn_on_wheeltec_robot.launch

# 终端 2：数据采集
roslaunch turn_on_wheeltec_robot data_collector.launch fault_label:=0

# 终端 3：Web 控制（禁用冲突节点）
roslaunch turn_on_wheeltec_robot web_control.launch start_base:=false start_current_reader:=false start_data_collector:=false
```

## Web 控制端口

| 服务 | 端口 | 说明 |
|------|------|------|
| Web 界面 | `http://<robot_ip>:8000` | 浏览器控制面板 |
| rosbridge | `ws://<robot_ip>:9090` | WebSocket 桥接 |

## 串口设备

| 设备 | 路径 | 波特率 | 用途 |
|------|------|--------|------|
| 底盘控制器 | `/dev/ttyCH343USB0` | 115200 | 电机控制、里程计、IMU |
| 电流传感器 | `/dev/ttyUSB0` | 115200 | 三通道电流 |

串口参数通过 launch 文件参数传递（`web_control.launch` 中的 `current_port` 等），不在 Python 脚本中硬编码。

## 串口协议

- 底盘数据帧：帧头 `0x7B`，帧尾 `0x7D`，BCC 校验
- 发送帧（ROS->STM32）：13 字节，含速度 + 角度标志 + 目标角度
- 接收帧（STM32->ROS）：30 字节，含速度 + IMU + 电压 + 轮速
- 电流帧：`$CURRENT,ch0,ch1,ch2*XX\r\n`，XOR 校验
- 详细协议文档：`docs/PROTOCOL.md`

## 核心话题

| 话题 | 类型 | 频率 | 说明 |
|------|------|------|------|
| `/odom` | nav_msgs/Odometry | 20Hz | 里程计数据 |
| `/imu` | sensor_msgs/Imu | 20Hz | IMU 数据 |
| `/PowerVoltage` | std_msgs/Float32 | 20Hz | 电池电压 |
| `/current_data` | Float32MultiArray | ~5-6Hz | 三通道电流 |
| `/cmd_vel` | geometry_msgs/Twist | 40Hz | 最终电机速度 |
| `/cmd_vel_web` | geometry_msgs/Twist | - | Web 手动驾驶指令 |
| `/web/cruise_cmd` | geometry_msgs/Twist | - | 巡航目标速度 |
| `/web/cruise_enable` | std_msgs/Bool | - | 巡航开关 |
| `/chassis/heading_deg` | std_msgs/Float32 | - | 标准化航向角 |
| `/target_angle` | std_msgs/Float32 | - | 目标航向角 |

## 安全参数

`web_control.launch` 中的关键参数：

| 参数 | 默认值 | 说明 |
|------|--------|------|
| `cmd_timeout` | 0.5s | 指令超时停机 |
| `heartbeat_timeout` | 1.0s | 心跳超时停机 |
| `max_linear_x` | 1.50 m/s | X 轴最大线速度 |
| `max_linear_y` | 1.00 m/s | Y 轴最大线速度 |
| `max_angular_z` | 3.75 rad/s | Z 轴最大角速度 |
| `linear_deadband` | 0.02 | 线速度死区 |
| `angular_deadband` | 0.03 | 角速度死区 |

## 数据采集

### 16 通道 CSV 数据

位置(x,y,z)、速度(vx,vy,vz)、加速度(ax,ay,az)、角速度(gx,gy,gz)、电压、电流(c0,c1,c2)

### 故障标签

| 标签 | 名称 | 说明 |
|------|------|------|
| 0 | normal | 正常 |
| 1 | drive_fault | 驱动异常（单轮堵转） |
| 2 | wheel_slip | 轮子打滑/损坏 |
| 3 | shaft_eccentric | 电机轴偏心 |
| 4 | battery_low | 电池低压 |

### 采集命令
```bash
roslaunch turn_on_wheeltec_robot data_collector.launch fault_label:=0  # 正常
roslaunch turn_on_wheeltec_robot data_collector.launch fault_label:=1  # 驱动异常
roslaunch turn_on_wheeltec_robot data_collector.launch fault_label:=2  # 轮子打滑
roslaunch turn_on_wheeltec_robot data_collector.launch fault_label:=3  # 电机轴偏心
roslaunch turn_on_wheeltec_robot data_collector.launch fault_label:=4  # 电池低压
```

### 输出目录

默认：`/home/wheeltec/R550PLUS_data_collect/log_v2`

## Electron 桌面端

```bash
cd desktop
npm install
npm start           # 开发模式
npm run build       # 打包（自动同步品牌配置）
```

品牌配置集中在 `desktop/app-config.json`，`npm run build` 时自动同步到 `electron-builder.yml`、`package.json`、`index.html`、`i18n.js`、`app.js`。

详见 `docs/DESKTOP_APP.md`。

## 调试命令

```bash
# 查看话题频率
rostopic hz /odom
rostopic hz /current_data

# 发送巡航命令
rostopic pub /web/cruise_cmd geometry_msgs/Twist '{linear: {x: 0.5}}'
rostopic pub /web/cruise_enable std_msgs/Bool '{data: true}'

# 串口检查
ls -l /dev/ttyCH343USB0 /dev/ttyUSB0

# 桌面端静态检查
node --check desktop/main.js
node --check desktop/preload.js
```

## 作者

杨鹏 - 燕山大学本科毕业设计
