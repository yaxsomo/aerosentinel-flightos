/*
 * KalmanFilter.c
 *
 *  Created on: Aug 2, 2023
 *      Author: yaxsomo
 */



#include "KalmanFilter.h"
#include "arm_math.h"


// Kalman Filter constants (You may need to tune these based on sensor characteristics)
float dt = 0.01; // Time step (adjust as needed)
float Q[9][9] = { /* Process noise covariance matrix */ };
KalmanFilter kf;
MeasurementVector measurements;
//float R[6][6] = { /* Measurement noise covariance matrix */ };

// Kalman Filter initialization
void kalman_init(KalmanFilter* kf) {
    // Assuming stationary initial state
    kf->x_hat.x = 0.0;
    kf->x_hat.y = 0.0;
    kf->x_hat.z = 0.0;
    kf->x_hat.vx = 0.0;
    kf->x_hat.vy = 0.0;
    kf->x_hat.vz = 0.0;
    kf->x_hat.roll = 0.0;
    kf->x_hat.pitch = 0.0;
    kf->x_hat.yaw = 0.0;

    // Initialize the covariance matrix to large values (for uncertainty)
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            kf->P[i][j] = 1000.0;
        }
    }
}

// Kalman Filter prediction step
void kalman_predict(KalmanFilter* kf) {
    // Assuming constant velocity model (predicting the next state)
    kf->x_hat.x += dt * kf->x_hat.vx;
    kf->x_hat.y += dt * kf->x_hat.vy;
    kf->x_hat.z += dt * kf->x_hat.vz;

    // Construct the state transition matrix A
    // The state transition matrix A describes how the state evolves from one time step to the next.
    float A[81] = {
        1, 0, 0, dt, 0, 0, 0, 0, 0,
        0, 1, 0, 0, dt, 0, 0, 0, 0,
        0, 0, 1, 0, 0, dt, 0, 0, 0,
        0, 0, 0, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 1
    };

    // Temporary array for the matrix multiplication: A * P
    float AP[81];

    // Perform matrix multiplication: AP = A * P
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            AP[i * 9 + j] = 0;
            for (int k = 0; k < 9; k++) {
                AP[i * 9 + j] += A[i * 9 + k] * kf->P[k][j];
            }
        }
    }

    // Temporary array for the matrix multiplication: AP * A^T
    float APA_T[81];

    // Perform matrix multiplication: APA_T = AP * A^T
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            APA_T[i * 9 + j] = 0;
            for (int k = 0; k < 9; k++) {
                APA_T[i * 9 + j] += AP[i * 9 + k] * A[j * 9 + k];
            }
        }
    }

    // Update the covariance matrix P = APA_T + Q
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            kf->P[i][j] = APA_T[i * 9 + j] + Q[i][j];
        }
    }
}


// Kalman Filter update step
void kalman_update(KalmanFilter* kf, const MeasurementVector* z) {
    // Convert the state vector (x_hat) to an array for easy manipulation
    float x_hat[9] = {
        kf->x_hat.x, kf->x_hat.y, kf->x_hat.z,
        kf->x_hat.vx, kf->x_hat.vy, kf->x_hat.vz,
        kf->x_hat.roll, kf->x_hat.pitch, kf->x_hat.yaw
    };

    // Measurement Matrix H (Assuming direct measurements of position, velocity, and heading)
    float H[81] = { // 9x9 identity matrix
        1, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 1
    };

    // Measurement Noise Covariance Matrix R (Assuming diagonal matrix)
    float R[81] = { // 9x9 identity matrix with ones on the diagonal
        1, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 1
    };

    // Measurement Residual Calculation: r = z - H * x_hat
    float r[9];
    // Initialize the measurement vector H * x_hat
    float Hx_hat[9];

    // Perform matrix multiplication: Hx_hat = H * x_hat
    for (int i = 0; i < 9; i++) {
        Hx_hat[i] = 0;
        for (int j = 0; j < 9; j++) {
            Hx_hat[i] += H[i * 9 + j] * x_hat[j];
        }
    }

    // Calculate the measurement residual r = z - H * x_hat
    r[0] = z->accel_x - Hx_hat[0];
    r[1] = z->accel_y - Hx_hat[1];
    r[2] = z->accel_z - Hx_hat[2];
    r[3] = z->barometer - Hx_hat[3];
    r[4] = z->mag_x - Hx_hat[4];
    r[5] = z->mag_y - Hx_hat[5];
    r[6] = z->mag_z - Hx_hat[6];

    // Calculate Kalman Gain: K = P * H^T * S_inv
    float K[81];
    float S[81];
    float S_inv[81];

    // Perform matrix multiplication: S = H * P * H^T + R
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            S[i * 9 + j] = 0;
            for (int k = 0; k < 9; k++) {
                S[i * 9 + j] += H[i * 9 + k] * kf->P[k][j];
            }
            if (i == j) {
                S[i * 9 + j] += R[i * 9 + j];
            }
        }
    }

    // Calculate matrix inversion: S_inv = inv(S)
    arm_matrix_instance_f32 mat_S, mat_S_inv;
    arm_mat_init_f32(&mat_S, 9, 9, S);
    arm_mat_init_f32(&mat_S_inv, 9, 9, S_inv);
    arm_status status = arm_mat_inverse_f32(&mat_S, &mat_S_inv);

    if (status == ARM_MATH_SUCCESS) {
        // Calculate Kalman Gain: K = P * H^T * S_inv
        arm_matrix_instance_f32 mat_P, mat_H, mat_K;
        arm_mat_init_f32(&mat_P, 9, 9, (float32_t *)kf->P);
        arm_mat_init_f32(&mat_H, 9, 9, H);
        arm_mat_init_f32(&mat_K, 9, 9, K);
        arm_mat_mult_f32(&mat_P, &mat_H, &mat_K); // K = P * H^T
        arm_mat_mult_f32(&mat_K, &mat_S_inv, &mat_K); // K = K * S_inv
    } else {
        // Matrix inversion failed, handle the error here.
        // For example, you can provide default values for K or skip the update step.
        return;
    }

    // Update the state estimate x_hat = x_hat + K * r
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            x_hat[i] += K[i * 9 + j] * r[j];
        }
    }

    // Update the covariance matrix P = (I - K * H) * P
    float KH[81]; // K * H

    // Perform matrix multiplication: KH = K * H
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            KH[i * 9 + j] = 0;
            for (int k = 0; k < 9; k++) {
                KH[i * 9 + j] += K[i * 9 + k] * H[j * 9 + k];
            }
        }
    }

    // Update P: P = (I - KH) * P
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            kf->P[i][j] = kf->P[i][j] - KH[i * 9 + j];
        }
    }

    // Finally, update the state vector with the new estimates
    kf->x_hat.x = x_hat[0];
    kf->x_hat.y = x_hat[1];
    kf->x_hat.z = x_hat[2];
    kf->x_hat.vx = x_hat[3];
    kf->x_hat.vy = x_hat[4];
    kf->x_hat.vz = x_hat[5];
    kf->x_hat.roll = x_hat[6];
    kf->x_hat.pitch = x_hat[7];
    kf->x_hat.yaw = x_hat[8];
}







// Function to perform sensor fusion
void sensor_fusion() {
        // Get sensor measurements (IMU, Barometer, Magnetometer)


        // Call each sensor function and receive the data structures
        IMUData imu_data = Transmit_IMU_Data();
        PressureTempData barometer_data = Transmit_Pressure_Temp_Data();
        CompassData compass_data = Transmit_Compass_Data();

        // Call sensor functions and populate the MeasurementVector structure
        measurements.accel_x = imu_data.acceleration_x;
        measurements.accel_y = imu_data.acceleration_y;
        measurements.accel_z = imu_data.acceleration_z;

        measurements.barometer = barometer_data.pressure_hpa;

        // Convert heading to three-axis magnetometer data (assuming roll and pitch are 0)
        float heading_rad = compass_data.heading * 0.0174533; // Convert heading from degrees to radians
        measurements.mag_x = cos(heading_rad);
        measurements.mag_y = sin(heading_rad);
        measurements.mag_z = 0.0; // Assuming the magnetometer is only sensitive to the horizontal plane


        // Perform Kalman Filter prediction step
        kalman_predict(&kf);

        // Perform Kalman Filter update step with the sensor measurements
        kalman_update(&kf, &measurements);

        // Print or use the estimated state vector (kf.x_hat)
        // You can access position, velocity, and orientation estimates from kf.x_hat
}


/*
 * Execution of Kalman Filter and data print on UART1
 * Usage on code :  (
 * 					execute_kalman();
 * 					)
 */
void execute_kalman(){
	kalman_init(&kf);
	sensor_fusion();
	 // Print the estimated state vector (kf.x_hat)
	char output_str[200]; // You can adjust the buffer size as needed
	snprintf(output_str, sizeof(output_str), "Position: (%f, %f, %f)\r\n", kf.x_hat.x, kf.x_hat.y, kf.x_hat.z);
	UART_Transmit_String(output_str);

	snprintf(output_str, sizeof(output_str), "Velocity: (%f, %f, %f)\r\n", kf.x_hat.vx, kf.x_hat.vy, kf.x_hat.vz);
	UART_Transmit_String(output_str);

	snprintf(output_str, sizeof(output_str), "Orientation (Roll, Pitch, Yaw): (%f, %f, %f)\r\n", kf.x_hat.roll, kf.x_hat.pitch, kf.x_hat.yaw);
	UART_Transmit_String(output_str);



}

