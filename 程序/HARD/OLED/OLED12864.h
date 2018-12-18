
#ifndef __OLED12864__H__
#define __OLED12864__H__

#include "UHEAD.h"
#include "spi.h"
#include "stm32f3xx_hal_spi.h"

#define XLevelL		0x00
#define XLevelH		0x10
#define XLevel	    ((XLevelH&0x0F)*16+XLevelL)
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xCF 
#define X_WIDTH 128
#define Y_WIDTH 64

#define	OLED_RES		OLED_RES_GPIO_Port,OLED_RES_Pin

/*延时函数移植*/
#define	LCD_DLY_ms(t)	HAL_Delay(t)

/*GPIO操作移植*/
#define	LCD_DC_1	HAL_GPIO_WritePin(OLED_DC_GPIO_Port,OLED_DC_Pin,GPIO_PIN_SET);
#define	LCD_DC_0	HAL_GPIO_WritePin(OLED_DC_GPIO_Port,OLED_DC_Pin,GPIO_PIN_RESET);

#define	LCD_RST_1	HAL_GPIO_WritePin(OLED_RES_GPIO_Port,OLED_RES_Pin,GPIO_PIN_SET);
#define	LCD_RST_0	HAL_GPIO_WritePin(OLED_RES_GPIO_Port,OLED_RES_Pin,GPIO_PIN_RESET);

#define	OLED_WrDat(d)	HAL_SPI_Transmit(&hspi2,&d,1,2000);	//OLED写数据
#define	OLED_WrCmd(d)	HAL_SPI_Transmit(&hspi2,&d,1,2000);	//OLED写数据

#define	PIAN	0	//偏移，校正


typedef	enum{
	FRAME_5 = 0,
	FRAME_64 = 1,
	FRAME_128 = 2,
	FRAME_256 = 3,
	FRAME_2 = 4,
	FRAME_3 = 5,
	FRAME_4 = 6,
	FRAME_1 = 7,
	
}FRAMES_ENUM;

void LCD_Init(void);
void LCD_DrawWord(unsigned char* x,unsigned char* y,unsigned char ch);
void OLED_Display(const int* pdata, u16 w, u16 h, int posX, int posY);
void LCD_SetContrast(u8 val);//设置对比度
void OLED_DrawPoint(u8 pos_x,u8 pos_y,u8 ison);//ison 是显示0或者1
void OLED_DrawPicture(const u8* pdata, u16 w, u16 h, int posX, int posY);
void OLED_FanBai(int pos_x, int pos_y,u8 height);//在任意一个位置反白一行
void LCD_Fill(unsigned char bmp_dat);
void ClearLCD(void);
void Set_Display_On_Off(unsigned char d);

#endif
