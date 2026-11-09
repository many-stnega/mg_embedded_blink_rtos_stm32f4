# ------------------------------------------------------------
# Makefile for STM32F407 FreeRTOS Blink
# Target: mg_embedded_blink_rtos_stm32f4
# ------------------------------------------------------------

# Project name
PROJECT = blink_rtos_f4

# Compiler
CC = arm-none-eabi-gcc

# Source files
SRCS = Core/Src/main.c \
       Middlewares/RTOS/Source/list.c \
       Middlewares/RTOS/Source/queue.c \
       Middlewares/RTOS/Source/tasks.c \
       Middlewares/RTOS/Source/timers.c

# Include paths (adjust to your STM32 install)
INC_DIRS = -ICore/Inc \
           -IDrivers/CMSIS/Include \
           -IDrivers/CMSIS/Device/ST/STM32F4xx/Include \
           -IDrivers/STM32F4xx_HAL_Driver/Inc \
           -IMiddlewares/RTOS/Source/include \
           -IMiddlewares/RTOS/Source/CMSIS_RTOS_V2

# Compiler flags
CFLAGS = -mcpu=cortex-m4 \
         -mfpu=fpv4-sp-d16 \
         -mfloat-abi=hard \
         -std=gnu11 \
         -Og -g -Wall -Wextra \
         -ffunction-sections -fdata-sections \
         -MMD -MP \
         $(INC_DIRS)

# Linker flags
LDFLAGS = -Tstm32f407.ld \
          -nostartfiles \
          -mcpu=cortex-m4 \
          -mfpu=fpv4-sp-d16 \
          -mfloat-abi=hard \
          -Specs=nosys.specs \
          -Wl,-gc-sections \
          -Map=$(PROJECT).map

# Output binary
OUTPUT = $(PROJECT).elf
HEX = $(PROJECT).hex

all: $(OUTPUT) $(HEX)

$(OUTPUT): $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(HEX): $(OUTPUT)
	arm-none-eabi-objcopy -O ihex $< $@

clean:
	rm -f $(OUTPUT) $(HEX) $(PROJECT).map *.d

deploy: $(HEX)
	@echo "Deploy $(HEX) to your STM32F407"

flash: deploy

.PHONY: all clean deploy flash