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
  * Copyright (c) 2019 STMicroelectronics International N.V. 
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

#define D1_Pin GPIO_PIN_13
#define D1_GPIO_Port GPIOC
#define D2_Pin GPIO_PIN_14
#define D2_GPIO_Port GPIOC
#define D3_Pin GPIO_PIN_15
#define D3_GPIO_Port GPIOC
#define DCLCK_Pin GPIO_PIN_0
#define DCLCK_GPIO_Port GPIOA
#define S1_Pin GPIO_PIN_1
#define S1_GPIO_Port GPIOA
#define S2_Pin GPIO_PIN_2
#define S2_GPIO_Port GPIOA
#define S3_Pin GPIO_PIN_3
#define S3_GPIO_Port GPIOA
#define Button_Setup_Pin GPIO_PIN_4
#define Button_Setup_GPIO_Port GPIOA
#define Button_Up_Pin GPIO_PIN_5
#define Button_Up_GPIO_Port GPIOA
#define S4_Pin GPIO_PIN_6
#define S4_GPIO_Port GPIOA
#define S5_Pin GPIO_PIN_7
#define S5_GPIO_Port GPIOA
#define F3_Pin GPIO_PIN_0
#define F3_GPIO_Port GPIOB
#define F5_Pin GPIO_PIN_1
#define F5_GPIO_Port GPIOB
#define INT_IN_Pin GPIO_PIN_2
#define INT_IN_GPIO_Port GPIOB
#define IN_TX_Pin GPIO_PIN_10
#define IN_TX_GPIO_Port GPIOB
#define IN_RX_Pin GPIO_PIN_11
#define IN_RX_GPIO_Port GPIOB
#define INDEX_Pin GPIO_PIN_15
#define INDEX_GPIO_Port GPIOB
#define ENCODER_B_Pin GPIO_PIN_8
#define ENCODER_B_GPIO_Port GPIOA
#define ENCODER_A_Pin GPIO_PIN_9
#define ENCODER_A_GPIO_Port GPIOA
#define LED_POWER_Pin GPIO_PIN_10
#define LED_POWER_GPIO_Port GPIOA
#define LED_STATUS_Pin GPIO_PIN_15
#define LED_STATUS_GPIO_Port GPIOA
#define OLED_SCL_Pin GPIO_PIN_6
#define OLED_SCL_GPIO_Port GPIOB
#define OLED_SDA_Pin GPIO_PIN_7
#define OLED_SDA_GPIO_Port GPIOB
#define Button_Down_Pin GPIO_PIN_8
#define Button_Down_GPIO_Port GPIOB
#define CSYNC_Pin GPIO_PIN_9
#define CSYNC_GPIO_Port GPIOB

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */

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