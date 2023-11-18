/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: CLCD_config.h			**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file CLCD_config.h
 * @author Ibrahim Tarek
 * @brief This file configures the CLCD module in prebuild configuration method.
 * @version 1.00
 */

#ifndef CLCD_CONFIG_H_
#define CLCD_CONFIG_H_

/**
 * @details Configure the mode you want to work on with LCD,
 * 			Options are: 1- FOUR_BIT_MODE
 * 						 2- EI-GHT_BIT_MODE
 */
#define CLCD_OP_MODE			FOUR_BIT_MODE

/**
 * @details Configure the cursor display, Options: 1- ENABLED
 * 												   2- DISABLED
 */
#define CLCD_CURSOR_DISPLAY		DISABLED

/**
 * @details Configure the cursor Blinking, Options: 1- ENABLED
 * 												 	2- DISABLED
 */
#define CLCD_CURSOR_BLINK		DISABLED

/**
 * @details Configure the display font size, Options: 1- FONT_5x11
 * 												 	  2- FONT_5x8
 */
#define CLCD_FONT_SIZE			FONT_5x11

/**
 * @details Configure the port to connect control pins: CLCD_RS_PIN, CLCD_RW_PIN, CLCD_E_PIN,
 * 			Options are: 1- DIO_u8PORTA
 * 		 				 2- DIO_u8PORTB
 * 		 				 3- DIO_u8PORTC
 * 		 				 4- DIO_u8PORTD
 */
#define CLCD_u8CTRL_PORT	DIO_u8PORTA

/**
 * @details Configure pins to connect control pins: CLCD_RS_PIN, CLCD_RW_PIN, CLCD_E_PIN,
 * 			Options: 1- DIO_u8PIN0
 * 					 2- DIO_u8PIN1
 * 					 3- DIO_u8PIN2
 * 					 4- DIO_u8PIN3
 * 					 5- DIO_u8PIN4
 * 					 6- DIO_u8PIN5
 * 					 7- DIO_u8PIN6
 * 					 8- DIO_u8PIN7
 */
#define CLCD_u8RS_PIN		DIO_u8PIN0
#define CLCD_u8RW_PIN		DIO_u8PIN1
#define CLCD_u8E_PIN		DIO_u8PIN2

/**
 * @details Configure the port to connect data pins,
 * 			Options are: 1- DIO_u8PORTA
 * 		 				 2- DIO_u8PORTB
 * 		 				 3- DIO_u8PORTC
 * 		 				 4- DIO_u8PORTD
 */
#define CLCD_u8DATA_PORT	DIO_u8PORTA

/**
 * @details Configure pins to connect data pins (if FOUR_BIT_MODE is enabled): D4, D5, D6, D7,
 * 			Options: 1- DIO_u8PIN0
 * 					 2- DIO_u8PIN1
 * 					 3- DIO_u8PIN2
 * 					 4- DIO_u8PIN3
 * 					 5- DIO_u8PIN4
 * 					 6- DIO_u8PIN5
 * 					 7- DIO_u8PIN6
 * 					 8- DIO_u8PIN7
 */
#if CLCD_OP_MODE == FOUR_BIT_MODE
#define CLCD_u8D4_PIN		DIO_u8PIN3
#define CLCD_u8D5_PIN		DIO_u8PIN4
#define CLCD_u8D6_PIN		DIO_u8PIN5
#define CLCD_u8D7_PIN		DIO_u8PIN6
#endif

#endif
