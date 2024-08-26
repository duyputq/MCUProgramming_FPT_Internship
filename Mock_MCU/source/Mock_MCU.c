#include <MKE16Z4.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
//#include "checkError.h"

#define SystemCoreClock 48000000
#define BaudRate_UART 9600
#define DELAY_CNT (3000000)
#define MAX_RECORDS 300

// Global variables
char queue[4][255];
uint8_t push_index = 0;
uint8_t element_index = 0;
uint8_t pop_index = 0;
uint8_t queue_element = 0;

void initUART0() {
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
    LPUART0->DATA = character & 0xFF; // Send one character (32 bit)
}

// Function to send a string of characters over UART
void send_data(const char *str) {
    while (*str != '\0') {
        send_character(*str++);
    }
}

void Erase_Sector(uint32_t Address)
{
	// wait previous command finish
	while (FTFA->FSTAT == 0x00);

	// clear previous cmd error
	if (FTFA->FSTAT != 0x80)
	{
		FTFA->FSTAT = 0x30; // Clear 2 error flag
	}

	// Erase all bytes in a program flash sector
	FTFA->FCCOB0 = 0x09;  // command erase
	FTFA->FCCOB1 = (Address >> 16) & 0xFF;
	FTFA->FCCOB2 = (Address >> 8) & 0xFF;
	FTFA->FCCOB3 = (Address >> 0) & 0xFF;

	// run command
	FTFA->FSTAT = 0x80;

	// wait command finish
	while (FTFA->FSTAT == 0x00);

}

void Program_LongWord(uint32_t Address, uint8_t *Data)
{
	// wait previous command finish
	while (FTFA->FSTAT == 0x00);
	while (!(FTFA->FSTAT & FTFA_FSTAT_CCIF_MASK));


	// clear previous cmd error
	if (FTFA->FSTAT != 0x80)
	{
		FTFA->FSTAT = 0x30; // Clear 2 error flag
	}

	// Flash 4 bytes in a program flash sector
	FTFA->FCCOB0 = 0x06;  // command erase
	FTFA->FCCOB1 = (Address >> 16) & 0xFF;
	FTFA->FCCOB2 = (Address >> 8) & 0xFF;
	FTFA->FCCOB3 = (Address >> 0) & 0xFF;

	FTFA->FCCOB4 = Data[0];
	FTFA->FCCOB5 = Data[1];
	FTFA->FCCOB6 = Data[2];
	FTFA->FCCOB7 = Data[3];

	// run command
	FTFA->FSTAT = 0x80;

	// wait command finish
	while (FTFA->FSTAT == 0x00);

}
/*** Queue handling ***/

// Clear the specified queue row
void clear(uint8_t index) {
    uint8_t j = 0;
    while (queue[index][j] != '\0') {
        queue[index][j] = '\0';
        j++;
    }
}

// Push character into queue
void push_queue(char data) {
    // If the line ends, move to the next queue row
    if (data == '\n') {
        push_index++;
        queue_element++;

        // If the queue is full, reset to the first row
        if (push_index == 4) {
            push_index = 0;
        }

        element_index = 0;
    } else {
        queue[push_index][element_index] = data;
        element_index++;
    }
}


// Function to extract and send address and data from S-record

void extract_and_send_Srecord(const char* srecord) {
    uint8_t recordType = srecord[1];
    uint8_t addressLength = 0;

    // Determine address length based on record type
    if (recordType == '1') {
        addressLength = 4;
    } else if (recordType == '2') {
        addressLength = 6;
    } else if (recordType == '3') {
        addressLength = 8;
    } else {
        // Unsupported record type
        return;
    }

    // Convert address from string to integer
    uint32_t address = 0;
    for (uint8_t i = 4; i < 4 + addressLength; i++) {
        address = (address << 4) | ((srecord[i] >= '0' && srecord[i] <= '9') ? (srecord[i] - '0') : (toupper(srecord[i]) - 'A' + 10));
    }

    // Length of data (excluding address, checksum, and newline characters)
    uint8_t dataLength = strlen(srecord) - (4 + addressLength + 3); // Exclude address, checksum, and newline characters

    // Prepare data to write
    uint8_t data[256] = {0};
    for (uint8_t i = 4 + addressLength; i < 4 + addressLength + dataLength; i++) {
        uint8_t hexValue = (srecord[i] >= '0' && srecord[i] <= '9') ? (srecord[i] - '0') : (toupper(srecord[i]) - 'A' + 10);
        if ((i - (4 + addressLength)) % 2 == 0) {
            data[(i - (4 + addressLength)) / 2] = hexValue << 4;
        } else {
            data[(i - (4 + addressLength)) / 2] |= hexValue;
        }
    }

    // Erase sector before programming
    Erase_Sector(address);

    // Program data into flash
    for (uint8_t i = 0; i < dataLength / 4; i++) {
        Program_LongWord(address + i * 4, data + i * 4);
    }

    // Handle remaining bytes if dataLength is not a multiple of 4
    if (dataLength % 4 != 0) {
        uint8_t remainingData[4] = {0};
        memcpy(remainingData, data + (dataLength / 4) * 4, dataLength % 4);
        Program_LongWord(address + (dataLength / 4) * 4, remainingData);
    }
}

uint8_t check_S(char* src) {
	uint8_t check;
	if (src[0] == 'S') {
		check = 1;
	}
	else {
		check = 0;
	}
	return check;
}

// Process and pop data from queue
void pop_queue() {
    if (queue_element > 0) {
        // Check the first character of the line
        if (check_S(queue[pop_index]) == 1) {
            // Extract and write address and data to flash
            extract_and_send_Srecord(queue[pop_index]);
        }

        // Clear the processed line
        clear(pop_index);

        // Move to the next line in the queue
        queue_element--;
        pop_index++;

        // Reset pop index if it exceeds the queue limit
        if (pop_index == 4) {
            pop_index = 0;
        }
    }
}


void LPUART0_IRQHandler() {
    char data = LPUART0->DATA & 0xFF;

    // Check if data is not null (null character)
    if (data != '\0') {
        // Push data to queue
        push_queue(data);
    }

    // No need to pop queue here, handled in the main loop
}

void delay() {
    uint32_t i;
    for (i = 0; i < DELAY_CNT; i++) {
        __asm("nop");
    }
}

int main(void) {
    initUART0();

    while (1) {
        if (queue_element > 0) {
            // Process queue in main loop
            pop_queue();
        }

        // Add delay or perform other tasks if needed
        //delay();
    }

    return 0;
}
