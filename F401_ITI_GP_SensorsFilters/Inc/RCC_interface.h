#ifndef RCC_INTERFACE_H_
#define RCC_INTERFACE_H_

typedef enum
{
	HSI = 0,
	HSE,
	PLL
}RCC_Clk_t;

typedef enum
{
	GPIOA_EN = 0,
	GPIOB_EN,
	GPIOC_EN,
	GPIOD_EN,
	GPIOE_EN,
	GPIOH_EN = 7,
	CRC_EN = 12,
	FLITF_EN = 15,
	SRAM1_EN,
	DMA1_EN = 21,
	DMA2_EN
}RCC_AHB1_Peripheral_t;

/*Buses*/
#define RCC_APB1				0
#define RCC_APB2				1
#define RCC_AHB1				2
#define RCC_AHB2				3

typedef enum
{
	OTGFS_EN = 7
}RCC_AHB2_Peripheral_t;

typedef enum
{
	TIM2_EN = 0,
	TIM3_EN,
	TIM4_EN,
	TIM5_EN,
	WWDG_EN = 11,
	SPI2_EN = 14,
	SPI3_EN,
	USART2_EN = 17,
	I2C1_EN = 21,
	I2C2_EN,
	I2C3_EN,
	PWR_EN = 28
}RCC_APB1_Peripheral_t;

typedef enum
{
	TIM1_EN = 0,
	USART1_EN = 4,
	USART6_EN,
	ADC1_EN = 8,
	SDIO_EN = 11,
	SPI1_EN,
	SPI4_EN,
	SYSCFG_EN,
	TIM9_EN = 16,
	TIM10_EN,
	TIM11_EN
}RCC_APB2_Peripheral_t;

typedef enum
{
	HSE_DIV_BY_2 = 0,
	HSE_DIV_BY_1
}RCC_HSE_Prescaler_t;

Error_t RCC_enSetClkStatus(RCC_Clk_t Copy_enClockSource, Defines_Status_t Copy_enStatus);
Error_t RCC_enSetSystemClk(RCC_Clk_t Copy_enClockSource);

Error_t RCC_enHSE_Config();
Error_t RCC_enPLL_Config();

Error_t RCC_enAHB1_EnableClk(RCC_AHB1_Peripheral_t Copy_enPeripheral);
Error_t RCC_enAHB1_DisableClk(RCC_AHB1_Peripheral_t Copy_enPeripheral);

Error_t RCC_enAHB2_EnableClk(RCC_AHB2_Peripheral_t Copy_enPeripheral);
Error_t RCC_enAHB2_DisableClk(RCC_AHB2_Peripheral_t Copy_enPeripheral);

Error_t RCC_enAPB1_EnableClk(RCC_APB1_Peripheral_t Copy_enPeripheral);
Error_t RCC_enAPB1_DisableClk(RCC_APB1_Peripheral_t Copy_enPeripheral);

Error_t RCC_enAPB2_EnableClk(RCC_APB2_Peripheral_t Copy_enPeripheral);
Error_t RCC_enAPB2_DisableClk(RCC_APB2_Peripheral_t Copy_enPeripheral);

#endif




