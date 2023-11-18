/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: DIO_interface.h		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file DIO_interface.h
 * @author Ibrahim Tarek
 * @brief This file interfaces the DIO module functions.
 * @version 1.00
 */

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

/*Copy_u8Port Options*/
#define DIO_u8PORTA			0u
#define DIO_u8PORTB			1u
#define DIO_u8PORTC			2u
#define DIO_u8PORTD			3u

/*Copy_u8Pin Options*/
#define DIO_u8PIN0			0u
#define DIO_u8PIN1			1u
#define DIO_u8PIN2			2u
#define DIO_u8PIN3			3u
#define DIO_u8PIN4			4u
#define DIO_u8PIN5			5u
#define DIO_u8PIN6			6u
#define DIO_u8PIN7			7u

/*Copy_u8Direction Options*/
#define DIO_u8PIN_INPUT		0u
#define DIO_u8PIN_OUTPUT	1u

/*Copy_u8Value Options*/
#define DIO_u8PIN_LOW		0u
#define	DIO_u8PIN_HIGH		1u

/**
 * @brief 					Function to change the data direction of a pin.
 * @param Copy_u8Port 		Port number on which the pin is found.
 * @param Copy_u8Pin 		Pin number.
 * @param Copy_u8Direction 	The new direction wanted to set.
 * @return 					Error state.
 */
uint8 DIO_u8SetPinDirection(uint8 Copy_u8Port, uint8 Copy_u8Pin, uint8 Copy_u8Direction);

/**
 * @brief 				Function to change the value of a pin.
 * @param Copy_u8Port 	Port number on which the pin is found.
 * @param Copy_u8Pin 	Pin number.
 * @param Copy_u8Value 	The new value wanted to set.
 * @return 				Error state.
 */
uint8 DIO_u8SetPinValue(uint8 Copy_u8Port, uint8 Copy_u8Pin, uint8 Copy_u8Value);

/**
 * @brief 				Function to toggle the value of a pin.
 * @param Copy_u8Port 	Port number on which the pin is found.
 * @param Copy_u8Pin 	Pin number.
 * @return 				Error state.
 */
uint8 DIO_u8TogglePinValue(uint8 Copy_u8Port, uint8 Copy_u8Pin);

/**
 * @brief 				Function to return the value of a pin.
 * @param Copy_u8Port 	Port number on which the pin is found.
 * @param Copy_u8Pin 	Pin number.
 * @param Copy_pu8Value Pointer to return the value of the pin.
 * @return 				Error state.
 */
uint8 DIO_u8GetPinValue(uint8 Copy_u8Port, uint8 Copy_u8Pin, uint8 *Copy_pu8Value);

/**
 * @brief 					Function to set the direction of a full port.
 * @param Copy_u8Port		Port number.
 * @param Copy_u8Direction	Character to represent port Direction.
 * @return					Error state.
 */
uint8 DIO_u8SetPortDirection(uint8 Copy_u8Port, uint8 Copy_u8Direction);

/**
 * @brief 					Function to set the value of a full port.
 * @param Copy_u8Port		Port number.
 * @param Copy_u8Direction	Character to represent port value.
 * @return					Error state.
 */
uint8 DIO_u8SetPortValue(uint8 Copy_u8Port, uint8 Copy_u8Value);

#endif
