#include <stdio.h>
#include <MKE16Z4.h>
#define GREEN_LED_PIN           (1 << 4)
#define RED_LED_PIN             (1 << 5)


void init_button()
{
	//cap xung
	PCC ->CLKCFG[PCC_PORTD_INDEX] |= 1 << 30;

	//cau hinh cho 2 port D như GPIO
	PORTD->PCR[2] |= (1 << 9);
	PORTD->PCR[2] &= ~(1 << 10);

	//Config GPIOD_2 as input
	GPIOD->PDDR &= ~(1 << 2);
}

void initLed()
{
    //PCC->CLKCFG[PCC_PORTB_INDEX] |= PCC_CLKCFG_CGC(1);

    PCC->CLKCFG[PCC_PORTB_INDEX] |= PCC_CLKCFG_CGC(1);

    PORTB->PCR[5] |= PORT_PCR_MUX(1);

    FGPIOB->PDDR |= GREEN_LED_PIN ;

    FGPIOB->PDOR &= ~RED_LED_PIN;

}

void PORTBCD_IRQHandler(void) //ham ngat
{
	PORTD->PCR[2] |= 1 << 24;
	FGPIOB->PTOR |= GREEN_LED_PIN;
}

int main ()
{
	initLed();
	init_button();

	while(1)
	{
		if (((GPIOD -> PDIR >> 2) & 0x01) == 0 )
		{
			//nut bam duoc nhan
			FGPIOB->PTOR |= GREEN_LED_PIN;
		}
	}

	return 0;
}
