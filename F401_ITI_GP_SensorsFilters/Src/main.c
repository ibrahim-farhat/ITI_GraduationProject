#include <stdint.h>

#include "../Inc/Defines.h"

#include "../Inc/FIR_interface.h"

#include "../Inc/RCC_interface.h"
#include "../Inc/GPIO_interface.h"
#include "../Inc/SYSTICK_interface.h"
#include "../Inc/MSPI_Interface.h"

#include "../Inc/MCP2515_interface.h"

/*
 * This node will:
 * 1- take sensor readings from the CAN bus and filter it then launch it to the bus again.
 */

/*Define needed messages' IDs*/
#define MAIN_LDR_MESSAGE_ID					0x10
#define MAIN_REAR_DISTANCE_MESSAGE_ID		0x12
#define MAIN_TEMPERATURE_MESSAGE_ID			0x14
#define MAIN_FRONT_DISTANCE_MESSAGE_ID		0x20

/*Initialize the GPIO pins*/
static GPIO_PinConfig_t Main_stTFT_CLK = {
		.AltFunc = GPIO_AF5,
		.OutputSpeed = GPIO_LOW,
		.OutputType = GPIO_PUSH_PULL,
		.PinMode = GPIO_ALTERNATE_FUNCTION,
		.PinNum = GPIO_PIN5,
		.Port = GPIO_PORTA,
		.PullType = GPIO_NO_PULL
};
static GPIO_PinConfig_t Main_stTFT_MOSI = {
		.AltFunc = GPIO_AF5,
		.OutputSpeed = GPIO_LOW,
		.OutputType = GPIO_PUSH_PULL,
		.PinMode = GPIO_ALTERNATE_FUNCTION,
		.PinNum = GPIO_PIN7,
		.Port = GPIO_PORTA,
		.PullType = GPIO_NO_PULL
};
static GPIO_PinConfig_t Main_stTFT_MISO = {
		.AltFunc = GPIO_AF5,
		.OutputSpeed = GPIO_LOW,
		.OutputType = GPIO_PUSH_PULL,
		.PinMode = GPIO_ALTERNATE_FUNCTION,
		.PinNum = GPIO_PIN6,
		.Port = GPIO_PORTA,
		.PullType = GPIO_NO_PULL
};
static GPIO_PinConfig_t Main_stSS = {
		.AltFunc = GPIO_AF5,
		.OutputSpeed = GPIO_LOW,
		.OutputType = GPIO_PUSH_PULL,
		.PinMode = GPIO_OUTPUT,
		.PinNum = GPIO_PIN4,
		.Port = GPIO_PORTA,
		.PullType = GPIO_NO_PULL
};
static GPIO_PinConfig_t Main_stMCPInterrupt = {
		.AltFunc = GPIO_AF0,
		.OutputSpeed = GPIO_LOW,
		.OutputType = GPIO_PUSH_PULL,
		.PinMode = GPIO_INPUT,
		.PinNum = GPIO_PIN0,
		.Port = GPIO_PORTA,
		.PullType = GPIO_PULL_UP
};

/*Define sensors' needed filters*/
FIR_Filter_t Main_stLDRFilter =
{
		.ImpulseRespone =
		{
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625
		}
};

FIR_Filter_t Main_stTemperatureFilter =
{
		.ImpulseRespone =
		{
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625
		}
};

FIR_Filter_t Main_stFrontDistanceFilter =
{
		.ImpulseRespone =
		{
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625
		}
};

FIR_Filter_t Main_stRearDistanceFilter =
{
		.ImpulseRespone =
		{
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625,
			0.0625
		}
};

int main(void)
{
	/*Initialize the filters*/
	FIR_voidFilterInit(&Main_stLDRFilter);
	FIR_voidFilterInit(&Main_stRearDistanceFilter);
	FIR_voidFilterInit(&Main_stFrontDistanceFilter);
	FIR_voidFilterInit(&Main_stTemperatureFilter);

	/*Initialize systick peripheral*/
	SYSTICK_Config_t Local_stSystickConfig =
	{
			.Exception_Request = DISABLE,
			.Prescaler = SYSTICK_AHB_BY_8,
			.ClkFreq = 16u
	};
	SYSTICK_enInit(&Local_stSystickConfig);

	/*Open the RCC for GPIOA and SPI1*/
	RCC_enAHB1_EnableClk(GPIOA_EN);
	RCC_enAPB2_EnableClk(SPI1_EN);

	/*Initialize GPIO SPI pins*/
	GPIO_enPinInit(&Main_stTFT_CLK);
	GPIO_enPinInit(&Main_stTFT_MISO);
	GPIO_enPinInit(&Main_stTFT_MOSI);
	GPIO_enPinInit(&Main_stSS);
	GPIO_enPinInit(&Main_stMCPInterrupt);

	/*Initialize MCP for sending and receiving*/
	MCP2515_voidInit();
	MCP2515_voidReceiveInit();

	/*Define a temporary message to receive data into it*/
	MCP2515_CanMessage_t Local_stTempMessage =
	{
			.properties = 0u
	};

	/*Define filtered LDR reading CAN message*/
	MCP2515_CanMessage_t Local_stFilteredLDR =
	{
			.properties = 0u,
			.length = 2u,
			.id = 0x31
	};

	/*Define filtered temperature CAN message*/
	MCP2515_CanMessage_t Local_stFilteredTemperature =
	{
			.properties = 0u,
			.length = 1u,
			.id = 0x33
	};

	/*Define filtered front distance CAN message*/
	MCP2515_CanMessage_t Local_stFilteredFrontDistance =
	{
			.properties = 0u,
			.length = 2u,
			.id = 0x35
	};

	/*Define filtered rear distance CAN message*/
	MCP2515_CanMessage_t Local_stFilteredRearDistance =
	{
			.properties = 0u,
			.length = 2u,
			.id = 0x37
	};

	/*Define speed CAN message*/
	MCP2515_CanMessage_t Local_stSpeed =
	{
			.properties = 0u,
			.length = 1u,
			.id = 0x15
	};
	Local_stSpeed.data[0] = 0;

	/*Define array for the LDR readings before filter*/
	uint16_t Local_u16LDRReadingsBeforeArr[3];
	/*Define LDR readings average variable*/
	uint16_t Local_u16LDRReadingsAverage;
	/*Define LDR reading variable after filter*/
	float Local_f32FilteredLDRReading;
	uint16_t Local_u16FilteredLDRReading;

	/*Define temperature variable before filter*/
	uint8_t Local_u8TemperatureBefore;
	/*Define temperature variable after filter*/
	float Local_f32FilteredTemperature;
	uint8_t Local_u8FilteredTemperature;

	/*Define rear distance variable before filter*/
	uint16_t Local_u16RearDistanceBefore;
	uint16_t Local_u16PreviousRearDistanceBefore = 0u;
	/*Define rear distance variable after filter*/
	float Local_f32FilteredRearDistance;
	uint16_t Local_u16FilteredRearDistance;

	/*Define front distance variable before filter*/
	uint16_t Local_u16FrontDistanceBefore;
	uint16_t Local_u16PreviousFrontDistanceBefore = 0u;
	/*Define Front distance variable after filter*/
	float Local_f32FilteredFrontDistance;
	uint16_t Local_u16FilteredFrontDistance;

	/*Define GPIO pin value variable for the MCP2515 interrupt pin*/
	GPIO_PinValue_t Local_enInterrupt;
	/*Define flag to go on when the MCP capture CAN message*/
	uint8_t Local_u8SamplingFlag = 0u;

	while(1)
	{
		/*Check the interrupt pin from MCP2515*/
		GPIO_enReadPinValue(&Main_stMCPInterrupt, &Local_enInterrupt);
//		MCP2515_voidSendCANmsg(Local_stFilteredRearDistance);

		/*If the MCP2515 detect CAN message, Read this message*/
		if(Local_enInterrupt == GPIO_PIN_LOW)
		{
			/*Read the message received*/
			Local_stTempMessage = MCP2515_stReceiveCANmsg();

			/*Rise the sampling flag*/
			Local_u8SamplingFlag = 1u;
		}

		/*If MCP2515 received data*/
		if(Local_u8SamplingFlag == 1u)
		{
			/*Search for which message has been received*/
			if(Local_stTempMessage.id == MAIN_LDR_MESSAGE_ID)
			{
				/*Validate the message length*/
				if(Local_stTempMessage.length == 6u)
				{
					/*Reconstruct the LDR readings*/
					Local_u16LDRReadingsBeforeArr[0] = (uint16_t) Local_stTempMessage.data[0];
					Local_u16LDRReadingsBeforeArr[0] |= (((uint16_t) Local_stTempMessage.data[1]) << 8u);
					Local_u16LDRReadingsBeforeArr[1] = (uint16_t) Local_stTempMessage.data[2];
					Local_u16LDRReadingsBeforeArr[1] |= (((uint16_t) Local_stTempMessage.data[3]) << 8u);
					Local_u16LDRReadingsBeforeArr[2] = (uint16_t) Local_stTempMessage.data[4];
					Local_u16LDRReadingsBeforeArr[2] |= (((uint16_t) Local_stTempMessage.data[5]) << 8u);

					/*Calculate the average from the 3 LDR sensors*/
					Local_u16LDRReadingsAverage = (Local_u16LDRReadingsBeforeArr[0] + Local_u16LDRReadingsBeforeArr[1] + Local_u16LDRReadingsBeforeArr[2]) / 3UL;

					/*Update the filter samples*/
					Local_f32FilteredLDRReading = FIR_f32FilterUpdate(&Main_stLDRFilter, Local_u16LDRReadingsAverage);
					Local_u16FilteredLDRReading = (uint16_t) Local_f32FilteredLDRReading;

					/*Construct the filtered LDR reading message*/
					Local_stFilteredLDR.data[0] = (uint8_t) Local_u16FilteredLDRReading;
					Local_stFilteredLDR.data[1] = (uint8_t) (Local_u16FilteredLDRReading >> 8u);

					/*Send the CAN message*/
					MCP2515_voidSendCANmsg(Local_stFilteredLDR);
				}
			}
			else if(Local_stTempMessage.id == MAIN_TEMPERATURE_MESSAGE_ID)
			{
				/*Validate the message length*/
				if(Local_stTempMessage.length == 1u)
				{
					/*Reconstruct the temperature reading*/
					Local_u8TemperatureBefore = Local_stTempMessage.data[0];

					/*Update the filter samples*/
					Local_f32FilteredTemperature = FIR_f32FilterUpdate(&Main_stTemperatureFilter, Local_u8TemperatureBefore);
					Local_u8FilteredTemperature = (uint8_t) Local_f32FilteredTemperature;

					/*Construct the filtered temperature reading message*/
					Local_stFilteredTemperature.data[0] = Local_u8FilteredTemperature;

					/*Send the CAN message*/
					MCP2515_voidSendCANmsg(Local_stFilteredTemperature);

					/*Update the speed*/
					Local_stSpeed.data[0] += 5;
					if(Local_stSpeed.data[0] > 140)
					{
						Local_stSpeed.data[0] = 0;
					}

					/*Send the CAN message*/
					MCP2515_voidSendCANmsg(Local_stSpeed);
				}
			}
			else if(Local_stTempMessage.id == MAIN_FRONT_DISTANCE_MESSAGE_ID)
			{
				/*Validate the message length*/
				if(Local_stTempMessage.length == 2u)
				{
					/*Reconstruct the front distance*/
					Local_u16FrontDistanceBefore = (uint16_t) Local_stTempMessage.data[0];
					Local_u16FrontDistanceBefore |= (((uint16_t) Local_stTempMessage.data[1]) << 8u);

					/*Correct the front distance*/
					if(Local_u16FrontDistanceBefore > 300u || Local_u16FrontDistanceBefore == 0)
					{
						Local_u16FrontDistanceBefore = Local_u16PreviousFrontDistanceBefore;
					}
					Local_u16PreviousFrontDistanceBefore = Local_u16FrontDistanceBefore;

					/*Update the filter samples*/
					Local_f32FilteredFrontDistance = FIR_f32FilterUpdate(&Main_stFrontDistanceFilter, Local_u16FrontDistanceBefore);
					Local_u16FilteredFrontDistance = (uint16_t) Local_f32FilteredFrontDistance;

					/*Construct the filtered front distance message*/
					Local_stFilteredFrontDistance.data[0] = (uint8_t) Local_u16FilteredFrontDistance;
					Local_stFilteredFrontDistance.data[1] = (uint8_t) (Local_u16FilteredFrontDistance >> 8u);

					/*Send the CAN message*/
					MCP2515_voidSendCANmsg(Local_stFilteredFrontDistance);
				}
			}
			else if(Local_stTempMessage.id == MAIN_REAR_DISTANCE_MESSAGE_ID)
			{
				/*Validate the message length*/
				if(Local_stTempMessage.length == 2u)
				{
					/*Reconstruct the front distance*/
					Local_u16RearDistanceBefore = (uint16_t) Local_stTempMessage.data[0];
					Local_u16RearDistanceBefore |= (((uint16_t) Local_stTempMessage.data[1]) << 8u);

					/*Correct the rear distance*/
					if(Local_u16RearDistanceBefore > 300u || Local_u16RearDistanceBefore == 0)
					{
						Local_u16RearDistanceBefore = Local_u16PreviousRearDistanceBefore;
					}
					Local_u16PreviousRearDistanceBefore = Local_u16RearDistanceBefore;

					/*Update the filter samples*/
					Local_f32FilteredRearDistance = FIR_f32FilterUpdate(&Main_stRearDistanceFilter, Local_u16RearDistanceBefore);
					Local_u16FilteredRearDistance = (uint16_t) Local_f32FilteredRearDistance;

					/*Construct the filtered front distance message*/
					Local_stFilteredRearDistance.data[0] = (uint8_t) Local_u16FilteredRearDistance;
					Local_stFilteredRearDistance.data[1] = (uint8_t) (Local_u16FilteredRearDistance >> 8u);

					/*Send the CAN message*/
					MCP2515_voidSendCANmsg(Local_stFilteredRearDistance);
				}
			}

			Local_u8SamplingFlag = 0;
		}
	}
}


