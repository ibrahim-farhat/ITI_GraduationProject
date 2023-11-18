/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: MOTOR_program.c		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file MOTOR_program.c
 * @author Ibrahim Tarek
 * @brief This file implements the motor module functions.
 * @version 1.00
 */

#include "../../../Common/STD_TYPES.h"
#include "../../../Common/BIT_MATH.h"
#include "../../../Common/DEFINES.h"

#include "../../../MCAL/DIO/Header/DIO_interface.h"

#include "../Header/MOTOR_config.h"
#include "../Header/MOTOR_private.h"
#include "../Header/MOTOR_interface.h"

/**
 * @brief 					Function to rotate the motor in clock wise.
 * @param Copy_pstMotorInfo	Pointer to struct of the motor information.
 * @return					Error state.
 */
uint8 MOTOR_u8RotateCW(const MOTOR_t *Copy_pstMotorInfo)
{
	/*Define Variables*/
	uint8 Local_u8ErrorState = OK;

	/*Validate the pointer address*/
	if(Copy_pstMotorInfo != NULL)
	{
		/*Set pin 1 as low, pin 2 as high*/
		DIO_u8SetPinValue(Copy_pstMotorInfo -> Port, Copy_pstMotorInfo -> Pin1, DIO_u8PIN_LOW);
		DIO_u8SetPinValue(Copy_pstMotorInfo -> Port, Copy_pstMotorInfo -> Pin2, DIO_u8PIN_HIGH);
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	/*Return the error state*/
	return Local_u8ErrorState;
}

/**
 * @brief				 	Function to rotate the motor in counter clock wise.
 * @param Copy_pstMotorInfo	Pointer to struct of the motor information.
 * @return					Error state.
 */
uint8 MOTOR_u8RotateCCW(const MOTOR_t *Copy_pstMotorInfo)
{
	/*Define Variables*/
	uint8 Local_u8ErrorState = OK;

	/*Validate the pointer address*/
	if(Copy_pstMotorInfo != NULL)
	{
		/*Set pin 2 as low, pin 1 as high*/
		DIO_u8SetPinValue(Copy_pstMotorInfo -> Port, Copy_pstMotorInfo -> Pin2, DIO_u8PIN_LOW);
		DIO_u8SetPinValue(Copy_pstMotorInfo -> Port, Copy_pstMotorInfo -> Pin1, DIO_u8PIN_HIGH);
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	/*Return the error state*/
	return Local_u8ErrorState;
}

/**
 * @brief 					Function to stop the motor.
 * @param Copy_pstMotorInfo	Pointer to struct of the motor information.
 * @return					Error state.
 */
uint8 MOTOR_u8Stop(const MOTOR_t *Copy_pstMotorInfo)
{
	/*Define Variables*/
	uint8 Local_u8ErrorState = OK;

	/*Validate the pointer address*/
	if(Copy_pstMotorInfo != NULL)
	{
		/*Set pin 1 and 2 as low*/
		DIO_u8SetPinValue(Copy_pstMotorInfo -> Port, Copy_pstMotorInfo -> Pin2, DIO_u8PIN_LOW);
		DIO_u8SetPinValue(Copy_pstMotorInfo -> Port, Copy_pstMotorInfo -> Pin1, DIO_u8PIN_LOW);
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	/*Return the error state*/
	return Local_u8ErrorState;
}
