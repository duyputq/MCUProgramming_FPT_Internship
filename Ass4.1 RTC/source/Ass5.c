/*******************************************************************************
*Include
******************************************************************************/
#include "func.h"
/*******************************************************************************
*Definitions
******************************************************************************/
unsigned char led_green_on = 1;  /**< Green LED on time (seconds) */
unsigned char led_green_off = 1; /**< Green LED off time (seconds) */
unsigned char led_blue_on = 1;   /**< Blue LED on time (seconds) */
unsigned char led_blue_off = 1;  /**< Blue LED off time (seconds) */

/**
 *******************************************************************************
 * MAIN
 *******************************************************************************
 */
int main(void) {
    initLedgreen();
    initLedblue();
    initRTC();

    while (1) {
        // Turn on the green LED
        FGPIOB->PCOR = GREEN_LED_PIN;
        delay(led_green_on);

        // Turn off the green LED
        FGPIOB->PSOR = GREEN_LED_PIN;
        delay(led_green_off);

        // Turn on the blue LED
        FGPIOD->PCOR = BLUE_LED_PIN;
        delay(led_blue_on);

        // Turn off the blue LED
        FGPIOD->PSOR = BLUE_LED_PIN;
        delay(led_blue_off);
    }
}
/*******************************************************************************
*EOF
******************************************************************************/
