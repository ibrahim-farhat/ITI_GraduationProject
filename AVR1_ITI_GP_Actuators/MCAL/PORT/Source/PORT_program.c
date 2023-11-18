/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: PORT_program.c		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file PORT_program.c
 * @author Ibrahim Tarek
 * @brief This file implements the PORT module functions.
 * @version 1.00
 */

#include "../../../Common/STD_TYPES.h"
#include "../../../Common/BIT_MATH.h"
#include "../../../Common/DEFINES.h"

#include "../Header/PORT_config.h"
#include "../Header/PORT_interface.h"
#include "../Header/PORT_private.h"
#include "../Header/PORT_register.h"

/**
 * @brief Function to initialize all DIO pins (direction and value).
 */
void PORT_voidInit(void)
{
	/*Assign directions into DDR registers*/
	DDRA = PORTA_DIR;
	DDRB = PORTB_DIR;
	DDRC = PORTC_DIR;
	DDRD = PORTD_DIR;

	/*Assign values into PORT registers*/
	PORTA = PORTA_INITIAL_VALUE;
	PORTB = PORTB_INITIAL_VALUE;
	PORTC = PORTC_INITIAL_VALUE;
	PORTD = PORTD_INITIAL_VALUE;
}
