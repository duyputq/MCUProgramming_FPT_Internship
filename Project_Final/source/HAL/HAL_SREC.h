#ifndef HAL_SREC_H
#define HAL_SREC_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "MKE16Z4.h"
#include <stdint.h>
#include <string.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BC_FIELD_LENGTH		2	    /* Length of the byte count field (2 characters) */
#define STYPE_FIELD_LENGTH	2	    /* Length of the S type field (2 characters) */
#define CS_FIELD_LENGTH		2	    /* Length of the check sum field (2 characters) */
#define BYTE_LENGTH			2	    /* Length of a single hex byte (2 characters) */
#define TRUE				1
#define FALSE				0

/*******************************************************************************
 * Variables
 ******************************************************************************/
extern uint8_t queue[4][255];      /* Queue to store data for processing */
extern uint8_t data[255];          /* Data array to store extracted data */
extern uint8_t address[8];         /* Address array to store extracted addresses */

/*******************************************************************************
 * Function Prototypes
 ******************************************************************************/

/**
 * @brief  Converts a hexadecimal character to its corresponding value.
 *
 * @param  char: Hexadecimal character (0-9, A-F, a-f).
 *
 * @return Returns the value of the hex character as an 8-bit unsigned integer.
 */
uint8_t HexCharToValue(uint8_t c);

/**
 * @brief  Converts a hexadecimal string to a byte.
 *
 * @param  hexStr: Pointer to the hexadecimal string (2 characters).
 *
 * @return Returns the corresponding byte value as an 8-bit unsigned integer.
 */
uint8_t HexStringToByte(const uint8_t* hexStr);

/**
 * @brief  Checks if the given S-record line contains valid hexadecimal characters.
 *
 * @param  line: Pointer to the S-record line to be checked.
 *
 * @return Returns TRUE if the line is valid hexadecimal, otherwise FALSE.
 */
uint8_t check_Hex(const uint8_t* line);

/**
 * @brief  Check if the checksum of the given S-record line is valid.
 *
 * @param  line: Pointer to the S-record line.
 *
 * @return Returns TRUE if the check sum is valid, otherwise FALSE.
 */
uint8_t check_Sum(const uint8_t* line);

/**
 * @brief  Validates the byte count field of an S-record line.
 *
 * @param  line: Pointer to the S-record line.
 *
 * @return Returns TRUE if the byte count is valid, otherwise FALSE.
 */
uint8_t check_Bytecount(const uint8_t* line);

/**
 * @brief  Checks the type of the given S-record line.
 *
 * @param  line: Pointer to the S-record line.
 *
 * @return Returns TRUE if the S-type is valid, otherwise FALSE.
 */
uint8_t check_S(const uint8_t* line);

/**
 * @brief  Finds the type of the data record of a S-record file.
 *
 * @param  line: Pointer to the S-record line.
 *
 * @return Returns 1 if the file has S1 data type, 2 if the file has S2 data type,
 *         3 if the file has S3 data type, otherwise F.
 */
uint8_t find_Data_Type(const uint8_t* line);

/**
 * @brief  Checks if the line is the start of an S-record file.
 *
 * @param  firstLine: Pointer to the first line of the S-record file.
 *
 * @return Returns TRUE if it is the start of a file, otherwise FALSE.
 */
uint8_t check_Record_Start(const uint8_t* firstLine);

/**
 * @brief  Checks if the line is a termination record.
 *
 * @param  line: Pointer to the S-record line.
 *
 * @return Returns TRUE if it is a termination record, otherwise FALSE.
 */
uint8_t check_Terminate(const uint8_t* line);

/**
 * @brief  Extracts the address from an S-record line.
 *
 * @param  line: Pointer to the S-record line.
 */
void get_Address(const uint8_t* line);

/**
 * @brief  Extracts the data from an S-record line.
 *
 * @param  line: Pointer to the S-record line.
 */
void get_Data(const uint8_t* line);

#endif /* HAL_SREC_H */

/*******************************************************************************
 * EOF
 ******************************************************************************/
