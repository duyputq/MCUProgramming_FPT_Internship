#ifndef HAL_HAL_UART_H_
#define HAL_HAL_UART_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "DRIVER_UART.h"   /* Include the UART driver header file */

/*******************************************************************************
 * Function Prototypes
 ******************************************************************************/

/**
 * @brief  Initializes the UART peripheral.
 *         This function sets up the UART hardware configuration,
 *         including baud rate, parity, stop bits, and enables the UART module.
 *
 * @note   This function must be called before using any other UART functions.
 */
void HAL_Init_UART(void);

/**
 * @brief  Sends a single character over UART.
 *
 * @param  data: The character to send. This is an 8-bit unsigned integer.
 *
 * @note   This function is blocking and waits until the transmission is complete.
 */
void HAL_SendChar(uint8_t data);

/**
 * @brief  Sends a null-terminated string over UART.
 *
 * @param  string: Pointer to the string to be sent.
 *
 * @note   This function is blocking and sends characters one by one until
 *         the null terminator is encountered.
 */
void HAL_SendString(uint8_t* string);

#endif /* HAL_HAL_UART_H_ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
