/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: LDR_interface.h		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file LDR_interface.h
 * @author Ibrahim Tarek
 * @brief This file interfaces the LDR sensor module functions.
 * @version 1.00
 */

#ifndef LDR_INTERFACE_H_
#define LDR_INTERFACE_H_


/*Copy_u8ADCChannel Options*/
#define LDR_u8ADC_CH0		0u
#define LDR_u8ADC_CH1		1u
#define LDR_u8ADC_CH2		2u
#define LDR_u8ADC_CH3		3u
#define LDR_u8ADC_CH4		4u
#define LDR_u8ADC_CH5		5u
#define LDR_u8ADC_CH6		6u
#define LDR_u8ADC_CH7		7u

/**
 * @brief This is a function to get analog volt out from LDR sensor.
 * @note This function uses ADC with synchronous function.
 * @note LDR must be put into voltage divider circuit.
 * @param Copy_u8ADCChannel The ADC Channel to which the sensor is attached.
 * @param Copy_pu16AnalogVolt A pointer to return The analog voltage in milli volt.
 * @return Error State.
 */
uint8 LDR_u8GetAnalogVolt(uint8 Copy_u8ADCChannel, uint16 *Copy_pu16AnalogVolt);

/**
 * @brief This is a function to get the resistance of LDR sensor.
 * @note This function uses ADC with synchronous function.
 * @note LDR must be put into voltage divider circuit.
 * @param Copy_u8ADCChannel The ADC Channel to which the sensor is attached.
 * @param Copy_pu32LDRResistance A pointer to return the resistance in ohm.
 * @param Copy_u16SourceVoltage The source voltage which support the LDR with power in milli volt.
 * @param Copy_u16KnownResistance The resistance which participate in the voltage divider circuit in ohm.
 * @return Error State.
 */
uint8 LDR_u8GetResistance(uint8 Copy_u8ADCChannel, uint16 Copy_u16SourceVoltage, uint16 Copy_u16KnownResistance, uint32 *Copy_pu32LDRResistance);

#endif
