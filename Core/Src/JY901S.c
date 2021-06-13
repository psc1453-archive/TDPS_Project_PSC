//
// Created by 彭世辰 on 2021/6/14.
//

#include "JY901S.h"

void JY901S_Init(JY901S* jy901s, UART_HandleTypeDef* jy901s_uart, AngleFilterQueue angle_filter_queue)
{
    jy901s->angle_filter_queue = angle_filter_queue;
    jy901s->angle = 0;
    jy901s->uart_receive_buffer = 0;
    jy901s->jy901s_uart = jy901s_uart;
    union AngleBuffer angle_buffer = {.angle_raw = 0};
    jy901s->angle_union_buffer = angle_buffer;
    jy901s->angle_frame_ready = 0;
    HAL_UART_Receive_IT(jy901s_uart, &(jy901s->uart_receive_buffer), 1);
}

void AngleFilterEnqueue(AngleFilterQueue* queue, float element)
{
    queue->queue[queue->pt] = element;
    queue->pt = (queue->pt + 1) % QUEUE_SIZE;
    queue->mean = 0;
    for(int i = 0; i < QUEUE_SIZE; i++)
    {
        queue->mean += queue->queue[i] * (1.0/QUEUE_SIZE);
    }
}
float AngleFilterDequeue(AngleFilterQueue* queue)
{
    return queue->mean;
}

float RegulateAngle(float angle)
{
    if(angle <= -180.0)
    {
        return angle + 360.0;
    }
    else if(angle <= 180)
    {
        return angle;
    }
    else
    {
        return angle - 360.0;
    }
}

float DecodeAngle(int16_t angle_raw)
{
    return angle_raw / 32768.0 * 180.0;
}

void AngleStoreAndEnqueue(JY901S* jy901s)
{
    jy901s->angle = DecodeAngle(jy901s->angle_union_buffer.angle_raw);
    AngleFilterEnqueue(&(jy901s->angle_filter_queue), jy901s->angle);
}

float AngleGetLatest(JY901S* jy901s)
{
    return jy901s->angle;
}

float AngleGetLatestMean(JY901S* jy901s)
{
    return AngleFilterDequeue(&(jy901s->angle_filter_queue));
}

void Angle_UART_INT_Handler(JY901S* jy901s, UART_HandleTypeDef *huart)
{
    static uint8_t cnt;
    if(huart == jy901s->jy901s_uart)
    {
        switch (cnt)
        {
            case 0:
                if(jy901s->uart_receive_buffer == 0x55)
                {
                    cnt = 1;
                }
                else
                {
                    cnt = 0;
                }
                break;
            case 1:
                if(jy901s->uart_receive_buffer == 0x53)
                {
                    cnt = 2;
                }
                else
                {
                    cnt = 0;
                }
                break;
            case 2:
                cnt = 3;
                break;
            case 3:
                cnt = 4;
                break;
            case 4:
                cnt = 5;
                break;
            case 5:
                cnt = 6;
                break;
            case 6:
                jy901s->angle_frame_ready = 0;
                jy901s->angle_union_buffer.byte[0] = jy901s->uart_receive_buffer;
                cnt = 7;
                break;
            case 7:
                jy901s->angle_union_buffer.byte[1] = jy901s->uart_receive_buffer;
                jy901s->angle_frame_ready = 1;
                AngleStoreAndEnqueue(jy901s);
                cnt = 0;
                break;
            default:
                cnt = 0;
                break;
        }
        HAL_UART_Receive_IT(jy901s->jy901s_uart, &(jy901s->uart_receive_buffer), 1);
        return;
    }
}