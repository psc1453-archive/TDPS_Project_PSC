//
// Created by 彭世辰 on 2021/6/16.
//

#include "stm32h7xx_hal.h"
#include "app_x-cube-ai.h"
#include "tim.h"
#include "camera.h"
#include "lcd.h"
#include "dcmi.h"
#include "HCSR04.h"
#include "control.h"
#include "angle_preset.h"
#include "main.h"

#define FrameWidth 72
#define FrameHeight 54

#define NORMAL_SPEED 0.25
#define DIFF_SPEED 0.25
#define MAX_DEGREE 65.0

BUFFER_D1 uint16_t pic[FrameHeight][FrameWidth];
BUFFER_D1 uint8_t pic_gray[FrameHeight][FrameWidth];
BUFFER_D1 uint16_t pic_rgb[FrameHeight][FrameWidth];

uint32_t DCMI_FrameIsReady;
uint32_t Camera_FPS=0;
uint8_t DMA_Started = 0;

float nn_out[7];
float path_direction;
float path_degree;

uint8_t text[20];

extern I2C_HandleTypeDef hi2c1;
extern HCSR04 hcsr04_front;
extern HCSR04 hcsr04_left;
extern Motor_Pair motor_pair;
extern JY901S jy901s;
extern PID_Controller angle_pid_controller;

static void PWM_Left_Duty_Cycle(float dutyCycle)
{
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 1000*dutyCycle);
}

static void PWM_Right_Duty_Cycle(float dutyCycle)
{
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 1000*dutyCycle);
}

static void Left_Forward()
{
    HAL_GPIO_WritePin(MOTOR_L_F_GPIO_Port, MOTOR_L_F_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_L_B_GPIO_Port, MOTOR_L_B_Pin, GPIO_PIN_RESET);
}

static void Left_Backward()
{
    HAL_GPIO_WritePin(MOTOR_L_F_GPIO_Port, MOTOR_L_F_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_L_B_GPIO_Port, MOTOR_L_B_Pin, GPIO_PIN_SET);
}

static oid Right_Forward()
{
    HAL_GPIO_WritePin(MOTOR_R_F_GPIO_Port, MOTOR_R_F_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_R_B_GPIO_Port, MOTOR_R_B_Pin, GPIO_PIN_RESET);
}

static void Right_Backward() {
    HAL_GPIO_WritePin(MOTOR_R_F_GPIO_Port, MOTOR_R_F_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_R_B_GPIO_Port, MOTOR_R_B_Pin, GPIO_PIN_SET);
}

static void PWM_Left_Smart_Duty_Cycle(float dutyCycle)
{
    if(dutyCycle > 0)
    {
        HAL_GPIO_WritePin(MOTOR_L_F_GPIO_Port, MOTOR_L_F_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(MOTOR_L_B_GPIO_Port, MOTOR_L_B_Pin, GPIO_PIN_RESET);
        PWM_Left_Duty_Cycle(dutyCycle);
    }
    else
    {
//        HAL_GPIO_WritePin(MOTOR_L_F_GPIO_Port, MOTOR_L_F_Pin, GPIO_PIN_RESET);
//        HAL_GPIO_WritePin(MOTOR_L_B_GPIO_Port, MOTOR_L_B_Pin, GPIO_PIN_SET);
//        PWM_Left_Duty_Cycle(-dutyCycle);
    }
}

static void PWM_Right_Smart_Duty_Cycle(float dutyCycle)
{
    if(dutyCycle > 0)
    {
        HAL_GPIO_WritePin(MOTOR_R_F_GPIO_Port, MOTOR_R_F_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(MOTOR_R_B_GPIO_Port, MOTOR_R_B_Pin, GPIO_PIN_RESET);
        PWM_Left_Duty_Cycle(dutyCycle);
    }
    else
    {
//        HAL_GPIO_WritePin(MOTOR_R_F_GPIO_Port, MOTOR_R_F_Pin, GPIO_PIN_RESET);
//        HAL_GPIO_WritePin(MOTOR_R_B_GPIO_Port, MOTOR_R_B_Pin, GPIO_PIN_SET);
//        PWM_Right_Duty_Cycle(-dutyCycle);
    }
}

static void Update_Mortor(float degree)
{
    if(degree < 40.0 && degree > -33.0)
    {
        Left_Forward();
        Right_Forward();
        PWM_Left_Duty_Cycle(NORMAL_SPEED + 0.20 + (degree / MAX_DEGREE) * DIFF_SPEED);
        PWM_Right_Duty_Cycle(NORMAL_SPEED - 0.07 - (degree / MAX_DEGREE) * DIFF_SPEED);
    }
    else if(degree < -33.0)
    {
        Left_Backward();
        Right_Forward();
        PWM_Left_Duty_Cycle(0.3);
        PWM_Right_Duty_Cycle(NORMAL_SPEED + 0.1 - (degree / MAX_DEGREE) * DIFF_SPEED);
        HAL_Delay(50);
        PWM_Right_Duty_Cycle(NORMAL_SPEED - (degree / MAX_DEGREE) * DIFF_SPEED);
        HAL_Delay(70);
    }
    else
    {
        Left_Forward();
        Right_Forward();
        PWM_Left_Duty_Cycle(NORMAL_SPEED + (degree*1.1 / MAX_DEGREE) * DIFF_SPEED);
        PWM_Right_Duty_Cycle(NORMAL_SPEED - (degree*1.1 / MAX_DEGREE) * DIFF_SPEED);
    }
}

void Patio1()
{
    LCD_Init();
    sprintf((char *)&text, "Camera Not Found");
    LCD_ShowString(0, 58, ST7735Ctx.Width, 16, 16, text);
    Camera_Init_Device(&hi2c1, FRAMESIZE_TDPS_NN_54P, PIXFORMAT_YUV422);
    ST7735_LCD_Driver.FillRect(&st7735_pObj, 0, 58, ST7735Ctx.Width, 16, BLACK);
    // Path finding
    while(!(hcsr04_front.distance < 40.0 && hcsr04_front.distance > 0.5))
    {
        if(DMA_Started)
        {

        }
        else
        {
            HAL_DCMI_Start_DMA(&hdcmi, DCMI_MODE_SNAPSHOT, (uint32_t)&pic, FrameWidth * FrameHeight * 2 / 4);
            DMA_Started = 1;
        }
        if (DCMI_FrameIsReady)
        {
            HAL_DCMI_Stop(&hdcmi);
            DMA_Started = 0;
            DCMI_FrameIsReady = 0;


            for(int i = 0; i < FrameHeight; i++)
            {
                for(int j = 0; j < FrameWidth; j++)
                {
                    pic_gray[i][j] = pic[i][j] & 0xff;
                    pic_rgb[i][j] = (pic_gray[i][j] & 0b11111000) | (pic_gray[i][j] & 0b11111000) << 5 | (pic_gray[i][j] & 0b11100000) >> 5 | (pic_gray[i][j] & 0b00011100) << 11;
                }
            }
            MX_X_CUBE_AI_Process();
            path_degree = ((0.9444 * path_direction - 8.5) * path_direction + 38.53) * path_direction - 64.6;

            ST7735_FillRGBRect(&st7735_pObj,32,0,(uint8_t *)&pic_rgb[0][0], FrameWidth, FrameHeight);

            sprintf((char *)&text,"%dFPS",Camera_FPS);
            LCD_ShowString(0,0,120,16,12,text);
            sprintf((char *)&text,"%1.3f",path_direction);
            LCD_ShowString(0,16,120,16,12,text);
            sprintf((char *)&text,"%1.3f",path_degree);
            LCD_ShowString(0,32,120,16,12,text);
            Update_Mortor(path_degree);

        }
    }
    HAL_DCMI_Stop(&hdcmi);
    Motor_Stop(&motor_pair);
    // Turn to bridge
    TurnTo(&jy901s, &motor_pair, BRIDGE_TARGET_ANGLE, 0.25, 2000, 10);
    // Cross bridge
    while (!(hcsr04_front.distance < 40.0 && hcsr04_front.distance > 0.5))
    {
        Keep_Angle_Forward(&motor_pair, &jy901s, &angle_pid_controller, 0.5, BRIDGE_TARGET_ANGLE);
    }
    // Turn to gate
    TurnTo(&jy901s, &motor_pair, GATE_TARGET_ANGLE, 0.25, 2000, 10);
    // Drive across Gate
    while(!(hcsr04_left.distance < 20.0 && hcsr04_left.distance > 0.5))
    {
        Keep_Angle_Forward(&motor_pair, &jy901s, &angle_pid_controller, 0.5, GATE_TARGET_ANGLE);
    }
    HAL_Delay(2000);
    Motor_Stop(&motor_pair);
}

void HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi)
{
    static uint32_t count = 0,tick = 0;

    if(HAL_GetTick() - tick >= 1000)
    {
        tick = HAL_GetTick();
        Camera_FPS = count;
        count = 0;
    }
    count ++;

    DCMI_FrameIsReady = 1;
}