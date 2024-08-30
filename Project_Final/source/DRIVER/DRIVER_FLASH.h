#ifndef DRIVER_DRIVER_FLASH_H_
#define DRIVER_DRIVER_FLASH_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string.h>        /* String manipulation functions */
#include <stdint.h>        /* Standard integer types */
#include <MKE16Z4.h>       /* Microcontroller-specific definitions */

/*******************************************************************************
 * Function Prototypes
 ******************************************************************************/

/**
 * @brief  Converts two hexadecimal characters to an 8-bit unsigned integer.
 *
 * @param  high: The high nibble hexadecimal character.
 * @param  low: The low nibble hexadecimal character.
 *
 * @return Returns the 8-bit unsigned integer represented by the hex characters.
 *
 * @note   The function assumes valid hexadecimal input.
 */
uint8_t hex_to_uint8(uint8_t high, uint8_t low);

/**
 * @brief  Converts a hexadecimal string to a byte array.
 *
 * @param  hex_string: Pointer to the input hexadecimal string.
 * @param  byte_array: Pointer to the output byte array.
 * @param  length:     Length of the byte array to be filled.
 *
 * @note   The function converts pairs of hexadecimal characters from the string
 *         into bytes and stores them in the byte array.
 */
void hex_string_to_byte_array(const uint8_t *hex_string, uint8_t *byte_array, uint8_t length);

/**
 * @brief  Erases a sector of the Flash memory.
 *
 * @param  Addr: The starting address of the sector to be erased.
 *
 * @return Returns 0 if the erase operation was successful, otherwise returns
 *         a non-zero value indicating an error.
 *
 * @note   Ensure the address provided is aligned with the sector boundary.
 */
uint8_t Erase_Sector(uint32_t Addr);

/**
 * @brief  Programs a long word (32 bits) of data into Flash memory.
 *
 * @param  Address: The address in Flash memory where the data will be written.
 * @param  Data:    Pointer to the data to be written (4 bytes).
 *
 * @note   The Flash memory region should be erased before writing new data.
 */
void Program_LongWord(uint32_t Address, uint8_t *Data);

#endif /* DRIVER_DRIVER_FLASH_H_ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
