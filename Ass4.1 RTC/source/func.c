/*
 * func.c
 *
 *  Created on: Aug 16, 2024
 *      Author: son50
 */
/*******************************************************************************
*Include
******************************************************************************/
#include "func.h"

/**
 *******************************************************************************
 * @brief            Initializes the green LED on PORTB4.
 *
 * @param[in]        None
 * @param[out]       None
 * @return           None
 *******************************************************************************
 */
void initLedgreen(void) {
    PCC->CLKCFG[PCC_PORTB_INDEX] |= PCC_CLKCFG_CGC(1);
    PORTB->PCR[4] = PORT_PCR_MUX(1);
    FGPIOB->PDDR |= GREEN_LED_PIN;
    FGPIOB->PDOR |= GREEN_LED_PIN;  // Turn off LED (active low)
}

/**
 *******************************************************************************
 * @brief            Initializes the blue LED on PORTD1.
 *
 * @param[in]        None
 * @param[out]       None
 * @return           None
 *******************************************************************************
 */
void initLedblue(void) {
    PCC->CLKCFG[PCC_PORTD_INDEX] |= PCC_CLKCFG_CGC(1);
    PORTD->PCR[1] = PORT_PCR_MUX(1);
    FGPIOD->PDDR |= BLUE_LED_PIN;
    FGPIOD->PDOR |= BLUE_LED_PIN;  // Turn off LED (active low)
}

/**
 *******************************************************************************
 * @brief            Initializes the RTC for timekeeping.
 *
 * @param[in]        None
 * @param[out]       None
 * @return           None
 *******************************************************************************
 */
void initRTC() {
    PCC->CLKCFG[PCC_RTC_INDEX] |= PCC_CLKCFG_CGC_MASK;

    // Reset RTC and set initial time
    while (RTC->SR & RTC_SR_TIF_MASK) {
        RTC->CR |= RTC_CR_SWR_MASK;
        RTC->CR &= ~RTC_CR_SWR_MASK;
        RTC->TSR = 1;
    }

    RTC->CR = RTC_CR_LPOS(1) | RTC_CR_CPS(0) | RTC_CR_CPE(0) | RTC_CR_OSCE(0);
    RTC->IER = 0;
    RTC->TSR = 0;
    RTC->SR |= RTC_SR_TCE_MASK;
}

/**
 *******************************************************************************
 * @brief            Creates a delay based on RTC polling.
 *
 * @param[in]        seconds Duration of the delay in seconds.
 * @param[out]       None
 * @return           None
 *******************************************************************************
 */
void delay(uint32_t seconds) {
    uint32_t start_time = RTC->TSR;  // Get current RTC time
    uint32_t end_time = start_time + seconds;

    while (RTC->TSR < end_time) {
    }
}



