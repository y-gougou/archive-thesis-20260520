# AGENTS.md - WHEELTEC Omni-Directional Car Project

## Project Overview
STM32F4xx-based omni-directional wheel car (全向轮小车) using FreeRTOS, EIDE (Embedded IDE), and JLink debugging.

## Key Architecture
- **MCU**: STM32F40_41xxx (Cortex-M4 with FPU)
- **RTOS**: FreeRTOS with multiple tasks for balance, IMU, display, LED, PS2 controller, and data communication
- **Toolchain**: Keil AC5 via EIDE VS Code extension
- **Debugger**: JLink (8000 kHz speed)

## Build & Flash Commands
- **Build**: Use EIDE extension command `eide.project.build` or VS Code task "build"
- **Flash**: Use EIDE extension command `eide.project.uploadToDevice` or VS Code task "flash"
- **Build & Flash**: Use VS Code task "build and flash"
- **Clean**: Use VS Code task "clean" or run `keilkilll.bat` for Keil artifacts

## Project Structure
```
├── USER/           # Main application (main.c, interrupt handlers)
├── BALANCE/        # Core balance and control logic (system.c, balance.c, control.c)
├── HARDWARE/       # Peripheral drivers (LED, OLED, motor, encoder, PS2, etc.)
├── SYSTEM/         # System utilities (delay, sys, usart)
├── CORE/           # Startup assembly file
├── FWLIB/          # STM32 Standard Peripheral Library
├── FreeRTOS/       # FreeRTOS kernel and portable layer
├── HUB_DRIVER/     # Hub motor driver (UART and CAN interfaces)
├── MPU6050/        # IMU sensor driver (I2C interface)
├── AutoRecharge/   # Auto-recharging functionality
├── .eide/          # EIDE project configuration
└── .vscode/        # VS Code tasks configuration
```

## Critical Files
- `USER/main.c`: Entry point - creates FreeRTOS tasks
- `BALANCE/system.h`: Master include file with all headers and global variables
- `BALANCE/balance.c`: Core balance control logic
- `BALANCE/control.c`: Motor control and PID algorithms
- `.eide/eide.yml`: Project configuration (toolchain, memory layout, includes)

## FreeRTOS Tasks (created in main.c)
1. **Balance_task**: Vehicle motion control (priority: BALANCE_TASK_PRIO)
2. **MPU6050_task**: IMU data reading (priority: MPU6050_TASK_PRIO)
3. **show_task**: OLED display (priority: SHOW_TASK_PRIO)
4. **led_task**: LED blinking (priority: LED_TASK_PRIO)
5. **pstwo_task**: PS2 controller reading (priority: PS2_TASK_PRIO)
6. **data_task**: USART3, USART1, and CAN data sending (priority: DATA_TASK_PRIO)

## Important Constants
- `CONTROL_DELAY`: 750 (10-second delay before allowing movement)
- `CAR_NUMBER`: 7 (number of supported car types)
- Motor structure: `Motor_parameter` with encoder, RPM, PWM, target, and PID values
- Car modes: `Omni` (1) for omni-directional, `Mec` (0) for mecanum

## Development Notes
- **No unit tests**: This is bare-metal embedded code; verification is hardware-based
- **Build artifacts**: Output in `build/` directory (gitignored)
- **Keil artifacts**: Use `keilkilll.bat` to clean Keil-generated files
- **Case sensitivity**: Some files have mixed case (e.g., `LED.C` vs `led.h`)
- **Language**: Code comments are bilingual (Chinese/English)

## Configuration Details
- **Memory layout**: ROM at 0x08000000 (512KB), RAM at 0x20000000 (128KB)
- **Compiler flags**: C99 mode, optimization level 2, microLIB enabled
- **Preprocessor defines**: `STM32F40_41xxx`, `USE_STDPERIPH_DRIVER`, `__FPU_PRESENT=1`

## Quick Reference
- **Entry point**: `USER/main.c:main()` → `systemInit()` → creates FreeRTOS tasks
- **Global state**: All major variables declared in `BALANCE/system.h`
- **Motor control**: See `BALANCE/control.c` for PID and speed control
- **IMU data**: `MPU6050/MPU6050.c` handles I2C communication
- **Hub motors**: `HUB_DRIVER/HubDriver.c` (UART) and `HubDriverCan.c` (CAN)