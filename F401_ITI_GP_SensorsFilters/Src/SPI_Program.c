/*
 * MSPI_Program.c
 *
 *  Created on: Oct 2, 2023
 *      Author: Shereef Mahmoud
 */

#include <stdint.h>

#include "../Inc/BIT_MATH.h"
#include "../Inc/Defines.h"

#include "../Inc/Stm32F401cc.h"

#include "../Inc/GPIO_Interface.h"

#include "../Inc/MSPI_Interface.h"
#include "../Inc/MSPI_Private.h"
#include "../Inc/MSPI_Config.h"

GPIO_PinConfig_t MSPI_stSSPin = {
		.AltFunc = GPIO_AF0,
		.OutputSpeed = GPIO_LOW,
		.OutputType = GPIO_PUSH_PULL,
		.PinMode = GPIO_OUTPUT,
		.PinNum = GPIO_PIN0,
		.Port = GPIO_PORTA,
		.PullType = GPIO_NO_PULL
};


void MSPI_voidInitSlave(void)
{
	SPI1 -> CR1 = 0b0000000001000000;
}
void MSPI_voidInitMaster(void)
{
	SPI1 -> CR1 = 0b0000001101010100;
}

void MSPI_voidSendRecieveDataSync(uint8_t Copy_u8TransmitData,uint8_t* Copy_u8RecievedData)
{
	/*Clear for slave select pin*/
//	GPIO_enSetPinValue(&MSPI_stSSPin, GPIO_PIN_LOW);

	/*Send Data*/
//	if(GET_BIT(SPI1 -> SR, TXE))
	while(!(GET_BIT(SPI1 -> SR, TXE)));
	SPI1 -> DR = Copy_u8TransmitData;

//	while(GET_BIT(SPI1->SR , BSY));

//	if(GET_BIT(SPI1 -> SR, RXNE))
	while(!(GET_BIT(SPI1 -> SR, RXNE)));
	*Copy_u8RecievedData = SPI1 -> DR;


//	while(GET_BIT(SPI1 -> SR, BSY));
	/*Wait flag*/

	/*Return for the received data*/

	/*Set Slave select pin*/
//	GPIO_enSetPinValue(&MSPI_stSSPin, GPIO_PIN_HIGH);
}

void MSPI_voidSendRecieveDataAsync(uint8_t Copy_u8TransmitData, void(*Copy_pvoidCallBack)(uint8_t Copy_u8Data))
{
		/*Clear for slave select pin*/
		GPIO_enSetPinValue(&MSPI_stSSPin, GPIO_PIN_LOW);

		/*Send Data*/
		SPI1 -> DR = Copy_u8TransmitData;
}
