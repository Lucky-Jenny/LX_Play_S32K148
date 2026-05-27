/**
  ******************************************************************************
  * @file    log.c
  * @brief   This file contains definitions of log print.
  * @details The protocol to print log in this file is UART.
  * @author  Shawn.Liu
  * @date    2026-04-23
  * @version V1.0
  ******************************************************************************
  */

/*******************************************************************************
 * Included Files
 ******************************************************************************/
#include"log.h"
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
static char LOG_Buffer[LOG_MAX_SIZE];
/*******************************************************************************
 * Static Internal Function Declarations
 ******************************************************************************/

/*******************************************************************************
 * Public Function Implementation
 ******************************************************************************/

/*!
 * @brief Print information log by UART.
 *
 * @param[in] fmt: string format.
 */
void LOG_Print(char *fmt, ...)
{
    uint32_t bytesRemain;
    va_list ap;

    va_start(ap,fmt);
    vsprintf(LOG_Buffer, fmt, ap);
    va_end(ap);

    /* Send log by UART. */
    LPUART_DRV_SendData(LOG_INST_UART, (uint8_t *)LOG_Buffer, (uint32_t)strlen(LOG_Buffer));
    while (LPUART_DRV_GetTransmitStatus(LOG_INST_UART, &bytesRemain) != STATUS_SUCCESS)
    {
        /* Do Nothing. */
    }
}

/*!
 * @brief Print single Byte in HEX format. 
 *
 * @param[in] dataByte: single byte.
 */
void LOG_Print_Hex(uint8_t dataByte)
{
    LOG_Print("%02hhX ", dataByte);
}

/*!
 * @brief Print Array in HEX format with specified length.
 *
 * @param[in] srcAddress: source address of array.
 * @param[in] printLen: specified byte length to be printed.
 *                      !!! Overflow Caution !!!
 */
void LOG_Print_Array(uint8_t *srcAddress, uint32_t plen)
{
    uint8_t idx = 0;

    for(; idx < (uint8_t)plen; idx++)
    {
        LOG_Print("0x%02X ", ((uint8_t*)srcAddress)[idx]);
        /* Print 16 bytes each line. */
        if(((idx+1) % 16) == 0)
        {
            LOG_Print("\r\n");
        }
    }
    LOG_Print("\r\n");
}

