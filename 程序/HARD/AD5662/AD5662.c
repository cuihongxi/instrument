#include "AD5662.h"

/************************************************************************************
*-函数名称	：初始化
*-参数			：
*-返回值		：
*-备注			：全部拉高
*-创建者		：蓬莱市博硕电子科技
*/

void AD5662_Init(void)
{
	AD5662_DIN_1;
	AD5662_SYNC_1;
	AD5662_SCK_1;
}

/************************************************************************************
*-函数名称	：写数据
*-参数			：mod: 00正常模式;01 1 kΩ TO GND;10 100 kΩ TO GND;11 THREE-STATE 
*-返回值		：
*-备注			：24个时钟周期一个数据,下降沿数据稳定
*-创建者		：蓬莱市博硕电子科技
*/

void AD5662_Write(AD5662_PowerDownMod mod,u16 dat)
{
	u8 i = 0;
	AD5662_SCK_0;
	AD5662_DIN_0;
	AD5662_SYNC_0;	
	for(i=0;i<6;i++)
	{
		AD5662_SCK_1;
		AD5662_SCK_0;	
	}
	//发送模式
	if(mod&0x02)AD5662_DIN_1;
	else AD5662_DIN_0;
	AD5662_SCK_1;
	AD5662_SCK_0;	
	if(mod&0x01)AD5662_DIN_1;
	else AD5662_DIN_0;
	AD5662_SCK_1;
	AD5662_SCK_0;
	//发送数据
	for(i=0;i<16;i++)
	{
		if(dat&0x8000)AD5662_DIN_1;
		else AD5662_DIN_0;		
		AD5662_SCK_1;
		AD5662_SCK_0;
		dat <<= 1;	
	}	
	AD5662_SYNC_1;
	
}
/************************************************************************************
*-函数名称	：输出4~20ma对应的电流
*-参数			：upper_dat: 上限; floor_dat: 下限; dat: 实时数据
*-返回值		：
*-备注			：
*-创建者		：蓬莱市博硕电子科技
*/

void Output_4To20mA(float upper_dat,float floor_dat,float dat)
{
	AD5662_Write(AD5662_MOD_NORMAL,(u16)(65536*dat/(upper_dat-floor_dat)));
}






