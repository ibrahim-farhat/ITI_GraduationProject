#include "../Common/STD_TYPES.h"
#include "../Common/DEFINES.h"
#include "../Common/BIT_MATH.h"

#include "../MCAL/GIE/Header/GIE_interface.h"
#include "../MCAL/DIO/Header/DIO_interface.h"
#include "../MCAL/PORT/Header/PORT_interface.h"
#include "../MCAL/TIMERS/Header/TIMERS_interface.h"
#include "../HAL/CLCD/Header/CLCD_interface.h"

#include "../HAL/MOTOR/Header/MOTOR_interface.h"
#include "../HAL/MCP/Header/MCP2515_interface.h"
#include "../HAL/ULTSONIC/Header/ULTSONIC_interface.h"

#include "../MCAL/USART/Header/USART_interface.h"

#include <util/delay.h>`

#define DEBUG

/*Define the motors macros*/
#define RIGHT_MOTOR			1u
#define LEFT_MOTOR			2u

/*Define the direction macros*/
#define MOVE_FORWARD		1u
#define MOVE_BACKWARD		2u
#define MOVE_RIGHT			3u
#define MOVE_LEFT			4u
#define STOP				5u

/*Define internal direction macros*/
#define FORWARD_DIRECTION	1u
#define BACKWARD_DIRECTION	2u

/*Define the */
/*
 * Main purpose for this project:
 * 1- drive the 2 motors.
 * 2- support a PWM signal which control the motor velocity.
 * 3- take the order of motion from the CAN bus.
 */

void Main_voidReceiveNotificFunc(void);
void Main_voidMove(uint8 Copy_u8Direction);
void Main_voidSetMotorSpeed(uint8 Copy_u8Motor, uint16 Copy_u8Speed);
void Main_voidTimer0ISR(void);

/*Define two DC motors*/
MOTOR_t Main_stRightMotor;
MOTOR_t Main_stLeftMotor;

/*Define global variables*/
static uint8 Main_u8ReceivedData = 0u;
//static uint8 Main_u8PreviousReceivedData;
//static uint8 Main_u8ReceivedFlag;
//static uint8 Main_u8CarDirection;
//static uint8 Main_u8Timer0State = 0;
//static uint16 Main_u16CarSpeedDutyCycle;

/*Define sensors sampling states*/
#define MAIN_u8SAMPLING_READY					0u
#define MAIN_u8SAMPLING_STILL_PENDING			1u

/*Define sampling flag*/
uint8 Main_u8UltrasonicSamplingFlag = MAIN_u8SAMPLING_STILL_PENDING;
/*Define UART receiving flag*/
uint8 Main_u8UartReceivingFlag = 0u;
/*It is the main*/
void main(void)
{
	/*Initialize needed peripherals*/
	PORT_voidInit();
	CLCD_voidInit();
	USART_voidInit();

	/*Initialize the MCP for sending and receiving*/
	MCP2515_voidReceiveInit();
	MCP2515_voidSendInit();

	/*Enable Global Interrupt*/
	GIE_voidEnable();

	/*Initialize Timer 1 to generate PWM signal to manage the motors speed*/
//	TIMER1_CFG_t Local_stTimer1;
//	Local_stTimer1.ClkSelect = TIMER1_u8SYS_CLK_BY_8;
//	Local_stTimer1.OCAMode = NON_INVERTED_PWM;
//	Local_stTimer1.OCBMode = NON_INVERTED_PWM;
//	Local_stTimer1.WGM = FAST_PWM_10_BITS;
//	TIMER1_voidSetCompValueChA(1000);
//	TIMER1_voidSetCompValueChB(1000);
//	TIMER1_u8Init(&Local_stTimer1);
	DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN4, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN5, DIO_u8PIN_HIGH);

	/*Initialize timer 0*/
	TIMER0_2_CFG_t Local_stTimer0 =
	{
			.ClkSelect = TIMER0_u8SYS_CLK_BY_8,
			.OCMode = OC_DISCONNECTED,
			.WGM = CTC
	};
	TIMER0_u8Init(&Local_stTimer0);
	TIMER0_voidSetCompValue(250);
	TIMERS_u8SetCallBack(TIMER0_COMP, Main_voidTimer0ISR);
	TIMERS_u8IntEnable(TIMER0_COMP);

	/*Initialize motors' pins*/
	Main_stRightMotor.Pin1 = DIO_u8PIN2;
	Main_stRightMotor.Pin2 = DIO_u8PIN3;
	Main_stRightMotor.Port = DIO_u8PORTC;

	Main_stLeftMotor.Pin1 = DIO_u8PIN0;
	Main_stLeftMotor.Pin2 = DIO_u8PIN1;
	Main_stLeftMotor.Port = DIO_u8PORTC;

	/*Define ultrasonic variables*/
	ULTSONIC_t Local_stFrontUltrasonic =
	{
			.TrigPort = DIO_u8PORTD,
			.TrigPin = DIO_u8PIN7
	};

	/*Define distance variables*/
	uint16 Local_u16FrontDistance = 0u;

	/*Define a temporary CAN message to receive data into it*/
	MCP2515_CanMessage_t Local_stTempCANMessage;

	/**
	 * @struct CAN message to carry the front ultrasonic distance.
	 */
	MCP2515_CanMessage_t Local_stFrontUltrasonicMessage =
	{
			.id = 0x20,
			.properties = 0u,
			.length = 2u
	};

	/**
	 * @struct CAN message to carry the front ultrasonic distance.
	 */
	MCP2515_CanMessage_t Local_stGearState =
	{
			.id = 0x21,
			.properties = 0u,
			.length = 1u
	};`

	uint8 Local_u8MCPInterruptPin;

	/*Super Loop*/
	while(1)
	{
		/*Receive Character message from USART with asynchronous function*/
		Main_u8ReceivedData = 0u;
		USART_u8ReceiveBufferAsynch(&Main_u8ReceivedData, 1, Main_voidReceiveNotificFunc);

#ifdef DEBUG
		DIO_u8GetPinValue(DIO_u8PORTB, DIO_u8PIN3, &Local_u8MCPInterruptPin);

		if(Local_u8MCPInterruptPin == DIO_u8PIN_LOW)
		{
			Local_stTempCANMessage = MCP2515_stReceiveCANmsg();

			CLCD_u8GoToXY(0, 0);
			CLCD_voidSendDecimalNumber(Local_stTempCANMessage.id);
		}
#endif

		/*Apply the received input to the motors*/
		if(Main_u8ReceivedData == 'F')
		{
			Main_voidSetMotorSpeed(RIGHT_MOTOR, 900u);
			Main_voidSetMotorSpeed(LEFT_MOTOR, 900u);
			Main_voidMove(MOVE_FORWARD);
			Local_stGearState.data[0] = 4;
			MCP2515_voidSendCANmsg(Local_stGearState);
			_delay_ms(50);
		}
		else if(Main_u8ReceivedData == 'B')
		{
			Main_voidSetMotorSpeed(RIGHT_MOTOR, 900u);
			Main_voidSetMotorSpeed(LEFT_MOTOR, 900u);
			Main_voidMove(MOVE_BACKWARD);
			Local_stGearState.data[0] = 2;
			MCP2515_voidSendCANmsg(Local_stGearState);
			_delay_ms(50);
		}
		else if(Main_u8ReceivedData == 'R')
		{
			Main_voidSetMotorSpeed(RIGHT_MOTOR, 900u);
			Main_voidSetMotorSpeed(LEFT_MOTOR, 900u);
			Main_voidMove(MOVE_RIGHT);
			_delay_ms(50);
		}
		else if(Main_u8ReceivedData == 'L')
		{
			Main_voidSetMotorSpeed(RIGHT_MOTOR, 900u);
			Main_voidSetMotorSpeed(LEFT_MOTOR, 900u);
			Main_voidMove(MOVE_LEFT);
			_delay_ms(50);
		}
		else
		{
			Main_voidSetMotorSpeed(RIGHT_MOTOR, 0u);
			Main_voidSetMotorSpeed(LEFT_MOTOR, 0u);
			Main_voidMove(STOP);
			Local_stGearState.data[0] = 4;
			MCP2515_voidSendCANmsg(Local_stGearState);
		}


		if(Main_u8UltrasonicSamplingFlag == MAIN_u8SAMPLING_READY)
		{
			/*Measure the distance from the rear ultrasonic*/
			TIMERS_u8IntDisable(TIMER0_COMP);
			ULTSONIC_u8MeasureDistance(&Local_stFrontUltrasonic, &Local_u16FrontDistance);
			TIMERS_u8IntEnable(TIMER0_COMP);

			CLCD_voidClearDisplay();
			CLCD_u8GoToXY(0, 1);
			CLCD_voidSendDecimalNumber(Local_u16FrontDistance);

			/*Construct the rear distance into the CAN message*/
			Local_stFrontUltrasonicMessage.data[0] = (uint8) Local_u16FrontDistance;
			Local_stFrontUltrasonicMessage.data[1] = (uint8) (Local_u16FrontDistance >> 8u);

			/*Send the rear distance to the CAN bus*/
			MCP2515_voidSendCANmsg(Local_stFrontUltrasonicMessage);

			/*Pend the sampling flag again*/
			Main_u8UltrasonicSamplingFlag = MAIN_u8SAMPLING_STILL_PENDING;
		}


		if(Local_u16FrontDistance > 30)
		{
			/*Do nothing*/
		}
		else if(Local_u16FrontDistance > 20)
		{
			DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN4, DIO_u8PIN_HIGH);
			_delay_ms(120);
			DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN4, DIO_u8PIN_LOW);
			_delay_ms(119);

		}
		else if(Local_u16FrontDistance > 10)
		{
			DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN4, DIO_u8PIN_HIGH);
			_delay_ms(90);
			DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN4, DIO_u8PIN_LOW);
			_delay_ms(89);
		}
		else if(Local_u16FrontDistance > 5)
		{
			DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN4, DIO_u8PIN_HIGH);
			_delay_ms(50);
			DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN4, DIO_u8PIN_LOW);
			_delay_ms(49);
		}
		else
		{
			DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN4, DIO_u8PIN_HIGH);
			_delay_ms(30);
		}
	}
}

void Main_voidSetMotorSpeed(uint8 Copy_u8Motor, uint16 Copy_u8Speed)
{
    if(Copy_u8Motor == RIGHT_MOTOR)
    {
    	TIMER1_voidSetCompValueChA(Copy_u8Speed);
    }
    else if(Copy_u8Motor == LEFT_MOTOR)
    {
    	TIMER1_voidSetCompValueChB(Copy_u8Speed);
    }
}

void Main_voidSetMotorDirection(uint8 Copy_u8Motor, uint8 Copy_u8Direction)
{
    if(Copy_u8Motor == RIGHT_MOTOR)
    {
        if(Copy_u8Direction == FORWARD_DIRECTION)
        {
        	MOTOR_u8RotateCW(&Main_stRightMotor);
        }
        else if(Copy_u8Direction == BACKWARD_DIRECTION)
        {
        	MOTOR_u8RotateCCW(&Main_stRightMotor);
        }
        else if(Copy_u8Direction == STOP)
        {
        	MOTOR_u8Stop(&Main_stRightMotor);
        }
    }
    else if(Copy_u8Motor == LEFT_MOTOR)
    {
        if (Copy_u8Direction == FORWARD_DIRECTION)
        {
        	MOTOR_u8RotateCCW(&Main_stLeftMotor);
        }
        else if(Copy_u8Direction == BACKWARD_DIRECTION)
        {
        	MOTOR_u8RotateCW(&Main_stLeftMotor);
        }
        else if(Copy_u8Direction == STOP)
        {
        	MOTOR_u8Stop(&Main_stLeftMotor);
        }
    }
}

/*
 * you can set the speed here, with a variable
 */
void Main_voidMove(uint8 Copy_u8Direction)
{
	if(Copy_u8Direction == MOVE_FORWARD)
	{
		Main_voidSetMotorDirection(RIGHT_MOTOR, FORWARD_DIRECTION);
		Main_voidSetMotorDirection(LEFT_MOTOR, FORWARD_DIRECTION);
	}
	else if(Copy_u8Direction == MOVE_BACKWARD)
	{
		Main_voidSetMotorDirection(RIGHT_MOTOR, BACKWARD_DIRECTION);
		Main_voidSetMotorDirection(LEFT_MOTOR, BACKWARD_DIRECTION);
	}
	else if(Copy_u8Direction == MOVE_RIGHT)
	{
		Main_voidSetMotorDirection(RIGHT_MOTOR, BACKWARD_DIRECTION);
		Main_voidSetMotorDirection(LEFT_MOTOR, FORWARD_DIRECTION);
	}
	else if(Copy_u8Direction == MOVE_LEFT)
	{
		Main_voidSetMotorDirection(RIGHT_MOTOR, FORWARD_DIRECTION);
		Main_voidSetMotorDirection(LEFT_MOTOR, BACKWARD_DIRECTION);
	}
	else if(Copy_u8Direction == STOP)
	{
		Main_voidSetMotorDirection(RIGHT_MOTOR, STOP);
		Main_voidSetMotorDirection(LEFT_MOTOR, STOP);
	}
}

/*USART Receive ISR*/
void Main_voidReceiveNotificFunc(void)
{

}

void Main_voidTimer0ISR(void)
{
	/*Define static counter*/
	static uint16 Local_u16Counter;

	Local_u16Counter++;

	/*Control the LDRs sampling flag*/
	if(Local_u16Counter == 400u)
	{
		/*Rise the sampling flag*/
		Main_u8UltrasonicSamplingFlag = MAIN_u8SAMPLING_READY;

		/*Reset the static counter*/
		Local_u16Counter = 0u;
	}
}
//{
//	static uint8 Local_u8PreviousReceivedData = 0u;
//
//	/*Do nothing*/
//	/*Switch the char which received then take its corresponding order*/
//	if(Main_u8ReceivedData != Local_u8PreviousReceivedData)
//	{
//		Main_voidSetMotorSpeed(RIGHT_MOTOR, 500u);
//		Main_voidSetMotorSpeed(LEFT_MOTOR, 500u);
//		Main_u16CarSpeedDutyCycle = 500u;
//		if(Main_u8ReceivedData == 'F')
//		{
//			Main_voidMove(MOVE_FORWARD);
//		}
//		else if(Main_u8ReceivedData == 'B')
//		{
//			Main_voidMove(MOVE_BACKWARD);
//		}
//		else if(Main_u8ReceivedData == 'R')
//		{
//			Main_voidMove(MOVE_RIGHT);
//		}
//		else if(Main_u8ReceivedData == 'L')
//		{
//			Main_voidMove(MOVE_LEFT);
//		}
//	}
//
//	if((Main_u8Timer0State == 0u) && (Main_u8ReceivedData == 'F' || Main_u8ReceivedData == 'B' || Main_u8ReceivedData == 'R' || Main_u8ReceivedData == 'L'))
//	{
//		TIMERS_u8IntEnable(TIMER0_COMP);
//		Main_u8Timer0State = 1u;
//	}
//
//	Local_u8PreviousReceivedData = Main_u8ReceivedData;
//	Main_u8ReceivedFlag = 1u;
//}
//
///*If the UART received data in 20 ml from the previous data stop the car*/
//void Main_voidTimer0ISR(void)
//{
//	static uint8 Local_u8Counter;
//	static uint8 Local_u8PreviousRecievedData;
//	CLCD_voidClearDisplay();
//	CLCD_u8GoToXY(0, 0);
//	CLCD_voidSendDecimalNumber(Main_u8ReceivedFlag);
//	CLCD_u8GoToXY(0, 1);
//	CLCD_voidSendDecimalNumber(Local_u8Counter);
//
//	if(Main_u8ReceivedData != Local_u8PreviousRecievedData)
//	{
//		Local_u8Counter = 0u;
//	}
//
//	Local_u8Counter++;
//	if(Local_u8Counter == 10u)
//	{
//		if(Main_u8ReceivedFlag == 1u)
//		{
//			if(Main_u8ReceivedData == Local_u8PreviousRecievedData)
//			{
//				if(Main_u16CarSpeedDutyCycle < 1000u)
//				{
//					Main_u16CarSpeedDutyCycle += 50;
//				}
//				else
//				{
//					/*Do nothing*/
//				}
//			}
//
//			Main_u8ReceivedFlag = 0u;
//		}
//		else if(Main_u8ReceivedFlag == 0u)
//		{
//			TIMERS_u8IntDisable(TIMER0_COMP);
//			Main_u16CarSpeedDutyCycle = 0u;
//			Main_u8Timer0State = 0u;
//			Main_voidMove(STOP);
//		}
//
//		Main_voidSetMotorSpeed(RIGHT_MOTOR, Main_u16CarSpeedDutyCycle);
//		Main_voidSetMotorSpeed(LEFT_MOTOR, Main_u16CarSpeedDutyCycle);
//
//		Local_u8Counter = 0u;
//
//		Local_u8PreviousRecievedData = Main_u8ReceivedData;
//	}
//}
//
///*Function to move the car in all directions*/
//void Main_voidMove(uint8 Copy_u8Direction, uint16 Copy_u16Duration)
//{
//	/*Send the direction to the timer ISR*/
//	Main_u8CarDirection = Copy_u8Direction;
//
//	/*Enable the timer*/
//	TIMERS_u8IntEnable(TIMER0_COMP);
//
//	/*Delay for the step time*/
//	_delay_ms(Copy_u16Duration);
//
//	/*Stop the vehicle*/
//	Main_voidStop();
//}

//void Main_voidStop(void)
//{
//	/*Disable the timer*/
//	TIMERS_u8IntDisable(TIMER0_COMP);
//
//	/*Stop the motors*/
//	MOTOR_u8Stop(&Main_stMotor1);
//	MOTOR_u8Stop(&Main_stMotor2);
//}

///*Timer 0 ISR*/
//void Main_voidTimer0ISR()
//{
//	/*Define variables*/
//	static uint8 Local_u8Counter = 0u;
//
//	/*Increment the counter of entering the ISR*/
//	Local_u8Counter++;
//
//	/*Move the car according to the needed speed and direction*/
//	if(Local_u8Counter == Main_u8MotorSpeed)
//	{
//		if(Main_u8CarDirection == 'F')
//		{
//			MOTOR_u8RotateCCW(&Main_stMotor1);
//			MOTOR_u8RotateCCW(&Main_stMotor2);
//		}
//		else if(Main_u8CarDirection == 'B')
//		{
//			MOTOR_u8RotateCW(&Main_stMotor1);
//			MOTOR_u8RotateCW(&Main_stMotor2);
//		}
//		else if(Main_u8CarDirection == 'R')
//		{
//			MOTOR_u8RotateCW(&Main_stMotor2);
//			MOTOR_u8RotateCCW(&Main_stMotor1);
//		}
//		else if(Main_u8CarDirection == 'L')
//		{
//			MOTOR_u8RotateCCW(&Main_stMotor2);
//			MOTOR_u8RotateCW(&Main_stMotor1);
//		}
//	}
//
//	/*Every period time stop the motors and zero the counter*/
//	else if(Local_u8Counter == 20u)
//	{
//		MOTOR_u8Stop(&Main_stMotor1);
//		MOTOR_u8Stop(&Main_stMotor2);
//		Local_u8Counter = 0u;
//	}
//}
