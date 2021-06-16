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
#include "stdio.h"

void TurnTo(JY901S* jy901s, Motor_Pair* motor_pair, float target_angle, float speed, uint8_t delay, int stable_times);

void Controlled_Move_Forward(Motor_Pair* motor_pair, PID_Controller* pid_controller, float parameter_error, float offset_speed);

void Keep_Distance_Forward(Motor_Pair* motor_pair, HCSR04* hcsr04, JY901S* jy901s, PID_Controller* pid_controller, float offset_speed, float preset_angle);

void Keep_Angle_Forward(Motor_Pair* motor_pair, JY901S* jy901s, PID_Controller* pid_controller, float offset_speed, float preset_angle);

#endif //TDPS_PROJECT_PSC_CONTROL_H
