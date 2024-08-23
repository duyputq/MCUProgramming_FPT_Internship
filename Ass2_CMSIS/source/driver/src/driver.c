/*
 * driver.c
 *
 *  Created on: Aug 8, 2024
 *      Author: Duy
 */

#include "inc/driver.h"

#define DELAY_CNT               (2400000)
#define GREEN_LED_PIN           (1 << 4)
#define PWM_PERIOD              (24000)

void initLed()
{
    PCC->CLKCFG[PCC_PORTB_INDEX] |= PCC_CLKCFG_CGC(1);
    PORTB->PCR[4] |= PORT_PCR_MUX(1);
    FGPIOB->PDDR |= GREEN_LED_PIN;
    FGPIOB->PDOR |= GREEN_LED_PIN;
}

void PWM(uint8_t dutyCycle)
{
    uint32_t onTime = (PWM_PERIOD * dutyCycle) / 100;
    uint32_t offTime = PWM_PERIOD - onTime;

    FGPIOB->PTOR |= GREEN_LED_PIN;
    delay(onTime);
    FGPIOB->PTOR |= GREEN_LED_PIN;
    delay(offTime);
}
