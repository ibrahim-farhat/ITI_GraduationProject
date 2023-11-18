/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: ULTSONIC_interface.h	**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file ULTSONIC_interface.h
 * @author Ibrahim Tarek
 * @brief This file interfaces the ULTSONIC sensor module functions.
 * @version 1.00
 */

#ifndef ULTSONIC_INTERFACE_H_
#define ULTSONIC_INTERFACE_H_

/**
 * @brief 			Struct type to configure the ultratsonic information.
 * @param TrigPort	Port number to which ultrasonic is connected.
 * @param TrigPin	Pin number to which ultrasonic is connected.
 */
typedef struct
{
	uint8 TrigPort;
	uint8 TrigPin;
}
ULTSONIC_t;

/**
 * @brief 						Function to measure the distance with ultrasonic using input capture unit of timer 1.
 * @param Copy_pstUltsonicData 	Pointer to struct that carry the ultrasonic data.
 * @param Copy_pu16Distance 	Pointer to return the distance in CM.
 * @return 						Error State.
 */
uint8 ULTSONIC_u8MeasureDistance(const ULTSONIC_t *Copy_pstUltsonicData, uint16 *Copy_pu16Distance);

#endif
