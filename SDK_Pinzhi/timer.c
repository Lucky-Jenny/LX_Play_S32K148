/*
 * 定时器模块
 */
#include "timer.h"
#include "oled.h"


static uint16_t counter_tmr0 = 0;

/* 定时器中断函数
 * FTM周期中断计算公式:
 * 重装载值  /(主频/分频) 单位:秒
 *
 * 例如设置100ms的中断周期:
 * - 重装载值: finalValue = 37500
 * -   分频: ftmPrescaler = 128
 * 
 * 37500(重载值)/(48000000hz(主频)/128(分频)) = 1/10秒 = 100ms
 */
void Timer0_ISR_100ms(void)
{
    counter_tmr0++;
    // OLED_write_number(8, 12, counter_tmr0, 8, 0);

    /* Clear Flag of FTM */
    FTM_DRV_ClearStatusFlags(INST_FLEXTIMER_MC1, (uint32_t)FTM_TIME_OVER_FLOW_FLAG);
}

/*!
 * @brief Initialize Timer based on FlexTimer(NXP).
 */
void Timer_Init(void)
{
    ftm_state_t ftmState;

    /* Initial FTM */
    FTM_DRV_Init(INST_FLEXTIMER_MC1, &flexTimer_mc1_InitConfig, &ftmState);
    /* Config Interrupt: Overflow and Reload */
    INT_SYS_InstallHandler(FTM0_Ovf_Reload_IRQn, &Timer0_ISR_100ms, (isr_t*) 0U);
    INT_SYS_EnableIRQ(FTM0_Ovf_Reload_IRQn);
    /* Initial Timer */
    FTM_DRV_InitCounter(INST_FLEXTIMER_MC1, &flexTimer_mc1_TimerConfig);
    /* Start Timer */
    FTM_DRV_CounterStart(INST_FLEXTIMER_MC1);

    //OLED_ShowString(8,2,(uint8_t*)"counterTmr0:",8,0);
}
