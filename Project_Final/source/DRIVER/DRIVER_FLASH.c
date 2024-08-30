/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <DRIVER_FLASH.h>

/*******************************************************************************
 * Functions
 ******************************************************************************/
uint8_t hex_to_uint8(uint8_t high, uint8_t low) {
	uint8_t high_val = 0;
	uint8_t low_val = 0;
    high_val = (high >= 'A') ? (high - 'A' + 10) : (high - '0');
    low_val = (low >= 'A') ? (low - 'A' + 10) : (low - '0');

    return (high_val << 4) | low_val;
}

void hex_string_to_byte_array(const uint8_t *hex_string, uint8_t *byte_array, uint8_t length) {
	uint8_t i = 0;

	for (i = 0; i < length; i++) {
        byte_array[i] = hex_to_uint8(hex_string[i * 2], hex_string[i * 2 + 1]);
    }
}

uint8_t Erase_Sector(uint32_t Addr) {
    while (FTFA->FSTAT == 0x00);

    if (FTFA->FSTAT != 0x80) {
        FTFA->FSTAT = 0x30;
    }

    FTFA->FCCOB0 = 0x09;

    FTFA->FCCOB1 = (uint8_t)(Addr >> 16);
    FTFA->FCCOB2 = (uint8_t)(Addr >> 8);
    FTFA->FCCOB3 = (uint8_t)(Addr >> 0);

    FTFA->FSTAT = 0x80;
    while (FTFA->FSTAT == 0x00);

    return 1;
}

void Program_LongWord(uint32_t Address, uint8_t *Data) {
    while (FTFA->FSTAT == 0x00);

    if (FTFA->FSTAT != 0x80) {
        FTFA->FSTAT = 0x30;
    }

    FTFA->FCCOB0 = 0x06;
    FTFA->FCCOB1 = (Address >> 16) & 0xFF;
    FTFA->FCCOB2 = (Address >> 8) & 0xFF;
    FTFA->FCCOB3 = (Address >> 0) & 0xFF;

    FTFA->FCCOB4 = Data[0];
    FTFA->FCCOB5 = Data[1];
    FTFA->FCCOB6 = Data[2];
    FTFA->FCCOB7 = Data[3];

    FTFA->FSTAT = 0x80;

    while (FTFA->FSTAT == 0x00);
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
