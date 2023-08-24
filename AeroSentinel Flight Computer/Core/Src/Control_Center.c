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
#include "e220.h"

extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart6;
double Va_mps = 10.0;
double T = 0.1;
double NdivT = 125;


const uint32_t SAMPLE_TIME_EKF_MS = 100;
float roll_deg = 0.0f;
float pitch_deg = 0.0f;
float yaw_deg = 0.0f;



//LORA SECTION DECLARATION

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


    //scanSingleUARTDevice(&huart1); // Checks for UART devices connected


}

void printOptions(){
    UART_Transmit_String("\r\nChoose an option:\r\n");
    UART_Transmit_String("0 - Initialize Flight Computer\r\n");
    UART_Transmit_String("1 - Read All Sensors\r\n");
    UART_Transmit_String("2 - Execute Kalman Filtering and Print [KO for now]\r\n");
    UART_Transmit_String("3 - Execute Pyro Test (Ignition)\r\n");
    UART_Transmit_String("4 - Execute Pyro Test (Parachute)\r\n");
    UART_Transmit_String("5 - Launch Procedure\r\n");
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


    IMUData imu_data = IMU_Data_Read();
    TemperatureData temperature_data = Transmit_Temperature();
    PressureTempData pressure_temp_data = Transmit_Pressure_Temp_Data();
    CompassData compass_data = Transmit_Compass_Data();

    // Print the data for each sensor and append to the file
    char buffer[200];

    // Format IMU data into the buffer
    sprintf(buffer, "IMU Data: \n"
            "Acceleration (X=%.3f g, Y=%.3f g, Z=%.3f g), \n"
            "Angular Rate (X=%4.2f dps, Y=%4.2f dps, Z=%4.2f dps), \n"
            "Roll=%.3f°, Pitch=%.3f°\r", // Note the '\r' to return to the beginning of the line
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






// Custom function to print data in the required model format
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








void menu(char command)
{
	int transmission_delay = 50; // In Milliseconds

	uint32_t numIterations = 0;
    switch (command)
    {
    case '0':
    	  uint32_t initialization_state = initialization_procedure();
    	  if(initialization_state != 0){
    		  UART_Transmit_String("Error initializing the Flight Controller.");
    	  } else{
    		  UART_Transmit_String("Flight Controller Initialized successfully!\r\n");

    	  }
    	  UART_Transmit_String("\r\n");
        break;
    case '1':
    	UART_Transmit_String("\r\n");
    	    	numIterations = getNumberOfIterations();
    			for (uint32_t i = 0; i < numIterations; i++)
    			        {
    				sensors_readings();
    				HAL_Delay(transmission_delay);
    			        }
        break;
    case '2':
    	//TODO : IMPLEMENTATION OF LORA TEST
    	break;
    case '3':
    	UART_Transmit_String("\r\n");
    	UART_Transmit_String("Starting Firing test (Ignition)\r\n");
    	UART_Transmit_String("Arming the igniter..");
    	pyro_arm(1);
    	UART_Transmit_String("Armed\r\n");
    	count_down_sequence_fire_test(5000);
    	pyro_fire(1);
    	UART_Transmit_String("Test Completed Successfully!\r\n");
    	HAL_Delay(1000);
        break;
    case '4':
    	UART_Transmit_String("\r\n");
    	UART_Transmit_String("Starting Firing test (Parachute)\r\n");
    	UART_Transmit_String("Arming the igniter..");
    	pyro_arm(2);
    	UART_Transmit_String("Armed\r\n");
    	count_down_sequence_fire_test(5000);
    	pyro_fire(2);
    	UART_Transmit_String("Test Completed Successfully!\r\n");
    	HAL_Delay(1000);
        break;
    case '5':
    	launch_procedure(10000);
    	while(1){
    		sensors_readings_graphs();
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


void lora_initialize_sender(){
 //SENDER

		int8_t packet_size= 0,data_rate= 0,broadcast_address= 0,channel= 0,normal_mode = 0;
		char sender_check[100];

		UART_Transmit_String("Sender : Configuring ports \r\n");
		LoraTX.uart_handler=&huart6;
		LoraTX.M_GPIO_PORT=GPIOA;
		LoraTX.AUX_GPIO_PORT=GPIOB;
		LoraTX.M0_PIN=GPIO_PIN_15; // PWM 1
		LoraTX.M1_PIN=GPIO_PIN_1; // PWM 2
		LoraTX.MAUX_PIN=GPIO_PIN_4; // PWM 3

		UART_Transmit_String("Sender : Entering Configuration Mode \r\n");

		while (E220_enter_config_mode(&LoraTX)!=1);


		//E220_reset(&LoraTX);

		packet_size= E220_set_packetsize_32k(&LoraTX);
		sprintf(sender_check, "Packet Size Config : %d \r\n", packet_size);
		UART_Transmit_String(sender_check);

		data_rate= E220_set_datarate_62k(&LoraTX);
		sprintf(sender_check, "Data Rate Config : %d \r\n", data_rate);
		UART_Transmit_String(sender_check);

		broadcast_address= E220_set_broadcast_address(&LoraTX);
		sprintf(sender_check, "Broadcast Address Config : %d \r\n", broadcast_address);
		UART_Transmit_String(sender_check);

		channel= E220_set_channel(&LoraTX, 4);
		sprintf(sender_check, "Channel Config : %d \r\n", channel);
		UART_Transmit_String(sender_check);

		result=E220_read_register_all(&LoraTX,all_reg_tx);

		normal_mode= E220_enter_normal_mode(&LoraTX);
		sprintf(sender_check, "Normal Mode Switch : %d \r\n", normal_mode);
		UART_Transmit_String(sender_check);

}

void lora_initialize_receiver(){

	int8_t packet_size= 0,data_rate= 0,broadcast_address= 0,channel= 0,normal_mode = 0;
	char sender_check[100];


  //RECEIVER
	UART_Transmit_String("Receiver : Configuring ports \r\n");
	  LoraRX.uart_handler=&huart6;
	  LoraRX.M_GPIO_PORT=GPIOA;
	  LoraRX.AUX_GPIO_PORT=GPIOB;
	  LoraRX.M0_PIN=GPIO_PIN_15;  // PWM 1
	  LoraRX.M1_PIN=GPIO_PIN_1; // PWM 2
	  LoraRX.MAUX_PIN=GPIO_PIN_4; // PWM 3



	  UART_Transmit_String("Receiver : Entering Configuration Mode \r\n");
	   while (E220_enter_config_mode(&LoraRX)!=1);

	   //E220_reset(&LoraRX);

	   packet_size = E220_set_packetsize_32k(&LoraRX);
		sprintf(sender_check, "Packet Size Config : %d \r\n", packet_size);
		UART_Transmit_String(sender_check);

		data_rate= E220_set_datarate_62k(&LoraRX);
		sprintf(sender_check, "Data Rate Config : %d \r\n", data_rate);
		UART_Transmit_String(sender_check);

		broadcast_address= E220_set_broadcast_address(&LoraRX);
		sprintf(sender_check, "Broadcast Address Config : %d \r\n", broadcast_address);
		UART_Transmit_String(sender_check);


		channel= E220_set_channel(&LoraRX, 4);
		sprintf(sender_check, "Channel Config : %d \r\n", channel);
		UART_Transmit_String(sender_check);


	   result=E220_read_register_all(&LoraRX,all_reg_rx);

	   normal_mode= E220_enter_normal_mode(&LoraRX);
		sprintf(sender_check, "Normal Mode Switch : %d \r\n", normal_mode);
		UART_Transmit_String(sender_check);



}


void lora_send(){


	  UART_Transmit_String("Sending..");

	  E220_transmit_payload(&LoraTX,send_buffer,32);


       //sprintf(transmission_buffer, "%p\r\n", send_buffer);
       UART_Transmit_String((char*)send_buffer);
       UART_Transmit_String("\r\n");

       HAL_Delay(1000);

}

void lora_receive(){


	  UART_Transmit_String("Receiving..");

	  E220_receive_payload(&LoraRX,receive_buffer,32);


     //sprintf(reception_buffer, "%p\r\n", receive_buffer);
     UART_Transmit_String((char*)receive_buffer);
     UART_Transmit_String("\r\n");

     HAL_Delay(500);

}
