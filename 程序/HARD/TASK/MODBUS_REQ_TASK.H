#ifndef	__MODBUS_REQ_TASK_H
#define	__MODBUS_REQ_TASKK_H
#include "uhead.h"




#define	RS485_TX1		RS485_RE1_GPIO_Port,RS485_RE1_Pin

#define	MD_GUITASK 	1

HAL_StatusTypeDef RS485_UART_Transmit_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);//485µÄDMA´«Êä



#endif
