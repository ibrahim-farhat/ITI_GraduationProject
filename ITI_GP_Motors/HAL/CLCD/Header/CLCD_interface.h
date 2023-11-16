/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: CLCD_interface.h		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file CLCD_interface.h
 * @author Ibrahim Tarek
 * @brief This file interfaces the CLCD module functions.
 * @version 1.00
 */

#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_

/**
 * @brief Function to send command order to the CLCD.
 * @param Copy_u8Cmd Parameter which take the number of the command as 1 byte
 */
void CLCD_voidSendCmd(uint8 Copy_u8Cmd);

/**
 * @brief Function to send data to the CLCD.
 * @param Copy_c8Data Parameter which take 1 byte data to be set.
 */
void CLCD_voidSendData(char Copy_u8Data);

/**
 * @brief Function to send string to be printed on the CLCD.
 * @param Copy_ch8String Pointer to the string which needed to be printed.
 * @return Error State
 */
uint8 CLCD_u8SendString(const char *Copy_ch8String);

/**
 * @brief Function to print a decimal number into the CLCD.
 * @param Copy_s32Number Number wanted to be printed.
 */
void CLCD_voidSendDecimalNumber(sint32 Copy_s32Number);

/**
 * @brief Function that takes decimal number and print its binary representation into the CLCD.
 * @param Copy_s16Number Number wanted to be printed.
 */
void CLCD_voidSendBinaryNumber(sint16 Copy_s16Number);

/**
 * @brief Function that takes decimal number and print its hexadecimal representation into the CLCD.
 * @param Copy_s32Number Number wanted to be printed.
 */
void CLCD_voidSendHexaNumber(sint32 Copy_s32Number);

/**
 * @brief Function to print a special character into the CLCD.
 * @param Copy_pu8Pattern Pointer to the array that represent the pattern of a special character.
 * @param Copy_u8PatternNum Number that represent the memory location of the special character.
 * @param Copy_u8XPos X position to print the special character.
 * @param Copy_u8YPos Y position to print the special character.
 */
void CLCD_voidSendSpecialCharacter(uint8 *Copy_pu8PatternArr, uint8 Copy_u8PatternNum, uint8 Copy_u8XPos, uint8 Copy_u8YPos);

/**
 * @brief Function to initialize the CLCD according to its configurations.
 */
void CLCD_voidInit(void);

/**
 * @brief Function to clear the display.
 */
void CLCD_voidClearDisplay(void);

/**
 * @brief Function to move the cursor to a particular position.
 * @param Copy_u8XPos X position of the new particular position.
 * @param Copy_u8YPos Y position of the new particular position.
 * @return Error state.
 */
uint8 CLCD_u8GoToXY(uint8 Copy_u8XPos, uint8 Copy_u8YPos);

#endif
