/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define AD7147_INT_Pin GPIO_PIN_13
#define AD7147_INT_GPIO_Port GPIOC
#define AD7147_INT_EXTI_IRQn EXTI15_10_IRQn
#define T2_OUT3_Pin GPIO_PIN_0
#define T2_OUT3_GPIO_Port GPIOA
#define T2_OUT2_Pin GPIO_PIN_1
#define T2_OUT2_GPIO_Port GPIOA
#define ALARM_LED_R_Pin GPIO_PIN_5
#define ALARM_LED_R_GPIO_Port GPIOA
#define ALARM_LED_G_Pin GPIO_PIN_7
#define ALARM_LED_G_GPIO_Port GPIOA
#define INPUT1_Pin GPIO_PIN_0
#define INPUT1_GPIO_Port GPIOB
#define INPUT2_Pin GPIO_PIN_1
#define INPUT2_GPIO_Port GPIOB
#define LED_NEXT_Pin GPIO_PIN_2
#define LED_NEXT_GPIO_Port GPIOB
#define AD5662_DIN_Pin GPIO_PIN_10
#define AD5662_DIN_GPIO_Port GPIOB
#define OLED_RES_Pin GPIO_PIN_12
#define OLED_RES_GPIO_Port GPIOB
#define OLED_CLK_Pin GPIO_PIN_13
#define OLED_CLK_GPIO_Port GPIOB
#define OLED_DC_Pin GPIO_PIN_14
#define OLED_DC_GPIO_Port GPIOB
#define OLED_DATO_Pin GPIO_PIN_15
#define OLED_DATO_GPIO_Port GPIOB
#define T1_OUT1_Pin GPIO_PIN_8
#define T1_OUT1_GPIO_Port GPIOA
#define LED_ENTER_Pin GPIO_PIN_11
#define LED_ENTER_GPIO_Port GPIOA
#define LED_485_Pin GPIO_PIN_12
#define LED_485_GPIO_Port GPIOA
#define AD7147_CS_Pin GPIO_PIN_15
#define AD7147_CS_GPIO_Port GPIOA
#define AD7147_CLK_Pin GPIO_PIN_3
#define AD7147_CLK_GPIO_Port GPIOB
#define AD7147_SDO_Pin GPIO_PIN_4
#define AD7147_SDO_GPIO_Port GPIOB
#define AD7147_SDI_Pin GPIO_PIN_5
#define AD7147_SDI_GPIO_Port GPIOB
#define POWER_INT_Pin GPIO_PIN_6
#define POWER_INT_GPIO_Port GPIOB
#define WATCHDOG_Pin GPIO_PIN_7
#define WATCHDOG_GPIO_Port GPIOB
#define AD5662_SYNC_Pin GPIO_PIN_8
#define AD5662_SYNC_GPIO_Port GPIOB
#define AD5662_SCK_Pin GPIO_PIN_9
#define AD5662_SCK_GPIO_Port GPIOB

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */



#define	AD7147_INT		AD7147_INT_GPIO_Port,AD7147_INT_Pin
#define	ALARM_LED_G		ALARM_LED_G_GPIO_Port,ALARM_LED_G_Pin
#define	ALARM_LED_R		ALARM_LED_R_GPIO_Port,ALARM_LED_R_Pin




/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
