
#include "MODBUS_REQ_TASK.H"
#include "MODBUS_RSP_TASK.H"
#include "uhead.h"
#include "usart.h"
#include "stm32f3xx_hal_uart.h"
#include "stm32f3xx_hal_dma.h"
#include "modbus_req.h"
#include "tim.h"
#include "modbus.h"
#include "cmsis_os.h"
#include "listview.h"

#define	USART_BUF_NUM	50
TaskHandle_t	modbusReq_Handle;

extern MD_datstr MDRsp_str;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern TaskHandle_t 	GUI_Handle;


u8 flag_inSetMenu	= 0;								//进入设置菜单的标志位,计时3分钟,无按键按下自动回到主界面
u32 counter_inSetMenu = 0;						//3分钟计时器
#ifdef 		SHOW_ME_RunTimeStats
unsigned long freeRTOSrunTimeTicks = 0;	//任务计时器
#endif

QueueHandle_t req_QueueHandle;	//发送请求队列句柄


MD_datstr MD_str = {0};	//一个MODBUS请求实例

//485的DMA传输
HAL_StatusTypeDef RS485_UART_Transmit_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
	if(Size)
	{
		if(huart == &huart1)
		return HAL_UART_Transmit_DMA(huart,pData,Size);	
	}
	return HAL_ERROR;

}

//读偏移的数据

typeErro REQTask_Read(MD_datstr* pMD_Reqstr,u8 FunNum,u8 dev_addr,u16 startAddr,u16 datnum,datBuf* saveAddr)
{
	 return REQ_Read(pMD_Reqstr,FunNum,dev_addr,startAddr,datnum,(u8*)(saveAddr) + (startAddr-0xdc)*2);
}

//写偏移的数据
typeErro REQTask_WriteREGs(MD_datstr* pMD_Reqstr,u8 dev_addr,u16 startAddr,u16 datnum,datBuf* pDatBuf)
{
	return REQ_WriteREGs(pMD_Reqstr,dev_addr,startAddr,datnum,(u16*)pDatBuf  + (startAddr-0xdc));
}

void ModbusReq_Task(void)
{
	reqQueueStr req_message ={0};
	typeErro erro = 0;
	MD_REQ_Init(19200,&MD_str);												 
	HAL_UART_Receive_DMA(&huart1,(u8*)&MD_str,MD_BUFNUM);
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);						// 开启空闲接收中断 
	__HAL_UART_CLEAR_IDLEFLAG(&huart1); 										//清空闲中断
	
	req_QueueHandle = xQueueCreate(4,sizeof(reqQueueStr));	//创建请求队列
	if(req_QueueHandle == NULL) 
	{
		ERROR_Log("Create ReqQueue Fail\r\n");
	}
	DEBUG_Log("ModbusReq_Task created OK!\r\n");
	HAL_TIM_Base_Start_IT(&htim6);	//开启定时器
	while(1)		//读参数
	{
		erro = REQTask_Read(&MD_str,MD_READ_HOLD_REG,1,0x0100,66,&rspHoldREGDatBuf);	
		if(erro != MD_ERROR_OK)		ERROR_Log("REQ_Read ERROR = 0X%X\r\n",erro);
		ulTaskNotifyTake(pdTRUE,500);	//等待通知
		if(REQ_DMAInMain(&MD_str) != MD_ERROR_OK)
		{
			__HAL_UART_CLEAR_IDLEFLAG(&huart1); 
			HAL_UART_Receive_DMA(&huart1,(u8*)&MD_str,MD_BUFNUM);				
		}else 
		{
			ERROR_Log("\r\nOK\r\n");
			break;	
		}
		vTaskDelay(500);
	}		

	
	while(1)
	{
			
			xQueueReceive(req_QueueHandle,&req_message,portMAX_DELAY);				//获取消息队列中的消息
			if(req_message.FunNum == MD_WRITE_REGS)					//写入寄存器
			{
				erro = REQTask_WriteREGs(&MD_str,req_message.dev_addr,req_message.startAddr,req_message.datnum,&rspHoldREGDatBuf);
			}else
				erro = REQTask_Read(&MD_str,req_message.FunNum,req_message.dev_addr,req_message.startAddr,req_message.datnum,&rspHoldREGDatBuf);			
			if(erro != MD_ERROR_OK)		ERROR_Log("REQ_Read ERROR = 0X%X\r\n",erro);
			ulTaskNotifyTake(pdTRUE,500);	//等待通知
			if(REQ_DMAInMain(&MD_str) != MD_ERROR_OK)
			{
				__HAL_UART_CLEAR_IDLEFLAG(&huart1); 
				HAL_UART_Receive_DMA(&huart1,(u8*)&MD_str,MD_BUFNUM);				
			}
			//如果是GUI发来的任务,发回一个信号量
			if(req_message.task == MD_GUITASK)		
			{
				xTaskNotify(GUI_Handle,1,eSetValueWithOverwrite);	
			}

		vTaskDelay(3);
	}
}

/* 串口接收空闲中断 */ 
void UsartReceive_IDLE(UART_HandleTypeDef *huart) 
	{ 
		
		if(huart == &huart1)
		{			
			MD_DMAInUART_IDLE(&MD_str,&huart1,&hdma_usart1_rx);
		}	
	} 

#define	TIMOUT_INSETMENU	900000
#include "menu.h"
extern	ShowStr showNature;	
//定时器更新中断,200us
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	static u8 counter6 = 0;
	reqQueueStr req_message ;
	BaseType_t pxHigherPriority;		//保存是否进行任务切换
	req_message.datnum = 28;
	req_message.dev_addr = 1;
	req_message.FunNum = MD_READ_HOLD_REG;
	req_message.startAddr = 0xe4;

	if(htim == &htim6)
	{
#ifdef 		SHOW_ME_RunTimeStats		
		freeRTOSrunTimeTicks ++;
#endif		
		//定时发送
		counter6 ++;
		if(counter6 > 250)	//50ms定时到
		{
			counter6 = 0;
			xQueueSendFromISR(req_QueueHandle,&req_message,&pxHigherPriority);		
		}	
			//MODBUS
		MD_Fun_InTime(&MD_str,200);				//在定时器中的函数	
		MD_Fun_InTime(&MDRsp_str,200);		//在定时器中的函数	
		if(flag_inSetMenu)								//3分钟定时回到主界面
		{
			counter_inSetMenu ++;
			if(counter_inSetMenu > TIMOUT_INSETMENU)
			{
				flag_inSetMenu = 0;
				counter_inSetMenu = 0;
				showNature.flag_init = NO_INIT;
				showNature.thisNature = (NatureStr*)MainMenu;
			}
		}
	}
}






