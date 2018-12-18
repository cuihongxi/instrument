// Header:		
// File Name: 
// Author:		
// Date:		2018年8月11日18:33:54

#ifndef		__MENU_H
#define		__MENU_H

#include "uhead.h"
#include "DLinkList.h"

#define	NO_INIT			0
#define	IS_INIT			1
#define	NOT_REVIEW 		0
#define	NEED_REVIEW 	1

///////////////定义显示界面结构体////////////
typedef struct Show_Str ShowStr;
typedef	enum{
	ENGLISH ,
	CHINESE
}languageEnum;

typedef	enum{
	List,			//列表属性
	View,			//视图属性
}natureEnum;



//MENU属性结构体
typedef struct{
	TDLinkList circle;	
	natureEnum showNature ;						//属性
	const char* title_E ;							//标题英文
	const char* title_C;							//标题中文
	void(*pShow)(ShowStr*);						//显示函数
	void(*pSkan)(ShowStr*);						//扫描按键	
}NatureStr;


typedef	enum{
	Select,				//选项
	Value,				//值调整
}ViewForm;



//视图结构体
typedef struct{
	NatureStr nature;	
	u32* parameter;										//仪表参数保存的地址
	const char** strList;							//字符串表
	u8 sizeStrList;										//保存字符串的长度
	
}ViewStr;

//列表结构体
typedef struct{
	NatureStr nature;	
	DLinkList*	ChildList;						//子列表
}ListStr;

//显示列表结构体
typedef struct{
	ListStr list;
	u32* parameter;
}ListShowStr;

typedef	enum{
	signal_SSZLLL,
	signal_SSTJLL,
	signal_density,
	signal_temp
}exnumSignalSelect1;		//输出信号选择1

typedef	enum{
	signal_ZLLL,
	signal_TJLL
}exnumSignalSelect2;		//输出信号选择2 :质量流量,体积流量

typedef	enum{
	Baud_1200,
	Baud_9600,
	Baud_19200,
	Baud_38400,
	Baud_57600,
	Baud_115200
}exnumBaud;		//通讯波特率

typedef	enum{
drive_1,drive_2,drive_3,drive_4,drive_5
}exnumQudongFudu;		//驱动幅度调整

typedef	enum{
_NO,_YES
}exnumYesNo;			//是或否选择

typedef enum{
	HIGH,
	LOW,
}enumControlForm;
//显示属性
struct Show_Str{

	u8 flag_init;										//是否被初始化
	u8 flag_review;									//用在keyscan重画	
	NatureStr* thisNature;					//指向当前的列表
	//相关参数
	languageEnum Language;					//语言选择	
	u32 Resolution_InstantZLLL;			//分辨率-瞬时质量流量
	u32 Resolution_AddUpZLLL;				//分辨率-累计质量流量
	u32 Resolution_InstantTJLL;			//分辨率-瞬时体积流量		
	u32 Resolution_AddUpTJLL;				//分辨率-累计体积流量
	u32 Resolution_MediumDensity;		//分辨率-介质密度
	u32 FreUper;										//输出频率上限
	u32 PulesWith;									//脉宽
	u32	Interface;									//默认界面选择
	u32 signalSelect1;							//输出信号选择1
	u32 signalSelect2;							//输出信号选择2
	u32 baud;												//通讯波特率
	u32 MailAddr;										//通讯地址
	u32 SelectControlPar;						//选择控制参数
	enumControlForm ValidControlForm;	//有效控制形式
	u32 quDongFudu;									//驱动幅度调整
	u32 PassWord;										//用户密码
	/***************以下不能确定是否保存***********************/
	u32 ZeroResize;
	u32 ClearCumulants;	
	
};

/*函数*/
ViewStr* CreatView_MenuSelec(const char* titleE,const char* titleC,const char** strList,u8 sizeStrList,u32* parameter);//创建一个视图,选择参数
#define	CreatViewMenuSelec(titleE,titleC,strList,parameter) \
	CreatView_MenuSelec(titleE,titleC,strList,GETSIZE(strList),parameter)
ViewStr* MD_ByteCreatView_MenuSelec(const char* titleE,const char* titleC,const char** strList,u8 sizeStrList,u32* parameter);
#define	MD_ByteCreatViewMenuSelec(titleE,titleC,strList,parameter) \
	MD_ByteCreatView_MenuSelec(titleE,titleC,strList,GETSIZE(strList),parameter)
ViewStr* CreatViewMenuValu(const char* titleE,const char* titleC,u32* parameter);
ListStr* CreatListMenu(const char* titleE,const char* titleC);//创建列表

ViewStr* CreatViewSaveFlaseValu(const char* titleE,const char* titleC,u32* parameter);//创建一个视图,调整参数后EEPROM保存
ViewStr* CreatView_SaveFlaseSelec(const char* titleE,const char* titleC,const char** strList,u8 sizeStrList,u32* parameter);
#define	CreatViewSaveFlaseSelec(titleE,titleC,strList,parameter) \
	CreatView_SaveFlaseSelec(titleE,titleC,strList,GETSIZE(strList),parameter)

void AddNode2List(ListStr*  list, DLinkListNode*  node);//添加视图到列表
void DeleNodeFromList(ListStr*  list, DLinkListNode*  node);//从列表中删除节点
void ShowListMenu(ShowStr* showStr);//显示当前列表
void MenuKeyScan(ShowStr* showStr);
void ReturnFatherList(ShowStr* showStr);//返回父链表
void ReturnGrandFatherList(ShowStr* showStr);//返回爷爷链表
void View_ValueKeyScan(ShowStr* showStr);	//视图值调整的按键扫描
void View_SelectKeyScan(ShowStr* showStr);//视图选项按键扫描
void MDView_ValueShow(ShowStr* showStr);		//视图值调整的显示,从MD中读,修改后发送到MD
void View_SelectShow(ShowStr* showStr);			//视图选项的显示
void View_FlashValueShow(ShowStr* showStr);//视图值调整的显示,flash保存
void View_FlashSelectShow(ShowStr* showStr);//视图选项的调整,flash保存

ViewStr* CreatViewMenuExit(const char* title_E,const char* title_C);	//创建EXIT菜单
ListShowStr* CreatListShowValu(const char* titleE,const char* titleC,u32* parameter);	//创建一个视图,显示参数




#endif

