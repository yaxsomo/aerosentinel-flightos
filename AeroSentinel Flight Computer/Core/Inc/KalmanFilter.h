/*
 * KalmanFilter.h
 *
 *  Created on: Aug 2, 2023
 *      Author: yaxsomo
 */

#ifndef INC_KALMANFILTER_H_
#define INC_KALMANFILTER_H_

#include <stdio.h>
#include <Compass.h>
#include "IMU.h"
#include <Pressure.h>
#include <math.h>
#define ARM_MATH_CM4

// Define the state vector (position, velocity, orientation)
typedef struct {
    float x, y, z;      // Position
    float vx, vy, vz;   // Velocity
    float roll, pitch, yaw; // Orientation
} StateVector;

// Define the sensor measurement vector
typedef struct {
    float accel_x, accel_y, accel_z; // IMU Acceleration
    float barometer; // Barometer data
    float mag_x, mag_y, mag_z; // Magnetometer data
} MeasurementVector;

// Define the Kalman Filter parameters
typedef struct {
    StateVector x_hat; // Estimated state vector
    float P[9][9];     // Covariance matrix
} KalmanFilter;



// Kalman Filter Functions Prototypes

void kalman_init(KalmanFilter* kf);
void kalman_predict(KalmanFilter* kf);
void kalman_update(KalmanFilter* kf, const MeasurementVector* z);
void sensor_fusion();
void execute_kalman();



#endif /* INC_KALMANFILTER_H_ */
