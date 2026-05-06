/*
 * timer.h
 *
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <stdio.h>
#include <stdint.h>
#include "Cpu.h"


/* Macros Definition */

/* Functions Declaration */
uint16_t Timer_Get_Counter(void);
void Timer_Init(void);

#endif /* TIMER_H_ */
