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

static void FLASH_SetPSIZE(FLASH_RegDef_t *pFLASHx, uint32_t size)
{
    pFLASHx->CR &= ~(0x3U << F_PSIZE);
    pFLASHx->CR |= (size << F_PSIZE);
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

	FLASH_SetPSIZE(pFLASHx, FLASH_PSIZE_X32);

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

	if (pFLASHx->SR & FLASH_SR_ERR_MASK)
	{
	    return FLASH_ERROR;
	}
	return status;
}

void FLASH_ClearErrorFlags(FLASH_RegDef_t *pFLASHx)
{
	pFLASHx->SR = FLASH_SR_ERR_MASK;
}

uint8_t FLASH_ProgramWord(FLASH_RegDef_t *pFLASHx,uint32_t address,uint32_t data)
{
	uint8_t status;
	if (address < FLASH_APP_START_ADDR || (address > (FLASH_APP_END_ADDR - 3U)))
		{
			return FLASH_RANGE_ERROR;
		}

	if (address % 4U != 0U)
		{
			return FLASH_ALIGN_ERROR;
		}

	if(pFLASHx->CR & (1 << F_LOCK))
		{
	    	return FLASH_ERROR;
		}

	status = FLASH_WaitForLastOperation(pFLASHx);

	if (status != FLASH_OK)
		{
			return status;
		}

	FLASH_ClearErrorFlags(pFLASHx);

	//configuring the p_size
	FLASH_SetPSIZE(pFLASHx, FLASH_PSIZE_X32);
	//Flash programming activated
	pFLASHx->CR |= (0x1U << F_PG);

	*((__vo uint32_t*) address)=data;

	// Wait for programming operation
	status = FLASH_WaitForLastOperation(pFLASHx);

	//Flash programming deactivated
	pFLASHx->CR &= ~(1U << F_PG);

	if (status != FLASH_OK)
	{
	    return status;
	}

	// Check programming errors
	if (pFLASHx->SR & FLASH_SR_ERR_MASK)
	{
	    return FLASH_ERROR;
	}

	return FLASH_OK;
}
