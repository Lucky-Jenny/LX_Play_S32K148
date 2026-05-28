/**
  ******************************************************************************
  * @file    Flash_FlexRAM.h
  * @brief   通过FlexRAM模拟EEPROM实现数据读写的驱动头文件
  * @details 利用芯片内部 FlexRAM + FlexNVM 实现 EEPROM 模拟功能，
  *           支持任意字节读写、掉电数据保持、自动磨损均衡。
  * @author  Shawn.Liu
  * @date    2026-05-27
  * @version V1.0
  ******************************************************************************
  */

#ifndef FLASH_FLEXRAM_H_
#define FLASH_FLEXRAM_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Included Files
 ******************************************************************************/
#include "Cpu.h"
#include <stdio.h>
#include <stdint.h>
/*******************************************************************************
 * Macro Definitions
 ******************************************************************************/
#define FLASH_FLEXRAM_HAS_DEBUG         (0U)
/*******************************************************************************
 * Type Definitions
 ******************************************************************************/

/*******************************************************************************
 * Extern Global Variables
 ******************************************************************************/

/*******************************************************************************
 * Public Function Prototypes
 ******************************************************************************/
#if FEATURE_FLS_HAS_FLEX_NVM
void Flash_FlexRAM_Init(void);
uint8_t Flash_FlexRAM_WriteData(uint8_t *data, uint32_t offset, uint32_t size);
void Flash_FlexRAM_ReadData(uint8_t *destAddr, uint32_t offset, uint32_t size);
#endif /* End of FEATURE_FLS_HAS_FLEX_NVM */


#ifdef __cplusplus
}
#endif

#endif /* FLASH_FLEXRAM_H_ */
