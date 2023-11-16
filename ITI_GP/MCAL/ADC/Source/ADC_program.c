/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: ADC_program.c			**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file ADC_program.c
 * @author Ibrahim Tarek
 * @brief This file implements the ADC module functions.
 * @version 1.00
 */

#include "../../../Common/STD_TYPES.h"
#include "../../../Common/BIT_MATH.h"
#include "../../../Common/DEFINES.h"

#include "../Header/ADC_register.h"
#include "../Header/ADC_config.h"
#include "../Header/ADC_private.h"
#include "../Header/ADC_interface.h"

/*Define global variables*/
static void (* ADC_pvNotificationFunc)(void) = NULL;

static uint16 *ADC_pu16ConversionResult = NULL;

static uint8 ADC_u8BusyFlag = IDLE;

static ADC_ChainConv_t *ADC_pstChainData = NULL;

static uint8 ADC_u8ChainChannelCounter;

static uint8 ADC_u8IntSource;

/**
 * @brief Function to initialize ADC with prebuild configuration.
 */
void ADC_voidInit(void)
{
	/*Reference Selection*/
#if	ADC_u8REF_VOLT == AREF_REF
	CLR_BIT(ADMUX,ADMUX_REFS0);
	CLR_BIT(ADMUX,ADMUX_REFS1);

#elif ADC_u8REF_VOLT == AVCC_REF
	SET_BIT(ADMUX,ADMUX_REFS0);
	CLR_BIT(ADMUX,ADMUX_REFS1);

#elif ADC_u8REF_VOLT == INTERNAL_2560mV_REF
	SET_BIT(ADMUX,ADMUX_REFS0);
	SET_BIT(ADMUX,ADMUX_REFS1);

#else
#error Wrong ADC_u8REF_VOLT configuration option

#endif

	/*Left Adjust Result Selection*/
#if	ADC_u8RESOLUTION == EIGHT_BITS
	SET_BIT(ADMUX,ADMUX_ADLAR);

#elif ADC_u8RESOLUTION == TEN_BITS
	CLR_BIT(ADMUX,ADMUX_ADLAR);

#else
#error Wrong ADC_u8RESOLUTION configuration option

#endif

	/*Prescaler Selection*/
	ADCSRA = ADCSRA & PRESCALER_MASK;
	ADCSRA = ADCSRA | ADC_u8PRESCALER_VALUE;

	/*Enable the ADC*/
	SET_BIT(ADCSRA,ADCSRA_ADEN);
}


/**
 * @brief Function to get the reading of an ADC channel.
 * @param Copy_u8Channel The number of channel you want to read.
 * @param Copy_pu16Result This pointer return the reading of the channel selected.
 * @return Error State of the function.
 */
uint8 ADC_u8StartConversionSynch(uint8 Copy_u8Channel, uint16 *Copy_pu16Result)
{
	/*Define variables*/
	uint8 Local_u8ErrorState = OK;
	uint32 Local_u32TimeoutCounter = 0u;

	/*Validate Copy_pu16Rsult*/
	if(Copy_pu16Result != NULL)
	{
		if(ADC_u8BusyFlag == IDLE)
		{
			/*Inform others that adc is busy*/
			ADC_u8BusyFlag = BUSY;

			/*Set the required channel*/
			ADMUX = ADMUX & CHANNEL_MASK;
			ADMUX = ADMUX | Copy_u8Channel;

			/*Start Conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			/*Polling until the interrupt flag rise*/
			while((GET_BIT(ADCSRA,ADCSRA_ADIF) == 0) && (Local_u32TimeoutCounter < ADC_u32TIMEOUT))
			{
				Local_u32TimeoutCounter++;
			}

			/*Check why the loop has been broken*/
			if(Local_u32TimeoutCounter == ADC_u32TIMEOUT)
			{
				/*Loop is broken because the conversion exceed timeout counter*/
				Local_u8ErrorState = TIMEOUT_ERR;
			}
			else
			{
				/*Loop is broken because the conversion has been done*/

				/*Clear the conversion complete flag flag*/
				SET_BIT(ADCSRA,ADCSRA_ADIF);

				/*Return the data*/
#if ADC_u8RESOLUTION == EIGHT_BITS
				*Copy_pu16Result = ADCH;

#elif ADC_u8RESOLUTION == TEN_BITS
				*Copy_pu16Result = ADC;
#endif
			}

			/*Inform others that ADC is idle now*/
			ADC_u8BusyFlag = IDLE;
		}
		else
		{
			/*ADC is busy now*/
			Local_u8ErrorState = BUSY_STATE_ERR;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	/*Return the error state*/
	return Local_u8ErrorState;
}


/**
 * @brief Function to get the reading of an ADC channel.
 * @note You should enable GIE before using this function.
 * @param Copy_u8Channel The number of channel you want to read.
 * @param Copy_pu16Result This pointer return the reading of the channel selected.
 * @param Copy_pvNotificationFunc This pointer set call back the notification function from the application layer.
 * @return Error State of the function.
 */
uint8 ADC_u8StartConversionAsynch(uint8 Copy_u8Channel, uint16 *Copy_pu16Result, void (*Copy_pvNotificationFunc)(void))
{

	/*Define variables*/
	uint8 Local_u8ErrorState = OK;

	/*Validate Copy_pu16Rsult*/
	if((Copy_pu16Result != NULL) && (Copy_pvNotificationFunc != NULL))
	{
		/*Check if ADC is busy or idle*/
		if(ADC_u8BusyFlag == IDLE)
		{
			/*Inform others that ADC is busy now*/
			ADC_u8BusyFlag = BUSY;

			/*Inform ISR the interrupt source*/
			ADC_u8IntSource = SINGLE_CONV_ASYNCH;

			/*Initialize the result pointer globally*/
			ADC_pu16ConversionResult = Copy_pu16Result;

			/*Initialize the notification function globally*/
			ADC_pvNotificationFunc = Copy_pvNotificationFunc;

			/*Set the required channel*/
			ADMUX = ADMUX & CHANNEL_MASK;
			ADMUX = ADMUX | Copy_u8Channel;

			/*Start Conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			/*Enable ADC Conversion Complete Interrupt*/
			SET_BIT(ADCSRA,ADCSRA_ADIE);
		}
		else
		{
			/*ADC is busy now*/
			Local_u8ErrorState = BUSY_STATE_ERR;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	/*Return the error state*/
	return Local_u8ErrorState;
}

/**
 * @brief Function to get the reading of a series of channels.
 * @param Copy_pstChain Pointer to struct which carry the chain data.
 * @return Error State of the function.
 */
uint8 ADC_u8StartChainConversionAsynch(ADC_ChainConv_t *Copy_pstChain)
{
	/*Define Error State*/
	uint8 Local_u8ErrorState = OK;

	/*Validate Pointers*/
	if((Copy_pstChain != NULL) && (Copy_pstChain -> ChainArr != NULL) && (Copy_pstChain -> NotificationFunc != NULL) && (Copy_pstChain -> ResultArr != NULL))
	{
		/*Check if ADC is busy or not*/
		if(ADC_u8BusyFlag == IDLE)
		{
			/*Inform others that ADC is busy now*/
			ADC_u8BusyFlag = BUSY;

			/*Inform the ISR the interrupt source*/
			ADC_u8IntSource = CHAIN_CONV_ASYNCH;

			/*Initialize the global chain data*/
			ADC_pstChainData = Copy_pstChain;
			ADC_u8ChainChannelCounter = 0u;

			/*Set the first channel*/
			ADMUX &= CHANNEL_MASK;
			ADMUX |= ADC_pstChainData -> ChainArr[ADC_u8ChainChannelCounter];

			/*Start the conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			/*Enable the ADC conversion complete interrupt*/
			SET_BIT(ADCSRA,ADCSRA_ADIE);
		}
		else
		{
			Local_u8ErrorState = BUSY_STATE_ERR;
		}
	}
	/*Return Error State*/
	return Local_u8ErrorState;
}

/**
 * @brief ADC Conversion Complete ISR.
 */
void __vector_16 (void) __attribute((signal));
void __vector_16 (void)
{
	if(ADC_u8IntSource == SINGLE_CONV_ASYNCH)
	{
		if(ADC_pu16ConversionResult != NULL)
		{
			/*Return the data*/
#if ADC_u8RESOLUTION == EIGHT_BITS
			*ADC_pu16ConversionResult = ADCH;

#elif ADC_u8RESOLUTION == TEN_BITS
			*ADC_pu16ConversionResult = ADC;
#endif

			/*Disable ADC Conversion Complete Interrupt*/
			CLR_BIT(ADCSRA,ADCSRA_ADIE);

			/*Inform others that ADC is idle now*/
			ADC_u8BusyFlag = IDLE;

			/*Invoke the application notification function*/
			if(ADC_pvNotificationFunc != NULL)
			{
				ADC_pvNotificationFunc();
			}
			else
			{
				/*Notification pointer is assigned to NULL*/
			}
		}
		else
		{
			/*Result pointer is assigned to NULL*/
		}
	}
	else if(ADC_u8IntSource == CHAIN_CONV_ASYNCH)
	{
		if(ADC_pstChainData != NULL)
		{
			/*Return the channel result*/
#if ADC_u8RESOLUTION == EIGHT_BITS
			ADC_pstChainData -> ResultArr[ADC_u8ChainChannelCounter] = ADCH;

#elif ADC_u8RESOLUTION == TEN_BITS
			ADC_pstChainData -> ResultArr[ADC_u8ChainChannelCounter] = ADC;
#endif

			/*Increment the counter*/
			ADC_u8ChainChannelCounter++;

			if(ADC_u8ChainChannelCounter < ADC_pstChainData -> ChainSize)	//Chain is not finished yet.
			{
				/*Set the next channel*/
				ADMUX &= CHANNEL_MASK;
				ADMUX |= ADC_pstChainData -> ChainArr[ADC_u8ChainChannelCounter];

				/*Start the next Conversion*/
				SET_BIT(ADCSRA,ADCSRA_ADSC);
			}
			else 															//Chain is finished.
			{
				/*Disable ADC Conversion Complete Interrupt*/
				CLR_BIT(ADCSRA,ADCSRA_ADIE);

				/*Inform others that ADC is idle now*/
				ADC_u8BusyFlag = IDLE;

				/*Invoke the application notification function*/
				if(ADC_pstChainData -> NotificationFunc != NULL)
				{
					ADC_pstChainData -> NotificationFunc();
				}
				else
				{
					/*Notification pointer is assigned to NULL*/
				}
			}
		}
	}
}
