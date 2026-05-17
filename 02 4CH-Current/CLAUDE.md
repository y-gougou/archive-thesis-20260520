# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

4-Channel Current Sensor - An embedded firmware project for STM32F103C8T6 with a Python host application and ROS integration. The device reads current from 4 channels via INA282 amplifiers, displays on OLED, and communicates via UART.

## Directory Structure

```
Firmware/           # STM32 embedded C firmware (Keil MDK-ARM project)
  Core/
    Inc/            # HAL headers and app-specific: current_types.h, current_filter.h, uart_protocol.h
    Src/            # Implementation: main.c, adc.c, uart_protocol.c, current_filter.c, oled.c
  Drivers/          # STM32 HAL and CMSIS
  MDK-ARM/          # Keil project files (.uvproj, .sct)
  4CH-Current.ioc   # STM32CubeMX configuration

HostApp/            # Python PySide6 host application (uv-managed)
  src/ch4_current/
    main.py         # Entry point (ch4-current command)
    gui.py          # PySide6 UI with pyqtgraph
    protocol.py     # Protocol parsing
    serial_comm.py  # Serial communication

ROS/ch4_current_sensor/  # ROS Noetic package for robot integration

Tools/
  calibration_tool.py    # Tkinter-based calibration utility
  README_Calibration.md  # Calibration procedure documentation
```

## Building & Running

### Firmware
- **IDE**: Keil MDK-ARM (open `Firmware/MDK-ARM/*.uvprojx`)
- **Config**: `Firmware/4CH-Current.ioc` - STM32CubeMX file, edit to regenerate HAL
- **Protocol selection**: `Firmware/Core/Inc/uart_protocol.h` line 31 - `UART_PROTOCOL_TYPE`:
  - `0` = Custom binary protocol (bidirectional)
  - `1` = FireWater text protocol (compatible with VOFA+)
- **Calibration params**: Edit `Firmware/Core/Inc/current_types.h` lines 68-86

### HostApp
```bash
cd HostApp
uv sync                    # Install dependencies
uv run ch4-current        # Run application
uv run black src/         # Format code
uv run ruff check src/    # Lint
uv run mypy src/          # Type check
```

### ROS
```bash
cd ~/catkin_ws && catkin_make
roslaunch ch4_current_sensor sensor.launch port:=/dev/ttyUSB0 baudrate:=115200
```

## Architecture

### Firmware Data Flow
```
ADC (DMA) → Raw Buffer → process_adc_data() → Filter → g_current_values[] → OLED display
                                                    ↓
                                            UART (protocol_send_current_data)
```

### UART Protocol
Two modes via `UART_PROTOCOL_TYPE`:
- **Binary (Type 0)**: Frame format `AA 55 | CMD | LEN | DATA | CRC | 0D 0A`
- **FireWater (Type 1)**: Text format `$CURRENT,ch0,ch1,ch2*XX\r\n`

Only 3 channels (M2/M3/M4) are sent via UART - channel 0 (M1/PA0) has no output.

### Calibration Formula
```
真实电流 = 测量电流 × GAIN + OFFSET
```
Apply gain/offset per-channel from `current_types.h` during ADC processing.
