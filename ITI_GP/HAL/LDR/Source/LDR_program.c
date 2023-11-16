/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: LDR_program.c			**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file LDR_program.c
 * @author Ibrahim Tarek
 * @brief This file implements the LDR sensor module functions.
 * @version 1.00
 */

#include "../../../Common/STD_TYPES.h"
#include "../../../Common/BIT_MATH.h"
#include "../../../Common/DEFINES.h"

#include "../../../MCAL/ADC/Header/ADC_interface.h"

#include "../Header/LDR_private.h"
#include "../Header/LDR_config.h"
#include "../Header/LDR_interface.h"


/**
 * @brief This is a function to get analog volt out from LDR sensor.
 * @note This function uses ADC with synchronous function.
 * @note LDR must be put into voltage divider circuit.
 * @param Copy_u8ADCChannel The ADC Channel to which the sensor is attached.
 * @param Copy_pu16AnalogVolt A pointer to return The analog voltage in milli volt.
 * @return Error State.
 */
uint8 LDR_u8GetAnalogVolt(uint8 Copy_u8ADCChannel, uint16 *Copy_pu16AnalogVolt)
{
	/*Define variables*/
	uint8 Local_u8ErrorState = OK;
	uint16 Local_u16ADCReading = 0;

	/*Validate the pointer passed by the user*/
	if(Copy_pu16AnalogVolt != NULL)
	{
		/*Get the reading from ADC*/
		switch(Copy_u8ADCChannel)
		{
		case LDR_u8ADC_CH0: ADC_u8StartConversionSynch(ADC_u8SINGLE_ENDED_CH0, &Local_u16ADCReading);	break;
		case LDR_u8ADC_CH1: ADC_u8StartConversionSynch(ADC_u8SINGLE_ENDED_CH1, &Local_u16ADCReading);	break;
		case LDR_u8ADC_CH2: ADC_u8StartConversionSynch(ADC_u8SINGLE_ENDED_CH2, &Local_u16ADCReading);	break;
		case LDR_u8ADC_CH3: ADC_u8StartConversionSynch(ADC_u8SINGLE_ENDED_CH3, &Local_u16ADCReading);	break;
		case LDR_u8ADC_CH4: ADC_u8StartConversionSynch(ADC_u8SINGLE_ENDED_CH4, &Local_u16ADCReading);	break;
		case LDR_u8ADC_CH5: ADC_u8StartConversionSynch(ADC_u8SINGLE_ENDED_CH5, &Local_u16ADCReading);	break;
		case LDR_u8ADC_CH6: ADC_u8StartConversionSynch(ADC_u8SINGLE_ENDED_CH6, &Local_u16ADCReading);	break;
		case LDR_u8ADC_CH7: ADC_u8StartConversionSynch(ADC_u8SINGLE_ENDED_CH7, &Local_u16ADCReading);	break;
		default: Local_u8ErrorState = NOK;
		}

		/*Calculate the voltage and return it to the user*/
#if LDR_u8ADC_RESOLUTION == LDR_u8ADC_8BITS_RES
		*Copy_pu16AnalogVolt = (uint16) (((uint32) Local_u16ADCReading * LDR_u8ADC_REF_VOLT * 1000UL) / 256UL);
#elif LDR_u8ADC_RESOLUTION == LDR_u8ADC_10BITS_RES
		*Copy_pu16AnalogVolt = (uint16) (((uint32) Local_u16ADCReading * LDR_u8ADC_REF_VOLT * 1000UL) / 1024UL);
#else
#error Wrong LDR_u8ADC_RESOLUTION configuration option
#endif

	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	/*Return the error state*/
	return Local_u8ErrorState;
}


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
uint8 LDR_u8GetResistance(uint8 Copy_u8ADCChannel, uint16 Copy_u16SourceVoltage, uint16 Copy_u16KnownResistance, uint32 *Copy_pu32LDRResistance)
{
	/*Define variables*/
	uint8 Local_u8ErrorState = OK;
	uint16 Local_u16Voltage = 0;
	uint32 Local_u32Resistance = 0;

	/*Validate the pointer passed by the user*/
	if(Copy_pu32LDRResistance != NULL)
	{
		/*Get the voltage out from the LDR sensor*/
		LDR_u8GetAnalogVolt(Copy_u8ADCChannel, &Local_u16Voltage);

		/*Calculate the resistance*/
		Local_u32Resistance = ((uint32) Copy_u16SourceVoltage / 10UL) * ((uint32) Copy_u16KnownResistance / 10UL);
		Local_u32Resistance = Local_u32Resistance / (uint32) Local_u16Voltage;
		Local_u32Resistance = (Local_u32Resistance * 100UL) - (uint32) Copy_u16KnownResistance;
		*Copy_pu32LDRResistance = Local_u32Resistance;
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	/*Return Error State*/
	return Local_u8ErrorState;
}
