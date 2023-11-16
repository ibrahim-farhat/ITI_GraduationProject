/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: SPI_register.h		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file SPI_register.h
 * @author Ibrahim Tarek
 * @brief This file contains SPI module registers' memory locations.
 * @version 1.00
 */

#ifndef SPI_REGISTER_H_
#define SPI_REGISTER_H_

#define SPCR			*((volatile uint8 *) 0x2D)	/*SPI Control Register*/
#define SPCR_SPR0		0u							//SPI Clock Rate Select Bit 0
#define SPCR_SPR1		1u							//SPI Clock Rate Select Bit 1
#define SPCR_CPHA		2u							//Clock Phase
#define SPCR_CPOL		3u							//Clock Polarity
#define SPCR_MSTR		4u							//Master/Slave Select
#define SPCR_DORD		5u							//Data Order
#define SPCR_SPE		6u							//SPI Enable
#define SPCR_SPIE		7u							//SPI Interrupt Enable

#define SPSR			*((volatile uint8 *) 0x2E)	/*SPI Status Register*/
#define SPSR_SPIF		7u							//SPI Interrupt Flag
#define SPSR_WCOL		6u							//Write Collision Flag
#define SPSR_SPI2X		0u							//Double SPI Speed Bit

#define SPDR			*((volatile uint8 *) 0x2F)	/*SPI Data Register*/

#endif
