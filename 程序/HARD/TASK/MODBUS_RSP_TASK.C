#include "MODBUS_RSP_TASK.H"
#include "uhead.h"
#include "usart.h"
#include "stm32f3xx_hal_uart.h"
#include "string.h"
#include "stm32f3xx_hal_dma.h"
#include "modbus_rsp.h"

extern DMA_HandleTypeDef hdma_usart2_rx;
TaskHandle_t	modbusRsp_Handle;
MD_datstr MDRsp_str = {0};	

void ModbusRsp_Task(void)
{
	typeErro erro = 0;
	MD_RSP_Init(19200,&MDRsp_str);
//	HAL_GPIO_WritePin(RS485_TX2,GPIO_PIN_RESET); 						// USART2接收  
	HAL_UART_Receive_DMA(&huart2,(u8*)&MDRsp_str,MD_BUFNUM);
	__HAL_UART_ENABLE_IT(&huart2, UART_IT_IDLE);						// 开启空闲接收中断 
	__HAL_UART_CLEAR_IDLEFLAG(&huart2); 										//清空闲中断
	DEBUG_Log("ModbusRsp_Task created OK!\r\n");
	
	while(1)
	{

			ulTaskNotifyTake(pdTRUE,portMAX_DELAY);	//等待通知
			erro = RSP_CallBack(&MDRsp_str);
		
			if(erro != MD_ERROR_OK)
			{
					switch(erro)
					{
						case REQ_RECEIVE_ERROR_NUM:			ERROR_Log("REQ_RECEIVE_ERROR_NUM\r\n");
							break;
						case REQ_RECEIVE_ERROR_CRC:  		ERROR_Log("REQ_RECEIVE_ERROR_CRC\r\n");
							break;
            	default: 										 	ERROR_Log("\r\n Rsp error:  0x%x\r\n ",erro);
            		break;
					}
			}
				
				HAL_UART_Receive_DMA(&huart2,(u8*)&MDRsp_str,MD_BUFNUM);
			//rspHoldREGDatBuf.MassFlow ++;
			((datBuf*)&rspHoldREGDatBuf)->DrivAd = 0x11223344;
			((datBuf*)&rspHoldREGDatBuf)->LeftAd = 0x00005000;
			
//			rspHoldREGDatBuf.DspTemp = 23;
//			rspHoldREGDatBuf.DspFreq = 50;
	}
}

void UsartReceiveRSP_IDLE(UART_HandleTypeDef *huart) 
	{ 
		if(huart == &huart2)
		{			
			MD_DMAInUART_IDLE(&MDRsp_str,&huart2,&hdma_usart2_rx);
		}		
	} 




