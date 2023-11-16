/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: LM35_interface.h		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file LM35_interface.h
 * @author Ibrahim Tarek
 * @brief This file interfaces the LM35 sensor module functions.
 * @version 1.00
 */

#ifndef LM35_INTERFACE_H_
#define LM35_INTERFACE_H_


/*Copy_u8ADCChannel Options*/
#define LM35_u8ADC_CH0		0u
#define LM35_u8ADC_CH1		1u
#define LM35_u8ADC_CH2		2u
#define LM35_u8ADC_CH3		3u
#define LM35_u8ADC_CH4		4u
#define LM35_u8ADC_CH5		5u
#define LM35_u8ADC_CH6		6u
#define LM35_u8ADC_CH7		7u

/**
 * @brief 					This is a function to get temperature from LM35 temperature sensor.
 * @note 					This function uses ADC with synchronous function.
 * @param Copy_u8ADCChannel The ADC Channel to which the sensor is attached.
 * @param Copy_pu8Temp 		Pointer to return The temperature in celsius degrees.
 * @return 					Error State.
 */
uint8 LM35_u8GetTemp(uint8 Copy_u8ADCChannel, uint8 *Copy_pu8Temp);

#endif
