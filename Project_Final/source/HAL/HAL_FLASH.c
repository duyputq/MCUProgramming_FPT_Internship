/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "HAL_FLASH.h"
#include <string.h>

/*******************************************************************************
 * Functions
 ******************************************************************************/
void HAL_Erase_Flash() {
	Erase_Sector(0xA000);
}

void Write_to_Flash(const uint8_t* data, const uint8_t* address) {
	uint8_t address_fl[4];
	uint8_t data_fl[128];
	uint32_t address_temp = 0x0;
	uint32_t i = 0;

	uint8_t data_len = strlen((char*) data)/2;
	uint8_t address_len = strlen((char*) address)/2;

	uint8_t hex_data[255] = {0};
	strcpy((char*)hex_data, (char*) data);

	hex_string_to_byte_array(hex_data, data_fl, data_len);

	hex_string_to_byte_array(address, address_fl, address_len);

	if(address_len == 2) {
		address_temp = (address_fl[0] << 8) + address_fl[1];
	}
	else if(address_len == 3) {
		address_temp = (address_fl[0] << 16) + (address_fl[1] << 8) + address_fl[2];
	}
	else if(address_len == 4) {
		address_temp = (address_fl[0] << 24) + (address_fl[1] << 16) + (address_fl[2] << 8)
				+ address_fl[3];
	}

	for (i = 0; i <data_len; i += 4) {
		Program_LongWord(address_temp + i, &data_fl[i]);
	}
}
/*******************************************************************************
 * EOF
 ******************************************************************************/
