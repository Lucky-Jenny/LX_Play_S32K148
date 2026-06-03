/**
  ******************************************************************************
  * @file    uart.h
  * @brief   UART abstraction layer for application / LPUART driver separation
  * @details This module provides abstract UART interfaces.
  *          It isolates the upper application layer from the LPUART driver.
  * @author  Shawn.Liu
  * @date    2026-06-03
  * @version V1.0
  ******************************************************************************
  */

#ifndef UART_H_
#define UART_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Included Files
 ******************************************************************************/
#include <stdio.h>
#include"Cpu.h"
/*******************************************************************************
 * Macro Definitions
 ******************************************************************************/
#define UART_RX_MAX_LEN                 ((uint8_t)128U)
#define UART_FLG_RX_NOT_RECEIVED        ((uint8_t)0U)
#define UART_FLG_RX_RECEIVED            ((uint8_t)1U)
/*******************************************************************************
 * Type Definitions
 ******************************************************************************/

/*******************************************************************************
 * Extern Global Variables
 ******************************************************************************/

/*******************************************************************************
 * Public Function Prototypes
 ******************************************************************************/
void UART_Init(void);
void UART_Rx_Data_Handler(uint32_t instance);
void UART_MainFunction(void);

#ifdef __cplusplus
}
#endif

#endif /* UART_H_ */
