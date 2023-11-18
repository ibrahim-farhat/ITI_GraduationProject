#include <stdint.h>

#include "../Inc/Defines.h"

#include "../Inc/Stm32F401cc.h"

#include "../Inc/GPIO_interface.h"
#include "../Inc/GPIO_private.h"

Error_t GPIO_enPinInit(const GPIO_PinConfig_t *Copy_pstPinConfig)
{
	Error_t Local_enErrorState = OK;

	if(Copy_pstPinConfig != NULL)
	{
		switch(Copy_pstPinConfig -> Port)
		{
		case GPIO_PORTA:
			if((Copy_pstPinConfig -> PinNum) <= 15)
			{
				/* Set the pin mode */
				GPIOA -> MODER &= ~(0b11 << (2 * (Copy_pstPinConfig -> PinNum)));
				GPIOA -> MODER |= ((Copy_pstPinConfig -> PinMode) << (2 * (Copy_pstPinConfig -> PinNum)));

				if(((Copy_pstPinConfig -> PinMode) == GPIO_OUTPUT) || ((Copy_pstPinConfig -> PinMode) == GPIO_ALTERNATE_FUNCTION))
				{
					/* Set the pin output type */
					GPIOA -> OTYPER &= ~(1 << Copy_pstPinConfig -> PinNum);
					GPIOA -> OTYPER |= ((Copy_pstPinConfig -> OutputType) << (Copy_pstPinConfig -> PinNum));

					/* Set the pin output speed*/
					GPIOA -> OSPEEDER &= ~(0b11 << (2 * (Copy_pstPinConfig -> PinNum)));
					GPIOA -> OSPEEDER |= ((Copy_pstPinConfig -> OutputSpeed) << (2 * (Copy_pstPinConfig -> PinNum)));

					/* Set the pin alternate function*/
					GPIOA -> AFR[(Copy_pstPinConfig -> PinNum) / 8] &= ~(0b1111 << (4 * ((Copy_pstPinConfig -> PinNum) % 8)));
					GPIOA -> AFR[(Copy_pstPinConfig -> PinNum) / 8] |= ((Copy_pstPinConfig -> AltFunc) << (4 * ((Copy_pstPinConfig -> PinNum) % 8)));
				}

				/* Set the pin pull type */
				GPIOA -> PUPDR &= ~(0b11 << (2 * (Copy_pstPinConfig -> PinNum)));
				GPIOA -> PUPDR |= ((Copy_pstPinConfig -> PullType) << (2 * (Copy_pstPinConfig -> PinNum)));

			}
			else
			{
				Local_enErrorState = NOK;
			}
			break;

		case GPIO_PORTB:
			if((Copy_pstPinConfig -> PinNum) <= 15)
			{
				/* Set the pin mode */
				GPIOB -> MODER &= ~(0b11 << (2 * (Copy_pstPinConfig -> PinNum)));
				GPIOB -> MODER |= ((Copy_pstPinConfig -> PinMode) << (2 * (Copy_pstPinConfig -> PinNum)));

				if(((Copy_pstPinConfig -> PinMode) == GPIO_OUTPUT) || ((Copy_pstPinConfig -> PinMode) == GPIO_ALTERNATE_FUNCTION))
				{
					/* Set the pin output type */
					GPIOB -> OTYPER &= ~(1 << Copy_pstPinConfig -> PinNum);
					GPIOB -> OTYPER |= ((Copy_pstPinConfig -> OutputType) << (Copy_pstPinConfig -> PinNum));

					/* Set the pin output speed*/
					GPIOB -> OSPEEDER &= ~(0b11 << (2 * (Copy_pstPinConfig -> PinNum)));
					GPIOB -> OSPEEDER |= ((Copy_pstPinConfig -> OutputSpeed) << (2 * (Copy_pstPinConfig -> PinNum)));

					/* Set the pin alternate function*/
					GPIOB -> AFR[(Copy_pstPinConfig -> PinNum) / 8] &= ~(0b1111 << (4 * ((Copy_pstPinConfig -> PinNum) % 8)));
					GPIOB -> AFR[(Copy_pstPinConfig -> PinNum) / 8] |= ((Copy_pstPinConfig -> AltFunc) << (4 * ((Copy_pstPinConfig -> PinNum) % 8)));
				}

				/* Set the pin pull type */
				GPIOB -> PUPDR &= ~(0b11 << (2 * (Copy_pstPinConfig -> PinNum)));
				GPIOB -> PUPDR |= ((Copy_pstPinConfig -> PullType) << (2 * (Copy_pstPinConfig -> PinNum)));
			}
			else
			{
				Local_enErrorState = NOK;
			}
			break;

		case GPIO_PORTC:
			if(((Copy_pstPinConfig -> PinNum) >= 13) && ((Copy_pstPinConfig -> PinNum) <= 15))
			{
				/* Set the pin mode */
				GPIOC -> MODER &= ~(0b11 << (2 * (Copy_pstPinConfig -> PinNum)));
				GPIOC -> MODER |= ((Copy_pstPinConfig -> PinMode) << (2 * (Copy_pstPinConfig -> PinNum)));

				if((Copy_pstPinConfig -> PinMode) == GPIO_OUTPUT)
				{
					/* Set the pin output type */
					GPIOC -> OTYPER &= ~(1 << Copy_pstPinConfig -> PinNum);
					GPIOC -> OTYPER |= ((Copy_pstPinConfig -> OutputType) << (Copy_pstPinConfig -> PinNum));

					/* Set the pin output speed*/
					GPIOC -> OSPEEDER &= ~(0b11 << (2 * (Copy_pstPinConfig -> PinNum)));
					GPIOC -> OSPEEDER |= ((Copy_pstPinConfig -> OutputSpeed) << (2 * (Copy_pstPinConfig -> PinNum)));

					/* Set the pin Alternate Function */
					GPIOC -> AFR[0] &= ~(0b1111 << (4 * (Copy_pstPinConfig -> PinNum)));
					GPIOC -> AFR[0] |= ((Copy_pstPinConfig -> AltFunc) << (4 * (Copy_pstPinConfig -> PinNum)));
				}

				/* Set the pin pull type */
				GPIOC -> PUPDR &= ~(0b11 << (2 * (Copy_pstPinConfig -> PinNum)));
				GPIOC -> PUPDR |= ((Copy_pstPinConfig -> PullType) << (2 * (Copy_pstPinConfig -> PinNum)));
			}
			else
			{
				Local_enErrorState = NOK;
			}
			break;

		default:
			Local_enErrorState = NOK;
			break;
		}
	}
	else
	{
		Local_enErrorState = NULL_PTR_ERROR;
	}

	return Local_enErrorState;
}

Error_t GPIO_enSetPinValue(const GPIO_PinConfig_t *Copy_pstPinConfig, GPIO_PinValue_t Copy_enPinValue)
{
	Error_t Local_enErrorState = OK;

	if(Copy_pstPinConfig != NULL)
	{
		switch(Copy_pstPinConfig -> Port)
		{
		case GPIO_PORTA:
			GPIOA -> ODR &= ~(1 << Copy_pstPinConfig -> PinNum);
			GPIOA -> ODR |= (Copy_enPinValue << (Copy_pstPinConfig -> PinNum));
			break;

		case GPIO_PORTB:
			GPIOB -> ODR &= ~(1 << Copy_pstPinConfig -> PinNum);
			GPIOB -> ODR |= (Copy_enPinValue << (Copy_pstPinConfig -> PinNum));
			break;

		case GPIO_PORTC:
			GPIOC -> ODR &= ~(1 << Copy_pstPinConfig -> PinNum);
			GPIOC -> ODR |= (Copy_enPinValue << (Copy_pstPinConfig -> PinNum));
			break;

		default:
			Local_enErrorState = NOK;
			break;
		}
	}
	else
	{
		Local_enErrorState = NULL_PTR_ERROR;
	}

	return Local_enErrorState;
}


Error_t GPIO_enReadPinValue(const GPIO_PinConfig_t *Copy_pstPinConfig, GPIO_PinValue_t *Copy_penPinValue)
{

	Error_t Local_enErrorState = OK;

	if((Copy_pstPinConfig != NULL) || (Copy_penPinValue != NULL))
	{
		switch(Copy_pstPinConfig -> Port)
		{
		case GPIO_PORTA:	*Copy_penPinValue = (((GPIOA -> IDR) >> (Copy_pstPinConfig -> PinNum)) & 0b1);	break;

		case GPIO_PORTB:	*Copy_penPinValue = (((GPIOB -> IDR) >> (Copy_pstPinConfig -> PinNum)) & 0b1);	break;

		case GPIO_PORTC:	*Copy_penPinValue = (((GPIOC -> IDR) >> (Copy_pstPinConfig -> PinNum)) & 0b1);	break;

		default:	Local_enErrorState = NOK;														break;
		}
	}
	else
	{
		Local_enErrorState = NULL_PTR_ERROR;
	}

	return Local_enErrorState;
}


Error_t GPIO_enTogglePinValue(const GPIO_PinConfig_t *Copy_pstPinConfig)
{

	Error_t Local_enErrorState = OK;

	if(Copy_pstPinConfig != NULL)
	{
		switch(Copy_pstPinConfig -> Port)
		{
		case GPIO_PORTA:	GPIOA -> ODR ^= (0b1 << Copy_pstPinConfig -> PinNum);	break;

		case GPIO_PORTB:	GPIOB -> ODR ^= (0b1 << Copy_pstPinConfig -> PinNum);	break;

		case GPIO_PORTC:	GPIOC -> ODR ^= (0b1 << Copy_pstPinConfig -> PinNum);	break;

		default: 	Local_enErrorState = NOK;					break;
		}
	}
	else
	{
		Local_enErrorState = NULL_PTR_ERROR;
	}

	return Local_enErrorState;
}

Error_t GPIO_enSetPortValue(GPIO_Port_t Copy_enPort, uint16_t Copy_u16PortValue)
{
	Error_t Local_enErrorState = OK;

	switch(Copy_enPort)
	{
	case GPIO_PORTA:
		GPIOA -> ODR = Copy_u16PortValue;
		break;

	case GPIO_PORTB:
		GPIOB -> ODR = Copy_u16PortValue;
		break;

	case GPIO_PORTC:
		GPIOC -> ODR = Copy_u16PortValue;
		break;

	default:
		Local_enErrorState = NOK;
		break;
	}

	return Local_enErrorState;
}

Error_t GPIO_enSetHalfPortValue(GPIO_Port_t Copy_enPort, uint8_t Copy_u8HalfPortValue, GPIO_Section_t Copy_enSection)
{
	Error_t Local_enErrorState = OK;

	if(Copy_enSection == GPIO_RIGHT_SECTION)
	{
		switch(Copy_enPort)
		{
		case GPIO_PORTA:
			GPIOA -> ODR &= 0xff00;
			GPIOA -> ODR |= (uint16_t) Copy_u8HalfPortValue;
			break;

		case GPIO_PORTB:
			GPIOB -> ODR &= 0xff00;
			GPIOB -> ODR |= (uint16_t) Copy_u8HalfPortValue;
			break;

		case GPIO_PORTC:
			GPIOC -> ODR &= 0xff00;
			GPIOC -> ODR |= (uint16_t) Copy_u8HalfPortValue;
			break;

		default:
			Local_enErrorState = NOK;
			break;
		}
	}
	else if(Copy_enSection == GPIO_LEFT_SECTION)
	{
		switch(Copy_enPort)
		{
		case GPIO_PORTA:
			GPIOA -> ODR &= 0x00ff;
			GPIOA -> ODR |= (((uint16_t) Copy_u8HalfPortValue) << 8);
			break;

		case GPIO_PORTB:
			GPIOB -> ODR &= 0x00ff;
			GPIOB -> ODR |= (((uint16_t) Copy_u8HalfPortValue) << 8);
			break;

		case GPIO_PORTC:
			GPIOC -> ODR &= 0x00ff;
			GPIOC -> ODR |= (((uint16_t) Copy_u8HalfPortValue) << 8);
			break;

		default:
			Local_enErrorState = NOK;
			break;
		}
	}
	else
	{
		Local_enErrorState = NOK;
	}

	return Local_enErrorState;
}
