/*
 * MSPI_Interface.h
 *
 *  Created on: Oct 2, 2023
 *      Author: Shereef Mahmoud
 */

#ifndef MSPI_INTERFACE_H_
#define MSPI_INTERFACE_H_

void MSPI_voidInit(void);
void MSPI_voidSendRecieveDataSync(uint8_t Copy_u8TransmitData,uint8_t *Copy_u8RecievedData);

void MSPI_voidInitSlave(void);
void MSPI_voidInitMaster(void);

#endif /* MSPI_INTERFACE_H_ */
