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
