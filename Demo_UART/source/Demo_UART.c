#include <MKE16Z4.h>
#include <string.h>

// Baud rate: 9600 bps - Data bits: 8 bits - Stop bits: 1 bit - No parity bit
void init_UART()
{
	// Enable clock for UART module with 48 Mhz
	PCC->CLKCFG[PCC_LPUART0_INDEX] |= (1 << 25) | (1<< 24);
	PCC->CLKCFG[PCC_LPUART0_INDEX] &= ~(1 << 26);

	//System Control Gate
	// Enable Fast IRC Clock Divide 2
	SCG->FIRCDIV |= 1 << 8;
	SCG->FIRCDIV &= ~(0x03 << 9); // Clear bit 9 and 10

	// Enable Clock Gate Control
	PCC->CLKCFG[PCC_LPUART0_INDEX] |= (1 <<30);

	// Enable clock for port B
	PCC->CLKCFG[PCC_PORTB_INDEX] |= 1 << 30;

	// Configure pin PB0 & PB1 as UART
	PORTB->PCR[0] |= 1 << 9;
	PORTB->PCR[0] &= ~(0x05 << 8); // 5 = 101 -> clear bit 8 and 10
	PORTB->PCR[1] |= 1 << 9;
	PORTB->PCR[1] &= ~(0x05 << 8); // 5 = 101 -> clear bit 8 and 10

	// Configure baudrate 9600 bps
	LPUART0->BAUD |= LPUART_BAUD_OSR(4); // OSR = 4
    LPUART0->BAUD |= LPUART_BAUD_SBR(1000);

    // 8 bit data
    LPUART0->CTRL &= ~(1<< 4);

    // Configure one stop bit
    LPUART0->BAUD &= ~(1<< 13);

    // No parity bit
    LPUART0->CTRL &= ~(1<< 1);

}

void send_character(char character)
{
	while (((LPUART0->STAT >> 23) & 0x01) == 0);
	LPUART0->DATA |= character & 0xFF;  // write 8 bit data from 0 -> 7

	// ....
}


void send_data (char * string, char length)
{
	int index = 0;
	for (index  = 0; index < length; index++)
	{
		send_character((char)(string[index]));
	}
}


int main()
{
	char hello[15] = "Hello world";
	init_UART();

	while(1)
	{
		// delay cho 1s de no truyen 1 lan
		send_data(hello, strlen(hello));
	}

	return 0;
}
