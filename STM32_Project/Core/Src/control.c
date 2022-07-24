//
// Created by 彭世辰 on 2021/6/15.
//

#include "control.h"

void TurnTo(JY901S* jy901s, Motor_Pair* motor_pair, float target_angle, float speed, uint8_t delay, int stable_times)
{
    int match_cnt = 0;
    float current_angle;
    while(match_cnt <= stable_times)
    {
        current_angle = AngleGetLatestMean(jy901s);
        if(RegulateAngle(target_angle - current_angle) > 1.5)
        {
            Motor_Smart_PWM_Right_Duty_Cycle(motor_pair, speed);
            Motor_Smart_PWM_Left_Duty_Cycle(motor_pair, -speed);
        }
        else if(RegulateAngle(target_angle - current_angle) < -1.5)
        {
            Motor_Smart_PWM_Right_Duty_Cycle(motor_pair, -speed);
            Motor_Smart_PWM_Left_Duty_Cycle(motor_pair, speed);
        }
        else
        {
            printf("current: %f\r\n", current_angle);
            Motor_Stop(motor_pair);
            HAL_Delay(200);
            match_cnt++;
        }
    }
    HAL_Delay(delay);
    Motor_Stop(motor_pair);

}

void Controlled_Move_Forward(Motor_Pair* motor_pair, PID_Controller* pid_controller, float parameter_error, float offset_speed)
{
    float diff_speed = PID_Out(pid_controller, parameter_error);
    Motor_Smart_PWM_Left_Duty_Cycle(motor_pair, offset_speed - diff_speed);
    Motor_Smart_PWM_Right_Duty_Cycle(motor_pair, offset_speed + diff_speed);

}

void Keep_Distance_Forward(Motor_Pair* motor_pair, HCSR04* hcsr04, JY901S* jy901s, PID_Controller* pid_controller, float offset_speed, float preset_angle)
{
    float current_distance = hcsr04->distance;
    float distance_error = pid_controller->target - current_distance;
    float angle_diff = preset_angle - AngleGetLatestMean(jy901s);
//    if(angle_diff > 220 || angle_diff < -200)
//    {
//        TurnTo(jy901s, motor_pair, preset_angle, 0.25, 0, 1);
//        pid_controller->error_sum = 0;
//        pid_controller->error_last = 0;
//    }
//    else
    {
        Controlled_Move_Forward(motor_pair, pid_controller, -distance_error, offset_speed);
    }
}

void Keep_Angle_Forward(Motor_Pair* motor_pair, JY901S* jy901s, PID_Controller* pid_controller, float offset_speed, float preset_angle)
{
    float angle_error = RegulateAngle(preset_angle - AngleGetLatest(jy901s));
    Controlled_Move_Forward(motor_pair, pid_controller, angle_error, offset_speed);
}