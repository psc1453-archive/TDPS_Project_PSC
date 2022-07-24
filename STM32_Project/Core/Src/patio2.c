//
// Created by 彭世辰 on 2021/6/16.
//

#include "patio2.h"
#include "HCSR04.h"
#include "control.h"
#include "Color.h"
#include "angle_preset.h"

extern TCS34725 color_sensor;
extern COLOR_RGBC_RAW raw_buffer;
extern COLOR_CMYK cmyk_buffer;
extern COLOR_HSL hsl_buffer;

extern Motor_Pair motor_pair;

extern JY901S jy901s;

extern PID_Controller angle_pid_controller;
extern PID_Controller distance_pid_controller;

extern HCSR04 hcsr04_front;
extern HCSR04 hcsr04_left;

int color = 0;

int isOnColor()
{

    static color_last = 0;
    static int compare_cnt = 0;
    TCS34725_GetRawData(&color_sensor, &raw_buffer);
    TCS34725_RAW_To_HSL(&raw_buffer, &hsl_buffer);
    TCS34725_RAW_To_CMYK(&raw_buffer, &cmyk_buffer);
    printf(cmyk_buffer.c < cmyk_buffer.m ? (cmyk_buffer.m < cmyk_buffer.y ? "yellow\r\n" : "red\r\n") : (cmyk_buffer.c < cmyk_buffer.y ? "yellow\r\n" : "blue\r\n"));
      printf("%d\r\n", hsl_buffer.s);
    color = cmyk_buffer.c < cmyk_buffer.m ? (cmyk_buffer.m < cmyk_buffer.y ? 3 : 2) : (cmyk_buffer.c < cmyk_buffer.y ? 3 : 1);
    if(color == 1)
    {
        if(hsl_buffer.s > 35)
        {
            if(color_last == color)
            {
                color_last = color;
                compare_cnt++;
            }
            else
            {
                color_last = 0;
                compare_cnt = 0;
            }

        }
        else
        {
            color_last = 0;
            compare_cnt = 0;
        }
    }
    else if(color == 2)
    {
        if(hsl_buffer.s > 10)
        {
            if(color_last == color)
            {
                color_last = color;
                compare_cnt++;
            }
            else
            {
                color_last = 0;
                compare_cnt = 0;
            }
        }
        else
        {
            color_last = 0;
            compare_cnt = 0;
        }
    }
    else
    {
        if(hsl_buffer.s > 35)
        {
            if(color_last == color)
            {
                color_last = color;
                compare_cnt++;
            }
            else
            {
                color_last = 0;
                compare_cnt = 0;
            }
        }
        else
        {
            color_last = 0;
            compare_cnt = 0;
        }
    }
    color_last = color;
    printf("%d %d %d\r\n", color_last, color, compare_cnt);
    if(compare_cnt > 20)
    {
        return color_last;
    }
    else
    {
        return 0;
    }
}

void Patio2()
{
    while(!isOnColor())
    {
        Motor_Straight(&motor_pair, 0.3);
    }
    Motor_Stop(&motor_pair);
    switch (color) {
        case 0:
            TurnTo(&jy901s, &motor_pair, COLOR_LEFT_TARGET_ANGLE, 0.25, 2000, 10);
            Keep_Angle_Forward(&motor_pair, &jy901s, &angle_pid_controller, 0.3, COLOR_LEFT_TARGET_ANGLE);
            break;
        case 1:
            TurnTo(&jy901s, &motor_pair, COLOR_CENTER_TARGET_ANGLE, 0.25, 2000, 10);
            Keep_Angle_Forward(&motor_pair, &jy901s, &angle_pid_controller, 0.3, COLOR_CENTER_TARGET_ANGLE);
            break;
        case 2:
            TurnTo(&jy901s, &motor_pair, COLOR_RIGHT_TARGET_ANGLE, 0.25, 2000, 10);
            Keep_Angle_Forward(&motor_pair, &jy901s, &angle_pid_controller, 0.3, COLOR_RIGHT_TARGET_ANGLE);
            break;
        default:
            break;
    }
    HAL_Delay(1000);
    TurnTo(&jy901s, &motor_pair, FORWARD_TARGET_ANGLE, 0.25, 2000, 1);
    while(!(hcsr04_front.distance < 40.0 && hcsr04_front.distance > 0.5))
    {
        Keep_Angle_Forward(&motor_pair, &jy901s, &angle_pid_controller, 0.3, FORWARD_TARGET_ANGLE);
    }
    TurnTo(&jy901s, &motor_pair, LAKE_TARGET_ANGLE, 0.25, 2000, 1);
    while(hcsr04_left.distance < 200)
    {
        Keep_Distance_Forward(&motor_pair, &hcsr04_left, &jy901s, &distance_pid_controller, 0.3, LAKE_TARGET_ANGLE);
    }
    HAL_Delay(4000);
    TurnTo(&jy901s, &motor_pair, FORWARD_TARGET_ANGLE, 0.25, 2000, 10);
    Motor_Straight(&motor_pair, 0.3);
    HAL_Delay(3000);
    TurnTo(&jy901s, &motor_pair, LAKE_TARGET_ANGLE, 0.25, 2000, 10);
    while(!(hcsr04_front.distance < 40.0 && hcsr04_front.distance > 0.5))
    {
        Keep_Angle_Forward(&motor_pair, &jy901s, &angle_pid_controller, 0.3, LAKE_TARGET_ANGLE);
    }
    Motor_Stop(&motor_pair);
}