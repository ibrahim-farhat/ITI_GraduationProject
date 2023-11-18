/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: TIMERS_interface.h	**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file TIMERS_interface.h
 * @author Ibrahim Tarek
 * @brief This file interfaces the TIMERS module functions.
 * @version 1.00
 */

#ifndef TIMERS_INTERFACE_H_
#define TIMERS_INTERFACE_H_

/*Copy_u8WatchDogTime Options*/
#define WDT_16K_CYCLES			0u
#define WDT_32K_CYCLES			1u
#define WDT_64K_CYCLES			2u
#define WDT_128K_CYCLES			3u
#define WDT_256K_CYCLES			4u
#define WDT_512K_CYCLES			5u
#define WDT_1024K_CYCLES		6u
#define WDT_1048K_CYCLES		7u


/**
 * @brief 			Enum that provide the options of waveform generation mode of timers 0 or 2.
 * @arg	NORMAL		For normal WGM.
 * @arg PHASE_CORR	For phase correct PWM WGM.
 * @arg CTC			For CTC WGM.
 * @arg FAST_PWM	For fast PWM WGM.
 */
typedef enum
{
	NORMAL = 0,//!< NORMAL
	PHASE_CORR,//!< PHASE_CORR
	CTC,       //!< CTC
	FAST_PWM   //!< FAST_PWM
}
TIMER0_2_WGM_t;

/**
 * @brief 						Enum that provide the options of waveform generation mode of timer 1.
 * @arg NORMAL_16_BITS			For normal WGM with a top at 0xFFFF.
 * @arg PHASE_CORR_8_BITS		For phase correct PWM WGM with a top at 0x00FF.
 * @arg PHASE_CORR_9_BITS		For phase correct PWM WGM with a top at 0x01FF.
 * @arg PHASE_CORR_10_BITS		For phase correct PWM WGM with a top at 0x03FF.
 * @arg CTC_OCR1A				For CTC WGM with a top at OCR1A register value.
 * @arg FAST_PWM_8_BITS			For fast PWM WGM with a top at 0x00FF.
 * @arg FAST_PWM_9_BITS			For fast PWM WGM with a top at 0x01FF.
 * @arg FAST_PWM_10_BITS		For fast PWM WGM with a top at 0x03FF.
 * @arg PHASE_FREQ_CORR_ICR1	For phase and frequency correct WGM with a top at ICR1 register value.
 * @arg PHASE_FREQ_CORR_OCR1A	For phase and frequency correct WGM with a top at OCR1A register value.
 * @arg PHASE_CORR_ICR1			For phase correct PWM WGM with a top at ICR1 register value.
 * @arg PHASE_CORR_OCR1A		For phase correct PWM WGM with a top at OCR1A register value.
 * @arg	CTC_ICR1				For CTC WGM with a top at ICR1 register value.
 * @arg	FAST_PWM_ICR1			For PWM WGM with a top at ICR1 register value.
 * @arg FAST_PWM_OCR1A			For PWM WGM with a top at OCR1A register value.
 */
typedef enum
{
	NORMAL_16_BITS = 0,   //!< NORMAL_16_BITS
	PHASE_CORR_8_BITS,    //!< PHASE_CORR_8_BITS
	PHASE_CORR_9_BITS,    //!< PHASE_CORR_9_BITS
	PHASE_CORR_10_BITS,   //!< PHASE_CORR_10_BITS
	CTC_OCR1A,            //!< CTC_OCR1A
	FAST_PWM_8_BITS,      //!< FAST_PWM_8_BITS
	FAST_PWM_9_BITS,      //!< FAST_PWM_9_BITS
	FAST_PWM_10_BITS,     //!< FAST_PWM_10_BITS
	PHASE_FREQ_CORR_ICR1, //!< PHASE_FREQ_CORR_ICR1
	PHASE_FREQ_CORR_OCR1A,//!< PHASE_FREQ_CORR_OCR1A
	PHASE_CORR_ICR1,      //!< PHASE_CORR_ICR1
	PHASE_CORR_OCR1A,     //!< PHASE_CORR_OCR1A
	CTC_ICR1,             //!< CTC_ICR1
	RESERVED,             //!< RESERVED
	FAST_PWM_ICR1,        //!< FAST_PWM_ICR1
	FAST_PWM_OCR1A        //!< FAST_PWM_OCR1A
}
TIMER1_WGM_t;


/*
 * CompOutMode Options of fast or phase correct PWM mode:
 *
 * For fast PWM: NON_INVERTED -->> Clear OC0 on compare match, Set OC0 on Top.
 * 				 INVERTED 	  -->> Set OC0 on compare match, Clear OC0 on Top.
 *
 * For phase correct PWM: NON_INVERTED -->> Clear OC0 on compare match when up counting,
 * 											Set OC0 on compare match when down counting.
 * 				 		  INVERTED 	   -->> Set OC0 on compare match when up counting,
 * 											Clear OC0 on compare match when down counting.
 */
/*
 * CompOutMode Options of non PWM mode:	1- TOG_OC	2- CLR_OC	3- SET_OC
 */
/**
 * @brief 					Enum that provides the options of compare match output.
 * @arg OC_DISCONNECTED		To disconnect any of OC1x pins.
 * @arg	TOG_OC				To toggle OC1x pins.
 * @arg	CLR_OC				To clear OC1x pins.
 * @arg	SET_OC				To set OC1x pins.
 * @arg	NON_INVERTED_PWM	For non inverted PWM.
 * @arg INVERTED_PWM		For inverted PWM.
 * @arg	DO_NOT_CHANGE		To not change the current mode.
 */
typedef enum
{
	OC_DISCONNECTED = 0,//!< OC_DISCONNECTED
	TOG_OC,             //!< TOG_OC
	CLR_OC,             //!< CLR_OC
	SET_OC,             //!< SET_OC
	NON_INVERTED_PWM,   //!< NON_INVERTED_PWM
	INVERTED_PWM,       //!< INVERTED_PWM
	DO_NOT_CHANGE       //!< DO_NOT_CHANGE
}
TIMERS_OC_MODE_t;


/**
 * @brief 			Struct to configure timers 0 or 2 options for initialization.
 * @param ClkSelect	Clock prescaler.
 * @param WGM		Waveform generation mode.
 * @param OCMode	Output compare mode for OCx pins.
 */
typedef struct
{
	uint8 ClkSelect;
	TIMER0_2_WGM_t WGM;
	TIMERS_OC_MODE_t OCMode;
}
TIMER0_2_CFG_t;

/**
 * @brief			Struct to configure timer 1 options for initialization.
 * @param ClkSelect	Clock prescaler.
 * @param WGM		Waveform generation mode.
 * @param OCAMode	Output compare mode for OC1A pin.
 * @param OCBMode	Output compare mode for OC1B pin.
 */
typedef struct
{
	uint8 ClkSelect;
	TIMER1_WGM_t WGM;
	TIMERS_OC_MODE_t OCAMode;
	TIMERS_OC_MODE_t OCBMode;
}
TIMER1_CFG_t;


/*ClkSelect Options for each timer*/
#define TIMER0_u8NO_CLK_SRC				0u
#define TIMER0_u8SYS_CLK_BY_1			1u
#define TIMER0_u8SYS_CLK_BY_8			2u
#define TIMER0_u8SYS_CLK_BY_64			3u
#define TIMER0_u8SYS_CLK_BY_256			4u
#define TIMER0_u8SYS_CLK_BY_1024		5u
#define TIMER0_u8EXT_CLK_FALLING		6u
#define TIMER0_u8EXT_CLK_RISING			7u

#define TIMER1_u8NO_CLK_SRC				0u
#define TIMER1_u8SYS_CLK_BY_1			1u
#define TIMER1_u8SYS_CLK_BY_8			2u
#define TIMER1_u8SYS_CLK_BY_64			3u
#define TIMER1_u8SYS_CLK_BY_256			4u
#define TIMER1_u8SYS_CLK_BY_1024		5u
#define TIMER1_u8EXT_CLK_FALLING		6u
#define TIMER1_u8EXT_CLK_RISING			7u

#define TIMER2_u8NO_CLK_SRC				0u
#define TIMER2_u8SYS_CLK_BY_1			1u
#define TIMER2_u8SYS_CLK_BY_8			2u
#define TIMER2_u8SYS_CLK_BY_32			3u
#define TIMER2_u8SYS_CLK_BY_64			4u
#define TIMER2_u8SYS_CLK_BY_128			5u
#define TIMER2_u8SYS_CLK_BY_256			6u
#define TIMER2_u8SYS_CLK_BY_1024		7u


/**
 * @brief 				Enum that provides the options for timers' interrupt sources.
 * @arg	TIMER0_OVF		For timer 0 overflow interrupt.
 * @arg	TIMER0_COMP		For timer 0 compare match interrupt.
 * @arg TIMER1_OVF		For timer 1 overflow interrupt.
 * @arg TIMER1_COMPA	For timer 1 compare match channel A interrupt.
 * @arg TIMER1_COMPB	For timer 1 compare match channel B interrupt.
 * @arg TIMER1_CAPT		For timer 1 input capture unit interrupt.
 * @arg TIMER2_OVF		For timer 2 overflow interrupt.
 * @arg TIMER2_COMP		For timer 2 compare match interrupt.
 */
typedef enum
{
	TIMER0_OVF = 0,//!< TIMER0_OVF
	TIMER0_COMP,   //!< TIMER0_COMP
	TIMER1_OVF,    //!< TIMER1_OVF
	TIMER1_COMPA,  //!< TIMER1_COMPA
	TIMER1_COMPB,  //!< TIMER1_COMPB
	TIMER1_CAPT,   //!< TIMER1_CAPT
	TIMER2_OVF,    //!< TIMER2_OVF
	TIMER2_COMP    //!< TIMER2_COMP
}
TIMERS_Int_Src_t;


/**
 * @brief 		Enum that provides the options of the timer number.
 * @arg TIMER0	For timer 0.
 * @arg TIMER1	For timer 1.
 * @arg TIMER2	For timer 2.
 */
typedef enum
{
	TIMER0,//!< TIMER0
	TIMER1,//!< TIMER1
	TIMER2 //!< TIMER2
}
TIMERS_NUM;


/*Copy_u8TriggerSrc Options*/
#define TIMER1_u8ICU_RISING_EDGE	0u
#define TIMER1_u8ICU_FALLING_EDGE	1u


/**
 * @brief 						Function to initialize timer 0 peripheral.
 * @param Copy_pstTimerConfig	Struct to configure timer 0 options.
 * @return						Error State.
 */
uint8 TIMER0_u8Init(const TIMER0_2_CFG_t *Copy_pstTimerConfig);
/**
 * @brief 						Function to initialize timer 1 peripheral.
 * @param Copy_pstTimerConfig	Struct to configure timer 1 options.
 * @return						Error State.
 */
uint8 TIMER1_u8Init(const TIMER1_CFG_t *Copy_pstTimerConfig);
/**
 * @brief 						Function to initialize timer 2 peripheral.
 * @param Copy_pstTimerConfig	Struct to configure timer 2 otions.
 * @return						Error State.
 */
uint8 TIMER2_u8Init(const TIMER0_2_CFG_t *Copy_pstTimerConfig);

/**
 * @brief 						Function to set the compare output mode of timer 0.
 * @param Copy_pstTimerConfig	Struct of the timer configurations.
 * @param Copy_u8Mode			Compare output mode which needed to be set.
 * @return						Error State.
 */
uint8 TIMER0_u8SetCompOutMode(const TIMER0_2_CFG_t *Copy_pstTimerConfig, TIMERS_OC_MODE_t Copy_u8Mode);
/**
 * @brief 						Function to set the compare output mode of timer 1 channel A.
 * @param Copy_pstTimerConfig	Struct of the timer configurations.
 * @param Copy_u8Mode			Compare output mode which needed to be set.
 * @return						Error State.
 */
uint8 TIMER1_u8SetCompOutModeChA(const TIMER1_CFG_t *Copy_pstTimerConfig, TIMERS_OC_MODE_t Copy_u8Mode);
/**
 * @brief 						Function to set the compare output mode of timer 1 channel B.
 * @param Copy_pstTimerConfig	Struct of the timer configurations.
 * @param Copy_u8Mode			Compare output mode which needed to be set.
 * @return						Error State.
 */
uint8 TIMER1_u8SetCompOutModeChB(const TIMER1_CFG_t *Copy_pstTimerConfig, TIMERS_OC_MODE_t Copy_u8Mode);
/**
 * @brief 						Function to set the compare output mode of timer 2.
 * @param Copy_pstTimerConfig	Struct of the timer configurations.
 * @param Copy_u8Mode			Compare output mode which needed to be set.
 * @return						Error State.
 */
uint8 TIMER2_u8SetCompOutMode(const TIMER0_2_CFG_t *Copy_pstTimerConfig, TIMERS_OC_MODE_t Copy_u8Mode);

/**
 * @brief 					Function to enable any of timer interrupts.
 * @param Copy_u8TimerInt	Interrupt source wanted to be enabled.
 * @return					Error State.
 */
uint8 TIMERS_u8IntEnable(TIMERS_Int_Src_t Copy_u8TimerInt);
/**
 * @brief 					Function to disable any of timer interrupts.
 * @param Copy_u8TimerInt	Interrupt source wanted to be disabled.
 * @return					Error State.
 */
uint8 TIMERS_u8IntDisable(TIMERS_Int_Src_t Copy_u8TimerInt);

/**
 * @brief				Function to disable a timer peripheral.
 * @param Copy_u8Timer	Timer wanted to be disabled.
 * @return				Error State.
 */
uint8 TIMERS_u8Disable(TIMERS_NUM Copy_u8Timer);

/**
 * @brief 						Function to set call back function of interrupts ISRs.
 * @param Copy_u8TimerIntSource	Interrupt source.
 * @param Copy_pvCallBackFunc	Pointer to call back function.
 * @return						Error State.
 */
uint8 TIMERS_u8SetCallBack(TIMERS_Int_Src_t Copy_u8TimerIntSource, void (* Copy_pvCallBackFunc)(void));

/**
 * @brief 				Function to set the output compare value of timer 0 (OCR0).
 * @param Copy_u8Value	Value of output compare.
 */
void TIMER0_voidSetCompValue(uint8 Copy_u8Value);
/**
 * @brief 				Function to set the overflow value (preload) of timer 0 (TCNT0).
 * @param Copy_u8Value	Value of preload.
 */
void TIMER0_voidSetOvfValue(uint8 Copy_u8Value);
/**
 * @brief 	Function to get the timer (TCNT0) value.
 * @return	Timer value.
 */
uint8 TIMER0_u8GetTimerValue(void);

/**
 * @brief 				Function to set the output compare value of timer 2 (OCR2).
 * @param Copy_u8Value	Value of output compare.
 */
void TIMER2_voidSetCompValue(uint8 Copy_u8Value);
/**
 * @brief 				Function to set the overflow value (preload) of timer 2 (TCNT2).
 * @param Copy_u8Value	Value of preload.
 */
void TIMER2_voidSetOvfValue(uint8 Copy_u8Value);
/**
 * @brief 	Function to get the timer (TCNT2) value.
 * @return	Timer value.
 */
uint8 TIMER2_u8GetTimerValue(void);

/**
 * @brief 				Function to set the output compare value of timer 1 channel A (OCR1A).
 * @param Copy_u16Value	Value of ouput compare channel A.
 */
void TIMER1_voidSetCompValueChA(uint16 Copy_u16Value);
/**
 * @brief 				Function to set the output compare value of timer 1 channel B (OCR1B).
 * @param Copy_u16Value	Value of ouput compare channel B.
 */
void TIMER1_voidSetCompValueChB(uint16 Copy_u16Value);
/**
 * @brief 				Function to set the overflow value (preload) of timer 1 (TCNT1).
 * @param Copy_u16Value	Value of preload.
 */
void TIMER1_voidSetOvfValue(uint16 Copy_u16Value);
/**
 * @brief 				Function to set a value into input capture register (ICR1).
 * @param Copy_u16Value	Value wanted to set.
 */
void TIMER1_voidSetInputCaptValue(uint16 Copy_u16Value);
/**
 * @brief	Function to get the timer (TCNT1) value.
 * @return	Timer value.
 */
uint16 TIMER1_u16GetTimerValue(void);
/**
 * @brief	Function to get the input capture (ICR1) value.
 * @return	Input capture value.
 */
uint16 TIMER1_u16GetInputCaptValue(void);
/**
 * @brief					Function to set the input capture trigger source.
 * @param Copy_u8TriggerSrc	Trigger source.
 * @return					Error State.
 */
uint8 TIMER1_u8SetInputCaptTriggerSrc(uint8 Copy_u8TriggerSrc);

/**
 * @brief Function to set the watchdog timer.
 */
void WDT_voidEnable(void);
/**
 * @brief Function to reset the watchdog timer.
 */
void WDT_voidDisable(void);
/**
 * @brief 						Function to set the watchdog timer prescaler.
 * @param Copy_u8WatchDogTime	Time that watchdog timer will delay with.
 * @return						Error State.
 */
uint8 WDT_u8SetTime(uint8 Copy_u8WatchDogTime);

#endif
