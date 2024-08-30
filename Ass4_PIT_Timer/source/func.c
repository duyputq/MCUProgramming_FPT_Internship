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

/*******************************************************************************
* @brief:           Initializes the green LED on PORTB4.
* @param[in]:       None
* @param[out]:      None
* @return:          None
******************************************************************************/
void initLedgreen(void) {
    PCC->CLKCFG[PCC_PORTB_INDEX] |= PCC_CLKCFG_CGC(1);
    PORTB->PCR[4] = PORT_PCR_MUX(1);

    FGPIOB->PDDR |= GREEN_LED_PIN;
    FGPIOB->PDOR |= GREEN_LED_PIN;  // Turn off LED (active low)
}

/*******************************************************************************
* @brief:           Initializes the blue LED on PORTD1.
* @param[in]:       None
* @param[out]:      None
* @return:          None
******************************************************************************/
void initLedblue(void) {
    PCC->CLKCFG[PCC_PORTD_INDEX] |= PCC_CLKCFG_CGC(1);
    PORTD->PCR[1] = PORT_PCR_MUX(1);
    FGPIOD->PDDR |= BLUE_LED_PIN;
    FGPIOD->PDOR |= BLUE_LED_PIN;  // Turn off LED (active low)
}

/*******************************************************************************
* @brief:           Initializes the PIT for LED toggling.
* @param[in]:       None
* @param[out]:      None
* @return:          None
******************************************************************************/
void initPIT(void) {
	PCC->CLKCFG[PCC_LPIT0_INDEX] |= 3 << 24;
    PCC->CLKCFG[PCC_LPIT0_INDEX] |= PCC_CLKCFG_CGC(1);

    SCG->FIRCDIV |= 1 << 8;

    LPIT0->MCR |= 1 << 1;
    LPIT0->MCR &= ~(1 << 1);
    LPIT0->MCR |= 1 << 0;

    LPIT0->CHANNEL[0].TVAL = 48000000 - 1;
    LPIT0->CHANNEL[0].TCTRL |= LPIT_TCTRL_MODE(0);

    LPIT0->MIER |= LPIT_MIER_TIE0_MASK;

    LPIT0->MSR |= 1 << 0;

    NVIC_EnableIRQ(LPIT0_IRQn);
}

/*******************************************************************************
* @brief:           Interrupt handler for PIT channel 0.
* @param[in]:       None
* @param[out]:      None
* @return:          None
******************************************************************************/
void LPIT0_IRQHandler(void) {
    static int counter = 0;

    if (LPIT0->MSR & LPIT_MSR_TIF0_MASK) {
        LPIT0->MSR = LPIT_MSR_TIF0_MASK;

        if (counter == 0) {
            FGPIOB->PCOR = GREEN_LED_PIN;
            FGPIOD->PSOR = BLUE_LED_PIN;
        } else if (counter == 1) {
            FGPIOB->PSOR = GREEN_LED_PIN;
            FGPIOD->PCOR = BLUE_LED_PIN;
        } else if (counter == 2) {
            FGPIOD->PSOR = BLUE_LED_PIN;
        }

        counter++;
        if (counter > 2) {
            counter = 0;
        }
    }
}
/*******************************************************************************
*EOF
******************************************************************************/

