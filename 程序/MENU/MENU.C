#include "MENU.H"
#include "GUI.H"
#include "CUIGUI_LCDDRIVER.H"
#include "OLED12864.H"
#include "LISTVIEW.H"
#include "keyscan_task.h"
#include "queue.h"
#include "modbus.h"
#include "stm32f3xx_hal_flash.h"
#include "stmflash.h"
#include "usart.h"

extern QueueHandle_t req_QueueHandle;	//发送请求队列句柄
extern ShowStr showNature;
extern datBuf rspHoldREGDatBuf;

static char numarry[10] = {0};		//保存值的字符串
extern unsigned int keyval;
extern float MDint2float(u32* array);
extern void MDfloat2Array(float num,u32* array);
void ShowValuMenu(ShowStr* showStr);
void MD_ByteView_SelectShow(ShowStr* showStr);
void Save8Num(u8* numArray,u8* targetArray);
const char* GetLanguage(ShowStr* showStr,void* list);//获得支持的语言的字符串
void MD_REQ_ReadMessage(ShowStr* showStr);//MDBUS_REQ_TASK中向消息队列中发送读数据,并等待通知返回
void MD_REQ_WriteDat(ShowStr* showStr,u16 datnum,u16 startaddr);//MDBUS_REQ_TASK中向消息队列中发送写数据,并等待返回,datnum为要写入的字节数
void MD_REQ_ReadListShowMessage(ShowStr* showStr);

#define	PRECISION		6		//精度设定

//创建一个视图,调整参数并MODBUS发送修改参数
ViewStr* CreatViewMenuValu(const char* titleE,const char* titleC,u32* parameter)
{
	ViewStr* menu = (ViewStr*)malloc(sizeof(ViewStr));
	menu->nature.showNature = View;
	menu->nature.title_E = titleE;
	menu->nature.title_C = titleC;
	menu->parameter = parameter;
	menu->nature.pShow = MDView_ValueShow;
	menu->nature.pSkan = View_ValueKeyScan;
	return menu;
}

	//创建一个视图,显示参数
ListShowStr* CreatListShowValu(const char* titleE,const char* titleC,u32* parameter)
{
	
	ListShowStr* menu = (ListShowStr*)malloc(sizeof(ListShowStr));
	menu->list.nature.showNature = List;
	menu->list.nature.title_E = titleE;
	menu->list.nature.title_C = titleC;
	menu->parameter = parameter;
	menu->list.nature.pShow = ShowValuMenu;
	menu->list.nature.pSkan = MenuKeyScan;
	return menu;
}

//MD显示值和退出选项
void ShowValuMenu(ShowStr* showStr)
{
	const char* str;
	static u8 nowlist;
	static u8 array[10] = {0};							//临时保存数据
	DLinkList* node = ((ListStr*)showStr->thisNature)->ChildList;
		if(showStr->flag_init == NO_INIT)
		{
			showStr->flag_init = IS_INIT;
			//发送读MODBUS数据
			MD_REQ_ReadListShowMessage(showStr);
			
			Set_Display_On_Off(0);
			ClearLCD();				
			str = GetLanguage(showStr,showStr->thisNature);
			CUIGUI_DrawStr((GetLCDWidth()-GetLengthStr(str))/2,0,1,str);		//显示标题	
			Set_Display_On_Off(1);
			DLinkList_Reset(node);									//重置指针
			//显示列表项			
			for (nowlist=0;nowlist<2;nowlist++)
			{			
					
				if(nowlist>0)
				{
					
					DoubletoString(array,MDint2float(((ListShowStr*)showStr->thisNature)->parameter),PRECISION);//数值转换成字符串
					str = (const char*)array;
					CUIGUI_DrawStr(16,15*(nowlist+1),1,str);																			//显示数据
				}						
				else	
				{
					str = GetLanguage(showStr,DLinkList_Get(node,nowlist));
					CUIGUI_DrawStr(16,15*(nowlist+1),0,str);
				}																
			}
			nowlist = 0;
			showStr->flag_review = NOT_REVIEW;
		}
		if(showStr->flag_review == NEED_REVIEW)
		{
			showStr->flag_review = NOT_REVIEW;
			//将当前反白的清空
			if(nowlist == 0)
				str = GetLanguage(showStr,DLinkList_Current(node));
			else
			{
					str = (const char*)array;					
			}
			CUIGUI_DrawStr(16,15*(nowlist+1),1,str);	
			
			nowlist ++;	
			nowlist %= 2;					
			DLinkList_Next(node);
			if(nowlist == 0)
				str = GetLanguage(showStr,DLinkList_Current(node));
			else
			{
					str = (const char*)array;					
			}
			CUIGUI_DrawStr(16,15*(nowlist+1),0,str);						
		}	
}
	//创建EXIT菜单
ViewStr* CreatViewMenuExit(const char* title_E,const char* title_C)
{
	ViewStr* menu = (ViewStr*)malloc(sizeof(ViewStr));
	menu->nature.showNature = View;
	menu->nature.title_E = title_E;//" Exit Menu ";
	menu->nature.title_C = title_C;//" 退出菜单 ";
	menu->nature.pShow = ExitMenuFun;
	menu->nature.pSkan = MenuKeyScan;
	return menu;
}

//创建一个视图,调整参数后EEPROM保存
ViewStr* CreatViewSaveFlaseValu(const char* titleE,const char* titleC,u32* parameter)
{
	ViewStr* menu = (ViewStr*)malloc(sizeof(ViewStr));
	menu->nature.showNature = View;
	menu->nature.title_E = titleE;
	menu->nature.title_C = titleC;
	menu->parameter = parameter;
	menu->nature.pShow = View_FlashValueShow;
	menu->nature.pSkan = View_ValueKeyScan;
	return menu;
}
/************************************************************************************
*-函数名称	：创建一个视图,选择参数
*-参数			：
*-返回值		：
*-备注			：
*-创建者		：蓬莱市博硕电子科技
*/

ViewStr* CreatView_MenuSelec(const char* titleE,const char* titleC,const char** strList,u8 sizeStrList,u32* parameter)
{
	ViewStr* menu = (ViewStr*)malloc(sizeof(ViewStr));
	menu->nature.showNature = View;
	menu->nature.title_E = titleE;
	menu->nature.title_C = titleC;
	menu->nature.pShow = View_SelectShow;
	menu->nature.pSkan = View_SelectKeyScan;
	menu->strList = strList;
	menu->sizeStrList = sizeStrList;
	menu->parameter = parameter;
	return menu;
}

/************************************************************************************
*-函数名称	：创建一个视图,选择参数,并EEPROM保存
*-参数			：
*-返回值		：
*-备注			：
*-创建者		：蓬莱市博硕电子科技
*/

ViewStr* CreatView_SaveFlaseSelec(const char* titleE,const char* titleC,const char** strList,u8 sizeStrList,u32* parameter)
{
	ViewStr* menu = (ViewStr*)malloc(sizeof(ViewStr));
	menu->nature.showNature = View;
	menu->nature.title_E = titleE;
	menu->nature.title_C = titleC;
	menu->nature.pShow = View_FlashSelectShow;
	menu->nature.pSkan = View_SelectKeyScan;
	menu->strList = strList;
	menu->sizeStrList = sizeStrList;
	menu->parameter = parameter;
	return menu;
}

/************************************************************************************
*-函数名称	：modbus下传送byte参数,创建一个视图,选择参数
*-参数			：
*-返回值		：
*-备注			：
*-创建者		：蓬莱市博硕电子科技
*/

ViewStr* MD_ByteCreatView_MenuSelec(const char* titleE,const char* titleC,const char** strList,u8 sizeStrList,u32* parameter)
{
	ViewStr* menu = (ViewStr*)malloc(sizeof(ViewStr));
	menu->nature.showNature = View;
	menu->nature.title_E = titleE;
	menu->nature.title_C = titleC;
	menu->nature.pShow = MD_ByteView_SelectShow;
	menu->nature.pSkan = View_SelectKeyScan;
	menu->strList = strList;
	menu->sizeStrList = sizeStrList;
	menu->parameter = parameter;
	
	return menu;
}
//创建列表
ListStr* CreatListMenu(const char* titleE,const char* titleC)
{
	ListStr* menu = (ListStr*)malloc(sizeof(ListStr));
	menu->nature.showNature = List;
	menu->nature.title_E = titleE;
	menu->nature.title_C = titleC;
	menu->ChildList = NULL;
	menu->nature.pShow = ShowListMenu;
	menu->nature.pSkan = MenuKeyScan;
	return menu;
}



//添加视图到列表
void AddNode2List(ListStr*  list, DLinkListNode*  node)
{
	if(list->ChildList==NULL)
		list->ChildList = DLinkList_Create();
	node->father = (DLinkListNode*)list;
	
	DLinkList_Insert(list->ChildList, node, DLinkList_Length(list->ChildList));
	
}
//从列表中删除节点
void DeleNodeFromList(ListStr*  list, DLinkListNode*  node)
{
	if(list->ChildList==NULL) return;

	DLinkList_DeleteNode(list->ChildList,node);
}

void AddNode2Listpos(ListStr*  list, DLinkListNode*  node,u8 pos)
{
	if(list->ChildList==NULL)
		list->ChildList = DLinkList_Create();
	node->father = (DLinkListNode*)list;
	DLinkList_Insert(list->ChildList, node,pos);
	
}

//进入子链表
void EnterChildList(ShowStr* showStr)
{
		showStr->flag_init = NO_INIT;
		showStr->thisNature = (NatureStr*)DLinkList_Current(((ListStr*)showStr->thisNature)->ChildList);
}
//返回父链表
void ReturnFatherList(ShowStr* showStr)
{
	NatureStr* addr = (NatureStr* )(((TDLinkList*)showStr->thisNature)->header.father);
	if(addr == NULL)return;
	showStr->flag_init = NO_INIT;
	showStr->thisNature = addr;
}

//获得支持的语言的字符串
const char* GetLanguage(ShowStr* showStr,void* list)
{	
	return ((const char**)(&(((NatureStr*)list)->title_E)))[showStr->Language];
}

//显示列表
void ShowListMenu(ShowStr* showStr)
{
	const char* str;		
	u16 length = 0;
	u8 i;
	static u8 startPage;							//显示的开视页
	static u8 nowlist;								//当前的项，1~4
	u8 oldStartPage;
	u8 nowlength;
	oldStartPage = startPage;

	if(showStr->thisNature->showNature == List)
	{
		DLinkList* node = ((ListStr*)showStr->thisNature)->ChildList;
		
		if(showStr->flag_init == NO_INIT)
		{
			showStr->flag_init = IS_INIT;
			
			Set_Display_On_Off(0);
			ClearLCD();				
			str = GetLanguage(showStr,showStr->thisNature);
			length = GetLengthStr(str);
			CUIGUI_DrawStr((GetLCDWidth()-length)/2,0,1,str);		//显示标题	
			Set_Display_On_Off(1);
			DLinkList_Reset(node);									//重置指针
			//显示列表项			
			for (i=0;i<DLinkList_Length(node);i++)
			{			
				if((i)<4)
				{
					CUIGUI_DrawNum(4,13*(i+1),i+1,8);	//序号
					CUIGUI_DrawStr(9,13*(i+1),1,".");
					str = GetLanguage(showStr,DLinkList_Get(node,i));
					if(i>0) CUIGUI_DrawStr(16,13*(i+1),1,str);
					else		CUIGUI_DrawStr(16,13*(i+1),0,str);					
				}						
			}
			
			nowlist = 0;
			startPage = 0;
			showStr->flag_review = NOT_REVIEW;
		}
		if(showStr->flag_review == NEED_REVIEW)
		{
			showStr->flag_review = NOT_REVIEW;
			//将当前反白的清空
			CUIGUI_DrawNum(4,13*(nowlist+1),startPage*4+nowlist+1,8);	//序号
			CUIGUI_DrawStr(9,13*(nowlist+1),1,".");
			str = GetLanguage(showStr,DLinkList_Current(node));
			CUIGUI_DrawStr(16,13*(nowlist+1),1,str);	
			nowlist ++;	
			if(nowlist>=4)
			{
				nowlist = 0;
				startPage ++;
				
			}
			if((startPage*4+nowlist)>=DLinkList_Length(node))
			{
				startPage = 0;
				nowlist = 0;
			}
					
			DLinkList_Next(node);
			nowlength = DLinkList_CurrentLength(node);
			if(startPage != oldStartPage)//翻页了
			{
				ClearLCD();				
				str = GetLanguage(showStr,showStr->thisNature);
				length = GetLengthStr(str);	
				CUIGUI_DrawStr((GetLCDWidth()-length)/2,0,1,str);		//显示标题	
				for (i=nowlength;i<DLinkList_Length(node);i++)
				{
					if((i-nowlength)<4)
					{
						CUIGUI_DrawNum(4,13*(i-nowlength+1),i+1,8);	//序号
						CUIGUI_DrawStr(9,13*(i-nowlength+1),1,".");
						str = GetLanguage(showStr,DLinkList_Get(node,i));
						if((i-DLinkList_CurrentLength(node)) == 0) CUIGUI_DrawStr(16,13*(i-nowlength+1),0,str);
						else	CUIGUI_DrawStr(16,13*(i-nowlength+1),1,str);					
					}
											
				}			
			}else
			{
				CUIGUI_DrawNum(4,13*(nowlist+1),startPage*4+nowlist+1,8);	//序号
				CUIGUI_DrawStr(9,13*(nowlist+1),1,".");
				str = GetLanguage(showStr,DLinkList_Current(node));
				CUIGUI_DrawStr(16,13*(nowlist+1),0,str);				
			}
	
			
		}	
	}	
}

//列表按键扫描
void MenuKeyScan(ShowStr* showStr)
{
	if(key_val)
	{
		switch(key_val)
		{
			case BUTTON_ENTER_VAL:	if(((ListStr*)(DLinkList_Current(((ListStr*)showStr->thisNature)->ChildList)))->ChildList != NULL || \
				((ListStr*)(DLinkList_Current(((ListStr*)showStr->thisNature)->ChildList)))->nature.pShow == ExitMenuFun) EnterChildList(showStr);
				break;
			case BUTTON_NEXT_VAL: 	showStr->flag_review = NEED_REVIEW;
				break;	
			case BUTTON_NEXT_VAL|BUTTON_ENTER_VAL:
				ClearLCD();
				showStr->flag_init = NO_INIT;
				AddNode2List((ListStr*)showStr->thisNature,(DLinkListNode*)ViewExitConfig);
				showStr->thisNature = (NatureStr*)ViewExitConfig;
			
			break;					
		}
		key_val = 0;	
	}

}

//视图值调整的按键扫描
void View_ValueKeyScan(ShowStr* showStr)
{
	if(key_val)
	{
		switch(key_val)
		{
			case BUTTON_ENTER_VAL:
					showStr->flag_review ++;	//	该标志在值调整中的另一个作用是表示要调整的数的值变化			
				break;
			case BUTTON_NEXT_VAL: 	
					
					showStr->flag_init ++;	//	该标志在值调整中的另一个作用是表示要调整的数位置
				break;	
			case BUTTON_NEXT_VAL|BUTTON_ENTER_VAL:

							showStr->flag_init = 0xff;
			break;					
		}
		key_val = 0;		
	}

}

#define	VALUESTR_POSY		18		//数值显示的Y坐标
#define	YES_POS_Y				51			//是否的位置Y坐标

//MDBUS_REQ_TASK中向消息队列中发送读数据,并等待通知返回
void MD_REQ_ReadMessage(ShowStr* showStr)
{
	reqQueueStr req_message ;
	req_message.datnum = 2;
	req_message.dev_addr = 1;
	req_message.FunNum = MD_READ_HOLD_REG;
	req_message.task = MD_GUITASK;				//标记是GUI的任务,在MODBUS_REQ_TASK中处理
	req_message.startAddr = 0xe4 + (((ViewStr*)showStr->thisNature)->parameter - &(rspHoldREGDatBuf.DrivAd))*2;//计算偏移地址

	DEBUG_Log("&(rspHoldREGDatBuf.DrivAd) - ((ViewStr*)showStr->thisNature)->parameter = %d\r\n",&(rspHoldREGDatBuf.DrivAd) - ((ViewStr*)showStr->thisNature)->parameter);
	xQueueSend(req_QueueHandle,&req_message,500);//发送消息队列
	ulTaskNotifyTake(pdTRUE,300);	//等待通知
	DEBUG_Log("return Message\r\n");
}

//ListShow MDBUS_REQ_TASK中向消息队列中发送读数据,并等待通知返回
void MD_REQ_ReadListShowMessage(ShowStr* showStr)
{
	reqQueueStr req_message ;
	req_message.datnum = 2;
	req_message.dev_addr = 1;
	req_message.FunNum = MD_READ_HOLD_REG;
	req_message.task = MD_GUITASK;				//标记是GUI的任务,在MODBUS_REQ_TASK中处理
	req_message.startAddr = 0xe4 + (((ListShowStr*)showStr->thisNature)->parameter - &(rspHoldREGDatBuf.DrivAd))*2;//计算偏移地址
	
	DEBUG_Log("req_message.startAddr = %#x\r\n",req_message.startAddr);
	xQueueSend(req_QueueHandle,&req_message,500);//发送消息队列
	ulTaskNotifyTake(pdTRUE,2000);	//等待通知
	DEBUG_Log("return Message\r\n");
}

//MDBUS_REQ_TASK中向消息队列中发送写数据,并等待返回,datnum为要写入的字节数
void MD_REQ_WriteDat(ShowStr* showStr,u16 datnum,u16 startaddr)
{
	reqQueueStr req_message ;
	req_message.datnum = datnum;
	req_message.dev_addr = 1;
	req_message.FunNum = MD_WRITE_REGS;
	req_message.task = MD_GUITASK;				//标记是GUI的任务,在MODBUS_REQ_TASK中处理
	req_message.startAddr = startaddr; 
	xQueueSend(req_QueueHandle,&req_message,500);//发送消息队列
	ulTaskNotifyTake(pdTRUE,300);	//等待通知

}
//视图值调整的显示,MODBUS发送
void MDView_ValueShow(ShowStr* showStr)
{
	u16 length = 0;
	const char*	str = 0;
	static u8 strSide[16] = {0};		//保存值的相对位置
	float num = 0;
	static u8 flag_init2;						//保存这两个标志位
	static u8 flag_review2;	
	static Position bigPos;					//保存变大的位置坐标
	static u8 posx;									//保存字符串居中起始位置X坐标
	static u8 numOfStr = 0;				//保存数字的个数
	u8 array[10] = {0};							//临时保存数据
	static const char* yesOnArray[] = {"YES","是","NO","否"};

	if(showStr->flag_init == NO_INIT)
	{
		ClearLCD();
		for(num = 0;num<GETSIZE(numarry);num++)
			numarry[(u8)num] = 0;
//		//发送读MODBUS数据
//		MD_REQ_ReadMessage(showStr);/*更改到ShowValuMenu()中读数据*/
		num = MDint2float(((ViewStr*)showStr->thisNature)->parameter);	
		DEBUG_Log("num = %f\r\n",num);
		str = GetLanguage(showStr,showStr->thisNature);
		length = GetLengthStr(str);
		CUIGUI_DrawStr((GetLCDWidth()-length)/2,0,1,str);						//显示标题	
		
		CUIGUI_SetFont(&GUI_Fontsongti24);   												//设定字体
		DoubletoString(array,num,PRECISION);																	//数值转换成字符串
		DEBUG_Log("array = %s\r\n",array);
		Save8Num(array,(u8*)numarry);																//将STR转换成8位保存到数组
		DEBUG_Log("numarry = %s\r\n",numarry);
		length = GetStrLengthAndSaveSide(numarry,strSide);					//保存位置和长度
		posx = 	(GetLCDWidth()-length)/2;
		CUIGUI_DrawStr(posx,VALUESTR_POSY,1,(const char*)numarry);	//在中间位置打印出数值
		CUIGUI_SetFont(&GUI_Fontsongti12); 
		CUIGUI_DrawStr(16,YES_POS_Y,1,yesOnArray[0+ showStr->Language]);		//是的位置
		CUIGUI_DrawStr(100,YES_POS_Y,0,yesOnArray[2+ showStr->Language]);		//否的位置
		numOfStr = GetNumOfStr(numarry);
		showStr->flag_init = numOfStr + 3;
		showStr->flag_review = NOT_REVIEW;
		flag_init2 = showStr->flag_init;
		flag_review2 = showStr->flag_review;
//		flag_on = 0;
	}else 
	if(showStr->flag_review != flag_review2)	//enter按到
	{
		
		flag_review2 = showStr->flag_review;
		if(showStr->flag_init == numOfStr + 3)	//在否的位置
		{
			CUIGUI_SetFont(&GUI_Fontsongti12);   //设定字体
			ReturnFatherList(showStr);
		}else
		if(showStr->flag_init == numOfStr + 2)//是的位置,保存退出
		{			
			StrtoDouble((unsigned char*)numarry,&num);
			if(num != MDint2float(((ViewStr*)showStr->thisNature)->parameter))
			{
				//保存数值			
				MDfloat2Array(num,((ViewStr*)showStr->thisNature)->parameter);
				//modbus写回MVD
				MD_REQ_WriteDat(showStr,2,0xe4 + (((ViewStr*)showStr->thisNature)->parameter - &(rspHoldREGDatBuf.DrivAd))*2);
								
			}

			DEBUG_Log("num = %f\r\n",num);			
			DEBUG_Log("numarry -> %s\r\n",numarry);
			DEBUG_Log("((ViewStr*)showStr->thisNature)->parameter = %f\r\n",MDint2float(((ViewStr*)showStr->thisNature)->parameter));	
			CUIGUI_SetFont(&GUI_Fontsongti12);   //设定字体
			vTaskDelay(100);
			ReturnFatherList(showStr);			
		}else
		{
			if(flag_review2 >= 12) 
			{
					flag_review2 = 0;
					showStr->flag_review  = 0;
			}
			//清除原先的大字
			CUIGUI_SetFont(&GUI_Fontsongti36);   								//设定字体
			CUIGUI_DrawWord(bigPos.posx,bigPos.posy,2,&numarry[flag_init2 -2]);
				
			//重写新的大字
			numarry[flag_init2 -2] = "0123456789.-"[flag_review2];
			CUIGUI_DrawWord(bigPos.posx,bigPos.posy,3,&numarry[flag_init2 -2]);
			CUIGUI_SetFont(&GUI_Fontsongti24);   										//设定字体		
					
		}

	}else
	if(showStr->flag_init != flag_init2)											//next键被按到
	{
		if(showStr->flag_init == 0xff)													//退出当前菜单
		{			
			CUIGUI_SetFont(&GUI_Fontsongti12);   //设定字体
			ReturnFatherList(showStr);
		}
		else
		{
//			flag_on = 1;
			flag_init2 = showStr->flag_init;
			if((flag_init2 -2)== numOfStr + 2)
			{
				CUIGUI_DrawStr(100,YES_POS_Y,1,yesOnArray[2+ showStr->Language]);		//清反白否的位置
				flag_init2 = 2;
				showStr->flag_init = flag_init2;
			}
			if(flag_init2 == 2)											//第一次调整变大
			{
					bigPos = CUIGUI_NumSelect2(posx,VALUESTR_POSY,numarry,strSide,flag_init2-2,&GUI_Fontsongti24,&GUI_Fontsongti36);
				
			}else
			if((flag_init2 -2)== numOfStr+1)	//清是反白
			{
					CUIGUI_DrawStr(16,YES_POS_Y,1,yesOnArray[0+ showStr->Language]);		//是清反白
					CUIGUI_DrawStr(100,YES_POS_Y,0,yesOnArray[2+ showStr->Language]);		//否的位置反白
			}else
			if((flag_init2 -2)== numOfStr)
			{
				//消除最后一位的数
				CUIGUI_SetFont(&GUI_Fontsongti36);   								//设定字体
				CUIGUI_DrawWord(bigPos.posx,bigPos.posy,2,&numarry[flag_init2 -3]); 
				CUIGUI_SetFont(&GUI_Fontsongti24);   								//设定字体
				//重写当前的数
				CUIGUI_DrawWord(posx + strSide[flag_init2 -3],VALUESTR_POSY,1,&numarry[flag_init2 -3]);
				//移动到是,反白
				CUIGUI_SetFont(&GUI_Fontsongti12);  
				CUIGUI_DrawStr(16,YES_POS_Y,0,yesOnArray[0+ showStr->Language]);		//是的位置反白
			}
			else			
			{
					//清除变大的数
				CUIGUI_SetFont(&GUI_Fontsongti36);   								//设定字体
				CUIGUI_DrawWord(bigPos.posx,bigPos.posy,2,&numarry[flag_init2 -3]);
				CUIGUI_SetFont(&GUI_Fontsongti24);   								//设定字体
				if(flag_init2 > 3)
				{
					//补全前面的数
					CUIGUI_DrawWord(posx + strSide[flag_init2 -4],VALUESTR_POSY,1,&numarry[flag_init2 -4]);			
				}
				//重写当前的数
				CUIGUI_DrawWord(posx + strSide[flag_init2 -3],VALUESTR_POSY,1,&numarry[flag_init2 -3]);
				//清除下一位数,放大重写
				bigPos = CUIGUI_NumSelect2(posx,VALUESTR_POSY,numarry,strSide,flag_init2-2,&GUI_Fontsongti24,&GUI_Fontsongti36);
			
			
			}
			
			if(numarry[flag_init2-2] == '-')
			{
				flag_review2 = 10;
			
			}else
			if(numarry[flag_init2-2] == '.')
			{
				flag_review2 = 9;
			}else
				flag_review2 = numarry[flag_init2-2] - 0x30;
				showStr->flag_review = flag_review2;		
		}

	}
			
}

//视图值调整的显示,flash保存
void View_FlashValueShow(ShowStr* showStr)
{
	u16 length = 0;
	const char*	str = 0;
	static u8 strSide[16] = {0};		//保存值的相对位置
	float num = 0;
	static u8 flag_init2;						//保存这两个标志位
	static u8 flag_review2;	
	static Position bigPos;					//保存变大的位置坐标
	static u8 posx;									//保存字符串居中起始位置X坐标
	static u8 flag_on = 0;					//初次进入的标志
	u8 array[10] = {0};							//临时保存数据
	
	if(showStr->flag_init == NO_INIT)
	{
		ClearLCD();		
		for(num = 0;num<GETSIZE(numarry);num++)
			numarry[(u8)num] = 0;
		num = *((ViewStr*)showStr->thisNature)->parameter;	
		DEBUG_Log("num = %f\r\n",num);
		str = GetLanguage(showStr,showStr->thisNature);
		length = GetLengthStr(str);
		CUIGUI_DrawStr((GetLCDWidth()-length)/2,0,1,str);						//显示标题	
		
		CUIGUI_SetFont(&GUI_Fontsongti24);   												//设定字体
		DoubletoString(array,num,PRECISION);																	//数值转换成字符串
		DEBUG_Log("array = %s\r\n",array);
		Save8Num(array,(u8*)numarry);																//将STR转换成8位保存到数组
		DEBUG_Log("numarry = %s\r\n",numarry);
		length = GetStrLengthAndSaveSide(numarry,strSide);					//保存位置和长度
		posx = 	(GetLCDWidth()-length)/2;
		CUIGUI_DrawStr(posx,VALUESTR_POSY,1,(const char*)numarry);	//在中间位置打印出数值
		showStr->flag_init = IS_INIT;
		showStr->flag_review = NOT_REVIEW;
		flag_init2 = showStr->flag_init;
		flag_review2 = showStr->flag_review;
		flag_on = 0;
	}else 
	if(showStr->flag_review != flag_review2)	//enter按到
	{
		
		flag_review2 = showStr->flag_review;
		if(	flag_on == 0) return;
		if(flag_review2 >= 12) 
		{
				flag_review2 = 0;
				showStr->flag_review  = 0;
		}
		//清除原先的大字
		CUIGUI_SetFont(&GUI_Fontsongti36);   								//设定字体
		CUIGUI_DrawWord(bigPos.posx,bigPos.posy,2,&numarry[flag_init2 -2]);
			
		//重写新的大字
		numarry[flag_init2 -2] = "0123456789.-"[flag_review2];
		CUIGUI_DrawWord(bigPos.posx,bigPos.posy,3,&numarry[flag_init2 -2]);
		CUIGUI_SetFont(&GUI_Fontsongti24);   										//设定字体		
		
	}else
	if(showStr->flag_init != flag_init2)											//next键被按到
	{
		if(showStr->flag_init == 0xff)													//延时一下,保存退出当前菜单
		{
			if(flag_on)
			{
					//消除最后一位的数
					CUIGUI_SetFont(&GUI_Fontsongti36);   								//设定字体
					CUIGUI_DrawWord(bigPos.posx,bigPos.posy,2,&numarry[flag_init2 -2]); 
					CUIGUI_SetFont(&GUI_Fontsongti24);   								//设定字体
					//重写当前的数
					CUIGUI_DrawWord(posx + strSide[flag_init2 -2],VALUESTR_POSY,1,&numarry[flag_init2 -2]);			
			}
			
			StrtoDouble((unsigned char*)numarry,&num);
			if(*(((ViewStr*)showStr->thisNature)->parameter) != (u32)num)
			{
				//保存数值
				*(((ViewStr*)showStr->thisNature)->parameter) = (u32)num;
			//保存数据到EEPROM中
				STMFLASH_Write(FLASH_START_SECTOR,(u32*)(&(showStr->Language)),(sizeof(ShowStr)-6)/4);			
			}

			DEBUG_Log("num = %f\r\n",num);		
			DEBUG_Log("numarry -> %s\r\n",numarry);
			CUIGUI_SetFont(&GUI_Fontsongti12);   //设定字体
			vTaskDelay(100);
			ReturnFatherList(showStr);
		}else
		{
			flag_on = 1;
			flag_init2 = showStr->flag_init;
			if((flag_init2 -2)>= GetNumOfStr(numarry))
			{
					//消除最后一位的数
				CUIGUI_SetFont(&GUI_Fontsongti36);   								//设定字体
				CUIGUI_DrawWord(bigPos.posx,bigPos.posy,2,&numarry[flag_init2 -3]); 
				CUIGUI_SetFont(&GUI_Fontsongti24);   								//设定字体
							//重写当前的数
				CUIGUI_DrawWord(posx + strSide[flag_init2 -3],VALUESTR_POSY,1,&numarry[flag_init2 -3]);
				
				flag_init2 = 2;
				showStr->flag_init = 2;
			}
			if(flag_init2 == 2)											//第一次调整变大
			{
					bigPos = CUIGUI_NumSelect2(posx,VALUESTR_POSY,numarry,strSide,flag_init2-2,&GUI_Fontsongti24,&GUI_Fontsongti36);
				
			}else
			{
					//清除变大的数
				CUIGUI_SetFont(&GUI_Fontsongti36);   								//设定字体
				CUIGUI_DrawWord(bigPos.posx,bigPos.posy,2,&numarry[flag_init2 -3]);
				CUIGUI_SetFont(&GUI_Fontsongti24);   								//设定字体
				if(flag_init2 > 3)
				{
					//补全前面的数
					CUIGUI_DrawWord(posx + strSide[flag_init2 -4],VALUESTR_POSY,1,&numarry[flag_init2 -4]);			
				}
				//重写当前的数
				CUIGUI_DrawWord(posx + strSide[flag_init2 -3],VALUESTR_POSY,1,&numarry[flag_init2 -3]);
				//清除下一位数,放大重写
				bigPos = CUIGUI_NumSelect2(posx,VALUESTR_POSY,numarry,strSide,flag_init2-2,&GUI_Fontsongti24,&GUI_Fontsongti36);
			}
			
			if(numarry[flag_init2-2] == '-')
			{
				flag_review2 = 10;
			
			}else
			if(numarry[flag_init2-2] == '.')
			{
				flag_review2 = 9;
			}else
				flag_review2 = numarry[flag_init2-2] - 0x30;
				showStr->flag_review = flag_review2;		
		}

	}
			
}

//视图选项按键扫描
void View_SelectKeyScan(ShowStr* showStr)
{
	if(key_val)
	{
		switch(key_val)
		{
			case BUTTON_ENTER_VAL:	
					showStr->flag_review ++;	//	该标志在选项选择中的另一个作用是代表选择的值			
				break;
			case BUTTON_NEXT_VAL: 	
					if(showStr->flag_review > 0)
						showStr->flag_review --;	//	该标志在值调整中的另一个作用是表示要调整的数位置
				break;	
			case BUTTON_NEXT_VAL|BUTTON_ENTER_VAL:

						showStr->flag_init = 0xff;
				break;					
		}
		key_val = 0;	
	}		
}
//定义<>显示的横坐标
#define		LEFT_POSX		2
#define		RIGHT_POSX	104
//视图选项的显示
void View_SelectShow(ShowStr* showStr)
{				
	static u8	flag_review2 ;
  const char** strList= ((ViewStr*)showStr->thisNature)->strList;	
	static u8 strSize ;
		if(showStr->flag_init == NO_INIT)
		{
			showStr->flag_init = IS_INIT;
			flag_review2 = *((u8*)(((ViewStr*)showStr->thisNature)->parameter));
			strSize = ((ViewStr*)showStr->thisNature)->sizeStrList;
			Set_Display_On_Off(0);
			ClearLCD();				
			const char* str = GetLanguage(showStr,showStr->thisNature);
			CUIGUI_DrawStr((GetLCDWidth()- GetLengthStr(str))/2,0,1,str);		//显示标题	
			CUIGUI_SetFont(&GUI_Fontsong48);   //设定字体
				if(flag_review2 != strSize-1)
					{
						CUIGUI_DrawStr(RIGHT_POSX,3,3,">");
					}

				if(flag_review2 != 0)
					{
						CUIGUI_DrawStr(LEFT_POSX,3,3,"<");
					}
			CUIGUI_SetFont(&GUI_Fontsongti12);   //设定字体					
			//显示选项			
			CUIGUI_DrawStr((GetLCDWidth()- GetLengthStr(strList[flag_review2]))/2,23,3,strList[flag_review2]);
			showStr->flag_review = flag_review2;
			Set_Display_On_Off(1);
			
			}else 
			if(showStr->flag_init == 0xff)	//保存退出
			{
				if(*((u8*)(((ViewStr*)showStr->thisNature)->parameter)) != showStr->flag_review)
				{
					*((u8*)(((ViewStr*)showStr->thisNature)->parameter)) = showStr->flag_review;	//保存数值
				}
					
					ReturnFatherList(showStr);
			}else
			if(showStr->flag_review != flag_review2)
			{
				CUIGUI_DrawStr((GetLCDWidth()- GetLengthStr(strList[flag_review2]))/2,23,2,strList[flag_review2]);				

				if(showStr->flag_review >= strSize)
				{
					showStr->flag_review = strSize - 1;										
				}		
				flag_review2 = showStr->flag_review;
				CUIGUI_SetFont(&GUI_Fontsong48);   //设定字体
				if(flag_review2 == strSize-1)
					{
						CUIGUI_DrawStr(RIGHT_POSX,3,2,">");
					}
				else
					{
						CUIGUI_DrawStr(RIGHT_POSX,3,3,">");
					}
				if(flag_review2 == 0)
					{
						CUIGUI_DrawStr(LEFT_POSX,3,2,"<");
					}
				else
					{
						CUIGUI_DrawStr(LEFT_POSX,3,3,"<");
					}
				CUIGUI_SetFont(&GUI_Fontsongti12);   //设定字体		
				CUIGUI_DrawStr((GetLCDWidth()- GetLengthStr(strList[flag_review2]))/2,23,3,strList[flag_review2]);
				showStr->flag_review = flag_review2;						
			}
	
}
//FLASH保存选项内容
void View_FlashSelectShow(ShowStr* showStr)
{				
	static u8	flag_review2 ;
  const char** strList= ((ViewStr*)showStr->thisNature)->strList;	
	static u8 strSize ;
		if(showStr->flag_init == NO_INIT)
		{
			showStr->flag_init = IS_INIT;
			flag_review2 = *((u8*)(((ViewStr*)showStr->thisNature)->parameter));
			strSize = ((ViewStr*)showStr->thisNature)->sizeStrList;
			Set_Display_On_Off(0);
			ClearLCD();				
			const char* str = GetLanguage(showStr,showStr->thisNature);
			CUIGUI_DrawStr((GetLCDWidth()- GetLengthStr(str))/2,0,1,str);		//显示标题	
			CUIGUI_SetFont(&GUI_Fontsong48);   //设定字体
				if(flag_review2 != strSize-1)
					{
						CUIGUI_DrawStr(RIGHT_POSX,3,3,">");
					}

				if(flag_review2 != 0)
					{
						CUIGUI_DrawStr(LEFT_POSX,3,3,"<");
					}
			CUIGUI_SetFont(&GUI_Fontsongti12);   //设定字体					
			//显示选项			
			CUIGUI_DrawStr((GetLCDWidth()- GetLengthStr(strList[flag_review2]))/2,23,3,strList[flag_review2]);
			showStr->flag_review = flag_review2;
			Set_Display_On_Off(1);
			
			}else 
			if(showStr->flag_init == 0xff)	//保存退出
			{
				if(*((u8*)(((ViewStr*)showStr->thisNature)->parameter)) != showStr->flag_review)
				{
					*((u8*)(((ViewStr*)showStr->thisNature)->parameter)) = showStr->flag_review;	//保存数值
				//保存数据到EEPROM中
					STMFLASH_Write(FLASH_START_SECTOR,(u32*)(&(showStr->Language)),(sizeof(ShowStr)-6)/4);				
				}
					ReturnFatherList(showStr);
			}else
			if(showStr->flag_review != flag_review2)
			{
				CUIGUI_DrawStr((GetLCDWidth()- GetLengthStr(strList[flag_review2]))/2,23,2,strList[flag_review2]);				

				if(showStr->flag_review >= strSize)
				{
					showStr->flag_review = strSize - 1;										
				}		
				flag_review2 = showStr->flag_review;
				CUIGUI_SetFont(&GUI_Fontsong48);   //设定字体
				if(flag_review2 == strSize-1)
					{
						CUIGUI_DrawStr(RIGHT_POSX,3,2,">");
					}
				else
					{
						CUIGUI_DrawStr(RIGHT_POSX,3,3,">");
					}
				if(flag_review2 == 0)
					{
						CUIGUI_DrawStr(LEFT_POSX,3,2,"<");
					}
				else
					{
						CUIGUI_DrawStr(LEFT_POSX,3,3,"<");
					}
				CUIGUI_SetFont(&GUI_Fontsongti12);   //设定字体		
				CUIGUI_DrawStr((GetLCDWidth()- GetLengthStr(strList[flag_review2]))/2,23,3,strList[flag_review2]);
				showStr->flag_review = flag_review2;						
			}
	
}

//视图选项的显示,MODBUS发送8位
void MD_ByteView_SelectShow(ShowStr* showStr)
{				
	static u8	flag_review2 ;
  const char** strList= ((ViewStr*)showStr->thisNature)->strList;	
	static u8 strSize ;
		if(showStr->flag_init == NO_INIT)
		{
			showStr->flag_init = IS_INIT;
			flag_review2 = *((u8*)(((ViewStr*)showStr->thisNature)->parameter));
			strSize = ((ViewStr*)showStr->thisNature)->sizeStrList;
			Set_Display_On_Off(0);
			ClearLCD();				
			const char* str = GetLanguage(showStr,showStr->thisNature);
			CUIGUI_DrawStr((GetLCDWidth()- GetLengthStr(str))/2,0,1,str);		//显示标题	
			CUIGUI_SetFont(&GUI_Fontsong48);   //设定字体
			if(flag_review2 != strSize-1)
				{
					CUIGUI_DrawStr(RIGHT_POSX,3,3,">");
				}

			if(flag_review2 != 0)
				{
					CUIGUI_DrawStr(LEFT_POSX,3,3,"<");
				}
			CUIGUI_SetFont(&GUI_Fontsongti12);   //设定字体					
			//显示选项			
			CUIGUI_DrawStr((GetLCDWidth()- GetLengthStr(strList[flag_review2]))/2,23,3,strList[flag_review2]);
			showStr->flag_review = flag_review2;
			Set_Display_On_Off(1);
			
			}else
			if(showStr->flag_init == 0xff)	//保存退出
			{
				//if(*((u8*)(((ViewStr*)showStr->thisNature)->parameter)) != showStr->flag_review)
				{
					*((u8*)(((ViewStr*)showStr->thisNature)->parameter)) = showStr->flag_review;	//保存数值		 
					MD_REQ_WriteDat(showStr,6,0x13c);	//写入U8类型等信息
					MD_REQ_WriteDat(showStr,6,0x13c);	//写入U8类型等信息
					MD_REQ_WriteDat(showStr,6,0x13c);	//写入U8类型等信息
						//如果是波特率,则更改波特率
					if(((ViewStr*)showStr->thisNature)->parameter == (u32*)&rspHoldREGDatBuf.BautRate)
					{
						extern const char* arryBaud[];
						float baud ;
						StrtoDouble((unsigned char*)arryBaud[*((u8*)(((ViewStr*)showStr->thisNature)->parameter))],&baud);
						SetUART1_Baud((u32)baud);			//设置波特率
						vTaskDelay(500);
						//保存数据到EEPROM中
						showStr->baud = (u32)baud;
						STMFLASH_Write(FLASH_START_SECTOR,(u32*)(&(showStr->Language)),(sizeof(ShowStr)-6)/4);	
					}
				}
					ReturnFatherList(showStr);
			}else
			if(showStr->flag_review != flag_review2)
			{
				CUIGUI_DrawStr((GetLCDWidth()- GetLengthStr(strList[flag_review2]))/2,23,2,strList[flag_review2]);				

				if(showStr->flag_review >= strSize)
				{
					showStr->flag_review = strSize - 1;										
				}		
				flag_review2 = showStr->flag_review;
				CUIGUI_SetFont(&GUI_Fontsong48);   //设定字体
				if(flag_review2 == strSize-1)
					{
						CUIGUI_DrawStr(RIGHT_POSX,3,2,">");
					}
				else
					{
						CUIGUI_DrawStr(RIGHT_POSX,3,3,">");
					}
				if(flag_review2 == 0)
					{
						CUIGUI_DrawStr(LEFT_POSX,3,2,"<");
					}
				else
					{
						CUIGUI_DrawStr(LEFT_POSX,3,3,"<");
					}
				CUIGUI_SetFont(&GUI_Fontsongti12);   //设定字体		
				CUIGUI_DrawStr((GetLCDWidth()- GetLengthStr(strList[flag_review2]))/2,23,3,strList[flag_review2]);
				showStr->flag_review = flag_review2;						
			}
	
}

//用在LISTVIEW中的改变数值函数,函数改变的参数固定是8位
//8位保存数据,
//00012345
void Save8Num(u8* numArray,u8* targetArray)
{
	u8 num = 0;	//保存numArray中位数
	u8 i = 0;
	while(numArray[num]!=0) num ++;
	if(num<8)
	{
		//前面补0
		for(i=0;i<(8-num);i++)
		{
			targetArray[i] = '0';
		}

	}
	//然后依次存储
	for(;i<8;i++)
	{
		targetArray[i] = *numArray;
		numArray ++;
	}
}










