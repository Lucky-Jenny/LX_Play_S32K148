/**
  ******************************************************************************
  * @file    uart.c
  * @brief   Implementation of UART abstraction layer.
  * @details This file implements the UART abstraction layer APIs.
  *          It encapsulates the underlying LPUART driver (S32K LPUART)
  *          and provides  commmon interfaces for the application layer.
  * @author  Shawn.Liu
  * @date    2026-06-03
  * @version V1.0
  ******************************************************************************
  */

/*******************************************************************************
 * Included Files
 ******************************************************************************/
#include "uart.h"
/*******************************************************************************
 * Internal Macro Definitions
 ******************************************************************************/

/*******************************************************************************
 * Internal Type Definitions
 ******************************************************************************/

/*******************************************************************************
 * Global Variables Definition
 ******************************************************************************/

/*******************************************************************************
 * Static Local Variables
 ******************************************************************************/
static uint8_t Uart1_Rx_Buffer[UART_RX_MAX_LEN];
/*******************************************************************************
 * Static Internal Function Declarations
 ******************************************************************************/
/*!
 * @brief       UART Rx callback function, triggered only if data is fully received.
 * @details     This callback only supports fixed-length reception mode; 
 *              It can't support variable-length frame.
 *
 * @param[in]   driverState: Pointer to LPUART driver internal state handle (Unused)
 * @param[in]   event: UART event flag, including RX_FULL, END_TRANSFER...
 * @param[in]   userData: User private parameter pointer passed in (Unused)
 * @param[out]  void
 */
static void LX_RxCallback(void *driverState, uart_event_t event, void *userData)
{
    (void)driverState;
    (void)userData;

    if (event == UART_EVENT_RX_FULL) 
    {
        // Handle received data.
    }
    else if (event == UART_EVENT_END_TRANSFER) 
    {
        /* Re-Start receving channel. */
        LPUART_DRV_ReceiveData(INST_LPUART1, Uart1_Rx_Buffer, UART_RX_MAX_LEN);
    }
}

/*******************************************************************************
 * Public Function Implementation
 ******************************************************************************/

/*!
 * @brief Initialize LPUART Drivers according to requirements.
 *
 * @param[in]   void
 * @param[out]  void
 */
void UART_Init(void)
{
    /* Init for UART1 */
    LPUART_DRV_Init(INST_LPUART1, &lpuart1_State, &lpuart1_InitConfig0);
    LPUART_DRV_InstallRxCallback(INST_LPUART1, LX_RxCallback, NULL);
    /* Enable Channel to receive data. */
    LPUART_DRV_ReceiveData(INST_LPUART1, Uart1_Rx_Buffer, UART_RX_MAX_LEN);
}

