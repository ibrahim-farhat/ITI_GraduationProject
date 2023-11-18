/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: USART_private.h		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file USART_private.h
 * @author Ibrahim Tarek
 * @brief This file contains USART module private defines.
 * @version 1.00
 */

#ifndef USART_PRIVATE_H_
#define USART_PRIVATE_H_

/*Masks*/
#define CHAR_SIZE_MASK				0b11111001


/*USART_u8CHAR_SIZE Options*/
#define FIVE_BITS_CHAR_SIZE			1u
#define SIX_BITS_CHAR_SIZE			2u
#define SEVEN_BITS_CHAR_SIZE		3u
#define EIGHT_BITS_CHAR_SIZE		4u
#define NINE_BITS_CHAR_SIZE			5u

/*USART_u8SYNCH_MODE Options*/
#define	SYNCHRONOUS_MODE			1u
#define ASYNCHRONOUS_MODE			2u

/*USART_u8PARITY_MODE Options*/
#define EVEN_PARITY					1u
#define ODD_PARITY					2u

/*USART_u8STOP_BITS_NUM Options*/
#define ONE_BIT						1u
#define TWO_BITS					2u

/*USART_u8BAUD_RATE Options*/
#define BAUD_RATE_2400				207u
#define	BAUD_RATE_4800				103u
#define BAUD_RATE_9600				51u
#define BAUD_RATE_14e4K				34u
#define BAUD_RATE_19e2K				25u
#define BAUD_RATE_28e8K				16u
#define BAUD_RATE_38e4K				12u
#define BAUD_RATE_57e6K				8u
#define BAUD_RATE_76e8K				6u
#define BAUD_RATE_115e2K			3u
#define BAUD_RATE_230e4K			1u
#define	BAUD_RATE_250K				1u
#define	BAUD_RATE_0e5M				0u

/*USART_u8TransmitCallSrc, USART_u8ReceiveCallSrc Options*/
#define MAIN_CALL					0U
#define SYNCH_FUNC_CALL				1u

#endif
