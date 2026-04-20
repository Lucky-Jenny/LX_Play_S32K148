/* Standard includes. */
#include <stdlib.h>
#include <string.h>
/* User includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "Cpu.h"
#include "uart.h"
#include "MyTask.h"


static void MyTask_10ms(void *pvParameters)
{
    (void)pvParameters;
    while(1)
    {
        //PINS_DRV_TogglePins(PTE, 1 << 23);
        vTaskDelay(MTASK_DELAY_10_MS);
    }
}

static void MyTask_50ms(void *pvParameters)
{
    (void)pvParameters;
    while(1)
    {
        //PINS_DRV_TogglePins(PTE, 1 << 22);
        vTaskDelay(MTASK_DELAY_50_MS);
    }
}

static void MyTask_100ms(void *pvParameters)
{
    (void)pvParameters;
    while(1)
    {
        //PINS_DRV_TogglePins(PTE, 1 << 21);
        vTaskDelay(MTASK_DELAY_100_MS);
    }
}

static void MyTask_500ms(void *pvParameters)
{
    (void)pvParameters;
    while(1)
    {
        PINS_DRV_TogglePins(PTE, 1 << 20);
        u1_printf("MyTask_500ms is runnig.\r\n");
        vTaskDelay(MTASK_DELAY_500_MS);
    }
}

static void MyTask_CreateTasks(void)
{
    /* 
     * BaseType_t xTaskCreate(
     *    TaskFunction_t pvTaskCode,            // 任务函数指针
     *    const char *pcName,                   // 任务名字（调试用）
     *    configSTACK_DEPTH_TYPE usStackDepth,  // 栈大小（字）
     *    void *pvParameters,                   // 传递给任务的参数
     *    UBaseType_t uxPriority,               // 任务优先级
     *    TaskHandle_t *pvCreatedTask           // 任务句柄（输出）
     * );
     */
    xTaskCreate(MyTask_10ms,    "10ms_Task",    MTASK_STACK_2K ,  NULL,   16, NULL);
    xTaskCreate(MyTask_50ms,    "50ms_Task",    MTASK_STACK_1K ,  NULL,   14, NULL);
    xTaskCreate(MyTask_100ms,   "100ms_Task",   MTASK_STACK_2K ,  NULL,   12, NULL);
    xTaskCreate(MyTask_500ms,   "500ms_Task",   MTASK_STACK_1K ,  NULL,   10, NULL);
}


void MyTask_Start_Schedule(void)
{
    MyTask_CreateTasks();
    vTaskStartScheduler();
}




