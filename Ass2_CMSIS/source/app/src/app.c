/*
 * app.c
 *
 *  Created on: Aug 8, 2024
 *      Author: Duy
 */

#include "inc/app.h"

#define DELAY_CNT               (2400000)
#define GREEN_LED_PIN           (1 << 4)
#define PWM_PERIOD              (24000)

void delay(uint32_t count)
{
    uint32_t index = 0;
    while (index < count)
    {
        index++;
    }
}

void delay500ms()
{
    uint32_t index = 0;
    while (index < DELAY_CNT)
    {
        index++;
    }
}
