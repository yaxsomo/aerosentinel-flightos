/*
 * Pyro.c
 *
 *  Created on: Aug 3, 2023
 *      Author: yaxsomo
 */

#include "pyro.h"

void UART_Transmit_Pyro(const char* str)
{
  HAL_UART_Transmit(&huart1, (uint8_t*)str, strlen(str), HAL_MAX_DELAY);
}

// Function to arm the pyro charge
void pyro_arm(int pyroSlot) {
    if (pyroSlot == 1) {
        // Arm Pyro 1 (set the GPIO pin low)
        HAL_GPIO_WritePin(PYRO_1_PORT, PYRO_1_PIN, GPIO_PIN_RESET);
    } else if (pyroSlot == 2) {
        // Arm Pyro 2 (set the GPIO pin low)
        HAL_GPIO_WritePin(PYRO_2_PORT, PYRO_2_PIN, GPIO_PIN_RESET);
    }
}

// Function to fire the pyro charge
void pyro_fire(int pyroSlot) {
    if (pyroSlot == 1) {
        // Fire Pyro 1 (set the GPIO pin high)
        HAL_GPIO_WritePin(PYRO_1_PORT, PYRO_1_PIN, GPIO_PIN_SET);
        UART_Transmit_Pyro("Ignition..");
        HAL_Delay(PYRO_IGNITION_TIME);
        HAL_GPIO_WritePin(PYRO_1_PORT, PYRO_1_PIN, GPIO_PIN_RESET);
        UART_Transmit_Pyro("Finished.\r\n");
    } else if (pyroSlot == 2) {
        // Fire Pyro 2 (set the GPIO pin high)
        HAL_GPIO_WritePin(PYRO_2_PORT, PYRO_2_PIN, GPIO_PIN_SET);
        UART_Transmit_Pyro("Ignition..");
        HAL_Delay(PYRO_IGNITION_TIME);
        HAL_GPIO_WritePin(PYRO_2_PORT, PYRO_2_PIN, GPIO_PIN_RESET);
        UART_Transmit_Pyro("Finished.\r\n");
    }
}

