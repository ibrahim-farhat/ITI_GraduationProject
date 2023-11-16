/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: USART_config.h		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file USART_config.h
 * @author Ibrahim Tarek
 * @brief This file configures the USART module in prebuild configuration method.
 * @version 1.00
 */

#ifndef USART_CONFIG_H_
#define USART_CONFIG_H_



/**
 * @details Configure the USART character size, Options: 1- FIVE_BITS_CHAR_SIZE
 * 														 2- SIX_BITS_CHAR_SIZE
 * 														 3- SEVEN_BITS_CHAR_SIZE
 * 														 4- EIGHT_BITS_CHAR_SIZE
 * 														 5- NINE_BITS_CHAR_SIZE
 */
#define USART_u8CHAR_SIZE				EIGHT_BITS_CHAR_SIZE


/**
 * @details Configure the USART synchronization mode, Options: 1- SYNCHRONOUS_MODE
 * 											   				   2- ASYNCHRONOUS MODE
 */
#define USART_u8SYNCH_MODE				ASYNCHRONOUS_MODE


/**
 * @details Configure the USART parity mode, Options: 1- DISABLED
 * 													  2- EVEN_PARITY
 * 													  3- ODD_PARITY
 */
#define USART_u8PARITY_MODE				DISABLED


/**
 * @details Configure the USART stop bits number, Options: 1- ONE_BIT
 * 														   2- TWO_BITS
 */
#define USART_u8STOP_BITS_NUM			ONE_BIT


/**
 * @details Configure the USART baud rate,
 * 			All baud rates included are at system frequency of 8 MHz and Disable the Double Transmission Speed,
 * 			Options: 1- BAUD_RATE_2400
 * 					 2- BAUD_RATE_4800
 * 					 3- BAUD_RATE_9600
 * 					 4- BAUD_RATE_14.4K
 * 					 5- BAUD_RATE_19.2K
 * 					 6- BAUD_RATE_28.8K
 * 					 7- BAUD_RATE_38.4K
 * 					 8- BAUD_RATE_57.6K
 * 					 9- BAUD_RATE_76.8K
 * 					 10- BAUD_RATE_115.2K
 * 					 11- BAUD_RATE_230.4K
 * 					 12- BAUD_RATE_250K
 * 					 13- BAUD_RATE_0.5M
 */
#define USART_u8BAUD_RATE				BAUD_RATE_9600


/**
 * @details Configure the USART time out counter limit which used in Synchronous functions.
 */
#define USART_u32TIMEOUT				100000u
#endif
