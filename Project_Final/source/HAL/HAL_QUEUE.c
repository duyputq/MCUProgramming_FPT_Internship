/*******************************************************************************
* Include
*******************************************************************************/
#include "HAL_QUEUE.h"

/*******************************************************************************
* Variables
*******************************************************************************/

uint8_t queue[4][255];
uint8_t temp_queue[255];
uint8_t push_index = 0;
uint8_t element_index = 0;
uint8_t pop_index = 0;
uint8_t queue_element = 0;
error_t error_check = ERR_NONE;
uint8_t first_flag = FALSE;
uint8_t terminate_flag = FALSE;

/*******************************************************************************
* Function
*******************************************************************************/

void clear(uint8_t queueIndex){
	uint8_t index = 0;

	while(queue[queueIndex][index] != '\0'){
		queue[queueIndex][index] = '\0';
		index++;
	}
}

void clear_temp() {
	uint8_t index = 0;

	while(temp_queue[index] != '\0') {
		temp_queue[index] = '\0';
		index++;
	}
}

void push_queue(uint8_t data){
	if(data == '\n') {
		push_index++;
		queue_element++;

		if(push_index == 4) {
			push_index = 0;
		}
		element_index = 0;

	}
	else if(data == '\r') {
		/*do nothing*/
	}
	else {
		queue[push_index][element_index] = data;
		element_index++;
	}
}

void parse_queue(uint8_t* line){
	if(first_flag == FALSE) {
		if(!check_Record_Start(line)){
			error_check = ERR_RECORD_START;
		}
		first_flag = TRUE;
	}

	if(!check_Hex(line)) {
		error_check = ERR_HEX;
	}

	if(!check_S(line)) {
		error_check = ERR_S_TYPE;
	}

	if(!check_Bytecount(line)) {
		error_check = ERR_BYTE_COUNT;
	}

	if(!check_Sum(line)) {
		error_check = ERR_CHECK_SUM;
	}

	if(!check_Terminate(line)) {
		error_check = ERR_TERMINATE;
	}
}

void pop_queue(){
	if(queue_element > 0){
		strcpy((char*)temp_queue, (char*)queue[pop_index]);

		parse_queue(queue[pop_index]);
		queue_element--;

		if((queue[pop_index][1] == '9') || (queue[pop_index][1] == '8')
				|| (queue[pop_index][1] == '7')) {
				terminate_flag = TRUE;
				first_flag = FALSE;
		}

		clear(pop_index);
		pop_index++;

		if(pop_index == 4){
			pop_index = 0;
		}
	}
}

void reset_queue(){
	uint8_t i = 0;

	error_check = ERR_NONE;
	clear_temp();

	if(terminate_flag == TRUE) {
		for(i = 0; i < 4; i++) {
			clear(i);
		}
		terminate_flag = FALSE;
		push_index = 0;
		pop_index = 0;
	}
}
/*******************************************************************************
* EOF
*******************************************************************************/
