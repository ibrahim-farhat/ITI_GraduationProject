/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: USART_program.c		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file USART_program.c
 * @author Ibrahim Tarek
 * @brief This file implements the USART module functions.
 * @version 1.00
 */

#include "../../../Common/STD_TYPES.h"
#include "../../../Common/BIT_MATH.h"
#include "../../../Common/DEFINES.h"

#include "../Header/USART_config.h"
#include "../Header/USART_interface.h"
#include "../Header/USART_private.h"
#include "../Header/USART_register.h"


static void (*USART_pvTransmitNotificationFunc)(void) = NULL;
static uint8 USART_u8TransmitBufferSize = 0u;
static void *USART_pvTransmitBufferArr = NULL;
static uint8 USART_u8TransmitBufferCounter = 0u;

static void (*USART_pvReceiveNotificationFunc)(void) = NULL;
static uint8 USART_u8ReceiveBufferSize = 0u;
static void *USART_pvReceiveBufferArr = NULL;
static uint8 USART_u8ReceiveBufferCounter = 0u;

static uint8 USART_u8TransmitBusyState = IDLE;
static uint8 USART_u8ReceiveBusyState = IDLE;

static uint8 USART_u8TransmitCallSrc = MAIN_CALL;
static uint8 USART_u8ReceiveCallSrc = MAIN_CALL;


/**
 * @brief Function to initialize the USART peripheral.
 */
void USART_voidInit(void)
{
	/*Define Temporary Variable for UCSRC*/
	uint8 Local_u8TempUCSRC = 0u;

	/*Enable Receiver*/
	SET_BIT(UCSRB,UCSRB_RXEN);

	/*Enable Transmitter*/
	SET_BIT(UCSRB,UCSRB_TXEN);

	/*Disable Double Transmission Speed*/
	CLR_BIT(UCSRA,UCSRA_U2X);

	/*Select the character size*/
#if USART_u8CHAR_SIZE == FIVE_BITS_CHAR_SIZE
	Local_u8TempUCSRC &= CHAR_SIZE_MASK;
	CLR_BIT(Local_u8TempUCSRC, UCSRC_UCSZ0);
	CLR_BIT(Local_u8TempUCSRC, UCSRC_UCSZ1);
	CLR_BIT(UCSRB,UCSRB_UCSZ2);

#elif USART_u8CHAR_SIZE == SIX_BITS_CHAR_SIZE
	Local_u8TempUCSRC &= CHAR_SIZE_MASK;
	SET_BIT(Local_u8TempUCSRC, UCSRC_UCSZ0);
	CLR_BIT(Local_u8TempUCSRC, UCSRC_UCSZ1);
	CLR_BIT(UCSRB,UCSRB_UCSZ2);

#elif USART_u8CHAR_SIZE == SEVEN_BITS_CHAR_SIZE
	Local_u8TempUCSRC &= CHAR_SIZE_MASK;
	CLR_BIT(Local_u8TempUCSRC, UCSRC_UCSZ0);
	SET_BIT(Local_u8TempUCSRC, UCSRC_UCSZ1);
	CLR_BIT(UCSRB,UCSRB_UCSZ2);

#elif USART_u8CHAR_SIZE == EIGHT_BITS_CHAR_SIZE
	Local_u8TempUCSRC &= CHAR_SIZE_MASK;
	SET_BIT(Local_u8TempUCSRC, UCSRC_UCSZ0);
	SET_BIT(Local_u8TempUCSRC, UCSRC_UCSZ1);
	CLR_BIT(UCSRB,UCSRB_UCSZ2);

#elif USART_u8CHAR_SIZE == NINE_BITS_CHAR_SIZE
	Local_u8TempUCSRC &= CHAR_SIZE_MASK;
	SET_BIT(Local_u8TempUCSRC, UCSRC_UCSZ0);
	SET_BIT(Local_u8TempUCSRC, UCSRC_UCSZ1);
	SET_BIT(UCSRB,UCSRB_UCSZ2);

#else
#error Wrong USART_u8CHAR_SIZE configuration option

#endif

	/*Select Synchronization Mode*/
#if USART_u8SYNCH_MODE == SYNCHRONOUS_MODE
	SET_BIT(Local_u8TempUCSRC,UCSRC_UMSEL);

#elif USART_u8SYNCH_MODE == ASYNCHRONOUS_MODE
	CLR_BIT(Local_u8TempUCSRC,UCSRC_UMSEL);

#else
#error Wrong USART_u8SYNCH_MODE configuration type
#endif

	/*Select Parity Mode*/
#if USART_u8PARITY_MODE == DISABLED
	CLR_BIT(Local_u8TempUCSRC,UCSRC_UPM0);
	CLR_BIT(Local_u8TempUCSRC,UCSRC_UPM1);

#elif USART_u8PARITY_MODE == EVEN_PARITY
	CLR_BIT(Local_u8TempUCSRC,UCSRC_UPM0);
	SET_BIT(Local_u8TempUCSRC,UCSRC_UPM1);

#elif USART_u8PARITY_MODE == ODD_PARITY
	SET_BIT(Local_u8TempUCSRC,UCSRC_UPM0);
	SET_BIT(Local_u8TempUCSRC,UCSRC_UPM1);

#else
#error Wrong USART_u8PARITY_MODE configuration type
#endif

	/*Select Stop Bit Mode*/
#if USART_u8STOP_BITS_NUM == ONE_BIT
	CLR_BIT(Local_u8TempUCSRC,UCSRC_USBS);

#elif USART_u8STOP_BITS_NUM == TWO_BITS
	SET_BIT(Local_u8TempUCSRC,UCSRC_USBS);

#else
#error Wrong USART_u8STOP_BITS_NUM configuration type
#endif

	/*Select Mode of UCSRC Register to write on it*/
	SET_BIT(Local_u8TempUCSRC,UCSRC_URSEL);
	UCSRC = Local_u8TempUCSRC;

	/*Set Baud Rate*/
	UBRRL = USART_u8BAUD_RATE;
}

/**
 * @brief 				Function to transmit data by USART up to nine bits.
 * @param Copy_u16Data	Data that will be transmitted by USART.
 * @return				Error State.
 */
uint8 USART_u8Send(uint16 Copy_u16Data)
{
	/*Define Variables*/
	uint8 Local_u8ErrorState = OK;
	uint32 Local_u32TimeoutCounter = 0u;

	/*Check if USART Transmitter is idle or not*/
	if((USART_u8TransmitBusyState == IDLE) || (USART_u8TransmitCallSrc == SYNCH_FUNC_CALL))
	{
		/*Inform Others that transmit channel is busy from now*/
		USART_u8TransmitBusyState = BUSY;

		/*Polling until Transmit Buffer is ready*/
		while(((GET_BIT(UCSRA,UCSRA_UDRE)) == 0) && (Local_u32TimeoutCounter < USART_u32TIMEOUT))
		{
			Local_u32TimeoutCounter++;
		}

		/*Check why the loop has been broken*/
		if(Local_u32TimeoutCounter == USART_u32TIMEOUT)
		{
			/*Loop is broken because the counter exceed timeout counts*/
			Local_u8ErrorState = TIMEOUT_ERR;
		}
		else
		{
			/*Loop is broken because the transmit buffer is ready*/

			/*Set the transmit data*/
			UDR = (uint8) Copy_u16Data;
#if USART_u8CHAR_SIZE == NINE_BITS_CHAR_SIZE
			switch(GET_BIT(Copy_u16Data, 8u))
			{
			case 0u: CLR_BIT(UCSRB,UCSRB_TXB8);	break;
			case 1u: SET_BIT(UCSRB,UCSRB_TXB8);	break;
			}
#endif
		}


		if(USART_u8TransmitCallSrc == MAIN_CALL)
		{
			/*Reset busy flag to be idle*/
			USART_u8TransmitBusyState = IDLE;
		}

	}
	else
	{
		Local_u8ErrorState = BUSY_STATE_ERR;
	}

	/*Return Error state*/
	return Local_u8ErrorState;
}

/**
 * @brief 				Function to receive data by USART up to nine bits.
 * @param Copy_pvData 	Pointer to return the data received.
 * @return 				Error State.
 */
uint8 USART_u8Receive(void *Copy_pvData)
{
	/*Define Variables*/
	uint8 Local_u8ErrorState = OK;

	/*Validate the pointer*/
	if(Copy_pvData != NULL)
	{
		if((USART_u8ReceiveBusyState == IDLE) || (USART_u8ReceiveCallSrc == SYNCH_FUNC_CALL))
		{
			/*Inform Others that Receive channel is busy from now*/
			USART_u8ReceiveBusyState = BUSY;

			/*Polling until USART receive data in receive buffer*/
			while((GET_BIT(UCSRA,UCSRA_RXC)) == 0);

			/*Return data received*/
#if USART_u8CHAR_SIZE < NINE_BITS_CHAR_SIZE
			*(uint8 *) Copy_pvData = UDR;

#elif USART_u8CHAR_SIZE == NINE_BITS_CHAR_SIZE
			*(uint16 *) Copy_pvData = (uint8) UDR;
			switch(GET_BIT(UCSRB,UCSRB_RXB8))
			{
			case 0u: CLR_BIT((*(uint16 *) Copy_pvData),8u);	break;
			case 1u: SET_BIT((*(uint16 *) Copy_pvData),8u);	break;
			}
#endif

			if(USART_u8ReceiveCallSrc == MAIN_CALL)
			{
				/*Reset busy flag to be idle*/
				USART_u8ReceiveBusyState = IDLE;
			}
		}
		else
		{
			Local_u8ErrorState = BUSY_STATE_ERR;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	/*Return Error State*/
	return Local_u8ErrorState;
}


/**
 * @brief 					Function to send a buffer by USART with synchronous operation.
 * @param Copy_pvBufferArr	Pointer to buffer array to be transmitted.
 * @param Copy_u8BufferSize Size of the buffer array.
 * @return 					Error State.
 */
uint8 USART_u8SendBufferSynch(const void *Copy_pvBufferArr, uint8 Copy_u8BufferSize)
{
	/*Define Variables*/
	uint8 Local_u8ErrorState = OK;
	uint8 Local_u8ErrorFounder = OK;
	uint8 Local_u8Counter = 0u;

	/*Validate the pointer*/
	if(Copy_pvBufferArr != NULL)
	{
		if(USART_u8TransmitBusyState == IDLE)
		{
			/*Inform Others that transmit channel is busy from now*/
			USART_u8TransmitBusyState = BUSY;

			/*Inform function USART_u8Send that I am the caller*/
			USART_u8TransmitCallSrc = SYNCH_FUNC_CALL;

			/*Pass over all the buffer elements*/
			for(Local_u8Counter = 0u; Local_u8Counter < Copy_u8BufferSize; Local_u8Counter++)
			{
#if USART_u8CHAR_SIZE < NINE_BITS_CHAR_SIZE
				/*Transmit each element with function USART_u8Send*/
				Local_u8ErrorFounder = USART_u8Send((uint8) (*((uint8 *) Copy_pvBufferArr + Local_u8Counter)));

#elif USART_u8CHAR_SIZE == NINE_BITS_CHAR_SIZE
				/*Transmit each element with function USART_u8Send*/
				Local_u8ErrorFounder = USART_u8Send(*((uint16 *) Copy_pvBufferArr + Local_u8Counter));

#endif

				/*Check that the transmission operation goes well*/
				if(Local_u8ErrorFounder != OK)
				{
					Local_u8ErrorState = NOK;
					break;
				}
			}

			/*Inform function USART_u8Send that main is the caller from now*/
			USART_u8TransmitCallSrc = MAIN_CALL;

			/*Reset busy flag to be idle*/
			USART_u8TransmitBusyState = IDLE;
		}
		else
		{
			Local_u8ErrorState = BUSY_STATE_ERR;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	/*Return Error State*/
	return Local_u8ErrorState;
}


/**
 * @brief 						Function to send a buffer by USART with synchronous operation.
 * @param Copy_pu16BufferArr 	Pointer to buffer array to be transmitted.
 * @param Copy_u8BufferSize 	Size of the buffer array.
 * @return 						Error State.
 */
uint8 USART_u8ReceiveBufferSynch(uint8 *Copy_pu8BufferArr, uint8 Copy_u8BufferSize)
{
	/*Define Variables*/
	uint8 Local_u8ErrorState = OK;
	uint8 Local_u8ErrorFounder = OK;
	uint8 Local_u8Counter = 0u;

	/*Validate the pointer*/
	if(Copy_pu8BufferArr != NULL)
	{
		if(USART_u8ReceiveBusyState == IDLE)
		{
			/*Inform Others that Receive channel is busy from now*/
			USART_u8ReceiveBusyState = BUSY;

			/*Inform function USART_u8Receive that I am the caller*/
			USART_u8ReceiveCallSrc = SYNCH_FUNC_CALL;

			/*Pass over all the buffer elements*/
			for(Local_u8Counter = 0u; Local_u8Counter < Copy_u8BufferSize; Local_u8Counter++)
			{
				/*Transmit each element with function USART_u8Transmit*/
				Local_u8ErrorFounder = USART_u8Receive(&Copy_pu8BufferArr[Local_u8Counter]);

				/*Check that the Receive operation goes well*/
				if(Local_u8ErrorFounder != OK)
				{
					Local_u8ErrorState = NOK;
					break;
				}
			}

			/*Inform function USART_u8Receive that main is the caller from now*/
			USART_u8ReceiveCallSrc = MAIN_CALL;

			/*Reset busy flag to be idle*/
			USART_u8ReceiveBusyState = IDLE;
		}
		else
		{
			Local_u8ErrorState = BUSY_STATE_ERR;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	/*Return Error State*/
	return Local_u8ErrorState;
}

/**
 * @brief 							Function to send a buffer by USART with asynchronous operation.
 * @param Copy_pvBufferArr 			Pointer to buffer array to be transmitted.
 * @param Copy_u8BufferSize			Size of the buffer array.
 * @param Copy_pvNotificationFunc	Pointer to the notification function.
 * @return 							Error state.
 */
uint8 USART_u8SendBufferAsynch(void *Copy_pvBufferArr, uint8 Copy_u8BufferSize, void (*Copy_pvNotificationFunc)(void))
{
	/*Define Variables*/
	uint8 Local_u8ErrorState = OK;

	/*Validate Pointers passed*/
	if((Copy_pvBufferArr != NULL) && (Copy_pvNotificationFunc != NULL))
	{
		if(USART_u8TransmitBusyState == IDLE)
		{
			/*Inform Others that Transmit channel is busy from now*/
			USART_u8TransmitBusyState = BUSY;

			/*Initialize buffer pointer as global*/
			USART_pvTransmitBufferArr = Copy_pvBufferArr;

			/*Initialize buffer size as global*/
			USART_u8TransmitBufferSize = Copy_u8BufferSize;

			/*Initialize notification function as global*/
			USART_pvTransmitNotificationFunc = Copy_pvNotificationFunc;

			/*Set the buffer counter to 0*/
			USART_u8TransmitBufferCounter = 0u;

			/*Enable USART Data Register Empty Interrupt*/
			SET_BIT(UCSRB,UCSRB_UDRIE);
		}
		else
		{
			Local_u8ErrorState = BUSY_STATE_ERR;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	/*Return Error State*/
	return Local_u8ErrorState;
}

/**
 * @brief 							Function to receive a buffer by USART with asynchronous operation.
 * @param Copy_pvBufferArr 			Pointer to buffer array to return data on it.
 * @param Copy_u8Bufferize 			Size of the buffer array.
 * @param Copy_pvNotificationFunc 	Pointer to the notification function.
 * @return 							Error State.
 */
uint8 USART_u8ReceiveBufferAsynch(void *Copy_pvBufferArr, uint8 Copy_u8Bufferize, void (*Copy_pvNotificationFunc)(void))
{
	/*Define Variables*/
	uint8 Local_u8ErrorState = OK;

	/*Validate Pointers passed*/
	if((Copy_pvBufferArr != NULL) && (Copy_pvNotificationFunc != NULL))
	{
		if(USART_u8ReceiveBusyState == IDLE)
		{
			/*Inform Others that Receive channel is busy from now*/
			USART_u8ReceiveBusyState = BUSY;

			/*Initialize buffer pointer as global*/
			USART_pvReceiveBufferArr = Copy_pvBufferArr;

			/*Initialize buffer size as global*/
			USART_u8ReceiveBufferSize = Copy_u8Bufferize;

			/*Initialize notification function as global*/
			USART_pvReceiveNotificationFunc = Copy_pvNotificationFunc;

			/*Set the buffer counter to 0*/
			USART_u8ReceiveBufferCounter = 0u;

			/*Enable USART RX Complete Interrupt*/
			SET_BIT(UCSRB,UCSRB_RXCIE);
		}
		else
		{
			Local_u8ErrorState = BUSY_STATE_ERR;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	/*Return Error State*/
	return Local_u8ErrorState;
}

/**
 * @brief USART Receive Complete ISR.
 */
void __vector_13 (void) __attribute((signal));
void __vector_13 (void)
{
	/*Return data received*/
#if USART_u8CHAR_SIZE < NINE_BITS_CHAR_SIZE
	*((uint8 *) USART_pvReceiveBufferArr + USART_u8ReceiveBufferCounter) = UDR;

#elif USART_u8CHAR_SIZE == NINE_BITS_CHAR_SIZE
	*((uint16 *) USART_pvReceiveBufferArr + USART_u8ReceiveBufferCounter) = (uint8) UDR;
	switch(GET_BIT(UCSRB,UCSRB_RXB8))
	{
	case 0u: CLR_BIT(*(((uint16 *) USART_pvReceiveBufferArr) + USART_u8ReceiveBufferCounter),8u);	break;
	case 1u: SET_BIT(*(((uint16 *) USART_pvReceiveBufferArr) + USART_u8ReceiveBufferCounter),8u);	break;
	}
#endif

	/*Increment Receive Buffer Counter*/
	USART_u8ReceiveBufferCounter++;

	/*If USART reached the end of the buffer*/
	if(USART_u8ReceiveBufferCounter == USART_u8ReceiveBufferSize)
	{
		/*Reset busy flag for receive channel to be idle*/
		USART_u8ReceiveBusyState = IDLE;

		/*Disable USART Data Register Empty Interrupt*/
		CLR_BIT(UCSRB,UCSRB_RXCIE);

		/*Call Notification Function*/
		if(USART_pvReceiveNotificationFunc != NULL)
		{
			USART_pvReceiveNotificationFunc();
		}
		else
		{
			/*Do nothing*/
		}
	}
}

/**
 * @brief USART Data Register Empty ISR.
 */
void __vector_14 (void) __attribute((signal));
void __vector_14 (void)
{
	/*Set the data to the transmit register*/
#if USART_u8CHAR_SIZE < NINE_BITS_CHAR_SIZE
	UDR = *(((uint8 *) USART_pvTransmitBufferArr) + USART_u8TransmitBufferCounter);

#elif USART_u8CHAR_SIZE == NINE_BITS_CHAR_SIZE
	UDR = *(((uint16 *) USART_pvTransmitBufferArr) + USART_u8TransmitBufferCounter);
	switch(GET_BIT(*(((uint16 *) USART_pvTransmitBufferArr) + USART_u8TransmitBufferCounter), 8u))
	{
	case 0u: CLR_BIT(UCSRB,UCSRB_TXB8);	break;
	case 1u: SET_BIT(UCSRB,UCSRB_TXB8);	break;
	}
#endif

	/*Increment Transmit Buffer Counter*/
	USART_u8TransmitBufferCounter++;

	/*If USART reached the end of the buffer*/
	if(USART_u8TransmitBufferCounter == USART_u8TransmitBufferSize)
	{
		/*Reset busy flag for transmit channel to be idle*/
		USART_u8TransmitBusyState = IDLE;

		/*Disable USART Data Register Empty Interrupt*/
		CLR_BIT(UCSRB,UCSRB_UDRIE);

		/*Call Notification Function*/
		if(USART_pvTransmitNotificationFunc != NULL)
		{
			USART_pvTransmitNotificationFunc();
		}
		else
		{
			/*Do nothing*/
		}
	}
}

/**
 * @brief USART transmission Complete ISR.
 */
void __vector_15 (void) __attribute((signal));
void __vector_15 (void)
{

}
