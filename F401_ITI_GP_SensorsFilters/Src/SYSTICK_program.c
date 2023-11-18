#include <stdint.h>

#include "../Inc/Defines.h"

#include "../Inc/Stm32F401cc.h"

#include "../Inc/SYSTICK_interface.h"
#include "../Inc/SYSTICK_private.h"

static const SYSTICK_Config_t *SYSTICK_stConfig;
static uint8_t SYSTICK_u8BusyFlag = IDLE;
static void (*SYSTICK_pvCallBackFunction)(void) = NULL;

Error_t SYSTICK_enInit(const SYSTICK_Config_t *Copy_stConfig)
{
	/*Define Error State*/
	Error_t Local_enErrorState = OK;

	/*Validate the pointer to the struct*/
	if(Copy_stConfig != NULL)
	{
		/* Set the interrupt configuration */
		SYSTICK -> CTRL.TICKINT = Copy_stConfig -> Exception_Request;

		/* Set the clock source configuration */
		SYSTICK -> CTRL.CLKSOURCE = Copy_stConfig -> Prescaler;

		/* Make the pointer to the configuration to sturct as global */
		SYSTICK_stConfig = Copy_stConfig;
	}
	else
	{
		Local_enErrorState = NULL_PTR_ERROR;
	}

	/*Return Error State*/
	return Local_enErrorState;
}


void SYSTICK_voidDelayUS(uint32_t Copy_u32MicroSeconds)
{
	if(SYSTICK_u8BusyFlag == IDLE)
	{
		/* This is only for 16 MHz Clock */

		/* Load the Ticks in its register and make sure the VAL register will start from beginning */
		if(SYSTICK_stConfig -> Prescaler == SYSTICK_AHB)
		{
			SYSTICK -> LOAD = Copy_u32MicroSeconds * (SYSTICK_stConfig -> ClkFreq);
		}
		else if(SYSTICK_stConfig -> Prescaler == SYSTICK_AHB_BY_8)
		{
			SYSTICK -> LOAD = Copy_u32MicroSeconds * ((SYSTICK_stConfig -> ClkFreq) / 8);
		}

		/* Zero the value register */
		SYSTICK -> VALUE = 0u;

		/* Enable the counter */
		SYSTICK -> CTRL.Enable = 1u;

		/* Wait for time to pass */
		while((SYSTICK -> CTRL.COUNTFLAG) == 0u);

		/* Disable the counter */
		SYSTICK -> CTRL.Enable = 0u;
	}
}

void SYSTICK_voidEnable(void)
{
	SYSTICK_u8BusyFlag = BUSY;

	/* Zero the value register */
	SYSTICK -> VALUE = 0u;

	/* Enable the counter */
	SYSTICK -> CTRL.Enable = 1u;
}

void SYSTICK_voidDisable(void)
{
	SYSTICK_u8BusyFlag = IDLE;
}

void SYSTICK_voidDelayMS(uint32_t Copy_u32MilliSeconds)
{
	if(SYSTICK_u8BusyFlag == IDLE)
	{
		/* This is only for 16 MHz Clock */

		/* Load the Ticks in its register and make sure the VAL register will start from beginning */
		if(SYSTICK_stConfig -> Prescaler == SYSTICK_AHB)
		{
			SYSTICK -> LOAD = Copy_u32MilliSeconds * 1000 * (SYSTICK_stConfig -> ClkFreq);
		}
		else if(SYSTICK_stConfig -> Prescaler == SYSTICK_AHB_BY_8)
		{
			SYSTICK -> LOAD = Copy_u32MilliSeconds * 1000 * ((SYSTICK_stConfig -> ClkFreq) / 8);
		}

		/* Zero the value register */
		SYSTICK -> VALUE = 0u;

		/* Enable the counter */
		SYSTICK -> CTRL.Enable = 1u;

		/* Wait for time to pass */
		while((SYSTICK -> CTRL.COUNTFLAG) == 0u);

		/* Disable the counter */
		SYSTICK -> CTRL.Enable = 0u;
	}
}

void SYSTICK_voidSetReloadValue(uint32_t Copy_u32Value)
{
	SYSTICK -> LOAD = Copy_u32Value;

	/* Zero the value register */
	SYSTICK -> VALUE = 0u;
}

uint32_t SYSTICK_u32GetElapsedValue(void)
{
	uint32_t Local_u32ElapsedValue = SYSTICK -> LOAD - SYSTICK -> VALUE;

	return Local_u32ElapsedValue;
}

Error_t SYSTICK_voidSetCallBackFunction(void (*Copy_pvCallBackFunction)(void))
{
	Error_t Local_enErrorState = OK;

	if(Copy_pvCallBackFunction != NULL)
	{
		SYSTICK_pvCallBackFunction = Copy_pvCallBackFunction;
	}
	else
	{
		Local_enErrorState = NULL_PTR_ERROR;
	}

	return Local_enErrorState;
}
void SysTick_Handler(void)
{
	if(SYSTICK_pvCallBackFunction != NULL)
	{
		SYSTICK_pvCallBackFunction();
	}
}

