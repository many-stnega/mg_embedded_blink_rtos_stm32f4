#ifndef MAIN_H
#define MAIN_H

#include "stm32f4xx_hal.h"
#include "cmsis_os2.h"

/* LED pin definition (PC13) */
#define LED_GPIO_PORT  GPIOC
#define LED_GPIO_PIN   GPIO_PIN_13

/* FreeRTOS task handle */
extern TaskHandle_t xBlinkyTaskHandle;

/* Function prototypes */
void SystemClock_Config(void);
void vTaskBlinky(void *argument);

#endif /* MAIN_H */