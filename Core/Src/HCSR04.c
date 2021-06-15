//
// Created by 彭世辰 on 2021/6/14.
//

#include "HCSR04.h"
#include "delay.h"
#include <stdio.h>

void HCSR04_Init(HCSR04* hcsr04, HCSR04_Connector connector, LPTIM_HandleTypeDef* hlptim, int lptim_mhz)
{
    hcsr04->connector = connector;
    hcsr04->distance = 0;
    hcsr04->echo_time.time_ms = 0;
    hcsr04->echo_time.time_us = 0;
    hcsr04->hlptim = hlptim;
    hcsr04->lptim_mhz = lptim_mhz;
}

void HCSR04_Trig(HCSR04* hcsr04)
{
    HAL_GPIO_WritePin(hcsr04->connector.HCSR04_TRIG_Port, hcsr04->connector.HCSR04_TRIG_Pin, GPIO_PIN_SET);
    delay_us(20);
    HAL_GPIO_WritePin(hcsr04->connector.HCSR04_TRIG_Port, hcsr04->connector.HCSR04_TRIG_Pin, GPIO_PIN_RESET);
}

void HCSR04_Background_INT_Trigger(LPTIM_HandleTypeDef* trigger_lptim)
{
    HAL_LPTIM_PWM_Start_IT(trigger_lptim, 3200-1, 1-1);
}

// Put into void HAL_LPTIM_AutoReloadMatchCallback(LPTIM_HandleTypeDef *hlptim)
void HCSR04_Auto_Reload_Handler(HCSR04* hcsr04)
{
    hcsr04->echo_time.time_ms++;
}

// Put into void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
void HCSR04_EXTI_Handler(HCSR04* hcsr04)
{
    if(HAL_GPIO_ReadPin(hcsr04->connector.HCSR04_ECHO_Port, hcsr04->connector.HCSR04_ECHO_Pin))
    {
        hcsr04->echo_time.time_ms = 0;
        hcsr04->echo_time.time_us = 0;
        HAL_LPTIM_Counter_Start_IT(hcsr04->hlptim, hcsr04->lptim_mhz * 1000 - 1);
    }
    else
    {
        hcsr04->echo_time.time_us = HAL_LPTIM_ReadCounter(hcsr04->hlptim) / hcsr04->lptim_mhz;
        HAL_LPTIM_Counter_Stop_IT(hcsr04->hlptim);
        hcsr04->distance = (hcsr04->echo_time.time_ms * 1000.0 + hcsr04->echo_time.time_us) * 0.017;
    }
}

void HCSR04_Trig_Compare_Handler(HCSR04* hcsr04)
{
    HAL_GPIO_WritePin(hcsr04->connector.HCSR04_TRIG_Port, hcsr04->connector.HCSR04_TRIG_Pin, GPIO_PIN_RESET);
}

void HCSR04_Trig_Reload_Handler(HCSR04* hcsr04)
{
    HAL_GPIO_WritePin(hcsr04->connector.HCSR04_TRIG_Port, hcsr04->connector.HCSR04_TRIG_Pin, GPIO_PIN_SET);
}


