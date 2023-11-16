/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: SPI_private.h			**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file SPI_private.h
 * @author Ibrahim Tarek
 * @brief This file contains SPI module private defines.
 * @version 1.00
 */

#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_

/*Masks*/
#define CLOCK_PRESCALER_MASK	0b11111100

/*SPI_u8DATA_TRANSCEIVE_ORDER Options*/
#define LSB_FIRST		1u
#define MSB_FIRST		2u

/*SPI_u8MODE Options*/
#define MASTER			1u
#define SLAVE			2u

/*SPI_u8IDLE_STATE Options*/
#define LOW_VOLTAGE		1u
#define HIGH_VOLTAGE	2u

/*SPI_u8CLOCK_PHASE Options*/
#define SAMPLE_FIRST	1u
#define SETUP_FIRST		2u

/*SPI_u8CLOCK_PRESCALER Options*/
#define SYS_FREQ_BY_4	0u
#define SYS_FREQ_BY_16	1u
#define SYS_FREQ_BY_64	2u
#define SYS_FREQ_BY_128	3u

#endif
