/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: CLCD_program.c		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file CLCD_program.c
 * @author Ibrahim Tarek
 * @brief This file implements the CLCD module functions.
 * @version 1.00
 */

#include "../../../Common/STD_TYPES.h"
#include "../../../Common/BIT_MATH.h"
#include "../../../Common/DEFINES.h"

#include "../../../MCAL/DIO/Header/DIO_interface.h"

#include <util/delay.h>

#include "../Header/CLCD_config.h"
#include "../Header/CLCD_interface.h"
#include "../Header/CLCD_private.h"

/**
 * @brief Function to send enable pulse into the enable pin of the CLCD.
 */
static void voidSendEnablePulse(void)
{
	/*Send enable pulse*/
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT, CLCD_u8E_PIN, DIO_u8PIN_HIGH);

	/*Delay for 2 millisecond, it is enough time for lcd to implement any command*/
	_delay_ms(2);

	/*Clear enable*/
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT, CLCD_u8E_PIN, DIO_u8PIN_LOW);
}

#if CLCD_OP_MODE == FOUR_BIT_MODE
/**
 * @brief Function to set a nipple into the half data port.
 * @param Copy_u8Nipple
 */
static void voidSetLCDHalfDataPort(uint8 Copy_u8Nipple)
{
	DIO_u8SetPinValue(CLCD_u8DATA_PORT, CLCD_u8D4_PIN, GET_BIT(Copy_u8Nipple, 0));
	DIO_u8SetPinValue(CLCD_u8DATA_PORT, CLCD_u8D5_PIN, GET_BIT(Copy_u8Nipple, 1));
	DIO_u8SetPinValue(CLCD_u8DATA_PORT, CLCD_u8D6_PIN, GET_BIT(Copy_u8Nipple, 2));
	DIO_u8SetPinValue(CLCD_u8DATA_PORT, CLCD_u8D7_PIN, GET_BIT(Copy_u8Nipple, 3));
}
#endif

/**
 * @brief Function to send command order to the CLCD.
 * @param Copy_u8Cmd Parameter which take the number of the command as 1 byte
 */
void CLCD_voidSendCmd(uint8 Copy_u8Cmd)
{
	/*Set RS pin to low for command*/
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT, CLCD_u8RS_PIN, DIO_u8PIN_LOW);

	/*Set RW pin to low for write operation*/
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT, CLCD_u8RW_PIN, DIO_u8PIN_LOW);

#if CLCD_OP_MODE == EIGHT_BIT_MODE
	/*Set the command on data pins*/
	DIO_u8SetPortValue(CLCD_u8DATA_PORT, Copy_u8Cmd);
	/*Send Enable Pulse to lcd*/
	voidSendEnablePulse();

#elif CLCD_OP_MODE == FOUR_BIT_MODE
	/*Set the most 4 bits on data pins*/
	voidSetLCDHalfDataPort(Copy_u8Cmd >> 4);
	/*Send Enable Pulse to lcd*/
	voidSendEnablePulse();
	/*Set the least 4 bits on data pins*/
	voidSetLCDHalfDataPort(Copy_u8Cmd);
	/*Send Enable Pulse to lcd*/
	voidSendEnablePulse();

#endif

}

/**
 * @brief Function to send data to the CLCD.
 * @param Copy_c8Data Parameter which take 1 byte data to be set.
 */
void CLCD_voidSendData(char Copy_u8Data)
{

	/*Set RS pin to high for data*/
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT, CLCD_u8RS_PIN, DIO_u8PIN_HIGH);

	/*Set RW pin to low for write operation*/
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT, CLCD_u8RW_PIN, DIO_u8PIN_LOW);

#if CLCD_OP_MODE == EIGHT_BIT_MODE
	/*Set the data on data pins*/
	DIO_u8SetPortValue(CLCD_u8DATA_PORT, Copy_u8Data);
	/*Send Enable Pulse to lcd*/
	voidSendEnablePulse();

#elif CLCD_OP_MODE == FOUR_BIT_MODE
	/*Set the most 4 bits on data pins*/
	voidSetLCDHalfDataPort(Copy_u8Data >> 4);
	/*Send Enable Pulse to lcd*/
	voidSendEnablePulse();
	/*Set the least 4 bits on data pins*/
	voidSetLCDHalfDataPort(Copy_u8Data);
	/*Send Enable Pulse to lcd*/
	voidSendEnablePulse();

#endif
}

/**
 * @brief Function to initialize the CLCD according to its configurations.
 */
void CLCD_voidInit(void)
{
	/*Define variable to carry a command*/
	uint8 Local_u8Command;

	/*Wait for more than 30ms after power on*/
	_delay_ms(40);

	/*Function set command: 2 lines, and font size is 5x7 as default*/
#if	CLCD_OP_MODE == EIGHT_BIT_MODE
	Local_u8Command = 0b00111000;

	/*If the font is configured by 5x11 change it*/
#if CLCD_FONT_SIZE == FONT_5x11
	SET_BIT(Local_u8Command, 2);
#endif

	/*Send the command*/
	CLCD_voidSendCmd(Local_u8Command);

#elif CLCD_OP_MODE == FOUR_BIT_MODE
	CLCD_voidSendCmd(0b00100010);

	/*If the font is configured by 5x11 change it*/
#if CLCD_FONT_SIZE == FONT_5x11
	voidSetLCDHalfDataPort(0b1100);
#else
	voidSetLCDHalfDataPort(0b1000);
#endif

	voidSendEnablePulse();
#endif

	/*Display on/off control: display, cursor and blink (Enable/Disable)*/
	Local_u8Command = 0b00001100;
#if CLCD_CURSOR_DISPLAY == ENABLED
	SET_BIT(Local_u8Command, 1);
#endif
#if CLCD_CURSOR_BLINK == ENABLED
	SET_BIT(Local_u8Command, 0);
#endif
	CLCD_voidSendCmd(Local_u8Command);

	/*Display Clear command*/
	CLCD_voidSendCmd(0b00000001);

	/*Entry mode set command*/
	CLCD_voidSendCmd(0b00000110);
}

/**
 * @brief Function to clear the display.
 */
void CLCD_voidClearDisplay(void)
{
	CLCD_voidSendCmd(0x01);
}

/**
 * @brief Function to send string to be printed on the CLCD.
 * @param Copy_ch8String Pointer to the string which needed to be printed.
 * @return Error State
 */
uint8 CLCD_u8SendString(const char *Copy_ch8String)
{
	uint8 Local_u8ErrorState = OK;

	uint8 Local_u8Counter = 0;

	if(Copy_ch8String != NULL)
	{
		while(Copy_ch8String[Local_u8Counter] != '\0')
		{
			CLCD_voidSendData(Copy_ch8String[Local_u8Counter]);
			Local_u8Counter++;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}

/**
 * @brief Function to print a decimal number into the CLCD.
 * @param Copy_s32Number Number wanted to be printed.
 */
void CLCD_voidSendDecimalNumber(sint32 Copy_s32Number)
{
	char Local_ch8Digit[10] = {0};

	uint8 Local_u8ReverseCounter = 0u;
	uint8 Local_u8PrintCounter;

	if(Copy_s32Number == 0)
	{
		CLCD_voidSendData('0');
	}
	else
	{
		/*Check for the negative sign*/
		if(Copy_s32Number < 0)
		{
			/*Print the negative sign to the lcd*/
			CLCD_voidSendData('-');

			/*Change the sign of the number*/
			Copy_s32Number = Copy_s32Number * -1;
		}

		/*Extracting the number digits into array of characters*/
		while(Copy_s32Number > 0)
		{
			/*
			 * Extract every digit number to the array of characters,
			 * then translate it into ascii value through adding '0'
			 */
			Local_ch8Digit[Local_u8ReverseCounter] = (char) (Copy_s32Number % 10);
			Local_ch8Digit[Local_u8ReverseCounter] = Local_ch8Digit[Local_u8ReverseCounter] + '0';

			Copy_s32Number = Copy_s32Number / 10;
			Local_u8ReverseCounter++;
		}

		/*Printing every character in the array until the end of the number*/
		Local_u8PrintCounter = Local_u8ReverseCounter;
		do
		{
			CLCD_voidSendData(Local_ch8Digit[Local_u8PrintCounter - 1u]);
			Local_u8PrintCounter--;
		}
		while(Local_u8PrintCounter > 0u);
	}
}

/**
 * @brief Function that takes decimal number and print its binary representation into the CLCD.
 * @param Copy_s16Number Number wanted to be printed.
 */
void CLCD_voidSendBinaryNumber(sint16 Copy_s16Number)
{
	uint8 Local_u8BinaryDigits[32] = {0u};

	uint8 Local_u8ReverseCounter = 0u;
	uint8 Local_u8PrintCounter;

	/*Print 0b before the binary representation*/
	CLCD_u8SendString("0b");

	/*Loading zeros and ones into array of characters*/
	for(Local_u8ReverseCounter = 0; Local_u8ReverseCounter < 16; Local_u8ReverseCounter++)
	{
		if((Copy_s16Number & 1) == 1)
		{
			Local_u8BinaryDigits[Local_u8ReverseCounter] = 1u;
		}
		else
		{
			Local_u8BinaryDigits[Local_u8ReverseCounter] = 0u;
		}
		Copy_s16Number = Copy_s16Number >> 1;
	}

	/*Go to the next line in the lcd*/
	CLCD_u8GoToXY(0,1);

	/*Printing every character in the array until the end of the number*/
	Local_u8PrintCounter = 16;
	do
	{
		if(Local_u8BinaryDigits[Local_u8PrintCounter - 1] == 0)
		{
			CLCD_voidSendData('0');
		}
		else
		{
			CLCD_voidSendData('1');
		}

		Local_u8PrintCounter--;
	}
	while(Local_u8PrintCounter > 0);
}

/**
 * @brief Function that takes decimal number and print its hexadecimal representation into the CLCD.
 * @param Copy_s32Number Number wanted to be printed.
 */
void CLCD_voidSendHexaNumber(sint32 Copy_s32Number)
{
	/*Define Variables*/
	char Local_ch8HexaTable[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
									'A', 'B', 'C', 'D', 'E', 'F'};
	uint8 Local_u8HexaDigits[8];
	sint8 Local_s8PrintCounter;
	uint8 Local_u8ReverseCounter;
	uint8 Local_u8LeastFourBits;
	uint8 Local_u8PrintTemp;

	/*Load the Hexadecimal digits into array of characters*/
	for(Local_u8ReverseCounter = 0u; Local_u8ReverseCounter < 8u; Local_u8ReverseCounter++)
	{
		/*Get the least for bits of the number*/
		Local_u8LeastFourBits = Copy_s32Number & 0x0f;
		Copy_s32Number = Copy_s32Number >> 4;

		Local_u8HexaDigits[Local_u8ReverseCounter] = Local_u8LeastFourBits;
	}

	/*Print 0x before Hexadecimal representation*/
	CLCD_u8SendString("0x");

	/*Print the hexadecimal number from array of hexadecimal table*/
	for(Local_s8PrintCounter = 7; Local_s8PrintCounter >= 0; Local_s8PrintCounter--)
	{
		Local_u8PrintTemp = Local_u8HexaDigits[Local_s8PrintCounter];
		CLCD_voidSendData(Local_ch8HexaTable[Local_u8PrintTemp]);
	}
}

/**
 * @brief Function to print a special character into the CLCD.
 * @param Copy_pu8Pattern Pointer to the array that represent the pattern of a special character.
 * @param Copy_u8PatternNum Number that represent the memory location of the special character.
 * @param Copy_u8XPos X position to print the special character.
 * @param Copy_u8YPos Y position to print the special character.
 */
void CLCD_voidSendSpecialCharacter(uint8 *Copy_pu8PatternArr, uint8 Copy_u8PatternNum, uint8 Copy_u8XPos, uint8 Copy_u8YPos)
{
	/*Define Variables*/
	uint8 Local_u8CGRAMAdd = Copy_u8PatternNum * 8u;
	uint8 Local_u8Counter;

	/*Set bit 6 in CGRAMAdd for CGRAM Address command standard*/
	SET_BIT(Local_u8CGRAMAdd, 6);

	/*Send the address command to CLCD*/
	CLCD_voidSendCmd(Local_u8CGRAMAdd);

	/*Send the pattern to the CLCD*/
	for(Local_u8Counter = 0u; Local_u8Counter < 8u; Local_u8Counter++)
	{
		CLCD_voidSendData(Copy_pu8PatternArr[Local_u8Counter]);
	}

	/*Go to DDRAM Address to display the pattern*/
	CLCD_u8GoToXY(Copy_u8XPos, Copy_u8YPos);

	/*Display the pattern from CGRAM to DDRAM*/
	CLCD_voidSendData(Copy_u8PatternNum);
}

/**
 * @brief Function to move the cursor to a particular position.
 * @param Copy_u8XPos X position of the new particular position.
 * @param Copy_u8YPos Y position of the new particular position.
 * @return Error state.
 */
uint8 CLCD_u8GoToXY(uint8 Copy_u8XPos, uint8 Copy_u8YPos)
{
	uint8 Local_u8ErrorState = OK;

	uint8 Local_u8DDRamAdd;

	/*Configure the address of DDRam*/
	if(Copy_u8YPos == 0u)
	{
		Local_u8DDRamAdd = 0x00 + Copy_u8XPos;
	}
	else if(Copy_u8YPos == 1u)
	{
		Local_u8DDRamAdd = 0x40 + Copy_u8XPos;
	}
	else
	{
		Local_u8ErrorState = NOK;
	}

	/*Send DDRam Set Address command to lcd*/
	SET_BIT(Local_u8DDRamAdd,7);
	CLCD_voidSendCmd(Local_u8DDRamAdd);

	return Local_u8ErrorState;
}
