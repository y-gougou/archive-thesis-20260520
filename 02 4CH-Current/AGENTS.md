# Repository Guidelines

## Project Structure & Module Organization

- `Firmware/`: STM32F103C8T6 C firmware. Application code is in `Core/Src/`, headers are in `Core/Inc/`, vendor HAL/CMSIS code is in `Drivers/`, and Keil project files are in `MDK-ARM/`.
- `HostApp/`: Python host application. Source lives under `src/ch4_current/`; `main.py` is the entry point, `gui.py` contains the PySide6 UI, `protocol.py` handles frame parsing, and `serial_comm.py` handles serial I/O.
- `ROS/ch4_current_sensor/`: ROS Noetic package with `scripts/sensor_node.py`, `msg/CurrentData.msg`, and `launch/sensor.launch`.
- `Tools/`: calibration utilities, including `calibration_tool.py`.

## Build, Test, and Development Commands

- `cd HostApp && uv sync`: install Python dependencies for the host app.
- `cd HostApp && uv run ch4-current`: run the desktop host application.
- `cd HostApp && uv run black src/`: format Python source.
- `cd HostApp && uv run ruff check src/`: lint Python source.
- `cd HostApp && uv run mypy src/`: run static type checks.
- `cd HostApp && uv run pytest`: run Python tests when present.
- Open `Firmware/MDK-ARM/4CH-Current.uvprojx` in Keil MDK-ARM to build firmware.
- In a catkin workspace, run `catkin_make`, then `roslaunch ch4_current_sensor sensor.launch port:=/dev/ttyUSB0 baudrate:=115200`.

## Coding Style & Naming Conventions

Python targets 3.10+, uses 4-space indentation, Black formatting, Ruff linting, and MyPy type checking. Keep modules and functions in `snake_case`, classes in `PascalCase`, and constants in `UPPER_SNAKE_CASE`.

Firmware C should follow the existing STM32Cube/HAL layout: public declarations in `Core/Inc/*.h`, implementations in `Core/Src/*.c`, and hardware configuration changes through CubeMX/Keil project files where appropriate.

## Testing Guidelines

There is no committed test suite yet. For Python changes, add focused `pytest` tests under `HostApp/tests/` using names like `test_protocol.py`. Prioritize protocol parsing, calibration math, and serial error handling. For firmware changes, document manual verification steps, expected UART output, and hardware setup in the pull request.

## Commit & Pull Request Guidelines

This checkout has no `.git` history, so no repository-specific commit convention is available. Use concise imperative commits such as `Fix UART frame checksum` or `Add host protocol tests`.

Pull requests should include a short summary, affected areas (`Firmware`, `HostApp`, `ROS`, `Tools`), test or hardware verification results, linked issues when available, and screenshots for GUI changes.

## Security & Configuration Tips

Do not commit machine-specific serial ports, generated calibration captures, or local IDE state unless intentionally shared. Keep protocol mode changes in `Firmware/Core/Inc/uart_protocol.h` and calibration constants in `Firmware/Core/Inc/current_types.h` clearly documented.
