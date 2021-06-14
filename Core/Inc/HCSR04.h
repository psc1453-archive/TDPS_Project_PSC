//
// Created by 彭世辰 on 2021/6/14.
//

#ifndef TDPS_PROJECT_PSC_HCSR04_H
#define TDPS_PROJECT_PSC_HCSR04_H

#include "main.h"

typedef struct
{
    GPIO_TypeDef* HCSR04_TRIG_Port; uint16_t HCSR04_TRIG_Pin;
    GPIO_TypeDef* HCSR04_ECHO_Port; uint16_t HCSR04_ECHO_Pin;
}HCSR04_Connector;

typedef struct
{
    uint16_t time_ms;
    uint16_t time_us;
}HCSR04_Time;

// Declare in main.c and extern in it.c
typedef struct
{
    HCSR04_Connector connector;
    HCSR04_Time echo_time;
    LPTIM_HandleTypeDef* hlptim;
    double distance;
    int lptim_mhz;
}HCSR04;

void HCSR04_Init(HCSR04* hcsr04, HCSR04_Connector connector, LPTIM_HandleTypeDef* hlptim, int lptim_mhz);
void HCSR04_Trig(HCSR04* hcsr04);

// Put into void HAL_LPTIM_AutoReloadMatchCallback(LPTIM_HandleTypeDef *hlptim)
void HCSR04_Auto_Reload_Handler(HCSR04* hcsr04);
// Put into void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
void HCSR04_EXTI_Handler(HCSR04* hcsr04);

#endif //TDPS_PROJECT_PSC_HCSR04_H
