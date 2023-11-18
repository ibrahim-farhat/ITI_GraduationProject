/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: ULTSONIC_private.h	**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file ULTSONIC_private.h
 * @author Ibrahim Tarek
 * @brief This file contains ULTSONIC sensor module private defines.
 * @version 1.00
 */

#ifndef ULTSONIC_PRIVATE_H_
#define ULTSONIC_PRIVATE_H_

/**
 * @brief Function to be set as input capture ISR.
 */
static void ULTSONIC_voidCaptureISR(void);

/**
 * @brief Function to be set as overflow ISR.
 */
static void ULTSONIC_voidOvfISR(void);

#endif

