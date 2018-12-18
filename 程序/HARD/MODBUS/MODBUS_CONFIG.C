#include "MODBUS_CONFIG.H"
#include "MODBUS.H"


#if   USE_RSP_OutCoil >0
u8 rspOutCoilDatBuf[L_RSP_OC]={0X55,0X55,0X55,0X55,0X55};		//输出离散量数组，数据按照倒序存放*
#endif

#if   USE_RSP_InCoil >0
u8 rspInputCoilDatBuf[L_RSP_IC]={0X55,0X55,0X55,0X55,0X55};		//输入离散量数组，数据按照倒序存放
#endif

#if   USE_RSP_HoldREG >0

datBuf rspHoldREGDatBuf = {0};
#endif

#if   USE_RSP_InREG >0
//u16 rspInputREGDatBuf[L_RSP_INREG]={11,12,13,14,15,16,17,18,19,110,111,112,113,114,115,116,117,118};			//输入寄存器数据数组，数据按照倒序存放
#endif

u8 reqSendParameters[L_REQ_OC] = {0};

/*- 数据按照倒序存放- 是指数据的第一位是,rspOutCoilDatBuf[L_RSP_OC-1]的位0，第二位是rspOutCoilDatBuf[L_RSP_OC-1]的位1*/

/************************************************************************************
*-函数名称	：主机请求,发送一条信息
*-参数			：array发送数组,个数是num
*-返回值		：
*-备注			：
*-创建者		：蓬莱市博硕电子科技
*/
void REQSendMessage(u8* array,u16 num)
{
    //发数据
		taskENTER_CRITICAL();
		RS485_UART_Transmit_DMA(&huart1,array,num);
		taskEXIT_CRITICAL();	
}


/************************************************************************************
*-函数名称	：从机回复请求,发送一条信息
*-参数			：array发送数组,个数是num
*-返回值		：
*-备注			：
*-创建者		：蓬莱市博硕电子科技
*/
void RSPSendMessage(u8* array,u16 num)
{

    //发数据
		taskENTER_CRITICAL();     
		RS485_UART_Transmit_DMA(&huart2,array,num);
		taskEXIT_CRITICAL();	
}

//在MODBUS数组低位保存的数组里整型转换成float型
float MDint2float(u32* array)
{
	return *(float*)array;
}
//在MODBUS数组保存的数组里整型转换成int型
u32 MDint2int(u32* array)
{
	return *array;
}
//将foat型转换一下存到MODBUS数组中
void MDfloat2Array(float num,u32* array)
{
	*(float*)array = num;
}

