/*******************************************************************************
* Includes
*******************************************************************************/
#include "HAL_SREC.h"

/*******************************************************************************
* Variables
*******************************************************************************/
static uint32_t count_S1 = 0;
static uint32_t count_S2 = 0;
static uint32_t count_S3 = 0;

uint8_t data[255];
uint8_t address[8];

/*******************************************************************************
* Function
*******************************************************************************/

uint8_t HexCharToValue(uint8_t c) {
    uint8_t value = 0;

    if ((c >= '0') && (c <= '9')) {
        value = c - '0';
    }
    else if ((c >= 'A') && (c <= 'F')) {
        value = c - 'A' + 10;
    }
    else if ((c >= 'a') && (c <= 'f')) {
        value = c - 'a' + 10;
    }
    else {
    	/* do nothing */
    }

    return value;
}

uint8_t HexStringToByte(const uint8_t* hexStr) {
    uint8_t value = 0;

	value = (HexCharToValue(hexStr[0]) << 4) | HexCharToValue(hexStr[1]);

    return value;
}

uint8_t check_Hex(const uint8_t* line) {
	uint8_t index = 2;
	uint8_t checkVal = TRUE;

	while ((line[index] != '\n') && (line[index] != '\0')) {
		if ((line[index] >= '0') && (line[index] <= '9')) {
			checkVal = TRUE;
		}
		else if ((line[index] >= 'A') && (line[index] <= 'F')) {
			checkVal = TRUE;
		}
		else {
			checkVal = FALSE;
		}
		index++;
	}

	return checkVal;
}

uint8_t check_Sum(const uint8_t* line) {
    uint8_t checkVal = FALSE;
    uint8_t lineLen = 0;
    uint8_t checkSum = 0;
    uint8_t sum = 0;
    uint8_t index = 0;
    uint8_t byteVal = 0; /* value of tracking byte */

	lineLen = (uint8_t)strlen((const char*)line);
	checkSum = HexStringToByte(&line[lineLen - 2]);

    /* calculate sum of byte count, address, data field */
    for (index = 2; index < lineLen - 2; index += 2) {
        byteVal = HexStringToByte(&line[index]);
        sum += byteVal;
    }

    sum = 0xFF - (sum & 0xFF);

    if (sum == checkSum) {
        checkVal = TRUE;
    }
    else {
        checkVal = FALSE;
    }

    return checkVal;
}

uint8_t check_Bytecount(const uint8_t* line) {
    uint8_t checkVal = FALSE;
    uint8_t byteCount = 0; 		 /* value of byte count field */
    uint32_t lineLen = 0;
    uint32_t byteCountCheck = 0; /* calculate the actual value of byte count */

	byteCount = HexStringToByte(&line[2]);
	lineLen = (uint32_t)strlen((const char*)line);
	byteCountCheck = lineLen - BC_FIELD_LENGTH - STYPE_FIELD_LENGTH;

    if (byteCount == (byteCountCheck / BYTE_LENGTH)) {
        checkVal = TRUE;
    }
    else
    {
        checkVal = FALSE;
    }

    return checkVal;
}

uint8_t check_S(const uint8_t* line) {
	uint8_t checkVal = TRUE;

	if (line[0] != 'S') {
		checkVal = FALSE;
	}
	else {
		if (line[1] == '4') {
			checkVal = FALSE;
		}
		else if ((line[1] < '0') || (line[1] > '9')) {
			checkVal = FALSE;
		}
		else {
			checkVal = TRUE;
		}
	}

	return checkVal;
}

uint8_t find_Data_Type(const uint8_t* line) {
	uint8_t index = 1;
	uint8_t dataType = '1';

	if (line[index] == '1') {
		count_S1++;
	}
	else if (line[index] == '2') {
		count_S2++;
	}
	else if (line[index] == '3') {
		count_S3++;
	}
	else {
		/* do nothing */
	}

	if ((count_S1 > count_S2) && (count_S1 > count_S3)) {
		dataType = '1';
	}
	else if ((count_S2 > count_S1) && (count_S2 > count_S3)) {
		dataType = '2';
	}
	else if ((count_S3 > count_S1) && (count_S3 > count_S2)) {
		dataType = '3';
	}
	else {
		dataType = 'F';
	}

	return dataType;

}

uint8_t check_Record_Start(const uint8_t* firstLine) {
	uint8_t checkVal = TRUE;

	if ((firstLine[0] != 'S') || (firstLine[1] != '0')) {
		checkVal = FALSE;
	}
	else {
		checkVal = TRUE;
	}

	return checkVal;
}

uint8_t check_Terminate(const uint8_t* line) {
	uint8_t checkVal = TRUE;
	uint8_t data_type = 0;

	data_type = find_Data_Type(line);

	if ((line[1] == '9') || (line[1] == '8') || (line[1] == '7')) {
		if ((data_type == '1') && (line[1] == '9')) {
			checkVal = TRUE;
		}
		else if ((data_type == '2') && (line[1] == '8')) {
			checkVal = TRUE;
		}
		else if ((data_type == '3') && (line[1] == '7')) {
			checkVal = TRUE;
		}
		else {
			checkVal = FALSE;
		}
	}
	else {
		/* do nothing */
	}

	return checkVal;
}

void get_Address(const uint8_t* line) {
	uint8_t strAddress[8] = { 0, };  /* temporaray data array */
	uint8_t addressLen = 0;	           /* length of address field, max is 4 bytes = 8 chars */

	if ((line[1] == '1') || (line[1] == '0')) {
		addressLen = 4;
	}
	else if (line[1] == '2') {
		addressLen = 6;
	}
	else if (line[1] == '3') {
		addressLen = 8;
	}
	else {
		/* do nothing */
	}

	strncpy((char*)strAddress,(char*) &line[STYPE_FIELD_LENGTH + BC_FIELD_LENGTH]
	         , addressLen);
	strcpy((char*)address, (char*)strAddress);

}

void get_Data(const uint8_t* line) {
	uint8_t strData[255] = { 0, };  /* temporaray data array */
	uint8_t dataLen = 0;			/* length of data field */
	uint8_t addressLen = 0;			/* length of address field, max is 4 bytes = 8 chars */

	if ((line[1] == '1') || (line[1] == '0')) {
		addressLen = 4;
	}
	else if (line[1] == '2') {
		addressLen = 6;
	}
	else if (line[1] == '3') {
		addressLen = 8;
	}
	else {
		/* do nothing */
	}

	dataLen = strlen((char*)line) - BC_FIELD_LENGTH - STYPE_FIELD_LENGTH
	         - CS_FIELD_LENGTH - addressLen;
	strncpy((char*)strData,(char*) &line[STYPE_FIELD_LENGTH + BC_FIELD_LENGTH
	         + addressLen], dataLen);
	strcpy((char*)data, (char*)strData);


}

/*******************************************************************************
* EOF
*******************************************************************************/
