//
// Created by 彭世辰 on 2021/6/15.
//

#ifndef TDPS_PROJECT_PSC_PID_H
#define TDPS_PROJECT_PSC_PID_H

typedef struct
{
    float Kp;
    float Ki;
    float Kd;
    float target;
    float error_last;
    float error_sum;
}PID_Controller;

void PID_Init(PID_Controller* pid_controller, float target, float Kp, float Ki, float Kd);

float PID_Out(PID_Controller* pid_controller, float new_error);

#endif //TDPS_PROJECT_PSC_PID_H
