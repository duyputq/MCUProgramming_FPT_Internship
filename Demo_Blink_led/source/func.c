///*
// * func.c
// *
// *  Created on: Aug 7, 2024
// *      Author: son50
// */
//#include "MKE16Z4.h"
//#include "func.h"
//
//#define DELAY_CNT               (2400000)
//#define GREEN_LED_PIN           (1 << 4)
//#define PWM_PERIOD              (24000)
//
//void initLed()
//{
//    PCC->CLKCFG[PCC_PORTB_INDEX] |= PCC_CLKCFG_CGC(1);
//    PORTB->PCR[4] |= PORT_PCR_MUX(1);
//    FGPIOB->PDDR |= GREEN_LED_PIN;
//    FGPIOB->PDOR |= GREEN_LED_PIN;
//}
//
//void delay(uint32_t count)
//{
//    uint32_t index = 0;
//    while (index < count)
//    {
//        index++;
//    }
//}
//
//void delay500ms()
//{
//    uint32_t index = 0;
//    while (index < DELAY_CNT)
//    {
//        index++;
//    }
//}
//
//void PWM(uint8_t dutyCycle)
//{
//    uint32_t onTime = (PWM_PERIOD * dutyCycle) / 100;
//    uint32_t offTime = PWM_PERIOD - onTime;
//
//    FGPIOB->PTOR |= GREEN_LED_PIN;
//    delay(onTime);
//    FGPIOB->PTOR |= GREEN_LED_PIN;
//    delay(offTime);
//}
//
//void Mode1()
//{
//    uint32_t index;
//    uint32_t period = 400;
//
//    for (index = 0; index < period; index++)
//    {
//        uint8_t dutyCycle = (index * 100) / period;
//        PWM(dutyCycle);
//    }
//
//    for (index = period; index > 0; index--)
//    {
//        uint8_t dutyCycle = (index * 100) / period;
//        PWM(dutyCycle);
//    }
//}
//
//void Mode2()
//{
//    uint32_t index;
//    for (index = 0; index < 16; index++)
//    {
//        delay500ms();
//        FGPIOB->PTOR |= GREEN_LED_PIN;
//    }
//}
//
//