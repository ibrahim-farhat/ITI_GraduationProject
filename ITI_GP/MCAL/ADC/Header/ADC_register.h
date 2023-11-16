/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: ADC_register.h		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file ADC_register.h
 * @author Ibrahim Tarek
 * @brief This file contains ADC peripheral registers' memory locations.
 * @version 1.00
 */

#ifndef ADC_REGISTER_H_
#define ADC_REGISTER_H_

#define ADMUX			*((volatile uint8 *) 0x27)	/*ADC Multiplexer Selection Register*/
#define ADMUX_MUX0		0u							/*Analog Channel and Gain Selection Bit 0*/
#define ADMUX_MUX1		1u							/*Analog Channel and Gain Selection Bit 1*/
#define ADMUX_MUX2		2u							/*Analog Channel and Gain Selection Bit 2*/
#define ADMUX_MUX3		3u							/*Analog Channel and Gain Selection Bit 3*/
#define ADMUX_MUX4		4u							/*Analog Channel and Gain Selection Bit 4*/
#define ADMUX_ADLAR		5u							/*ADC Left Adjust Result*/
#define ADMUX_REFS0		6u							/*Reference Selection Bit 0*/
#define ADMUX_REFS1		7u							/*Reference Selection Bit 1*/

#define ADCSRA			*((volatile uint8 *) 0x26)	/*ADC Control and Status Register A*/
#define ADCSRA_ADPS0	0u							/*ADC Prescaler Select Bit 0*/
#define ADCSRA_ADPS1	1u							/*ADC Prescaler Select Bit 1*/
#define ADCSRA_ADPS2	2u							/*ADC Prescaler Select Bit 2*/
#define ADCSRA_ADIE		3u							/*ADC Interrupt Enable*/
#define ADCSRA_ADIF		4u							/*ADC Interrupt Flag*/
#define ADCSRA_ADATE	5u							/*ADC Auto Trigger Enable*/
#define ADCSRA_ADSC		6u							/*ADC Start Conversion*/
#define ADCSRA_ADEN		7u							/*ADC Enable*/

#define ADC				*((volatile uint16 *) 0x24)	/*ADC All Data Register*/
#define ADCL			*((volatile uint8 *) 0x24)	/*ADC Low Data Register*/
#define ADCH			*((volatile uint8 *) 0x25)	/*ADC High Data Register*/

#define SFIOR			*((volatile uint8 *) 0x50)	/*Special FunctionIO Register*/
#define SFIOR_ADTS0		5u							/*ADC Auto Trigger Source Bit 0*/
#define SFIOR_ADTS1		6u							/*ADC Auto Trigger Source Bit 1*/
#define SFIOR_ADTS2		7u							/*ADC Auto Trigger Source Bit 2*/

#endif
