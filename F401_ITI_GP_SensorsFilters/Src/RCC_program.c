#include <stdint.h>

#include "../Inc/Defines.h"

#include "../Inc/Stm32F401cc.h"

#include "../Inc/RCC_interface.h"
#include "../Inc/RCC_private.h"

Error_t RCC_enSetClkStatus(RCC_Clk_t Copy_enClockSource, Defines_Status_t Copy_enStatus)
{
	Error_t Local_enErrorSatate = OK;
	uint32_t Local_u32TimeoutCounter = 0U;

	switch(Copy_enClockSource)
	{
	case HSI:
		switch(Copy_enStatus)
		{
		case DISABLE:	RCC -> CR.HSION = 0U;		break;
		case ENABLE:
			RCC -> CR.HSION = 1U;
			while((RCC -> CR.HSIRDY != 1U) && (Local_u32TimeoutCounter != TIMEOUT))
			{
				Local_u32TimeoutCounter++;
			}
			break;
		default: 		Local_enErrorSatate = NOK;	break;
		}
		break;

	case HSE:
		switch(Copy_enStatus)
		{
		case DISABLE:	RCC -> CR.HSEON = 0U;		break;
		case ENABLE:
			RCC -> CR.HSEON = 1U;
			while((RCC -> CR.HSERDY != 1U) && (Local_u32TimeoutCounter != TIMEOUT))
			{
				Local_u32TimeoutCounter++;
			}
			break;
		default: 		Local_enErrorSatate = NOK;	break;
		}
		break;

	case PLL:
		switch(Copy_enStatus)
		{
		case DISABLE:	RCC -> CR.PLLON = 0U;		break;
		case ENABLE:
			RCC -> CR.PLLON = 1U;
			while((RCC -> CR.PLLRDY != 1U) && (Local_u32TimeoutCounter != TIMEOUT))
			{
				Local_u32TimeoutCounter++;
			}
			break;
		default: 		Local_enErrorSatate = NOK;	break;
		}
		break;

	default:
		Local_enErrorSatate = NOK;
		break;
	}

	if(Local_u32TimeoutCounter == TIMEOUT)
	{
		Local_enErrorSatate = TIMEOUT_ERROR;
	}

	return Local_enErrorSatate;
}

Error_t RCC_enSetSystemClk(RCC_Clk_t Copy_enClockSource)
{
	Error_t Local_enErrorState = OK;

	switch(Copy_enClockSource)
	{
	case HSI:
		if(RCC -> CR.HSIRDY == 1U)
		{
			RCC -> CFGR.SW = HSI;
		}
		break;

	case HSE:
		if(RCC -> CR.HSIRDY == 1U)
		{
			RCC -> CFGR.SW = HSE;
		}
		break;

	case PLL:
		if(RCC -> CR.HSIRDY == 1U)
		{
			RCC -> CFGR.SW = PLL;
		}
		break;

	default:
		Local_enErrorState = NOK;
		break;
	}
	return Local_enErrorState;
}

Error_t RCC_enHSE_Config();
Error_t RCC_enPLL_Config();

Error_t RCC_enAHB1_EnableClk(RCC_AHB1_Peripheral_t Copy_enPeripheral)
{
	Error_t Local_enErrorState = OK;

	switch(Copy_enPeripheral)
	{
	case GPIOA_EN:
	case GPIOB_EN:
	case GPIOC_EN:
	case GPIOD_EN:
	case GPIOE_EN:
	case GPIOH_EN:
	case CRC_EN:
	case FLITF_EN:
	case SRAM1_EN:
	case DMA1_EN:
	case DMA2_EN:
		RCC -> AHB1ENR |= (0b1 << Copy_enPeripheral);
		break;

	default:
		Local_enErrorState = NOK;
		break;
	}
	return Local_enErrorState;
}
Error_t RCC_enAHB1_DisableClk(RCC_AHB1_Peripheral_t Copy_enPeripheral)
{
	Error_t Local_enErrorState = OK;

	switch(Copy_enPeripheral)
	{
	case GPIOA_EN:
	case GPIOB_EN:
	case GPIOC_EN:
	case GPIOD_EN:
	case GPIOE_EN:
	case GPIOH_EN:
	case CRC_EN:
	case FLITF_EN:
	case SRAM1_EN:
	case DMA1_EN:
	case DMA2_EN:
		RCC -> AHB1ENR &= ~(0b1 << Copy_enPeripheral);
		break;

	default:
		Local_enErrorState = NOK;
		break;
	}
	return Local_enErrorState;
}

Error_t RCC_enAPB2_EnableClk(RCC_APB2_Peripheral_t Copy_enPeripheral)
{
	Error_t Local_enErrorState = OK;

	switch(Copy_enPeripheral)
	{
	case TIM1_EN:
	case USART1_EN:
	case USART6_EN:
	case ADC1_EN:
	case SDIO_EN:
	case SPI1_EN:
	case SPI4_EN:
	case SYSCFG_EN:
	case TIM9_EN:
	case TIM10_EN:
	case TIM11_EN:
		RCC -> APB2ENR |= (0b1 << Copy_enPeripheral);
		break;

	default:
		Local_enErrorState = NOK;
		break;
	}
	return Local_enErrorState;
}

