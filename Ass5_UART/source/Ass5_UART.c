#include <MKE16Z4.h>
#include <string.h>
#include <stdbool.h>

#define LED_ON_DURATION 1000  // Duration for LED to stay on in milliseconds

volatile uint32_t led_on_start_time = 0;
volatile bool led_on = false;

#define GREEN_LED_PIN   (1 << 4)
#define VALID_STRING     "Hello from PC!"
#define HELLO_STRING     "Hello from MKE16Z!\r\n"
#define BUFFER_SIZE      100

volatile uint32_t systick_counter = 0;
char rx_buffer[BUFFER_SIZE];
uint8_t rx_index = 0;
char previous_char = '\0';  // Variable to store the previous character

// Function prototypes
void send_character(char character);
void send_data(const char *string, uint8_t length);
void initLedgreen(void); //main
void LPUART0_IRQHandler(void);
void initSystick(void); //main
void SysTick_Handler(void);
void init_UART(void); //main

void init_UART()
{
    // Enable clock for UART module with 48 Mhz
    PCC->CLKCFG[PCC_LPUART0_INDEX] |= (1 << 25) | (1 << 24);
    PCC->CLKCFG[PCC_LPUART0_INDEX] &= ~(1 << 26); //xoa bit 26

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
    LPUART0->BAUD &= ~(1 << 13); //tai bit thu 13 thi no stop, doc trong diagram

    // No parity bit
    LPUART0->CTRL &= ~(1 << 1); //huy enable bit

    // Enable interrupt
    LPUART0->CTRL |= 1 << 21;

    // Enable UART interrupt in NVIC
    __NVIC_EnableIRQ(LPUART0_IRQn);

    /*tai bit 18,19 thi enable transmit va receive*/
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
//hoi xem cai length nay co limit khong
void send_data(const char *string, uint8_t length) {
    for (uint8_t index = 0; index < length; index++) {
        send_character(string[index]);
    }
}

// Function to initialize the green LED
void initLedgreen(void) {
    PCC->CLKCFG[PCC_PORTB_INDEX] |= PCC_CLKCFG_CGC(1);
    PORTB->PCR[4] = PORT_PCR_MUX(1);
    FGPIOB->PDDR |= GREEN_LED_PIN;
    FGPIOB->PDOR |= GREEN_LED_PIN;  // Turn off LED (active low)
}

void LPUART0_IRQHandler(void) {
    char received_char = LPUART0->DATA & 0xFF;

    // Store received character
    if (rx_index < BUFFER_SIZE - 1) {
        rx_buffer[rx_index++] = received_char;

        // Check if we have received enough characters for a valid string
        if (rx_index >= 14) {  // Check for 14 characters
            rx_buffer[rx_index] = '\0'; // Null-terminate the string

            // Check if the received string matches VALID_STRING
            bool is_match = true;
            for (uint8_t i = 0; i < 14; i++) {
                if (rx_buffer[i] != VALID_STRING[i]) {
                    is_match = false;
                    break;
                }
            }

            if (is_match) {
                FGPIOB->PDOR &= ~GREEN_LED_PIN;  // Turn on LED (active low)
                send_data("LED ON\r\n", strlen("LED ON\r\n"));  // Send LED ON message
                led_on = true;
                led_on_start_time = systick_counter;  // Record the start time
            } else {
                FGPIOB->PDOR |= GREEN_LED_PIN;   // Turn off LED (active low)
                send_data("LED OFF\r\n", strlen("LED OFF\r\n"));  // Send LED OFF message
            }

            // Reset index for next message
            rx_index = 0;
        }
    }

    // Echo received character
    send_character(received_char);
}



void initSystick(void) {
    SysTick_Config(48000000 / 1000);  // Configure SysTick to interrupt every 1ms
}

// SysTick interrupt handler
void SysTick_Handler(void) {
    systick_counter++;

    if (led_on && (systick_counter - led_on_start_time >= LED_ON_DURATION)) {
        FGPIOB->PDOR |= GREEN_LED_PIN;  // Turn off LED (active low)
        send_data("LED OFF\r\n", strlen("LED OFF\r\n"));  // Send LED OFF message
        led_on = false;  // Reset LED state
    }

    if (systick_counter % 1000 == 0) {
        send_data(HELLO_STRING, strlen(HELLO_STRING));
    }
}


int main(void) {
    init_UART();        // Initialize UART
    initLedgreen();    // Initialize green LED
    initSystick();     // Initialize SysTick timer

    while (1) {
        // Main loop does nothing, all tasks are handled in interrupts
    }
}