/*
 * key.h
 *
 */

#ifndef KEY_H_
#define KEY_H_

#include "Cpu.h"
#include <stdio.h>
#include <stdint.h>


/*!
 * @brief Enum of Key index.
 */
typedef enum
{
    KEY_1_INDEX = 0x0U,
    KEY_2_INDEX,
    KEY_3_INDEX,
    KEY_4_INDEX,
    KEY_5_INDEX,
    KEY_INDEX_MAX,
} E_KEY_INDEX;

typedef struct
{
    E_KEY_INDEX     key_index;
    uint8_t         key_port;
    GPIO_Type*      key_portBase;
}Key_Config_t;


/* Configurations for S32K148 */
#define KEY_READ_PORT_BASE          PINS_DRV_ReadPins(PTC)

#define KEY_1_PORT                  (uint8_t)(12U)
#define KEY_2_PORT                  (uint8_t)(13U)
#define KEY_3_PORT                  (uint8_t)(14U)
#define KEY_4_PORT                  (uint8_t)(15U)
#define KEY_5_PORT                  (uint8_t)(19U)

#define KEY_IS_NOT_PRESSED          (uint8_t)(0x00U)
#define KEY_IS_PRESSED              (uint8_t)(0x01U)
#define KEY_IS_INVALID              (uint8_t)(0xFFU)


#define KEY_READ_STATUS(X)          ((KEY_READ_PORT_BASE >> (X)) & 0x01U)
#define KEY_TOTAL_NUM               (uint8_t)KEY_INDEX_MAX


/* Functions Declaration */
uint8_t Key_Is_Pressed(uint8_t k_idx);

#endif /* KEY_H_ */
