//
// Created by 彭世辰 on 2021/5/28.
//

#include "main.h"
#include "stm32h7xx_hal.h"

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

extern UART_HandleTypeDef huart3;

PUTCHAR_PROTOTYPE
{
    HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 50);

    return ch;
}