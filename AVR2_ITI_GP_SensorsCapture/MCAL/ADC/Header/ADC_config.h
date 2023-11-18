/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: ADC_config.h			**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file ADC_config.h
 * @author Ibrahim Tarek
 * @brief This file configures the ADC module in prebuild configuration method.
 * @version 1.00
 */

#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_

/**
 * @details Configure the ADC reference voltage, options are: 1- AREF_REF
 * 														   	  2- AVCC_REF
 * 														   	  3- INTERNAL_2560mV_REF
 */
#define ADC_u8REF_VOLT			AVCC_REF


/**
 * @details Configure the ADC resolution, options are: 1- EIGHT_BITS
 * 													   2- TEN_BITS
 */
#define ADC_u8RESOLUTION		TEN_BITS


/**
 * @details Configure the ADC prescaler division factor, options are: 1- DIVISION_BY_2
 * 																	  2- DIVISION_BY_4
 * 																	  3- DIVISION_BY_8
 * 																	  4- DIVISION_BY_16
 * 																	  5- DIVISION_BY_32
 * 																	  6- DIVISION_BY_64
 * 																	  7- DIVISION_BY_128
 */
#define ADC_u8PRESCALER_VALUE	DIVISION_BY_128


/**
 * @details configure the ADC timeout counter value Which used in the ADC synchronous function.
 * @attention the number should not exceed the range of unsigned integer.
 */
#define ADC_u32TIMEOUT			100000u

#endif
