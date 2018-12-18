#ifndef __KEYSCAN_TASK_H
#define	__KEYSCAN_TASK_H
#include "UHEAD.H"

#define		BUTTON_ENTER_VAL	0x0001		//ENTER¼üÖµ
#define		BUTTON_NEXT_VAL		0x0002		//NEXT¼üÖµ

#define	LED_ENTER		LED_ENTER_GPIO_Port,LED_ENTER_Pin
#define	LED_NEXT		LED_NEXT_GPIO_Port,LED_NEXT_Pin
#define	LED_485			LED_485_GPIO_Port,LED_485_Pin

#define	LIGHTEN_LED(a)		HAL_GPIO_WritePin(a,GPIO_PIN_RESET)
#define	QUENCH_LED(a)			HAL_GPIO_WritePin(a,GPIO_PIN_SET)

extern u8 key_val;

#endif
