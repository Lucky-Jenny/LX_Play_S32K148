/*
 * °´¼üº¯Êý
 */
#include <stdint.h>
#include"Cpu.h"
#include"key.h"

static const Key_Config_t Key_Config_Table[KEY_TOTAL_NUM] = 
{
    /*   index         port        port Base */
    {KEY_1_INDEX,   KEY_1_PORT,     PTC},
    {KEY_2_INDEX,   KEY_2_PORT,     PTC},
    {KEY_3_INDEX,   KEY_3_PORT,     PTC},
    {KEY_4_INDEX,   KEY_4_PORT,     PTC},
    {KEY_5_INDEX,   KEY_5_PORT,     PTC}
};

/*!
 * @brief Check whether Key is Presed or not.
 *
 * @param[in] key_index Key Index (Key 1, Key 2, Key 3, etc.)
 * @return Key Pressed Status. The rule is as follows:
 *      - 0x00 : corresponding key is not pressed.
 *      - 0x01 : corresponding key is pressed.
 *      - 0xFF : input key index is invalid.
 */
uint8_t Key_Is_Pressed(uint8_t key_index)
{
    uint8_t index_table = 0;
    uint8_t input_keyStatus = 0;
    uint8_t ret_keyValue = KEY_IS_INVALID;

    for(index_table; index_table < KEY_TOTAL_NUM; index_table++)
    {
        if(key_index == Key_Config_Table[index_table].key_index)
        {
            input_keyStatus = ((PINS_DRV_ReadPins(Key_Config_Table[index_table].key_portBase) \
                              >> Key_Config_Table[index_table].key_port) & 0x01U);

            if(input_keyStatus == 0x01U)
            {
                ret_keyValue = KEY_IS_PRESSED;
            }
            else
            {
                ret_keyValue = KEY_IS_NOT_PRESSED;
            }
        }
    }

    return ret_keyValue;
}
