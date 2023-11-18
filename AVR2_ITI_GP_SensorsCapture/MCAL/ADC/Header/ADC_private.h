/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: ADC_private.h			**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file ADC_private.h
 * @author Ibrahim Tarek
 * @brief This file contains ADC module private defines.
 * @version 1.00
 */

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

/*BITS' MASKS*/
#define PRESCALER_MASK			0b11111000
#define CHANNEL_MASK			0b11100000

/*ADC_u8REF_VOLT OPTIONS*/
#define AREF_REF				1u
#define AVCC_REF				2u
#define INTERNAL_2560mV_REF		3u

/*ADC_u8RESOLUTION OPTIONS*/
#define EIGHT_BITS				1u
#define TEN_BITS				2u

/*ADC_u8PRESCALER_VALUE OPTIONS*/
#define DIVISION_BY_2			1u
#define DIVISION_BY_4			2u
#define DIVISION_BY_8			3u
#define DIVISION_BY_16			4u
#define DIVISION_BY_32			5u
#define DIVISION_BY_64			6u
#define DIVISION_BY_128			7u

/*ADC_u8IntSource Options*/
#define SINGLE_CONV_ASYNCH		0u
#define CHAIN_CONV_ASYNCH		1u

#endif
