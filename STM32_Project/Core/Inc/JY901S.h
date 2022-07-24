//
// Created by 彭世辰 on 2021/6/14.
//

#ifndef TDPS_PROJECT_PSC_JY901S_H
#define TDPS_PROJECT_PSC_JY901S_H

// Modify to target chip
#include "stm32h7xx_hal.h"

#define QUEUE_SIZE 10

union AngleBuffer
{
    uint8_t byte[2];
    int16_t angle_raw;
};

typedef struct
{
    float queue[QUEUE_SIZE];
    float mean;
    uint8_t pt;
}AngleFilterQueue;

// Declare in main.c and extern in it.c
typedef struct
{
    UART_HandleTypeDef* jy901s_uart;
    uint8_t angle_frame_ready;
    union AngleBuffer angle_union_buffer;
    uint8_t uart_receive_buffer;
    float angle;
    AngleFilterQueue* angle_filter_queue;
}JY901S;

void JY901S_Init(JY901S* jy901s, UART_HandleTypeDef* jy901s_uart, AngleFilterQueue* angle_filter_queue);

void AngleFilterEnqueue(AngleFilterQueue* queue, float element);

float AngleFilterDequeue(AngleFilterQueue* queue);

float RegulateAngle(float angle);

float DecodeAngle(int16_t angle_raw);

void AngleStoreAndEnqueue(JY901S* jy901s);

float AngleGetLatest(JY901S* jy901s);

float AngleGetLatestMean(JY901S* jy901s);

// Put into void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
void Angle_UART_INT_Handler(JY901S* jy901s, UART_HandleTypeDef *huart);

#endif //TDPS_PROJECT_PSC_JY901S_H
