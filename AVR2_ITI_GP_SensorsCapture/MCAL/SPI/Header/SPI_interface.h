/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: SPI_interface.h		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file SPI_interface.h
 * @author Ibrahim Tarek
 * @brief This file interfaces the SPI module functions.
 * @version 1.00
 */

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

/**
 * @brief Function to initialize the SPI peripheral with prebuild configurations.
 */
void SPI_voidInit(void);

/**
 * @brief 				Function to transfer and receive data with SPI peripheral.
 * @param Copy_u8Data	The Transmitting data.
 * @return				The Received Data.
 */
uint8 SPI_u8Transceive(uint8 Copy_u8Data);

#endif
