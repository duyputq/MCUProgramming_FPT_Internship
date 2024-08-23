
#include "MKE16Z4.h"
#include <stdio.h>

#define DELAY_CNT               (3000000)
#define DELAY_CNT_100			(100)

#define GREEN_LED_PIN           (1 << 4)
#define RED_LED_PIN             (1 << 5)

void initLed();

void Systick_Handler()
{
	FGPIOB->PTOR |= GREEN_LED_PIN ;
}

void initLed()
{
    //PCC->CLKCFG[PCC_PORTB_INDEX] |= PCC_CLKCFG_CGC(1);

    PCC->CLKCFG[PCC_PORTB_INDEX] |= PCC_CLKCFG_CGC(1);

    PORTB->PCR[5] |= PORT_PCR_MUX(1);

    FGPIOB->PDDR |= GREEN_LED_PIN ;

    FGPIOB->PDOR &= ~RED_LED_PIN;

}

int main(void) {

	initLed();
	SysTick_Config(12000000); /*san vong lap dem di dem lai*/

	while(1)
	{

	}
    return 0 ;
}
