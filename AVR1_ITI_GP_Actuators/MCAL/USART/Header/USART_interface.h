/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: USART_interface.h		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file USART_interface.h
 * @author Ibrahim Tarek
 * @brief This file interfaces the USART module functions.
 * @version 1.00
 */

#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

/**
 * @brief Function to initialize the USART peripheral.
 */
void USART_voidInit(void);

/**
 * @brief 				Function to transmit data by USART up to nine bits.
 * @param Copy_u16Data	Data that will be transmitted by USART.
 * @return				Error State.
 */
uint8 USART_u8Send(uint16 Copy_u16Data);


/**
 * @brief 				Function to receive data by USART up to nine bits.
 * @param Copy_pvData 	Pointer to return the data received.
 * @return 				Error State.
 */
uint8 USART_u8Receive(void *Copy_pvData);

/**
 * @brief 					Function to send a buffer by USART with synchronous operation.
 * @param Copy_pvBufferArr	Pointer to buffer array to be transmitted.
 * @param Copy_u8BufferSize Size of the buffer array.
 * @return 					Error State.
 */
uint8 USART_u8SendBufferSynch(const void *Copy_pvBufferArr, uint8 Copy_u8BufferSize);

/**
 * @brief 						Function to send a buffer by USART with synchronous operation.
 * @param Copy_pu16BufferArr 	Pointer to buffer array to be transmitted.
 * @param Copy_u8BufferSize 	Size of the buffer array.
 * @return 						Error State.
 */
uint8 USART_u8ReceiveBufferSynch(uint8 *Copy_pu8BufferArr, uint8 Copy_u8BufferSize);

/**
 * @brief 							Function to send a buffer by USART with asynchronous operation.
 * @param Copy_pvBufferArr 			Pointer to buffer array to be transmitted.
 * @param Copy_u8BufferSize			Size of the buffer array.
 * @param Copy_pvNotificationFunc	Pointer to the notification function.
 * @return 							Error state.
 */
uint8 USART_u8SendBufferAsynch(void *Copy_pvBufferArr, uint8 Copy_u8BufferSize, void (*Copy_pvNotificationFunc)(void));

/**
 * @brief 							Function to receive a buffer by USART with asynchronous operation.
 * @param Copy_pvBufferArr 			Pointer to buffer array to return data on it.
 * @param Copy_u8Bufferize 			Size of the buffer array.
 * @param Copy_pvNotificationFunc 	Pointer to the notification function.
 * @return 							Error State.
 */
uint8 USART_u8ReceiveBufferAsynch(void *Copy_pvBufferArr, uint8 Copy_u8Bufferize, void (*Copy_pvNotificationFunc)(void));

#endif
