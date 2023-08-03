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
#include "KalmanFilter.h"

void printIntroTitle();
void printOptions();
int32_t initialization_procedure();
void sensors_readings();
void UART_Transmit_String(const char* str);
void handleUserCommand(char command);
uint32_t getNumberOfIterations();


#endif /* INC_CONTROL_CENTER_H_ */
