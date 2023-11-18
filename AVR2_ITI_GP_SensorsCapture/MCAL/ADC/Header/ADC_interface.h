/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: ADC_interface.h		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file ADC_interface.h
 * @author Ibrahim Tarek
 * @brief This file interfaces the ADC module functions.
 * @version 1.00
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

/**
 * @brief Struct type for chain conversion asynchronous.
 *
 * @param ChainArr Pointer to array of channels.
 * @param ResultArr Pointer to array of uint16 to return results to the main.
 * @param NotificationFunc Pointer to function which take place after ADC terminate its work.
 * @param ChainSize Number of channels in the chain.
 */
typedef struct
{
	uint8 *ChainArr;
	uint16 *ResultArr;
	void(*NotificationFunc)(void);
	uint8 ChainSize;
}ADC_ChainConv_t;

/*Copy_u8Channel Options*/
#define ADC_u8SINGLE_ENDED_CH0		0u
#define ADC_u8SINGLE_ENDED_CH1		1u
#define ADC_u8SINGLE_ENDED_CH2		2u
#define ADC_u8SINGLE_ENDED_CH3		3u
#define ADC_u8SINGLE_ENDED_CH4		4u
#define ADC_u8SINGLE_ENDED_CH5		5u
#define ADC_u8SINGLE_ENDED_CH6		6u
#define ADC_u8SINGLE_ENDED_CH7		7u
#define ADC_u8DIFF_CH0_CH0_10x		8u
#define ADC_u8DIFF_CH1_CH0_10x		9u
#define ADC_u8DIFF_CH0_CH0_200x		10u
#define ADC_u8DIFF_CH1_CH0_200x		11u
#define ADC_u8DIFF_CH2_CH2_10x		12u
#define ADC_u8DIFF_CH3_CH2_10x		13u
#define ADC_u8DIFF_CH2_CH2_200x		14u
#define ADC_u8DIFF_CH3_CH2_200x		15u
#define ADC_u8DIFF_CH0_CH1_1x		16u
#define ADC_u8DIFF_CH1_CH1_1x		17u
#define ADC_u8DIFF_CH2_CH1_1x		18u
#define ADC_u8DIFF_CH3_CH1_1x		19u
#define ADC_u8DIFF_CH4_CH1_1x		20u
#define ADC_u8DIFF_CH5_CH1_1x		21u
#define ADC_u8DIFF_CH6_CH1_1x		22u
#define ADC_u8DIFF_CH7_CH1_1x		23u
#define ADC_u8DIFF_CH0_CH2_1x		24u
#define ADC_u8DIFF_CH1_CH2_1x		25u
#define ADC_u8DIFF_CH2_CH2_1x		26u
#define ADC_u8DIFF_CH3_CH2_1x		27u
#define ADC_u8DIFF_CH4_CH2_1x		28u
#define ADC_u8DIFF_CH5_CH2_1x		29u
#define ADC_u8SINGLE_ENDED_1220mV	30u
#define ADC_u8SINGLE_ENDED_0mV		31u

/**
 * @brief Function to initialize ADC with prebuild configuration.
 */
void ADC_voidInit(void);

/**
 * @brief Function to get the reading of an ADC channel.
 * @param Copy_u8Channel The number of channel you want to read.
 * @param Copy_pu16Result This pointer return the reading of the channel selected.
 * @return Error State of the function.
 */
uint8 ADC_u8StartConversionSynch(uint8 Copy_u8Channel, uint16 *Copy_pu16Result);


/**
 * @brief Function to get the reading of an ADC channel.
 * @note You should enable GIE before using this function.
 * @param Copy_u8Channel The number of channel you want to read.
 * @param Copy_pu16Result This pointer return the reading of the channel selected.
 * @param Copy_pvNotificationFunc This pointer set call back the notification function from the application layer.
 * @return Error State of the function.
 */
uint8 ADC_u8StartConversionAsynch(uint8 Copy_u8Channel, uint16 *Copy_pu16Result, void (* Copy_pvNotificationFunc)(void));

/**
 * @brief Function to get the reading of a series of channels.
 * @param Copy_pstChain Pointer to struct which carry the chain data.
 * @return Error State of the function.
 */
uint8 ADC_u8StartChainConversionAsynch(ADC_ChainConv_t *Copy_pstChain);

#endif
