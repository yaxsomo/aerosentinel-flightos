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



/*
 * Variables and structures definitions
 */

#define    LSM6DS3TRC_ADDRESS   0x6B << 1   // 0x6B ->   |  0x6A ->  x = x
#define    BOOT_TIME            15 //ms
#define    TX_BUF_DIM           1000
#define CALIBRATION_SAMPLES 3000

typedef struct {
    float acceleration_x;
    float acceleration_y;
    float acceleration_z;
    float angular_rate_x;
    float angular_rate_y;
    float angular_rate_z;
    float roll;
    float pitch;
} IMUData;

//Functions prototypes
int32_t platform_write(I2C_HandleTypeDef *handle, uint8_t reg, uint8_t *bufp,
                              uint16_t len);
int32_t platform_read(I2C_HandleTypeDef *handle, uint8_t reg, uint8_t *bufp,
                             uint16_t len);



int32_t IMU_Initialization();
int32_t IMU_Data_Read();
void Calibrate_IMU();
int32_t IMU_Data_Read_Calibrated();
IMUData Transmit_IMU_Data();




#endif /* INC_IMU_H_ */
