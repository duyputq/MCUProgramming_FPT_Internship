#include <MKE16Z4.h>
#include <stdio.h>
#include <stdint.h>
//#include "checkError.h"

#define SystemCoreClock 48000000
#define BaudRate_UART 9600
#define DELAY_CNT               (3000000)

//global variables
char queue[4][255];
uint8_t push_index = 0;
uint8_t element_index = 0;
uint8_t pop_index = 0;
uint8_t queue_element = 0;
uint8_t error_check = 0;

//y nguyen ass5
void initUART0()
{
    // Enable clock for UART module with 48 MHz
    PCC->CLKCFG[PCC_LPUART0_INDEX] |= (1 << 25) | (1 << 24);
    PCC->CLKCFG[PCC_LPUART0_INDEX] &= ~(1 << 26);

    // Enable Fast IRC Clock Divide 2
    SCG->FIRCDIV |= 1 << 8;
    SCG->FIRCDIV &= ~(0x03 << 9); // Clear bit 9 and 10

    // Enable Clock Gate Control
    PCC->CLKCFG[PCC_LPUART0_INDEX] |= (1 << 30);

    // Enable clock for port B
    PCC->CLKCFG[PCC_PORTB_INDEX] |= 1 << 30;

    // Configure pin PB0 & PB1 as UART
    PORTB->PCR[0] |= 1 << 9;
    PORTB->PCR[0] &= ~(0x05 << 8); // 5 = 101 -> clear bit 8 and 10

    PORTB->PCR[1] |= 1 << 9;
    PORTB->PCR[1] &= ~(0x05 << 8); // 5 = 101 -> clear bit 8 and 10

    LPUART0->BAUD |= (1 << 17);

    // Configure baudrate 9600 bps
    LPUART0->BAUD &= ~(1 << 24);
    LPUART0->BAUD &= ~(1 << 25);
    LPUART0->BAUD &= ~(1 << 27);
    LPUART0->BAUD |= (LPUART0->BAUD & ~(1 << 2)) | LPUART_BAUD_SBR(1000);

    // 8 bit data
    LPUART0->CTRL &= ~(1 << 4);

    // Configure one stop bit
    LPUART0->BAUD &= ~(1 << 13);

    // No parity bit
    LPUART0->CTRL &= ~(1 << 1);

    // Enable interrupt
    LPUART0->CTRL |= 1 << 21;
    // Enable UART interrupt in NVIC
    __NVIC_EnableIRQ(LPUART0_IRQn);

    // Enable transmit
    LPUART0->CTRL |= 1 << 19;
    // Enable receive
    LPUART0->CTRL |= 1 << 18;
}

void send_character(char character) {
    while (((LPUART0->STAT >> 23) & 0x01) == 0); // Wait until transmit data register is empty
    LPUART0->DATA = character & 0xFF; //luu 1 ky tu don (32 bit)
}

// Function to send a string of characters over UART
void send_data(const char *str) {
	while(*str != '\0'){
		send_character(*str++);
	}
}

/***XU LY QUEUE ***/

//viet ham push queue
void clear(uint8_t index){
	uint8_t j = 0;
	while(queue[index][j] != '\0'){
		queue[index][j] = '\0';
		j++;
	}
}

//push_index la hang ma se day data vao
void push_queue(char data){
	//neu moi hang rong con lai se + vao push index
	if(data == '\0'){
		push_index++;
		queue_element++;

		//neu hang 4 thi se reset lai hang dau
		if(push_index == 4){
			push_index = 0;
		}

		element_index =0;
	} else {
		queue[push_index][element_index] = data;
		element_index++;
	}
}

//ham xu ly cac dong trong queue (cac ham import trong checkError.h)
/*void handle_queue(uint8_t* src){
	//check error
	uint8_t exception;

	if (check_S(src) == 0)
	{
		exception = 2;
	}
	else if (check_byte_count(src) == 0) {
		exception = 3;
	}
	else if (check_hexa(src) == 0) {
		exception = 4;
	}
//dang khong biet totalLine cua file
//	else if (check_data_record(src, totalLine)==0) {
//		exception = 5;
//	}
//	else if (check_line_count(src, totalLine)==0) {
//		exception = 6;
//	}
//	else if (check_terminate(src, totalLine)==0) {
//		exception = 7;
//	}
	else if (check_sum(src) == 0) {
		exception = 8;
	}
	else {
		exception = 0;
	}

	/*give priority to check record start*/
//	if (i == 1) {
//		if (check_record_start(src) == 0) {
//			exception = 1;
//			printf(output, "Wrong Start line \n");
//		}
//	}

	/*Handle Exception
	switch (exception)
	{
	case 1:
		break;
	case 2:
		send_data("Wrong First Letter \n");
		break;
	case 3:
		send_data("Wrong Byte count\n");
		break;
	case 4:
		send_data("Wrong Format\n");
		break;
	case 5:
		send_data("Wrong Data Record\n");
		break;
	case 6:
		send_data("Wrong Line Count\n");
		break;
	case 7:
		send_data("Wrong Terminate\n");
		break;
	case 8:
		send_data("Wrong Checksum\n");
		break;
	default:
		send_data("Normal");
		break;
	}
}*/

void pop_queue(){
	if(queue_element > 0){
		// Thực hiện xử lý dữ liệu trong queue tại đây
		// handle_queue(queue[pop_index]);

		// Sau khi xử lý xong, xoá dữ liệu trong hàng đợi
		clear(pop_index);

		// Tăng chỉ số pop và giảm số lượng phần tử trong queue
		queue_element--;
		pop_index++;

		// Reset lại pop_index nếu nó vượt quá 4 (tối đa 4 hàng đợi)
		if(pop_index == 4){
			pop_index = 0;
		}
	}
}

//ham xy ly chinh
void LPUART0_IRQHandler() {
    char data = LPUART0->DATA & 0xFF;

    // Echo lại dữ liệu vừa nhận
    send_character(data);

    // Đưa dữ liệu vào hàng đợi
    push_queue(data);

    if (data == '\0') {
        pop_queue();
    }
}

void delay()
{
    uint32_t i;
    for (i = 0; i < DELAY_CNT; i++) //3000000
    {
        __asm("nop");
    }
}

int main(void) {
    initUART0();

    while (1) {
        if (queue_element > 0) {
            pop_queue();
        }

        // Có thể thêm delay hoặc thực hiện các công việc khác nếu cần
        delay();
    }

    return 0;
}
