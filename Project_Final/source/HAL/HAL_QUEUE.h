#ifndef HAL_QUEUE_H_
#define HAL_QUEUE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "HAL_SREC.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/**
 * @brief Enumeration for error codes related to queue processing.
 */
typedef enum {
    ERR_NONE,
    ERR_RECORD_START,
    ERR_S_TYPE,
    ERR_HEX,
    ERR_BYTE_COUNT,
    ERR_CHECK_SUM,
    ERR_TERMINATE,
} error_t;

#define TRUE	1
#define FALSE	0

/*******************************************************************************
 * Variables
 ******************************************************************************/
extern uint8_t queue[4][255];
extern uint8_t temp_queue[255];    /**< Temporary queue for data processing */
extern uint8_t push_index;         /**< Index in queue to push new data */
extern uint8_t element_index;      /**< Index of the current element in queue */
extern uint8_t pop_index;          /**< Index of the queue being processed */
extern uint8_t queue_element;      /**< Number of unhandled queues */
extern error_t error_check;        /**< Variable to store error codes */
extern uint8_t first_flag;         /**< Flag indicating the first queue element */
extern uint8_t terminate_flag;     /**< Flag indicating the presence of a termination record */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/**
 * @brief Clears the specified queue.
 *
 * @param queueIndex: The index of the queue to be cleared.
 *
 * @note This function sets all elements of the specified queue to '\0'.
 */
void clear(uint8_t queueIndex);

/**
 * @brief Clears the temporary queue.
 *
 * @note This function sets all elements of the temporary queue to '\0'.
 */
void clear_temp(void);

/**
 * @brief Pushes data into the current queue.
 *
 * @param data: The data char to be pushed into the queue.
 *
 * @note The data is pushed into the queue at the current `push_index`.
 */
void push_queue(uint8_t data);

/**
 * @brief Parses the queue and processes each element.
 *
 * @param line: Pointer to the line being processed from the queue.
 */
void parse_queue(uint8_t* line);

/**
 * @brief Processes and pops the current queue.
 *
 * @note This function removes the processed queue element and shifts the queue.
 */
void pop_queue(void);

/**
 * @brief Resets the entire queue system.
 *
 * @note This function clears all queues and resets indices and flags.
 */
void reset_queue(void);

#endif /* HAL_QUEUE_H_ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
