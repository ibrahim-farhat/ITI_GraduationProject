/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: TIMERS_private.h		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file TIMERS_private.h
 * @author Ibrahim Tarek
 * @brief This file contains TIMERS module private defines.
 * @version 1.00
 */

#ifndef TIMERS_PRIVATE_H_
#define TIMERS_PRIVATE_H_

/*BITS' MASKS*/
#define PRESCALER_MASK			0b11111000
#define TIMER0_2_OCMATCH_MASK	0b11001111
#define TIMER1_OCMATCH_A_MASK	0b00111111
#define TIMER1_OCMATCH_B_MASK	0b11001111
#define TIMER1_WGM_MASK_A		0b11111100
#define TIMER1_WGM_MASK_B		0b11100111
#define WDT_PRESCALER_MASK		0b11111000

#endif
