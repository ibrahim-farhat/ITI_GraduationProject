#include "../Common/STD_TYPES.h"
#include "../Common/DEFINES.h"
#include "../Common/BIT_MATH.h"

#include "../Data_Structures/Queue/queue.h"
#include "../SERL/FIR/Header/FIR_interface.h"

#include "../MCAL/GIE/Header/GIE_interface.h"
#include "../MCAL/DIO/Header/DIO_interface.h"
#include "../MCAL/ADC/Header/ADC_interface.h"
#include "../MCAL/PORT/Header/PORT_interface.h"
#include "../MCAL/TIMERS/Header/TIMERS_interface.h"

#include "../HAL/CLCD/Header/CLCD_interface.h"
#include "../HAL/LDR/Header/LDR_interface.h"
#include "../HAL/LM35/Header/LM35_interface.h"
#include "../HAL/ULTSONIC/Header/ULTSONIC_interface.h"
#include "../HAL/MCP/Header/MCP2515_interface.h"

#include "util/delay.h"

#define DEBUG

/*
 * Main purpose for this project:
 * 1- read the distance from 2 ultrasonic (one in the front and the second one in the rear).
 * 2- read the light intensity from 3 LDR sensors (distributed along the car).
 * 3- send all the readings to the stm32 by CAN bus.
 */

/**
 * @brief Function to be run every timer 0 interrupt.
 * @details This function manage the sampling rate of all the sensors.
 */
void Main_voidTimer0ISR(void);

/*Define sensors sampling states*/
#define MAIN_u8SAMPLING_READY					0u
#define MAIN_u8SAMPLING_STILL_PENDING			1u

/*Define sampling flags*/
uint8 Main_u8LDRSamplingFlag = MAIN_u8SAMPLING_READY;
uint8 Main_u8TempSamplingFlag = MAIN_u8SAMPLING_READY;
uint8 Main_u8UltrasonicSamplingFlag = MAIN_u8SAMPLING_READY;

void main(void)
{
	/*Peripherals Initializations*/
	PORT_voidInit();
	GIE_voidEnable();
	ADC_voidInit();
	MCP2515_voidInit();

//#ifdef DEBUG
//	CLCD_voidInit();
//#endif
//
	/*Initialize timer 0*/
	TIMER0_2_CFG_t Local_stTimer0;
	Local_stTimer0.ClkSelect = TIMER0_u8SYS_CLK_BY_8;
	Local_stTimer0.OCMode = OC_DISCONNECTED;
	Local_stTimer0.WGM = CTC;
	TIMER0_u8Init(&Local_stTimer0);
	TIMER0_voidSetCompValue(250);
	TIMERS_u8SetCallBack(TIMER0_COMP, Main_voidTimer0ISR);
	TIMERS_u8IntEnable(TIMER0_COMP);

	/*Define LDR readings variables*/
	uint16 Local_u16RightLDRReading;
	uint16 Local_u16MediumLDRReading;
	uint16 Local_u16LeftLDRReading;

	/*Define ultrasonic variables*/
	ULTSONIC_t Local_stRearUltrasonic =
	{
			.TrigPort = DIO_u8PORTD,
			.TrigPin = DIO_u8PIN7
	};

	/*Define distance variables*/
	uint16 Local_u16RearDistance = 0;

	/*Define temperature variable*/
	uint8 Local_u8Temperature = 0;

	/*Define CAN readings message*/
	/**
	 * @struct CAN message to carry the LDR readings.
	 */
	MCP2515_CanMessage_t Local_stLDRReadingsMessage =
	{
			.id = 0x11,
			.properties = 0,
			.length = 6
	};

	/**
	 * @struct CAN message to carry the rear ultrasonic distance.
	 */
	MCP2515_CanMessage_t Local_stRearUltrasonicMessage =
	{
			.id = 0x22,
			.properties = 0,
			.length = 1
	};

	/**
	 * @struct CAN message to carry the temperature.
	 */
	MCP2515_CanMessage_t Local_stTemperatureMessage =
	{
			.id = 0x33,
			.properties = 0,
			.length = 1
	};


	while(1)
	{
		if(Main_u8LDRSamplingFlag == MAIN_u8SAMPLING_READY)
		{
			/*Get the light intensity from the 3 LDRs*/
			LDR_u8GetAnalogVolt(LDR_u8ADC_CH0, &Local_u16RightLDRReading);
			LDR_u8GetAnalogVolt(LDR_u8ADC_CH1, &Local_u16MediumLDRReading);
			LDR_u8GetAnalogVolt(LDR_u8ADC_CH2, &Local_u16LeftLDRReading);

			/*Construct the LDR samples into the CAN message*/
			Local_stLDRReadingsMessage.data[0] = (uint8) Local_u16RightLDRReading;
			Local_stLDRReadingsMessage.data[1] = (uint8) (Local_u16RightLDRReading >> 8u);
			Local_stLDRReadingsMessage.data[2] = (uint8) Local_u16MediumLDRReading;
			Local_stLDRReadingsMessage.data[3] = (uint8) (Local_u16MediumLDRReading >> 8u);
			Local_stLDRReadingsMessage.data[4] = (uint8) Local_u16LeftLDRReading;
			Local_stLDRReadingsMessage.data[5] = (uint8) (Local_u16LeftLDRReading >> 8u);

			/*Send the LDR samples to the CAN bus*/
			MCP2515_voidSendCANmsg(Local_stLDRReadingsMessage);

			CLCD_u8GoToXY(0, 0);
			CLCD_voidSendDecimalNumber(Local_u16RightLDRReading);

			CLCD_u8GoToXY(5, 0);
			CLCD_voidSendDecimalNumber(Local_u16MediumLDRReading);

			CLCD_u8GoToXY(10, 0);
			CLCD_voidSendDecimalNumber(Local_u16LeftLDRReading);

			/*Pend the sampling flag again*/
			Main_u8LDRSamplingFlag = MAIN_u8SAMPLING_STILL_PENDING;
		}

		if(Main_u8UltrasonicSamplingFlag == MAIN_u8SAMPLING_READY)
		{
			/*Measure the distance from the rear ultrasonic*/
			TIMERS_u8IntDisable(TIMER0_COMP);
			ULTSONIC_u8MeasureDistance(&Local_stRearUltrasonic, &Local_u16RearDistance);
			TIMERS_u8IntEnable(TIMER0_COMP);

			if(Local_u16RearDistance > 300)
			{
				Local_u16RearDistance = 0u;
			}

			/*Construct the rear distance into the CAN message*/
			Local_stRearUltrasonicMessage.data[0] = (uint8) Local_u16RearDistance;

			/*Send the rear distance to the CAN bus*/
			MCP2515_voidSendCANmsg(Local_stRearUltrasonicMessage);

			/*Pend the sampling flag again*/
			CLCD_u8GoToXY(8, 1);
			CLCD_voidSendDecimalNumber(Local_u16RearDistance);

			Main_u8UltrasonicSamplingFlag = MAIN_u8SAMPLING_STILL_PENDING;
		}

		if(Main_u8TempSamplingFlag == MAIN_u8SAMPLING_READY)
		{
			/*Get the temperature from LM35 sensor*/
			LM35_u8GetTemp(LM35_u8ADC_CH3, &Local_u8Temperature);

			/*Construct the temperature into the CAN message*/
			Local_stTemperatureMessage.data[0] = Local_u8Temperature;

			/*Send the rear distance to the CAN bus*/
			MCP2515_voidSendCANmsg(Local_stTemperatureMessage);

			CLCD_voidClearDisplay();
			CLCD_u8GoToXY(0, 1);
			CLCD_voidSendDecimalNumber(Local_u8Temperature);

			/*Pend the sampling flag again*/
			Main_u8TempSamplingFlag = MAIN_u8SAMPLING_STILL_PENDING;
		}
	}
}

void Main_voidTimer0ISR(void)
{
	static uint16 Local_u16Counter;

	Local_u16Counter++;

	/*Control the LDRs sampling flag*/
	if((Local_u16Counter % 80) == 0u)
	{
		Main_u8LDRSamplingFlag = MAIN_u8SAMPLING_READY;
	}

	/*Control the rear ultrasonic distance sampling flag*/
	if((Local_u16Counter % 1000) == 0u)
	{
		Main_u8UltrasonicSamplingFlag = MAIN_u8SAMPLING_READY;
	}

	/*Control the temperature sampling flag*/
	if(Local_u16Counter == 2000u)
	{
		Main_u8TempSamplingFlag = MAIN_u8SAMPLING_READY;
		Local_u16Counter = 0;
	}
}
