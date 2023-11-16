/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: PORT_config.h			**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file PORT_config.h
 * @author Ibrahim Tarek
 * @brief This file initialize values of all the DIO pins in prebuild configuration method.
 * @version 1.00
 */

#ifndef PORT_CONFIG_H_
#define PORT_CONFIG_H_

/**
 * @details Configure the initial directions of PORTA pins, options: 1- INPUT
 * 																	 2- OUTPUT
 */
#define PORTA_PIN0_DIR		OUTPUT
#define PORTA_PIN1_DIR		OUTPUT
#define PORTA_PIN2_DIR		OUTPUT
#define PORTA_PIN3_DIR		OUTPUT
#define PORTA_PIN4_DIR		OUTPUT
#define PORTA_PIN5_DIR		OUTPUT
#define PORTA_PIN6_DIR		OUTPUT
#define PORTA_PIN7_DIR		OUTPUT

/**
 * @details Configure the initial directions of PORTB pins, options: 1- INPUT
 * 																	 2- OUTPUT
 */
#define PORTB_PIN0_DIR		OUTPUT
#define PORTB_PIN1_DIR		OUTPUT
#define PORTB_PIN2_DIR		OUTPUT
#define PORTB_PIN3_DIR		INPUT
#define PORTB_PIN4_DIR		OUTPUT
#define PORTB_PIN5_DIR		OUTPUT
#define PORTB_PIN6_DIR		INPUT
#define PORTB_PIN7_DIR		OUTPUT

/**
 * @details Configure the initial directions of PORTC pins, options: 1- INPUT
 * 																	 2- OUTPUT
 */
#define PORTC_PIN0_DIR		OUTPUT
#define PORTC_PIN1_DIR		OUTPUT
#define PORTC_PIN2_DIR		OUTPUT
#define PORTC_PIN3_DIR		OUTPUT
#define PORTC_PIN4_DIR		OUTPUT
#define PORTC_PIN5_DIR		OUTPUT
#define PORTC_PIN6_DIR		OUTPUT
#define PORTC_PIN7_DIR		OUTPUT

/**
 * @details Configure the initial directions of PORTD pins, options: 1- INPUT
 * 																	 2- OUTPUT
 */
#define PORTD_PIN0_DIR		INPUT
#define PORTD_PIN1_DIR		OUTPUT
#define PORTD_PIN2_DIR		INPUT
#define PORTD_PIN3_DIR		INPUT
#define PORTD_PIN4_DIR		OUTPUT
#define PORTD_PIN5_DIR		OUTPUT
#define PORTD_PIN6_DIR		INPUT
#define PORTD_PIN7_DIR		OUTPUT

/**
 * @details Configure the initial values of PORTA pins,
 *
 * 			If the pin is INPUT, options: 1- LOW
 * 										  2- HIGH
 *
 * 			If the pin is OUTPUT, options: 1- FLOATING
 * 										   2- INTERNAL_PULL_UP
 */
#define PORTA_PIN0_INITIAL_VALUE		FLOATING
#define PORTA_PIN1_INITIAL_VALUE		FLOATING
#define PORTA_PIN2_INITIAL_VALUE		FLOATING
#define PORTA_PIN3_INITIAL_VALUE		FLOATING
#define PORTA_PIN4_INITIAL_VALUE		FLOATING
#define PORTA_PIN5_INITIAL_VALUE		FLOATING
#define PORTA_PIN6_INITIAL_VALUE		FLOATING
#define PORTA_PIN7_INITIAL_VALUE		FLOATING

/**
 * @details Configure the initial values of PORTB pins,
 *
 * 			If the pin is INPUT, options: 1- LOW
 * 										  2- HIGH
 *
 * 			If the pin is OUTPUT, options: 1- FLOATING
 * 										   2- INTERNAL_PULL_UP
 */
#define PORTB_PIN0_INITIAL_VALUE		INTERNAL_PULL_UP
#define PORTB_PIN1_INITIAL_VALUE		INTERNAL_PULL_UP
#define PORTB_PIN2_INITIAL_VALUE		INTERNAL_PULL_UP
#define PORTB_PIN3_INITIAL_VALUE		INTERNAL_PULL_UP
#define PORTB_PIN4_INITIAL_VALUE		INTERNAL_PULL_UP
#define PORTB_PIN5_INITIAL_VALUE		INTERNAL_PULL_UP
#define PORTB_PIN6_INITIAL_VALUE		FLOATING
#define PORTB_PIN7_INITIAL_VALUE		INTERNAL_PULL_UP

/**
 * @details Configure the initial values of PORTC pins,
 *
 * 			If the pin is INPUT, options: 1- LOW
 * 										  2- HIGH
 *
 * 			If the pin is OUTPUT, options: 1- FLOATING
 * 										   2- INTERNAL_PULL_UP
 */
#define PORTC_PIN0_INITIAL_VALUE		LOW
#define PORTC_PIN1_INITIAL_VALUE		LOW
#define PORTC_PIN2_INITIAL_VALUE		LOW
#define PORTC_PIN3_INITIAL_VALUE		LOW
#define PORTC_PIN4_INITIAL_VALUE		LOW
#define PORTC_PIN5_INITIAL_VALUE		LOW
#define PORTC_PIN6_INITIAL_VALUE		LOW
#define PORTC_PIN7_INITIAL_VALUE		LOW

/**
 * @details Configure the initial values of PORTD pins,
 *
 * 			If the pin is INPUT, options: 1- LOW
 * 										  2- HIGH
 *
 * 			If the pin is OUTPUT, options: 1- FLOATING
 * 										   2- INTERNAL_PULL_UP
 */
#define PORTD_PIN0_INITIAL_VALUE		INTERNAL_PULL_UP
#define PORTD_PIN1_INITIAL_VALUE		INTERNAL_PULL_UP
#define PORTD_PIN2_INITIAL_VALUE		INTERNAL_PULL_UP
#define PORTD_PIN3_INITIAL_VALUE		INTERNAL_PULL_UP
#define PORTD_PIN4_INITIAL_VALUE		INTERNAL_PULL_UP
#define PORTD_PIN5_INITIAL_VALUE		INTERNAL_PULL_UP
#define PORTD_PIN6_INITIAL_VALUE		INTERNAL_PULL_UP
#define PORTD_PIN7_INITIAL_VALUE		INTERNAL_PULL_UP

#endif
