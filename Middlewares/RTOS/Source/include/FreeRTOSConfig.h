#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include <stdint.h>

/* ------------------------------------------------------------
   FreeRTOS Configuration for STM32F407
   ------------------------------------------------------------ */

/* RTOS Kernel Settings */
#define configUSE_PREEMPTION         1
#define configUSE_TIME_SLICING       1
#define configTICK_SOURCE            TICKSOURCE_SYSTICK

/* STM32F407 specific: HCLK = 168 MHz, SysTick config */
#define configCPU_CLOCK_HZ           (168000000ULL)
#define configTICK_RATE_HZ           (1000)    /* 1 kHz tick = 1 ms */
#define configMAX_PRIORITIES       (5)

/* Memory allocation (simple BMP style) */
#define configSUPPORT_STATIC_ALLOCATION    1
#define configSUPPORT_DYNAMIC_ALLOCATION   1
#define configTOTAL_HEAP_SIZE              ((size_t)(128 * 1024)) /* 128 KB heap */

/* Run time and stats gathering (optional) */
#define configUSE_TRACE_FACILITY           0
#define configUSE_STATS_FORMATTING         0
#define configGENERATE_RUN_TIME_STATS      0

/* Co-routine / SMP settings (not used here) */
#define configUSE_CO_ROUTINES              0
#define configMAX_CO_ROUTINE_PRIORITIES    (2)

/* Hook functions (optional) */
#define configUSE_IDLE_HOOK                0
#define configUSE_TICK_HOOK                0
#define configCHECK_FOR_STACK_OVERFLOW     0
#define configUSE_MUTEXES                  1
#define configUSE_RECURSIVE_MUTEXES        1
#define configUSE_COUNTING_SEMAPHORES      1
#define configQUEUE_REGISTRY_SIZE          8

/* Assertion configuration */
void vAssertCalled(unsigned long ulLine, const char *pcFile);
#define configAssertDefined()             vAssertCalled(__LINE__, __FILE__)
#define configASSERT(x)                   if ((x) == 0) { taskDISABLE_INTERRUPTS(); for(;;); }

#endif /* FREERTOS_CONFIG_H */