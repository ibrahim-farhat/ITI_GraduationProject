#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_

typedef enum
{
	GPIO_LEFT_SECTION = 0,
	GPIO_RIGHT_SECTION
}GPIO_Section_t;

typedef enum
{
	GPIO_PORTA = 0,
	GPIO_PORTB,
	GPIO_PORTC,
	GPIO_PORTD,
	GPIO_PORTE,
	GPIO_PORTF,
	GPIO_PORTG,
	GPIO_PORTH
}GPIO_Port_t;


typedef enum
{
	GPIO_PIN0 = 0,
	GPIO_PIN1,
	GPIO_PIN2,
	GPIO_PIN3,
	GPIO_PIN4,
	GPIO_PIN5,
	GPIO_PIN6,
	GPIO_PIN7,
	GPIO_PIN8,
	GPIO_PIN9,
	GPIO_PIN10,
	GPIO_PIN11,
	GPIO_PIN12,
	GPIO_PIN13,
	GPIO_PIN14,
	GPIO_PIN15
}GPIO_PinNum_t;


typedef enum
{
	GPIO_INPUT = 0,
	GPIO_OUTPUT,
	GPIO_ALTERNATE_FUNCTION,
	GPIO_ANALOG
}GPIO_PinMode_t;


typedef enum
{
	GPIO_PIN_LOW = 0,
	GPIO_PIN_HIGH
}GPIO_PinValue_t;


typedef enum
{
	GPIO_LOW = 0,
	GPIO_MIDIUM,
	GPIO_FAST,
	GPIO_HIGH
}GPIO_PinOutputSpeed_t;


typedef enum
{
	GPIO_PUSH_PULL = 0,
	GPIO_OPEN_DRAIN
}GPIO_PinOutputType_t;


typedef enum
{
	GPIO_AF0 = 0,
	GPIO_AF1,
	GPIO_AF2,
	GPIO_AF3,
	GPIO_AF4,
	GPIO_AF5,
	GPIO_AF6,
	GPIO_AF7,
	GPIO_AF8,
	GPIO_AF9,
	GPIO_AF10,
	GPIO_AF11,
	GPIO_AF12,
	GPIO_AF13,
	GPIO_AF14,
	GPIO_AF15
}GPIO_PinAltFunc_t;


typedef enum
{
	GPIO_NO_PULL = 0,
	GPIO_PULL_UP,
	GPIO_PULL_DOWN,
}GPIO_PinPullUpDown_t;


typedef struct
{
	GPIO_Port_t Port;
	GPIO_PinNum_t PinNum;
	GPIO_PinMode_t PinMode;
	GPIO_PinOutputType_t OutputType;
	GPIO_PinOutputSpeed_t OutputSpeed;
	GPIO_PinPullUpDown_t PullType;
	GPIO_PinAltFunc_t AltFunc;
}GPIO_PinConfig_t;


Error_t GPIO_enPinInit(const GPIO_PinConfig_t *Copy_pstPinConfig);
Error_t GPIO_enSetPinValue(const GPIO_PinConfig_t *Copy_pstPinConfig, GPIO_PinValue_t Copy_enPinValue);
Error_t GPIO_enReadPinValue(const GPIO_PinConfig_t *Copy_pstPinConfig, GPIO_PinValue_t *Copy_penPinValue);
Error_t GPIO_enTogglePinValue(const GPIO_PinConfig_t *Copy_pstPinConfig);
Error_t GPIO_enSetHalfPortValue(GPIO_Port_t Copy_enPort, uint8_t Copy_u8HalfPortValue, GPIO_Section_t Copy_enSection);
Error_t GPIO_enSetPortValue(GPIO_Port_t Copy_enPort, uint16_t Copy_u16PortValue);

#endif




