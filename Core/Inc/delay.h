//
// Created by 彭世辰 on 2021/6/14.
//

#ifndef TDPS_PROJECT_PSC_DELAY_H
#define TDPS_PROJECT_PSC_DELAY_H

// Modify to target chip
#include "stm32h7xx_hal.h"

// Modify to system clock (MHz)
#define SystemCoreClockMHz 480
#define SystemCoreClock (SystemCoreClockMHz*1000)

void delay_us(uint32_t udelay);

#endif //TDPS_PROJECT_PSC_DELAY_H
