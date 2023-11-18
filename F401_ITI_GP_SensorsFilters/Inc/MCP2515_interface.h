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
    uint32_t id;     // CAN message identifier
    uint8_t data[8]; // Data payload
    uint8_t length;  // Data length (0-8)
    uint8_t properties; // Message properties, including the RTR bit (bit 6)
}
MCP2515_CanMessage_t;

uint8_t MCP2515_u8ReadRegister(uint8_t Copy_u8Address);
void MCP2515_voidWriteRegister(uint8_t Copy_u8Address, uint8_t Copy_u8Value);
void MCP2515_VidSetBitTiming(uint8_t Copy_u8CNF1Value, uint8_t Copy_u8CNF2Value, uint8_t Copy_u8CNF3Value);
void MCP2515_voidReset(void);
void MCP2515_voidChangeBits(uint8_t Copy_u8RegAddress, uint8_t Copy_u8Mask, uint8_t Copy_u8Value);
void MCP2515_voidSetMode(uint8_t Copy_u8Mode);
void MCP2515_voidInit(void);
void MCP2515_voidSendCANmsg(MCP2515_CanMessage_t Copy_stMessage);
void MCP2515_voidSetRollover(uint8_t Copy_u8Value);
void MCP2515_voidSetMask(uint8_t Copy_u8MaskAddress, uint32_t Copy_u32MaskValue, uint8_t Copy_u8Extended);
void MCP2515_voidReceiveInit(void);
MCP2515_CanMessage_t MCP2515_stReceiveCANmsg(void);
void MCP2515_voidReceiveCANmsg2(void);

#define MCP2515_MODE_NORMAL			0x0
#define MCP2515_MODE_SLEEP			0x1
#define MCP2515_MODE_LOOPBACK		0x2
#define MCP2515_MODE_LISTEN_ONLY	0x3
#define MCP2515_MODE_CONFG			0x4

#endif
