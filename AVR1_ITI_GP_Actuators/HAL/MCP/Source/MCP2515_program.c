/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: MCP2515_program.c		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file MCP2515_program.c
 * @author Ibrahim Tarek
 * @brief This file implements the MCP2515 module functions.
 * @version 1.00
 */

#include "../../../Common/STD_TYPES.h"
#include "../../../Common/BIT_MATH.h"
#include "../../../Common/DEFINES.h"

#include "../../../MCAL/DIO/Header/DIO_interface.h"
#include "../../../MCAL/SPI/Header/SPI_interface.h"

#include "../Header/MCP2515_interface.h"
#include "../Header/MCP2515_config.h"
#include "../Header/MCP2515_private.h"

static void MCP2515_voidChipSelect(uint8 Copy_u8State)
{
	if(Copy_u8State == SLAVE_CHOOSE)
	{
		DIO_u8SetPinValue(MCP2515_u8Slave_SELECT_PORT, MCP2515_u8Slave_SELECT_PIN, DIO_u8PIN_LOW);
	}
	else if(Copy_u8State == SLAVE_RELEASE)
	{
		DIO_u8SetPinValue(MCP2515_u8Slave_SELECT_PORT, MCP2515_u8Slave_SELECT_PIN, DIO_u8PIN_HIGH);
	}
}

uint8 MCP2515_u8ReadRegister(uint8 Copy_u8Address)
{
	uint8 Local_u8ReadValue;

	MCP2515_voidChipSelect(SLAVE_CHOOSE);

	SPI_u8Transceive(INST_READ);
	SPI_u8Transceive(Copy_u8Address);

	Local_u8ReadValue = SPI_u8Transceive(0);

	MCP2515_voidChipSelect(SLAVE_RELEASE);

	return Local_u8ReadValue;
}

void MCP2515_voidWriteRegister(uint8 Copy_u8Address, uint8 Copy_u8Value)
{
	MCP2515_voidChipSelect(SLAVE_CHOOSE);

	SPI_u8Transceive(INST_WRITE);
	SPI_u8Transceive(Copy_u8Address);
	SPI_u8Transceive(Copy_u8Value);

	MCP2515_voidChipSelect(SLAVE_RELEASE);
}

void MCP2515_voidSetBitTiming(uint8 Copy_u8CNF1Value, uint8 Copy_u8CNF2Value, uint8 Copy_u8CNF3Value)
{
	MCP2515_voidWriteRegister(CNF1, Copy_u8CNF1Value);
	MCP2515_voidWriteRegister(CNF2, Copy_u8CNF2Value);
	MCP2515_voidWriteRegister(CNF3, Copy_u8CNF3Value);
}

void MCP2515_voidReset(void)
{
	MCP2515_voidChipSelect(SLAVE_CHOOSE);

	SPI_u8Transceive(INST_RESET);

	MCP2515_voidChipSelect(SLAVE_RELEASE);
}

void MCP2515_voidChangeBits(uint8 Copy_u8RegAddress, uint8 Copy_u8Mask, uint8 Copy_u8Value)
{
	MCP2515_voidChipSelect(SLAVE_CHOOSE);

	SPI_u8Transceive(INST_BIT_MODIFY);
	SPI_u8Transceive(Copy_u8RegAddress);
	SPI_u8Transceive(Copy_u8Mask);
	SPI_u8Transceive(Copy_u8Value);

	MCP2515_voidChipSelect(SLAVE_RELEASE);
}

void MCP2515_voidSetMode(uint8 Copy_u8Mode)
{
	MCP2515_voidChangeBits(CANCTRL, 0xE0, Copy_u8Mode << 5);
	while((MCP2515_u8ReadRegister(CANSTAT) >> 5) != Copy_u8Mode);
}

void MCP2515_voidSendInit(void)
{
	SPI_voidInit();
//	SPI_VidMasterInit();

	MCP2515_voidReset();

	/*Enter configuration mode and enable CLKOUT with no prescaler*/
	MCP2515_voidWriteRegister(CANCTRL, 0x84);

	while((MCP2515_u8ReadRegister(CANSTAT)>>5) != MCP2515_MODE_CONFG);

	/*To run at 250 KHz bit rate using 8 MHz oscillator*/
	MCP2515_voidSetBitTiming((2 << 6), ((1 << 7) | (6 << 3) | (1)), 5);

	MCP2515_voidSetMode(MCP2515_MODE_NORMAL);
}



void MCP2515_voidSendCANmsg(MCP2515_CanMessage_t Copy_stMessage)
{
	MCP2515_voidChipSelect(SLAVE_CHOOSE);

	uint8 Local_u8Counter;

	/*Send header and address*/
	SPI_u8Transceive(INST_WRITE);
	SPI_u8Transceive(TXB0CTRL);

	/*Setup message priority*/
	SPI_u8Transceive(3);

	/* Setup standard or extended identifier */
	SPI_u8Transceive((uint8)(Copy_stMessage.id >> 3));
	SPI_u8Transceive((uint8)(Copy_stMessage.id << 5));
	SPI_u8Transceive(0);
	SPI_u8Transceive(0);

	/* Setup message length and RTR bit */
	SPI_u8Transceive((Copy_stMessage.length) | (Copy_stMessage.properties << 6));

	/* Store the message into the buffer */
	for(Local_u8Counter = 0; Local_u8Counter < Copy_stMessage.length; Local_u8Counter++)
	{
		SPI_u8Transceive(Copy_stMessage.data[Local_u8Counter]);
	}

	/*Release the bus*/
	MCP2515_voidChipSelect(SLAVE_RELEASE);

	/*Send request to send*/
	MCP2515_voidChipSelect(SLAVE_CHOOSE);
	SPI_u8Transceive(INST_RTS_TXB0);
	MCP2515_voidChipSelect(SLAVE_RELEASE);
}


void MCP2515_voidSetRollover(uint8 Copy_u8Value)
{
	MCP2515_voidChangeBits(RXB0CTRL, 1 << BUKT, Copy_u8Value << BUKT);
}

void MCP2515_voidSetMask(uint8 Copy_u8MaskAddress, uint32 Copy_u32MaskValue, uint8 Copy_u8Extended)
{
	MCP2515_voidChipSelect(SLAVE_CHOOSE);

	SPI_u8Transceive(INST_WRITE);
	SPI_u8Transceive(Copy_u8MaskAddress);

	if(Copy_u8Extended)
	{
		/*Extended Address*/
		SPI_u8Transceive((uint8) (Copy_u32MaskValue >> 3));
		SPI_u8Transceive((uint8) (Copy_u32MaskValue << 5) | (1<<3) | (uint32) (Copy_u32MaskValue >> 27));
		SPI_u8Transceive((uint8) (Copy_u32MaskValue >> 19));
		SPI_u8Transceive((uint8) (Copy_u32MaskValue >> 11));
	}
	else
	{
		/*Standard Address*/
		SPI_u8Transceive((uint8) (Copy_u32MaskValue >> 3));
		SPI_u8Transceive((uint8) (Copy_u32MaskValue << 5));
	}

	MCP2515_voidChipSelect(SLAVE_RELEASE);
}



void MCP2515_voidReceiveInit(void)
{
	SPI_voidInit();
//	SPI_VidMasterInit();

	MCP2515_voidReset();

	/*Enter configuration mode and enable CLKOUT with no prescaler*/
	MCP2515_voidWriteRegister(CANCTRL, 0x84);

	while((MCP2515_u8ReadRegister(CANSTAT) >> 5) != MCP2515_MODE_CONFG);

	/*To run at 250 KHz bit rate using 8 MHz oscillator*/
	MCP2515_voidSetBitTiming((2 << 6), (1 << 7) | (6 << 3) | (1), (5));

	//	MCP2515_VidSetBitTiming(0, 0xAC, 0x03);
	/*Accept all messages*/
	MCP2515_voidSetMask(RXM0SIDH, 0x00000000, 1);
	MCP2515_voidSetMask(RXM1SIDH, 0x00000000, 1);
	MCP2515_voidSetRollover(1);

	MCP2515_voidWriteRegister(CANINTE, 1<<RX0IE);

	MCP2515_voidSetMode(MCP2515_MODE_NORMAL);
}

uint8 MCP2515_u8ReadBuffer[14];

MCP2515_CanMessage_t MCP2515_stReceiveCANmsg(void)
{
	MCP2515_CanMessage_t Local_stReceive = {0};
	uint8 Local_u8Counter = 0;

	MCP2515_voidChipSelect(SLAVE_CHOOSE);

	SPI_u8Transceive(INST_READ);
	SPI_u8Transceive(RXB0CTRL);


	for(Local_u8Counter = 0; Local_u8Counter < 14; Local_u8Counter++)
	{
		MCP2515_u8ReadBuffer[Local_u8Counter] = SPI_u8Transceive(0);
	}

	MCP2515_voidChipSelect(SLAVE_RELEASE);

	MCP2515_voidWriteRegister(CANINTF, 0);

	Local_stReceive.id = MCP2515_u8ReadBuffer[1];
	Local_stReceive.id = Local_stReceive.id << 3;
	uint8 Local_u8Hegazy = MCP2515_u8ReadBuffer[2];
	Local_stReceive.id |= Local_u8Hegazy >> 5;
	Local_stReceive.length = MCP2515_u8ReadBuffer[5] & 0x0F;

	for(Local_u8Counter = 0; Local_u8Counter < 8; Local_u8Counter++)
	{
		Local_stReceive.data[Local_u8Counter] = MCP2515_u8ReadBuffer[6 + Local_u8Counter];
	}

	Local_stReceive.properties = GET_BIT(MCP2515_u8ReadBuffer[0],3);

	return Local_stReceive;
}

void MCP2515_voidReceiveCANmsg2(void)
{
	MCP2515_voidChipSelect(SLAVE_CHOOSE);

	uint8 Local_u8Counter;

	SPI_u8Transceive(INST_READ);
	SPI_u8Transceive(RXB0CTRL);

	for(Local_u8Counter = 0; Local_u8Counter < 14; Local_u8Counter++)
	{
		MCP2515_u8ReadBuffer[Local_u8Counter] = SPI_u8Transceive(0);
	}

	MCP2515_voidChipSelect(SLAVE_RELEASE);

	MCP2515_voidWriteRegister(CANINTF, 0);
}

