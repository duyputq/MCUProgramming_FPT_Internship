/*
 * func.h
 *
 *  Created on: Aug 16, 2024
 *      Author: son50
 */

#ifndef FUNC_H
#define FUNC_H

#define GREEN_LED_PIN    (1U << 4)  // FGPIOB4
#define BLUE_LED_PIN     (1 << 1)   // FGPIOD1
/*******************************************************************************
*Include
******************************************************************************/
#include "MKE16Z4.h"

/*******************************************************************************
*Definitions
******************************************************************************/
extern unsigned char led_green_on;  /**< Green LED on time (seconds) */
extern unsigned char led_green_off; /**< Green LED off time (seconds) */
extern unsigned char led_blue_on;   /**< Blue LED on time (seconds) */
extern unsigned char led_blue_off;  /**< Blue LED off time (seconds) */

/*******************************************************************************
*Protocols
******************************************************************************/
void initLedgreen(void);
void initLedblue(void);
void initRTC(void);
void delay(uint32_t seconds);

#endif // FUNC_H
