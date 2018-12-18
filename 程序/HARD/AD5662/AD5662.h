/*
16位DAC驱动
*/

#ifndef	__AD5662_H
#define	__AD5662_H
#include "uhead.h"

#define	AD5662_DIN_0	GPIO_RESET(AD5662_DIN)
#define	AD5662_DIN_1	GPIO_SET(AD5662_DIN)
#define	AD5662_SYNC_0	GPIO_RESET(AD5662_SYNC)
#define	AD5662_SYNC_1	GPIO_SET(AD5662_SYNC)
#define	AD5662_SCK_0	GPIO_RESET(AD5662_SCK)
#define	AD5662_SCK_1	GPIO_SET(AD5662_SCK)

	//掉电模式
typedef enum
{
	AD5662_MOD_NORMAL = 0,
	AD5662_MOD_1K,
	AD5662_MOD_100K,
	AD5662_MOD_THREE_STATE 
}AD5662_PowerDownMod;

/*函数*/
void AD5662_Init(void);
void AD5662_Write(AD5662_PowerDownMod mod,u16 dat);
void Output_4To20mA(float upper_dat,float floor_dat,float dat);
#endif		
