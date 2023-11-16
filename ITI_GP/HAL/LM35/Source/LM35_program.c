/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: LM35_program.c		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file LM35_program.c
 * @author Ibrahim Tarek
 * @brief This file implements the LM35 sensor module functions.
 * @version 1.00
 */

#include "../../../Common/STD_TYPES.h"
#include "../../../Common/BIT_MATH.h"
#include "../../../Common/DEFINES.h"

#include "../../../MCAL/ADC/Header/ADC_interface.h"

#include "../Header/LM35_config.h"
#include "../Header/LM35_private.h"
#include "../Header/LM35_interface.h"


/**
 * @brief 					This is a function to get temperature from LM35 temperature sensor.
 * @note 					This function uses ADC with synchronous function.
 * @param Copy_u8ADCChannel The ADC Channel to which the sensor is attached.
 * @param Copy_pu8Temp 		Pointer to return The temperature in celsius degrees.
 * @return 					Error State.
 */
uint8 LM35_u8GetTemp(uint8 Copy_u8ADCChannel, uint8 *Copy_pu8Temp)
{
	/*Define variables*/
	uint8 Local_u8ErrorState = OK;
	uint16 Local_u16Voltage = 0;
	uint16 Local_u16ADCReading = 0;

	/*Validate the pointer passed by the user*/
	if(Copy_pu8Temp != NULL)
	{
		/*Get the reading from ADC*/
		switch(Copy_u8ADCChannel)
		{
		case LM35_u8ADC_CH0: ADC_u8StartConversionSynch(ADC_u8SINGLE_ENDED_CH0, &Local_u16ADCReading);	break;
		case LM35_u8ADC_CH1: ADC_u8StartConversionSynch(ADC_u8SINGLE_ENDED_CH1, &Local_u16ADCReading);	break;
		case LM35_u8ADC_CH2: ADC_u8StartConversionSynch(ADC_u8SINGLE_ENDED_CH2, &Local_u16ADCReading);	break;
		case LM35_u8ADC_CH3: ADC_u8StartConversionSynch(ADC_u8SINGLE_ENDED_CH3, &Local_u16ADCReading);	break;
		case LM35_u8ADC_CH4: ADC_u8StartConversionSynch(ADC_u8SINGLE_ENDED_CH4, &Local_u16ADCReading);	break;
		case LM35_u8ADC_CH5: ADC_u8StartConversionSynch(ADC_u8SINGLE_ENDED_CH5, &Local_u16ADCReading);	break;
		case LM35_u8ADC_CH6: ADC_u8StartConversionSynch(ADC_u8SINGLE_ENDED_CH6, &Local_u16ADCReading);	break;
		case LM35_u8ADC_CH7: ADC_u8StartConversionSynch(ADC_u8SINGLE_ENDED_CH7, &Local_u16ADCReading);	break;
		default: Local_u8ErrorState = NOK;
		}

		/*Calculate the voltage*/
#if LM35_u8ADC_RESOLUTION == LM35_u8ADC_8BITS_RES
		Local_u16Voltage = (uint16) (((uint32) Local_u16ADCReading * LM35_u8ADC_REF_VOLT * 1000UL) / 256UL);
#elif LM35_u8ADC_RESOLUTION == LM35_u8ADC_10BITS_RES
		Local_u16Voltage = (uint16) (((uint32) Local_u16ADCReading * LM35_u8ADC_REF_VOLT * 1000UL) / 1024UL);
#else
#error Wrong LM35_u8ADC_RESOLUTION configuration option
#endif

		/*Calculate the temperature*/
		*Copy_pu8Temp = (uint8) (Local_u16Voltage /  10u);
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	/*Return the error state*/
	return Local_u8ErrorState;
}
