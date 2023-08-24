/*
 * TMP112AIDRLR.c
 *
 *  Created on: 9 juil. 2023
 *      Author: yaxsomo
 */

#include <Temperature.h>
#include <main.h>
extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart1;

HAL_StatusTypeDef ret;
uint8_t buffer[12];
int16_t val;
float temp_c;
TemperatureData temperature_data;

void UART_Transmit_Messages_Temperature(const char* str)
{
  HAL_UART_Transmit(&huart1, (uint8_t*)str, strlen(str), HAL_MAX_DELAY);
}


TemperatureData Transmit_Temperature(){


	buffer[0] = TEMP_READ_ADDRESS;
	//UART_Transmit_String("Reading temperature..\r\n");
	ret = HAL_I2C_Master_Transmit(&hi2c1,TEMP_SENSOR_ADDRESS,buffer,1,HAL_MAX_DELAY);
	if (ret != HAL_OK){
		UART_Transmit_String("Error communicating with Temperature sensor");
		UART_Transmit_String("\r\n");
	} else{
		ret = HAL_I2C_Master_Receive(&hi2c1,TEMP_SENSOR_ADDRESS,buffer,2,HAL_MAX_DELAY);
		if (ret != HAL_OK){
			UART_Transmit_String("Error receiving data from Temperature sensor");
			UART_Transmit_String("\r\n");
		} else {
			//Combine the bytes
			val = ((int16_t)buffer[0] << 4) | (buffer[1] >> 4);

			//Convert to 2's complement (temperature can be negative)
			if(val > 0x7FF){
				val |= 0xF000;
			}

			//Convert to float temperature value (Celsius)
			temp_c = val * 0.0625; // 0.0625 can be retreived into the datasheet

			//Convert to temperature to decimal format
			temp_c *= 100;

			temperature_data.temperature_celsius = temp_c;

			return temperature_data;

		}
	}

	//Error State
	temperature_data.temperature_celsius = -100.00;
	return temperature_data;

}
