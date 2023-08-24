  /***
   *               ______ _____   ____   _____ ______ _   _ _______ _____ _   _ ______ _
   *         /\   |  ____|  __ \ / __ \ / ____|  ____| \ | |__   __|_   _| \ | |  ____| |
   *        /  \  | |__  | |__) | |  | | (___ | |__  |  \| |  | |    | | |  \| | |__  | |
   *       / /\ \ |  __| |  _  /| |  | |\___ \|  __| | . ` |  | |    | | | . ` |  __| | |
   *      / ____ \| |____| | \ \| |__| |____) | |____| |\  |  | |   _| |_| |\  | |____| |____
   *     /_/    \_\______|_|  \_\\____/|_____/|______|_| \_|  |_|  |_____|_| \_|______|______|
   *                                                                 By Yassine DEHHANI
   *	 _______________________________________________
   *     |								               |
   *     | File : Control_Center.c	                   |
   *     |_____________________________________________|
   *     |								               |
   *     | Description : Serves as a                   |
   *     | workspace where all functions are executed  |
   *     |_____________________________________________|
   *
   *
   */

#ifndef INC_CONTROL_CENTER_H_
#define INC_CONTROL_CENTER_H_


#include <Compass.h>
#include "IMU.h"
#include <Pressure.h>
#include <Temperature.h>

void printIntroTitle();
void printOptions();
int32_t initialization_procedure();
void sensors_readings();
void UART_Transmit_String(const char* str);
void menu(char command);
void launch_procedure(int countdown_duration_ms);
void lora_initialize_sender();
void lora_initialize_receiver();
void lora_send();
void lora_receive();
void count_down_sequence_fire_test(int countdown_duration_ms);
uint32_t getNumberOfIterations();
void scanSingleUARTDevice(UART_HandleTypeDef *huart);

#endif /* INC_CONTROL_CENTER_H_ */
