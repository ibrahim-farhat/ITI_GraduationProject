/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: ULTSONIC_program.c	**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file ULTSONIC_program.c
 * @author Ibrahim Tarek
 * @brief This file implements the ULTSONIC sensor module functions.
 * @version 1.00
 */

#include "../../../Common/STD_TYPES.h"
#include "../../../Common/BIT_MATH.h"
#include "../../../Common/DEFINES.h"

#include "../../../MCAL/TIMERS/Header/TIMERS_interface.h"
#include "../../../MCAL/DIO/Header/DIO_interface.h"

#include "util/delay.h"

#include "../Header/ULTSONIC_config.h"
#include "../Header/ULTSONIC_private.h"
#include "../Header/ULTSONIC_interface.h"

/*Define global variables*/
static uint16 ULTSONIC_u16Capture1 = 0u;
static uint16 ULTSONIC_u16Capture2 = 0u;

static uint16 ULTSONIC_u16OvfCounter = 0u;
static uint16 ULTSONIC_u16EchoOvfCounter = 0u;

/**
 * @brief 						Function to measure the distance with ultrasonic using input capture unit of timer 1.
 * @param Copy_pstUltsonicData 	Pointer to struct that carry the ultrasonic data.
 * @param Copy_pu16Distance 	Pointer to return the distance in CM.
 * @return 						Error State.
 */
uint8 ULTSONIC_u8MeasureDistance(const ULTSONIC_t *Copy_pstUltsonicData, uint16 *Copy_pu16Distance)
{
	/*Define Variables*/
	uint8 Local_u8ErrorState = OK;
	uint8 Local_u8ErrorFounder = OK;
	uint32 Local_u32EchoTime = 0u;
	uint32 Local_u32TimeoutCounter = 0u;

	/*Initialize timer 1*/
	TIMER1_CFG_t Local_stTimer1Cfg;
	Local_stTimer1Cfg.ClkSelect = TIMER1_u8SYS_CLK_BY_8;
	Local_stTimer1Cfg.WGM = NORMAL_16_BITS;
	Local_stTimer1Cfg.OCAMode = OC_DISCONNECTED;
	Local_stTimer1Cfg.OCBMode = OC_DISCONNECTED;
	Local_u8ErrorFounder = TIMER1_u8Init(&Local_stTimer1Cfg);

	if(Local_u8ErrorFounder == OK)
	{
		/*Initialize and Enable Capture Unit and Overflow Interrupts of timer 1*/
		TIMERS_u8SetCallBack(TIMER1_OVF, ULTSONIC_voidOvfISR);
		TIMER1_u8SetInputCaptTriggerSrc(TIMER1_u8ICU_RISING_EDGE);
		TIMERS_u8SetCallBack(TIMER1_CAPT, ULTSONIC_voidCaptureISR);
		TIMERS_u8IntEnable(TIMER1_CAPT);

		/*Trigger the ultrasonic to return its echo*/
		DIO_u8SetPinValue(Copy_pstUltsonicData -> TrigPort, Copy_pstUltsonicData -> TrigPin, DIO_u8PIN_HIGH);
		_delay_us(100);
		DIO_u8SetPinValue(Copy_pstUltsonicData -> TrigPort, Copy_pstUltsonicData -> TrigPin, DIO_u8PIN_LOW);

		/*Polling until the echo time is measured*/
		while(((ULTSONIC_u16Capture1 == 0u) || (ULTSONIC_u16Capture2 == 0u)) && (Local_u32TimeoutCounter < ULTSOINC_u32TIMEOUT))
		{
			Local_u32TimeoutCounter++;
		}

		/*Disable timer 1 and overflow interrupt of it*/
		TIMERS_u8IntDisable(TIMER1_OVF);
		TIMERS_u8IntDisable(TIMER1_CAPT);
		TIMERS_u8Disable(TIMER1);

		/*Check if there was overflow interrupts or not*/
		if(ULTSONIC_u16EchoOvfCounter == 0u)
		{
			/*Calculate Echo Time in microseconds*/
			Local_u32EchoTime = ULTSONIC_u16Capture2 - ULTSONIC_u16Capture1;
		}
		else
		{
			/*Calculate Echo Time in microseconds*/
			if(ULTSONIC_u16Capture2 >= ULTSONIC_u16Capture1)
			{
				Local_u32EchoTime = (ULTSONIC_u16Capture2 - ULTSONIC_u16Capture1) + (ULTSONIC_u16EchoOvfCounter * 65536u);
			}
			else if(ULTSONIC_u16Capture2 < ULTSONIC_u16Capture1)
			{
				Local_u32EchoTime = (ULTSONIC_u16Capture1 - ULTSONIC_u16Capture2) + (ULTSONIC_u16EchoOvfCounter * 65536u);
			}
		}

		/*Measure Distance using Echo Time*/
		*Copy_pu16Distance = (((f32) Local_u32EchoTime / 2.0) * (34.0 / 1000.0));

		/*Reset the global variables*/
		ULTSONIC_u16Capture1 = 0u;
		ULTSONIC_u16Capture2 = 0u;
		ULTSONIC_u16OvfCounter = 0u;
		ULTSONIC_u16EchoOvfCounter = 0u;
	}
	else
	{
		Local_u8ErrorState = NOK;
	}

	/*Return Error State*/
	return Local_u8ErrorState;
}

/**
 * @brief Function to be set as input capture ISR.
 */
static void ULTSONIC_voidCaptureISR(void)
{
	static uint8 Local_u8Counter = 0u;

	Local_u8Counter++;

	if(Local_u8Counter == 1u)
	{
		/*Enable Overflow interrupt of timer1*/
		TIMERS_u8IntEnable(TIMER1_OVF);
		ULTSONIC_u16Capture1 = TIMER1_u16GetInputCaptValue();
		TIMER1_u8SetInputCaptTriggerSrc(TIMER1_u8ICU_FALLING_EDGE);
	}
	else if(Local_u8Counter == 2u)
	{
		ULTSONIC_u16Capture2 = TIMER1_u16GetInputCaptValue();
		ULTSONIC_u16EchoOvfCounter = ULTSONIC_u16OvfCounter;
		Local_u8Counter = 0;
	}
}

/**
 * @brief Function to be set as overflow ISR.
 */
static void ULTSONIC_voidOvfISR(void)
{
	ULTSONIC_u16OvfCounter++;
}






























///*********************************************/
//void Main_voidMeasureDistance(void);
//static uint16 Main_u16Reading1;
//static uint16 Main_u16Reading2;
//
///*It is the main*/
//void main(void)
//{
//	/*Peripherals Initialization*/
//	PORT_voidInit();
//	CLCD_voidInit();
//	GIE_voidEnable();
//	uint16 Local_u16Distance;
//
//	TIMER1_CFG_t Local_stTimer1;
//	Local_stTimer1.ClkSelect = TIMER1_u8SYS_CLK_BY_8;
//	Local_stTimer1.OCAMode = OC_DISCONNECTED;
//	Local_stTimer1.OCBMode = OC_DISCONNECTED;
//	Local_stTimer1.WGM = NORMAL_16_BITS;
//	TIMER1_u8Init(&Local_stTimer1);
//
//	TIMERS_u8IntEnable(TIMER1_CAPT);
//	TIMER1_u8SetInputCaptTriggerSrc(TIMER1_u8ICU_RISING_EDGE);
//	TIMERS_u8SetCallBack(TIMER1_CAPT, Main_voidMeasureDistance);
//
//	/*Super Loop*/
//	while(1)
//	{
//		_delay_ms(200);
//		CLCD_voidClearDisplay();
//		DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN0, DIO_u8PIN_HIGH);
//		_delay_ms(100);
//		DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN0, DIO_u8PIN_LOW);
//
//		while((Main_u16Reading1 == 0u) || (Main_u16Reading2 == 0u));
//		Local_u16Distance = Main_u16Reading2 - Main_u16Reading1;
//		CLCD_u8GoToXY(0, 0);
//		CLCD_voidSendDecimalNumber(Local_u16Distance);
//		Main_u16Reading1 = 0u;
//		Main_u16Reading2 = 0u;
//		TIMER1_u8SetInputCaptTriggerSrc(TIMER1_u8ICU_RISING_EDGE);
//	}
//}
//void Main_voidMeasureDistance(void)
//{
//	static uint8 Local_u8Counter = 0u;
//	if(Local_u8Counter == 0u)
//	{
//		TIMER1_u8SetInputCaptTriggerSrc(TIMER1_u8ICU_FALLING_EDGE);
//		Main_u16Reading1 = TIMER1_u16GetInputCaptValue();
//		Local_u8Counter++;
//	}
//	else if(Local_u8Counter == 1u)
//	{
//		Main_u16Reading2 = TIMER1_u16GetInputCaptValue();
//		Local_u8Counter = 0u;
//	}
//}
