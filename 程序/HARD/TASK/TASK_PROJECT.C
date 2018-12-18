#include "TASK_PROJECT.H"
#include "KEYSCAN_TASK.H"
#include "GUI_TASK.H"
#include "MODBUS_REQ_TASK.H"

TimerHandle_t timerHandle;		//定时器句柄
TaskHandle_t HighWaterMark_Handle;
void HighWaterMark_Task(void);
#ifdef 		SHOW_METaskInfor
char infoBuffer[500] = {0};
#endif
#ifdef 		SHOW_ME_RunTimeStats
char infoBuffer[500] = {0};
#endif

extern TaskHandle_t 	KeyScan_Handle;
extern TaskHandle_t 	GUI_Handle;
extern TaskHandle_t		modbusReq_Handle;
extern TaskHandle_t		modbusRsp_Handle;
extern TaskHandle_t 	PWM_T1OUT1Handle;
extern TaskHandle_t 	PWM_T2OUT2Handle;
extern TaskHandle_t 	PWM_T2OUT3Handle;

extern void KeyScan_Task(void);
extern void GUI_Task(void);
extern void ModbusReq_Task(void);
extern void ModbusRsp_Task(void);
extern void PWM_T1OUT1_Task(void);
extern void PWM_T2OUT2_Task(void);
extern void PWM_T2OUT3_Task(void);

//任务数组
TASK_STR taskArray[] ={
(TaskFunction_t)KeyScan_Task,				"KeyScan",			128,	NULL,8,&KeyScan_Handle,
(TaskFunction_t)GUI_Task,						"GUI",				200,NULL,14,&GUI_Handle,	
(TaskFunction_t)ModbusReq_Task,			"ModbusReq",		200,NULL,7,&modbusReq_Handle,	
//(TaskFunction_t)ModbusRsp_Task,			"ModbusRsp",		200,NULL,10,&modbusRsp_Handle, 
#ifdef 		SHOW_ME_RunTimeStats
(TaskFunction_t)HighWaterMark_Task,			"RunTimeStats",		128,NULL,10,&HighWaterMark_Handle, 
#endif	
#ifdef 		SHOW_METaskInfor
(TaskFunction_t)HighWaterMark_Task,			"TaskInfor",		128,NULL,10,&HighWaterMark_Handle, 
#endif		
(TaskFunction_t)PWM_T1OUT1_Task,			"PWM_T1OUT1",		128,NULL,13,&PWM_T1OUT1Handle, 	
(TaskFunction_t)PWM_T2OUT2_Task,			"PWM_T2OUT2",		128,NULL,12,&PWM_T2OUT2Handle, 	
(TaskFunction_t)PWM_T2OUT3_Task,			"PWM_T2OUT3",		128,NULL,11,&PWM_T2OUT3Handle, 	
	
};


void HighWaterMark_Task(void)
{

	
	while(1)
	{
		
#ifdef 		SHOW_ME_RunTimeStats
		vTaskGetRunTimeStats(infoBuffer);//打印任务运行时间
		printf("%s\r\n",infoBuffer);
#endif		
		
#ifdef SHOW_METaskInfor
		vTaskList(infoBuffer);				//打印任务信息
		printf("%s\r\n",infoBuffer);
#endif			
		vTaskDelay(2000);
	}
}
//遍历创建任务
//返回0 创建成功；返回数字代表相应的任务没有创建成功
u8 Task_CreatTrave(void)
{
	u8 i = 0;
	BaseType_t erro;
	taskENTER_CRITICAL();
	for(i=0;i<GETSIZE(taskArray);i++)
	{
		
		erro = xTaskCreate(
		taskArray[i].pxTaskCode,
		taskArray[i].pcName,
		taskArray[i].usStackDepth,
		taskArray[i].pvParameters,
		taskArray[i].uxPriority,
		taskArray[i].pxCreatedTask);
		
		
		if(erro != pdPASS) 
		{
			DEBUG_Log("xTaskCreate ERROR : i+1\r\n");
			taskEXIT_CRITICAL();
			return i+1;
		}
		
	}
	DEBUG_Log("xTaskCreate OK!\r\n");
	taskEXIT_CRITICAL();
	return 0;
}

#ifdef 		SHOW_ME_RunTimeStats
extern unsigned long freeRTOSrunTimeTicks;	//任务时间节拍计时器
//获得运行时间
unsigned long getRunTimeCounterValue(void)
{
	return  freeRTOSrunTimeTicks;	//任务计时器
}
#endif	
