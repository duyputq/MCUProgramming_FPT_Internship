/*
 * hal.c
 *
 *  Created on: Aug 8, 2024
 *      Author: Duy
 */

#include "inc/hal.h"

#define DELAY_CNT               (2400000)
#define GREEN_LED_PIN           (1 << 4)
#define PWM_PERIOD              (24000)

void Mode1()
{
    uint32_t index;
    uint32_t period = 400;

    for (index = 0; index < period; index++)
    {
        uint8_t dutyCycle = (index * 100) / period;
        PWM(dutyCycle);
    }

    for (index = period; index > 0; index--)
    {
        uint8_t dutyCycle = (index * 100) / period;
        PWM(dutyCycle);
    }
}

void Mode2()
{
    uint32_t index;
    for (index = 0; index < 16; index++)
    {
        delay500ms();
        FGPIOB->PTOR |= GREEN_LED_PIN;
    }
}
