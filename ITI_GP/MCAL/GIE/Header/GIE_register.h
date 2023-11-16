/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: GIE_register.h		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file GIE_register.h
 * @author Ibrahim Tarek
 * @brief This file contains GIE module registers' memory locations.
 * @version 1.00
 */

#ifndef GIE_REGISTER_H_
#define GIE_REGISTER_H_

#define SREG			*((volatile uint8 *) 0x5F)	/*Status Register*/
#define SREG_I			7u							/*Interrupt Bit*/

#endif
