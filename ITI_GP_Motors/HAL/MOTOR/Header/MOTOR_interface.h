/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: MOTOR_interface.h		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file MOTOR_interface.h
 * @author Ibrahim Tarek
 * @brief This file interfaces the motor module functions.
 * @version 1.00
 */

#ifndef MOTOR_INTERFACE_H_
#define MOTOR_INTERFACE_H_

/**
 * @brief 		Struct type for configure the motor information.
 * @param Port 	Port number to which the motor is connected.
 * @param Pin1 	Pin number of the first pin of the motor.
 * @param Pin2 	Pin number of the second pin of the motor.
 */
typedef struct MOTOR_t
{
	uint8 Port;
	uint8 Pin1;
	uint8 Pin2;
}MOTOR_t;

/**
 * @brief 					Function to rotate the motor in clock wise.
 * @param Copy_pstMotorInfo	Pointer to struct of the motor information.
 * @return					Error state.
 */
uint8 MOTOR_u8RotateCW(const MOTOR_t *Copy_pstMotorInfo);

/**
 * @brief				 	Function to rotate the motor in counter clock wise.
 * @param Copy_pstMotorInfo	Pointer to struct of the motor information.
 * @return					Error state.
 */
uint8 MOTOR_u8RotateCCW(const MOTOR_t *Copy_pstMotorInfo);

/**
 * @brief 					Function to stop the motor.
 * @param Copy_pstMotorInfo	Pointer to struct of the motor information.
 * @return					Error state.
 */
uint8 MOTOR_u8Stop(const MOTOR_t *Copy_psttMotorInfo);

#endif
