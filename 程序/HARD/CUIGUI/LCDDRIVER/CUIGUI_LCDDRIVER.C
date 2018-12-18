#include "CUIGUI_LCDDRIVER.H"

/*********************************************************

      添加LCD驱动
*/
#include "OLED12864.H"

/************************************************************************************
*-函数名称	：初始化LCD
*-参数	：
*返回值	：
*-函数功能	：
*-创建者	：蓬莱市博硕电子科技
*/

void CUIGUI_Init(void) 
{    
    LCD_Init();
}

/************************************************************************************
*-函数名称	：画点
*-参数	：
*返回值	：
*-函数功能	：
*-创建者	：蓬莱市博硕电子科技
*/

void CUIGUI_DrawPoint(u16 x, u16 y, COLOR_DATTYPE color) 
{
   OLED_DrawPoint(x,y,color);
}


/************************************************************************************
*-函数名称	  ：画横线
*-参数		  ：
*返回值		  ：
*-函数功能	  ：
*-创建者		  ：蓬莱市博硕电子科技
*/
void CUIGUI_DrawHLine(u16 x0,u16 y,u16 x1,COLOR_DATTYPE color)
{
      u16 i ;
      for(i=x0;i<x1;i++)
      {
        CUIGUI_DrawPoint(i,y,color);//画点
      }
}


/************************************************************************************
*-函数名称	  ：填充矩形区域
*-参数		  ：
*返回值		  ：
*-函数功能	  ：
*-创建者		  ：蓬莱市博硕电子科技
*/
void CUIGUI_FillRect(u16 x0, u16 y0, u16 width, u16 height,COLOR_DATTYPE color)
{
	u16 i;
 	for(i=0;i<height;i++)
	{
            CUIGUI_DrawHLine(x0,y0+i,x0+width,color);
	}   
}

    
/************************************************************************************
*-函数名称	  ：画竖线
*-参数		  ：
*返回值		  ：
*-函数功能	  ：
*-创建者		  ：蓬莱市博硕电子科技
*/
void CUIGUI_DrawVLine(u16 x,u16 y0,u16 y1,COLOR_DATTYPE color) 
{
    u16 i ;
    for(i=y0;i<y1;i++)
    {
        CUIGUI_DrawPoint(x,i,color);//画点 
    }
}

//获取LCD的长度
u16 GetLCDWidth(void)
{
	return 128;
}
