#include <MKE16Z4.h>

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

void initLed()
{
	//Peripheral Clock Control (dieu khien clock ngoai vi)
    PCC->CLKCFG[PCC_PORTB_INDEX] |= PCC_CLKCFG_CGC(1);
    PORTB->PCR[4] |= PORT_PCR_MUX(1); //cau hinh thanh ghi cho PORTB (Pin Control Register)
    FGPIOB->PDDR |= GREEN_LED_PIN; //set cai thang ghi thu tu cua cai thanh ghi PDDR nay la Green led
    FGPIOB->PDOR |= GREEN_LED_PIN; //set cai thanh ghi PDDR nay la Green led (bit thu 4)
}

void PWM(uint8_t dutyCycle)
{
    uint32_t onTime = (PWM_PERIOD * dutyCycle) / 100;
    uint32_t offTime = PWM_PERIOD - onTime;

    FGPIOB->PTOR |= GREEN_LED_PIN;  //thay doi trang thai sang xanh (Toggle)
    delay(onTime);
    FGPIOB->PTOR |= GREEN_LED_PIN; // thay doi trang thai sang xanh(Toggle)
    delay(offTime);
}



//sang dan roi tat dan
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


//sang, tat theo chu ky
void Mode2()
{
    uint32_t index;
    for (index = 0; index < 16; index++)
    {
        delay500ms();
        FGPIOB->PTOR |= GREEN_LED_PIN;
    }
}

int main (void){

    initLed();

    while (1)
    {
        Mode1();
        Mode2();
    }
	return 0;
}
