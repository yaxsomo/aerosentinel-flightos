/*
 * IMU.h
 *
 *  Created on: Jul 14, 2023
 *      Author: yaxsomo
 */

#ifndef INC_IMU_H_
#define INC_IMU_H_

#include "lsm6ds3tr-c_reg.h"
#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "motion_fx.h"
#include <string.h>
#include <stdio.h>
//#include <Compass.h>


/*
 * Variables and structures definitions
 */

#define LSM6DS3TRC_ADDRESS   0x6B << 1   // 0x6B ->   |  0x6A ->  x = x
#define TIME_ODR_12Hz5    0.08f   // 12.5 Hz -> 1 / 12.5 = 0.08 seconds
#define TIME_ODR_26Hz     0.0385f // 26 Hz -> 1 / 26 = 0.0385 seconds
#define TIME_ODR_52Hz     0.0192f // 52 Hz -> 1 / 52 = 0.0192 seconds
#define TIME_ODR_104Hz    0.0096f // 104 Hz -> 1 / 104 = 0.0096 seconds
#define TIME_ODR_208Hz    0.0048f // 208 Hz -> 1 / 208 = 0.0048 seconds
#define TIME_ODR_416Hz    0.0024f // 416 Hz -> 1 / 416 = 0.0024 seconds
#define TIME_ODR_833Hz    0.0012f // 833 Hz -> 1 / 833 = 0.0012 seconds
#define TIME_ODR_1k66Hz   0.0006f // 1.66 kHz -> 1 / 1666 = 0.0006 seconds
#define TIME_ODR_3k33Hz   0.0003f // 3.33 kHz -> 1 / 3333 = 0.0003 seconds
#define TIME_ODR_6k66Hz   0.00015f// 6.66 kHz -> 1 / 6666 = 0.00015 seconds
#define TIME_ODR_1Hz6     1.0f    // 1.6 Hz -> 1 / 1.6 = 0.625 seconds


typedef struct {
    float acceleration_x;
    float acceleration_y;
    float acceleration_z;
    float angular_rate_x;
    float angular_rate_y;
    float angular_rate_z;
    float yaw;
    float roll;
    float pitch;
} IMUData;



//Functions prototypes
int32_t platform_write(I2C_HandleTypeDef *handle, uint8_t reg, uint8_t *bufp,
                              uint16_t len);
int32_t platform_read(I2C_HandleTypeDef *handle, uint8_t reg, uint8_t *bufp,
                             uint16_t len);
int32_t IMU_Initialization();
IMUData IMU_Data_Read();


#endif /* INC_IMU_H_ */
