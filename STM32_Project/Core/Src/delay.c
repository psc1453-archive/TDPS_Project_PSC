//
// Created by 彭世辰 on 2021/6/14.
//

#include "delay.h"

void delay_us(uint32_t udelay)
{
    uint32_t startval,tickn,delays,wait;

    startval = SysTick->VAL;
    tickn = HAL_GetTick();
    //sysc = 72000;  //SystemCoreClock / (1000U / uwTickFreq);
    delays = udelay * (SystemCoreClock / 1000); //sysc / 1000 * udelay;
    if(delays > startval)
    {
        while(HAL_GetTick() == tickn)
        {

        }
        wait = SystemCoreClock + startval - delays;
        while(wait < SysTick->VAL)
        {

        }
    }
    else
    {
        wait = startval - delays;
        while(wait < SysTick->VAL && HAL_GetTick() == tickn)
        {

        }
    }
}

