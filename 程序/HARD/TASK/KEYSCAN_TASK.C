#include "KEYSCAN_TASK.H"
#include "ad7147_spi.h"
#include "ad7147regmap.h"
#include "ad7147_spi.h"
#include "TASK_PROJECT.H"
#include "timers.h"
u8 key_val = 0;
TaskHandle_t 	KeyScan_Handle;
unsigned int keyval = 0;
void KeyScan_Task(void)
{
	
	u8 flag_notify = 0;				//非零的时候发送通知
	static unsigned int beforeVal = 0;
	static u8 flag_tim = 0;
	ConfigAD7147();
	DEBUG_Log("KeyScan_Task created OK! \r\n");
//	ReadFromAD7147(0x017,1,(WORD*)&keyval,0);
//	DEBUG_Log("AD7147 IP = %#x\r\n",keyval);		//打印版本号ID：0x1471
	keyval = 0;
	
	while(1)
	{
		ulTaskNotifyTake(pdTRUE,portMAX_DELAY);	//等待通知
		keyval = ServiceAD7147Isr();			//获取键值

		if(keyval == 0)	//抬起
		{
			if(beforeVal == BUTTON_ENTER_VAL) flag_notify = beforeVal;
			if(beforeVal == BUTTON_NEXT_VAL) flag_notify = beforeVal;
			beforeVal = 0;
		}
		//同时按下
		if(keyval == (BUTTON_ENTER_VAL|BUTTON_NEXT_VAL) && flag_tim == 0)
		{
			flag_tim = 1;			
			xTimerStart(timerHandle,0);
		}else 
		{
			if(flag_tim)
			{
				flag_tim = 0;
				xTimerStop(timerHandle,0);
			}
		}
		
		if(beforeVal<keyval) beforeVal = keyval;	//保持这次的键值
		
		//LED响应
		if(keyval & BUTTON_ENTER_VAL)
		{
				//HAL_GPIO_WritePin(LED_ENTER,GPIO_PIN_SET);
				LIGHTEN_LED(LED_ENTER);		
		}	  
		else  QUENCH_LED(LED_ENTER);//HAL_GPIO_WritePin(LED_ENTER,GPIO_PIN_RESET);
		if(keyval & BUTTON_NEXT_VAL)
		{
				//HAL_GPIO_WritePin(LED_NEXT,GPIO_PIN_SET);
				LIGHTEN_LED(LED_NEXT);		
		}
		else  QUENCH_LED(LED_NEXT);//HAL_GPIO_WritePin(LED_NEXT,GPIO_PIN_RESET);
		//发送通知
		if(flag_notify)
		{	
			key_val = flag_notify;
			flag_notify = 0;
		}
		vTaskDelay(10);	
		
	}
	
}

//定时器回调函数
void keyTimerCallBack(TimerHandle_t xTimer)
{
	key_val = BUTTON_ENTER_VAL|BUTTON_NEXT_VAL;
}


extern u32 counter_inSetMenu;//3分钟计时器
//INT中断
  void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
  {
	  static BaseType_t baseVal = 0;
		counter_inSetMenu = 0;						//3分钟计时器清0	
	  vTaskNotifyGiveFromISR(KeyScan_Handle,&baseVal);
	  portYIELD_FROM_ISR(baseVal);
  }
