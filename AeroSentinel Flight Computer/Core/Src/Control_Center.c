/*
 * Control_Center.c
 *
 *  Created on: Jul 15, 2023
 *      Author: yaxsomo
 */

#include "Control_Center.h"
#include <stdbool.h>
#include <stdlib.h>
#include "fatfs.h"
#include "BlackBox.h"
#include "pyro.h"
#include "time.h"
//#include "e220.h"
#include "e22900t22d.h"

extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart6;


// **************** RTOS SECTION **************** //

// Define a semaphore to signal when to start the menu
//osSemaphoreId_t menuSemaphore;
// Declare a variable to store the current menu state
enum MenuState currentMenuState = MENU_MAIN;


// **************** END RTOS SECTION **************** //




//LORA SECTION DECLARATION

/*
	// SENDER

	uint8_t send_buffer[32]="Hello There!";
	int16_t result;
	uint8_t all_reg_tx[8];
	struct LoRa_Handler LoraTX={0};

	//RECEIVER
	uint8_t receive_buffer[32];
	int16_t result;
	uint8_t all_reg_rx[8];
	struct LoRa_Handler LoraRX={0};
*/

void UART_Transmit_String(const char* str)
{
  HAL_UART_Transmit(&huart1, (uint8_t*)str, strlen(str), HAL_MAX_DELAY);
}


void UART_Transmit_Logo() {
    UART_Transmit_String("                                                                \r\n");
	UART_Transmit_String("                                                                \r\n");
	UART_Transmit_String("                            ,,								  \r\n");
	UART_Transmit_String("                           ^B$~								  \r\n");
	UART_Transmit_String("                          '$$$$|								  \r\n");
	UART_Transmit_String("                           ,$$$$/							      \r\n");
	UART_Transmit_String("                            _$$$$j							  \r\n");
	UART_Transmit_String("                             {$$$$v'							  \r\n");
	UART_Transmit_String("                              <$$$$8.						      \r\n");
	UART_Transmit_String("                               i$$$$x						      \r\n");
	UART_Transmit_String("                    ,'          I$$$$'						  \r\n");
	UART_Transmit_String("                   +$8`     |M`  %$$$n.						  \r\n");
	UART_Transmit_String("                  |$$$@.   1$$@`  'W$$$W'					      \r\n");
	UART_Transmit_String("                 t$$$$:   '*}|[M   '&$$$8'				      \r\n");
	UART_Transmit_String("               .u$$$$!    x8/fx$,   `@$$$%,					  \r\n");
	UART_Transmit_String("              '&$$$$+     $$$$$${    `%$$$$'					  \r\n");
	UART_Transmit_String("             .8$$$$>      $$$$$$|     `8$$$&.				      \r\n");
	UART_Transmit_String("             x$$$$l       $$$$$$}      '&$$$W'				  \r\n");
	UART_Transmit_String("           .r$$$%'        #$$$$$:       .n$$$8^				  \r\n");
 	UART_Transmit_String("          'M$$$&'       .t+$$$$@>].       /$$$$;				  \r\n");
	UART_Transmit_String("         '&$$$W'       ,$$,$$$$)f$W        x$$$$!			      \r\n");
	UART_Transmit_String("        '8$$$&.        !$$;t$$$`@$$        '8$$$$<			  \r\n");
	UART_Transmit_String("       ,B$$$B`         !$$>.^;..$$$         'c$$$$1			  \r\n");
	UART_Transmit_String("      '$$$$%`          '+^. ^>  ':{           j$$$$-			  \r\n");
	UART_Transmit_String("     .&$$$8'            .^' ^!  '`             t$$$$:		      \r\n");
	UART_Transmit_String("    'W$$$&'            '`   `;   .^             /$$$$I		  \r\n");
	UART_Transmit_String("   ^8$$$n.                  `,                   +$$$$]		  \r\n");
	UART_Transmit_String("  ;$$$$/                    .^                    ,$$$$j		  \r\n");
	UART_Transmit_String(" !$$$$x                     .'                     _$$$$x.	  \r\n");
	UART_Transmit_String(" .....                       .                      .....	      \r\n");

}


//-------------------------   RTOS DEDICATED FUNCTIONS --------------------------------//


// Function to wait for the start command ('00$')
bool waitForStartCommand(void) {
    char inputBuffer[4] = {0}; // Buffer to store received command

    // Read user input character by character until we encounter '$'
    for (int bufferIndex = 0; bufferIndex < 3; bufferIndex++) {
        HAL_UART_Receive(&huart1, (uint8_t *)&inputBuffer[bufferIndex], sizeof(char), HAL_MAX_DELAY);
    }

    // Null-terminate the input buffer
    inputBuffer[3] = '\0';

    // Check if the received command is '00$'
    if (strcmp(inputBuffer, "00$") == 0) {
        return true; // If '00$' is received, return true
    } else {
        return false; // If not received, return false
    }
}



// Function to wait for user input
char waitForUserInput(void) {
    char userInput = 0;

    // Wait for user input (single character)
    HAL_UART_Receive(&huart1, (uint8_t*)&userInput, 1, HAL_MAX_DELAY);

    // Return the received character
    return userInput;
}



// Function to print the menu based on the current state
void printMenu(enum MenuState state) {
    switch (state) {
        case MENU_MAIN:
        	UART_Transmit_String("\r\n");
            UART_Transmit_String("0 - Initialize Flight Computer\r\n");
            UART_Transmit_String("1 - Read All Sensors\r\n");
            UART_Transmit_String("2 - LoRa Test (Sender)\r\n");
            UART_Transmit_String("3 - LoRa Test (Receiver)\r\n");
            UART_Transmit_String("4 - Execute Pyro Test (Ignition)\r\n");
            UART_Transmit_String("5 - Execute Pyro Test (Parachute)\r\n");
            UART_Transmit_String("6 - Launch Procedure\r\n");
            UART_Transmit_String("\r\n");
            break;
        case MENU_INIT:
            UART_Transmit_String("Initializing the Flight Controller...\r\n");
            break;
        case MENU_SENSOR_READINGS:
            UART_Transmit_String("Reading Sensors...\r\n");
            break;
        case MENU_LORA_SEND:
            UART_Transmit_String("Running LoRa SENDING Test...\r\n");
            break;
        case MENU_LORA_RECEIVE:
            UART_Transmit_String("Running LoRa RECEIVING Test...\r\n");
            break;
        case MENU_IGNITION:
            UART_Transmit_String("Starting Firing test (Ignition)...\r\n");
            break;
        case MENU_PARACHUTE:
            UART_Transmit_String("Starting Firing test (Parachute)...\r\n");
            break;
        case MENU_LAUNCH:
            UART_Transmit_String("Launching Procedure...\r\n");
            break;
        default:
            break;
    }
}



// Function to handle user input and change the current state
void handleUserInput(char command) {
    switch (command) {
        case '0':
            currentMenuState = MENU_INIT;
            break;
        case '1':
            currentMenuState = MENU_SENSOR_READINGS;
            break;
        case '2':
            currentMenuState = MENU_LORA_SEND;
            break;
        case '3':
            currentMenuState = MENU_LORA_RECEIVE;
            break;
        case '4':
            currentMenuState = MENU_IGNITION;
            break;
        case '5':
            currentMenuState = MENU_PARACHUTE;
            break;
        case '6':
            currentMenuState = MENU_LAUNCH;
            break;
        default:
            UART_Transmit_String("Invalid command! Try again.\r\n");
            break;
    }
}



//-------------------------   END RTOS DEDICATED FUNCTIONS --------------------------------//



void printIntroTitle()
{
	UART_Transmit_Logo();
    UART_Transmit_String("*********************************************************\r\n");
    UART_Transmit_String("*               AEROSENTINEL Flight OS                  *\r\n");
    UART_Transmit_String("*    A versatile flight control system for your rocket  *\r\n");
    UART_Transmit_String("*********************************************************\r\n");
    mount_sd_card();
    check_free_space();




    //scanSingleUARTDevice(&huart1); // Checks for UART devices connected


}

void main_lora_packet_receive(uint8_t* dataPacket, uint8_t size)
{
	uint8_t loraPacket[MAX_DATA_PACKET_SIZE] = {0};
	//Copy data to the main layer
	memcpy(&loraPacket, dataPacket, size);
	// TODO: implement main layer packet handling
}

/**
 * @brief 	UART data transmission complete callback over DMA
 *
 * @param 	huart	:	Pointer to the UART handler
 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	//Change the TX line state to ready
	e22_lora_make_ready();
}
/**
 * @brief 	UART data reception complete callback over DMA
 *
 * @param 	huart	:	Pointer to the UART handler
 *
 * @param 	Size	:	Packet size received over UART
 */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	e22_lora_reception_complete(Size);
}

/**
 * @brief 	LoRa module transceiver mode selection.  when this mode is active, the module configuration can't be modified.
 *
 *
 */
void main_e22_transceiverMode(void)
{
	//M0
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
	//M1
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);

}
/**
 * @brief 	LoRa module config mode selection. when this mode is active, wireless communication is inactive.
 *
 */
void main_e22_configurationMode(void)
{
	//M0
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
	//M1
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
}

void lora_transmit(){

	 const uint8_t packetSize = 4;

	 const uint8_t receiverAddress = 0x09;

	 const uint8_t ComChannel = 0x12;

	 uint8_t packet[5] = "ping";

	for(int i=0; i< 20; i++)
	{

		e22_lora_transnit(packet, packetSize, receiverAddress, ComChannel);

	}
}


int32_t initialization_procedure(){


	  int32_t fc_initialization_state;


	  UART_Transmit_String("Starting initialization process.. \r\n");
	  int32_t imu_init_state = IMU_Initialization();
	  char imu_buffer[100];

	  HAL_Delay(100);

	  sprintf(imu_buffer, "IMU Initialization. Code : %ld  \r\n", imu_init_state);
	  UART_Transmit_String(imu_buffer);

	  HAL_Delay(100);

	  int32_t pressure_init_state = Pressure_Init();
	  char pressure_buffer[100];
	  sprintf(pressure_buffer, "Pressure Initialization. Code : %ld  \r\n", pressure_init_state);
	  UART_Transmit_String(pressure_buffer);

	  HAL_Delay(100);

	  int32_t magnetometer_init_state = QMC_init(&hi2c1, 200);
	  char magneto_buffer[100];
	  sprintf(magneto_buffer, "Magnetometer Initialization. Code : %ld  \r\n", magnetometer_init_state);
	  UART_Transmit_String(magneto_buffer);

	  HAL_Delay(100);


	  e22_lora_init(&huart6, HAL_UART_Transmit_DMA, HAL_UARTEx_ReceiveToIdle_DMA,main_lora_packet_receive,main_e22_configurationMode,main_e22_transceiverMode);






	  fc_initialization_state = imu_init_state + pressure_init_state + magnetometer_init_state;

	  return fc_initialization_state;
}


void sensors_readings() {
    // Call each sensor function and receive the data structures


    IMUData imu_data = IMU_Data_Read();
    TemperatureData temperature_data = Transmit_Temperature();
    PressureTempData pressure_temp_data = Transmit_Pressure_Temp_Data();
    CompassData compass_data = Transmit_Compass_Data();



    // Print the data for each sensor and append to the file
    char buffer[200];

    // Format IMU data into the buffer
    sprintf(buffer,"Roll=%.3f° | Pitch=%.3f° | Yaw=%.3f \r\n",imu_data.roll, imu_data.pitch, compass_data.heading);
    UART_Transmit_String(buffer);

	sprintf(buffer, "IMU Data: \n"
		"Acceleration (X=%.3f g, Y=%.3f g, Z=%.3f g), \r\n"
		"Angular Rate (X=%4.2f dps, Y=%4.2f dps, Z=%4.2f dps), \r\n", // Note the '\r' to return to the beginning of the line
		imu_data.acceleration_x, imu_data.acceleration_y, imu_data.acceleration_z,
		imu_data.angular_rate_x, imu_data.angular_rate_y, imu_data.angular_rate_z);
    UART_Transmit_String(buffer);
    append_data_to_file("data.txt", buffer);

    // Concatenate temperature data to buffer
    sprintf(buffer, "Temperature: %.2f°C \r\n", temperature_data.temperature_celsius/100);
    UART_Transmit_String(buffer);
    append_data_to_file("data.txt", buffer);

    // Concatenate pressure and temperature data to buffer
    sprintf(buffer, "PRESSURE : %.2f hPa, TEMPERATURE : %.2f°C\r\n",
            pressure_temp_data.pressure_hpa, pressure_temp_data.temperature_celsius);
    UART_Transmit_String(buffer);
    append_data_to_file("data.txt", buffer);

    // Concatenate compass data to buffer
    //sprintf(buffer, "HEADING (YAW): %.1f\r\n", compass_data.heading);
    //UART_Transmit_String(buffer);
    //append_data_to_file("data.txt", buffer);

    UART_Transmit_String("------------------------------------------------------ \r\n");
    // Append the separator to the file
    append_data_to_file("data.txt", "------------------------------------------------------ \r\n");
}






// Send data to Ground Control System Software
void send_data_to_gcs(int datatype, float value) {
	// Print the data for each sensor and append to the file
	char gcs_buffer[200];


    // Print data in the specified format
    sprintf(gcs_buffer, "%d, %.2f;\r\n",
            datatype, value);

    UART_Transmit_String(gcs_buffer);

    HAL_Delay(15);


}

void sensors_readings_graphs() {
    // Call each sensor function and receive the data structures
    IMUData imu_data = IMU_Data_Read();
    TemperatureData temperature_data = Transmit_Temperature();
    PressureTempData pressure_temp_data = Transmit_Pressure_Temp_Data();
    CompassData compass_data = Transmit_Compass_Data();


    // Print IMU data
    send_data_to_gcs(1, imu_data.acceleration_x);
    send_data_to_gcs(2, imu_data.acceleration_y);
    send_data_to_gcs(3, imu_data.acceleration_z);
    send_data_to_gcs(4, imu_data.angular_rate_x);
    send_data_to_gcs(5, imu_data.angular_rate_y);
    send_data_to_gcs(6, imu_data.angular_rate_z);

    //Print Roll and Pitch data
    send_data_to_gcs(7, imu_data.roll);
    send_data_to_gcs(8, imu_data.pitch);

    // Print temperature data
    send_data_to_gcs(9, temperature_data.temperature_celsius / 100);

    // Print pressure and temperature data
    send_data_to_gcs(10, pressure_temp_data.pressure_hpa);
    send_data_to_gcs(11, pressure_temp_data.temperature_celsius);

    // Print compass data
    send_data_to_gcs(12, compass_data.heading);
}







// Modify the menu function to use the current state
void menu(char command) {
    int transmission_delay = 50; // In Milliseconds
    handleUserInput(command);
    switch (currentMenuState) {
        case MENU_MAIN:

            break;
        case MENU_INIT:
            if (currentMenuState == MENU_INIT) {
                uint32_t initialization_state = initialization_procedure();
                if (initialization_state != 0) {
                    UART_Transmit_String("Error initializing the Flight Controller.\r\n");
                } else {
                    UART_Transmit_String("Flight Controller Initialized successfully!\r\n");
                }
            }
            break;
        case MENU_SENSOR_READINGS:
            if (currentMenuState == MENU_SENSOR_READINGS) {
                uint32_t numIterations = getNumberOfIterations();
                UART_Transmit_String("\r\n");
                for (uint32_t i = 0; i < numIterations; i++) {
                    sensors_readings();
                    HAL_Delay(transmission_delay);
                }
            }
            break;
        case MENU_LORA_SEND:
            lora_transmit();
            break;
        case MENU_LORA_RECEIVE:
            e22_lora_manager();
            break;
        case MENU_IGNITION:
            if (currentMenuState == MENU_IGNITION) {
                UART_Transmit_String("\r\n");
                UART_Transmit_String("Starting Firing test (Ignition)\r\n");
                UART_Transmit_String("Arming the igniter...");
                pyro_arm(1);
                UART_Transmit_String("Armed\r\n");
                count_down_sequence_fire_test(5000);
                pyro_fire(1);
                UART_Transmit_String("Test Completed Successfully!\r\n");
                HAL_Delay(1000);
            }
            break;
        case MENU_PARACHUTE:
            if (currentMenuState == MENU_PARACHUTE) {
                UART_Transmit_String("\r\n");
                UART_Transmit_String("Starting Firing test (Parachute)\r\n");
                UART_Transmit_String("Arming the igniter...");
                pyro_arm(2);
                UART_Transmit_String("Armed\r\n");
                count_down_sequence_fire_test(5000);
                pyro_fire(2);
                UART_Transmit_String("Test Completed Successfully!\r\n");
                HAL_Delay(1000);
            }
            break;
        case MENU_LAUNCH:
            if (currentMenuState == MENU_LAUNCH) {
                launch_procedure(10000);
                while (1) {
                    sensors_readings_graphs();
                }

            }
            break;
        default:
            break;
    }

    currentMenuState = MENU_MAIN; // Return to the main menu
    printMenu(currentMenuState);
}




// Function to get the number of iterations from the user
uint32_t getNumberOfIterations()
{
    char inputBuffer[10];
    char inputChar;
    int bufferIndex = 0;

    // Ask for the number of iterations
    UART_Transmit_String("\r\nEnter the number of iterations[Finish the integer with '$']: ");

    // Read user input character by character until we encounter '\n'
    do
    {
        HAL_UART_Receive(&huart1, (uint8_t *)&inputChar, sizeof(inputChar), HAL_MAX_DELAY);
        inputBuffer[bufferIndex++] = inputChar;
    } while (inputChar != '$');

    // Null-terminate the input buffer
    inputBuffer[bufferIndex] = '\0';

    // Convert the input string to an integer using atoi
    int userInput = atoi(inputBuffer);

    return userInput;
}


void launch_procedure(int countdown_duration_ms) {

	UART_Transmit_String("Launch procedure starting.... \r\n");

    int count_down_print = countdown_duration_ms / 1000;

    // Calculate the number of SysTick ticks required for the countdown
    uint32_t ticks_start = HAL_GetTick();
    uint32_t ticks_end = ticks_start + countdown_duration_ms;

    char count_down_str[5]; // Buffer to store the countdown value as a string

    // Loop until the countdown duration is over
    while (HAL_GetTick() < ticks_end) {
    	if(count_down_print <= (countdown_duration_ms / 1000)) {
        // Toggle the buzzer (set the GPIO pin high and then low with a delay to produce sound)
        HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_SET);

        // Convert the countdown value to a string
        sprintf(count_down_str, "%d...", count_down_print);

        // Transmit the countdown value via UART
        UART_Transmit_String(count_down_str);

        HAL_Delay(200); // Delay for 200 milliseconds (adjust the value as needed)

        HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);
        HAL_Delay(800); // Delay for 800 milliseconds (adjust the value as needed)
    	}
        count_down_print--;
    }

    pyro_arm(1);
    // Enable the buzzer at the end of the countdown (Launching the test!!!)
    HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_SET);
    pyro_fire(1);
    HAL_Delay(800);
    HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);

}


void count_down_sequence_fire_test(int countdown_duration_ms) {

    int count_down_print = countdown_duration_ms / 1000;

    // Calculate the number of SysTick ticks required for the countdown
    uint32_t ticks_start = HAL_GetTick();
    uint32_t ticks_end = ticks_start + countdown_duration_ms;

    char count_down_str[5]; // Buffer to store the countdown value as a string

    // Loop until the countdown duration is over
    while (HAL_GetTick() < ticks_end) {
        // Toggle the buzzer (set the GPIO pin high and then low with a delay to produce sound)
        HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_SET);

        // Convert the countdown value to a string
        sprintf(count_down_str, "%d...", count_down_print);

        // Transmit the countdown value via UART
        UART_Transmit_String(count_down_str);

        HAL_Delay(200); // Delay for 200 milliseconds (adjust the value as needed)

        HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);
        HAL_Delay(800); // Delay for 800 milliseconds (adjust the value as needed)
        count_down_print--;
    }

    // Enable the buzzer at the end of the countdown (Launching the test!!!)
    HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_SET);
    HAL_Delay(800);
    HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);

}



void scanI2CDevices()
{
  uint8_t address;
  //uint8_t buffer[1];
  char output[100];  // Adjust the buffer size as per your requirements

  UART_Transmit_String("Scanning I2C bus...\r\n");

  for (address = 1; address <= 127; address++)
  {
    HAL_StatusTypeDef status = HAL_I2C_IsDeviceReady(&hi2c1, address << 1, 1, HAL_MAX_DELAY);
    if (status == HAL_OK)
    {
      sprintf(output, "Device found at address 0x%02X\r\n", address);
      UART_Transmit_String(output);
    }
  }

  UART_Transmit_String("Scanning complete.\r\n");
}



void scanSingleUARTDevice(UART_HandleTypeDef *huart)
{
  char output[100];  // Adjust the buffer size as per your requirements

  UART_Transmit_String("Scanning UART device...\r\n");

  HAL_StatusTypeDef status = HAL_UART_Init(huart); // Try to initialize the UART

  if (status == HAL_OK)
  {
    sprintf(output, "UART device found at specified huart\r\n");
    UART_Transmit_String(output);
    HAL_UART_DeInit(huart); // Deinitialize the UART after checking
  }
  else
  {
    UART_Transmit_String("UART device not found at specified huart\r\n");
  }

  UART_Transmit_String("UART scanning complete.\r\n");
}
