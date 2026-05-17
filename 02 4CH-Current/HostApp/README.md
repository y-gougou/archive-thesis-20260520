# 4CH-Current Host Application

Python 上位机应用程序，用于 4 通道电流传感器的数据采集、可视化和记录。

## 功能特性

- ✅ 实时数据可视化（4 通道电流曲线）
- ✅ 串口自动扫描与连接
- ✅ CSV 格式数据记录
- ✅ 设备命令控制（版本查询、重置等）
- ✅ 支持二进制协议解析
- ✅ PySide6 现代化 GUI

## 安装

### 使用 UV（推荐）

```bash
# 安装 UV
curl -LsSf https://astral.sh/uv/install.sh | sh

# 进入项目目录
cd HostApp

# 创建虚拟环境并安装依赖
uv sync

# 运行应用
uv run ch4-current
```

### 使用 pip

```bash
cd HostApp
pip install -e .
ch4-current
```

## 使用说明

### 基本操作

1. **连接设备**
   - 点击 "Refresh Ports" 扫描可用串口
   - 从下拉列表选择对应的串口（如 `COM3` 或 `/dev/ttyUSB0`）
   - 点击 "Connect" 建立连接

2. **查看数据**
   - 连接成功后，4 个通道的电流值会实时显示
   - 曲线图会自动更新，显示最近 500 个数据点

3. **记录数据**
   - 点击 "Start Recording" 开始记录
   - 数据将保存为 `current_data_YYYYMMDD_HHMMSS.csv`
   - 点击 "Stop Recording" 停止记录

4. **设备控制**
   - "Query Version": 查询固件版本号
   - "Reset Device": 重启设备

### 协议切换

上位机自动识别设备使用的协议类型（二进制或 FireWater）。

## 开发

### 代码规范

项目使用以下工具确保代码质量：

```bash
# 代码格式化
uv run black src/

# 代码检查
uv run ruff check src/

# 类型检查
uv run mypy src/
```

### 项目结构

```
src/ch4_current/
├── __init__.py       # 包初始化
├── protocol.py       # 协议解析
├── serial_comm.py    # 串口通信
├── gui.py            # PySide6 GUI
└── main.py           # 主入口
```

## 故障排查

### 无法找到串口

- **Windows**: 确保安装了对应的 USB 转串口驱动（如 CH340、CP2102）
- **Linux**: 确保当前用户在 `dialout` 组中：`sudo usermod -a -G dialout $USER`

### 连接成功但无数据

1. 检查固件的波特率设置（应为 115200）
2. 确认固件已启用串口输出（`UART_PROTOCOL_TYPE`）
3. 查看日志输出，检查是否有协议解析错误

### 数据抖动

检查固件端的滤波参数（`FILTER_WINDOW_SIZE`, `EMA_ALPHA`）。

## 许可证

MIT License
