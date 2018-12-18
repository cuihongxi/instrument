#include "LISTVIEW.h"
#include "CUIGUI_LCDDRIVER.H"
#include "GUI.H"
#include "dataview.h"
#include "keyscan_task.h"
#include "modbus_config.h"

ListStr*  listINTERFACE;
ViewStr*  ViewExitMenu;
ListStr*  MainMenu;
ViewStr*  ViewExitConfig;
extern void ClearLCD(void);
extern void Set_Display_On_Off(unsigned char d);
extern ShowStr showNature;
extern void DataViewMenu(ShowStr* showStr );
extern void DataViewKeyScan(ShowStr* showStr);
u32 dat0 = 1;
//u32 dat1 = 2;
//u32 dat2 = 0;
//参数选项表
const char* arraySetZLCeLiangUnits[] = {"g/s","g/m","g/h","kg/s","kg/m","kg/h","t/s","t/m","t/h"};//质量流量测量单位
const char* arraySetZLLeiJiUnits[] = {"g","kg","t"};//质量流量累计单位
const char* arraySetTJCeLiangUnits[] = {"mL/s", "mL/m","mL/h","L/s","L/m","L/h","m^3/s","m^3/m","m^3/h"};//体积流量测量单位
const char* arraySetTJLeiJiUnits[] = {"mL","L","m^3"};//体积流量累计单位
const char* arraySetDensityUnits[] = {"g/cm^3","kg/cm^3"};//密度单位
const char* arraySetTempUnits[] = {"℃","F","K"};//温度单位
const char* arrayLLSetMeasureDir[] = {"双向","正向","反向","绝对值"};//流量测量方向设置
const char* arraySelectShowParam[] = {"瞬时质量流量","累计质量流量","瞬时体积流量","累计体积流量","介质密度","介质温度"};//显示参数选择
const char* arraySelectShowForm[] = {"XXXXXXXX","XXXXXX.X","XXXXX.XX","XXXX.XXX","XXX.XXXX","XX.XXXXX","X.XXXXXX"};//显示格式
const char* arryInterface[] = {"Interface1","Interface2","Interface3"};//显示界面选择
const char* arryLanguage[] = {"English","中文"};//语言选择
const char* arrySelectOutputSignal1[] = {"瞬时质量流量","瞬时体积流量","密度","温度"};//输出信号选择1
const char* arrySelectOutputSignal2[] = {"质量流量","体积流量"};//输出信号选择2
const char* arrySelectAlarmParam[] = {"质量流量","质量累积量","体积流量","体积累计量","密度","温度"};//选择报警参数
const char* arrySetAlarmForm[] = {"上限","下限"};//设置报警形式
const char* arryControlOutput[] = {"是","否"};//控制输出
const char* arrySelectControlParam[] = {"零点校准","累积量清零"};//选择控制参数
const char* arrySelectControlForm[] = {"高电平","低电平"};//有效控制形式
const char* arryZeroResize[] = {"是","否"};//零点调整
const char* arryClearCumulants[] = {"是","否"};//累积量清零
const char* arryQudongFudu[] = {"1","2","3","4","5"};//驱动幅度调整
const char* arryBaud[] = {"1200","9600","19200","38400","57600","115200"};//通讯波特率
const char* arryAddr[] = {"0","1","2","3","4","5","6","7","8","9"};//通讯地址
const char* arrySelectControlPar[] = {"零点校准","累积量清零"};//选择控制参数
const char* arryValidControlForm[] = {"高电平","低电平"};//有效控制形式

//退出EXIT菜单函数
void ExitMenuFun(ShowStr* showStr)
{
	ClearLCD();
	showStr->flag_init = NO_INIT;
	ReturnFatherList(showStr);//返回父链表
	ReturnFatherList(showStr);//返回父链表
}

//退出设置
void ExitConfigShow(ShowStr* showStr )
{
	
	if(showStr->flag_init == NO_INIT)		//初始化
	{
		showStr->flag_init = IS_INIT;
		//画字符串
		if(showStr->Language == ENGLISH)
		{
			CUIGUI_DrawStr( 2,10,1,"EXIT FROM INTERFACE");
			CUIGUI_DrawStr( 40,30,1,"CONFIRMATION");	
			CUIGUI_DrawStr( 40,46,1,"PRESS BUTTON(↓)");
		}else
		{
			CUIGUI_DrawStr( 2,10,1,"EXIT FROM INTERFACE");
			CUIGUI_DrawStr( 20,30,1,"确认退出按按键(↓)");				
		}	
		
	}else
	{
		//已经初始化
		
	}
}

//退出设置扫描
void ExitConfigKeyScan(ShowStr* showStr )
{
	if(key_val)
	{
		ClearLCD();
		ReturnFatherList(showStr);//返回父链表
		//删掉退出设置菜单
		DeleNodeFromList((ListStr*) showStr->thisNature, (DLinkListNode*)ViewExitConfig);
		showStr->flag_init = NO_INIT;
		if(key_val == BUTTON_NEXT_VAL) 
		{		
			showStr->thisNature = (NatureStr*)MainMenu;
		}
		key_val = 0;	
	}
}




//创建所有的列表项
void CreatALLListMenu(void)
{	
	
	ViewExitConfig = CreatViewMenuValu("EXIT FROM INTERFACE","EXIT FROM INTERFACE",&dat0);//退出设置
	ViewExitConfig->nature.pShow = ExitConfigShow;
	ViewExitConfig->nature.pSkan = ExitConfigKeyScan;
	
	ViewStr* ViewExitMenu = CreatViewMenuExit(" Exit Menu "," 退出菜单 ");//退出菜单
	ViewStr* ViewExitMenu0 = CreatViewMenuExit(" Exit Menu "," 退出菜单 ");//退出菜单
	ViewStr* ViewExitMenu1 = CreatViewMenuExit(" Exit Menu "," 退出菜单 ");//退出菜单
	ViewStr* ViewExitMenu2 = CreatViewMenuExit(" Exit Menu "," 退出菜单 ");//退出菜单
	ViewStr* ViewExitMenu3 = CreatViewMenuExit(" Exit Menu "," 退出菜单 ");//退出菜单
	ViewStr* ViewExitMenu4 = CreatViewMenuExit(" Exit Menu "," 退出菜单 ");//退出菜单
	ViewStr* ViewExitMenu5 = CreatViewMenuExit(" Exit Menu "," 退出菜单 ");//退出菜单
	ViewStr* ViewExitMenu6 = CreatViewMenuExit(" Exit Menu "," 退出菜单 ");//退出菜单
	ViewStr* ViewExitMenu7 = CreatViewMenuExit(" Exit Menu "," 退出菜单 ");//退出菜单
	ViewStr* ViewExitMenu8 = CreatViewMenuExit(" Exit Menu "," 退出菜单 ");//退出菜单
	ViewStr* ViewExitMenu9 = CreatViewMenuExit(" Exit Menu "," 退出菜单 ");//退出菜单
	ViewStr* ViewExitMenu10 = CreatViewMenuExit(" Exit Menu "," 退出菜单 ");//退出菜单
	ViewStr* ViewExitMenu11 = CreatViewMenuExit(" Exit Menu "," 退出菜单 ");//退出菜单
	ViewStr* ViewExitMenu12 = CreatViewMenuExit(" Exit Menu "," 退出菜单 ");//退出菜单
	ViewStr* ViewExitMenu13 = CreatViewMenuExit(" Exit Menu "," 退出菜单 ");//退出菜单
	ViewStr* ViewExitMenu14 = CreatViewMenuExit(" Exit Menu "," 退出菜单 ");//退出菜单
	
		
	ViewStr* ViewExitMenu15 = CreatViewMenuExit(" Exit "," 退出 ");//退出菜单
	ViewStr* ViewExitMenu16 = CreatViewMenuExit(" Exit "," 退出 ");//退出菜单
	ViewStr* ViewExitMenu17 = CreatViewMenuExit(" Exit "," 退出 ");//退出菜单
	ViewStr* ViewExitMenu18 = CreatViewMenuExit(" Exit "," 退出 ");//退出菜单
	ViewStr* ViewExitMenu19 = CreatViewMenuExit(" Exit "," 退出 ");//退出菜单
	ViewStr* ViewExitMenu20 = CreatViewMenuExit(" Exit "," 退出 ");//退出菜单
	ViewStr* ViewExitMenu21 = CreatViewMenuExit(" Exit "," 退出 ");//退出菜单
	ViewStr* ViewExitMenu22 = CreatViewMenuExit(" Exit "," 退出 ");//退出菜单
	ViewStr* ViewExitMenu23 = CreatViewMenuExit(" Exit "," 退出 ");//退出菜单
	ViewStr* ViewExitMenu24 = CreatViewMenuExit(" Exit "," 退出 ");//退出菜单
	ViewStr* ViewExitMenu25 = CreatViewMenuExit(" Exit "," 退出 ");//退出菜单
	ViewStr* ViewExitMenu26 = CreatViewMenuExit(" Exit "," 退出 ");//退出菜单
	ViewStr* ViewExitMenu27 = CreatViewMenuExit(" Exit "," 退出 ");//退出菜单
	ViewStr* ViewExitMenu28 = CreatViewMenuExit(" Exit "," 退出 ");//退出菜单	
	ViewStr* ViewExitMenu29 = CreatViewMenuExit(" Exit "," 退出 ");//退出菜单
	ViewStr* ViewExitMenu30 = CreatViewMenuExit(" Exit "," 退出 ");//退出菜单
	ViewStr* ViewExitMenu31 = CreatViewMenuExit(" Exit "," 退出 ");//退出菜单
	ViewStr* ViewExitMenu32 = CreatViewMenuExit(" Exit "," 退出 ");//退出菜单
	ViewStr* ViewExitMenu33 = CreatViewMenuExit(" Exit "," 退出 ");//退出菜单
	ViewStr* ViewExitMenu34 = CreatViewMenuExit(" Exit "," 退出 ");//退出菜单
	ViewStr* ViewExitMenu35 = CreatViewMenuExit(" Exit "," 退出 ");//退出菜单		
	ViewStr* ViewExitMenu36 = CreatViewMenuExit(" Exit "," 退出 ");//退出菜单	
	ViewStr* ViewExitMenu37 = CreatViewMenuExit(" Exit "," 退出 ");//退出菜单
	ViewStr* ViewExitMenu38 = CreatViewMenuExit(" Exit "," 退出 ");//退出菜单
	ViewStr* ViewExitMenu39 = CreatViewMenuExit(" Exit "," 退出 ");//退出菜单
	ViewStr* ViewExitMenu40 = CreatViewMenuExit(" Exit "," 退出 ");//退出菜单
	ViewStr* ViewExitMenu41 = CreatViewMenuExit(" Exit "," 退出 ");//退出菜单
	ViewStr* ViewExitMenu42 = CreatViewMenuExit(" Exit "," 退出 ");//退出菜单
		
	//创建主界面	
	 MainMenu = CreatListMenu(" "," ");
	listINTERFACE = CreatListMenu(" Main Setting "," Main Setting ");
	AddNode2List(MainMenu,(DLinkListNode*)listINTERFACE);
	MainMenu->nature.pShow = DataViewMenu;
	MainMenu->nature.pSkan = DataViewKeyScan;	
	/**************************一级设置***************************************************/

	
	ListStr*  list1CeLiangCanShu = CreatListMenu(" CeLiangCanShu "," 测量参数设置 ");
	ListStr*  listDisplaySet = CreatListMenu(" DisplaySet "," 显示设置 ");
	ListStr*  list1XinHaoShuChu = CreatListMenu(" XinHaoShuChu "," 信号输出设置 ");
	ListStr*  listControlSet = CreatListMenu(" ControlSet "," 控制设置 ");
	ListStr*  list1ChaoJiQuanXian = CreatListMenu(" ChaoJiQuanXian "," 超级权限");
	AddNode2List(listINTERFACE,(DLinkListNode*)ViewExitMenu);
	AddNode2List(listINTERFACE,(DLinkListNode*)list1CeLiangCanShu);
	AddNode2List(listINTERFACE,(DLinkListNode*)listDisplaySet);
	AddNode2List(listINTERFACE,(DLinkListNode*)list1XinHaoShuChu);
	AddNode2List(listINTERFACE,(DLinkListNode*)listControlSet);
	AddNode2List(listINTERFACE,(DLinkListNode*)list1ChaoJiQuanXian);

	/**************************二级设置***************************************************/
	ListStr*  listYiBiaoXiShu = CreatListMenu(" YiBiaoXiShu "," 仪表系数设置 ");
	ListStr*  listCeLiangDanWei = CreatListMenu(" CeLiangDanWei "," 测量单位设置 ");
	ListStr*  listCeLiangLiangCeng = CreatListMenu(" CeLiangLiangCeng "," 测量量程设置 ");
	ListStr*  listLLTiaoZhengCanShu = CreatListMenu(" TiaoZhengCanShu "," 流量调整参数设置 ");
	ListStr*  listQTTiaoZhengCanShu = CreatListMenu(" TiaoZhengCanShu "," 其他调整参数设置 ");
	AddNode2List(list1CeLiangCanShu,(DLinkListNode*)ViewExitMenu0);
	AddNode2List(list1CeLiangCanShu,(DLinkListNode*)listYiBiaoXiShu);
	AddNode2List(list1CeLiangCanShu,(DLinkListNode*)listCeLiangDanWei);
	AddNode2List(list1CeLiangCanShu,(DLinkListNode*)listCeLiangLiangCeng);
	AddNode2List(list1CeLiangCanShu,(DLinkListNode*)listLLTiaoZhengCanShu);
	AddNode2List(list1CeLiangCanShu,(DLinkListNode*)listQTTiaoZhengCanShu);
	
	ListStr*  listResolution = CreatListMenu(" Resolution "," 显示分辨率选择 ");
	ViewStr*  listDefaultInterface = CreatViewSaveFlaseSelec(" DefaultInterface "," 默认界面选择 ",arryInterface,(u32*)&showNature.Interface);
	ViewStr*  listLanguage = CreatViewSaveFlaseSelec(" Language "," 语言选择 ",arryLanguage,(u32*)&showNature.Language);
	AddNode2List(listDisplaySet,(DLinkListNode*)ViewExitMenu1);
	AddNode2List(listDisplaySet,(DLinkListNode*)listResolution);
	AddNode2List(listDisplaySet,(DLinkListNode*)listDefaultInterface);
	AddNode2List(listDisplaySet,(DLinkListNode*)listLanguage);		
	listDisplaySet->nature.pShow = ShowListMenu;
	listDisplaySet->nature.pSkan = MenuKeyScan;
	
	ListStr*  listMaiChongShuChu1 = CreatListMenu(" MaiChongShuChu1 "," 脉冲信号输出1 ");
	ListStr*  listMaiChongShuChu2 = CreatListMenu(" MaiChongShuChu2 "," 脉冲信号输出2 ");
	AddNode2List(list1XinHaoShuChu,(DLinkListNode*)ViewExitMenu2);
	AddNode2List(list1XinHaoShuChu,(DLinkListNode*)listMaiChongShuChu1);
	AddNode2List(list1XinHaoShuChu,(DLinkListNode*)listMaiChongShuChu2);

	ListStr*  listInControlSet = CreatListMenu(" InControlSet "," 输入控制设置 ");
	ViewStr*  ViewZeroResize = CreatViewMenuSelec(" ZeroResize "," 零点调整 ",arryZeroResize,(u32*)&showNature.ZeroResize);
	ViewStr*  ViewClearCumulants  = CreatViewMenuSelec(" ClearCumulants "," 累积量清零 ",arryClearCumulants,(u32*)&showNature.ClearCumulants);
	ViewStr*  ViewQudongFudu = CreatViewMenuSelec(" QudongFudu "," 驱动幅度调整 ",arryQudongFudu,(u32*)&showNature.quDongFudu);
	ViewStr*  ViewMailAddr = MD_ByteCreatViewMenuSelec("MailAddr"," 通讯地址 ",arryAddr,(u32*)&rspHoldREGDatBuf.CommAddress);
	ViewStr*  ViewBaud = MD_ByteCreatViewMenuSelec(" Baud "," 通讯波特率 ",arryBaud,(u32*)&rspHoldREGDatBuf.BautRate);
	
	AddNode2List(listControlSet,(DLinkListNode*)ViewExitMenu3);
	AddNode2List(listControlSet,(DLinkListNode*)listInControlSet);
	AddNode2List(listControlSet,(DLinkListNode*)ViewZeroResize);
	AddNode2List(listControlSet,(DLinkListNode*)ViewClearCumulants);
	AddNode2List(listControlSet,(DLinkListNode*)ViewQudongFudu);
	AddNode2List(listControlSet,(DLinkListNode*)ViewMailAddr);
	AddNode2List(listControlSet,(DLinkListNode*)ViewBaud);
	
	ListStr*  listLogoSet = CreatListMenu(" LogoSet "," 开机启动logo选择 ");
	ListStr*  listPassWord  = CreatListMenu(" PassWord "," 用户密码设置 ");
	ListStr*  listOthers = CreatListMenu(" Others "," 其他 ");
	AddNode2List(list1ChaoJiQuanXian,(DLinkListNode*)ViewExitMenu4);
	AddNode2List(list1ChaoJiQuanXian,(DLinkListNode*)listLogoSet);
	AddNode2List(list1ChaoJiQuanXian,(DLinkListNode*)listPassWord);
	AddNode2List(list1ChaoJiQuanXian,(DLinkListNode*)listOthers);
/********************************三级设置*********************************************/

	ListShowStr*  ListShowSttingFC = CreatListShowValu(" SttingFC "," 流量系数FC ",&(rspHoldREGDatBuf.MassFlowK));//
	ListShowStr*  ListShowSettingFT = CreatListShowValu(" SettingFT "," 流量温度系数FT ",&(rspHoldREGDatBuf.MassCT));
	ListShowStr*  ListShowSettingK1 = CreatListShowValu(" SettingK1 "," 密度系数K1 ",&(rspHoldREGDatBuf.DensityK1));
	ListShowStr*  ListShowSettingK2 = CreatListShowValu(" SettingK2 "," 密度系数K2 ",&(rspHoldREGDatBuf.DensityK2));
	ListShowStr*  ListShowSettingDT = CreatListShowValu(" SettingDT "," 密度温度系数DT ",&(rspHoldREGDatBuf.DensityFD));
	ListShowStr*  ListShowSettingFD = CreatListShowValu(" SettingFD "," 密度流速系数FD ",&(rspHoldREGDatBuf.DensFT));	
	AddNode2List(listYiBiaoXiShu,(DLinkListNode*)ViewExitMenu5);
	AddNode2List(listYiBiaoXiShu,(DLinkListNode*)ListShowSttingFC);
	AddNode2List(listYiBiaoXiShu,(DLinkListNode*)ListShowSettingFT);
	AddNode2List(listYiBiaoXiShu,(DLinkListNode*)ListShowSettingK1);
	AddNode2List(listYiBiaoXiShu,(DLinkListNode*)ListShowSettingK2);
	AddNode2List(listYiBiaoXiShu,(DLinkListNode*)ListShowSettingDT);
	AddNode2List(listYiBiaoXiShu,(DLinkListNode*)ListShowSettingFD);
	
	ViewStr*  ViewSetZLCeLiangUnits = MD_ByteCreatViewMenuSelec(" SetZLCeLiangUnits "," 质量流量测量单位 ",arraySetZLCeLiangUnits,(u32*)&rspHoldREGDatBuf.UnitMassFlow);
	ViewStr*  ViewSetZLLeiJiUnits  = MD_ByteCreatViewMenuSelec(" SetZLLeiJiUnits "," 质量流量累计单位 ",arraySetZLLeiJiUnits,(u32*)&(rspHoldREGDatBuf.UnitMassTotal));
	ViewStr*  ViewSetTJCeLiangUnits = MD_ByteCreatViewMenuSelec(" SetTJCeLiangUnits "," 体积流量测量单位 ",arraySetTJCeLiangUnits,(u32*)&rspHoldREGDatBuf.UnitVolumeFlow);
	ViewStr*  ViewSetTJLeiJiUnits = MD_ByteCreatViewMenuSelec(" SetTJLeiJiUnits "," 体积流量累计单位 ",arraySetTJLeiJiUnits,(u32*)&rspHoldREGDatBuf.UnitVolumeTotal);
	ViewStr*  ViewSetDensityUnit = MD_ByteCreatViewMenuSelec(" SetDensityUnit "," 密度单位设置 ",arraySetDensityUnits,(u32*)&rspHoldREGDatBuf.UnitDensity);
	ViewStr*  ViewSetTempUnits = MD_ByteCreatViewMenuSelec(" SetTempUnits "," 温度单位设置 ",arraySetTempUnits,(u32*)&rspHoldREGDatBuf.UnitTemperature);
	AddNode2List(listCeLiangDanWei,(DLinkListNode*)ViewExitMenu6);
	AddNode2List(listCeLiangDanWei,(DLinkListNode*)ViewSetZLCeLiangUnits);
	AddNode2List(listCeLiangDanWei,(DLinkListNode*)ViewSetZLLeiJiUnits);
	AddNode2List(listCeLiangDanWei,(DLinkListNode*)ViewSetTJCeLiangUnits);
	AddNode2List(listCeLiangDanWei,(DLinkListNode*)ViewSetTJLeiJiUnits);
	AddNode2List(listCeLiangDanWei,(DLinkListNode*)ViewSetDensityUnit);	
	AddNode2List(listCeLiangDanWei,(DLinkListNode*)ViewSetTempUnits);	

	ListShowStr*  ListShowSetZLUper = CreatListShowValu(" SetZLUper "," 质量流量上限 ",&(rspHoldREGDatBuf.MaxMass));
	ListShowStr*  ListShowSetZLFloor  = CreatListShowValu(" SetZLFloor "," 质量流量下限 ",&(rspHoldREGDatBuf.MinMass));
	ListShowStr*  ListShowSetTJUper = CreatListShowValu(" SetTJUper "," 体积流量上限 ",&(rspHoldREGDatBuf.MaxVolu));
	ListShowStr*  ListShowSetTJFloor = CreatListShowValu(" SetTJFloor "," 体积流量下限 ",&(rspHoldREGDatBuf.MinVolu));
	ListShowStr*  ListShowSetMDUper = CreatListShowValu(" SetMDUper "," 密度测量上限 ",&(rspHoldREGDatBuf.MaxDens));
	ListShowStr*  ListShowSetMDFloor  = CreatListShowValu(" SetMDFloor "," 密度测量下限 ",&(rspHoldREGDatBuf.MinDens));
	ListShowStr*  ListShowSetWDUper = CreatListShowValu(" SetWDUper "," 温度测量上限 ",&(rspHoldREGDatBuf.MaxTemp));
	ListShowStr*  ListShowSetWDFloor = CreatListShowValu(" SetWDFloor "," 温度测量下限 ",&(rspHoldREGDatBuf.MinTemp));
	AddNode2List(listCeLiangLiangCeng,(DLinkListNode*)ViewExitMenu7);
	AddNode2List(listCeLiangLiangCeng,(DLinkListNode*)ListShowSetZLUper);
	AddNode2List(listCeLiangLiangCeng,(DLinkListNode*)ListShowSetZLFloor);
	AddNode2List(listCeLiangLiangCeng,(DLinkListNode*)ListShowSetTJUper);
	AddNode2List(listCeLiangLiangCeng,(DLinkListNode*)ListShowSetTJFloor);
	AddNode2List(listCeLiangLiangCeng,(DLinkListNode*)ListShowSetMDUper);
	AddNode2List(listCeLiangLiangCeng,(DLinkListNode*)ListShowSetMDFloor);
	AddNode2List(listCeLiangLiangCeng,(DLinkListNode*)ListShowSetWDUper);
	AddNode2List(listCeLiangLiangCeng,(DLinkListNode*)ListShowSetWDFloor);
	
	
	ViewStr*  ViewLLSetMeasureDir  = MD_ByteCreatViewMenuSelec(" LLSetMeasureDir "," 流量测量方向设置 ",arrayLLSetMeasureDir,(u32*)&(rspHoldREGDatBuf.Direction));	
	
	ListShowStr*  ListShowLittleNumCut = CreatListShowValu(" LittleNumCut "," 小信号切除值 ",&(rspHoldREGDatBuf.FlowGate));
	ListShowStr*  ListShowLLXianXingTiaoZheng = CreatListShowValu(" LLXianXingTiaoZheng "," 流量测量线性调整 ",&(rspHoldREGDatBuf.LLXianXingTiaoZheng));
	ListShowStr*  ListShowLLZeroAuto = CreatListShowValu(" LLZeroAutoTiaoZheng "," 流量自动零点调整 ",&(rspHoldREGDatBuf.MassAdjust));
	ListShowStr*  ListShowLLXieLvTiaoZheng= CreatListShowValu("LLXieLvTiaoZheng "," 流量测量斜率调整 ",&(rspHoldREGDatBuf.MassSlope));
	ListShowStr*  ListShowLLZeroTiaoZheng  = CreatListShowValu(" LLZeroTiaoZheng "," 流量测量零点调整 ",&(rspHoldREGDatBuf.MassZero));
	ListShowStr*  ListShowLLZuNiTiaoZheng = CreatListShowValu(" LLZuNiTiaoZheng "," 流量测量阻尼调整 ",&(rspHoldREGDatBuf.MassDamp));
	ListShowStr*  ListShowYaLiXiShuSet = CreatListShowValu(" YaLiXiShuSet "," 压力系数设置 ",&(rspHoldREGDatBuf.TempDefault));	
	
	AddNode2List(listLLTiaoZhengCanShu,(DLinkListNode*)ViewExitMenu8);
	AddNode2List(listLLTiaoZhengCanShu,(DLinkListNode*)ListShowLittleNumCut);
	AddNode2List(listLLTiaoZhengCanShu,(DLinkListNode*)ViewLLSetMeasureDir);
	AddNode2List(listLLTiaoZhengCanShu,(DLinkListNode*)ListShowLLXianXingTiaoZheng);
	AddNode2List(listLLTiaoZhengCanShu,(DLinkListNode*)ListShowLLZeroAuto);
	AddNode2List(listLLTiaoZhengCanShu,(DLinkListNode*)ListShowLLXieLvTiaoZheng);
	AddNode2List(listLLTiaoZhengCanShu,(DLinkListNode*)ListShowLLZeroTiaoZheng);
	AddNode2List(listLLTiaoZhengCanShu,(DLinkListNode*)ListShowLLZuNiTiaoZheng);
	AddNode2List(listLLTiaoZhengCanShu,(DLinkListNode*)ListShowYaLiXiShuSet);	

	ListShowStr*  ListShowMDXieLvTiaoZheng = CreatListShowValu(" MDXieLvTiaoZheng "," 密度测量斜率调整 ",&(rspHoldREGDatBuf.DensSlope));
	ListShowStr*  ListShowMDZeroTiaoZheng= CreatListShowValu("MDZeroTiaoZheng "," 密度测量零点调整 ",&(rspHoldREGDatBuf.DensZero));
	ListShowStr*  ListShowMDZuNiTiaoZheng  = CreatListShowValu(" MDZuNiTiaoZheng "," 密度测量阻尼调整 ",&(rspHoldREGDatBuf.DensDamp));
	ListShowStr*  ListShowMDCanKaoSet = CreatListShowValu(" MDCanKaoSet "," 参考密度值设置 ",&(rspHoldREGDatBuf.DensDefault));
	ListShowStr*  ListShowWDXieLvTiaoZheng = CreatListShowValu(" WDXieLvTiaoZheng "," 温度测量斜率调整 ",&(rspHoldREGDatBuf.TempSlope));	
	ListShowStr*  ListShowWDZeroTiaoZheng= CreatListShowValu("WDZeroTiaoZheng "," 温度测量零点调整 ",&(rspHoldREGDatBuf.TempZero));
	ListShowStr*  ListShowWDZuNiTiaoZheng  = CreatListShowValu(" WDZuNiTiaoZheng "," 温度测量阻尼调整 ",&(rspHoldREGDatBuf.TempDamp));
	ListShowStr*  ListShowWDComSet = CreatListShowValu(" WDComSet "," 常用温度值设置 ",&(rspHoldREGDatBuf.PressDefault));
	AddNode2List(listQTTiaoZhengCanShu,(DLinkListNode*)ViewExitMenu9);	
	AddNode2List(listQTTiaoZhengCanShu,(DLinkListNode*)ListShowMDXieLvTiaoZheng);
	AddNode2List(listQTTiaoZhengCanShu,(DLinkListNode*)ListShowMDZeroTiaoZheng);
	AddNode2List(listQTTiaoZhengCanShu,(DLinkListNode*)ListShowMDZuNiTiaoZheng);
	AddNode2List(listQTTiaoZhengCanShu,(DLinkListNode*)ListShowMDCanKaoSet);
	AddNode2List(listQTTiaoZhengCanShu,(DLinkListNode*)ListShowWDXieLvTiaoZheng);
	AddNode2List(listQTTiaoZhengCanShu,(DLinkListNode*)ListShowWDZeroTiaoZheng);
	AddNode2List(listQTTiaoZhengCanShu,(DLinkListNode*)ListShowWDZuNiTiaoZheng);
	AddNode2List(listQTTiaoZhengCanShu,(DLinkListNode*)ListShowWDComSet);

	ViewStr*  viewInstantZLLL = CreatViewSaveFlaseSelec(" InstantZLLL "," 瞬时质量流量 ",arraySelectShowForm,&showNature.Resolution_InstantZLLL);
	ViewStr*  viewAddUpZLLL = CreatViewSaveFlaseSelec(" AddUpZLLL "," 累计质量流量 ",arraySelectShowForm,&showNature.Resolution_AddUpZLLL);
	ViewStr*  viewInstantTJLL = CreatViewSaveFlaseSelec(" InstantTJLL "," 瞬时体积流量 ",arraySelectShowForm,&showNature.Resolution_InstantTJLL);
	ViewStr*  viewAddUpTJLL = CreatViewSaveFlaseSelec(" AddUpTJLL "," 累计体积流量 ",arraySelectShowForm,&showNature.Resolution_AddUpTJLL);
	ViewStr*  viewMediumDensity = CreatViewSaveFlaseSelec(" MediumDensity "," 介质密度 ",arraySelectShowForm,&showNature.Resolution_MediumDensity);	
	AddNode2List(listResolution,(DLinkListNode*)ViewExitMenu10);
	AddNode2List(listResolution,(DLinkListNode*)viewInstantZLLL);
	AddNode2List(listResolution,(DLinkListNode*)viewAddUpZLLL);
	AddNode2List(listResolution,(DLinkListNode*)viewInstantTJLL);
	AddNode2List(listResolution,(DLinkListNode*)viewAddUpTJLL);
	AddNode2List(listResolution,(DLinkListNode*)viewMediumDensity);		
	
	ViewStr*  ViewSelectOutputSignal  = CreatViewSaveFlaseSelec(" SelectOutputSignal "," 输出信号选择 ",arrySelectOutputSignal1,(u32*)&showNature.signalSelect1);
	ViewStr*  ViewSetFreUper  = CreatViewSaveFlaseValu(" SetFreUper "," 输出频率上限设置 ",(u32*)&showNature.FreUper);
	AddNode2List(listMaiChongShuChu1,(DLinkListNode*)ViewExitMenu11);
	AddNode2List(listMaiChongShuChu1,(DLinkListNode*)ViewSelectOutputSignal);
	AddNode2List(listMaiChongShuChu1,(DLinkListNode*)ViewSetFreUper);
	
	ViewStr*  ViewSelectOutputSignal2  = CreatViewSaveFlaseSelec(" SelectOutputSignal "," 输出信号选择 ",arrySelectOutputSignal1,(u32*)&showNature.signalSelect2);
	ViewStr*  ViewSetPulesEqu  = CreatViewMenuValu(" SetPulesEqu "," 脉冲当量设置 ",&(rspHoldREGDatBuf.PulseValue));
	ViewStr*  ViewSetPulesWith  = CreatViewSaveFlaseValu(" SetPulesWith "," 脉宽设置 ",(u32*)&showNature.PulesWith);
	AddNode2List(listMaiChongShuChu2,(DLinkListNode*)ViewExitMenu12);
	AddNode2List(listMaiChongShuChu2,(DLinkListNode*)ViewSelectOutputSignal2);
	AddNode2List(listMaiChongShuChu2,(DLinkListNode*)ViewSetPulesEqu);
	AddNode2List(listMaiChongShuChu2,(DLinkListNode*)ViewSetPulesWith);

	ViewStr*  ViewSelectControlPar  = CreatViewSaveFlaseSelec(" SelectControlPar "," 选择控制参数 ",arrySelectControlPar,(u32*)&showNature.SelectControlPar);
	ViewStr*  ViewValidControlForm  = CreatViewSaveFlaseSelec(" ValidControlForm "," 有效控制形式 ",arryValidControlForm,(u32*)&showNature.ValidControlForm);
	AddNode2List(listInControlSet,(DLinkListNode*)ViewExitMenu13);
	AddNode2List(listInControlSet,(DLinkListNode*)ViewSelectControlPar);
	AddNode2List(listInControlSet,(DLinkListNode*)ViewValidControlForm);

	ViewStr*  ViewSetPassWord  = CreatViewSaveFlaseValu(" PassWord "," 用户密码设置 ",(u32*)&showNature.PassWord);
	AddNode2List(listPassWord,(DLinkListNode*)ViewExitMenu14);
	AddNode2List(listPassWord,(DLinkListNode*)ViewSetPassWord);
/**************************************添加四级菜单**********************************************************/	
	ViewStr*  ViewSetingFC = CreatViewMenuValu(" SetingFC "," 流量系数FC ",&(rspHoldREGDatBuf.MassFlowK));//
	ViewStr*  ViewSetingFT = CreatViewMenuValu(" SetingFT "," 流量温度系数FT ",&(rspHoldREGDatBuf.MassCT));
	ViewStr*  ViewSetingK1 = CreatViewMenuValu(" SetingK1 "," 密度系数K1 ",&(rspHoldREGDatBuf.DensityK1));
	ViewStr*  ViewSetingK2 = CreatViewMenuValu(" SetingK2 "," 密度系数K2 ",&(rspHoldREGDatBuf.DensityK2));
	ViewStr*  ViewSetingDT = CreatViewMenuValu(" SetingDT "," 密度温度系数DT ",&(rspHoldREGDatBuf.DensityFD));
	ViewStr*  ViewSetingFD = CreatViewMenuValu(" SetingFD "," 密度流速系数FD ",&(rspHoldREGDatBuf.DensFT));	
	AddNode2List((ListStr*)ListShowSttingFC,(DLinkListNode*)ViewExitMenu15);	
	AddNode2List((ListStr*)ListShowSettingFT,(DLinkListNode*)ViewExitMenu16);
	AddNode2List((ListStr*)ListShowSettingK1,(DLinkListNode*)ViewExitMenu17);
	AddNode2List((ListStr*)ListShowSettingK2,(DLinkListNode*)ViewExitMenu18);
	AddNode2List((ListStr*)ListShowSettingDT,(DLinkListNode*)ViewExitMenu19);
	AddNode2List((ListStr*)ListShowSettingFD,(DLinkListNode*)ViewExitMenu20);
	AddNode2List((ListStr*)ListShowSttingFC,(DLinkListNode*)ViewSetingFC);
	AddNode2List((ListStr*)ListShowSettingFT,(DLinkListNode*)ViewSetingFT);
	AddNode2List((ListStr*)ListShowSettingK1,(DLinkListNode*)ViewSetingK1);
	AddNode2List((ListStr*)ListShowSettingK2,(DLinkListNode*)ViewSetingK2);
	AddNode2List((ListStr*)ListShowSettingDT,(DLinkListNode*)ViewSetingDT);
	AddNode2List((ListStr*)ListShowSettingFD,(DLinkListNode*)ViewSetingFD);
	
	ViewStr*  ViewSetZLUper = CreatViewMenuValu(" SetZLUper "," 质量流量上限 ",&(rspHoldREGDatBuf.MaxMass));
	ViewStr*  ViewSetZLFloor  = CreatViewMenuValu(" SetZLFloor "," 质量流量下限 ",&(rspHoldREGDatBuf.MinMass));
	ViewStr*  ViewSetTJUper = CreatViewMenuValu(" SetTJUper "," 体积流量上限 ",&(rspHoldREGDatBuf.MaxVolu));
	ViewStr*  ViewSetTJFloor = CreatViewMenuValu(" SetTJFloor "," 体积流量下限 ",&(rspHoldREGDatBuf.MinVolu));
	ViewStr*  ViewSetMDUper = CreatViewMenuValu(" SetMDUper "," 密度测量上限 ",&(rspHoldREGDatBuf.MaxDens));
	ViewStr*  ViewSetMDFloor  = CreatViewMenuValu(" SetMDFloor "," 密度测量下限 ",&(rspHoldREGDatBuf.MinDens));
	ViewStr*  ViewSetWDUper = CreatViewMenuValu(" SetWDUper "," 温度测量上限 ",&(rspHoldREGDatBuf.MaxTemp));
	ViewStr*  ViewSetWDFloor = CreatViewMenuValu(" SetWDFloor "," 温度测量下限 ",&(rspHoldREGDatBuf.MinTemp));
	AddNode2List((ListStr*)ListShowSetZLUper,(DLinkListNode*)ViewExitMenu21);	
	AddNode2List((ListStr*)ListShowSetZLFloor,(DLinkListNode*)ViewExitMenu22);
	AddNode2List((ListStr*)ListShowSetTJUper,(DLinkListNode*)ViewExitMenu23);
	AddNode2List((ListStr*)ListShowSetTJFloor,(DLinkListNode*)ViewExitMenu24);
	AddNode2List((ListStr*)ListShowSetMDUper,(DLinkListNode*)ViewExitMenu25);
	AddNode2List((ListStr*)ListShowSetMDFloor,(DLinkListNode*)ViewExitMenu26);	
	AddNode2List((ListStr*)ListShowSetWDUper,(DLinkListNode*)ViewExitMenu27);
	AddNode2List((ListStr*)ListShowSetWDFloor,(DLinkListNode*)ViewExitMenu28);	
	AddNode2List((ListStr*)ListShowSetZLUper,(DLinkListNode*)ViewSetZLUper);
	AddNode2List((ListStr*)ListShowSetZLFloor,(DLinkListNode*)ViewSetZLFloor);
	AddNode2List((ListStr*)ListShowSetTJUper,(DLinkListNode*)ViewSetTJUper);
	AddNode2List((ListStr*)ListShowSetTJFloor,(DLinkListNode*)ViewSetTJFloor);
	AddNode2List((ListStr*)ListShowSetMDUper,(DLinkListNode*)ViewSetMDUper);
	AddNode2List((ListStr*)ListShowSetMDFloor,(DLinkListNode*)ViewSetMDFloor);
	AddNode2List((ListStr*)ListShowSetWDUper,(DLinkListNode*)ViewSetWDUper);
	AddNode2List((ListStr*)ListShowSetWDFloor,(DLinkListNode*)ViewSetWDFloor);

	ViewStr*  ViewLittleNumCut = CreatViewMenuValu(" LittleNumCut "," 小信号切除值 ",&(rspHoldREGDatBuf.FlowGate));
	ViewStr*  ViewLLXianXingTiaoZheng = CreatViewMenuValu(" LLXianXingTiaoZheng "," 流量测量线性调整 ",&(rspHoldREGDatBuf.LLXianXingTiaoZheng));
	ViewStr*  ViewLLZeroAuto = CreatViewMenuValu(" LLZeroAutoTiaoZheng "," 流量自动零点调整 ",&(rspHoldREGDatBuf.MassAdjust));
	ViewStr*  ViewLLXieLvTiaoZheng= CreatViewMenuValu("LLXieLvTiaoZheng "," 流量测量斜率调整 ",&(rspHoldREGDatBuf.MassSlope));
	ViewStr*  ViewLLZeroTiaoZheng  = CreatViewMenuValu(" LLZeroTiaoZheng "," 流量测量零点调整 ",&(rspHoldREGDatBuf.MassZero));
	ViewStr*  ViewLLZuNiTiaoZheng = CreatViewMenuValu(" LLZuNiTiaoZheng "," 流量测量阻尼调整 ",&(rspHoldREGDatBuf.MassDamp));
	ViewStr*  ViewYaLiXiShuSet = CreatViewMenuValu(" YaLiXiShuSet "," 压力系数设置 ",&(rspHoldREGDatBuf.TempDefault));	
	AddNode2List((ListStr*)ListShowLittleNumCut,(DLinkListNode*)ViewExitMenu29);	
	AddNode2List((ListStr*)ListShowLLXianXingTiaoZheng,(DLinkListNode*)ViewExitMenu30);
	AddNode2List((ListStr*)ListShowSetTJUper,(DLinkListNode*)ViewExitMenu31);
	AddNode2List((ListStr*)ListShowSetTJFloor,(DLinkListNode*)ViewExitMenu32);
	AddNode2List((ListStr*)ListShowSetMDUper,(DLinkListNode*)ViewExitMenu33);
	AddNode2List((ListStr*)ListShowSetMDFloor,(DLinkListNode*)ViewExitMenu34);	
	AddNode2List((ListStr*)ListShowSetWDUper,(DLinkListNode*)ViewExitMenu35);
	AddNode2List((ListStr*)ListShowLittleNumCut,(DLinkListNode*)ViewLittleNumCut);
	AddNode2List((ListStr*)ListShowLLXianXingTiaoZheng,(DLinkListNode*)ViewLLXianXingTiaoZheng);
	AddNode2List((ListStr*)ListShowLLZeroAuto,(DLinkListNode*)ViewLLZeroAuto);
	AddNode2List((ListStr*)ListShowLLXieLvTiaoZheng,(DLinkListNode*)ViewLLXieLvTiaoZheng);
	AddNode2List((ListStr*)ListShowLLZeroTiaoZheng,(DLinkListNode*)ViewLLZeroTiaoZheng);
	AddNode2List((ListStr*)ListShowLLZuNiTiaoZheng,(DLinkListNode*)ViewLLZuNiTiaoZheng);
	AddNode2List((ListStr*)ListShowYaLiXiShuSet,(DLinkListNode*)ViewYaLiXiShuSet);	
	
	ViewStr*  ViewMDXieLvTiaoZheng = CreatViewMenuValu(" MDXieLvTiaoZheng "," 密度测量斜率调整 ",&(rspHoldREGDatBuf.DensSlope));
	ViewStr*  ViewMDZeroTiaoZheng= CreatViewMenuValu("MDZeroTiaoZheng "," 密度测量零点调整 ",&(rspHoldREGDatBuf.DensZero));
	ViewStr*  ViewMDZuNiTiaoZheng  = CreatViewMenuValu(" MDZuNiTiaoZheng "," 密度测量阻尼调整 ",&(rspHoldREGDatBuf.DensDamp));
	ViewStr*  ViewMDCanKaoSet = CreatViewMenuValu(" MDCanKaoSet "," 参考密度值设置 ",&(rspHoldREGDatBuf.DensDefault));
	ViewStr*  ViewWDXieLvTiaoZheng = CreatViewMenuValu(" WDXieLvTiaoZheng "," 温度测量斜率调整 ",&(rspHoldREGDatBuf.TempSlope));	
	ViewStr*  ViewWDZeroTiaoZheng= CreatViewMenuValu("WDZeroTiaoZheng "," 温度测量零点调整 ",&(rspHoldREGDatBuf.TempZero));
	ViewStr*  ViewWDZuNiTiaoZheng  = CreatViewMenuValu(" WDZuNiTiaoZheng "," 温度测量阻尼调整 ",&(rspHoldREGDatBuf.TempDamp));
	ViewStr*  ViewWDComSet = CreatViewMenuValu(" WDComSet "," 常用温度值设置 ",&(rspHoldREGDatBuf.PressDefault));
	
	AddNode2List((ListStr*)ListShowMDXieLvTiaoZheng,(DLinkListNode*)ViewExitMenu36);	
	AddNode2List((ListStr*)ListShowMDZeroTiaoZheng,(DLinkListNode*)ViewExitMenu37);
	AddNode2List((ListStr*)ListShowMDZuNiTiaoZheng,(DLinkListNode*)ViewExitMenu38);
	AddNode2List((ListStr*)ListShowWDXieLvTiaoZheng,(DLinkListNode*)ViewExitMenu39);
	AddNode2List((ListStr*)ListShowWDZeroTiaoZheng,(DLinkListNode*)ViewExitMenu40);
	AddNode2List((ListStr*)ListShowWDZuNiTiaoZheng,(DLinkListNode*)ViewExitMenu41);	
	AddNode2List((ListStr*)ListShowWDComSet,(DLinkListNode*)ViewExitMenu42);
	
	AddNode2List((ListStr*)ListShowMDXieLvTiaoZheng,(DLinkListNode*)ViewMDXieLvTiaoZheng);
	AddNode2List((ListStr*)ListShowMDZeroTiaoZheng,(DLinkListNode*)ViewMDZeroTiaoZheng);
	AddNode2List((ListStr*)ListShowMDZuNiTiaoZheng,(DLinkListNode*)ViewMDZuNiTiaoZheng);
	AddNode2List((ListStr*)ListShowMDCanKaoSet,(DLinkListNode*)ViewMDCanKaoSet);
	AddNode2List((ListStr*)ListShowWDXieLvTiaoZheng,(DLinkListNode*)ViewWDXieLvTiaoZheng);
	AddNode2List((ListStr*)ListShowWDZeroTiaoZheng,(DLinkListNode*)ViewWDZeroTiaoZheng);
	AddNode2List((ListStr*)ListShowWDZuNiTiaoZheng,(DLinkListNode*)ViewWDZuNiTiaoZheng);
	AddNode2List((ListStr*)ListShowWDComSet,(DLinkListNode*)ViewWDComSet);

}

