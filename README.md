# Blink RTOS STM32F4

A FreeRTOS-based blink project for STM32F407 microcontrollers.

## Overview

This project demonstrates FreeRTOS task creation and scheduling on an STM32F407ZGT6 (168 MHz HCLK). The built-in LED on PC13 toggles every 500 ms, driven by a FreeRTOS task.

## Hardware

- **MCU**: STM32F407ZGT6 (or any STM32F4 with PC13 LED)
- **Board**: STM32F407 Discovery / Nucleo-144
- **Debug/Flash**: ST-Link / CMSIS-DAP
- **LED**: PC13 (built-in)

## Software

- **Toolchain**: `arm-none-eabi-gcc` (GNU Arm Embedded Toolchain)
- **RTOS**: FreeRTOS v10+/v11+
- **HAL**: STM32F4xx Hardware Abstraction Layer
- **Config**: Custom `FreeRTOSConfig.h` optimized for 168 MHz / 1 kHz tick

## Quick Start

```bash
# 1. Clone the repository
git clone git@github.com:many-stnega/mg_embedded_blink_rtos_stm32f4.git
cd mg_embedded_blink_rtos_stm32f4

# 2. Build the firmware
make clean && make
# Output: blink_rtos_f4.elf, blink_rtos_f4.hex

# 3. Flash to STM32F407
# Using st-flash (ST-Link):
st-flash write blink_rtos_f4.hex 0x8000000

# Or via OpenOCD, dfu-util, your IDE, etc.
```

## Expected Result

The LED on PC13 should toggle **every 500 ms**, driven by the FreeRTOS task `vTaskBlinky` running at priority 1.

## Repository Structure

```text
mg_embedded_blink_rtos_stm32f4/
├── .gitignore          # Build artifacts, IDE files
├── Makefile            # GCC build system
├── Core/
│   ├── Inc/main.h      # Header: prototypes, LED defines
│   └── Src/main.c      # Application: FreeRTOS blink + SystemClock_Config
├── Drivers/
│   ├── CMSIS/          # Core header + device header
│   └── STM32F4xx_HAL_Driver/  # HAL source & headers
└── Middlewares/
    └── RTOS/
        └── FreeRTOS/
            └── Source/
                └── include/
                    └── FreeRTOSConfig.h  # FreeRTOS settings
```

## Mermaid Architecture Diagram

```mermaid
flowchart TD
    HCLK[HCLK: 168 MHz] --> SCHED[Scheduler]
    PCLK1[APB1: 42 MHz] --> SCHED
    PCLK2[APB2: 84 MHz] --> SCHED
    TICK[SysTick / 1 kHz tick] --> TASK[vTaskBlinky]
    TASK --> LED[PC13: LED]
    MAIN[main()] --> CLK[SystemClock]
    CLK --> HCLK
```

## Build Configuration

### `FreeRTOSConfig.h` Key Settings

| Setting | Value | Description |
|---------|-------|-------------|
| `configCPU_CLOCK_HZ` | `168000000ULL` | HCLK frequency |
| `configTICK_RATE_HZ` | `1000` | Tick = 1 ms (SysTick) |
| `configMAX_PRIORITIES` | `5` | Number of priority levels |
| `configTOTAL_HEAP_SIZE` | `128 * 1024` | 128 KB heap |
| `configUSE_PREEMPTION` | `1` | Pre-emptive scheduling |
| `configUSE_TIME_SLICING` | `1` | Time slice rotation |

### `Makefile` Key Flags

```make
CFLAGS = -mcpu=cortex-m4 \
         -mfpu=fpv4-sp-d16 \
         -mfloat-abi=hard \
         -std=gnu11 \
         -Og -g -Wall -Wextra
LDFLAGS = -Tstm32f407.ld \
          -Specs=nosys.specs \
          -Wl,-gc-sections
```

## License

MIT License — free for personal and commercial use.