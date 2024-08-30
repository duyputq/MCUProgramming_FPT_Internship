#ifndef HAL_HAL_FLASH_H_
#define HAL_HAL_FLASH_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "DRIVER_FLASH.h"

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/**
 * @brief  Writes data to the specified address in Flash memory.
 *
 * @param  data: Pointer to the data to be written to Flash memory.
 * @param  address: Pointer to the address in Flash memory where the data
 *                  should be written.
 */
void Write_to_Flash(const uint8_t* data, const uint8_t* address);

/**
 * @brief  Erases the Flash memory.
 *
 * @note   This function typically erases a specific sector A000 of the Flash memory.
 */
void HAL_Erase_Flash(void);

#endif /* HAL_HAL_FLASH_H_ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
