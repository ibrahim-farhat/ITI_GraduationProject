/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: CLCD_private.h		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file CLCD_private.h
 * @author Ibrahim Tarek
 * @brief This file contains CLCD module private defines.
 * @version 1.00
 */

#ifndef CLCD_PRIVATE_H_
#define CLCD_PRIVATE_H_

/*CLCD_OP_MODE Options*/
#define EIGHT_BIT_MODE	1u
#define FOUR_BIT_MODE	2u

/*CLCD_CURSOR_DISPLAY, CLCD_CURSOR_BLINK Options*/
#define	ENABLED			1u
#define	DISABLED		2u

/*CLCD_FONT_SIZE Options*/
#define FONT_5x11		1u
#define FONT_5x8		2u

/**
 * @brief Function to send enable pulse into the enable pin of the CLCD.
 */
static void voidSendEnablePulse(void);

/**
 * @brief Function to set a nipple into the half data port.
 * @param Copy_u8Nipple
 */
#if CLCD_OP_MODE == FOUR_BIT_MODE
static void voidSetLCDHalfDataPort(uint8 Copy_u8Nipple);
#endif

#endif
