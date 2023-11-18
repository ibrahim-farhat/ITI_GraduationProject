/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: TIMERS_program.c		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file TIMERS_program.c
 * @author Ibrahim Tarek
 * @brief This file implements the TIMERS module functions.
 * @version 1.00
 */

#include "../../../Common/STD_TYPES.h"
#include "../../../Common/BIT_MATH.h"
#include "../../../Common/DEFINES.h"

#include "../Header/TIMERS_interface.h"
#include "../Header/TIMERS_config.h"
#include "../Header/TIMERS_private.h"
#include "../Header/TIMERS_register.h"

/*Define array of pointer to call back functions*/
static void (* TIMERS_pvCallBackFuncArr[8])(void);

/*Define array of timers state (BUSY/IDLE)*/
static uint8 TIMERS_u8StateArr[3] = {IDLE};

/**
 * @brief 						Function to initialize timer 0 peripheral.
 * @param Copy_pstTimerConfig	Struct to configure timer 0 options.
 * @return						Error State.
 */
uint8 TIMER0_u8Init(const TIMER0_2_CFG_t *Copy_pstTimerConfig)
{
	/*Define Variables*/
	uint8 Local_u8ErrorState = OK;

	/*Validate the pointer to structure*/
	if(Copy_pstTimerConfig != NULL)
	{
		if(TIMERS_u8StateArr[TIMER0] == IDLE)
		{
			/*Inform others that timer 0 is busy*/
			TIMERS_u8StateArr[TIMER0] = BUSY;

			/*Select Wave Generation Mode*/
			switch(Copy_pstTimerConfig -> WGM)
			{
			case NORMAL:	CLR_BIT(TCCR0,TCCR0_WGM00);	CLR_BIT(TCCR0,TCCR0_WGM01);	break;
			case PHASE_CORR:SET_BIT(TCCR0,TCCR0_WGM00);	CLR_BIT(TCCR0,TCCR0_WGM01);	break;
			case CTC:		CLR_BIT(TCCR0,TCCR0_WGM00);	SET_BIT(TCCR0,TCCR0_WGM01);	break;
			case FAST_PWM:	SET_BIT(TCCR0,TCCR0_WGM00);	SET_BIT(TCCR0,TCCR0_WGM01);	break;
			}

			/*Select Output Compare Match Mode*/
			TCCR0 &= TIMER0_2_OCMATCH_MASK;
			if((Copy_pstTimerConfig -> WGM == NORMAL) || (Copy_pstTimerConfig -> WGM == CTC))
			{
				if((Copy_pstTimerConfig -> OCMode) < NON_INVERTED_PWM)
				{
					TCCR0 |= ((Copy_pstTimerConfig -> OCMode) << 4);
				}
				else
				{
					Local_u8ErrorState = NOK;
				}
			}
			else if((Copy_pstTimerConfig -> WGM == FAST_PWM) || (Copy_pstTimerConfig -> WGM == PHASE_CORR))
			{
				switch(Copy_pstTimerConfig -> OCMode)
				{
				case OC_DISCONNECTED:	TCCR0 |= (0 << 4);	break;
				case NON_INVERTED_PWM:	TCCR0 |= (2 << 4);	break;
				case INVERTED_PWM:		TCCR0 |= (3 << 4);	break;
				default: Local_u8ErrorState = NOK;
				}
			}

			/*Select the clock*/
			TCCR0 &= PRESCALER_MASK;
			TCCR0 |= Copy_pstTimerConfig -> ClkSelect;
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
 * @brief 						Function to initialize timer 1 peripheral.
 * @param Copy_pstTimerConfig	Struct to configure timer 1 options.
 * @return						Error State.
 */
uint8 TIMER1_u8Init(const TIMER1_CFG_t *Copy_pstTimerConfig)
{
	/*Define Variables*/
	uint8 Local_u8ErrorState = OK;

	/*Validate the pointer to structure*/
	if(Copy_pstTimerConfig != NULL)
	{
		if(TIMERS_u8StateArr[TIMER1] == IDLE)
		{
			/*Inform others that timer 1 is busy from now*/
			TIMERS_u8StateArr[TIMER1] = BUSY;

			/*Select Wave Generation Mode*/
			TCCR1A &= TIMER1_WGM_MASK_A;
			TCCR1B &= TIMER1_WGM_MASK_B;
			TCCR1A |= ((Copy_pstTimerConfig -> WGM) & 3);
			TCCR1B |= ((((Copy_pstTimerConfig -> WGM) >> 2) & 3) << 3);

			/*Select Output Compare Match Mode*/
			switch(Copy_pstTimerConfig -> WGM)
			{
			case NORMAL_16_BITS:
			case CTC_OCR1A:
			case CTC_ICR1:
				/*For Channel A*/
				if((Copy_pstTimerConfig -> OCAMode) < NON_INVERTED_PWM)
				{
					TCCR1A &= TIMER1_OCMATCH_A_MASK;
					TCCR1A |= ((Copy_pstTimerConfig -> OCAMode) << 6);
				}
				else if((Copy_pstTimerConfig -> OCAMode) == DO_NOT_CHANGE)
				{
					/*Do nothing*/
				}
				else
				{
					Local_u8ErrorState = NOK;
				}
				/*For Channel B*/
				if((Copy_pstTimerConfig -> OCBMode) < NON_INVERTED_PWM)
				{
					TCCR1A &= TIMER1_OCMATCH_B_MASK;
					TCCR1A |= ((Copy_pstTimerConfig -> OCBMode) << 4);
				}
				else if((Copy_pstTimerConfig -> OCBMode) == DO_NOT_CHANGE)
				{
					/*Do nothing*/
				}
				else
				{
					Local_u8ErrorState = NOK;
				}
				break;

			case FAST_PWM_8_BITS:
			case FAST_PWM_9_BITS:
			case FAST_PWM_10_BITS:
			case FAST_PWM_ICR1:
			case FAST_PWM_OCR1A:
			case PHASE_CORR_8_BITS:
			case PHASE_CORR_9_BITS:
			case PHASE_CORR_10_BITS:
			case PHASE_FREQ_CORR_ICR1:
			case PHASE_FREQ_CORR_OCR1A:
			case PHASE_CORR_ICR1:
			case PHASE_CORR_OCR1A:
				/*For Channel A*/
				switch(Copy_pstTimerConfig -> OCAMode)
				{
				case OC_DISCONNECTED:	TCCR1A &= TIMER1_OCMATCH_A_MASK;	TCCR1A |= (0 << 6);	break;
				case NON_INVERTED_PWM:	TCCR1A &= TIMER1_OCMATCH_A_MASK;	TCCR1A |= (2 << 6);	break;
				case INVERTED_PWM:		TCCR1A &= TIMER1_OCMATCH_A_MASK;	TCCR1A |= (3 << 6);	break;
				case DO_NOT_CHANGE:		/*Do nothing*/											break;
				default: Local_u8ErrorState = NOK;
				}
				/*For Channel B*/
				switch(Copy_pstTimerConfig -> OCBMode)
				{
				case OC_DISCONNECTED:	TCCR1A &= TIMER1_OCMATCH_B_MASK;	TCCR1A |= (0 << 4);	break;
				case NON_INVERTED_PWM:	TCCR1A &= TIMER1_OCMATCH_B_MASK;	TCCR1A |= (2 << 4);	break;
				case INVERTED_PWM:		TCCR1A &= TIMER1_OCMATCH_B_MASK;	TCCR1A |= (3 << 4);	break;
				case DO_NOT_CHANGE:		/*Do nothing*/											break;
				default: Local_u8ErrorState = NOK;
				}
				break;

			default:Local_u8ErrorState = NOK;	break;
			}

			/*Select the clock*/
			TCCR1B &= PRESCALER_MASK;
			TCCR1B |= Copy_pstTimerConfig -> ClkSelect;
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
 * @brief 						Function to initialize timer 2 peripheral.
 * @param Copy_pstTimerConfig	Struct to configure timer 2 otions.
 * @return						Error State.
 */
uint8 TIMER2_u8Init(const TIMER0_2_CFG_t *Copy_pstTimerConfig)
{
	/*Define Variables*/
	uint8 Local_u8ErrorState = OK;

	/*Validate the pointer to structure*/
	if(Copy_pstTimerConfig != NULL)
	{
		if(TIMERS_u8StateArr[TIMER2] == IDLE)
		{
			/*Inform others that timer 2 is busy from now*/
			TIMERS_u8StateArr[TIMER2] = BUSY;

			/*Select Wave Generation Mode*/
			switch(Copy_pstTimerConfig -> WGM)
			{
			case NORMAL:	CLR_BIT(TCCR2,TCCR2_WGM20);	CLR_BIT(TCCR2,TCCR2_WGM21);	break;
			case PHASE_CORR:SET_BIT(TCCR2,TCCR2_WGM20);	CLR_BIT(TCCR2,TCCR2_WGM21);	break;
			case CTC:		CLR_BIT(TCCR2,TCCR2_WGM20);	SET_BIT(TCCR2,TCCR2_WGM21);	break;
			case FAST_PWM:	SET_BIT(TCCR2,TCCR2_WGM20);	SET_BIT(TCCR2,TCCR2_WGM21);	break;
			}

			/*Select Output Compare Match Mode*/
			TCCR2 &= TIMER0_2_OCMATCH_MASK;
			if((Copy_pstTimerConfig -> WGM == NORMAL) || (Copy_pstTimerConfig -> WGM == CTC))
			{
				if((Copy_pstTimerConfig -> OCMode) < NON_INVERTED_PWM)
				{
					TCCR2 |= ((Copy_pstTimerConfig -> OCMode) << 4);
				}
				else
				{
					Local_u8ErrorState = NOK;
				}
			}
			else if((Copy_pstTimerConfig -> WGM == FAST_PWM) || (Copy_pstTimerConfig -> WGM == PHASE_CORR))
			{
				switch(Copy_pstTimerConfig -> OCMode)
				{
				case OC_DISCONNECTED:	TCCR2 |= (0 << 4);	break;
				case NON_INVERTED_PWM:	TCCR2 |= (2 << 4);	break;
				case INVERTED_PWM:		TCCR2 |= (3 << 4);	break;
				default: Local_u8ErrorState = NOK;
				}
			}

			/*Select the clock*/
			TCCR2 &= PRESCALER_MASK;
			TCCR2 |= Copy_pstTimerConfig -> ClkSelect;
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
 * @brief 						Function to set the compare output mode of timer 0.
 * @param Copy_pstTimerConfig	Struct of the timer configurations.
 * @param Copy_u8Mode			Compare output mode which needed to be set.
 * @return						Error State.
 */
uint8 TIMER0_u8SetCompOutMode(const TIMER0_2_CFG_t *Copy_pstTimerConfig, TIMERS_OC_MODE_t Copy_u8Mode)
{
	/*Define Variables*/
	uint8 Local_u8ErrorState = OK;

	/*Validate the pointer*/
	if(Copy_pstTimerConfig != NULL)
	{
		TCCR0 &= TIMER0_2_OCMATCH_MASK;
		if((Copy_pstTimerConfig -> WGM == NORMAL) || (Copy_pstTimerConfig -> WGM == CTC))
		{
			if(Copy_u8Mode < NON_INVERTED_PWM)
			{
				TCCR0 |= (Copy_u8Mode << 4);
			}
			else
			{
				Local_u8ErrorState = NOK;
			}
		}
		else if((Copy_pstTimerConfig -> WGM == FAST_PWM) || (Copy_pstTimerConfig -> WGM == PHASE_CORR))
		{
			switch(Copy_u8Mode)
			{
			case OC_DISCONNECTED:	TCCR0 |= (0 << 4);	break;
			case NON_INVERTED_PWM:	TCCR0 |= (2 << 4);	break;
			case INVERTED_PWM:		TCCR0 |= (3 << 4);	break;
			default: Local_u8ErrorState = NOK;
			}
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
 * @brief 						Function to set the compare output mode of timer 1 channel A.
 * @param Copy_pstTimerConfig	Struct of the timer configurations.
 * @param Copy_u8Mode			Compare output mode which needed to be set.
 * @return						Error State.
 */
uint8 TIMER1_u8SetCompOutModeChA(const TIMER1_CFG_t *Copy_pstTimerConfig, TIMERS_OC_MODE_t Copy_u8Mode)
{
	/*Define Variables*/
	uint8 Local_u8ErrorState = OK;

	/*Validate the pointer*/
	if(Copy_pstTimerConfig != NULL)
	{
		/*Select Output Compare Match Mode*/
		switch(Copy_pstTimerConfig -> WGM)
		{
		case NORMAL_16_BITS:
		case CTC_OCR1A:
		case CTC_ICR1:
			/*For Channel A*/
			if(Copy_u8Mode < NON_INVERTED_PWM)
			{
				TCCR1A &= TIMER1_OCMATCH_A_MASK;
				TCCR1A |= (Copy_u8Mode << 6);
			}
			else if(Copy_u8Mode == DO_NOT_CHANGE)
			{
				/*Do nothing*/
			}
			else
			{
				Local_u8ErrorState = NOK;
			}
			break;

		case FAST_PWM_8_BITS:
		case FAST_PWM_9_BITS:
		case FAST_PWM_10_BITS:
		case FAST_PWM_ICR1:
		case FAST_PWM_OCR1A:
		case PHASE_CORR_8_BITS:
		case PHASE_CORR_9_BITS:
		case PHASE_CORR_10_BITS:
		case PHASE_FREQ_CORR_ICR1:
		case PHASE_FREQ_CORR_OCR1A:
		case PHASE_CORR_ICR1:
		case PHASE_CORR_OCR1A:
			/*For Channel A*/
			switch(Copy_u8Mode)
			{
			case OC_DISCONNECTED:	TCCR1A &= TIMER1_OCMATCH_A_MASK;	TCCR1A |= (0 << 6);	break;
			case NON_INVERTED_PWM:	TCCR1A &= TIMER1_OCMATCH_A_MASK;	TCCR1A |= (2 << 6);	break;
			case INVERTED_PWM:		TCCR1A &= TIMER1_OCMATCH_A_MASK;	TCCR1A |= (3 << 6);	break;
			case DO_NOT_CHANGE:		/*Do nothing*/											break;
			default: Local_u8ErrorState = NOK;
			}
			break;

		default:Local_u8ErrorState = NOK;	break;
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
 * @brief 						Function to set the compare output mode of timer 1 channel B.
 * @param Copy_pstTimerConfig	Struct of the timer configurations.
 * @param Copy_u8Mode			Compare output mode which needed to be set.
 * @return						Error State.
 */
uint8 TIMER1_u8SetCompOutModeChB(const TIMER1_CFG_t *Copy_pstTimerConfig, TIMERS_OC_MODE_t Copy_u8Mode)
{
	/*Define Variables*/
	uint8 Local_u8ErrorState = OK;

	/*Validate the pointer*/
	if(Copy_pstTimerConfig != NULL)
	{
		switch(Copy_pstTimerConfig -> WGM)
		{
		case NORMAL_16_BITS:
		case CTC_OCR1A:
		case CTC_ICR1:
			/*For Channel B*/
			if(Copy_u8Mode < NON_INVERTED_PWM)
			{
				TCCR1A &= TIMER1_OCMATCH_B_MASK;
				TCCR1A |= (Copy_u8Mode << 4);
			}
			else if(Copy_u8Mode == DO_NOT_CHANGE)
			{
				/*Do nothing*/
			}
			else
			{
				Local_u8ErrorState = NOK;
			}
			break;

		case FAST_PWM_8_BITS:
		case FAST_PWM_9_BITS:
		case FAST_PWM_10_BITS:
		case FAST_PWM_ICR1:
		case FAST_PWM_OCR1A:
		case PHASE_CORR_8_BITS:
		case PHASE_CORR_9_BITS:
		case PHASE_CORR_10_BITS:
		case PHASE_FREQ_CORR_ICR1:
		case PHASE_FREQ_CORR_OCR1A:
		case PHASE_CORR_ICR1:
		case PHASE_CORR_OCR1A:
			/*For Channel B*/
			switch(Copy_u8Mode)
			{
			case OC_DISCONNECTED:	TCCR1A &= TIMER1_OCMATCH_B_MASK;	TCCR1A |= (0 << 4);	break;
			case NON_INVERTED_PWM:	TCCR1A &= TIMER1_OCMATCH_B_MASK;	TCCR1A |= (2 << 4);	break;
			case INVERTED_PWM:		TCCR1A &= TIMER1_OCMATCH_B_MASK;	TCCR1A |= (3 << 4);	break;
			case DO_NOT_CHANGE:		/*Do nothing*/											break;
			default: Local_u8ErrorState = NOK;
			}
			break;

		default:Local_u8ErrorState = NOK;	break;
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
 * @brief 						Function to set the compare output mode of timer 2.
 * @param Copy_pstTimerConfig	Struct of the timer configurations.
 * @param Copy_u8Mode			Compare output mode which needed to be set.
 * @return						Error State.
 */
uint8 TIMER2_u8SetCompOutMode(const TIMER0_2_CFG_t *Copy_pstTimerConfig, TIMERS_OC_MODE_t Copy_u8Mode)
{
	/*Define Variables*/
	uint8 Local_u8ErrorState = OK;

	/*Validate the pointer*/
	if(Copy_pstTimerConfig != NULL)
	{
		/*Select Wave Generation Mode*/
		switch(Copy_pstTimerConfig -> WGM)
		{
		case NORMAL:	CLR_BIT(TCCR2,TCCR2_WGM20);	CLR_BIT(TCCR2,TCCR2_WGM21);	break;
		case PHASE_CORR:SET_BIT(TCCR2,TCCR2_WGM20);	CLR_BIT(TCCR2,TCCR2_WGM21);	break;
		case CTC:		CLR_BIT(TCCR2,TCCR2_WGM20);	SET_BIT(TCCR2,TCCR2_WGM21);	break;
		case FAST_PWM:	SET_BIT(TCCR2,TCCR2_WGM20);	SET_BIT(TCCR2,TCCR2_WGM21);	break;
		}

		/*Select Output Compare Match Mode*/
		TCCR2 &= TIMER0_2_OCMATCH_MASK;
		if((Copy_pstTimerConfig -> WGM == NORMAL) || (Copy_pstTimerConfig -> WGM == CTC))
		{
			if(Copy_u8Mode < NON_INVERTED_PWM)
			{
				TCCR2 |= (Copy_u8Mode << 4);
			}
			else
			{
				Local_u8ErrorState = NOK;
			}
		}
		else if((Copy_pstTimerConfig -> WGM == FAST_PWM) || (Copy_pstTimerConfig -> WGM == PHASE_CORR))
		{
			switch(Copy_u8Mode)
			{
			case OC_DISCONNECTED:	TCCR2 |= (0 << 4);	break;
			case NON_INVERTED_PWM:	TCCR2 |= (2 << 4);	break;
			case INVERTED_PWM:		TCCR2 |= (3 << 4);	break;
			default: Local_u8ErrorState = NOK;
			}
		}

		/*Select the clock*/
		TCCR2 &= PRESCALER_MASK;
		TCCR2 |= Copy_pstTimerConfig -> ClkSelect;
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	/*Return Error State*/
	return Local_u8ErrorState;
}


/**
 * @brief 					Function to enable any of timer interrupts.
 * @param Copy_u8TimerInt	Interrupt source wanted to be enabled.
 * @return					Error State.
 */
uint8 TIMERS_u8IntEnable(TIMERS_Int_Src_t Copy_u8TimerInt)
{
	/*Define Error State*/
	uint8 Local_u8ErrorState = OK;

	/*Switch the interrupt*/
	switch(Copy_u8TimerInt)
	{
	case TIMER0_OVF:	SET_BIT(TIMSK,TIMSK_TOIE0);	break;
	case TIMER0_COMP:	SET_BIT(TIMSK,TIMSK_OCIE0);	break;
	case TIMER1_OVF:	SET_BIT(TIMSK,TIMSK_TOIE1);	break;
	case TIMER1_COMPA:	SET_BIT(TIMSK,TIMSK_OCIE1A);	break;
	case TIMER1_COMPB:	SET_BIT(TIMSK,TIMSK_OCIE1B);	break;
	case TIMER1_CAPT:	SET_BIT(TIMSK,TIMSK_TICIE1);	break;
	case TIMER2_COMP:	SET_BIT(TIMSK,TIMSK_OCIE2); break;
	case TIMER2_OVF:	SET_BIT(TIMSK,TIMSK_TOIE2);	break;
	default:Local_u8ErrorState = NOK;
	}

	/*Return Error State*/
	return Local_u8ErrorState;
}
/**
 * @brief 					Function to disable any of timer interrupts.
 * @param Copy_u8TimerInt	Interrupt source wanted to be disabled.
 * @return					Error State.
 */
uint8 TIMERS_u8IntDisable(TIMERS_Int_Src_t Copy_u8TimerInt)
{
	/*Define Error State*/
	uint8 Local_u8ErrorState = OK;

	/*Switch the interrupt*/
	switch(Copy_u8TimerInt)
	{
	case TIMER0_OVF:	CLR_BIT(TIMSK,TIMSK_TOIE0);	break;
	case TIMER0_COMP:	CLR_BIT(TIMSK,TIMSK_OCIE0);	break;
	case TIMER1_OVF:	CLR_BIT(TIMSK,TIMSK_TOIE1);	break;
	case TIMER1_COMPA:	CLR_BIT(TIMSK,TIMSK_OCIE1A);	break;
	case TIMER1_COMPB:	CLR_BIT(TIMSK,TIMSK_OCIE1B);	break;
	case TIMER1_CAPT:	CLR_BIT(TIMSK,TIMSK_TICIE1);	break;
	case TIMER2_COMP:	CLR_BIT(TIMSK,TIMSK_OCIE2); break;
	case TIMER2_OVF:	CLR_BIT(TIMSK,TIMSK_TOIE2);	break;
	default:Local_u8ErrorState = NOK;
	}

	/*Return Error State*/
	return Local_u8ErrorState;
}

/**
 * @brief				Function to disable a timer peripheral.
 * @param Copy_u8Timer	Timer wanted to be disabled.
 * @return				Error State.
 */
uint8 TIMERS_u8Disable(TIMERS_NUM Copy_u8Timer)
{
	/*Define Variables*/
	uint8 Local_u8ErrorState = OK;

	/*Switch the timer*/
	switch(Copy_u8Timer)
	{
	case TIMER0: TIMERS_u8StateArr[TIMER0] = IDLE;	TCCR0 &= PRESCALER_MASK;	break;
	case TIMER1: TIMERS_u8StateArr[TIMER1] = IDLE;	TCCR1B &= PRESCALER_MASK;	break;
	case TIMER2: TIMERS_u8StateArr[TIMER2] = IDLE;	TCCR2 &= PRESCALER_MASK;	break;
	default:	Local_u8ErrorState = NOK;	break;
	}

	/*Return Error State*/
	return Local_u8ErrorState;
}

/**
 * @brief 						Function to set call back function of interrupts ISRs.
 * @param Copy_u8TimerIntSource	Interrupt source.
 * @param Copy_pvCallBackFunc	Pointer to call back function.
 * @return						Error State.
 */
uint8 TIMERS_u8SetCallBack(TIMERS_Int_Src_t Copy_u8TimerIntSource, void (* Copy_pvCallBackFunc)(void))
{
	/*Define Variables*/
	uint8 Local_u8ErrorState = OK;

	/*Validate the pointer of function*/
	if(Copy_pvCallBackFunc != NULL)
	{
		TIMERS_pvCallBackFuncArr[Copy_u8TimerIntSource] = Copy_pvCallBackFunc;
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	/*Return Error State*/
	return Local_u8ErrorState;
}


/**
 * @brief 				Function to set the output compare value of timer 0 (OCR0).
 * @param Copy_u8Value	Value of output compare.
 */
void TIMER0_voidSetCompValue(uint8 Copy_u8Value)
{
	/*Set Compare Match Value of Timer 0*/
	OCR0 = Copy_u8Value;
}
/**
 * @brief 				Function to set the overflow value (preload) of timer 0 (TCNT0).
 * @param Copy_u8Value	Value of preload.
 */
void TIMER0_voidSetOvfValue(uint8 Copy_u8Value)
{
	/*Set Overflow Value of Timer 0*/
	TCNT0 = Copy_u8Value;
}
/**
 * @brief 	Function to get the timer (TCNT0) value.
 * @return	Timer value.
 */
uint8 TIMER0_u8GetTimerValue(void)
{
	/*Return Timer Value of Timer 0*/
	return TCNT0;
}



/**
 * @brief 				Function to set the output compare value of timer 2 (OCR2).
 * @param Copy_u8Value	Value of output compare.
 */
void TIMER2_voidSetCompValue(uint8 Copy_u8Value)
{
	/*Set Compare Match Value of Timer 2*/
	OCR2 = Copy_u8Value;
}
/**
 * @brief 				Function to set the overflow value (preload) of timer 2 (TCNT2).
 * @param Copy_u8Value	Value of preload.
 */
void TIMER2_voidSetOvfValue(uint8 Copy_u8Value)
{
	/*Set Overflow Value of Timer 2*/
	TCNT2 = Copy_u8Value;
}
/**
 * @brief 	Function to get the timer (TCNT2) value.
 * @return	Timer value.
 */
uint8 TIMER2_u8GetTimerValue(void)
{
	/*Return Timer Value of Timer 2*/
	return TCNT2;
}



/**
 * @brief 				Function to set the output compare value of timer 1 channel A (OCR1A).
 * @param Copy_u16Value	Value of ouput compare channel A.
 */
void TIMER1_voidSetCompValueChA(uint16 Copy_u16Value)
{
	/*Set Compare Match Value of Timer 1 Channel A*/
	OCR1A = Copy_u16Value;
}
/**
 * @brief 				Function to set the output compare value of timer 1 channel B (OCR1B).
 * @param Copy_u16Value	Value of ouput compare channel B.
 */
void TIMER1_voidSetCompValueChB(uint16 Copy_u16Value)
{
	/*Set Compare Match Value of Timer 1 Channel B*/
	OCR1B = Copy_u16Value;
}
/**
 * @brief 				Function to set the overflow value (preload) of timer 1 (TCNT1).
 * @param Copy_u16Value	Value of preload.
 */
void TIMER1_voidSetOvfValue(uint16 Copy_u16Value)
{
	/*Set Overflow Value of Timer 1*/
	TCNT1 = Copy_u16Value;
}
/**
 * @brief 				Function to set a value into input capture register (ICR1).
 * @param Copy_u16Value	Value wanted to set.
 */
void TIMER1_voidSetInputCaptValue(uint16 Copy_u16Value)
{
	/*Set Input Capture Value of Timer 1*/
	ICR1 = Copy_u16Value;
}
/**
 * @brief	Function to get the timer (TCNT1) value.
 * @return	Timer value.
 */
uint16 TIMER1_u16GetTimerValue(void)
{
	/*Return Timer Value of Timer 1*/
	return TCNT1;
}
/**
 * @brief	Function to get the input capture (ICR1) value.
 * @return	Input capture value.
 */
uint16 TIMER1_u16GetInputCaptValue(void)
{
	/*Return Input Capture Register Value*/
	return ICR1;
}
/**
 * @brief					Function to set the input capture trigger source.
 * @param Copy_u8TriggerSrc	Trigger source.
 * @return					Error State.
 */
uint8 TIMER1_u8SetInputCaptTriggerSrc(uint8 Copy_u8TriggerSrc)
{
	/*Define Variables*/
	uint8 Local_u8ErrorState = OK;

	/*Set the trigger source selected*/
	switch(Copy_u8TriggerSrc)
	{
	case TIMER1_u8ICU_RISING_EDGE:	SET_BIT(TCCR1B,TCCR1B_ICES1);	break;
	case TIMER1_u8ICU_FALLING_EDGE: CLR_BIT(TCCR1B,TCCR1B_ICES1);	break;
	default: Local_u8ErrorState = NOK;
	}

	/*Return Error State*/
	return Local_u8ErrorState;
}


/**
 * @brief Function to set the watchdog timer.
 */
void WDT_voidEnable(void)
{
	SET_BIT(WDTCR,WDTCR_WDE);
}
/**
 * @brief Function to reset the watchdog timer.
 */
void WDT_voidDisable(void)
{
	WDTCR |= (1 << WDTCR_WDTOE) | (1 << WDTCR_WDE);
	WDTCR &= 0b11110111;
}
/**
 * @brief 						Function to set the watchdog timer prescaler.
 * @param Copy_u8WatchDogTime	Time that watchdog timer will delay with.
 * @return						Error State.
 */
uint8 WDT_u8SetTime(uint8 Copy_u8WatchDogTime)
{
	/*Define variables*/
	uint8 Local_u8ErrorState = OK;

	if(Copy_u8WatchDogTime < 8u)
	{
		WDTCR &= WDT_PRESCALER_MASK;
		WDTCR |= Copy_u8WatchDogTime;
	}
	else
	{
		Local_u8ErrorState = NOK;
	}

	/*Return Error State*/
	return Local_u8ErrorState;
}




/**
 * @brief Timer/Counter 0 OverFlow Event ISR.
 */
void __vector_11 (void) __attribute((signal));
void __vector_11 (void)
{
	/*Validate the pointer*/
	if(TIMERS_pvCallBackFuncArr[TIMER0_OVF] != NULL)
	{
		/*Calling the ISR function*/
		TIMERS_pvCallBackFuncArr[TIMER0_OVF]();
	}
	else
	{
		/*Do nothing*/
	}
}

/**
 *@brief Timer/Counter 0 Compare Match Event ISR.
 */
void __vector_10 (void) __attribute((signal));
void __vector_10 (void)
{
	/*Validate the pointer*/
	if(TIMERS_pvCallBackFuncArr[TIMER0_COMP] != NULL)
	{
		/*Calling the ISR function*/
		TIMERS_pvCallBackFuncArr[TIMER0_COMP]();
	}
	else
	{
		/*Do nothing*/
	}
}

/**
 * @brief Timer/Counter 1 OverFlow Event ISR.
 */
void __vector_9 (void) __attribute((signal));
void __vector_9 (void)
{
	/*Validate the pointer*/
	if(TIMERS_pvCallBackFuncArr[TIMER1_OVF] != NULL)
	{
		/*Calling the ISR function*/
		TIMERS_pvCallBackFuncArr[TIMER1_OVF]();
	}
	else
	{
		/*Do nothing*/
	}
}

/**
 * @brief Timer/Counter 1 Channel B Compare Match Event ISR.
 */
void __vector_8 (void) __attribute((signal));
void __vector_8 (void)
{
	/*Validate the pointer*/
	if(TIMERS_pvCallBackFuncArr[TIMER1_COMPB] != NULL)
	{
		/*Calling the ISR function*/
		TIMERS_pvCallBackFuncArr[TIMER1_COMPB]();
	}
	else
	{
		/*Do nothing*/
	}
}

/**
 * @brief Timer/Counter 1 Channel A Compare Match Event ISR.
 */
void __vector_7 (void) __attribute((signal));
void __vector_7 (void)
{
	/*Validate the pointer*/
	if(TIMERS_pvCallBackFuncArr[TIMER1_COMPA] != NULL)
	{
		/*Calling the ISR function*/
		TIMERS_pvCallBackFuncArr[TIMER1_COMPA]();
	}
	else
	{
		/*Do nothing*/
	}
}

/**
 * @brief Timer/Counter 1 Input Capture Event ISR.
 */
void __vector_6 (void) __attribute((signal));
void __vector_6 (void)
{
	/*Validate the pointer*/
	if(TIMERS_pvCallBackFuncArr[TIMER1_CAPT] != NULL)
	{
		/*Calling the ISR function*/
		TIMERS_pvCallBackFuncArr[TIMER1_CAPT]();
	}
	else
	{
		/*Do nothing*/
	}
}

/**
 * @brief Timer/Counter 2 OverFlow Event ISR.
 */
void __vector_5 (void) __attribute((signal));
void __vector_5 (void)
{
	/*Validate the pointer*/
	if(TIMERS_pvCallBackFuncArr[TIMER2_OVF] != NULL)
	{
		/*Calling the ISR function*/
		TIMERS_pvCallBackFuncArr[TIMER2_OVF]();
	}
	else
	{
		/*Do nothing*/
	}
}

/**
 * @brief Timer/Counter 2 Compare Match Event ISR.
 */
void __vector_4 (void) __attribute((signal));
void __vector_4 (void)
{
	/*Validate the pointer*/
	if(TIMERS_pvCallBackFuncArr[TIMER2_COMP] != NULL)
	{
		/*Calling the ISR function*/
		TIMERS_pvCallBackFuncArr[TIMER2_COMP]();
	}
	else
	{
		/*Do nothing*/
	}
}
