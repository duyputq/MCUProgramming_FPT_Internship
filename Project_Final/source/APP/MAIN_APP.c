/*******************************************************************************
* Includes
*******************************************************************************/
#include "MKE16Z4.h"
#include "HAL_SREC.h"
#include "HAL_QUEUE.h"
#include "HAL_UART.h"
#include "HAL_FLASH.h"

/*******************************************************************************
 * Main Functions
 ******************************************************************************/
int main () {
	HAL_Init_UART();
	HAL_Erase_Flash();

	while(1) {
		pop_queue();
		switch(error_check) {
			case ERR_RECORD_START:
				HAL_SendString((uint8_t*)"Error Record Start !\n");
				break;
			case ERR_HEX:
				HAL_SendString((uint8_t*)"Error Check Hex !\n");
				break;
			case ERR_S_TYPE:
				HAL_SendString((uint8_t*)"Error Check S !\n");
				break;
			case ERR_BYTE_COUNT:
				HAL_SendString((uint8_t*)"Error Check ByteCount !\n");
				break;
			case ERR_CHECK_SUM:
				HAL_SendString((uint8_t*)"Error Check Sum !\n");
				break;
			case ERR_TERMINATE:
				HAL_SendString((uint8_t*)"Error Check Terminate !\n");
				break;
			default:
				if(temp_queue[0] !=  '\0' && temp_queue[1] != '0'){
					get_Data(temp_queue);
					get_Address(temp_queue);
					HAL_SendString(temp_queue);
					HAL_SendChar('\n');
					Write_to_Flash(data, address);
				}
				break;
		}

		reset_queue();
	}
}
/*******************************************************************************
* EOF
*******************************************************************************/
