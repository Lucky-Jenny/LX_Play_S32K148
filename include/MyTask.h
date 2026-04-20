/*!
*
*   @file    MyTask.h
*
*   @brief   This head file contains declarations of My Tasks.
*
******************************************************************************/

#ifndef __MYTASK_H
#define __MYTASK_H


#include <stdint.h>
#include "FreeRTOS.h"


#define MTASK_DELAY_10_MS       (uint16_t)(10U)
#define MTASK_DELAY_50_MS       (uint16_t)(50U)
#define MTASK_DELAY_100_MS      (uint16_t)(100U)
#define MTASK_DELAY_500_MS      (uint16_t)(500U)

/* The unit of Stask Size is Word --> 4 bytes. */
#define MTASK_STACK_2K          (uint16_t)(512U)    /* 2k bytes */
#define MTASK_STACK_1K          (uint16_t)(256U)    /* 1k bytes */


void MyTask_Start_Schedule(void);

#endif /* __MYTASK_H */
