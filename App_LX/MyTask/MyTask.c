/* Standard includes. */
#include <stdlib.h>
#include <string.h>
/* User includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "Cpu.h"
#include "log.h"
#include "key.h"
#include "delay.h"
#include "led.h"
#include "oled.h"
#include "MyTask.h"
#include "timer.h"
#include "Flash_FlexRAM.h"


#define WRITE_LEN       8U
uint8_t testWrite[WRITE_LEN] = {0x1U, 0x2U, 0x3U, 0x4U, 0x5U, 0x6U, 0x7U, 0x8U};
uint8_t testRead[WRITE_LEN];
uint8_t wr_flag = 0;
uint8_t wr_result;

/*!
 * @brief Some Initial Actions shall be after the start of FreeRTOS Scheduler.
 *
 * @param[in] pvParameters input param, default is NULL.
 */
static void MyTask_Init(void *pvParameters)
{
    (void)pvParameters;

    /* 
    * OLED initialization must be performed after the FreeRTOS scheduler has started.
    * I2C_PAL APIs rely on FreeRTOS primitives (semaphores), which are only available after vTaskStartScheduler().
    */
    OLED_Init();

    LOG_PRINT_INFO("Initialization Complete. MCU Freq: %dMhz.", Delay_GetMcuFreq());

    Flash_FlexRAM_ReadData(&wr_flag, 6, 1);
    LOG_PRINT_DBG("write_flag = %d.", wr_flag);
    Flash_FlexRAM_ReadData(testRead, 16, WRITE_LEN);
    LOG_PRINT_INFO("testRead:");
    LOG_PRINT_HEX_ARRAY(testRead, WRITE_LEN);


    /* Delete this Task. */
    vTaskDelete(NULL);
}

static void MyTask_10ms(void *pvParameters)
{
    (void)pvParameters;
    while(1)
    {
        OLED_write_number(10, 12, Timer_Get_Counter(), 16, 0);
        if(Key_Is_Pressed(KEY_1_INDEX))
        {
            LED_Set_Light(LED_PORT_YELLOW, LED_LIGHT_ON);
            if((wr_flag == 0x2u) || (wr_flag == 0xFFu))
            {
                wr_flag = 1U;
                wr_result = Flash_FlexRAM_WriteData(testWrite, 16, WRITE_LEN);
                LOG_PRINT_INFO("Write buffer Result: %d.", wr_result);
                wr_result = Flash_FlexRAM_WriteData(&wr_flag, 6, 1);
                LOG_PRINT_INFO("Write flag Result: %d.", wr_result);
            }
        }
        else
        {
            LED_Set_Light(LED_PORT_YELLOW, LED_LIGHT_OFF);
        }
        vTaskDelay(MTASK_DELAY_10_MS);
    }
}

static void MyTask_50ms(void *pvParameters)
{
    (void)pvParameters;
    while(1)
    {
        if(Key_Is_Pressed(KEY_2_INDEX))
        {
            LED_Set_Light(LED_PORT_RED, LED_LIGHT_ON);
            if(wr_flag == 0x1u)
            {
                wr_flag = 2U;
                wr_result = Flash_FlexRAM_WriteData(&wr_flag, 6, 1);
                LOG_PRINT_INFO("Write flag Result: %d.", wr_result);

            }
        }
        else
        {
            LED_Set_Light(LED_PORT_RED, LED_LIGHT_OFF);
        }
        vTaskDelay(MTASK_DELAY_50_MS);
    }
}

static void MyTask_100ms(void *pvParameters)
{
    (void)pvParameters;
    while(1)
    {
        if(Key_Is_Pressed(KEY_3_INDEX))
        {
            LED_Set_Light(LED_PORT_GREEN, LED_LIGHT_ON);
        }
        else
        {
            LED_Set_Light(LED_PORT_GREEN, LED_LIGHT_OFF);
        }
        vTaskDelay(MTASK_DELAY_100_MS);
    }
}

static void MyTask_500ms(void *pvParameters)
{
    (void)pvParameters;
    while(1)
    {
        if(Key_Is_Pressed(KEY_4_INDEX))
        {
            LED_Set_Light(LED_PORT_BLUE, LED_LIGHT_ON);
        }
        else
        {
            LED_Set_Light(LED_PORT_BLUE, LED_LIGHT_OFF);
        }
        vTaskDelay(MTASK_DELAY_500_MS);
    }
}

void MyTask_Initial_Task(void)
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
    xTaskCreate(MyTask_Init,    "Init_Task",    MTASK_STACK_1K ,  NULL,   20, NULL);
    xTaskCreate(MyTask_10ms,    "10ms_Task",    MTASK_STACK_2K ,  NULL,   16, NULL);
    xTaskCreate(MyTask_50ms,    "50ms_Task",    MTASK_STACK_1K ,  NULL,   14, NULL);
    xTaskCreate(MyTask_100ms,   "100ms_Task",   MTASK_STACK_2K ,  NULL,   12, NULL);
    xTaskCreate(MyTask_500ms,   "500ms_Task",   MTASK_STACK_1K ,  NULL,   10, NULL);
}


void MyTask_Start_Scheduler(void)
{
    vTaskStartScheduler();
}




