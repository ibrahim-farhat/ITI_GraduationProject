/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: GIE_program.c			**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file GIE_program.c
 * @author Ibrahim Tarek
 * @brief This file implements the GIE module functions.
 * @version 1.00
 */

#include "../../../Common/STD_TYPES.h"
#include "../../../Common/BIT_MATH.h"
#include "../../../Common/DEFINES.h"

#include "../Header/GIE_interface.h"
#include "../Header/GIE_config.h"
#include "../Header/GIE_private.h"
#include "../Header/GIE_register.h"


/**
 * @brief Function to enable global interrupt.
 */
void GIE_voidEnable(void)
{
	/*Enable global interrupt with c code*/
	//SET_BIT(SREG,SREG_I);

	/*Enable global interrupt with inline assembly code*/
	__asm __volatile("SEI");
}

/**
 * @brief Function to disable global interrupt.
 */
void GIE_voidDisable(void)
{
	/*Disable global interrupt with c code*/
	//CLR_BIT(SREG,SREG_I);

	/*Disable global interrupt with inline assembly code*/
	__asm __volatile("CLI");
}
