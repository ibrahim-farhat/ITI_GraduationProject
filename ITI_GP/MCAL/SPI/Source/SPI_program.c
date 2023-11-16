/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: SPI_program.c			**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file SPI_program.c
 * @author Ibrahim Tarek
 * @brief This file implements the SPI module functions.
 * @version 1.00
 */

#include "../../../Common/STD_TYPES.h"
#include "../../../Common/BIT_MATH.h"
#include "../../../Common/DEFINES.h"

#include "../Header/SPI_interface.h"
#include "../Header/SPI_config.h"
#include "../Header/SPI_private.h"
#include "../Header/SPI_register.h"

/**
 * @brief Function to initialize the SPI peripheral with prebuild configurations.
 */
void SPI_voidInit(void)
{
	/*Set the data order bit*/
#if SPI_u8DATA_TRANSCEIVE_ORDER == MSB_FIRST
	CLR_BIT(SPCR,SPCR_DORD);

#elif SPI_u8DATA_TRANSCEIVE_ORDER == LSB_FIRST
	SET_BIT(SPCR,SPCR_DORD);

#else
#error Wrong SPI_u8DATA_TRANSCEIVE_ORDER Configuration Choise.
#endif

	/*Set the SPI node mode*/
#if SPI_u8MODE == MASTER
	SET_BIT(SPCR,SPCR_MSTR);

#elif SPI_u8MODE == SLAVE
	CLR_BIT(SPCR,SPCR_MSTR);

#else
#error Wrong SPI_u8MODE Configuration Choise.
#endif

	/*Set the SPI clock polarity*/
#if SPI_u8IDLE_STATE == LOW_VOLTAGE
	CLR_BIT(SPCR,SPCR_CPOL);

#elif SPI_u8IDLE_STATE == HIGH_VOLTAGE
	SET_BIT(SPCR,SPCR_CPOL);

#else
#error Wrong SPI_u8IDLE_STATE Configuration Choise.
#endif

	/*Set the SPI clock phase*/
#if SPI_u8MODE == MASTER
	SPCR &= CLOCK_PRESCALER_MASK;
	SPCR |= SPI_u8CLOCK_PRESCALER;

	/*Set the SPI double clock rate speed bit*/
#if SPI_u8DOUBLE_SPEED == ENABLED
	SET_BIT(SPSR,SPSR_SPI2X);

#elif SPI_u8DOUBLE_SPEED == DISABLED
	CLR_BIT(SPSR,SPSR_SPI2X);

#else
#error Wrong SPI_u8DOUBLE_SPEED Configuration Choise.
#endif

#endif

	/*Enable SPI Peripheral*/
	SET_BIT(SPCR,SPCR_SPE);
}

/**
 * @brief 				Function to transfer and receive data with SPI peripheral.
 * @param Copy_u8Data	The Transmitting data.
 * @return				The Received Data.
 */
uint8 SPI_u8Transceive(uint8 Copy_u8Data)
{
	/*Set the transmitting data*/
	SPDR = Copy_u8Data;

	/*Polling until the data is transceived*/
	while((GET_BIT(SPSR,SPSR_SPIF)) == 0);

	/*Return the received data*/
	return SPDR;
}
