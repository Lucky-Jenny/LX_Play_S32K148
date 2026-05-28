/**
  ******************************************************************************
  * @file    Flash_FlexRAM.c
  * @brief   通过FlexRAM模拟EEPROM实现数据读写的驱动头文件
  * @details 利用芯片内部 FlexRAM + FlexNVM 实现 EEPROM 模拟功能，
  *           支持任意字节读写、掉电数据保持、自动磨损均衡。
  * @author  Shawn.Liu
  * @date    2026-05-27
  * @version V1.0
  ******************************************************************************
  */

/*******************************************************************************
 * Included Files
 ******************************************************************************/
#include <stdint.h>
#include "log.h"
#include "Flash_FlexRAM.h"
/*******************************************************************************
 * Internal Macro Definitions
 ******************************************************************************/
#if FLASH_FLEXRAM_HAS_DEBUG
  #define FLASH_LOG_DBG         LOG_PRINT_DBG
#else
  #define FLASH_LOG_DBG
#endif /* End of FLASH_FLEXRAM_HAS_DEBUG */
/*******************************************************************************
 * Internal Type Definitions
 ******************************************************************************/

/*******************************************************************************
 * Global Variables Definition
 ******************************************************************************/
// 系统参数
flash_ssd_config_t   flashSSDConfig;
/*******************************************************************************
 * Static Local Variables
 ******************************************************************************/
// flash操作的返回结果
static uint8_t  flashResult = 0;
// EEPROM基地址
static uint32_t EEPROM_BaseAddress = 0;
/*******************************************************************************
 * Static Internal Function Declarations
 ******************************************************************************/

/*******************************************************************************
 * Public Function Implementation
 ******************************************************************************/
#if FEATURE_FLS_HAS_FLEX_NVM
/**
 * @brief  Initialize FlexRAM Configurations.
 */
void Flash_FlexRAM_Init(void)
{
    /* Disable cache to ensure all flash operations will take effect instantly
    This is device dependent. */
    MSCM->OCMDR[0u] |= MSCM_OCMDR_OCM1(0x3u);
    MSCM->OCMDR[1u] |= MSCM_OCMDR_OCM1(0x3u);

    /* Initial Flash Driver by SDK */
    flashResult = FLASH_DRV_Init(&Flash1_InitConfig0, &flashSSDConfig);
    FLASH_LOG_DBG("FLASH_DRV_Init : %d", flashResult);

    /* Config flexRAMas EEPROM to save user datum. */
    if(flashSSDConfig.EEESize == 0u)
    {
        /*
        * Configure FlexRAM as EEPROM and FlexNVM as EEPROM backup region:
        * - FlexRAM -----> EEPROM
        * - FlexNVM -----> EEPROM Backup
        * DEFlashPartition will be failed if the IFR region isn't blank.
        * Refer to the device document for valid EEPROM Data Size Code
        * and FlexNVM Partition Code. For example on S32K148:
        * - EEEDataSizeCode = 0x02u: EEPROM size = 4 Kbytes
        * - DEPartitionCode = 0x04u: EEPROM backup size = 64 Kbytes
        * */
        flashResult = FLASH_DRV_DEFlashPartition(&flashSSDConfig, 0x02u, 0x04u, 0x0u, false, true);
        FLASH_LOG_DBG("DEFlashPartition : %d", flashResult);
        /* Re-initialize the driver to update the new EEPROM configuration */
        flashResult = FLASH_DRV_Init(&Flash1_InitConfig0, &flashSSDConfig);
        FLASH_LOG_DBG("FLASH_DRV_Init : %d", flashResult);
        /* Make FlexRAM available for EEPROM */
        flashResult = FLASH_DRV_SetFlexRamFunction(&flashSSDConfig, EEE_ENABLE, 0x00u, NULL);
        FLASH_LOG_DBG("SetFlexRamFunction : %d", flashResult);
    }
    else  /* FLexRAM is already configured as EEPROM */
    {
        /* Make FlexRAM available for EEPROM, make sure that FlexNVM and FlexRAM
        * are already partitioned successfully before */
        flashResult = FLASH_DRV_SetFlexRamFunction(&flashSSDConfig, EEE_ENABLE, 0x00u, NULL);
        FLASH_LOG_DBG("FLexRAM is already configured as EEPROM. SetFlexRamFunction : %d", flashResult);
    }
    EEPROM_BaseAddress = flashSSDConfig.EERAMBase;
}

/**
 * @brief  Write Data to Flash
 * @param  data: the source address of data.
 * @param  offset: the offset of EEPROM Base Address.
 * @param  size: the size of data to be written.
 * @retval flashResult:
 *      0 --> Write in Success.
 *      1 --> Write in Failed.
 * @note   The Unit of wirte size is Byte.
 */
uint8_t Flash_FlexRAM_WriteData(uint8_t *data, uint32_t offset, uint32_t size)
{
#if FLASH_FLEXRAM_HAS_DEBUG
    LOG_PRINT_HEX_ARRAY(data, size);
    flashResult = FLASH_DRV_EEEWrite(&flashSSDConfig, EEPROM_BaseAddress + offset, size, data);
    FLASH_LOG_DBG("FLASH_DRV_EEEWrite Result: %d", flashResult);
#else
    return FLASH_DRV_EEEWrite(&flashSSDConfig, EEPROM_BaseAddress + offset, size, data);
#endif /* End of FLASH_FLEXRAM_HAS_DEBUG */
}

/**
 * @brief  从EEPROM读数据
 * @param  destAddr: the destination address of read RAM.
 * @param  offset: the offset of EEPROM Base Address.
 * @param  size: the size of data to be read.
 * @retval void
 * @note   The Unit of wirte size is Byte.
 */
void Flash_FlexRAM_ReadData(uint8_t *destAddr, uint32_t offset, uint32_t size)
{
    uint32_t idx = 0;

    for(; idx < size; idx++)
    {
        destAddr[idx] = *((uint32_t *)(EEPROM_BaseAddress + offset + idx));
    }
#if FLASH_FLEXRAM_HAS_DEBUG
    FLASH_LOG_DBG("ReadData: ");
    LOG_PRINT_HEX_ARRAY(destAddr, size);
#endif /* End of FLASH_FLEXRAM_HAS_DEBUG */
}

#endif /* End of FEATURE_FLS_HAS_FLEX_NVM */

/*******************************************************************************
 * Static Internal Function Implementation
 ******************************************************************************/
