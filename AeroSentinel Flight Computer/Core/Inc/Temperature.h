/*
 * Temperature.h
 *
 *  Created on: 9 juil. 2023
 *      Author: yaxsomo
 */

#ifndef INC_TEMPERATURE_H_
#define INC_TEMPERATURE_H_


typedef struct {
    float temperature_celsius;
} TemperatureData;

/*
 * Temperature Sensor -> TMP112AIDRLR
 */
#define TEMP_SENSOR_ADDRESS 0x48 << 1  // 01001000
#define TEMP_READ_ADDRESS   0x00


void UART_Transmit_Messages_Temperature(const char* str);
TemperatureData Transmit_Temperature();

#endif /* INC_TMP112AIDRLR_H_ */


