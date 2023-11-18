/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: LM35_config.h			**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file LM35_config.h
 * @author Ibrahim Tarek
 * @brief This file configures the LM35 sensor module in prebuild configuration method.
 * @version 1.00
 */

#ifndef LM35_CONFIG_H_
#define LM35_CONFIG_H_

/**
 * @details Configure the ADC resolution, options are: 1- LM35_u8ADC_8BITS_RES
 * 													   2- LM35_u8ADC_10BITS_RES
 */
#define LM35_u8ADC_RESOLUTION		LM35_u8ADC_10BITS_RES


/**
 * @details Configure the ADC reference voltage, Range: 0u - 5u volt
 */
#define LM35_u8ADC_REF_VOLT			5u

#endif
