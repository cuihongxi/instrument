#include "dataview.h"
#include "CUIGUI_LCDDRIVER.H"
#include "GUI.H"
#include "OLED12864.H"
#include "keyscan_task.h"
#include "MODBUS_CONFIG.H"
#include "listview.h"

extern ListStr*  		listINTERFACE;
extern NatureStr 		mainMenu;
extern ShowStr 			showNature;
extern const char* 	arraySetZLCeLiangUnits[];
extern const char* 	arraySetTJCeLiangUnits[];
extern const char* 	arraySetDensityUnits[];
extern const char* 	arraySetTempUnits[];
extern u8 					flag_inSetMenu;
extern float 				MDint2float(u32* array);

u8  PageNumber=0; 

//更新数据
void ReviewData(int x,int y,float* olddata,float newdata,u8* numArray,u8 precision)
{
	if(*olddata != newdata)
	{
		CUIGUI_DrawDoubleColorNum(x,y, 2, *olddata,numArray,precision);	//清除原先的数字
		*olddata = newdata;
		CUIGUI_DrawDoubleColorNum(x,y, 1, *olddata,numArray,precision);	//更新现在的数字
	}
}

#define	LL_POS	 		44,19		//流量数据显示位置
#define	TOTOL_POS	 	25,35		//总量数据显示位置

void DataViewMenu(ShowStr* showStr )
{
	u8 i = 0;
	u8 numArray[20] = {0};
	static float  oldMassFlow;
	static float  oldMassTotal;
	static float  oldDspDensity;
	static float  oldVoluFlow;
	static float 	oldVoluTotal;
	static float 	oldDspTemp;
	static float 	oldZ0Delay;
	static float 	oldZ2Delay;
	static float 	oldDspFreq;
	static float 	oldZ1tDelay;
	
	if(showStr->flag_init == NO_INIT)		//初始化
	{
		showStr->flag_init = IS_INIT;
		CUIGUI_SetFont(&GUI_Fontsongti12); 
		flag_inSetMenu = 0;				//3分钟计时停止
		Set_Display_On_Off(0);
		//画字符串
			switch(PageNumber)
			{
				case 0:
					
					ClearLCD();		
					if(showStr->Language == ENGLISH)
					{
						CUIGUI_DrawStr( 2,1,1,"Mass Flow");
						CUIGUI_DrawStr( 2,32,1,"Density");	
					}else
					{
						CUIGUI_DrawStr( 2,2,1,"质量流量:");
						CUIGUI_DrawStr( 2,50,1,"密度");	
					}
					CUIGUI_DrawStr( 86,3,1,arraySetZLCeLiangUnits[rspHoldREGDatBuf.UnitMassFlow]);	//质量流量测量单位
					oldMassFlow = MDint2float(&rspHoldREGDatBuf.MassFlow);
					CUIGUI_DrawDoubleColorNum(44,19, 1,oldMassFlow,numArray,showNature.Resolution_InstantZLLL);	
					
					CUIGUI_DrawStr( 1,36,1,"Σ:");	
					oldMassTotal = MDint2float(&rspHoldREGDatBuf.MassTotal);
					CUIGUI_DrawDoubleColorNum(TOTOL_POS, 1,oldMassTotal,numArray,showNature.Resolution_AddUpZLLL);	
					
					CUIGUI_DrawStr( 86,50,1,arraySetDensityUnits[rspHoldREGDatBuf.UnitDensity]);		
					oldDspDensity = MDint2float(&rspHoldREGDatBuf.DspDensity);
					CUIGUI_DrawDoubleColorNum(30,50, 1,oldDspDensity,numArray,showNature.Resolution_MediumDensity);						
					break;
				case 1: 
					ClearLCD();						
					if(showStr->Language == ENGLISH)
					{
						CUIGUI_DrawStr( 2,1,1,"Mass Flow");
						CUIGUI_DrawStr( 2,32,1,"Density");	
					}else
					{
						CUIGUI_DrawStr( 2,2,1,"体积流量:");
						CUIGUI_DrawStr( 2,50,1,"温度:");	
					}
					CUIGUI_DrawStr( 89,3,1,arraySetTJCeLiangUnits[rspHoldREGDatBuf.UnitVolumeFlow]);	//体积流量单位				
					oldVoluFlow = MDint2float(&rspHoldREGDatBuf.VoluFlow);
					CUIGUI_DrawDoubleColorNum(44,19, 1, oldVoluFlow,numArray,showNature.Resolution_InstantTJLL);	
					
					CUIGUI_DrawStr( 1,36,1,"Σ:");	
					oldVoluTotal = MDint2float(&rspHoldREGDatBuf.VoluTotal);
					CUIGUI_DrawDoubleColorNum(TOTOL_POS, 1, oldVoluTotal,numArray,showNature.Resolution_AddUpTJLL);	
					
					CUIGUI_DrawStr( 89,50,1,arraySetTempUnits[rspHoldREGDatBuf.UnitTemperature]);		//温度单位	
					oldDspTemp = 	MDint2float(&rspHoldREGDatBuf.DspTemp);
					CUIGUI_DrawDoubleColorNum(58,50, 1,oldDspTemp,numArray,1);
					break;
				case 2:  
					ClearLCD();		
					CUIGUI_DrawStr( 1,3,1,"F0:");	
					oldZ0Delay = MDint2float(&rspHoldREGDatBuf.Z0Delay);
					CUIGUI_DrawDoubleColorNum(19,3, 1, oldZ0Delay,numArray,4);	
				
					CUIGUI_DrawStr( 1,20,1,"DP:");
					oldDspFreq = MDint2float(&rspHoldREGDatBuf.DspFreq);
					CUIGUI_DrawDoubleColorNum(19,19, 1, oldDspFreq,numArray,4);	
				
					CUIGUI_DrawStr( 1,36,1,"Z1:");	
					oldZ1tDelay = MDint2float(&rspHoldREGDatBuf.Z1tDelay);
					CUIGUI_DrawDoubleColorNum(19,35, 1, oldZ1tDelay,numArray,4);	
				
					CUIGUI_DrawStr( 1,50,1,"Z2:");	
					oldZ2Delay = MDint2float(&rspHoldREGDatBuf.Z2Delay);
					CUIGUI_DrawDoubleColorNum(19,51, 1, oldZ2Delay,numArray,4);	
					break;	
				default: break;
				
			}
		
		//画边框
		for(i=0;i<64;i++)
		{
			CUIGUI_DrawPoint(0,i,1) ;
			CUIGUI_DrawPoint(127,i,1) ;
		}

		for(i=1;i<127;i++)
		{
			CUIGUI_DrawPoint(i,0,1) ;
			CUIGUI_DrawPoint(i,15,1) ;	
			CUIGUI_DrawPoint(i,31,1) ;			
			CUIGUI_DrawPoint(i,47,1) ;
			CUIGUI_DrawPoint(i,63,1) ;
		}		
		Set_Display_On_Off(1);
	}else
	{
		//已经初始化
		//画字符串
			switch(PageNumber)
			{
				case 0:
					ReviewData(LL_POS,&oldMassFlow,MDint2float(&rspHoldREGDatBuf.MassFlow),numArray,showNature.Resolution_InstantZLLL);				//质量流量
					ReviewData(TOTOL_POS,&oldMassTotal,MDint2float(&rspHoldREGDatBuf.MassTotal),numArray,showNature.Resolution_AddUpZLLL);		//质量流量总量
					ReviewData(30,50,&oldDspDensity,MDint2float(&rspHoldREGDatBuf.DspDensity),numArray,showNature.Resolution_MediumDensity);	//密度				
					break;
				case 1: 			
					ReviewData(LL_POS,&oldVoluFlow,MDint2float(&rspHoldREGDatBuf.VoluFlow),numArray,showNature.Resolution_InstantTJLL);				//体积流量
					ReviewData(TOTOL_POS,&oldVoluTotal,MDint2float(&rspHoldREGDatBuf.VoluTotal),numArray,showNature.Resolution_AddUpTJLL);		//体力流量总量
					ReviewData(58,50,&oldDspTemp,MDint2float(&rspHoldREGDatBuf.DspTemp),numArray,2);																					//温度
					break;
				case 2:  
					ReviewData(19,3,&oldZ0Delay,MDint2float(&rspHoldREGDatBuf.Z0Delay),numArray,4);						
					ReviewData(19,19,&oldDspFreq,MDint2float(&rspHoldREGDatBuf.DspFreq),numArray,4);					
					ReviewData(19,35,&oldZ1tDelay,MDint2float(&rspHoldREGDatBuf.Z1tDelay),numArray,4);					
					ReviewData(19,51,&oldZ2Delay,MDint2float(&rspHoldREGDatBuf.Z2Delay),numArray,4);	
					break;	
				default: break;
				
			}		
		
	}

}


void DataViewKeyScan(ShowStr* showStr)
{
	if(key_val)
	{
		switch(key_val)
		{
			case BUTTON_ENTER_VAL: DEBUG_Log("BUTTON_ENTER_VAL  \r\n");
				if(PageNumber == 0)PageNumber = 2;
				else PageNumber --;
				showStr->flag_init = NO_INIT;
				break;
			case BUTTON_NEXT_VAL: DEBUG_Log("BUTTON_NEXT_VAL  \r\n");

				if(PageNumber++  >=  2) PageNumber=0;
			
				showStr->flag_init = NO_INIT;
			    DEBUG_Log("PageNumber = %x\r\n",PageNumber);
				break;	
			case BUTTON_NEXT_VAL|BUTTON_ENTER_VAL:
				flag_inSetMenu = 1;					//开始计时3分钟
				showStr->flag_init = NO_INIT;
				showStr->thisNature = (NatureStr*)listINTERFACE;
			
				break;				
		}
		key_val = 0;	
	}

}
