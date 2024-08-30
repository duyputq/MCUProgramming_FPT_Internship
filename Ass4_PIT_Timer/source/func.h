/*
 * func.h
 *
 *  Created on: Aug 18, 2024
 *      Author: son50
 */
/*******************************************************************************
*Define
******************************************************************************/
#ifndef FUNC_H_
#define FUNC_H_
#define GREEN_LED_PIN    (1U << 4)  // FGPIOB4
#define BLUE_LED_PIN     (1 << 1)   // FGPIOD1
/*******************************************************************************
*Include
******************************************************************************/
#include "MKE16Z4.h"

/*******************************************************************************
*Protocols
******************************************************************************/
void initLedgreen(void);
void initLedblue(void);
void initPIT(void);
void LPIT0_IRQHandler(void);

#endif /* FUNC_H_ */
