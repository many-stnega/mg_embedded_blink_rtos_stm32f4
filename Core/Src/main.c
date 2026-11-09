/* ------------------------------------------------------------
   Blinky with FreeRTOS on STM32F407
   Target: STM32F407ZGT6 (168 MHz HCLK)
   LED: PC13 (builtin on Discovery/ Nucleo boards)
   ------------------------------------------------------------ */

#include "main.h"
#include "cmsis_os2.h"
#include "stm32f4xx_hal.h"

/* Task prototype */
void vTaskBlinky(void *argument);

/* LED pin definition (PC13) */
#define LED_GPIO_PORT  GPIOC
#define LED_GPIO_PIN   GPIO_PIN_13

/* FreeRTOS task handle */
TaskHandle_t xBlinkyTaskHandle = NULL;

/* ------------------------------------------------------------
   main - entry point
   ------------------------------------------------------------ */

int main(void) {
    HAL_Init();
    SystemClock_Config();  /* Configure 168 MHz HCLK */

    /* Initialize LED GPIO */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = LED_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);

    /* Create FreeRTOS task */
    xTaskCreate(
        vTaskBlinky,       /* Task function */
        "Blinky",          /* Task name */
        128,               /* Stack size (words) */
        NULL,              /* Parameter */
        1,                 /* Priority (1 = lowest configured) */
        &xBlinkyTaskHandle /* Task handle */
    );

    /* Start scheduler */
    vTaskStartScheduler();

    /* Should never reach here */
    for (;;);
}

/* ------------------------------------------------------------
   vTaskBlinky - toggles LED every 500 ms
   ------------------------------------------------------------ */

void vTaskBlinky(void *argument) {
    (void)argument;

    for (;;) {
        HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_GPIO_PIN);
        vTaskDelay(pdMS_TO_TICKS(500)); /* 500 ms block */
    }
}

/* ------------------------------------------------------------
   SystemClock_Config - standard STM32F407 168 MHz config
   ------------------------------------------------------------ */

void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /* Enable HSE Oscillator and activate PLL with HSE as source */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 8;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 7;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    /* Select PLL as system clock source and configure HCLK and PCLK clocks */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  /* APB1 = 42 MHz */
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  /* APB2 = 84 MHz */
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
}