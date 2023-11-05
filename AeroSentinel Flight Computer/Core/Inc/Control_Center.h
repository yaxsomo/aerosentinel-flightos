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
#include <stdbool.h>

// **************** RTOS SECTION **************** //


// Define an enum to represent the menu states
enum MenuState {
    MENU_MAIN,
    MENU_INIT,
    MENU_SENSOR_READINGS,
    MENU_LORA_SEND,
	MENU_LORA_RECEIVE,
    MENU_IGNITION,
    MENU_PARACHUTE,
    MENU_LAUNCH,
};


#define MAX_LEN 128


// ---------  RTOS FUNCTIONS PROTOTYPES ---------//
bool waitForStartCommand(void);
char waitForUserInput(void);
void printMenu(enum MenuState state);
void handleUserInput(char command);
// ---------  END RTOS FUNCTIONS PROTOTYPES ---------//



// **************** END RTOS SECTION **************** //




void UART_Transmit_Logo();
void printIntroTitle();
void printOptions();

void main_lora_packet_receive(uint8_t* dataPacket, uint8_t size);
void main_e22_configurationMode(void);
void main_e22_transceiverMode(void);
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size);
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);

int32_t initialization_procedure();
void sensors_readings();
void UART_Transmit_String(const char* str);
void menu(char command);
void launch_procedure(int countdown_duration_ms);
/*
void lora_initialize_sender();
void lora_initialize_receiver();
void lora_send();
void lora_receive();
*/
void count_down_sequence_fire_test(int countdown_duration_ms);
uint32_t getNumberOfIterations();
void scanSingleUARTDevice(UART_HandleTypeDef *huart);

#endif /* INC_CONTROL_CENTER_H_ */
