/*
 * IMU.c
 *
 *  Created on: Jul 14, 2023
 *      Author: yaxsomo
 */

#include "IMU.h"




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

static uint8_t whoamI, rst;
stmdev_ctx_t device;
extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart1;
IMUData imu_data;


#define STATE_SIZE                      (size_t)(2432)
#define GBIAS_ACC_TH_SC                 (2.0f*0.000765f)
#define GBIAS_GYRO_TH_SC                (2.0f*0.002f)
#define DECIMATION                      1U
#define FROM_MG_TO_G  0.001f
#define FROM_G_TO_MG  1000.0f
#define FROM_MDPS_TO_DPS  0.001f
#define FROM_DPS_TO_MDPS  1000.0f

static MFX_knobs_t iKnobs;
static MFX_knobs_t *ipKnobs = &iKnobs;
static uint8_t mfxstate[STATE_SIZE];





// TRASMIT MESSAGES VIA UART FUNCTION
void UART_Transmit_Messages_IMU(const char* str)
{
  HAL_UART_Transmit(&huart1, (uint8_t*)str, strlen(str), HAL_MAX_DELAY);
}

// SENSOR READING FUNCTION DEFINITION
int32_t platform_read(I2C_HandleTypeDef *handle, uint8_t reg, uint8_t *bufp, uint16_t len)
{
  // Perform the I2C read operation using HAL_I2C_Mem_Read
  HAL_StatusTypeDef status = HAL_I2C_Mem_Read(handle, LSM6DS3TRC_ADDRESS, reg, I2C_MEMADD_SIZE_8BIT, bufp, len, 100);
  // Return the appropriate value based on the HAL status
  return (status == HAL_OK) ? 0 : -1;
}

// SENSOR WRITING FUNCTION DEFINITION
int32_t platform_write(I2C_HandleTypeDef *handle, uint8_t reg, uint8_t *bufp, uint16_t len)
{
  // Perform the I2C write operation using HAL_I2C_Mem_Write
  HAL_StatusTypeDef status = HAL_I2C_Mem_Write(handle, LSM6DS3TRC_ADDRESS, reg, I2C_MEMADD_SIZE_8BIT, bufp, len, 100);
  // Return the appropriate value based on the HAL status
  return (status == HAL_OK) ? 0 : -1;
}


// IMU INITIALIZATION FUNCTION
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

	int32_t int_set,xl_fs,xl_dr,gy_fs,gy_dr,bdu,xl_fas,xl_lp,gy_bps,state;
	//int32_t dev_round_status,dev_round_mode;

	//Enabling I2C Communication
	int_set = lsm6ds3tr_c_i2c_interface_set(&device,LSM6DS3TR_C_I2C_ENABLE);

	  /* Enable Block Data Update */
	  bdu = lsm6ds3tr_c_block_data_update_set(&device, PROPERTY_ENABLE);
	  /* Set Output Data Rate */
	  xl_dr= lsm6ds3tr_c_xl_data_rate_set(&device, LSM6DS3TR_C_XL_ODR_104Hz);
	  gy_dr= lsm6ds3tr_c_gy_data_rate_set(&device, LSM6DS3TR_C_XL_ODR_104Hz);
	  /* Set full scale */
	  xl_fs= lsm6ds3tr_c_xl_full_scale_set(&device, LSM6DS3TR_C_2g);
	  gy_fs= lsm6ds3tr_c_gy_full_scale_set(&device, LSM6DS3TR_C_500dps);


	  /* Configure filtering chain(No aux interface) */
	  /* Accelerometer - analog filter */
	  xl_fas= lsm6ds3tr_c_xl_filter_analog_set(&device,
	                                   LSM6DS3TR_C_XL_ANA_BW_400Hz);
	  /* Accelerometer - LPF1 path ( LPF2 not used )*/
	  //xl_lp = lsm6ds3tr_c_xl_lp1_bandwidth_set(&device, LSM6DS3TR_C_XL_LP1_ODR_DIV_4);
	  /* Accelerometer - LPF1 + LPF2 path */
	  xl_lp= lsm6ds3tr_c_xl_lp2_bandwidth_set(&device,LSM6DS3TR_C_XL_LOW_NOISE_LP_ODR_DIV_100);
	  /* Accelerometer - High Pass / Slope path */
	  //lsm6ds3tr_c_xl_reference_mode_set(&device, PROPERTY_DISABLE);
	  //lsm6ds3tr_c_xl_hp_bandwidth_set(&device, LSM6DS3TR_C_XL_HP_ODR_DIV_100);
	  /* Gyroscope - filtering chain */
	  gy_bps= lsm6ds3tr_c_gy_band_pass_set(&device,
	                               LSM6DS3TR_C_HP_260mHz_LP1_STRONG);

	  //dev_round_status = lsm6ds3tr_c_rounding_on_status_set(&device,PROPERTY_ENABLE);
	  //dev_round_mode= lsm6ds3tr_c_rounding_mode_set(&device,LSM6DS3TR_C_ROUND_GY_XL);


		state = int_set + xl_fs + xl_dr + gy_fs + gy_dr + bdu + xl_fas + xl_lp + gy_bps;

		//UART_Transmit_Messages_IMU("Configuration successful. \r\n");


		  MotionFX_initialize((MFXState_t *)mfxstate);

		  MotionFX_getKnobs(mfxstate, ipKnobs);

		  ipKnobs->acc_orientation[0] = 'n';
		  ipKnobs->acc_orientation[1] = 'w';
		  ipKnobs->acc_orientation[2] = 'u';
		  ipKnobs->gyro_orientation[0] = 'n';
		  ipKnobs->gyro_orientation[1] = 'w';
		  ipKnobs->gyro_orientation[2] = 'u';

		  ipKnobs->gbias_acc_th_sc = GBIAS_ACC_TH_SC;
		  ipKnobs->gbias_gyro_th_sc = GBIAS_GYRO_TH_SC;

		  ipKnobs->output_type = MFX_ENGINE_OUTPUT_ENU;
		  ipKnobs->LMode = 1;
		  ipKnobs->modx = DECIMATION;

		  MotionFX_setKnobs(mfxstate, ipKnobs);
		  MotionFX_enable_6X(mfxstate, MFX_ENGINE_ENABLE);
		  MotionFX_enable_9X(mfxstate, MFX_ENGINE_DISABLE);


		return state;


}


//IMU DATA READING FUNCTION
IMUData IMU_Data_Read(){

	int32_t reading_state, gyro_reading, acc_reading;
    MFX_input_t data_in;
    MFX_output_t data_out;
    float delta_time = TIME_ODR_104Hz;
	//char test[100];


	//ACCELEROMETER RAW DATA READING
	acc_reading = lsm6ds3tr_c_acceleration_raw_get(&device,data_raw_acceleration);
	//GYROSCOPE
	gyro_reading = lsm6ds3tr_c_angular_rate_raw_get(&device,data_raw_angular_rate);


	reading_state = gyro_reading + acc_reading; // If 0 -> Success | Otherwise error code



	  if (reading_state == 0){

			data_in.acc[0] = (lsm6ds3tr_c_from_fs2g_to_mg(data_raw_acceleration[0]) * FROM_MG_TO_G);
			data_in.acc[1] = (lsm6ds3tr_c_from_fs2g_to_mg(data_raw_acceleration[1]) * FROM_MG_TO_G);
			data_in.acc[2] = (lsm6ds3tr_c_from_fs2g_to_mg(data_raw_acceleration[2]) * FROM_MG_TO_G);


			data_in.gyro[0] = (lsm6ds3tr_c_from_fs500dps_to_mdps(data_raw_angular_rate[0]) * FROM_MDPS_TO_DPS) ;
			data_in.gyro[1] = (lsm6ds3tr_c_from_fs500dps_to_mdps(data_raw_angular_rate[1]) * FROM_MDPS_TO_DPS) ;
			data_in.gyro[2] = (lsm6ds3tr_c_from_fs500dps_to_mdps(data_raw_angular_rate[2]) * FROM_MDPS_TO_DPS) ;


		    /* Don't set mag values because we use only acc and gyro */
		    data_in.mag[0] = 0.0f;
		    data_in.mag[1] = 0.0f;
		    data_in.mag[2] = 0.0f;



	      MotionFX_propagate(mfxstate, &data_out, &data_in, &delta_time);
	      MotionFX_update(mfxstate, &data_out, &data_in, &delta_time, NULL);

	        // Update imu_data
	        imu_data.acceleration_x = data_out.gravity[0];
	        imu_data.acceleration_y = data_out.gravity[1];
	        imu_data.acceleration_z = data_out.gravity[2];
	        imu_data.angular_rate_x = data_out.linear_acceleration[0];
	        imu_data.angular_rate_y = data_out.linear_acceleration[1];
	        imu_data.angular_rate_z = data_out.linear_acceleration[2];
	        imu_data.pitch = data_out.rotation[1];
	        imu_data.roll = data_out.rotation[2];


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










