/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: LDR_config.h			**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file LDR_config.h
 * @author Ibrahim Tarek
 * @brief This file configures the LDR sensor module in prebuild configuration method.
 * @version 1.00
 */

#ifndef LDR_CONFIG_H_
#define LDR_CONFIG_H_

/**
 * @details Configure the ADC resolution, options are: 1- LDR_u8ADC_8BITS_RES
 * 													   2- LDR_u8ADC_10BITS_RES
 */
#define LDR_u8ADC_RESOLUTION		LDR_u8ADC_10BITS_RES


/**
 * @details Configure the ADC reference voltage, Range: 0u - 5u volt
 */
#define LDR_u8ADC_REF_VOLT			5u

#endif
