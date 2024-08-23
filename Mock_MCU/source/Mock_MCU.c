#include <MKE16Z4.h>
#include <stdio.h>

#define SystemCoreClock 48000000
#define BaudRate_UART 9600

//viet ham push queue

void initUART0(){
	//cau hinh xung
	PCC->CLKCFG[PCC_PORTB_INDEX] |= PCC_CLKCFG_CGC(1);
	PORTB->PCR[0] |= PORT_PCR_MUX(2);
	PORTB->PCR[1] |= PORT_PCR_MUX(2);

	//cau hinh xung cho uart
	PCC->CLKCFG[PCC_LPUART0_INDEX] |= PCC_CLKCFG_PCS(3);
	PCC->CLKCFG[PCC_LPUART0_INDEX] |= PCC_CLKCFG_PCS(1);
	SCG->FIRCDIV |= SCG_FIRCDIV_FIRCDIV2(1);

	//cau hinh UART
	LPUART0->CTRL &= ~(1<<19 | 1<< 18);
	LPUART0->CTRL &= ~(1<<4);
	LPUART0->CTRL &= ~(1<<29);
	LPUART0->CTRL &= ~(1<<13);

	//cau hinh BAUD
	LPUART0->BAUD |= 1<<17;
	LPUART0->BAUD &= ~(0b1011 << 24);
	LPUART0->BAUD = (LPUART0->BAUD &~(1<<2)) |
			LPUART_BAUD_SBR(SystemCoreClock / (BaudRate_UART * 5));

	//Enable Receiver  Interrupt
	LPUART0->CTRL |= 1<<21;
	NVIC_EnableIRQ(LPUART0_IRQn);

	LPUART0->CTRL |= (1<<19 | 1<<18);
}

void sendChar(uint8_t data){
	while(!(LPUART0->STAT & LPUART_STAT_TDRE_MASK)){}
	LPUART0->DATA = data;
}

void sendString(uint8_t *str){
	while(*str != '\0'){
		sendChar(*str++);
	}
}

void LPUART0_IRQHandler(){
	uint8_t data = 0;
	uint8_t flag = 0;
	data = LPUART0->DATA & 0xFF;

	//them vao hang doi
	//xoa khoi hang doi
}

int main(void){
	initUART0();
	return 0;
}
