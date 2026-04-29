/*
 * delay.h
 *
 *  Created on: 2020Äê11ÔÂ18ÈÕ
 *      Author: Administrator
 */

#ifndef DELAY_H_
#define DELAY_H_


#define DL_MHZ          1000000U

void delay_ms(uint32_t nms);
void delay_us(uint32_t nus);
void Delay_Init(void);
uint32_t Delay_GetMcuFreq(void);

#endif /* DELAY_H_ */
