/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: MCP2515_interface.h	**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file MCP2515_interface.h
 * @author Ibrahim Tarek
 * @brief This file interfaces the MCP2515 module functions.
 * @version 1.00
 */

#ifndef MCP2515_INTERFACE_H_
#define MCP2515_INTERFACE_H_

typedef struct
{
    uint32 id;     // CAN message identifier
    uint8 data[8]; // Data payload
    uint8 length;  // Data length (0-8)
    uint8 properties; // Message properties, including the RTR bit (bit 6)
}
MCP2515_CanMessage_t;

uint8 MCP2515_u8ReadRegister(uint8 Copy_u8Address);
void MCP2515_voidWriteRegister(uint8 Copy_u8Address, uint8 Copy_u8Value);
void MCP2515_voidSetBitTiming(uint8 Copy_u8CNF1Value, uint8 Copy_u8CNF2Value, uint8 Copy_u8CNF3Value);
void MCP2515_voidReset(void);
void MCP2515_voidChangeBits(uint8 Copy_u8RegAddress, uint8 Copy_u8Mask, uint8 Copy_u8Value);
void MCP2515_voidSetMode(uint8 Copy_u8Mode);
void MCP2515_voidSendInit(void);
void MCP2515_voidSendCANmsg(MCP2515_CanMessage_t Copy_stMessage);
void MCP2515_voidSetRollover(uint8 Copy_u8Value);
void MCP2515_voidSetMask(uint8 Copy_u8MaskAddress, uint32 Copy_u32MaskValue, uint8 Copy_u8Extended);
void MCP2515_voidReceiveInit(void);
MCP2515_CanMessage_t MCP2515_stReceiveCANmsg(void);
void MCP2515_voidReceiveCANmsg2(void);

//uint8 MCP2515_U8ReadRegister(uint8 address);
//void MCP2515_VidWriteRegister(uint8 address, uint8 value);
//void MCP2515_VidSetBitTiming(uint8 cnf1Value, uint8 cnf2Value, uint8 cnf3Value);
//void MCP2515_VidReset();
//void MCP2515_VidChangeBits(uint8 RegAddress, uint8 Mask, uint8 Value);
//void MCP2515_VidSetMode(uint8 mode);
//void MCP2515_VidInit(void);
//void MCP2515_VidSendCANmsg(MCP2515_CanMessage_t Copy_stMessage);
//MCP2515_CanMessage_t MCP2515_VidReceiveCANmsg(void);
//void MCP2515_VidReceiveInit(void);
//void MCP2515_VidReceiveCANmsg2(void);


#define MCP2515_MODE_NORMAL			0x0
#define MCP2515_MODE_SLEEP			0x1
#define MCP2515_MODE_LOOPBACK		0x2
#define MCP2515_MODE_LISTEN_ONLY	0x3
#define MCP2515_MODE_CONFG			0x4

#endif
