#ifndef STM32F401CC_H_
#define STM32F401CC_H_

/*******************************  Various Memories Base Addresses  *****************************/
#define FLASH_BASE_ADDRESS      0x08000000UL
#define SRAM_BASE_ADDRESS       0x20000000UL
#define ROM_BASE_ADDRESS        0x1FFF0000UL


/*******************************  Core Peripherals' Base Addresses  *****************************/
#define SYSTICK_BASE_ADDRESS    0xE000E010UL
#define NVIC_BASE_ADDRESS      	0xE000E100UL


/*******************************  AHB1 Peripherals' Base Addresses  *****************************/
#define GPIOA_BASE_ADDRESS      0x40020000UL
#define GPIOB_BASE_ADDRESS      0x40020400UL
#define GPIOC_BASE_ADDRESS      0x40020800UL
#define GPIOD_BASE_ADDRESS      0x40020C00UL
#define GPIOE_BASE_ADDRESS      0x40021000UL
#define GPIOF_BASE_ADDRESS      0x40021400UL
#define GPIOG_BASE_ADDRESS      0x40021800UL
#define GPIOH_BASE_ADDRESS      0x40021C00UL

#define RCC_BASE_ADDRESS        0x40023800UL

#define FDI_BASE_ADDRESS        0x40023C00UL

#define DMA1_BASE_ADDRESS		0x40026000UL
#define DMA2_BASE_ADDRESS		0x40026400UL

/*******************************  AHB2 Peripherals' Base Addresses  *****************************/
/*******************************  AHB3 Peripherals' Base Addresses  *****************************/
/*******************************  APB1 Peripherals' Base Addresses  *****************************/
#define USART2_BASE_ADDRESS		0x40004400UL


/*******************************  APB2 Peripheral Base Addresses  *****************************/
#define USART1_BASE_ADDRESS		0x40011000UL
#define USART6_BASE_ADDRESS		0x40011400UL

#define SPI1_BASE_ADDRESS		0x40013000UL
#define SPI2_BASE_ADDRESS		0x40013800UL
#define SPI3_BASE_ADDRESS		0x40013C00UL
#define SPI4_BASE_ADDRESS		0x40013400UL

#define EXTI_BASE_ADDRESS		0x40013C00UL
#define SYSCFG_BASE_ADDRESS		0x40013800UL

/*******************************  GPIO Register Definition Structure  *****************************/
typedef struct
{
    volatile uint32_t MODER;            /* GPIO Port Mode Register*/
    volatile uint32_t OTYPER;           /* GPIO Port Output Type Register*/
    volatile uint32_t OSPEEDER;         /* GPIO Port Output Speed Register*/
    volatile uint32_t PUPDR;            /* GPIO Port Pull Up/Down Register*/
    volatile uint32_t IDR;              /* GPIO Port Input Data Register*/
    volatile uint32_t ODR;              /* GPIO Port Output Data Register*/
    volatile uint32_t BSRR;             /* GPIO Port Bit Set/Reset Register*/
    volatile uint32_t LCKR;             /* GPIO Port Lock Register*/
    volatile uint32_t AFR[2];           /* GPIO Port Alternate Function Register*/   
}GPIO_RegDef_t;

/*******************************  RCC Register Definition Structure   *****************************/
typedef struct
{
	struct
	{
		uint32_t HSION 		:1;
		uint32_t HSIRDY		:1;
		uint32_t Reserved0 	:1;
		uint32_t HSITRIM 	:5;
		uint32_t HSICAL		:8;
		uint32_t HSEON		:1;
		uint32_t HSERDY		:1;
		uint32_t HSEBYP		:1;
		uint32_t CSSON		:1;
		uint32_t Reserved1	:4;
		uint32_t PLLON		:1;
		uint32_t PLLRDY		:1;
		uint32_t PLL2SON	:1;
		uint32_t PLL2SRDY	:1;
		uint32_t Reserved	:4;
	}CR;
	uint32_t PLLCFGR;
	struct
	{
		uint32_t SW 		:2;
		uint32_t SWS		:2;
		uint32_t HPRE		:4;
		uint32_t Reserved0 	:2;
		uint32_t PPRE1		:3;
		uint32_t PPRE2		:3;
		uint32_t RTCPRE		:5;
		uint32_t MCO1		:2;
		uint32_t I2SSCR		:1;
		uint32_t MCO1PRE	:3;
		uint32_t MCO2PRE	:3;
		uint32_t MCO2		:2;
	}CFGR;
	uint32_t CIR;
	uint32_t AHB1RSTR;
	uint32_t AHB2RSTR;
	uint32_t RESERVED1;
	uint32_t RESERVED2;
	uint32_t APB1RSTR;
	uint32_t APB2RSTR;
	uint32_t RESERVED3;
	uint32_t RESERVED4;
	uint32_t AHB1ENR;
	uint32_t AHB2ENR;
	uint32_t RESERVED5;
	uint32_t RESERVED6;
	uint32_t APB1ENR;
	uint32_t APB2ENR;
	uint32_t RESERVED7;
	uint32_t RESERVED8;
	uint32_t AHB1LPENR;
	uint32_t AHB2LPENR;
	uint32_t RESERVED9;
	uint32_t RESERVED10;
	uint32_t APB1LPENR;
	uint32_t APB2LPENR;
	uint32_t RESERVED11;
	uint32_t RESERVED12;
	uint32_t BDCR;
	uint32_t CSR;
	uint32_t RESERVED13;
	uint32_t RESERVED14;
	uint32_t SSCGR;
	uint32_t PLLI2SCFGR;
	uint32_t RESERVED15;
	uint32_t DCKCFGR;
}RCC_RegDef_t;

/*******************************  USART Register Definition Structure  *****************************/
typedef struct
{
	uint32_t SR;
	uint32_t DR;

	struct
	{
		uint32_t DIV_Fraction	:4;
		uint32_t DIV_Mantissa	:12;
		uint32_t RESERVED0		:16;
	}BRR;

	struct
	{
		uint32_t SBK		:1;
		uint32_t RWU		:1;
		uint32_t RE			:1;
		uint32_t TE			:1;
		uint32_t IDLEIE		:1;
		uint32_t RXNEIE		:1;
		uint32_t TCIE		:1;
		uint32_t TXEIF		:1;
		uint32_t PEIE		:1;
		uint32_t PS			:1;
		uint32_t PCE		:1;
		uint32_t WAKE		:1;
		uint32_t M			:1;
		uint32_t UE			:1;
		uint32_t RESERVED0	:1;
		uint32_t OVER8		:1;
		uint32_t RESERVED1	:16;
	}CR1;

	struct
	{
		uint32_t ADD		:4;
		uint32_t RESERVED0	:1;
		uint32_t LBDL		:1;
		uint32_t LBDIE		:1;
		uint32_t RESERVED1	:1;
		uint32_t LBCL		:1;
		uint32_t CPHA		:1;
		uint32_t CPOL		:1;
		uint32_t CLKEN		:1;
		uint32_t STOP		:2;
		uint32_t LINEN		:1;
		uint32_t RESERVED2	:17;
	}CR2;

	struct
	{
		uint32_t EIE		:1;
		uint32_t IREN		:1;
		uint32_t IRLP		:1;
		uint32_t HDSEL		:1;
		uint32_t NACK		:1;
		uint32_t SCEN		:1;
		uint32_t DMAR		:1;
		uint32_t DMAT		:1;
		uint32_t RTSE		:1;
		uint32_t CTSE		:1;
		uint32_t CTSIE		:1;
		uint32_t ONEBIT		:1;
		uint32_t RESERVED0 	:20;
	}CR3;

	uint32_t GTPR;
}USART_RegDef_t;

/*******************************  SYSTICK Register Definition Structure  *****************************/
typedef struct
{
	struct
	{
		volatile uint32_t Enable: 1;
		volatile uint32_t TICKINT: 1;
		volatile uint32_t CLKSOURCE: 1;
		volatile uint32_t Reserved0: 13;
		volatile uint32_t COUNTFLAG: 1;
		volatile uint32_t Reserved1: 15;
	}CTRL;

	volatile uint32_t LOAD;
	volatile uint32_t VALUE;
	volatile uint32_t CALIB;
}SYSTICK_RegDef_t;

/*******************************  NVIC Register Definition Structure  *****************************/
typedef struct
{
	uint32_t ISER[8];
	uint32_t RESERVERD0[24];
	uint32_t ICER[8];
	uint32_t RESERVERD1[24];
	uint32_t ISPR[8];
	uint32_t RESERVERD2[24];
	uint32_t ICPR[8];
	uint32_t RESERVERD3[24];
	uint32_t IABR[8];
	uint32_t RESERVERD4[56];
	uint8_t IPR[240];
	uint32_t RESERVERD5[580];
	uint32_t STIR;
}NVIC_RegDef_t;

/*******************************  FDI Register Definition Structure  *****************************/
typedef struct
{
	volatile uint32_t ACR;
	volatile uint32_t KEYR;
	volatile uint32_t OPTKEYR;
	volatile uint32_t SR;
	volatile uint32_t CR;
	volatile uint32_t OPTCR;
}FDI_RegDef_t;

/*******************************  DMA Register Definition Structure  *****************************/
typedef struct
{
	volatile uint32_t LISR;
	volatile uint32_t HISR;
	volatile uint32_t LIFCR;
	volatile uint32_t HIFCR;

	struct
	{
		volatile uint32_t SxCR;
		volatile uint32_t SxNDTR;
		volatile uint32_t SxPAR;
		volatile uint32_t SxM0AR;
		volatile uint32_t SxM1AR;
		volatile uint32_t SxFCR;
	}Stream[8];
}DMA_RegDef_t;

/*******************************  SPI Register Definition Structure  *****************************/
typedef struct
{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t CRCPR;
	volatile uint32_t RXCRCR;
	volatile uint32_t TXCRCR;
}SPI_RegDef_t;

/*******************************  EXTI Register Definition Structure  *****************************/
typedef struct
{
	uint32_t IMR;
	uint32_t EMR;
	uint32_t RTSR;
	uint32_t FTSR;
	uint32_t SWIER;
	uint32_t PR;

}EXTI_RegDef_t;

/*******************************  SYSCFG Register Definition Structure  *****************************/
typedef struct
{
	uint32_t MEMRMP;
	uint32_t PMC;
	uint32_t EXTICR[4];
	uint32_t RESERVED0[2];
	uint32_t CMPCR;
}SYSCFG_RegDef_t;

/*******************************  GPIO Peripheral Definitions  *****************************/
#define GPIOA           ((GPIO_RegDef_t *) GPIOA_BASE_ADDRESS)             	/*GPIO A Peripheral Structure Pointer*/
#define GPIOB           ((GPIO_RegDef_t *) GPIOB_BASE_ADDRESS)             	/*GPIO B Peripheral Structure Pointer*/
#define GPIOC           ((GPIO_RegDef_t *) GPIOC_BASE_ADDRESS)             	/*GPIO C Peripheral Structure Pointer*/
#define GPIOD           ((GPIO_RegDef_t *) GPIOD_BASE_ADDRESS)             	/*GPIO D Peripheral Structure Pointer*/
#define GPIOE           ((GPIO_RegDef_t *) GPIOE_BASE_ADDRESS)             	/*GPIO E Peripheral Structure Pointer*/
#define GPIOF           ((GPIO_RegDef_t *) GPIOF_BASE_ADDRESS)             	/*GPIO F Peripheral Structure Pointer*/
#define GPIOG           ((GPIO_RegDef_t *) GPIOG_BASE_ADDRESS)             	/*GPIO G Peripheral Structure Pointer*/
#define GPIOH           ((GPIO_RegDef_t *) GPIOH_BASE_ADDRESS)             	/*GPIO H Peripheral Structure Pointer*/

/*******************************  RCC Peripheral Definitions   *****************************/
#define RCC           	((RCC_RegDef_t *) RCC_BASE_ADDRESS)             	/*RCC Peripheral Structure Pointer*/

/*******************************  USART Peripheral Definitions   *****************************/
#define USART1          ((USART_RegDef_t *) USART1_BASE_ADDRESS)          	/*USART 1 Peripheral Structure Pointer*/
#define USART2          ((USART_RegDef_t *) USART2_BASE_ADDRESS)          	/*USART 2 Peripheral Structure Pointer*/
#define USART6          ((USART_RegDef_t *) USART6_BASE_ADDRESS)          	/*USART 6 Peripheral Structure Pointer*/

/*******************************  SYSTICK Peripheral Definitions   *****************************/
#define SYSTICK      	((SYSTICK_RegDef_t *) SYSTICK_BASE_ADDRESS)         /*SYSTICK Peripheral Structure Pointer*/

/*******************************  NVIC Peripheral Definitions   *****************************/
#define NVIC           	((NVIC_RegDef_t *) NVIC_BASE_ADDRESS)             	/*NVIC Peripheral Structure Pointer*/

/*******************************  FDI Peripheral Definitions   *****************************/
#define FDI				((FDI_RegDef_t *) FDI_BASE_ADDRESS)             	/*FDI Peripheral Structure Pointer*/

/*******************************  DMA Peripheral Definitions   *****************************/
#define DMA1			((DMA_RegDef_t *) DMA1_BASE_ADDRESS)             	/*DMA 1 Peripheral Structure Pointer*/
#define DMA2			((DMA_RegDef_t *) DMA2_BASE_ADDRESS)             	/*DMA 2 Peripheral Structure Pointer*/

/*******************************  SPI Peripheral Definitions   *****************************/
#define SPI1			((SPI_RegDef_t *) SPI1_BASE_ADDRESS)             	/*SPI 1 Peripheral Structure Pointer*/
#define SPI2			((SPI_RegDef_t *) SPI2_BASE_ADDRESS)             	/*SPI 2 Peripheral Structure Pointer*/
#define SPI3			((SPI_RegDef_t *) SPI3_BASE_ADDRESS)             	/*SPI 3 Peripheral Structure Pointer*/
#define SPI4			((SPI_RegDef_t *) SPI4_BASE_ADDRESS)             	/*SPI 4 Peripheral Structure Pointer*/

/*******************************  EXTI Peripheral Definitions   *****************************/
#define EXTI			((EXTI_RegDef_t *) EXTI_BASE_ADDRESS)             	/*EXTI Peripheral Structure Pointer*/

/*******************************  SYSCFG Peripheral Definitions   *****************************/
#define SYSCFG			((SYSCFG_RegDef_t *) SYSCFG_BASE_ADDRESS)             	/*SYSCFG Peripheral Structure Pointer*/

#endif
