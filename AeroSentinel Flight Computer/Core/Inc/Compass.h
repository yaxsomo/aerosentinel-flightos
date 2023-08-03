/*
 * QMC5883L.h
 *
 *  Created on: 11 juil. 2023
 *      Author: yaxsomo
 */

#ifndef INC_COMPASS_H_
#define INC_COMPASS_H_



//#########################################################################################################
#ifdef __cplusplus
 extern "C" {
#endif
//#########################################################################################################
#include "main.h"
#include "stm32f4xx_hal.h"
 //#########################################################################################################
#define Standby 0
#define Continuous 1
#define QMC_OK 0
#define QMC_FALSE 1
// Constants for normalization
#define MAG_MIN_VALUE -32768
#define MAG_MAX_VALUE 32767

// Variables for filtering
#define FILTER_ALPHA 0.2f
//#########################################################################################################

typedef struct QMC
{
	I2C_HandleTypeDef   *i2c;
	uint8_t				Control_Register;
	uint8_t             datas[6];
	int16_t             Xaxis;
	int16_t             Yaxis;
	int16_t             Zaxis;
	float			    heading;
	float               compas;
}QMC_t;


typedef struct {
    float heading;
    const char* direction;
} CompassData;

typedef struct {
    float min;
    float max;
    const char* direction;
} HeadingDirection;
//#########################################################################################################
void UART_Transmit_Messages_Magnetometer(const char* str);
uint32_t QMC_init(I2C_HandleTypeDef *i2c,uint8_t Output_Data_Rate);
uint8_t QMC_read();
uint8_t QMC_read_Normalize();
float   QMC_readHeading();
uint8_t QMC_Standby();
uint8_t QMC_Reset();
CompassData Transmit_Compass_Data();





//#########################################################################################################
#ifdef __cplusplus
}
#endif
#endif /* INC_COMPASS_H_ */
