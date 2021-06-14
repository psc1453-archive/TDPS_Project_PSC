//
// Created by 彭世辰 on 2021/6/15.
//

#ifndef TDPS_PROJECT_PSC_CONTROL_H
#define TDPS_PROJECT_PSC_CONTROL_H

#include "JY901S.h"
#include "HCSR04.h"
#include "angle_preset.h"
#include "PID.h"
#include "motor.h"

void TurnTo(JY901S* jy901s, Motor_Pair* motor_pair, float target_angle, float speed, uint8_t delay)
{
    static int match_cnt = 0;
    if(RegulateAngle(target_angle - AngleGetLatestMean(jy901s)) > 1.5)
    {
        Motor_Smart_PWM_Right_Duty_Cycle(motor_pair, speed);
        Motor_Smart_PWM_Left_Duty_Cycle(motor_pair, -speed);
    }
    else if(RegulateAngle(target_angle - AngleGetLatestMean(jy901s)) < -1.5)
    {
        Motor_Smart_PWM_Right_Duty_Cycle(motor_pair, -speed);
        Motor_Smart_PWM_Left_Duty_Cycle(motor_pair, speed);
    }
    else
    {
        Motor_Stop(motor_pair);
        if(++match_cnt > 10)
        {
            match_cnt = 0;
            HAL_Delay(delay);
            return;
        }
    }
}

void Controlled_Move_Forward(Motor_Pair* motor_pair, PID_Controller* pid_controller, float parameter_error, float offset_speed)
{
    float diff_speed = PID_Out(pid_controller, parameter_error);
    Motor_Smart_PWM_Left_Duty_Cycle(motor_pair, offset_speed + diff_speed);
    Motor_Smart_PWM_Right_Duty_Cycle(motor_pair, offset_speed - diff_speed);
}

void Keep_Distance_Forward(Motor_Pair* motor_pair, HCSR04* hcsr04, JY901S* jy901s, PID_Controller* pid_controller, float offset_speed, float preset_angle)
{
    float current_distance = hcsr04->distance;
    float distance_error = pid_controller->target - current_distance;
    float angle_diff = preset_angle - AngleGetLatestMean(jy901s);
    if(angle_diff > 15 || angle_diff < -15)
    {
        TurnTo(jy901s, motor_pair, preset_angle, 0.15, 500);
        pid_controller->error_sum = 0;
        pid_controller->error_last = 0;
    }
    else
    {
        Controlled_Move_Forward(motor_pair, pid_controller, distance_error, 0.2);
    }
}

void Keep_Angle_Forward(Motor_Pair* motor_pair, JY901S* jy901s, PID_Controller* pid_controller, float offset_speed, float preset_angle)
{
    float angle_error = preset_angle - AngleGetLatestMean(jy901s);
    Controlled_Move_Forward(motor_pair, pid_controller, angle_error, 0.2);
}

#endif //TDPS_PROJECT_PSC_CONTROL_H
