#include "GUI.H"
#include "CUIGUI_LCDDRIVER.H"
//#include "stdio.h"

const GUI_FONT* cuigui_Font;  //定义全局变量
      //用到的字
      //用到的字
static const WCHAR Array[2][213] = {
//GBK码
{
0xA1CC ,0xA1C1 ,0xA6B2 ,0xA1E6 ,0xD6CA ,0xC1BF ,0xC1F7 ,0xB2E2 ,0xB5A5 ,0xCEBB ,
0xCCE5 ,0xBBFD ,0xD6B5 ,0xBCC6 ,0xC0DB ,0xD5F1 ,0xB9DC ,0xB9A4 ,0xD7F7 ,0xC6B5 ,
0xC2CA ,0xC3DC ,0xB6C8 ,0xCEC2 ,0xC5A8 ,0xCFE0 ,0xCEBB ,0xB2EE ,0xC1E3 ,0xB5E3 ,
0xB5F7 ,0xD5FB ,0xB6AF ,0xCCAC ,0xC7FD ,0xB7F9 ,0xD4F6 ,0xD2E6 ,0xC1AC ,0xD0F8 ,
0xCAB1 ,0xBCE4 ,0xCDCB ,0xB3F6 ,0xD6F7 ,0xB2CB ,0xB1A8 ,0xBEAF ,0xCCE1 ,0xCABE ,
0xD0C5 ,0xCFA2 ,0xC9E8 ,0xB1B8 ,0xCEAC ,0xBBA4 ,0xCFD4 ,0xCABE ,0xCAE4 ,0xC8EB ,
0xBBF9 ,0xB1BE ,0xB9A6 ,0xC4DC ,0xC4DA ,0xB2BF ,0xB7B5 ,0xBBD8 ,0xD2AA ,0xB1E4 ,
0xD6C3 ,0xC8DD ,0xBFAA ,0xC6F4 ,0xD7E9 ,0xB7BD ,0xCABD ,0xD0C5 ,0xBAC5 ,0xC0EB ,
0xC9A2 ,0xC2F6 ,0xB3E5 ,0xB6CB ,0xBFDA ,0xB5E7 ,0xC9CF ,0xD2BB ,0xBCB6 ,0xC0E0 ,
0xD0CD ,0xC3BB ,0xD3D0 ,0xCAB9 ,0xD3C3 ,0xC5E4 ,0xB7C2 ,0xD5E6 ,0xD7B4 ,0xB7D6 ,
0xBFED ,0xC4A3 ,0xB9CA ,0xD5CF ,0xB0B2 ,0xC8AB ,0xCAB5 ,0xBCCA ,0xB2BB ,0xD0DE ,
0xD5FD ,0xCFF2 ,0xCBAB ,0xB7B4 ,0xB2B9 ,0xB3A5 ,0xB1A3 ,0xB3D6 ,0xB9D8 ,0xB1D5 ,
0xCAFD ,0xC4BF ,0xB1EA ,0xB2CE ,0xBFBC ,0xB3A3 ,0xBAF3 ,0xCCD8 ,0xCAE2 ,0xBFAA ,
0xC6F4 ,0xB5B1 ,0xC7B0 ,0xCFDE ,0xD6C6 ,0xD1D3 ,0xBBD6 ,0xB8B4 ,0xC7E5 ,0xC1E3 ,
0xD0A3 ,0xD7BC ,0xB7A7 ,0xCFB5 ,0xCDB3 ,0xCFDF ,0xD0D4 ,0xB4D3 ,0xBBFA ,0xB5D8 ,
0xD6B7 ,0xB2A8 ,0xCCD8 ,0xC6E6 ,0xC5BC ,0xD1E9 ,0xD0B4 ,0xBBA4 ,0xBACF ,0xCDA3 ,
0xD6B9 ,0xD6F7 ,0xBCD3 ,0xC6F7 ,0xA1FD ,0xCDCB ,0xB3F6 ,0xB0B4 ,0xBCFC ,0xB3AC ,
0xC8A8 ,0xD2C7 ,0xB1ED ,0xB3CC ,0xC2EB ,0xC6E4 ,0xCBFB ,0xBFD8 ,0xCBD9 ,0xB8F1 ,
0xD1A1 ,0xD4F1 ,0xD0CE ,0xD0A7 ,0xB8A8 ,0xD6FA ,0xD3EF ,0xD1D4 ,0xD0A1 ,0xC7D0 ,
0xB3FD ,0xD7D4 ,0xBBA7 ,0xCFC2 ,0xD6D0 ,0xCEC4 ,0xCAC7 ,0xB7F1 ,0xD0B1 ,0xD7E8 ,
0xC4E1 ,0xD1B9 ,0xC1A6 ,0xCBB2 ,0xBDE9 ,0xB1E6 ,0xC4AC ,0xC8CF ,0xBDE7 ,0xC3E6 ,
0xCDA8 ,0xD1B6 
},
//UNICODE码
{
0x221A ,0x00D7 ,0x03A3 ,0x2103 ,0x8D28 ,0x91CF ,0x6D41 ,0x6D4B ,0x5355 ,0x4F4D ,
0x4F53 ,0x79EF ,0x503C ,0x8BA1 ,0x7D2F ,0x632F ,0x7BA1 ,0x5DE5 ,0x4F5C ,0x9891 ,
0x7387 ,0x5BC6 ,0x5EA6 ,0x6E29 ,0x6D53 ,0x76F8 ,0x4F4D ,0x5DEE ,0x96F6 ,0x70B9 ,
0x8C03 ,0x6574 ,0x52A8 ,0x6001 ,0x9A71 ,0x5E45 ,0x589E ,0x76CA ,0x8FDE ,0x7EED ,
0x65F6 ,0x95F4 ,0x9000 ,0x51FA ,0x4E3B ,0x83DC ,0x62A5 ,0x8B66 ,0x63D0 ,0x793A ,
0x4FE1 ,0x606F ,0x8BBE ,0x5907 ,0x7EF4 ,0x62A4 ,0x663E ,0x793A ,0x8F93 ,0x5165 ,
0x57FA ,0x672C ,0x529F ,0x80FD ,0x5185 ,0x90E8 ,0x8FD4 ,0x56DE ,0x8981 ,0x53D8 ,
0x7F6E ,0x5BB9 ,0x5F00 ,0x542F ,0x7EC4 ,0x65B9 ,0x5F0F ,0x4FE1 ,0x53F7 ,0x79BB ,
0x6563 ,0x8109 ,0x51B2 ,0x7AEF ,0x53E3 ,0x7535 ,0x4E0A ,0x4E00 ,0x7EA7 ,0x7C7B ,
0x578B ,0x6CA1 ,0x6709 ,0x4F7F ,0x7528 ,0x914D ,0x4EFF ,0x771F ,0x72B6 ,0x5206 ,
0x5BBD ,0x6A21 ,0x6545 ,0x969C ,0x5B89 ,0x5168 ,0x5B9E ,0x9645 ,0x4E0D ,0x4FEE ,
0x6B63 ,0x5411 ,0x53CC ,0x53CD ,0x8865 ,0x507F ,0x4FDD ,0x6301 ,0x5173 ,0x95ED ,
0x6570 ,0x76EE ,0x6807 ,0x53C2 ,0x8003 ,0x5E38 ,0x540E ,0x7279 ,0x6B8A ,0x5F00 ,
0x542F ,0x5F53 ,0x524D ,0x9650 ,0x5236 ,0x5EF6 ,0x6062 ,0x590D ,0x6E05 ,0x96F6 ,
0x6821 ,0x51C6 ,0x9600 ,0x7CFB ,0x7EDF ,0x7EBF ,0x6027 ,0x4ECE ,0x673A ,0x5730 ,
0x5740 ,0x6CE2 ,0x7279 ,0x5947 ,0x5076 ,0x9A8C ,0x5199 ,0x62A4 ,0x5408 ,0x505C ,
0x6B62 ,0x4E3B ,0x52A0 ,0x5668 ,0x2193 ,0x9000 ,0x51FA ,0x6309 ,0x952E ,0x8D85 ,
0x6743 ,0x4EEA ,0x8868 ,0x7A0B ,0x7801 ,0x5176 ,0x4ED6 ,0x63A7 ,0x901F ,0x683C ,
0x9009 ,0x62E9 ,0x5F62 ,0x6548 ,0x8F85 ,0x52A9 ,0x8BED ,0x8A00 ,0x5C0F ,0x5207 ,
0x9664 ,0x81EA ,0x6237 ,0x4E0B ,0x4E2D ,0x6587 ,0x662F ,0x5426 ,0x659C ,0x963B ,
0x5C3C ,0x538B ,0x529B ,0x77AC ,0x4ECB ,0x8FA8 ,0x9ED8 ,0x8BA4 ,0x754C ,0x9762 ,
0x901A ,0x8BAF 
},
                  
      };
/************************************************************************************
*-函数名称	：设定字体
*-参数	：
*返回值	：
*-函数功能	：
*-创建者	：蓬莱市博硕电子科技
*/

void CUIGUI_SetFont(const GUI_FONT* GUI_FontNum)
{
    cuigui_Font = GUI_FontNum;
}

/************************************************************************************
*-函数名称	：获得字体
*-参数	：
*返回值	：
*-函数功能	：
*-创建者	：蓬莱市博硕电子科技
*/

const GUI_FONT* CUIGUI_GetFont(void)                 //获取当前字体
{
      return cuigui_Font;
}


//根据GBK码返回在数组中的位置,根据数组中的位置返回UNICODE码
WCHAR GBK2UNICODE(WCHAR word)
{

   u16 i = 0;
    while((word != Array[0][i]) &&(i<sizeof(Array)/sizeof(WCHAR)))  
    {
      i++;
    }  
     FONT_Log("\r\n find! i= %d",i);
      if(i>=sizeof(Array)/sizeof(WCHAR)) return 0x0020;//没找到返回空格
    else return Array[1][i];
      
}



/************************************************************************************
*-函数名称	：自定义 获得UNICODE码
*-参数	：
*返回值	：
*-函数功能	：
*-创建者	：蓬莱市博硕电子科技
*/
WCHAR GetUnicode(WCHAR word)
{
      return GBK2UNICODE(word);
}

/************************************************************************************
*-函数名称	：输出一个宽度为w，高度为h的字模到屏幕的 (x,y) 坐标出，文字的颜色为 color，
*-参数			：文字的点阵数据为 p_data 所指
*返回值			：color = 0:反白显示, = 1:正常打点; =2 :清空显示 >2 :与底相与显示
*-函数功能	：
*-创建者	：蓬莱市博硕电子科技
*/

void  _draw_model(const u8 *p_data, int w, int h, int x, int y, COLOR_DATTYPE color)
{
		int     i;    /* 控制行 */
    int     j;    /* 控制一行中的8个点 */
    int     k;    /* 一行中的第几个“8个点”了 */
    int     nc;   /* 到点阵数据的第几个字节了 */
    int     cols; /* 控制列 */
    w  = (w + 7) / 8 * 8;  /* 重新计算w */
    nc = 0;
    for (i=0; i<h; i++)
        {
        cols = 0;
        for (k=0; k<w/8; k++)
            {
            for (j=0; j<8; j++)
                {
									if(color<2)
									{
											if (p_data[nc]&(0x80>>j)) CUIGUI_DrawPoint(x+cols, y+i, color);
											else CUIGUI_DrawPoint(x+cols, y+i,!color);
									}else if(color == 2)
									{
											if (p_data[nc]&(0x80>>j)) CUIGUI_DrawPoint(x+cols, y+i, 0);
									}else
									{
											if (p_data[nc]&(0x80>>j)) CUIGUI_DrawPoint(x+cols, y+i, color);
									}

									cols++;
                }
            nc++;
            }
        }
}


/************************************************************************************
*-函数名称	：打印一个字符
*-参数	：
*返回值	：返回字宽度
*-函数功能	：
*-创建者	：蓬莱市博硕电子科技
*/

u16 CUIGUI_DrawWord( int x, int y, COLOR_DATTYPE color,const char* word)
{
      u16 w;        //宽
      u16 h;        //高  
      WCHAR dat;   
      const GUI_FONT_PROP*   prop;  
      prop = cuigui_Font->prop;          
   
      if((u8)*word>127)
      {
            dat = (WCHAR)((u16)*word<<8 | (*((u16*)word)>>8));
           // printf("\r\n dat0 = %x",dat);            
#if  CUIGUI_FONT936 > 0            
            
            dat =  ff_convert(dat);               
#else                  
            dat = GetUnicode(dat);  
           // printf("\r\n dat_unicode = %x",dat);
#endif             
      }else      dat = *word;
	  FONT_Log("\r\n dat = %d",dat);
    while((dat< prop->fc || dat> prop->lc) && (prop->pNext != 0))
    {
        prop = prop->pNext;
    }
      w = (prop->afc+(dat- prop->fc))->x;            	//获得宽度
		
      h = cuigui_Font->height;                  		//获得高度
      FONT_Log("\r\n w0 = %d , h = %d",w,h);
    
    _draw_model((prop->afc+(dat-prop->fc))->acGUI_Font ,w,h,x,y,color);
    
    return w;      
}




/************************************************************************************
*-函数名称	：打印一个字符串
*-参数	：
*返回值	：返回最后位置
*-函数功能	：
*-创建者	：蓬莱市博硕电子科技
*/

u16 CUIGUI_DrawStr( int x, int y, COLOR_DATTYPE color,const char* str)
{
      u16 w;   
      while(*str != 0)
      { 
          w = CUIGUI_DrawWord(x,y,color,str); 

          if((u8)*str>127)
          {
                 str += 2; 
                
          }else //ASCII码
           
            {              
                str ++;  
            }            
            x += w;
      }
      return (u16)x;
}


//获得一个字符的宽度
u16 GetWordWidth(const char* word)
{
      u16 w;        //宽  
      WCHAR dat;   
      const GUI_FONT_PROP*   prop;  
      prop = cuigui_Font->prop;             
      if((u8)*word>127)
      {
            dat = (WCHAR)((u16)*word<<8 | (*((u16*)word)>>8));
           // printf("\r\n dat0 = %x",dat);            
#if  CUIGUI_FONT936 > 0            
            
            dat =  ff_convert(dat);               
#else                  
            dat = GetUnicode(dat);  
           // printf("\r\n dat_unicode = %x",dat);
#endif             
      }else      dat = *word;
    while((dat< prop->fc || dat> prop->lc) && (prop->pNext != 0))
    {
        prop = prop->pNext;
    }
      w = (prop->afc+(dat- prop->fc))->x;            	//获得宽度
    return w;   
}
/************************************************************************************
*-函数名称	：
*-参数	：
*返回值	：
*-函数功能	：获得字符串长度
*-创建者	：博硕电子科技，www.explorersoftware.taobao.com
*/

u16 GetLengthStr(const char* str)
{
    u16 length =0;      
      while(*str != 0)
      {
             
          length += GetWordWidth(str);            //获得宽度; 
          


          if(*str>127)
          {
                 str += 2; 
                
          }else //ASCII码
          
            {
              
                str ++;  
            }            
  
      }
      return length;
}

/************************************************************************************
*-函数名称	：获取一个字体的高度
*-参数	：
*返回值	：
*-函数功能	：
*-创建者	：蓬莱市博硕电子科技
*/
u16 GetHeightFont(const GUI_FONT* font)
{
      return (font->height);
}


 /******************************************************************
 - 功能描述：将一个32位的变量dat转为字符串，比如把1234转为"1234"
 - 参数说明：dat:带转的long型的变量
             str:指向字符数组的指针，转换后的字节串放在其中   
				width 显示占宽
 - 返回说明：无
 ******************************************************************/

void u32tostr(unsigned long dat,char *str,u16 width)
{
	 unsigned char  temp[11]={0};
	 unsigned char  i=0,j=0;

	 while(dat)
	 {
		temp[i]=dat%10+0x30;
		i++;
		dat/=10;
	 }
	 if(i > width) i = width;
	 j=i;
	 for(i=0;i<j;i++)
	 {
		str[i]=temp[j-i-1];
	 }
	 
	 if(i < width)
	 while(i < width) {str[i++]=' ';}
	 str[width]=0;
}



//double类型转换成ASCII码存到数组中保存正值的函数
//precision 表示小数点后面几位
void DoubletoStringSaveZheng(unsigned char* resultArray0,float dat,u8 precision)
{
	  u8 i=0; 
    u32 power = 0;  		//	权
    u32 dat0 =0;
		u32 POWER = 1;		//10000权
		u8 j = 0 ;
		for(i = 0;i < precision; i++)
		{
			POWER *= 10;
		}
		for(power = POWER;power>=10;power /= 10)
		{
			j ++;  //权的位数
		}
			dat0 = dat;
			for( power=1;dat0>=10;dat0/=10)  
							power*=10;  
			dat0 = dat;
			for(i=0;power>0;power/=10)  
			{  
						resultArray0[i] = '0'+dat0/power; 			
						dat0%=power;  
						i++;
			}           
        dat0 = dat;
        power = 0;
      //存小数部分		
			dat0 = POWER*(dat-dat0);
			power = POWER;			
			 if(dat0>0)
			 {						
				 resultArray0[i] = '.';
				 i++; 
				 power/=10;
					for(;power>0;power/=10)  
					{  
								resultArray0[i] = '0'+dat0/power;							
								dat0 %= power;  
								i++;
					}
					resultArray0[i] = '\0';  //添加结束符
							
			 } else
			 resultArray0[i] = '\0';//添加结束符            
//       printf("datArray = %s ; dat = %f\r\n",resultArray0,dat);	
}
//double类型转换成ASCII码存到数组中
//precision精度
void DoubletoString(unsigned char* resultArray0,float dat,u8 precision)
{
    if(dat > 0)
    {
				DoubletoStringSaveZheng(resultArray0,dat,precision);
    }
    else if(dat<0)
    {
        resultArray0[0] = '-';
        dat =  (-dat);
				DoubletoStringSaveZheng(&resultArray0[1],dat,precision);
    }else
    {
         resultArray0[0] = '0';
         resultArray0[1] = 0;
    }
}

/*******************************************************
*-函数名称	：字符串类型数据转化成double类型
*-函数作用	：tab中的数变成浮点数,steptdir为正负号判断
*-参数		：
*-返回值	：如果字符串内容不对则不改变dat的原始值
*-备注		：判断正负小数
*******************************************************/
void StrtoDouble(unsigned char* resultArray,float* dat) 
{
    unsigned char i=0,m=0;
    float j = 0,k = 0;
		u8 steptdir = 0;
		unsigned char* tab = resultArray;
	   //有效性判断
		if((tab[0]<'0' && tab[0] != '-')||tab[0]>'9' ||tab[0] == 0)	return;
		
	
		//至多有一个'.',且不能在最后一位,中间不能有'-'
		i=1;
		while(tab[i] != 0)
		{
			if(tab[i] == '.') j ++;
			if(tab[i] == '-') k ++;
			i++;
		}
		if(k>0 ||j>1) return;
		
		j = 0; 
		k = 0;
	
    if(tab[0]=='-')
    {
        steptdir = 1;  //方向为负
        m=1;
    }else steptdir = 0;
    for(i = m;tab[i]!='.';i++)
    {
        if(tab[i]=='\0') 
        {
            *dat = k;
						return;
        }
        k = k*10+(tab[i]-0x30); //取出整数部分
         
    }
    i++;
    for(j = 1;tab[i]!='\0';i++)
    {   
        j = 0.1f*j;
        k = k+(tab[i]-0x30)*j;
    }
		
    *dat = k;
		if(steptdir) *dat = -*dat;
}



//显示数字
void CUIGUI_DrawNum(int x,int y,unsigned int num,u16 width)
{
	char numArray[11]={0};
	u32tostr(num,numArray,width);
	CUIGUI_DrawStr(x,y,1,numArray);
}

//显示double类型数字
void CUIGUI_DrawDoubleNum(int x,int y,float num,unsigned char* numArray)
{
	DoubletoString(numArray,num,4);
	CUIGUI_DrawStr(x,y,1,(const char*)numArray);
}

//显示double类型数字
void CUIGUI_DrawDoubleColorNum(int x,int y,COLOR_DATTYPE color,float num,unsigned char* numArray,u8 precision)
{
	DoubletoString(numArray,num,precision);
	CUIGUI_DrawStr(x,y,color,(const char*)numArray);
}

/************************************************************************************
*-函数名称	：
*-参数			：side位置,在str的位置;oldFontNum旧字体,newFontNum新字体
*-返回值		：返回新字的位置
*-备注			：新字体代替旧字体显示side位置的字符
*-创建者		：蓬莱市博硕电子科技
*/

Position CUIGUI_NumSelect(int x,int y,const char* str,u8 side,const GUI_FONT* oldFontNum,const GUI_FONT* newFontNum)
{
			u16 w;
			u8 i=0;
			u8 width[15] = {0};
			Position pos = {0};
			int x0 = x;
			const char* str0 = str;
			CUIGUI_SetFont(oldFontNum); 	
      while(*str0 != 0)
      { 
				if(i==side)
					w = CUIGUI_DrawWord(x0,y,2,str0); 	//清空
				else
          w = GetWordWidth(&str0[i]); 
					width[i] = w;								//保存每个字的宽度
				
				printf("width[%d] = %d w = %d\r\n",i,width[i],w);
          if((u8)*str0>127)
          {
                 str0 += 2; 
                
          }else //ASCII码
           
            {              
                str0 ++;  
            }            
            x0 += w;
						if(i<side) 
						{
								pos.posx +=  w;
						}
						i ++;
      }
			//保存高度
			pos.posy = GetHeightFont(oldFontNum);
			pos.posx += x;
			CUIGUI_SetFont(newFontNum);		
			pos.posx = pos.posx + width[side]/2 - GetWordWidth((const char*)&str[side])/2;
			pos.posy = y + pos.posy/2 - GetHeightFont(newFontNum)/2;
			CUIGUI_DrawWord(pos.posx,pos.posy,3,(const char*)&str[side]);
			CUIGUI_SetFont(oldFontNum);	
			return pos;
			
}

//保存每个字符的相对位置,并返回字符串长度
u16 GetStrLengthAndSaveSide(const char* str,u8* sideArray)
{
    u16 length =0;
		u8 i = 0;
		sideArray[0] = 0;	
		while(*str != 0)
		{
				i++;
				sideArray[i]  = GetWordWidth(str);		//获得宽度; 
	//		printf("sideArray[%d] = %d\r\n",i,sideArray[i]);
				length += sideArray[i];            
				sideArray[i] = length;
				if(*str>127)
				{
							 str += 2; 
							
				}else //ASCII码				
					{
						
							str ++;  
					}            

		}
		return length;
}

//获得字符串长度个数,不包括停止位0
u16 GetNumOfStr(const char* str)
{
	u16 i = 0;
	while(*str != 0)
	{
		i++;
		if(*str>127)
		{
					 str += 2; 
					
		}else //ASCII码				
			{
				
					str ++;  
			}   
	}
	return i;
}

/************************************************************************************
*-函数名称	：
*-参数			：side位置,在str的位置;oldFontNum旧字体,newFontNum新字体;widthArray 保存宽度的数组
*-返回值		：返回新字的位置
*-备注			：新字体代替旧字体显示side位置的字符
*-创建者		：蓬莱市博硕电子科技
*/

Position CUIGUI_NumSelect2(int x,int y,const char* str,u8* widthArray,u8 side,const GUI_FONT* oldFontNum,const GUI_FONT* newFontNum)
{
			Position pos = {0};
			CUIGUI_SetFont(oldFontNum); 	
			
			//保存高度
			pos.posy = GetHeightFont(oldFontNum);
			pos.posx = x + widthArray[side];
			//清除旧数
			CUIGUI_DrawWord(pos.posx,y,2,(const char*)&str[side]);
			CUIGUI_SetFont(newFontNum);		
			pos.posx = pos.posx + (widthArray[side+1]-widthArray[side])/2 - GetWordWidth((const char*)&str[side])/2;
			pos.posy = y + pos.posy/2 - GetHeightFont(newFontNum)/2;
			CUIGUI_DrawWord(pos.posx,pos.posy,3,(const char*)&str[side]);
			CUIGUI_SetFont(oldFontNum);	
			return pos;
			
}







