/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: TIMERS_register.h		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file TIMERS_register.h
 * @author Ibrahim Tarek
 * @brief This file contains TIMERS module registers' memory locations.
 * @version 1.00
 */

#ifndef TIMERS_REGISTER_H_
#define TIMERS_REGISTER_H_

#define TCCR0               *((volatile uint8 *) 0x53)  /*Timer/Counter 0 Control Register*/
#define TCCR0_CS00          0u                          //Clock Select for Timer/Counter 0 Bit 0
#define TCCR0_CS01          1u                          //Clock Select for Timer/Counter 0 Bit 1
#define TCCR0_CS02          2u                          //Clock Select for Timer/Counter 0 Bit 2
#define TCCR0_WGM01         3u                          //Wave Generation Mode for Timer/Counter 0 Bit 1
#define TCCR0_COM00         4u                          //Compare Match Output Mode for Timer/Counter 0 Bit 0
#define TCCR0_COM01         5u                          //Compare Match Output Mode for Timer/Counter 0 Bit 1
#define TCCR0_WGM00         6u                          //Wave Generation Mode for Timer/Counter 0 Bit 0
#define TCCR0_FOC0          7u                          //Force Output Compare for Timer/Counter 0

#define TCNT0               *((volatile uint8 *) 0x52)  /*Timer/Counter 0 Register*/

#define OCR0                *((volatile uint8 *) 0x5C)  /*Output Compare Register for Timer/Counter 0*/

#define TIMSK               *((volatile uint8 *) 0x59)  /*Timer/Counter Interrupt Mask Register*/
#define TIMSK_TOIE0         0u                          //Timer/Counter 0 Overflow Interrupt Enable
#define TIMSK_OCIE0         1u                          //Timer/Counter 0 Output Compare Match Interrupt Enable
#define TIMSK_TOIE1			2u							//Timer/Counter 1 Overflow Interrupt Enable
#define TIMSK_OCIE1B		3u							//Timer/Counter 1 Output Compare B Match Interrupt Enable
#define TIMSK_OCIE1A		4u							//Timer/Counter 1 Output Compare A Match Interrupt Enable
#define TIMSK_TICIE1		5u							//Timer/Counter 1 Input Capture Interrupt Enable
#define TIMSK_TOIE2			6u							//Timer/Counter 2 Overflow Interrupt Enable
#define TIMSK_OCIE2			7u							//Timer/Counter 2 Output Compare Match Interrupt Enable


#define TCCR1A				*((volatile uint8 *) 0x4F)	/*Timer/Counter 1 Control Register A*/
#define TCCR1A_WGM10		0u							//Wave Generation Mode for Timer/Counter 1 Bit 0
#define TCCR1A_WGM11		1u							//Wave Generation Mode for Timer/Counter 1 Bit 1
#define TCCR1A_FOC1B		2u							//Force Output Compare for Timer/Counter 1 Compare Unit B
#define TCCR1A_FOC1A		3u							//Force Output Compare for Timer/Counter 1 Compare Unit A
#define TCCR1A_COM1B0		4u							//Compare Match Output Mode for Timer/Counter 1 Compare Unit B Bit 0
#define TCCR1A_COM1B1		5u							//Compare Match Output Mode for Timer/Counter 1 Compare Unit B Bit 1
#define TCCR1A_COM1A0		6u							//Compare Match Output Mode for Timer/Counter 1 Compare Unit A Bit 0
#define TCCR1A_COM1A1		7u							//Compare Match Output Mode for Timer/Counter 1 Compare Unit A Bit 1

#define TCCR1B				*((volatile uint8 *) 0x4E)	/*Timer/Counter 1 Control Register B*/
#define TCCR1B_CS10			0u							//Clock Select for Timer/Counter 1 Bit 0
#define TCCR1B_CS11			1u							//Clock Select for Timer/Counter 1 Bit 1
#define TCCR1B_CS12			2u							//Clock Select for Timer/Counter 1 Bit 2
#define TCCR1B_WGM12		3u							//Wave Generation Mode for Timer/Counter 1 Bit 2
#define TCCR1B_WGM13		4u							//Wave Generation Mode for Timer/Counter 1 Bit 3
#define TCCR1B_R			5u							//Reserved Bit
#define TCCR1B_ICES1		6u							//Input Capture Noise Canceler for Timer/Counter 1
#define TCCR1B_ICNC1		7u							//Input Capture Edge Select for Timer/Counter 1

#define TCNT1				*((volatile uint16 *) 0x4C)	/*Timer/Counter 1 Register*/

#define OCR1A				*((volatile uint16 *) 0x4A)	/*Output Compare Register for Timer/Counter 1 Compare Unit A*/

#define OCR1B				*((volatile uint16 *) 0x48)	/*Output Compare Register for Timer/Counter 1 Compare Unit B*/

#define ICR1				*((volatile uint16 *) 0x46)	/*Input Capture Register for Timer/Counter 1*/

#define TCCR2				*((volatile uint8 *) 0x45)	/*Timer/Counter 2 Control Register*/
#define TCCR2_CS20          0u                          //Clock Select for Timer/Counter 2 Bit 0
#define TCCR2_CS21          1u                          //Clock Select for Timer/Counter 2 Bit 1
#define TCCR2_CS22          2u                          //Clock Select for Timer/Counter 2 Bit 2
#define TCCR2_WGM21         3u                          //Wave Generation Mode for Timer/Counter 2 Bit 1
#define TCCR2_COM20         4u                          //Compare Match Output Mode for Timer/Counter 2 Bit 0
#define TCCR2_COM21         5u                          //Compare Match Output Mode for Timer/Counter 2 Bit 1
#define TCCR2_WGM20         6u                          //Wave Generation Mode for Timer/Counter 2 Bit 0
#define TCCR2_FOC2          7u                          //Force Output Compare for Timer/Counter 2

#define TCNT2               *((volatile uint8 *) 0x44)  /*Timer/Counter 2 Register*/

#define OCR2                *((volatile uint8 *) 0x43)  /*Output Compare Register for Timer/Counter 2*/

#define WDTCR				*((volatile uint8 *) 0x41)	/*WatchDog Timer Control Register*/
#define WDTCR_WDP0			0u							//WatchDog Timer Prescaler Bit 0
#define WDTCR_WDP1			1u							//WatchDog Timer Prescaler Bit 1
#define WDTCR_WDP2			2u							//WatchDog Timer Prescaler Bit 2
#define WDTCR_WDE			3u							//WatchDog Enable
#define WDTCR_WDTOE			4u							//WatchDog Turn-off Enable

#endif
