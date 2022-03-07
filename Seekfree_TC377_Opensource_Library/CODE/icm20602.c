/*
 * icm20602.c
 *
 *  Created on: 2022��3��5��
 *      Author: Y
 */
#include "icm20602.h"



/**
 * @brief ���ɼ�����ֵת��Ϊʵ������ֵ, ���������ǽ���ȥ��Ư����
 * ���ٶȼƳ�ʼ������ -> ������Χ: ��8g        ��Ӧ������: 4096 LSB/g
 * �����ǳ�ʼ������   -> ������Χ: ��2000 dps  ��Ӧ������: 16.4 LSB/dps   (degree per second)
 * @tips: gyro = (gyro_val / 16.4) ��/s = ((gyro_val / 16.4) * PI / 180) rad/s
 */

gyro_param_t gyroOffsetInit(void)
{
    gyro_param_t GyroOffset;               // ������У׼ֵ
    GyroOffset.Xdata = 0;
    GyroOffset.Ydata = 0;
    GyroOffset.Zdata = 0;

    for (int i = 0; i < 100; ++i)
    {
        get_icm20602_gyro_spi();    // ��ȡ�����ǽ��ٶ�
        GyroOffset.Xdata += icm_gyro_x;
        GyroOffset.Ydata += icm_gyro_y;
        GyroOffset.Zdata += icm_gyro_z;
        systick_delay_ms(STM0,5);    // ��� 1Khz
    }

    GyroOffset.Xdata /= 100;
    GyroOffset.Ydata /= 100;
    GyroOffset.Zdata /= 100;

    return GyroOffset;
}

icm_param_t icmGetValues(gyro_param_t GyroOffset)
{


    float alpha = 0.3;
    get_icm20602_accdata_spi();
    get_icm20602_gyro_spi();    // ��ȡ�����ǽ��ٶ�
    icm_param_t icm_data;
    //һ�׵�ͨ�˲�����λg
    icm_data.acc_x = (((float) icm_acc_x) * alpha) / 4096 + icm_data.acc_x * (1 - alpha);
    icm_data.acc_y = (((float) icm_acc_y) * alpha) / 4096 + icm_data.acc_y * (1 - alpha);
    icm_data.acc_z = (((float) icm_acc_z) * alpha) / 4096 + icm_data.acc_z * (1 - alpha);

    //! �����ǽ��ٶȱ���ת��Ϊ�����ƽ��ٶ�: deg/s -> rad/s
    icm_data.gyro_x = ((float) icm_gyro_x - GyroOffset.Xdata) * PI / 180 / 16.4f;
    icm_data.gyro_y = ((float) icm_gyro_y - GyroOffset.Ydata) * PI / 180 / 16.4f;
    icm_data.gyro_z = ((float) icm_gyro_z - GyroOffset.Zdata) * PI / 180 / 16.4f;

    return icm_data;
}

float myRsqrt(float x) {
    float halfx = 0.5f * x;
    float y = x;
    long i = *(long*)&y;
    i = 0x5f3759df - (i>>1);
    y = *(float*)&i;
    y = y * (1.5f - (halfx * y * y));
    return y;
}




