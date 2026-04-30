/* Standard includes. */
#include <stdlib.h>
#include <string.h>
/* User includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "Cpu.h"
#include "uart.h"
#include "key.h"
#include "led.h"
#include "oled.h"
#include "MyTask.h"



/*!
 * @brief Some Initial Actions shall be after the start of FreeRTOS Scheduler.
 *
 * @param[in] pvParameters input param, default is NULL.
 */
static void MyTask_Init(void *pvParameters)
{
    (void)pvParameters;

    /* I2C */
    I2C_MasterInit(&i2c1_instance, &i2c1_MasterConfig0);
    INT_SYS_SetPriority(LPI2C1_Master_IRQn, 5U);
    /* OLED */
    OLED_Init();

    LOG_PRINT("Initialization Complete. MCU Freq: %dMhz\r\n", Delay_GetMcuFreq());
    OLED_TITLE((uint8_t*)"S32K148",(uint8_t*)"05_FTM");

    /* Delete this Task. */
    vTaskDelete(NULL);
}

static void MyTask_10ms(void *pvParameters)
{
    (void)pvParameters;
    //OLED_Init();
    while(1)
    {
        OLED_ShowString(0,0,"HELLO OLED", 11, 0);
        //OLED_ShowString(8,2,(uint8_t*)"counterTmr0:",8,0);
        if(Key_Is_Pressed(KEY_1_INDEX))
        {
            LED_Set_Light(LED_PORT_YELLOW, LED_LIGHT_ON);
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

void MyTask_Inital_Task(void)
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




