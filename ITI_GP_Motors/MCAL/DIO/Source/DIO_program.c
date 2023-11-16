/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: DIO_program.c			**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file DIO_program.c
 * @author Ibrahim Tarek
 * @brief This file implements the DIO module functions.
 * @version 1.00
 */

#include "../../../Common/STD_TYPES.h"
#include "../../../Common/BIT_MATH.h"
#include "../../../Common/DEFINES.h"

#include "../Header/DIO_config.h"
#include "../Header/DIO_interface.h"
#include "../Header/DIO_private.h"
#include "../Header/DIO_register.h"

/**
 * @brief 					Function to change the data direction of a pin.
 * @param Copy_u8Port 		Port number on which the pin is found.
 * @param Copy_u8Pin 		Pin number.
 * @param Copy_u8Direction 	The new direction wanted to set.
 * @return 					Error state.
 */
uint8 DIO_u8SetPinDirection(uint8 Copy_u8Port, uint8 Copy_u8Pin, uint8 Copy_u8Direction)
{
	uint8 Local_u8ErrorEstate = OK;

	if(Copy_u8Pin <= DIO_u8PIN7)
	{
		if(Copy_u8Direction == DIO_u8PIN_OUTPUT)
		{
			switch(Copy_u8Port)
			{
			case DIO_u8PORTA: SET_BIT(DDRA,Copy_u8Pin);	break;
			case DIO_u8PORTB: SET_BIT(DDRB,Copy_u8Pin);	break;
			case DIO_u8PORTC: SET_BIT(DDRC,Copy_u8Pin);	break;
			case DIO_u8PORTD: SET_BIT(DDRD,Copy_u8Pin);	break;
			default: Local_u8ErrorEstate = NOK;	break;
			}
		}
		else if(Copy_u8Direction == DIO_u8PIN_INPUT)
		{
			switch(Copy_u8Port)
			{
			case DIO_u8PORTA: CLR_BIT(DDRA,Copy_u8Pin);	break;
			case DIO_u8PORTB: CLR_BIT(DDRB,Copy_u8Pin);	break;
			case DIO_u8PORTC: CLR_BIT(DDRC,Copy_u8Pin);	break;
			case DIO_u8PORTD: CLR_BIT(DDRD,Copy_u8Pin);	break;
			default: Local_u8ErrorEstate = NOK;	break;
			}
		}
		else
		{
			Local_u8ErrorEstate = NOK;
		}
	}
	else
	{
		Local_u8ErrorEstate = NOK;
	}

	return Local_u8ErrorEstate;
}

/**
 * @brief 				Function to change the value of a pin.
 * @param Copy_u8Port 	Port number on which the pin is found.
 * @param Copy_u8Pin 	Pin number.
 * @param Copy_u8Value 	The new value wanted to set.
 * @return 				Error state.
 */
uint8 DIO_u8SetPinValue(uint8 Copy_u8Port, uint8 Copy_u8Pin, uint8 Copy_u8Value)
{
	uint8 Local_u8ErrorState = OK;

	if(Copy_u8Pin <= DIO_u8PIN7)
	{
		if(Copy_u8Value == DIO_u8PIN_HIGH)
		{
			switch(Copy_u8Port)
			{
			case DIO_u8PORTA: SET_BIT(PORTA,Copy_u8Pin);	break;
			case DIO_u8PORTB: SET_BIT(PORTB,Copy_u8Pin);	break;
			case DIO_u8PORTC: SET_BIT(PORTC,Copy_u8Pin);	break;
			case DIO_u8PORTD: SET_BIT(PORTD,Copy_u8Pin);	break;
			default: Local_u8ErrorState = NOK;	break;
			}
		}
		else if(Copy_u8Value == DIO_u8PIN_LOW)
		{
			switch(Copy_u8Port)
			{
			case DIO_u8PORTA: CLR_BIT(PORTA,Copy_u8Pin);	break;
			case DIO_u8PORTB: CLR_BIT(PORTB,Copy_u8Pin);	break;
			case DIO_u8PORTC: CLR_BIT(PORTC,Copy_u8Pin);	break;
			case DIO_u8PORTD: CLR_BIT(PORTD,Copy_u8Pin);	break;
			default: Local_u8ErrorState = NOK;	break;
			}
		}
		else
		{
			Local_u8ErrorState = NOK;
		}
	}
	else
	{
		Local_u8ErrorState = NOK;
	}

	return Local_u8ErrorState;
}

/**
 * @brief 				Function to toggle the value of a pin.
 * @param Copy_u8Port 	Port number on which the pin is found.
 * @param Copy_u8Pin 	Pin number.
 * @return 				Error state.
 */
uint8 DIO_u8TogglePinValue(uint8 Copy_u8Port, uint8 Copy_u8Pin)
{
	uint8 Local_u8ErrorState = OK;

	if(Copy_u8Pin <= DIO_u8PIN7)
	{
		switch(Copy_u8Port)
		{
		case DIO_u8PORTA: TOG_BIT(PORTA,Copy_u8Pin);	break;
		case DIO_u8PORTB: TOG_BIT(PORTB,Copy_u8Pin);	break;
		case DIO_u8PORTC: TOG_BIT(PORTC,Copy_u8Pin);	break;
		case DIO_u8PORTD: TOG_BIT(PORTD,Copy_u8Pin);	break;
		default: Local_u8ErrorState = NOK;
		}
	}
	else
	{
		Local_u8ErrorState = NOK;
	}

	return Local_u8ErrorState;
}

/**
 * @brief 				Function to return the value of a pin.
 * @param Copy_u8Port 	Port number on which the pin is found.
 * @param Copy_u8Pin 	Pin number.
 * @param Copy_pu8Value Pointer to return the value of the pin.
 * @return 				Error state.
 */
uint8 DIO_u8GetPinValue(uint8 Copy_u8Port, uint8 Copy_u8Pin, uint8 *Copy_pu8Value)
{
	uint8 Local_u8ErrorState = OK;

	if(Copy_u8Pin <= DIO_u8PIN7)
	{
		switch(Copy_u8Port)
		{
		case DIO_u8PORTA: *Copy_pu8Value = GET_BIT(PINA,Copy_u8Pin);	break;
		case DIO_u8PORTB: *Copy_pu8Value = GET_BIT(PINB,Copy_u8Pin);	break;
		case DIO_u8PORTC: *Copy_pu8Value = GET_BIT(PINC,Copy_u8Pin);	break;
		case DIO_u8PORTD: *Copy_pu8Value = GET_BIT(PIND,Copy_u8Pin);	break;
		default: Local_u8ErrorState = NOK;	break;
		}
	}
	else
	{
		Local_u8ErrorState = NOK;
	}

	return Local_u8ErrorState;
}

/**
 * @brief 					Function to set the direction of a full port.
 * @param Copy_u8Port		Port number.
 * @param Copy_u8Direction	Character to represent port Direction.
 * @return					Error state.
 */
uint8 DIO_u8SetPortDirection(uint8 Copy_u8Port, uint8 Copy_u8Direction)
{
	uint8 Local_u8ErrorState = OK;

	switch(Copy_u8Port)
	{
	case DIO_u8PORTA: DDRA = Copy_u8Direction;	break;
	case DIO_u8PORTB: DDRB = Copy_u8Direction;	break;
	case DIO_u8PORTC: DDRC = Copy_u8Direction;	break;
	case DIO_u8PORTD: DDRD = Copy_u8Direction;	break;
	default: Local_u8ErrorState = NOK;	break;
	}

	return Local_u8ErrorState;
}

/**
 * @brief 					Function to set the value of a full port.
 * @param Copy_u8Port		Port number.
 * @param Copy_u8Direction	Character to represent port value.
 * @return					Error state.
 */
uint8 DIO_u8SetPortValue(uint8 Copy_u8Port, uint8 Copy_u8Value)
{
	uint8 Local_u8ErrorState = OK;

	switch(Copy_u8Port)
	{
	case DIO_u8PORTA: PORTA = Copy_u8Value;	break;
	case DIO_u8PORTB: PORTB = Copy_u8Value;	break;
	case DIO_u8PORTC: PORTC = Copy_u8Value;	break;
	case DIO_u8PORTD: PORTD = Copy_u8Value;	break;
	default: Local_u8ErrorState = NOK;	break;
	}

	return Local_u8ErrorState;
}
