/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: LIBRARY_program.c		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file LIBRARY_program.c
 * @author Ibrahim Tarek
 * @brief This file implements the common library functions.
 * @version 1.00
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DEFINES.h"

#include "LIBRARY_interface.h"

/**
 * @brief This function returns the mapping of a point from a range into another range.
 * @param Copy_s32InputRangeMin	Minimum Value of the input range.
 * @param Copy_s32InputRangeMax	Maximum Value of the input range.
 * @param Copy_s32OutputRangeMin	Minimum Value of the output range.
 * @param Copy_OutputRangeMax	Maximum Value of the output range.
 * @param Copy_s32InputValue	Input value.
 * @return	Output Value
 */
sint32 LIBRARY_s32Mapping(sint32 Copy_s32InputRangeMin, sint32 Copy_s32InputRangeMax,
		sint32 Copy_s32OutputRangeMin, sint32 Copy_s32OutputRangeMax, sint32 Copy_s32InputValue)
{
	/*Define Variables*/
	sint32 Local_s32OutputValue = 0;

	/*Calculate the output value*/
	Local_s32OutputValue = (Copy_s32OutputRangeMax - Copy_s32OutputRangeMin) * (Copy_s32InputValue - Copy_s32InputRangeMin);
	Local_s32OutputValue = Local_s32OutputValue / (Copy_s32InputRangeMax - Copy_s32InputRangeMin);
	Local_s32OutputValue = Local_s32OutputValue + Copy_s32OutputRangeMin;

	return Local_s32OutputValue;
}
