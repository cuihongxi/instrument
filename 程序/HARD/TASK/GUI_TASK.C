#include "GUI_TASK.H"
#include "OLED12864.H"
#include "GUI.H"
#include "task_project.h"
#include "menu.h"
#include "dataview.h"
#include "CUIGUI_LCDDRIVER.H"
#include "LISTVIEW.h"
#include "keyscan_task.h"
#include "stmflash.h"
#include "usart.h"

#define	VERSION_NUM		"V.20181213"
TaskHandle_t 	GUI_Handle;
u8 arraybuf[10] = {0};
ShowStr showNature  = {0};	//显示属性
extern ListStr*  MainMenu;

//GUI界面任务
void GUI_Task(void)
{
	CreatALLListMenu();
	showNature.flag_init = 0;
	showNature.thisNature = (NatureStr*)MainMenu;
	CUIGUI_SetFont(&GUI_Fontsongti12);   	//设定字体	
	CUIGUI_DrawStr( 10,2, 1,"Version:");
	CUIGUI_DrawStr(40,18,1,VERSION_NUM);		//版本号
	LIGHTEN_LED(LED_NEXT);
	LIGHTEN_LED(LED_ENTER);
	LIGHTEN_LED(LED_485);
	LIGHTEN_LED(ALARM_LED_G);
	LIGHTEN_LED(ALARM_LED_R);
	FlashData_Init(&showNature);		//读EEPROM的数据
	CUIGUI_DrawStr( 10,34, 1,"Baud:");
	CUIGUI_DrawDoubleNum(40,50,showNature.baud,arraybuf);//显示波特率
	vTaskDelay(2000);
	QUENCH_LED(ALARM_LED_G);
	QUENCH_LED(ALARM_LED_R);
	QUENCH_LED(LED_NEXT);
	QUENCH_LED(LED_ENTER);
	QUENCH_LED(LED_485);
  SetUART1_Baud(showNature.baud);

	DEBUG_Log("GUI_Task created OK!\r\n");
	

	while(1)
	{
		showNature.thisNature->pSkan(&showNature);
		showNature.thisNature->pShow(&showNature);
		vTaskDelay(100);
	}
}
