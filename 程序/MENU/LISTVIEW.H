// Header:	所有的列表项都在这里添加
// File Name: 
// Author:
// Date: 2018年8月11日22:47:20


#ifndef  __LISTVIEW_H   
#define  __LISTVIEW_H 

#include "uhead.h"
#include "menu.h"


extern ViewStr*  ViewExitMenu;
extern ViewStr*  ViewExitConfig;
extern ListStr*  MainMenu;
/*FUNCTION*/

void CreatALLListMenu(void);
void ExitMenuFun(ShowStr* showStr);
void ExitConfigShow(ShowStr* showStr );
void ExitConfigKeyScan(ShowStr* showStr );





#endif
