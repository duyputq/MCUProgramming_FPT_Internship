#include "MKE16Z4.h"

#define DELAY_CNT               (3000000)
#define GREEN_LED_PIN           (1 << 4)
#define RED_LED_PIN             (1 << 5)

void initLed();
void delay();

int main(void)
{
    initLed();

    printf("Xin chao!!");

    while (1)
    {
        delay();

        FGPIOB->PTOR |= (GREEN_LED_PIN | RED_LED_PIN);
    }
}

void initLed()
{
    PCC->CLKCFG[PCC_PORTB_INDEX] |= PCC_CLKCFG_CGC(1);
    // PCC->CLKCFG[74] = 1<<30


    //moi 1 ping can 1 thanh ghi rieng de cau hinh cho no
    PORTB->PCR[4] |= PORT_PCR_MUX(1); //1 << 8;
    PORTB->PCR[5] |= PORT_PCR_MUX(1);

    FGPIOB->PDDR |= GREEN_LED_PIN | RED_LED_PIN; //cau hinh den do, den xanh?
    //set cai bit thu 4 va thu 5 (1<<4, 1<<5)cua thanh ghi PDDR nay

    //clear bit so 5
    FGPIOB->PDOR &= ~RED_LED_PIN; //mau do -> led do se sang
    //luu y: khong phai cu clear di la no se tat dau


    //set cai bit so 4
    FGPIOB->PDOR |= GREEN_LED_PIN; //mau xanh la cay -> led xanh se tat

}

void delay()
{
    uint32_t i;
    for (i = 0; i < DELAY_CNT; i++)
    {
        __asm("nop"); /*lenh assembly*/
    }
}
