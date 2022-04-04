/*
 * icm20602.h
 *
 *  Created on: 2022年3月5日
 *      Author: Y
 */

#ifndef CODE_ICM20602_H_
#define CODE_ICM20602_H_
#define delta_T     0.001f  // 采样周期1ms 即频率1KHZ
#define PI          3.1415926f

#include "zf_stm_systick.h"
#include "SEEKFREE_ICM20602.h"
#include "SEEKFREE_IPS200_PARALLEL8.h"

typedef struct{
        int16 Xdata;
        int16 Ydata;
        int16 Zdata;
}gyro_param_t;

typedef struct{
        float acc_x;
        float acc_y;
        float acc_z;
        float gyro_x;
        float gyro_y;
        float gyro_z;
}icm_param_t;

typedef struct{
        float q0;
        float q1;
        float q2;
        float q3;
}quater_param_t;


typedef struct{
        float pitch;
        float roll;
        float yaw;
}euler_param_t;



icm_param_t icmGetValues(gyro_param_t GyroOffset);
float myRsqrt(float x);
gyro_param_t gyroOffsetInit(void);
void icmAHRSupdate(icm_param_t* icm);
float get_pitch();

#endif /* CODE_ICM20602_H_ */
