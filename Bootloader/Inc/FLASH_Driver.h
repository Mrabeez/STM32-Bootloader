#ifndef FLASH_DRIVER_H_
#define FLASH_DRIVER_H_

#include <stdint.h>
#include "STM32F401CCUx.h"

//flash unlock keys
#define FLASH_KEY1    0x45670123U
#define FLASH_KEY2    0xCDEF89ABU

//FLASH_CR
#define F_LOCK      31
#define F_ERRIE     25
#define F_EOPIE     24
#define F_STRT      16
#define F_PSIZE     8
#define F_SNB       3
#define F_MER       2
#define F_SER       1
#define F_PG        0

//FLASH_SR
#define F_BSY       16
#define F_RDERR     8
#define F_PGSERR    7
#define F_PGPERR    6
#define F_PGAERR    5
#define F_WRPERR    4
#define F_OPERR     1
#define F_EOP       0

//Flash status
#define FLASH_OK             0U
#define FLASH_ERROR          1U
#define FLASH_BUSY           2U
#define FLASH_ALIGN_ERROR    3U
#define FLASH_RANGE_ERROR    4U

#define FLASH_MAX_SECTOR       5U
#define FLASH_BOOTLOADER_END   2U

uint8_t  FLASH_Unlock(FLASH_RegDef_t* pFLASHx);
void FLASH_Lock(FLASH_RegDef_t* pFLASHx);
uint8_t FLASH_WaitForLastOperation(FLASH_RegDef_t *pFLASHx);
uint8_t FLASH_EraseSector(FLASH_RegDef_t *pFLASHx,uint8_t sector);
void FLASH_ClearErrorFlags(FLASH_RegDef_t *pFLASHx);

#endif /* FLASH_DRIVER_H_ */
