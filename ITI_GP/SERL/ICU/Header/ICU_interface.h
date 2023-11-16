/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: ICU_interface.h		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file ICU_interface.h
 * @author Ibrahim Tarek
 * @brief This file interfaces the ICU service functions.
 * @version 1.00
 */

#ifndef ICU_INTERFACE_H_
#define ICU_INTERFACE_H_

/**
 * @brief 						Function that return the characteristics of a PWM signal.
 * @param Copy_pu8DutyCycle		Pointer to return the duty cycle of the signal.
 * @param Copy_pu32PeriodTime	Pointer to return the period time of the signal.
 */
void ICU_voidMeasurePWM(uint8 *Copy_pu8DutyCycle, uint32 *Copy_pu32PeriodTime);

#endif
