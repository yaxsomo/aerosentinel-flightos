/*
 * IMU.c
 *
 *  Created on: Jul 14, 2023
 *      Author: yaxsomo
 */

#include "IMU.h"
#include <string.h>
#include <stdio.h>



/**
  * @brief  Inertial Measurement Unit Initialization.
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of fs_xl in reg CTRL1_XL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */

/* Private variables ---------------------------------------------------------*/
static int16_t data_raw_acceleration[3];
static int16_t data_raw_angular_rate[3];
static float acceleration_mg[3];
static float angular_rate_mdps[3];
int32_t gyro_offset[3] = {0}; // Gyroscope offset for X, Y, Z axes
int32_t acc_offset[3] = {0};  // Accelerometer offset for X, Y, Z axes
static uint8_t whoamI, rst;
stmdev_ctx_t device;
extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart1;
IMUData imu_data;


void UART_Transmit_Messages_IMU(const char* str)
{
  HAL_UART_Transmit(&huart1, (uint8_t*)str, strlen(str), HAL_MAX_DELAY);
}

// Define the read function
int32_t platform_read(I2C_HandleTypeDef *handle, uint8_t reg, uint8_t *bufp, uint16_t len)
{

  // Perform the I2C read operation using HAL_I2C_Mem_Read
  HAL_StatusTypeDef status = HAL_I2C_Mem_Read(handle, LSM6DS3TRC_ADDRESS, reg, I2C_MEMADD_SIZE_8BIT, bufp, len, 100);

  // Return the appropriate value based on the HAL status
  return (status == HAL_OK) ? 0 : -1;
}

// Define the write function
int32_t platform_write(I2C_HandleTypeDef *handle, uint8_t reg, uint8_t *bufp, uint16_t len)
{

  // Perform the I2C write operation using HAL_I2C_Mem_Write
  HAL_StatusTypeDef status = HAL_I2C_Mem_Write(handle, LSM6DS3TRC_ADDRESS, reg, I2C_MEMADD_SIZE_8BIT, bufp, len, 100);

  // Return the appropriate value based on the HAL status
  return (status == HAL_OK) ? 0 : -1;
}



int32_t IMU_Initialization(){

	/* Initialize MEMS driver interface */
	device.write_reg = platform_write;
	device.read_reg = platform_read;
	device.handle = &hi2c1;

	/* Check device ID */
	whoamI = 0;
	lsm6ds3tr_c_device_id_get(&device, &whoamI);

	if ( whoamI != LSM6DS3TR_C_ID ) {
		return -1;
	}



	/* Restore default configuration */
	lsm6ds3tr_c_reset_set(&device, PROPERTY_ENABLE);

	do {
    lsm6ds3tr_c_reset_get(&device, &rst);
	} while (rst);

	int32_t int_set,xl_pm,xl_fs,xl_dr,xl_lp1,gy_pm,gy_fs,gy_dr,bdu,state;

	//Enabling I2C Communication
	int_set = lsm6ds3tr_c_i2c_interface_set(&device,LSM6DS3TR_C_I2C_ENABLE);


	//POWER-MODES

	//Accelerometer
	xl_pm = lsm6ds3tr_c_xl_power_mode_set(&device,LSM6DS3TR_C_XL_HIGH_PERFORMANCE);
	//Gyroscope
	gy_pm = lsm6ds3tr_c_gy_power_mode_set(&device,LSM6DS3TR_C_GY_HIGH_PERFORMANCE);

	//ACCELEROMETER

	//Setting Full-scale
	xl_fs = lsm6ds3tr_c_xl_full_scale_set(&device,LSM6DS3TR_C_2g);
	//Setting data rate
	xl_dr = lsm6ds3tr_c_xl_data_rate_set(&device,LSM6DS3TR_C_XL_ODR_833Hz);
	//Low-pass filter selection
	xl_lp1 = lsm6ds3tr_c_xl_lp1_bandwidth_set(&device,LSM6DS3TR_C_XL_LP1_ODR_DIV_2);



	//GYROSCOPE


	//Setting Full-scale
	gy_fs = lsm6ds3tr_c_gy_full_scale_set(&device,LSM6DS3TR_C_125dps);
	//Setting data scale
	gy_dr = lsm6ds3tr_c_gy_data_rate_set(&device,LSM6DS3TR_C_GY_ODR_833Hz);



	//BDU Setting
	bdu = lsm6ds3tr_c_block_data_update_set(&device,1); // O -> Disable | 1 -> ENABLE

	state = int_set + xl_pm + xl_fs + xl_dr + xl_lp1 + gy_pm + gy_fs + gy_dr + bdu;

	//UART_Transmit_Messages_IMU("Configuration successful. \r\n");

	return state;


}


int32_t IMU_Data_Read(){

	int32_t reading_state, gyro_reading, acc_reading;

	// Divide by 1000 to transofm millig (mg) in g and millidegrees per second (mdps) in degrees per second (dps)
	//GYROSCOPE
	gyro_reading = lsm6ds3tr_c_angular_rate_raw_get(&device,data_raw_angular_rate);
	angular_rate_mdps[0] = lsm6ds3tr_c_from_fs125dps_to_mdps(data_raw_angular_rate[0]) /1000.0;
	angular_rate_mdps[1] = lsm6ds3tr_c_from_fs125dps_to_mdps(data_raw_angular_rate[1]) /1000.0;
	angular_rate_mdps[2] = lsm6ds3tr_c_from_fs125dps_to_mdps(data_raw_angular_rate[2]) /1000.0;

	//ACCELEROMETER
	acc_reading = lsm6ds3tr_c_acceleration_raw_get(&device,data_raw_acceleration);
	acceleration_mg[0] = lsm6ds3tr_c_from_fs2g_to_mg(data_raw_acceleration[0]) /1000.0;
	acceleration_mg[1] = lsm6ds3tr_c_from_fs2g_to_mg(data_raw_acceleration[1]) /1000.0;
	acceleration_mg[2] = lsm6ds3tr_c_from_fs2g_to_mg(data_raw_acceleration[2]) /1000.0;

	reading_state = gyro_reading + acc_reading; // If 0 -> Success | Otherwise error code

	return reading_state;

}

int32_t IMU_Data_Read_Calibrated() {
    // IMU_Data_Read function should have been called previously to update angular_rate_mdps and acceleration_mg

	int32_t reading_state, gyro_reading, acc_reading;

	// Divide by 1000 to transofm millig (mg) in g and millidegrees per second (mdps) in degrees per second (dps)
	//GYROSCOPE
	gyro_reading = lsm6ds3tr_c_angular_rate_raw_get(&device,data_raw_angular_rate);
	angular_rate_mdps[0] = lsm6ds3tr_c_from_fs125dps_to_mdps(data_raw_angular_rate[0]) /1000.0;
	angular_rate_mdps[1] = lsm6ds3tr_c_from_fs125dps_to_mdps(data_raw_angular_rate[1]) /1000.0;
	angular_rate_mdps[2] = lsm6ds3tr_c_from_fs125dps_to_mdps(data_raw_angular_rate[2]) /1000.0;

	//ACCELEROMETER
	acc_reading = lsm6ds3tr_c_acceleration_raw_get(&device,data_raw_acceleration);
	acceleration_mg[0] = lsm6ds3tr_c_from_fs2g_to_mg(data_raw_acceleration[0]) /1000.0;
	acceleration_mg[1] = lsm6ds3tr_c_from_fs2g_to_mg(data_raw_acceleration[1]) /1000.0;
	acceleration_mg[2] = lsm6ds3tr_c_from_fs2g_to_mg(data_raw_acceleration[2]) /1000.0;


    // Apply calibration offsets to the raw data
    angular_rate_mdps[0] -= gyro_offset[0];
    angular_rate_mdps[1] -= gyro_offset[1];
    angular_rate_mdps[2] -= gyro_offset[2];


	reading_state = gyro_reading + acc_reading; // If 0 -> Success | Otherwise error code

	return reading_state;
}

void Calibrate_IMU() {

	UART_Transmit_Messages_IMU("IMU Calibration process started...");


    // Collect samples for gyroscope calibration
    for (int i = 0; i < CALIBRATION_SAMPLES; i++) {
        IMU_Data_Read(); // Read raw data from IMU
        gyro_offset[0] += angular_rate_mdps[0];
        gyro_offset[1] += angular_rate_mdps[1];
        gyro_offset[2] += angular_rate_mdps[2];
        HAL_Delay(2); // Delay between samples
    }

    // Calculate average offset for gyroscope
    gyro_offset[0] /= CALIBRATION_SAMPLES;
    gyro_offset[1] /= CALIBRATION_SAMPLES;
    gyro_offset[2] /= CALIBRATION_SAMPLES;

    // Store the calibration offsets for later use
    // (you may store them in global variables or pass them to IMU_Data_Read_Calibrated function)
    // gyro_offset[0], gyro_offset[1], gyro_offset[2] -> Gyroscope calibration offsets
    // acc_offset[0], acc_offset[1], acc_offset[2] -> Accelerometer calibration offsets
    UART_Transmit_Messages_IMU("Finished! \r\n");
}



IMUData Transmit_IMU_Data()
{

	  int32_t imu_read_state = IMU_Data_Read_Calibrated();
	  if (imu_read_state == 0){

		    imu_data.acceleration_x = acceleration_mg[0];
		    imu_data.acceleration_y = acceleration_mg[1];
		    imu_data.acceleration_z = acceleration_mg[2];
		    imu_data.angular_rate_x = angular_rate_mdps[0];
		    imu_data.angular_rate_y = angular_rate_mdps[1];
		    imu_data.angular_rate_z = angular_rate_mdps[2];

			// Calculate roll and pitch angles
			float roll = atan2(acceleration_mg[1], acceleration_mg[2]) * (180.0 / M_PI);
			float pitch = atan2(-acceleration_mg[0], sqrt(acceleration_mg[1] * acceleration_mg[1] + acceleration_mg[2] * acceleration_mg[2])) * (180.0 / M_PI);

		    imu_data.roll = roll;
		    imu_data.pitch = pitch;

		    return imu_data;
	  }	else	{

		  //Error State
		  imu_data.acceleration_x = 0.0;
		  imu_data.acceleration_y = 0.0;
		  imu_data.acceleration_z = 0.0;
		  imu_data.angular_rate_x = 0.0;
		  imu_data.angular_rate_y = 0.0;
		  imu_data.angular_rate_z = 0.0;
		  imu_data.pitch = 0.0;
		  imu_data.roll = 0.0;

	        return imu_data;
		}

}
