#ifndef FIR_INTERFACE_H_
#define FIR_INTERFACE_H_

#define FIR_FILTER_LENGTH	16u

typedef struct
{
	float QueueBuffer[FIR_FILTER_LENGTH];
	float ImpulseRespone[FIR_FILTER_LENGTH];
	int Front;
	int Rear;
	float Output;
}FIR_Filter_t;

void FIR_voidFilterInit(FIR_Filter_t *Copy_pstFilter);

float FIR_f32FilterUpdate(FIR_Filter_t *Copy_pstFilter, float Copy_f32Input);

uint32_t FIR_u32EMA(uint32_t Copy_u32NewValue, uint32_t Copy_u32OldValue, uint8_t Copy_u8Alpha);

uint8_t FIR_u8ComputeImpulseResponse(float *Local_f32H, int Copy_s32CoefficientsNum, float Copy_f32CutoffFrequency, float Copy_f32samplingRate);

#endif
