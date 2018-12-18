#ifndef  __CUIGUI_LCDDRIVER_H   
#define  __CUIGUI_LCDDRIVER_H 

#include "UHEAD.H"
#include "CUIGUI_CONFIG.H"
/*********************************************************
函数
*/

void            CUIGUI_Init(void);                                      //初始化
void            CUIGUI_DrawPoint(u16 x, u16 y, COLOR_DATTYPE color);    //画点
void            CUIGUI_DrawHLine(u16 x0,u16 y,u16 x1,COLOR_DATTYPE color); 
void            CUIGUI_DrawVLine(u16 x,u16 y0,u16 y1,COLOR_DATTYPE color);
void            CUIGUI_FillRect(u16 x0, u16 y0, u16 width, u16 height,COLOR_DATTYPE color);

u16 			GetLCDWidth(void);										//获取LCD的宽度

#endif
