#include "PWM_TASK.H"
#include "uhead.h"
#include "tim.h"
#include "stm32f3xx_hal_tim.h"
#include "MODBUS_CONFIG.H"
#include "menu.h"
#include "AD5662.h"

TaskHandle_t 	PWM_T1OUT1Handle;
TaskHandle_t 	PWM_T2OUT2Handle;
TaskHandle_t 	PWM_T2OUT3Handle;

extern ShowStr showNature ;

/************************************************************************************
*-函数名称	：PWM设置并开启
*-参数			： prescaler 预分频; period,周期; duty 占空比0~100
*-返回值		：
*-备注			：
*-创建者		：蓬莱市博硕电子科技
*/
void PWM_SetAndStart(TIM_HandleTypeDef* htim,u16 prescaler,u16 period ,uint32_t Channel,u8 duty)
{

	htim->Init.Prescaler = prescaler;           //定时器分频
	htim->Init.CounterMode = TIM_COUNTERMODE_UP;//向上计数模式
	htim->Init.Period = period;              		//自动重装载值
	htim->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;	//自动重装使能
	HAL_TIM_PWM_Init(htim);           					//初始化PWM

	TIM_OC_InitTypeDef     TIMx_CHxHandler;    //定时器x通道x句柄
	TIMx_CHxHandler.OCMode = TIM_OCMODE_PWM1; //模式选择PWM1
	TIMx_CHxHandler.Pulse = (period)*duty/100;            //设置比较值,此值用来确定占空比，默认比较值为自动重装载值的一半,即占空比为50%
	TIMx_CHxHandler.OCPolarity=TIM_OCPOLARITY_HIGH; //输出比较极性为高  
	TIMx_CHxHandler.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	TIMx_CHxHandler.OCFastMode = TIM_OCFAST_DISABLE;
	TIMx_CHxHandler.OCIdleState = TIM_OCIDLESTATE_RESET;
  TIMx_CHxHandler.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	
	HAL_TIM_PWM_ConfigChannel(htim,&TIMx_CHxHandler,Channel);//配置TIMx通道x    
	HAL_TIM_PWM_Start(htim,Channel);//开启PWM通道
}

/************************************************************************************
*-函数名称	：设置PWM频率
*-参数			：duty 占空比,0~100,hz 频率,0~10K
*-返回值		：
*-备注			：
*-创建者		：蓬莱市博硕电子科技
*/
void PWM_SetHz(TIM_HandleTypeDef* htim,uint32_t Channel,u8 duty,u16 hz)
{
	PWM_SetAndStart(htim,71,1000000/hz, Channel,duty);
}

/************************************************************************************
*-函数名称	：根据上下限和数值输出频率
*-参数			：
*-返回值		：
*-备注			：占空比固定是50,预分频系数72
*-创建者		：蓬莱市博硕电子科技
*/
void PWM_OutputHZ(TIM_HandleTypeDef* htim,uint32_t Channel,float upper_dat,float floor_dat,float upper_hz,float floor_hz,float dat)
{
	float hz = 0;
	if((upper_dat - floor_dat + floor_hz) != 0 )
		hz = (dat - floor_dat)*(upper_hz - floor_hz)/(upper_dat - floor_dat) + floor_hz;
	PWM_SetHz(htim,Channel,50,(u16)hz);
}

//根据设置,获取输出参数
typedef struct{
	float floor_dat;		//下限
	float upper_dat;		//上限
	float real_dat;			//瞬时数据
}pwmArgs;

void GetpwmArgs(pwmArgs* pwmArg,u8 sele)
{

	switch(sele)
	{
		case 0 :	//质量流量
				pwmArg->floor_dat = MDint2float(&rspHoldREGDatBuf.MinMass);
				pwmArg->upper_dat = MDint2float(&rspHoldREGDatBuf.MaxMass);
				pwmArg->real_dat = MDint2float(&rspHoldREGDatBuf.MassFlow);
			break;
		case 1 :	//体积流量
				pwmArg->floor_dat = MDint2float(&rspHoldREGDatBuf.MinVolu);
				pwmArg->upper_dat = MDint2float(&rspHoldREGDatBuf.MaxVolu);
				pwmArg->real_dat = MDint2float(&rspHoldREGDatBuf.VoluFlow);			
			break;
		case 2 :	//密度
				pwmArg->floor_dat = MDint2float(&rspHoldREGDatBuf.MinDens);
				pwmArg->upper_dat = MDint2float(&rspHoldREGDatBuf.MaxDens);
				pwmArg->real_dat = MDint2float(&rspHoldREGDatBuf.DspDensity);				
			break;
		case 3 :	//温度
				pwmArg->floor_dat = MDint2float(&rspHoldREGDatBuf.MinTemp);
				pwmArg->upper_dat = MDint2float(&rspHoldREGDatBuf.MaxTemp);
				pwmArg->real_dat = MDint2float(&rspHoldREGDatBuf.DspTemp);	
			break;
	}
}
void PWM_T1OUT1_Task(void)
{
	//根据设置,获取输出参数
	pwmArgs pwmArg ;
	static pwmArgs static_pwmArg ;
	static u8 static_sele;
	MDfloat2Array(100,&rspHoldREGDatBuf.MaxMass);		//设置质量流量上限
  MDfloat2Array(0,&rspHoldREGDatBuf.MinMass);			//设置质量流量下限
  GetpwmArgs(&pwmArg,(u8)showNature.signalSelect1);
	static_pwmArg.floor_dat = pwmArg.floor_dat;
	static_pwmArg.real_dat = pwmArg.real_dat;
	static_pwmArg.upper_dat = pwmArg.upper_dat;
	static_sele = (u8)showNature.signalSelect1;
	PWM_OutputHZ(&htim1,TIM_CHANNEL_1,pwmArg.upper_dat,pwmArg.floor_dat,10000.0,0,pwmArg.real_dat);
	Output_4To20mA(pwmArg.upper_dat,pwmArg.floor_dat,pwmArg.real_dat);//电流
	DEBUG_Log("PWM_T1OUT1_Task created OK!\r\n");
	while(1)
	{
		
		ulTaskNotifyTake(pdTRUE,portMAX_DELAY);	//等待通知
		GetpwmArgs(&pwmArg,(u8)showNature.signalSelect1);
		if(static_sele!=(u8)showNature.signalSelect1 || static_pwmArg.floor_dat != pwmArg.floor_dat\
			|| static_pwmArg.real_dat != pwmArg.real_dat || static_pwmArg.upper_dat != pwmArg.upper_dat)
		{	
			//变更输出频率和电流
			PWM_OutputHZ(&htim1,TIM_CHANNEL_1,pwmArg.upper_dat,pwmArg.floor_dat,10000.0,0,pwmArg.real_dat);	
			Output_4To20mA(pwmArg.upper_dat,pwmArg.floor_dat,pwmArg.real_dat);
			static_pwmArg.floor_dat = pwmArg.floor_dat;
			static_pwmArg.real_dat = pwmArg.real_dat;
			static_pwmArg.upper_dat = pwmArg.upper_dat;
			static_sele = (u8)showNature.signalSelect1;			
		}
		vTaskDelay(100);
	}
}

void PWM_T2OUT2_Task(void)
{
	
	PWM_SetAndStart(&htim2,71,10000,TIM_CHANNEL_2,50);
	DEBUG_Log("PWM_T2OUT2_Task created OK!\r\n");
	while(1)
	{
		vTaskDelay(100);

	}
}

void PWM_T2OUT3_Task(void)
{
	PWM_SetAndStart(&htim2,71,10000,TIM_CHANNEL_1,80);
	DEBUG_Log("PWM_T2OUT3_Task created OK!\r\n");
	while(1)
	{

		vTaskDelay(100);
	}
}





