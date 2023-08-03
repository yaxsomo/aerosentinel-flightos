/*
 * QMC5883.c
 *
 *  Created on: 11 juil. 2023
 *      Author: yaxsomo
 */


#include <Compass.h>
#include "math.h"
#include <main.h>
#include <Reg_Addresses.h>

extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart1;
QMC_t magneto_sensor;
CompassData compass_data;
//float Compas_Value;
const HeadingDirection directions[] = {
    { 0, 22.5, "N" },
    { 22.5, 67.5, "NE" },
    { 67.5, 112.5, "E" },
    { 112.5, 157.5, "SE" },
    { 157.5, 202.5, "S" },
    { 202.5, 247.5, "SO" },
    { 247.5, 292.5, "O" },
    { 292.5, 337.5, "NO" },
    { 337.5, 360, "N" }
};


void UART_Transmit_Messages_Magnetometer(const char* str)
{
  HAL_UART_Transmit(&huart1, (uint8_t*)str, strlen(str), HAL_MAX_DELAY);
}



//###############################################################################################################
uint32_t QMC_init(I2C_HandleTypeDef *i2c,uint8_t Output_Data_Rate)
{
	uint8_t array[2];
	magneto_sensor.i2c=i2c;
	magneto_sensor.Control_Register=0x11;
	array[0]=1;
	array[1]=magneto_sensor.Control_Register;

	if(Output_Data_Rate==200)magneto_sensor.Control_Register|=0b00001100;
	else if(Output_Data_Rate==100)magneto_sensor.Control_Register|=0b00001000;
	else if(Output_Data_Rate==50)magneto_sensor.Control_Register|=0b00000100;
	else if(Output_Data_Rate==10)magneto_sensor.Control_Register|=0b00000000;
	else magneto_sensor.Control_Register|=0b00001100;

	if(HAL_I2C_Mem_Write(magneto_sensor.i2c, MAGNETOMETER_ADDRESS << 1, 0x0B, 1, &array[0], 1, 100)!=HAL_OK)return 1;
	if(HAL_I2C_Mem_Write(magneto_sensor.i2c, MAGNETOMETER_ADDRESS << 1, 0x09, 1, &array[1], 1, 100)!=HAL_OK)return 1;

	return 0;
}

uint8_t QMC_read()
{
	  magneto_sensor.datas[0]=0;
	  HAL_I2C_Mem_Read(magneto_sensor.i2c, MAGNETOMETER_ADDRESS << 1, 0x06, 1, magneto_sensor.datas, 1, 100);

	  if((magneto_sensor.datas[0]&0x01)==1)
	  {
		  HAL_I2C_Mem_Read(magneto_sensor.i2c, MAGNETOMETER_ADDRESS << 1, 0x00, 1, magneto_sensor.datas, 6, 100);
		  magneto_sensor.Xaxis= (magneto_sensor.datas[1]<<8) | magneto_sensor.datas[0];
		  magneto_sensor.Yaxis= (magneto_sensor.datas[3]<<8) | magneto_sensor.datas[2];
		  magneto_sensor.Zaxis= (magneto_sensor.datas[5]<<8) | magneto_sensor.datas[4];

		  magneto_sensor.compas=atan2f(magneto_sensor.Yaxis,magneto_sensor.Xaxis)*180.00/M_PI;

		  if(magneto_sensor.compas>0)
		  {
			  magneto_sensor.heading= magneto_sensor.compas;
		  }
		  else
		  {
			  magneto_sensor.heading=360+magneto_sensor.compas;
		  }
	  }
	  else
	  {
		  return 1;
	  }
return 0;
}

uint8_t QMC_read_Normalize()
{
    magneto_sensor.datas[0] = 0;
    HAL_I2C_Mem_Read(magneto_sensor.i2c, MAGNETOMETER_ADDRESS << 1, 0x06, 1, magneto_sensor.datas, 1, 100);

    if ((magneto_sensor.datas[0] & 0x01) == 1)
    {
        HAL_I2C_Mem_Read(magneto_sensor.i2c, MAGNETOMETER_ADDRESS << 1, 0x00, 1, magneto_sensor.datas, 6, 100);
        magneto_sensor.Xaxis = (magneto_sensor.datas[1] << 8) | magneto_sensor.datas[0];
        magneto_sensor.Yaxis = (magneto_sensor.datas[3] << 8) | magneto_sensor.datas[2];
        magneto_sensor.Zaxis = (magneto_sensor.datas[5] << 8) | magneto_sensor.datas[4];

        // Normalize magnetometer data to a range of -1 to 1
        magneto_sensor.Xaxis = (magneto_sensor.Xaxis - MAG_MIN_VALUE) / (float)(MAG_MAX_VALUE - MAG_MIN_VALUE);
        magneto_sensor.Yaxis = (magneto_sensor.Yaxis - MAG_MIN_VALUE) / (float)(MAG_MAX_VALUE - MAG_MIN_VALUE);
        magneto_sensor.Zaxis = (magneto_sensor.Zaxis - MAG_MIN_VALUE) / (float)(MAG_MAX_VALUE - MAG_MIN_VALUE);

        // Apply filtering to the magnetometer data
        static float filteredX = 0.0f;
        static float filteredY = 0.0f;
        static float filteredZ = 0.0f;

        filteredX = (1.0f - FILTER_ALPHA) * filteredX + FILTER_ALPHA * magneto_sensor.Xaxis;
        filteredY = (1.0f - FILTER_ALPHA) * filteredY + FILTER_ALPHA * magneto_sensor.Yaxis;
        filteredZ = (1.0f - FILTER_ALPHA) * filteredZ + FILTER_ALPHA * magneto_sensor.Zaxis;

        magneto_sensor.Xaxis = filteredX;
        magneto_sensor.Yaxis = filteredY;
        magneto_sensor.Zaxis = filteredZ;

        magneto_sensor.compas = atan2f(magneto_sensor.Yaxis, magneto_sensor.Xaxis) * 180.0f / M_PI;

        if (magneto_sensor.compas > 0)
        {
            magneto_sensor.heading = magneto_sensor.compas;
        }
        else
        {
            magneto_sensor.heading = 360 + magneto_sensor.compas;
        }
    }
    else
    {
        return 1;
    }
    return 0;
}


float QMC_readHeading()
{
	QMC_read(magneto_sensor);
	return magneto_sensor.heading;
}

uint8_t QMC_Standby()
{
	uint8_t array[1]={0};
	if(HAL_I2C_Mem_Write(magneto_sensor.i2c, MAGNETOMETER_ADDRESS << 1, 0x09, 1, &array[0], 1, 100)!=HAL_OK)return 1;
	return 0;
}
uint8_t QMC_Reset()
{
	uint8_t array[1]={0x80};
	if(HAL_I2C_Mem_Write(magneto_sensor.i2c, MAGNETOMETER_ADDRESS << 1, 0x0A, 1, &array[0], 1, 100)!=HAL_OK)return 1;
	return 0;
}




CompassData Transmit_Compass_Data(){


		if(QMC_read() == 0)
		{
			float heading = magneto_sensor.heading;
			//Compas_Value=magneto_sensor.heading;
			//char mag_buffer[100];
			//sprintf(mag_buffer, "X=%d, Y=%d, Z=%d \r\n", magneto_sensor.Xaxis, magneto_sensor.Yaxis, magneto_sensor.Zaxis);
			//sprintf(mag_heading_buffer, "HEADING : %.1f\r\n",magneto_sensor.heading);
			//UART_Transmit_Messages_Magnetometer(mag_buffer);
			//UART_Transmit_Messages_Magnetometer(mag_heading_buffer);

	        const int numDirections = sizeof(directions) / sizeof(directions[0]);
	        const char* direction = "Unknown";

	        for (int i = 0; i < numDirections; ++i) {
	            if (heading >= directions[i].min && heading <= directions[i].max) {
	                direction = directions[i].direction;
	                break;
	            }
	        }

	        compass_data.heading = heading;
	        compass_data.direction = direction;

	        return compass_data;

		}
		else
		{
	        compass_data.heading = 0;
	        compass_data.direction = "ERR";

	        return compass_data;
		}

}
