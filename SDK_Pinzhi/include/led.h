/*
 * led.h
 *
 */

#ifndef LED_H_
#define LED_H_

#include "Cpu.h"
#include <stdio.h>
#include <stdint.h>


/* Configurations for S32K148 */
#define LED_WRITE_PORT_BASE         PTE
#define LED_PORT_YELLOW             (uint8_t)(20U)
#define LED_PORT_RED                (uint8_t)(21U)
#define LED_PORT_GREEN              (uint8_t)(22U)
#define LED_PORT_BLUE               (uint8_t)(23U)

#define LED_LIGHT_OFF               (uint8_t)(0x01U)
#define LED_LIGHT_ON                (uint8_t)(0x00U)


/* Functions Declaration */
void LED_Set_Light(uint8_t led_port, uint8_t led_status);

#endif /* LED_H_ */
