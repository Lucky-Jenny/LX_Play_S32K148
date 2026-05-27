/**
  ******************************************************************************
  * @file    log.h
  * @brief   This file contains declarations and macros of log.
  * @details The protocol to print log in this file is UART.
  * @author  Shawn.Liu
  * @date    2026-04-23
  * @version V1.0
  ******************************************************************************
  */

#ifndef LOG_H_
#define LOG_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Included Files
 ******************************************************************************/
#include <stdio.h>
#include <string.h>
#include "stdarg.h"
#include <stdint.h>
#include <stdbool.h>
#include"Cpu.h"
/*******************************************************************************
 * Macro Definitions
 ******************************************************************************/
/* Switch to On / Off LOG Print. */
#define LOG_IS_ENABLED          (1U)
/* Maximum size of Log Buffer. */
#define LOG_MAX_SIZE            (256U)
/* Device Instance number of UART. */
#define LOG_INST_UART           INST_LPUART1
/* ---------------------------------------- */

/* Ignore related Path. Only print Filename. */
#define __FILENAME__       (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#if LOG_IS_ENABLED
  /* Print Normal information log. */
  #define LOG_PRINT_INFO(fmt, ...)          LOG_Print(fmt "\r\n", ##__VA_ARGS__)
  /* Print debug log with prefix info as below:
   *  <fileName : lineNumber> [functionName] XXXXX
   */
  #define LOG_PRINT_DBG(fmt, ...) \
    LOG_Print("<%s:%d> [%s] " fmt "\r\n", __FILENAME__, __LINE__, __func__, ##__VA_ARGS__)
  /* Print single Byte in HEX format. */
  #define LOG_PRINT_HEX             LOG_Print_Hex
  /* Print Array in HEX format with specified length. */
  #define LOG_PRINT_HEX_ARRAY       LOG_Print_Array
#else  /* LOG_IS_ENABLED == 0*/
  #define LOG_PRINT_INFO
  #define LOG_PRINT_DBG
  #define LOG_PRINT_HEX
  #define LOG_PRINT_HEX_ARRAY
#endif /* End of LOG_IS_ENABLED */
/*******************************************************************************
 * Type Definitions
 ******************************************************************************/

/*******************************************************************************
 * Extern Global Variables
 ******************************************************************************/

/*******************************************************************************
 * Public Function Prototypes
 ******************************************************************************/
void LOG_Print(char *fmt, ...);
void LOG_Print_Hex(uint8_t dataByte);
void LOG_Print_Array(uint8_t *srcAddress, uint32_t plen);

#ifdef __cplusplus
}
#endif

#endif /* LOG_H_ */
