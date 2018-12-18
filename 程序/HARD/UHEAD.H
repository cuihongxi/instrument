#ifndef	__UHEAD_H
#define	__UHEAD_H

#include "stm32f3xx_hal.h"
#include "stm32f3xx_hal_gpio.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"


#define			GETSIZE(x)		(sizeof(x)/sizeof(x[0]))			//获得数组大小
#define			malloc(a)		pvPortMalloc(a)
#define			free(a)			vPortFree(a)

typedef	unsigned char 	u8;
typedef	unsigned short 	u16;
typedef	unsigned int 	u32;

typedef unsigned short	WCHAR;
typedef unsigned int	UINT;
typedef unsigned char   BYTE;

#define GUI_CONST_STORAGE   const

typedef enum {NO = 0, YES = !RESET} GUIFlagStatus;
typedef enum {ISOK = 0, ISERROR = 1} Flag_Status;

typedef struct
{
    u8 x;         //宽度
    u8 y;         //高度
    u8 size;      //占用字节数
 const  unsigned char* acGUI_Font;
}GUI_CHARINFO;

typedef struct GUI_FONT_PROP
{
   u16 fc; /* first character */
  u16 lc; /* last character  */
 const GUI_CHARINFO* afc; /* address of first character */
 const struct  GUI_FONT_PROP* pNext;  /* pointer to next GUI_FONT_PROP */
}GUI_FONT_PROP;      
typedef struct 
{
   u8    type ;             /* type of font    */
   u8    height ;           /* height of font  */
   u8    space;             /* space of font y */
   u8    magnification_x ;  /* magnification x */
   u8    magnification_y;   /* magnification y */
   const  GUI_FONT_PROP*  prop;
   u8 bl;                   /* Baseline */
   u8 hl;                   /* Height of lowercase characters */
   u8 hc;                   /* Height of capital characters */
}GUI_FONT;

typedef struct
	{
		u8 FunNum;				//命令
		u8 dev_addr;			//从机地址
		u16 startAddr;		//启始地址
		u16 datnum;				//数量
		u8 task;					//任务
	}reqQueueStr;
	
#define     DEBUG_LEVEL   0        

#if (DEBUG_LEVEL > 0)
#include "stdio.h"
#define  DEBUG_Log(...) printf(__VA_ARGS__);
#else
#define DEBUG_Log(...)   
#endif 

//信号引脚
#define			GPIO_SET(pin)												HAL_GPIO_WritePin(pin##_GPIO_Port,  pin##_Pin,GPIO_PIN_SET)
#define			GPIO_RESET(pin)											HAL_GPIO_WritePin(pin##_GPIO_Port,  pin##_Pin,GPIO_PIN_RESET)


#endif
