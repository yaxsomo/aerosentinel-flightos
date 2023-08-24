/*
 * Pyro.h
 *
 *  Created on: Aug 3, 2023
 *      Author: yaxsomo
 */

#ifndef INC_PYRO_H_
#define INC_PYRO_H_

#include "stm32f4xx_hal.h"
#include <string.h>


// Define constants for pyro slots
#define PYRO_1_PIN GPIO_PIN_6  // Slot n. 7
#define PYRO_1_PORT GPIOB

#define PYRO_2_PIN GPIO_PIN_0  // Slot n. 8
#define PYRO_2_PORT GPIOA
#define PYRO_IGNITION_TIME 1000

extern UART_HandleTypeDef huart1;

// Function prototypes
void pyro_arm(int pyroSlot);
void pyro_fire(int pyroSlot);


#endif /* INC_PYRO_H_ */
