/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: DIO_register.h		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file DIO_register.h
 * @author Ibrahim Tarek
 * @brief This file contains DIO peripheral registers' memory locations.
 * @version 1.00
 */

#ifndef DIO_REGISTER_H_
#define DIO_REGISTER_H_

#define DDRA 	*((volatile uint8 *) 0x3A)		/*Port A Data Direction Register*/
#define DDRB 	*((volatile uint8 *) 0x37)		/*Port B Data Direction Register*/
#define DDRC 	*((volatile uint8 *) 0x34)		/*Port C Data Direction Register*/
#define DDRD 	*((volatile uint8 *) 0x31)		/*Port D Data Direction Register*/

#define PORTA 	*((volatile uint8 *) 0x3B)		/*Port A Data Register*/
#define PORTB 	*((volatile uint8 *) 0x38)		/*Port B Data Register*/
#define PORTC 	*((volatile uint8 *) 0x35)		/*Port C Data Register*/
#define PORTD 	*((volatile uint8 *) 0x32)		/*Port D Data Register*/

#define PINA 	*((volatile uint8 *) 0x39)		/*Port A Input Pins Register Address*/
#define PINB	*((volatile uint8 *) 0x36)		/*Port B Input Pins Register Address*/
#define PINC	*((volatile uint8 *) 0x33)		/*Port C Input Pins Register Address*/
#define PIND 	*((volatile uint8 *) 0x30)		/*Port D Input Pins Register Address*/

#endif
