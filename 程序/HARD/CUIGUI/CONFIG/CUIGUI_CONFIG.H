/******************************************************************
*文件名:CUIGUI配置文件
*创建者:博硕电子科技，www.explorersoftware.taobao.com
*创建时间:2017年6月28日09:57:36
*文件说明:基于CUIGUI，适应各种屏需要配置更改的函数
*/

#ifndef  __CUIGUI_CONFIG_H  
#define  __CUIGUI_CONFIG_H

/*支持BMP格式*/
#define     USE_BMP           0           //使用位图

/*支持字体*/
#define     USE_FONT          1           //使用字体


/*设置保存句柄的最大数组*/
#define     HWIN_MAX          50   //句柄的最大数组

/*颜色配置*/

#define     COLOR_DATTYPE     u8          //定义颜色的数据类型
//定义颜色的数据类型
//typedef	enum{
//	COLOR_INVERSE	=0		,	//反白显示
//	COLOR_NORMAL			,	//正常打点
//	COLOR_CLEAR				,	//清除显示
//	COLOR_FLOOR				,	//与底相与显示
//}COLOR_DATTYPE;

#define     LCD_NUM_COLORS    2       `   //颜色数


#endif
