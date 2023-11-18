/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: BIT_MATH.h			**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file BIT_MATH.h
 * @author Ibrahim Tarek
 * @brief This file implements bit math library functions.
 * @version 1.00
 */

#ifndef	BIT_MATH_H_
#define BIT_MATH_H_

/**
 * @brief Function like macro to set a bit inside a number.
 * @param VAR is the number.
 * @param BIT_NUMBER is the bit wanted to be set.
 */
#define SET_BIT(VAR,BIT_NUMBER)	((VAR)|=(1<<(BIT_NUMBER)))

/**
 * @brief Function like macro to clear a bit inside a number.
 * @param VAR is the number.
 * @param BIT_NUMBER is the bit wanted to be cleared.
 */
#define CLR_BIT(VAR,BIT_NUMBER)	((VAR)&=(~(1<<(BIT_NUMBER))))

/**
 * @brief Function like macro to toggle a bit inside a number.
 * @param VAR is the number.
 * @param BIT_NUMBER is the bit wanted to be toggled.
 */
#define TOG_BIT(VAR,BIT_NUMBER)	((VAR)^=(1<<(BIT_NUMBER)))

/**
 * @brief Function like macro to get a bit from a number.
 * @param VAR is the number.
 * @param BIT_NUMBER is the bit wanted to be read.
 */
#define GET_BIT(VAR,BIT_NUMBER)	(((VAR)>>(BIT_NUMBER))&1)

#endif
