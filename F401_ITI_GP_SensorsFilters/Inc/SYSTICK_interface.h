#ifndef SYSTICK_INTERFACE_H_
#define SYSTICK_INTERFACE_H_

typedef enum
{
	SYSTICK_AHB_BY_8 = 0,
	SYSTICK_AHB
}SYSTICK_ClkSrc_t;

typedef struct
{
	SYSTICK_ClkSrc_t Prescaler;
	Defines_Status_t Exception_Request;
	uint8_t ClkFreq;
}SYSTICK_Config_t;

Error_t SYSTICK_enInit(const SYSTICK_Config_t *Copy_stConfig);
void SYSTICK_voidDelayUS(uint32_t Copy_u32MicroSeconds);
void SYSTICK_voidDelayMS(uint32_t Copy_u32MilliSeconds);
void SYSTICK_voidSetReloadValue(uint32_t Copy_u32Value);
uint32_t SYSTICK_u32GetElapsedValue(void);
void SYSTICK_voidEnable(void);
void SYSTICK_voidDisable(void);
Error_t SYSTICK_voidSetCallBackFunction(void (*Copy_pvCallBackFunction)(void));

#endif
