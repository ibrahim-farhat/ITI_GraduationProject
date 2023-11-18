/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: LIBRARY_interface.h	**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file LIBRARY_interface.h
 * @author Ibrahim Tarek
 * @brief This file interfaces a common library functions.
 * @version 1.00
 */

#ifndef	LIBRARY_INTERFACE_H_
#define	LIBRARY_INTERFACE_H_

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
		sint32 Copy_s32OutputRangeMin, sint32 Copy_s32OutputRangeMax, sint32 Copy_s32InputValue);

#endif
