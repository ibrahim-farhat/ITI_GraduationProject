/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: USART_register.h		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file USART_register.h
 * @author Ibrahim Tarek
 * @brief This file contains USART module registers' memory locations.
 * @version 1.00
 */

#ifndef USART_REGISTER_H_
#define USART_REGISTER_H_

#define UDR               	*((volatile uint8 *) 0x2C)  /*UART I/O Data Register, Read/Write Register*/

#define UCSRA               *((volatile uint8 *) 0x2B)  /*UART Control and Status Register A*/
#define UCSRA_MPCM          0u  						//Multi Processor Communication Mode
#define UCSRA_U2X           1u  						//Double the USART Transmission Speed
#define UCSRA_PE           	2u  						//Parity Error
#define UCSRA_DOR           3u  						//Data OverRun
#define UCSRA_FE           	4u  						//Frame Error
#define UCSRA_UDRE          5u  						//USART Data Register Empty
#define UCSRA_TXC           6u  						//USART Transmit Complete
#define UCSRA_RXC           7u  						//USART Receive Complete

#define UCSRB               *((volatile uint8 *) 0x2A)  /*UART Control and Status Register B*/
#define UCSRB_TXB8         	0u  						//Transmit Data Bit 8
#define UCSRB_RXB8          1u  						//Receive Data Bit 8
#define UCSRB_UCSZ2         2u  						//Character Size Bit 2
#define UCSRB_TXEN          3u  						//TX Enable
#define UCSRB_RXEN          4u  						//RX Enable
#define UCSRB_UDRIE         5u  						//USART Data Register Empty Interrupt Enable
#define UCSRB_TXCIE         6u  						//TX Complete Interrupt Enable
#define UCSRB_RXCIE         7u  						//RX Complete Interrupt Enable

#define UCSRC               *((volatile uint8 *) 0x40)  /*UART Control and Status Register C*/
#define UCSRC_UCPOL        	0u  						//Clock Parity
#define UCSRC_UCSZ0         1u  						//Character Size Bit 0
#define UCSRC_UCSZ1         2u  						//Character Size Bit 1
#define UCSRC_USBS          3u  						//Stop Bit Select
#define UCSRC_UPM0			4u  						//Parity Mode Bit 0
#define UCSRC_UPM1	        5u  						//Parity Mode Bit 1
#define UCSRC_UMSEL         6u  						//USART Mode Select
#define UCSRC_URSEL         7u  						//Register Select Between UBRRH/UCSRC

#define UBRRH				*((volatile uint8 *) 0x40)	/*USART Baud Rate High Register */
#define UBRRH_URSEL			7u							//Register Select Between UBRRH/UCSRC

#define UBRRL               *((volatile uint8 *) 0x29) 	/*USART Baud Rate Low Register */

#endif
