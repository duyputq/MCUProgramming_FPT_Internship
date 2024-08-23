#include "MKE16Z4.h"

//configure baud rate

void init_UART()
{
	//configure
	LPUART


}


void send_data(char *string, char length){
	int index =0;
	for(index = 0; index<length; i++){
		send_character((char)(string[index]));
	}
}


int main(void) {
	char hello[15] = "hello world";



	while(1){

	}

	return 0 ;
}
