#ifndef FIR_INTERFACE_H_
#define FIR_INTERFACE_H_

#define FIR_FILTER_LENGTH	16u

typedef struct
{
	f32 QueueBuffer[FIR_FILTER_LENGTH];
	f32 ImpulseRespone[FIR_FILTER_LENGTH];
	sint32 Front;
	sint32 Rear;
	f32 Output;
}FIR_Filter_t;

void FIR_voidFilterInit(FIR_Filter_t *Copy_pstFilter);

f32 FIR_f32FilterUpdate(FIR_Filter_t *Copy_pstFilter, f32 Copy_f32Input);

uint32 FIR_u32EMA(uint32 Copy_u32NewValue, uint32 Copy_u32OldValue, uint8 Copy_u8Alpha);
uint8 FIR_u8ComputeImpulseResponse(f32 *Local_f32H, sint32 Copy_s32CoefficientsNum, f32 Copy_f32CutoffFrequency, f32 Copy_f32samplingRate);
#endif
