#ifndef FLASH_DRIVER_H_
#define FLASH_DRIVER_H_

#include <stdint.h>

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

//Flash status
#define FLASH_OK             0U
#define FLASH_ERROR          1U
#define FLASH_BUSY           2U
#define FLASH_ALIGN_ERROR    3U
#define FLASH_RANGE_ERROR    4U

uint8_t  FLASH_Unlock(FLASH_RegDef_t* pFLASHx);

#endif /* FLASH_DRIVER_H_ */
