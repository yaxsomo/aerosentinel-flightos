/*
 * KalmanQuaternions.h
 *
 *  Created on: Aug 24, 2023
 *      Author: yaxsomo
 */

#ifndef INC_KALMANQUATERNIONS_H_
#define INC_KALMANQUATERNIONS_H_


/* Include files */
#include <stddef.h>
#include <stdlib.h>

/* Function Declarations */
extern void updateEKFQuatAtt(const float gyr_rps[3], const float acc_mps2[3],
  const float mag_unit[3], float Va_mps, float magDecRad, float T, float
  NdivT, float *roll_deg, float *pitch_deg, float *yaw_deg);
extern void updateEKFQuatAtt_initialize(void);
extern void updateEKFQuatAtt_terminate(void);


#endif /* INC_KALMANQUATERNIONS_H_ */
