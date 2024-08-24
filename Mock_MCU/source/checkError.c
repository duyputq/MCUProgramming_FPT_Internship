/*
 * checkError.c
 *
 *  Created on: Aug 24, 2024
 *      Author: Duy
 */
#include "checkError.h"

/*Cac ham con dung trong check error*/
void get_substring(const char* src, char* dest, uint8_t start, uint8_t length) {

	if (start < 0 || length < 0 || start + length > strlen(src)) {
		return;
	}

	strncpy(dest, src + start, length);

	dest[length] = '\0';
}

void get_address(const char* src, char* dest) {
	switch (src[1]) {
	case '1':
		get_substring(src, dest, 4, 4);
		break;
	case '2':
		get_substring(src, dest, 4, 6);
		break;
	case '3':
		get_substring(src, dest, 4, 8);
		break;
	case '9':
		get_substring(src, dest, 4, 4);
		break;
	case '8':
		get_substring(src, dest, 4, 6);
		break;
	case '7':
		get_substring(src, dest, 4, 8);
		break;
	case '0':
		get_substring("0000", dest, 0, 4);
		break;
	case '4':
		get_substring("Invalid", dest, 4, 7);
		break;
	case '5':
		get_substring(src, dest, 4, 4);
		break;
	default:
		return;
	}
}

uint16_t getByteCountInDec(const char* src) {
	char byteCount[8];
	get_substring(src, byteCount, 2, 2);
	int check = 1;
	uint16_t value = 0;
	if (byteCount[0] >= '0' && byteCount[0] <= '9') {
		value = byteCount[0] - '0';
	}
	else if (byteCount[0] >= 'A' && byteCount[0] <= 'F') {
		value = byteCount[0] - 'A' + 10;
	}
	else {
		check = 0;
	}
	if (byteCount[1] >= '0' && byteCount[1] <= '9') {
		value = value * 16 + (byteCount[1] - '0');
	}
	else if (byteCount[1] >= 'A' && byteCount[1] <= 'F') {
		value = value * 16 + (byteCount[1] - 'A' + 10);
	}
	else {
		check = 0;
	}
	if (check == 0) {
		value = 0;
	}
	return value;
}

void get_data(const char* src, char* dest) {
	uint16_t count;
	int len;
	count = getByteCountInDec(src);
	switch (src[1])
	{
	case '0':
		len = count * 2 - 6;
		get_substring(src, dest, 8, len);
		break;
	case '1':
		len = count * 2 - 6;
		get_substring(src, dest, 8, len);
		break;
	case '2':
		len = count * 2 - 8;
		get_substring(src, dest, 4, len);
		break;
	case '3':
		len = count * 2 - 10;
		get_substring(src, dest, 12, len);
		break;
	default:
		get_substring("No data", dest, 0, 7);
		break;
	}
}



/*check  = 0 la co loi, check = 1 la binh thuong*/
/*src la dong nhap vao*/
/*1*/
uint8_t check_record_start(char* src) {
	uint8_t check;
	uint8_t sub[3];
	get_substring(src, sub, 0, 2);
	uint8_t compare = strcmp(sub, "S0");
	if (compare == 0) {
		check = 1;
	}
	else {
		check = 0;
	}
	return check;
}

/*2*/
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

/*3*/
uint8_t check_byte_count(char* src) {
	uint8_t check;
	uint8_t count = getByteCountInDec(src);
	uint8_t lenByteCount = count * 2;

	uint8_t len = strlen(src);
	if (src[len - 1] == '\n') {
		src[len - 1] = '\0';
		len--;
	}

	if (lenByteCount == len - 4) {
		check = 1;
	}
	else {
		check = 0;
	}

	return check;

}
/*4*/
uint8_t check_hexa(char* src) {
	uint8_t sub[255];
	uint8_t len = strlen(src);
	get_substring(src, sub, 1, len - 1);
	uint8_t lenSub = strlen(sub);
	uint8_t check = 1;
	for (uint8_t i = 0; i < lenSub;i++) {
		if (!((sub[i] >= '0' && sub[i] <= '9') || (sub[i] >= 'A' && sub[i] <= 'F'))) {
			check = 0;
		}
	}
	return check;
}

/*5*/
/*khong dung duoc vi khong truy cap duoc totaline cua file */
// uint8_t check_data_record(const char* src, uint16_t totalLine, uint32_t line) {
// 	uint8_t check = 1;
// 	if (line == 2) {
// 		ch = src[1];
// 	}
// 	if (line > 2 && line < totalLine - 1) {

// 		if (ch != src[1]) {
// 			check = 0;
// 		}
// 	}
// 	return check;
// }


/*6*/
/*khong dung duoc vi khong truy cap duoc totaline cua file */
// uint8_t check_line_count(const char* src, uint16_t totalLine, uint32_t line) {
// 	uint16_t nearLastLine = totalLine - 1;
// 	uint8_t check;

// 	if (line == nearLastLine) {
// 		int8_t sub[10];
// 		get_address(src, sub);
// 		uint8_t len = strlen(sub);
// 		uint32_t value = 0;
// 		for (int i = 0; i < len;i++) {
// 			value *= 16;
// 			if (sub[i] >= '0' && sub[i] <= '9') {
// 				value += sub[i] - '0';
// 			}
// 			else if (sub[i] >= 'A' && sub[i] <= 'F') {
// 				value += sub[i] - 'A' + 10;
// 			}
// 			else {
// 				return -1;
// 			}
// 		}
// 		uint16_t dataLine = totalLine - 3;

// 		if (dataLine == value) {
// 			check = 1;
// 		}
// 		else {
// 			check = 0;
// 		}
// 		return check;
// 	}
// 	return 1;
// }

/*7*/
/*khong dung duoc vi khong truy cap duoc totaline cua file */
// uint8_t check_terminate(const char* src, uint16_t totalLine, uint32_t line) {
// 	uint8_t check = 1;
// 	uint16_t nearLastLine = totalLine - 1;

// 	if (line == 2) {
// 		charLineTwo = src[1];
// 	}

// 	if (line == nearLastLine) {
// 		charLineNearEnd = src[1];
// 	}
// 	if (line == totalLine) {
// 		charLineEnd = src[1];
// 		switch (charLineTwo)
// 		{
// 		case '1':
// 			if ((charLineNearEnd != '5') || (charLineEnd != '9')) {
// 				check = 0;
// 			}
// 			break;
// 		case '2':
// 			if ((charLineNearEnd != '5') || (charLineEnd != '8')) {
// 				check = 0;
// 			}
// 			break;
// 		case '3':
// 			if ((charLineNearEnd != '5') || (charLineEnd != '7')) {
// 				check = 0;
// 			}
// 			break;
// 		default:
// 			break;
// 		}
// 	}
// 	return check;
// }

/*8*/
uint8_t check_sum(const char* src) {
	uint32_t sum = 0;
	uint32_t byte;
	const char* ptr = src + 2;
	while (sscanf(ptr, "%2x", &byte) == 1) {
		sum += byte;
		ptr += 2;

		if (*(ptr + 2) == '\0') {
			break;
		}
	}
	uint8_t checksum = (~sum) & 0xFF;
	uint32_t expected_checksum;
	sscanf(src + strlen(src) - 2, "%2x", &expected_checksum);
	int check;
	if (checksum == expected_checksum) {
		check = 1;
	}
	else {
		check = 0;
	}
	return check;
}
