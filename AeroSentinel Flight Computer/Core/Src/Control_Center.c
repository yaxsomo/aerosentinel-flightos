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
#include "LoRa.h"

extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart1;

void UART_Transmit_String(const char* str)
{
  HAL_UART_Transmit(&huart1, (uint8_t*)str, strlen(str), HAL_MAX_DELAY);
}


void printIntroTitle()
{
    UART_Transmit_String("\r\n");
    UART_Transmit_String("*********************************************************\r\n");
    UART_Transmit_String("*               AEROSENTINEL Flight Computer           *\r\n");
    UART_Transmit_String("*    A versatile flight control system for your rocket  *\r\n");
    UART_Transmit_String("*********************************************************\r\n");
    UART_Transmit_String("               Welcome to AEROSENTINEL CLI              \r\n");
    UART_Transmit_String("*********************************************************\r\n");
    UART_Transmit_String("\r\n");
    mount_sd_card();
    check_free_space();

}

void printOptions(){
    UART_Transmit_String("\r\nChoose an option:\r\n");
    UART_Transmit_String("0 - Initialize Flight Computer\r\n");
    UART_Transmit_String("1 - Calibrate IMU\r\n");
    UART_Transmit_String("2 - Read IMU Data\r\n");
    UART_Transmit_String("3 - Read Barometer Data\r\n");
    UART_Transmit_String("4 - Read Magnetometer Data\r\n");
    UART_Transmit_String("5 - Read Temperature Sensor Data\r\n");
    UART_Transmit_String("6 - Read All Sensors\r\n");
    UART_Transmit_String("7 - Execute Kalman Filtering and Print [KO for now]\r\n");
    UART_Transmit_String("\r\n");
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




	  fc_initialization_state = imu_init_state + pressure_init_state + magnetometer_init_state;

	  return fc_initialization_state;
}


void sensors_readings() {
    // Call each sensor function and receive the data structures
    IMUData imu_data = Transmit_IMU_Data();
    TemperatureData temperature_data = Transmit_Temperature();
    PressureTempData pressure_temp_data = Transmit_Pressure_Temp_Data();
    CompassData compass_data = Transmit_Compass_Data();

    // Print the data for each sensor and append to the file
    char buffer[200];

    // Concatenate IMU data to buffer
    sprintf(buffer, "IMU Data: \r\n"
    		"Acceleration (X=%.2f g, Y=%.2f g, Z=%.2f g), \r\n"
    		"Angular Rate (X=%.2f°/s, Y=%.2f°/s, Z=%.2f°/s),\r\n"
    		"Roll=%.2f°, Pitch=%.2f° \r\n",
            imu_data.acceleration_x, imu_data.acceleration_y, imu_data.acceleration_z,
            imu_data.angular_rate_x, imu_data.angular_rate_y, imu_data.angular_rate_z,
            imu_data.roll, imu_data.pitch);
    UART_Transmit_String(buffer);
    append_data_to_file("sensor_data.txt", buffer);

    // Concatenate temperature data to buffer
    sprintf(buffer, "Temperature: %.2f°C \r\n", temperature_data.temperature_celsius/100);
    UART_Transmit_String(buffer);
    append_data_to_file("sensor_data.txt", buffer);

    // Concatenate pressure and temperature data to buffer
    sprintf(buffer, "PRESSURE : %.2f hPa, TEMPERATURE : %.2f°C\r\n",
            pressure_temp_data.pressure_hpa, pressure_temp_data.temperature_celsius);
    UART_Transmit_String(buffer);
    append_data_to_file("sensor_data.txt", buffer);

    // Concatenate compass data to buffer
    sprintf(buffer, "HEADING (YAW): %.1f\r\n", compass_data.heading);
    UART_Transmit_String(buffer);
    append_data_to_file("sensor_data.txt", buffer);

    UART_Transmit_String("------------------------------------------------------ \r\n");
    // Append the separator to the file
    append_data_to_file("sensor_data.txt", "------------------------------------------------------ \r\n");
}



void handleUserCommand(char command)
{
	int transmission_delay = 50;

	uint32_t numIterations = 0;
    switch (command)
    {
    case '0':
    	  uint32_t initialization_state = initialization_procedure();
    	  if(initialization_state != 0){
    		  UART_Transmit_String("Error initializing the Flight Controller.");
    	  } else{
    		  UART_Transmit_String("Flight Controller Initialized successfully!\n\n");
    	  }
        break;
    case '1':
			Calibrate_IMU();
        break;
    case '2':
    	numIterations = getNumberOfIterations();
    	UART_Transmit_String("\r\n----------------- \r\n");
    	UART_Transmit_String("IMU: \r\n");
		for (uint32_t i = 0; i < numIterations; i++)
		        {
			Transmit_IMU_Data();
			HAL_Delay(transmission_delay);
		        }
        break;
    case '3':
    	numIterations = getNumberOfIterations();
    	  UART_Transmit_String("\r\n----------------- \r\n");
    	  UART_Transmit_String("PRESSURE SENSOR: \r\n");
		for (uint32_t i = 0; i < numIterations; i++)
		        {
			 Transmit_Pressure_Temp_Data();
			 HAL_Delay(transmission_delay);
		        }
        break;
    case '4':
    	numIterations = getNumberOfIterations();
    	UART_Transmit_String("\r\n----------------- \r\n");
    	UART_Transmit_String("MAGNETOMETER SENSOR: \r\n");
		for (uint32_t i = 0; i < numIterations; i++)
		        {
			 Transmit_Compass_Data();
			 HAL_Delay(transmission_delay);
		        }
        break;
    case '5':
    	numIterations = getNumberOfIterations();
    	UART_Transmit_String("\r\n----------------- \r\n");
    	UART_Transmit_String("TEMPERATURE SENSOR: \r\n");
		for (uint32_t i = 0; i < numIterations; i++)
		        {
			  Transmit_Temperature();
			  HAL_Delay(transmission_delay);
		        }
        break;
    case '6':
    	UART_Transmit_String("\r\n");
    	numIterations = getNumberOfIterations();
		for (uint32_t i = 0; i < numIterations; i++)
		        {
			sensors_readings();
			HAL_Delay(transmission_delay);
		        }
        break;
    case '7':
    	UART_Transmit_String("\r\n");
    	numIterations = getNumberOfIterations();
		for (uint32_t i = 0; i < numIterations; i++)
		        {
			execute_kalman();
			HAL_Delay(transmission_delay);
		        }
        break;
    default:
        UART_Transmit_String("Invalid command! Try again.\r\n");
        break;
    }

    printOptions();
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


void initialize_lora(){

	//TODO: Make this function work

	  /*Initialize e22 LoRa module
	  e22_lora_init(&huart2,
			  	  	HAL_UART_Transmit_DMA,
					HAL_UARTEx_ReceiveToIdle_DMA,
					main_lora_packet_receive,
					main_e22_configurationMode,
					main_e22_transceiverMode);


	e22_lora_manager();

	  */



	  /* PING EXEMPLE
		 const uint8_t packetSize = 4;

		 const uint8_t receiverAddress = 0x09;

		 const uint8_t ComChannel = 0x12;

		 uint8_t packet[5] = "ping";

		 e22_lora_transnit(packet, packetSize, receiverAddress, ComChannel);
	  */

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



