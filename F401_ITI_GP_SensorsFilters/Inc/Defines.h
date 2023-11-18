#ifndef DEFINES_H_
#define DEFINES_H_


#define NULL		(void *) 0

typedef enum
{
	NULL_PTR_ERROR = 0,
	OK,
	NOK,
	TIMEOUT_ERROR
}Error_t;

typedef enum
{
	DISABLE = 0,
	ENABLE
}Defines_Status_t;

#define BUSY	0u
#define IDLE	1u

#endif
