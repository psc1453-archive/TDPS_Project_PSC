//
// Created by 彭世辰 on 2021/6/14.
//

#include "motor.h"
#include "stm32h7xx_hal.h"

void Motor_Init(Motor_Pair* motor_pair, Motor_Pair_Connector connector, TIM_HandleTypeDef* motor_l_pwm_tim, TIM_HandleTypeDef* motor_r_pwm_tim, uint32_t motor_l_pwm_channel, uint32_t motor_r_pwm_channel)
{
    motor_pair->connector = connector;
    motor_pair->motor_l_pwm_tim = motor_l_pwm_tim;
    motor_pair->motor_r_pwm_tim = motor_r_pwm_tim;
    motor_pair->motor_l_pwm_channel = motor_l_pwm_channel;
    motor_pair->motor_r_pwm_channel = motor_r_pwm_channel;
    HAL_TIM_PWM_Start(motor_l_pwm_tim, motor_l_pwm_channel);
    HAL_TIM_PWM_Start(motor_r_pwm_tim, motor_r_pwm_channel);
}

void Motor_Left_Forward(Motor_Pair* motor_pair)
{
    HAL_GPIO_WritePin(motor_pair->connector.L_F_Port, motor_pair->connector.L_F_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(motor_pair->connector.L_B_Port, motor_pair->connector.L_B_Pin, GPIO_PIN_RESET);
}

void Motor_Left_Backward(Motor_Pair* motor_pair)
{
    HAL_GPIO_WritePin(motor_pair->connector.L_F_Port, motor_pair->connector.L_F_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(motor_pair->connector.L_B_Port, motor_pair->connector.L_B_Pin, GPIO_PIN_SET);
}

void Motor_Right_Forward(Motor_Pair* motor_pair)
{
    HAL_GPIO_WritePin(motor_pair->connector.R_F_Port, motor_pair->connector.R_F_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(motor_pair->connector.R_B_Port, motor_pair->connector.R_B_Pin, GPIO_PIN_RESET);
}

void Motor_Right_Backward(Motor_Pair* motor_pair)
{
    HAL_GPIO_WritePin(motor_pair->connector.R_F_Port, motor_pair->connector.R_F_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(motor_pair->connector.R_B_Port, motor_pair->connector.R_B_Pin, GPIO_PIN_SET);
}

void Motor_PWM_Left_Duty_Cycle(Motor_Pair* motor_pair, float dutyCycle)
{
    __HAL_TIM_SET_COMPARE(motor_pair->motor_l_pwm_tim, motor_pair->motor_l_pwm_channel, 1000*dutyCycle-1);
}

void Motor_PWM_Right_Duty_Cycle(Motor_Pair* motor_pair, float dutyCycle)
{
    __HAL_TIM_SET_COMPARE(motor_pair->motor_r_pwm_tim, motor_pair->motor_r_pwm_channel, 1000*dutyCycle-1);
}

void Motor_Smart_PWM_Left_Duty_Cycle(Motor_Pair* motor_pair, float dutyCycle)
{
    if(dutyCycle >= 0 && dutyCycle <= 1)
    {
        Motor_Left_Forward(motor_pair);
        __HAL_TIM_SET_COMPARE(motor_pair->motor_l_pwm_tim, motor_pair->motor_l_pwm_channel, 1000*dutyCycle-1);
    }
    else if(dutyCycle > 1)
    {
        Motor_Left_Forward(motor_pair);
        __HAL_TIM_SET_COMPARE(motor_pair->motor_l_pwm_tim, motor_pair->motor_l_pwm_channel, 1000-1);
    }
    else if(dutyCycle < 0 && dutyCycle >= -1)
    {
        Motor_Left_Backward(motor_pair);
        __HAL_TIM_SET_COMPARE(motor_pair->motor_l_pwm_tim, motor_pair->motor_l_pwm_channel, -1000*dutyCycle-1);
    }
    else
    {
        Motor_Left_Backward(motor_pair);
        __HAL_TIM_SET_COMPARE(motor_pair->motor_l_pwm_tim, motor_pair->motor_l_pwm_channel, 1000-1);
    }
}

void Motor_Smart_PWM_Right_Duty_Cycle(Motor_Pair* motor_pair, float dutyCycle)
{
    if(dutyCycle >= 0 && dutyCycle <= 1)
    {
        Motor_Right_Forward(motor_pair);
        __HAL_TIM_SET_COMPARE(motor_pair->motor_r_pwm_tim, motor_pair->motor_r_pwm_channel, 1000*dutyCycle-1);
    }
    else if(dutyCycle > 1)
    {
        Motor_Right_Forward(motor_pair);
        __HAL_TIM_SET_COMPARE(motor_pair->motor_r_pwm_tim, motor_pair->motor_r_pwm_channel, 1000-1);
    }
    else if(dutyCycle < 0 && dutyCycle >= -1)
    {
        Motor_Right_Backward(motor_pair);
        __HAL_TIM_SET_COMPARE(motor_pair->motor_r_pwm_tim, motor_pair->motor_r_pwm_channel, -1000*dutyCycle-1);
    }
    else
    {
        Motor_Right_Backward(motor_pair);
        __HAL_TIM_SET_COMPARE(motor_pair->motor_r_pwm_tim, motor_pair->motor_r_pwm_channel, 1000-1);
    }
}

void Motor_Stop(Motor_Pair* motor_pair)
{
    HAL_GPIO_WritePin(motor_pair->connector.L_F_Port, motor_pair->connector.L_F_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(motor_pair->connector.L_B_Port, motor_pair->connector.L_B_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(motor_pair->connector.R_F_Port, motor_pair->connector.R_F_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(motor_pair->connector.R_B_Port, motor_pair->connector.R_B_Pin, GPIO_PIN_RESET);
}

void Motor_Straight(Motor_Pair* motor_pair, float dutyCycle)
{
    Motor_Left_Forward(motor_pair);
    Motor_Right_Forward(motor_pair);
    Motor_PWM_Left_Duty_Cycle(motor_pair, dutyCycle);
    Motor_PWM_Right_Duty_Cycle(motor_pair, dutyCycle);



}