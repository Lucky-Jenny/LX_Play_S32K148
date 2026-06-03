/**
 * @file     Global_Cfg.h
 * @brief    Global configuration header file
 * @details  This file provides universal macro definitions, global includes,
 *           and common configuration options for the entire project.
 *           It centralizes shared definitions to ensure consistency
 *           and simplify maintenance across all modules.
 * @author   Shawn.Liu
 * @date     2026-06-03
 * @version  V1.0
 */

#ifndef GLOBAL_CFG_H_
#define GLOBAL_CFG_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Included Files
 ******************************************************************************/
/* ----- SDK Inclusions ----- */
#include "Cpu.h"
#include "FreeRTOS.h"
#include "task.h"
#include "oled.h"
#include "delay.h"
/* ----- User Inclusions ----- */
#include "led.h"
#include "key.h"
#include "log.h"
#include "MyTask.h"
#include "timer.h"
#include "uart.h"
#include "Flash_FlexRAM.h"
/*******************************************************************************
 * Macro Definitions
 ******************************************************************************/

/*******************************************************************************
 * Type Definitions
 ******************************************************************************/

/*******************************************************************************
 * Extern Global Variables
 ******************************************************************************/

/*******************************************************************************
 * Public Function Prototypes
 ******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* GLOBAL_CFG_H_ */