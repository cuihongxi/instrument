/*
*		2018年7月31日22:23:53
*		任务工程接口函数
*	使用方法：
*	① 任务填写到数组中
*	② 修改任务数TASK_NUM
*	③ Task_CreatTrave(TASK_STR* taskArray,u8 taskNum);放入创建任务的函数中
*/

#ifndef	__TASK_PROJECT_H
#define	__TASK_PROJECT_H
#include "UHEAD.H"
#include "timers.h"

/*用户自定义*/


//任务的数据类型
typedef	struct{
	TaskFunction_t 			pxTaskCode;			//任务函数名
	const char * const 		pcName;				//任务字符串名
	const uint16_t 			usStackDepth;		//分配堆栈长度
	void * const 			pvParameters;		//传递给任务函数的参数
	UBaseType_t 			uxPriority;			//任务优先级
	TaskHandle_t * const 	pxCreatedTask; 		//任务句柄
}TASK_STR;

extern  TimerHandle_t timerHandle;		//定时器句柄

//遍历创建任务
//返回0 创建成功；返回数字代表相应的任务没有创建成功
u8 Task_CreatTrave(void);
#endif
