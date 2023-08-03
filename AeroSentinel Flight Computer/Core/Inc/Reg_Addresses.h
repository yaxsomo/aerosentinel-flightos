/*
 *  Reg_Addresses.h
 *
 *  Created on: 8 juil. 2023
 *  Author: Yassine DEHHANI
 *
 *  This file contains all the register addresses required to
 *  access the following devices on Aerosentinel :
 *
 *  - IMU : LSM6DS3TR
 *  - Barometer : DPS310XTSA1
 *  - Magnetometer : QMC5883L
 *  - Temperature Sensor : TMP112AIDRLR
 *  - EEPROM : AT24C128C
 */

#ifndef INC_REG_ADDRESSES_H_
#define INC_REG_ADDRESSES_H_



#endif /* INC_REG_ADDRESSES_H_ */

/*
 * IMU -> LSM6DS3TR
 */

#define IMU_ADDRESS             0x6A   // 01101010
#define IMU_ADDRESS_2           0x6B   // 01101011

//Configuration


#define IMU_ACCEL_CONFIG_REG    0x10   // CTRL1_XL
#define IMU_GYRO_CONFIG_REG     0x11   // CTRL2_G
#define IMU_CONFIG_MEM_SIZE     1      // 1 byte
#define IMU_ACCEL_CONFIG        0xA4   // 10100100 (6.66kHz | 16g | analog chain bandwidth 1.5kHz)
#define IMU_GYRO_CONFIG         0xAC   // 10101100 (6.66kHz | 2000dps | full-scale at 125dps disabled)

//Measurements
#define IMU_READ_MEM_SIZE       1
#define IMU_READ_AXIS_BYTES     2


//Gyroscope registers
#define IMU_GYRO_F_REG          0x22 //First register of the gyroscope registers (22 to 27)
#define IMU_ACCEL_F_REG         0x28 // First register of the accelerometer registers (28 to 2D)



//Accelerometer X axis
#define IMU_ACCEL_X_L           0x28
#define IMU_ACCEL_X_H           0x23

//Accelerometer Y axis
#define IMU_ACCEL_Y_L           0x2A
#define IMU_ACCEL_Y_H           0x25

//Accelerometer Z axis
#define IMU_ACCEL_Z_L           0x2C
#define IMU_ACCEL_Z_H           0x27

//Gyroscope X axis
#define IMU_GYRO_X_L            0x22
#define IMU_GYRO_X_H            0x29

//Gyroscope Y axis
#define IMU_GYRO_Y_L            0x24
#define IMU_GYRO_Y_H            0x2B

//Gyroscope Z axis
#define IMU_GYRO_Z_L            0x26
#define IMU_GYRO_Z_H            0x2D











/*
 * Magnetometer -> QMC5883L
 */
#define MAGNETOMETER_ADDRESS           0x0D   // 00001101
#define MAGNETOMETER_CTRL_REG          0x09   // Register for Control 1
#define MAGNETOMERER_CFG               0x75   // 01110101 (Continuous mode, 200Hz Output Data Rate, 8G Full-Scale Range, 256 Over Ration Samples)
#define MAGNETOMETER_F_READ_REG        0x00   // Magnetometer fist bit to start from for reading
#define MAGNETOMETER_READ_MEM_SIZE        1   //
#define MAGNETOMETER_READ_AXIS_BYTES      2   //



/*
 * EEPROM -> AT24C128C
 */
#define EEPROM_ADDRESS 0x50   // 01010000
