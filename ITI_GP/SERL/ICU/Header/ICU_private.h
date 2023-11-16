/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: ICU_private.h			**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file ICU_private.h
 * @author Ibrahim Tarek
 * @brief This file contains ICU service private defines.
 * @version 1.00
 */

#ifndef ICU_PRIVATE_H_
#define ICU_PRIVATE_H_

/**
 * @brief Input capture ISR Function to be send to the timer ISR.
 */
static void ICU_voidCaptureISR(void);

/**
 * @brief Overflow ISR Function to be send to the timer ISR.
 */
static void ICU_voidOvfISR(void);

#endif
