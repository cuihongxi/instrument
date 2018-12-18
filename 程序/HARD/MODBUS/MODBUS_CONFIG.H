/*
*-Header:MODBUS配置文件
*-Name	: 
*-Autho	:蓬莱市博硕电子科技
*-Date	:2018年7月13日10:31:21
*		重要的配置文档
*	波特率配置说明：
*- 	文档推荐波特率是19200，3.5个字节间隔为1458.3us，波特率115200，间隔为243us
*- 	定时器应配置100us以上中断
*- 	接收中断检测到数据时启动定时器，对1.5个字节时间的间隔不做判断
*- 	大于3.5个字节间隔就认为是一帧数据，并进行处理
*/

#ifndef	__MODBUS_CONFIG_H
#define	__MODBUS_CONFIG_H

#include "UHEAD.H"

/*包含串口头文件*/
#include "stm32f3xx_hal_uart.h"	
#include "MODBUS_REQ_TASK.H"

/*DMA串口接收配置*/
#define	MODBUS_UART_DMA			1

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern HAL_StatusTypeDef RS485_UART_Transmit_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);//485的DMA传输

//	保存数据区定义
//typedef struct{

//	u8 AutoZero;				//自动校零
//	u8 non2;
//	u16 non1[189];
//	u8 ErrorCode;				//报警代码
//	u8 DSPStatus;				//TEMP2
//	u8 CommAddress;			//通讯地址
//	u8 BautRate;				//波特率
//	u8 Direction;				//流量方向
//	u8 DriveSele;				//驱动选择
//	u8 UnitDensity ;		//密度单位
//	u8 UnitTemperature;//温度单位
//	u8 UnitVolumeFlow ;//体积流量单位
//	u8 UnitVolumeTotal;//体积总量单位
//	u8 UnitMassFlow;	//质量流量单位
//	u8 UnitMassTotal;	//质量总量单位
//	
//	u32 DensFT;				//FT
//	u32 MassCT;				//CT
//	u32 NumSN;				//变送器型号
//	u32 TempDamp;			//T阻尼调整系数
//	u32 TempZero;			//T零点调整系数
//	u32 TempSlope;		//T斜率调整系数
//	u32 DensDamp;			//D阻尼调整系数
//	u32 DensZero;			//D零点调整系数
//	u32 DensSlope;		//D斜率调整系数
//	u32 MassDamp;			//Fm阻尼调整系数
//	u32 MassZero;			//Fm零点调整系数
//	u32 MassSlope;		//Fm斜率调整系数
//	u32 MassAdjust;		//Fm流量调整系数
//	u32 PulseValue;		//脉冲当量
//	u32 DensDefault;	//标准密度
//	u32 FlowGate;			//小信号切除
//	u32 TempDefault;	//温度补偿
//	u32 PressDefault;//压力补偿
//	u32 MinTemp;		//温度下限
//	u32 MaxTemp;		//温度上限
//	u32 MinDens;		//密度下限
//	u32 MaxDens;		//密度上限
//	u32 MinVolu;		//体积下限
//	u32 MaxVolu;		//体积上限
//	u32 MinMass;		//质量下限
//	u32 MaxMass;		//质量上限
//	u32 DensityFD;	//密度系数FD
//	u32 DensityK2;	//密度系数K2
//	u32 DensityK1;	//密度系数K1
//	u32 MassFlowK;	//流量系数

//	u32 TimeCount;	//时间
//	u32 VoluTotal;	//体积总量
//	u32 VoluFlow;		//体积流量
//	u32 MassTotal;	//质量总量
//	u32 MassFlow;		//质量流量
//	u32 DspDensity;	//密度
//	u32 DspTemp;		//温度
//	u32 DspFreq;		//频率
//	u32 Z0Delay;		//实时零点	
//	u32 Z1tDelay;		//校正零点
//	u32 Z2Delay;		//动态零点
//	u32 RighAd;			//右线圈AD
//	u32 LeftAd;			//左线圈AD
//	u32 DrivAd;			//驱动AD
///*--------------------------*/
//	u32 FreUper;		//输出频率上限
//	u32 PulesWith;	//脉宽
//	u32 MailAddr;		//通讯地址
//	u32 LLXianXingTiaoZheng;//流量测量线性调整
//	
//	u16 non0[0xdc];	//空
//}datBuf;

typedef struct{
//	u16 non0[0xdc];	//空
	u32 FreUper;		//输出频率上限
	u32 PulesWith;	//脉宽
	u32 MailAddr;		//通讯地址
	u32 LLXianXingTiaoZheng;//流量测量线性调整
/*--------------------------*/	
	u32 DrivAd;			//驱动AD
	u32 LeftAd;			//左线圈AD
	u32 RighAd;			//右线圈AD
	u32 Z2Delay;		//动态零点	
	u32 Z1tDelay;		//校正零点	
	u32 Z0Delay;		//实时零点	
	u32 DspFreq;		//频率
	u32 DspTemp;		//温度
	u32 DspDensity;	//密度	
	u32 MassFlow;		//质量流量
	u32 MassTotal;	//质量总量	
	u32 VoluFlow;		//体积流量
	u32 VoluTotal;	//体积总量
	u32 TimeCount;		//时间
	u32 MassFlowK;	//流量系数	
	u32 DensityK1;	//密度系数K1	
	u32 DensityK2;	//密度系数K2
	u32 DensityFD;	//密度系数FD	
	u32 MaxMass;		//质量上限
	u32 MinMass;		//质量下限
	u32 MaxVolu;		//体积上限
	u32 MinVolu;		//体积下限
	u32 MaxDens;		//密度上限	
	u32 MinDens;		//密度下限
	u32 MaxTemp;		//温度上限
	u32 MinTemp;		//温度下限
	u32 PressDefault;//压力补偿
	u32 TempDefault;	//温度补偿
	u32 FlowGate;			//小信号切除	
	u32 DensDefault;	//标准密度
	u32 PulseValue;		//脉冲当量
	u32 MassAdjust;			//Fm流量调整系数
	u32 MassSlope;			//Fm斜率调整系数
	u32 MassZero;			//Fm零点调整系数
	u32 MassDamp;			//Fm阻尼调整系数
	u32 DensSlope;		//D斜率调整系数
	u32 DensZero;			//D零点调整系数
	u32 DensDamp;			//D阻尼调整系数
	u32 TempSlope;		//T斜率调整系数
	u32 TempZero;			//T零点调整系数
	u32 TempDamp;			//T阻尼调整系数
	u32 NumSN;					//变送器型号
	u32 MassCT;				//CT
	u32 DensFT;				//FT

	u8 UnitMassFlow;		//质量流量单位
	u8 UnitMassTotal;		//质量总量单位
	u8 UnitVolumeFlow ;	//体积流量单位	
	u8 UnitVolumeTotal;	//体积总量单位	
	u8 UnitDensity ;		//密度单位
	u8 UnitTemperature;	//温度单位
	u8 Direction;				//流量方向
	u8 DriveSele;				//驱动选择
	u8 CommAddress;			//通讯地址
	u8 BautRate;				//波特率
	u8 ErrorCode;				//报警代码
	u8 DSPStatus;				//TEMP2	
	u16 non1[189];
	u8 non2;
	u8 AutoZero;				//自动校零	
	
}datBuf;

//配置OFF是置0，还是置1
#define		MD_TURN_OFF(a,b)		a=((a)&(~(0x01<<(b))))			//写线圈为OFF状态,b是位
#define		MD_TURN_ON(a,b)			a=((a)|((0x01<<(b))))			//写线圈为ON状态,b是位


/*******************************从机RSP的配置***************************************************/
#define		L_RSP_OC				5			//输出线圈数组大小
#define		L_RSP_IC				5			//输入线圈数组大小
#define		L_RSP_OUTREG		512-0xdc		//输出保持寄存器数组大小
#define		L_RSP_INREG			18		//输入寄存器数组大小

#define		USE_RSP_OutCoil		0		//输出离散量数组，1为使能，0禁止
#define		USE_RSP_InCoil		0		//输入离散量数组，1为使能，0禁止
#define		USE_RSP_HoldREG		1		//输出保持寄存器，1为使能，0禁止
#define		USE_RSP_InREG			1		//输入寄存器，1为使能，0禁止

//设置串口初始化函数
#define		RSP_UART_INIT(a)		//RS485_Init(a)

//设置从机本地地址
#define		RSP_LOCAL_ADDR			1		//(1~247)为合法子地址，0为广播地址，所有子设备都要识别

extern u8 rspOutCoilDatBuf[L_RSP_OC];		//输出离散量数组，数据按照倒序存放*
extern u8 rspInputCoilDatBuf[L_RSP_IC];		//输入离散量数组，数据按照倒序存放
extern datBuf rspHoldREGDatBuf;//u16 rspHoldREGDatBuf[L_RSP_OUTREG] ;	//输出保持寄存器数据数组
extern u16 rspInputREGDatBuf[L_RSP_INREG];	//输入寄存器数据数组，数据按照倒序存放

/*********************************主机REQ的配置****************************************************/
#define		L_REQ_OC				8				//保存的是发送的器件地址，命令，数量，地址，所以大小至少为6
//#define		L_REQ_IC				20			//临时保存的是从机的返回数据

extern u8 reqSendParameters[L_REQ_OC];			//保存的是发送的器件地址，命令，数量，地址，所以大小至少为6
//extern u8 reqReceiveData[L_REQ_IC] ;				//临时保存的是从机的返回数据

#define		USE_REQ_OutCoil		0		//请求离散量数组，1为使能，0禁止
#define		USE_REQ_InCoil		0		//请求离散量数组，1为使能，0禁止
#define		USE_REQ_HoldREG		1		//请求保持寄存器，1为使能，0禁止
#define		USE_REQ_InREG		1		//请求寄存器，1为使能，0禁止

//设置主机串口初始化函数
#define		REQ_UART_INIT(a)		//RS485_Init(a)

//设置请求等待超时时间
#define		REQWAIT_TIME		0.5		//单位s

//主从机发送消息函数
void REQSendMessage(u8* array,u16 num);
void RSPSendMessage(u8* array,u16 num);
float MDint2float(u32* array);
u32 MDint2int(u32* array);

void MDfloat2Array(float num,u32* array);//将foat型转换一下存到MODBUS数组中
#endif


