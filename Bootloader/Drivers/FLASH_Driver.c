#include "FLASH_Driver.h"

uint8_t FLASH_Unlock(FLASH_RegDef_t* pFLASHx)
{
	if(pFLASHx->CR & (1 << F_LOCK))
	{
		pFLASHx->KEYR=FLASH_KEY1;
		pFLASHx->KEYR=FLASH_KEY2;
	}
	if(pFLASHx->CR & (1 << F_LOCK))
	{
		return FLASH_ERROR;

	}
	return FLASH_OK;
}

void FLASH_Lock(FLASH_RegDef_t* pFLASHx)
{
	pFLASHx->CR |= (1 << F_LOCK);


}


uint8_t FLASH_WaitForLastOperation(FLASH_RegDef_t *pFLASHx)
{
	while(pFLASHx->SR & (1 << F_BSY))
	{

	}
	return FLASH_OK;
}

uint8_t FLASH_EraseSector(FLASH_RegDef_t *pFLASHx,uint8_t sector)
{
	uint8_t status;
	if (sector > FLASH_MAX_SECTOR || sector <= FLASH_BOOTLOADER_END)
	{
		return FLASH_ERROR;
	}
	if (pFLASHx->CR & (1U << F_LOCK))
	{
	    return FLASH_ERROR;
	}

	status=FLASH_WaitForLastOperation(pFLASHx);

	if (status != FLASH_OK)
	{
		return status;
	}
	FLASH_ClearErrorFlags(pFLASHx);
	pFLASHx->CR &= ~(0xF << F_SNB);
	pFLASHx->CR |= (1 << F_SER);
	pFLASHx->CR |= ((uint32_t)sector << F_SNB);
	pFLASHx->CR |= (1 << F_STRT);

	status = FLASH_WaitForLastOperation(pFLASHx);

	pFLASHx->CR &= ~(1 << F_SER);

	if (status != FLASH_OK)
	{
	    return status;
	}

	if (pFLASHx->SR & FLASH_ERROR_FLAGS)
	{
	    return FLASH_ERROR;
	}
	return status;
}

void FLASH_ClearErrorFlags(FLASH_RegDef_t *pFLASHx)
{
	pFLASHx->SR = (1 << F_OPERR)  |	(1 << F_WRPERR) |
	              (1 << F_PGAERR) |	(1 << F_PGPERR) |
	              (1 << F_PGSERR);
}

