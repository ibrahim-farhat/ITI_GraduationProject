#include <stdint.h>

#include "../Inc/Defines.h"

#include "../Inc/queue.h"
#include "../Inc/FIR_interface.h"

//#include "../../../HAL/CLCD/Header/CLCD_interface.h"
//#include <util/delay.h>

#define PI 3.14159265359

void FIR_voidFilterInit(FIR_Filter_t *Copy_pstFilter)
{
	/*Define a counter*/
	uint8_t Local_u8Counter;

	Queue_voidCircularArrayQueueInit(&(Copy_pstFilter -> Front), &(Copy_pstFilter -> Rear));

	/*Clear filter buffer*/
	for(Local_u8Counter = 0; Local_u8Counter < FIR_FILTER_LENGTH; Local_u8Counter++)
	{
		Queue_voidCircularArrayQueueEnqueue(&(Copy_pstFilter -> Front), &(Copy_pstFilter -> Rear), FIR_FILTER_LENGTH, Copy_pstFilter -> QueueBuffer, 0);
	}
}

float FIR_f32FilterUpdate(FIR_Filter_t *Copy_pstFilter, float Copy_f32Input)
{
	/*Define a temporary variable to carry the output*/
	float Local_f32OutputSample;
	/*Define a counter variable*/
	uint8_t Local_u8Counter;
	/*Define an indicator to handle the buffer*/
	uint8_t Local_u8Indicator;

	/*Enqueue the latest sample in the buffer queue*/
	Queue_voidCircularArrayQueueDequeueEnqueue(&(Copy_pstFilter -> Front), &(Copy_pstFilter -> Rear), FIR_FILTER_LENGTH, Copy_pstFilter -> QueueBuffer, Copy_f32Input);

	/*Initialize the indicator to handle the buffer*/
	Local_u8Indicator = Copy_pstFilter -> Rear;

	/*Compute the output sample (via convolution)*/
	for(Local_u8Counter = 0; Local_u8Counter < FIR_FILTER_LENGTH; Local_u8Counter++)
	{
		/*Multiply impulse response with shifted input samples and add to output*/
		Local_f32OutputSample += Copy_pstFilter -> ImpulseRespone[Local_u8Counter] * Copy_pstFilter -> QueueBuffer[Local_u8Indicator];

		/*Move to the previous reading*/
		if(Local_u8Indicator > 0)
		{
			Local_u8Indicator--;
		}
		else
		{
			Local_u8Indicator = FIR_FILTER_LENGTH - 1;
		}

	}

	/*Put the output into the filter struct*/
	Copy_pstFilter -> Output = Local_f32OutputSample;

	/*Return the filter output*/
	return Local_f32OutputSample;
}

uint32_t FIR_u32EMA(uint32_t Copy_u32NewValue, uint32_t Copy_u32OldValue, uint8_t Copy_u8Alpha)
{
	uint32_t Local_u32Result = ((uint32_t) Copy_u8Alpha * Copy_u32NewValue) / 10UL + ((10UL - (uint32_t) Copy_u8Alpha) * Copy_u32OldValue) / 10UL;
	return Local_u32Result;
}

float ApproxSin(float Copy_f32Value)
{
	/*Define required variables*/
	uint8_t Local_u8Counter;
    float Local_f32Result = 0;
    int Local_s32Sign = 1;

    /*Normalize angle to be between -2*pi and 2*pi*/
    while (Copy_f32Value < -2 * PI)
    {
    	Copy_f32Value += 2 * PI;
    }
    while (Copy_f32Value >= 2 * PI)
    {
    	Copy_f32Value -= 2 * PI;
    }

    float Local_f32Term = Copy_f32Value;

    for(Local_u8Counter = 1; Local_u8Counter <= 10; Local_u8Counter += 2)
    {
    	Local_f32Result += Local_s32Sign * Local_f32Term;
    	Local_f32Term *= (Copy_f32Value * Copy_f32Value) / ((Local_u8Counter + 1) * (Local_u8Counter + 2));
        Local_s32Sign *= -1;
    }

    return Local_f32Result;
}

Error_t FIR_enComputeImpulseResponse(float *Local_f32H, int Copy_s32CoefficientsNum, float Copy_f32CutoffFrequency, float Copy_f32samplingRate)
{
	/*Define a counter*/
	uint8_t Local_u8Counter;
	Error_t Local_enErrorState = OK;

	/*Validate the pointer*/
	if(Local_f32H != NULL)
	{
		for(Local_u8Counter = 0; Local_u8Counter < Copy_s32CoefficientsNum; Local_u8Counter++)
		{
			if (Local_u8Counter == (Copy_s32CoefficientsNum - 1) / 2)
			{
				Local_f32H[Local_u8Counter] = 2 * Copy_f32CutoffFrequency / Copy_f32samplingRate;
			}
			else
			{
				Local_f32H[Local_u8Counter] = (ApproxSin(2 * PI * Copy_f32CutoffFrequency * (Local_u8Counter - (Copy_s32CoefficientsNum - 1) / 2) / Copy_f32samplingRate) /
					   (PI * (Local_u8Counter - (Copy_s32CoefficientsNum - 1) / 2)));
			}
		}
	}
	else
	{
		Local_enErrorState = NULL_PTR_ERROR;
	}

	return Local_enErrorState;
}

//void computeImpulseResponse(float* h, int numCoefficients, float cutoffFrequency, float samplingRate) {
//    for (int n = 0; n < numCoefficients; n++) {
//        if (n == (numCoefficients-1)/2) {
//            h[n] = 2 * cutoffFrequency / samplingRate;
//        } else {
//            h[n] = sin(2 * M_PI * cutoffFrequency * (n - (numCoefficients-1)/2) / samplingRate) /
//                   (M_PI * (n - (numCoefficients-1)/2));
//        }
//    }
//}
//
