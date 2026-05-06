/*
 * 灯光函数
 */
#include <stdint.h>
#include "cpu.h"
#include "led.h"
#include "uart.h"


/*!
 * @brief Set LED light according to port index.
 *
 * @param[in] led_port port index of led
 * @param[in] led_status light status (light on / off)
 */
void LED_Set_Light(uint8_t led_port, uint8_t led_status)
{
    if((led_port == LED_PORT_YELLOW)
    || (led_port == LED_PORT_RED)
    || (led_port == LED_PORT_GREEN)
    || (led_port == LED_PORT_BLUE))
    {
        PINS_DRV_WritePin(LED_WRITE_PORT_BASE, led_port, led_status);
    }
    else
    {
        LOG_PRINT("[LED_Set_Light] led_port is invalid!\n");
    }
}
