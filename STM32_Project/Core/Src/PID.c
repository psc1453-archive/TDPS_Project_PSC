//
// Created by 彭世辰 on 2021/6/15.
//

#include "PID.h"

void PID_Init(PID_Controller* pid_controller, float target, float Kp, float Ki, float Kd)
{
    pid_controller->target = target;
    pid_controller->Kp = Kp;
    pid_controller->Ki = Ki;
    pid_controller->Kd = Kd;
    pid_controller->error_last = 0;
    pid_controller->error_sum = 0;
}

float PID_Out(PID_Controller* pid_controller, float new_error)
{
    pid_controller->error_sum += new_error;
    float out_error_value = pid_controller->Kp * new_error + pid_controller->Ki * pid_controller->error_sum + pid_controller->Kd * (new_error - pid_controller->error_last);
    pid_controller->error_last = new_error;
    return out_error_value;
}