/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: SPI_config.h			**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file SPI_config.h
 * @author Ibrahim Tarek
 * @brief This file configures the SPI module in prebuild configuration method.
 * @version 1.00
 */

#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

/**
 * @details Configure the SPI First Data to transceive, Options: 1- MSB_FIRST
 * 																 2- LSB_FIRST
 */
#define SPI_u8DATA_TRANSCEIVE_ORDER			MSB_FIRST

/**
 * @details Configure the SPI Mode, Options: 1- MASTER
 * 											 2- SLAVE
 */
#define SPI_u8MODE							MASTER

/**
 * @details Configure the SPI clock polarity, Options: 1- LOW_VOLTAGE
 * 											 		   2- HIGH_VOLTAGE
 */
#define SPI_u8IDLE_STATE					LOW_VOLTAGE

/**
 * @details Configure the SPI clock phase, Options: 1- SAMPLE_FIRST
 * 											 		2- SETUP_FIRST
 */
#define SPI_u8CLOCK_PHASE					SAMPLE_FIRST

/**
 * @details Configure the SPI clock rate, Options: 1- SYS_FREQ_BY_4
 * 											 	   2- SYS_FREQ_BY_16
 * 											 	   3- SYS_FREQ_BY_64
 * 											 	   4- SYS_FREQ_BY_128
 */
#define SPI_u8CLOCK_PRESCALER				SYS_FREQ_BY_4

/**
 * @details Configure the SPI double speed, Options: 1- ENABLED
 * 											 	  	 2- DISABLED
 */
#define SPI_u8DOUBLE_SPEED					DISABLED


#endif
