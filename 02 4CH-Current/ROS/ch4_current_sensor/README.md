# 4CH-Current ROS Package

ROS Noetic 包，用于集成 4 通道电流传感器到机器人系统。

## 功能特性

- ✅ 发布 `/current_data` 话题（自定义消息）
- ✅ 发布诊断信息到 `/diagnostics`
- ✅ 可配置串口参数
- ✅ 自动重连机制

## 安装

### 依赖

- ROS Noetic
- Python 3.8+
- pyserial

```bash
sudo apt-get install python3-serial
```

### 编译

```bash
# 创建工作空间（如果还没有）
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws/src

# 复制包到 src 目录
cp -r /path/to/ch4_current_sensor .

# 编译
cd ~/catkin_ws
catkin_make

# source 环境
source devel/setup.bash
```

## 使用

### 启动节点

```bash
# 使用默认参数
roslaunch ch4_current_sensor sensor.launch

# 指定串口和波特率
roslaunch ch4_current_sensor sensor.launch port:=/dev/ttyUSB0 baudrate:=115200

# 指定发布频率
roslaunch ch4_current_sensor sensor.launch publish_rate:=20.0
```

### 订阅数据

```bash
# 查看话题
rostopic echo /current_data

# 绘制曲线
rqt_plot /current_data/ch0_current /current_data/ch1_current
```

### 参数配置

| 参数 | 类型 | 默认值 | 说明 |
|------|------|--------|------|
| `port` | string | `/dev/ttyUSB0` | 串口设备名 |
| `baudrate` | int | `115200` | 波特率 |
| `publish_rate` | float | `10.0` | 发布频率 (Hz) |

## 消息定义

### CurrentData.msg

```
Header header
float32 ch0_current  # Channel 0 current in Amperes
float32 ch1_current  # Channel 1 current in Amperes
float32 ch2_current  # Channel 2 current in Amperes
float32 ch3_current  # Channel 3 current in Amperes
uint16 ch0_raw_adc   # Channel 0 raw ADC value
uint16 ch1_raw_adc   # Channel 1 raw ADC value
uint16 ch2_raw_adc   # Channel 2 raw ADC value
uint16 ch3_raw_adc   # Channel 3 raw ADC value
```

## Python 脚本集成

```python
#!/usr/bin/env python3

import rospy
from ch4_current_sensor.msg import CurrentData

def callback(msg):
    rospy.loginfo(f"CH0: {msg.ch0_current:.3f} A")

rospy.init_node('current_listener')
sub = rospy.Subscriber('/current_data', CurrentData, callback)
rospy.spin()
```

## C++ 集成

```cpp
#include <ros/ros.h>
#include <ch4_current_sensor/CurrentData.h>

void callback(const ch4_current_sensor::CurrentData::ConstPtr& msg) {
    ROS_INFO("CH0: %.3f A", msg->ch0_current);
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "current_listener");
    ros::NodeHandle nh;
    
    ros::Subscriber sub = nh.subscribe("/current_data", 10, callback);
    ros::spin();
    
    return 0;
}
```

## 诊断信息

节点会发布诊断信息到 `/diagnostics`，包括：

- 连接状态
- 接收帧数
- 错误计数
- 串口配置

使用 `rqt_runtime_monitor` 查看：

```bash
rqt_runtime_monitor
```

## 故障排查

### 节点启动失败

检查串口权限：
```bash
sudo chmod 666 /dev/ttyUSB0
# 或永久添加用户到 dialout 组
sudo usermod -a -G dialout $USER
```

### 无数据发布

1. 检查设备是否已连接：`ls /dev/ttyUSB*`
2. 检查波特率是否匹配设备固件
3. 查看节点日志：`rosnode info /ch4_current_sensor`

## 许可证

MIT License
