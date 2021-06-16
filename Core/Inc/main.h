/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MOTOR_L_B_Pin GPIO_PIN_2
#define MOTOR_L_B_GPIO_Port GPIOE
#define LED_Pin GPIO_PIN_3
#define LED_GPIO_Port GPIOE
#define KEY_Pin GPIO_PIN_13
#define KEY_GPIO_Port GPIOC
#define DISTANCE_TOP_ECHO_Pin GPIO_PIN_4
#define DISTANCE_TOP_ECHO_GPIO_Port GPIOC
#define DISTANCE_TOP_ECHO_EXTI_IRQn EXTI4_IRQn
#define DISTANCE_TOP_TRIG_Pin GPIO_PIN_5
#define DISTANCE_TOP_TRIG_GPIO_Port GPIOC
#define MOTOR_PWM_R_Pin GPIO_PIN_0
#define MOTOR_PWM_R_GPIO_Port GPIOB
#define DISTANCE_LEFT_ECHO_Pin GPIO_PIN_1
#define DISTANCE_LEFT_ECHO_GPIO_Port GPIOB
#define DISTANCE_LEFT_ECHO_EXTI_IRQn EXTI1_IRQn
#define DISTANCE_LEFT_TRIG_Pin GPIO_PIN_2
#define DISTANCE_LEFT_TRIG_GPIO_Port GPIOB
#define LCD_BRIGHT_Pin GPIO_PIN_10
#define LCD_BRIGHT_GPIO_Port GPIOE
#define LCD_CS_Pin GPIO_PIN_11
#define LCD_CS_GPIO_Port GPIOE
#define LCD_SPI_SCK_Pin GPIO_PIN_12
#define LCD_SPI_SCK_GPIO_Port GPIOE
#define LCD_WR_RS_Pin GPIO_PIN_13
#define LCD_WR_RS_GPIO_Port GPIOE
#define LCD_SPI_MOSI_Pin GPIO_PIN_14
#define LCD_SPI_MOSI_GPIO_Port GPIOE
#define COLOR_INT_Pin GPIO_PIN_15
#define COLOR_INT_GPIO_Port GPIOE
#define COLOR_INT_EXTI_IRQn EXTI15_10_IRQn
#define COLOR_SCL_Pin GPIO_PIN_10
#define COLOR_SCL_GPIO_Port GPIOB
#define COLOR_SDA_Pin GPIO_PIN_11
#define COLOR_SDA_GPIO_Port GPIOB
#define ANGLE_RX_Pin GPIO_PIN_12
#define ANGLE_RX_GPIO_Port GPIOB
#define ANGLE_TX_Pin GPIO_PIN_13
#define ANGLE_TX_GPIO_Port GPIOB
#define DEBUG_TX_Pin GPIO_PIN_14
#define DEBUG_TX_GPIO_Port GPIOB
#define DEBUG_RX_Pin GPIO_PIN_15
#define DEBUG_RX_GPIO_Port GPIOB
#define HC12_TX_Pin GPIO_PIN_8
#define HC12_TX_GPIO_Port GPIOD
#define HC12_RX_Pin GPIO_PIN_9
#define HC12_RX_GPIO_Port GPIOD
#define DISTANCE_FRONT_ECHO_Pin GPIO_PIN_10
#define DISTANCE_FRONT_ECHO_GPIO_Port GPIOD
#define DISTANCE_FRONT_ECHO_EXTI_IRQn EXTI15_10_IRQn
#define DISTANCE_FRONT_TRIG_Pin GPIO_PIN_11
#define DISTANCE_FRONT_TRIG_GPIO_Port GPIOD
#define DISTANCE_RIGHT_ECHO_Pin GPIO_PIN_8
#define DISTANCE_RIGHT_ECHO_GPIO_Port GPIOC
#define DISTANCE_RIGHT_ECHO_EXTI_IRQn EXTI9_5_IRQn
#define DISTANCE_RIGHT_TRIG_Pin GPIO_PIN_9
#define DISTANCE_RIGHT_TRIG_GPIO_Port GPIOC
#define MOTOR_L_F_Pin GPIO_PIN_12
#define MOTOR_L_F_GPIO_Port GPIOC
#define CLOCK_RST_Pin GPIO_PIN_0
#define CLOCK_RST_GPIO_Port GPIOD
#define MOTOR_R_B_Pin GPIO_PIN_1
#define MOTOR_R_B_GPIO_Port GPIOD
#define CLOCK_DAT_Pin GPIO_PIN_2
#define CLOCK_DAT_GPIO_Port GPIOD
#define CLOCK_CLK_Pin GPIO_PIN_4
#define CLOCK_CLK_GPIO_Port GPIOD
#define MOTOR_PWM_L_Pin GPIO_PIN_5
#define MOTOR_PWM_L_GPIO_Port GPIOB
#define MOTOR_R_F_Pin GPIO_PIN_6
#define MOTOR_R_F_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
#define FrameWidth 72
#define FrameHeight 54

#define BUFFER_D1 __attribute__ ((section(".buffers"), used))
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
