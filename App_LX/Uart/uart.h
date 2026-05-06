/*
 * uart.h
 *
 */

#ifndef UART_H_
#define UART_H_

void Uart1_Printf(char* fmt,...);
// void Uart2_Printf(char* fmt,...);

#define UART_LOG_ENABLED         1

#if (UART_LOG_ENABLED == 1)
   #define LOG_PRINT             Uart1_Printf
#else
   #define LOG_PRINT
#endif

#endif /* UART_H_ */
