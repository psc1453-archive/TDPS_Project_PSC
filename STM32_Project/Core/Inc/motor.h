//
// Created by 彭世辰 on 2021/6/14.
//

#ifndef TDPS_PROJECT_PSC_MOTOR_H
#define TDPS_PROJECT_PSC_MOTOR_H

#include "stm32h7xx_hal.h"

typedef struct
{
    GPIO_TypeDef* L_F_Port; uint16_t L_F_Pin;
    GPIO_TypeDef* L_B_Port; uint16_t L_B_Pin;
    GPIO_TypeDef* R_F_Port; uint16_t R_F_Pin;
    GPIO_TypeDef* R_B_Port; uint16_t R_B_Pin;
}Motor_Pair_Connector;

typedef struct
{
    Motor_Pair_Connector connector;
    TIM_HandleTypeDef* motor_l_pwm_tim;
    TIM_HandleTypeDef* motor_r_pwm_tim;
    uint32_t motor_l_pwm_channel;
    uint32_t motor_r_pwm_channel;
}Motor_Pair;

void Motor_Init(Motor_Pair* motor_pair, Motor_Pair_Connector connector, TIM_HandleTypeDef* motor_l_pwm_tim, TIM_HandleTypeDef* motor_r_pwm_tim, uint32_t motor_l_pwm_channel, uint32_t motor_r_pwm_channel);

void Motor_Left_Forward(Motor_Pair* motor_pair);

void Motor_Left_Backward(Motor_Pair* motor_pair);

void Motor_Right_Forward(Motor_Pair* motor_pair);

void Motor_Right_Backward(Motor_Pair* motor_pair);

void Motor_PWM_Left_Duty_Cycle(Motor_Pair* motor_pair, float dutyCycle);

void Motor_PWM_Right_Duty_Cycle(Motor_Pair* motor_pair, float dutyCycle);

void Motor_Smart_PWM_Left_Duty_Cycle(Motor_Pair* motor_pair, float dutyCycle);

void Motor_Smart_PWM_Right_Duty_Cycle(Motor_Pair* motor_pair, float dutyCycle);

void Motor_Stop(Motor_Pair* motor_pair);

void Motor_Straight(Motor_Pair* motor_pair, float dutyCycle);

#endif //TDPS_PROJECT_PSC_MOTOR_H



