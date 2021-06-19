/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention89
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "crc.h"
#include "dcmi.h"
#include "dma.h"
#include "i2c.h"
#include "lptim.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "app_x-cube-ai.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "delay.h"
#include "Color.h"
#include "DS1302.h"
#include "HCSR04.h"
#include "JY901S.h"
#include "motor.h"
#include "control.h"
#include "patio1.h"
#include "patio2.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define ANGLE_P_DATA 0.006
#define ANGLE_I_DATA 0.0000
#define ANGLE_D_DATA 0.000

//#define ANGLE_P_DATA 0.006
//#define ANGLE_I_DATA 0.00000
//#define ANGLE_D_DATA 0.000

#define DISTANCE_P_DATA 0.005
#define DISTANCE_I_DATA 0.000
#define DISTANCE_D_DATA 0.000
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
Motor_Pair_Connector motor_pair_connector = {
        MOTOR_L_F_GPIO_Port, MOTOR_L_F_Pin,
        MOTOR_L_B_GPIO_Port, MOTOR_L_B_Pin,
        MOTOR_R_F_GPIO_Port, MOTOR_R_F_Pin,
        MOTOR_R_B_GPIO_Port, MOTOR_R_B_Pin,
};

Motor_Pair motor_pair;

HCSR04_Connector hcsr04_connector_front = {
        DISTANCE_FRONT_TRIG_GPIO_Port, DISTANCE_FRONT_TRIG_Pin,
        DISTANCE_FRONT_ECHO_GPIO_Port, DISTANCE_FRONT_ECHO_Pin
};

HCSR04 hcsr04_front;

HCSR04_Connector hcsr04_connector_left = {
        DISTANCE_LEFT_TRIG_GPIO_Port, DISTANCE_LEFT_TRIG_Pin,
        DISTANCE_LEFT_ECHO_GPIO_Port, DISTANCE_LEFT_ECHO_Pin
};

HCSR04 hcsr04_left;

AngleFilterQueue angle_filter_queue = {{0}, 0, 0};

JY901S jy901s;

PID_Controller angle_pid_controller;
PID_Controller distance_pid_controller;

TCS34725 color_sensor;
COLOR_RGBC_RAW raw_buffer;
COLOR_CMYK cmyk_buffer;
COLOR_HSL hsl_buffer;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

/* Configure the peripherals common clocks */
  PeriphCommonClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_CRC_Init();
  MX_DCMI_Init();
  MX_I2C2_Init();
  MX_LPTIM1_Init();
  MX_LPTIM2_Init();
  MX_LPTIM3_Init();
  MX_LPTIM4_Init();
  MX_SPI4_Init();
  MX_TIM1_Init();
  MX_UART5_Init();
  MX_USART3_UART_Init();
  MX_I2C1_Init();
  MX_TIM16_Init();
  MX_USART1_UART_Init();
  MX_TIM3_Init();
  MX_LPTIM5_Init();
  MX_X_CUBE_AI_Init();
  /* USER CODE BEGIN 2 */
    Motor_Init(&motor_pair, motor_pair_connector, &htim3, &htim3, TIM_CHANNEL_2, TIM_CHANNEL_3);

    HCSR04_Init(&hcsr04_front, hcsr04_connector_front, &hlptim2, 2);
    HCSR04_Init(&hcsr04_left, hcsr04_connector_left, &hlptim3, 2);
    HCSR04_Background_INT_Trigger(&hlptim1);

    JY901S_Init(&jy901s, &huart5, &angle_filter_queue);

//    HAL_Delay(3000);
    PID_Init(&angle_pid_controller, 0, ANGLE_P_DATA, ANGLE_I_DATA, ANGLE_D_DATA);
    PID_Init(&distance_pid_controller, 50, DISTANCE_P_DATA, DISTANCE_I_DATA, DISTANCE_D_DATA);

    TCS34725_Init(&color_sensor, &hi2c2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    HAL_Delay(1000);
//    Patio2();
int color = 0;
//    Motor_Straight(&motor_pair, 0.3);
    while (1)
  {
//      while(1)
//      {
//          printf("Hello World!\nPowerful Science Council\n2021/06/18 22:13:07\n\nShichen Peng 2429660P\nJinyu Yin 2429418Y\nYuxuan Wang 2429632W\nChenyue Wang 2429285W\nYuhui Zhang2429310Z\nYuhan Wu 2429633W\nYuxuan Liu 2429662L\nYueling Zhao 2429312Z\nYuxin Yang 2429637Y\nXincheng Zhu 2429649Z\n");
//          return 0;
//      }

      while(!(color = isOnColor()))
      {
          Motor_Straight(&motor_pair, 0.3);
      }
      Motor_Stop(&motor_pair);
      HAL_Delay(1000);

        if(color == 1)
        {
            TurnTo(&jy901s, &motor_pair, 0, 0.3, 100, 2);
            Keep_Angle_Forward(&motor_pair, &jy901s, &angle_pid_controller, 0.5, 0);
        }
        else if(color == 2)
        {
            while(hcsr04_front.distance > 55)
            {
                TurnTo(&jy901s, &motor_pair, 0, 0.3, 100, 2);

                Keep_Angle_Forward(&motor_pair, &jy901s, &angle_pid_controller, 0.5, 0);

            }
        }
        else
        {

        }
        TurnTo(&jy901s, &motor_pair, -90, 0.3, 100, 2);
        while(hcsr04_left.distance < 300)
        {
            Keep_Angle_Forward(&motor_pair, &jy901s, &angle_pid_controller, 0.9, -90);
        }
        HAL_Delay(3000);
        for(int i = 0; i < 8; i++)
        {
            TurnTo(&jy901s, &motor_pair, 0, 0.3, 100, 2);
            Motor_Straight(&motor_pair, 0.5);
            HAL_Delay(1000);
        }
        TurnTo(&jy901s, &motor_pair, -90, 0.3, 100, 1);
        while(hcsr04_front.distance > 40)
        {
            Keep_Angle_Forward(&motor_pair, &jy901s, &angle_pid_controller, 0.5, -90);
        }
        Motor_Stop(&motor_pair);
        HAL_Delay(1000);
        TurnTo(&jy901s, &motor_pair, 90, 0.4, 100, 1);
        while(hcsr04_front.distance > 50)
        {
            Keep_Angle_Forward(&motor_pair, &jy901s, &angle_pid_controller, 0.4, 87);
        }
        Motor_Stop(&motor_pair);
        printf("Hello World!\nPowerful Science Council\n2021/06/18 22:13:07\n\nShichen Peng 2429660P\nJinyu Yin 2429418Y\nYuxuan Wang 2429632W\nChenyue Wang 2429285W\nYuhui Zhang2429310Z\nYuhan Wu 2429633W\nYuxuan Liu 2429662L\nYueling Zhao 2429312Z\nYuxin Yang 2429637Y\nXincheng Zhu 2429649Z\n");
        return 0;


        TCS34725_GetRawData(&color_sensor, &raw_buffer);
      TCS34725_RAW_To_CMYK(&raw_buffer, &cmyk_buffer);
      TCS34725_RAW_To_HSL(&raw_buffer, &hsl_buffer);







//      printf(cmyk_buffer.c < cmyk_buffer.m ? (cmyk_buffer.m < cmyk_buffer.y ? "yellow\r\n" : "red\r\n") : (cmyk_buffer.c < cmyk_buffer.y ? "yellow\r\n" : "blue\r\n"));
//      printf("%d\r\n", hsl_buffer.s);




            //      Motor_Left_Backward(&motor_pair);
//      Motor_Right_Forward(&motor_pair);
//      Motor_PWM_Left_Duty_Cycle(&motor_pair, 1);
//      Motor_PWM_Right_Duty_Cycle(&motor_pair, 0.3);
//      TCS34725_GetRawData(&color_sensor, &raw_buffer);
//      TCS34725_RAW_To_CMYK(&raw_buffer, &cmyk_buffer);
//      TCS34725_RAW_To_HSL(&raw_buffer, &hsl_buffer);
//      printf(cmyk_buffer.c < cmyk_buffer.m ? (cmyk_buffer.m < cmyk_buffer.y ? "yellow\r\n" : "red\r\n") : (cmyk_buffer.c < cmyk_buffer.y ? "yellow\r\n" : "blue\r\n"));
//      printf("%d\r\n", hsl_buffer.s);

//      Keep_Distance_Forward(&motor_pair, &hcsr04_left, &jy901s, &distance_pid_controller, 0.3, -30);
//      printf("%f   %f    %f\r\n", hcsr04_front.distance, hcsr04_left.distance, AngleGetLatestMean(&jy901s));
//      printf("Angle_mean: %f\r\n", AngleGetLatestMean(&jy901s));
//      printf("%f\r\n", RegulateAngle(126.25- AngleGetLatestMean(&jy901s)));
//if(!start_strait)
//{
//    start_distance = hcsr04_left.distance;
//    start_angle = AngleGetLatest(&jy901s);
//    start_strait = 1;
//    PID_Init(&distance_pid_controller, start_distance, DISTANCE_P_DATA, DISTANCE_I_DATA, DISTANCE_D_DATA);
//}
//      TurnTo(&jy901s, &motor_pair, 126.25, 0.25, 2000);
////      HAL_Delay(3000);
//      while (1)
//      {
//          Keep_Angle_Forward(&motor_pair, &jy901s, &angle_pid_controller, 0.3, 126.25);
//
//      }
//      Motor_Stop(&motor_pair);
//      return 0;

//      Keep_Distance_Forward(&motor_pair, &hcsr04_left, &jy901s, &distance_pid_controller, 0.3, start_angle);
    /* USER CODE END WHILE */

//  MX_X_CUBE_AI_Process();
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
  /** Macro to configure the PLL clock source
  */
  __HAL_RCC_PLL_PLLSOURCE_CONFIG(RCC_PLLSOURCE_HSE);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48|RCC_OSCILLATORTYPE_LSI
                              |RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 5;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_HSI48, RCC_MCODIV_4);
}

/**
  * @brief Peripherals Common Clock Configuration
  * @retval None
  */
void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LPTIM2|RCC_PERIPHCLK_LPTIM3
                              |RCC_PERIPHCLK_LPTIM4|RCC_PERIPHCLK_LPTIM5;
  PeriphClkInitStruct.PLL2.PLL2M = 5;
  PeriphClkInitStruct.PLL2.PLL2N = 30;
  PeriphClkInitStruct.PLL2.PLL2P = 75;
  PeriphClkInitStruct.PLL2.PLL2Q = 128;
  PeriphClkInitStruct.PLL2.PLL2R = 2;
  PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2VCIRANGE_2;
  PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2VCOMEDIUM;
  PeriphClkInitStruct.PLL2.PLL2FRACN = 0;
  PeriphClkInitStruct.Lptim2ClockSelection = RCC_LPTIM2CLKSOURCE_PLL2;
  PeriphClkInitStruct.Lptim345ClockSelection = RCC_LPTIM345CLKSOURCE_PLL2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
