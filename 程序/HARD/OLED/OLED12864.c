
#include "OLED12864.H"
#include "spi.h"

static u8 oledMap[8][128]= {0};	//64,128

void LCD_WrDat(unsigned char dat)	 
{
	LCD_DC_1;
	OLED_WrDat(dat);
	
}
										
void LCD_WrCmd(unsigned char cmd)
{
	LCD_DC_0;	
 	OLED_WrCmd(cmd);
	
}

void LCD_Set_Pos(unsigned char x, unsigned char y) 
{ 
	LCD_WrCmd(0xb0+y);
	LCD_WrCmd(((x&0xf0)>>4)|0x10);
	LCD_WrCmd((x&0x0f)|0x00); 
} 


void LCD_Fill(unsigned char bmp_dat) 
{
	unsigned char y,x;
	for(y=0;y<8;y++)
	{
		LCD_WrCmd(0xb0+y);
		LCD_WrCmd(0x01);
		LCD_WrCmd(0x10);
		for(x=0;x<X_WIDTH;x++)
			LCD_WrDat(bmp_dat);
	}
	
	
}

//调节对比度
void LCD_SetContrast(u8 val)
{
	LCD_WrCmd(0x81);
	LCD_WrCmd(val);
}



//水平滚动
//0x26 向右滚，0x27向左滚
//startpage:0~7
//frame 滚动帧
//endpage:0~7
//startColumn:开始列

void LCD_ScrollHorizontal(u8 startpage,FRAMES_ENUM frame,u8 endpage,u8 startColumn,u8 endColumn)
{
	LCD_WrCmd(0x2e);
	LCD_WrCmd(0x27);
	LCD_WrCmd(0);
	LCD_WrCmd(startpage);
	LCD_WrCmd(frame);
	LCD_WrCmd(endpage);
	LCD_WrCmd(0);
	LCD_WrCmd(startColumn);
	LCD_WrCmd(endColumn);
	LCD_WrCmd(0x2f);
}
//void Set_Start_Column(unsigned char d)
//{
//	LCD_WrCmd(0x00+d%16);		// Set Lower Column Start Address for Page Addressing Mode
//						//   Default => 0x00
//	LCD_WrCmd(0x10+d/16);		// Set Higher Column Start Address for Page Addressing Mode
//						//   Default => 0x10
//}


//void Set_Addressing_Mode(unsigned char d)
//{
//	LCD_WrCmd(0x20);			// Set Memory Addressing Mode
//	LCD_WrCmd(d);			//   Default => 0x02
//						//     0x00 => Horizontal Addressing Mode
//						//     0x01 => Vertical Addressing Mode
//						//     0x02 => Page Addressing Mode
//}


//void Set_Column_Address(unsigned char a, unsigned char b)
//{
//	LCD_WrCmd(0x21);			// Set Column Address
//	LCD_WrCmd(a);			//   Default => 0x00 (Column Start Address)
//	LCD_WrCmd(b);			//   Default => 0x7F (Column End Address)
//}


//void Set_Page_Address(unsigned char a, unsigned char b)
//{
//	LCD_WrCmd(0x22);			// Set Page Address
//	LCD_WrCmd(a);			//   Default => 0x00 (Page Start Address)
//	LCD_WrCmd(b);			//   Default => 0x07 (Page End Address)
//}


//void Set_Start_Line(unsigned char d)
//{
//	LCD_WrCmd(0x40|d);			// Set Display Start Line
//						//   Default => 0x40 (0x00)
//}


//void Set_Contrast_Control(unsigned char d)
//{
//	LCD_WrCmd(0x81);			// Set Contrast Control for Bank 0
//	LCD_WrCmd(d);			//   Default => 0x7F
//}


//void Set_Segment_Remap(unsigned char d)
//{
//	LCD_WrCmd(d);			// Set Segment Re-Map
//						//   Default => 0xA0
//						//     0xA0 => Column Address 0 Mapped to SEG0
//						//     0xA1 => Column Address 0 Mapped to SEG127
//}


//void Set_Entire_Display(unsigned char d)
//{
//	LCD_WrCmd(d);			// Set Entire Display On / Off
//						//   Default => 0xA4
//						//     0xA4 => Normal Display
//						//     0xA5 => Entire Display On
//}


//void Set_Inverse_Display(unsigned char d)
//{
//	LCD_WrCmd(d);			// Set Inverse Display On/Off
//						//   Default => 0xA6
//						//     0xA6 => Normal Display
//						//     0xA7 => Inverse Display On
//}


//void Set_Multiplex_Ratio(unsigned char d)
//{
//	LCD_WrCmd(0xA8);			// Set Multiplex Ratio
//	LCD_WrCmd(d);			//   Default => 0x3F (1/64 Duty)
//}

//void Set_Command_Lock(unsigned char d)
//{
//	LCD_WrCmd(0xFD);			// Set Command Lock
//	LCD_WrDat(d);				//   Default => 0x12
//						//     0x12 => Driver IC interface is unlocked from entering command.
//						//     0x16 => All Commands are locked except 0xFD.
//}

//void Set_Display_On_Off(unsigned char d)	
//{
//	LCD_WrCmd(d);			// Set Display On/Off
//						//   Default => 0xAE
//						//     0xAE => Display Off
//						//     0xAF => Display On
//}
//void Set_Display_Clock(unsigned char d)
//{
//	LCD_WrCmd(0xD5);			// Set Display Clock Divide Ratio / Oscillator Frequency
//	LCD_WrCmd(d);			//   Default => 0x70
//						//     D[3:0] => Display Clock Divider
//						//     D[7:4] => Oscillator Frequency
//}

//void Set_Precharge_Period(unsigned char d)
//{
//	LCD_WrCmd(0xD9);			// Set Pre-Charge Period
//	LCD_WrCmd(d);			//   Default => 0x22 (2 Display Clocks [Phase 2] / 2 Display Clocks [Phase 1])
//						//     D[3:0] => Phase 1 Period in 1~15 Display Clocks
//						//     D[7:4] => Phase 2 Period in 1~15 Display Clocks
//}


//void Set_Common_Config(unsigned char d)
//{
//	LCD_WrCmd(0xDA);			// Set COM Pins Hardware Configuration
//	LCD_WrCmd(d);			//   Default => 0x12
//						//     Alternative COM Pin Configuration
//						//     Disable COM Left/Right Re-Map
//}


//void Set_VCOMH(unsigned char d)
//{
//	LCD_WrCmd(0xDB);			// Set VCOMH Deselect Level
//	LCD_WrCmd(d);			//   Default => 0x34 (0.78*VCC)
//}


//void Set_NOP()
//{
//	LCD_WrCmd(0xE3);			// Command for No Operation
//}


//void Set_Display_Offset(unsigned char d)
//{
//	LCD_WrCmd(0xD3);			// Set Display Offset
//	LCD_WrCmd(d);			//   Default => 0x00
//}

//void Set_Common_Remap(unsigned char d)
//{
//	LCD_WrCmd(d);			// Set COM Output Scan Direction
//						//   Default => 0xC0
//						//     0xC0 => Scan from COM0 to 63
//						//     0xC8 => Scan from COM63 to 0
//}

void LCD_Init(void)     
{  
	LCD_DLY_ms(100);
	LCD_RST_0;
	LCD_DLY_ms(200);
	LCD_RST_1;
	
	LCD_WrCmd(0xae);
	LCD_WrCmd(0x00);
	LCD_WrCmd(0x10);
	LCD_WrCmd(0x40);
	LCD_WrCmd(0x81);
	LCD_WrCmd(0xcf); 
	LCD_WrCmd(0xa1);
	LCD_WrCmd(0xc8);
	LCD_WrCmd(0xa6);
	LCD_WrCmd(0xa8);
	LCD_WrCmd(0x3f);
	LCD_WrCmd(0xd3);
	LCD_WrCmd(0x00);
	LCD_WrCmd(0xd5);
	LCD_WrCmd(0x80);
	LCD_WrCmd(0xd9);
	LCD_WrCmd(0xf1);
	LCD_WrCmd(0xda);
	LCD_WrCmd(0x12);
	LCD_WrCmd(0xdb);
	LCD_WrCmd(0x40);
	LCD_WrCmd(0x20);
	LCD_WrCmd(0x02);
	LCD_WrCmd(0x8d);
	LCD_WrCmd(0x14);
	LCD_WrCmd(0xa4);
	LCD_WrCmd(0xa6); 
	LCD_WrCmd(0xaf);
	
    LCD_SetContrast(0xff);
	LCD_Fill(0x00);  
	LCD_Set_Pos(0,0); 

//	Set_Command_Lock(0x12);			// Unlock Driver IC (0x12/0x16)
//	Set_Display_On_Off(0xAE);		// Display Off (0xAE/0xAF)
//	Set_Display_Clock(0xA0);		// Set Clock as 116 Frames/Sec
//	Set_Multiplex_Ratio(0x3F);		// 1/64 Duty (0x0F~0x3F)
//	Set_Display_Offset(0x00);		// Shift Mapping RAM Counter (0x00~0x3F)
//	Set_Start_Line(0x00);			// Set Mapping RAM Display Start Line (0x00~0x3F)
//	Set_Addressing_Mode(0x02);		// Set Page Addressing Mode (0x00/0x01/0x02)
//	Set_Segment_Remap(0xA1);		// Set SEG/Column Mapping (0xA0/0xA1)
//	Set_Common_Remap(0xC8);			// Set COM/Row Scan Direction (0xC0/0xC8)
//	Set_Common_Config(0x12);		// Set Alternative Configuration (0x02/0x12)
//	Set_Contrast_Control(Brightness);	// Set SEG Output Current
//	Set_Precharge_Period(0x25);		// Set Pre-Charge as 2 Clocks & Discharge as 5 Clocks
//	Set_VCOMH(0x34);			// Set VCOM Deselect Level
//	Set_Entire_Display(0xA4);		// Disable Entire Display On (0xA4/0xA5)
//	Set_Inverse_Display(0xA6);		// Disable Inverse Display On (0xA6/0xA7)

//	LCD_Fill(0x00);  				// Clear Screen

//	Set_Display_On_Off(0xAF);		// Display On (0xAE/0xAF)

//	LCD_RST_0;   //  RES = 0; 
//	LCD_DLY_ms(50);	 
//	LCD_RST_1;   // RES = 1;
//	LCD_DLY_ms(100);
//	
//#define	transfer_command	LCD_WrCmd

//	transfer_command(0xFD);	//Command Lock  ( SSD1309 use, SSD1305 no use )
//	transfer_command(0x12);	// Unlock Driver IC (0x12/0x16)	   

//	transfer_command(0xAE);	// Set Display Off

//	transfer_command(0xD5);	 //Set Display Clock Divide Ratio/Oscillator Frequency
//	transfer_command(0x90);	 //	 1305:0x60~0x90(324~396KHz)	   1309: 0x70~0xd0(360~540KHz)

//	transfer_command(0xA8);	//Set Multiplex Ratio 
//	transfer_command(0x3F);	// 

//	transfer_command(0xD3);	//Set Display Offset
//	transfer_command(0x00);	// 

//	transfer_command(0x40);	// Set Display Start Line

//  transfer_command(0xA1);	// Set SEG/Column Mapping (0xA0/0xA1)
//	transfer_command(0xC8);	// Set COM/Row Scan Direction (0xC0/0xC8)

//	transfer_command(0xDA);	//Set COM Pins Hardware Configuration
//	transfer_command(0x12);	// Set Alternative Configuration (0x02/0x12)
//	
//	transfer_command(0x81);	//Set Current Control 
//  transfer_command(0xDF);  // 
//	
//	transfer_command(0xD9);	//Set Pre-Charge Period 
//	transfer_command(0x82);	// 

//	transfer_command(0xDB);	//Set VCOMH Deselect Level
//	transfer_command(0);	// 

//	transfer_command(0xA4);	// Set Entire Display On/Off (0xA4/0xA5)
//	transfer_command(0xA6);	// Set Normal/Inverse Display (0xA6/0xA7)

//	LCD_Fill(0x00);  //清屏
//	LCD_DLY_ms(2);

//	transfer_command(0xAF);		//Set Display On

} 

//打点函数
//posY--页,posX列,w宽度,h高度
void OLED_Display(const int* pdata, u16 w, u16 h, int posX, int posY)
{
	 u16 i = 0,j = 0;
     LCD_Set_Pos(posX+PIAN,posY);
     w = (w+1)/2;
     h = (h +7)/8;
     
     for(j=0;j<h;j++)
    {
        for(i=0;i<w;i++)
        {
            LCD_WrDat(pdata[j*w+i]);
        }
        posY ++;
        LCD_Set_Pos(posX+PIAN,posY);
    }    

}

//ison 是显示0或者1
void OLED_DrawPoint(u8 pos_x,u8 pos_y,u8 ison)
{

	u8 byte = 0;
	if(pos_x>127 || pos_y>63) return ;
	byte = pos_y&7;				//获取在二维字节中的位置
	byte = 0x01 << (byte);
	pos_y /= 8;					//获取数组的二维位置
	if(ison) oledMap[pos_y][pos_x] |= byte;
	else oledMap[pos_y][pos_x] &= ~byte;	
	LCD_Set_Pos(pos_x,pos_y);  
	LCD_WrDat(oledMap[pos_y][pos_x]);
}

////竖向画点
//void Draw_V(u8 pdata, int posX,int posY,u8 length)
//{
//	u8 date = pdata;
//	while(length--)
//	{
//		if(date & 0x01)
//		OLED_DrawPoint(posX,posY,1);
//		else OLED_DrawPoint(posX,posY,0);
//		(posY) ++;
//		date >>= 1;
//	}
//}

void fan_bai(int pos_x, int pos_y,u8 dat)
{
	pos_y /= 8;				//获取在二维字节中的位置
	dat ^= oledMap[pos_y][pos_x];
	LCD_Set_Pos(pos_x,pos_y);  
	LCD_WrDat(dat);
}
//在任意一个位置反白一行
void OLED_FanBai(int pos_x, int pos_y,u8 height)
{
//	u8 byte = 0;
//	u8 h = 0;
//	u8 i = 0;
//	if(pos_x>127 || pos_y>63) return ;
//	h = pos_y&7;				//获取在二维字节中的位置
//	byte = 0xff << h;

//	for(i=0;i<128;i++)
//	{
//		fan_bai(i,pos_y,byte);
//	}
//	height -= (8-h);
//	pos_y += (8-h);
//	while(height>=8)
//	{
//		for(i=0;i<128;i++)
//		{
//			fan_bai(i,pos_y,0xff);
//		}
//		height -= (8-h);	
//	}
//	byte = 0xff << height;
//	LCD_Set_Pos(pos_x,pos_y);  
//	LCD_WrDat(oledMap[pos_y][pos_x]);
}

void ClearLCD(void)
{
	u8 i = 0;
	u8 j = 0;
	LCD_Fill(0x00);
	//LCD_Set_Pos(0,0); 
	for(i=0;i<8;i++)
	{
		for(j=0;j<128;j++)
		{
			oledMap[i][j] = 0;
		}
	}
}
void Set_Display_On_Off(unsigned char d)	
{
	if(d)
	LCD_WrCmd(0xAF);			// Set Display On/Off
		else					//   Default => 0xAE
	LCD_WrCmd(0xAE);			//     0xAE => Display Off
								//     0xAF => Display On
}
