/*
 * icm20602.c
 *
 *  Created on: 2022��3��5��
 *      Author: Y
 */
#include "icm20602.h"

quater_param_t Q_info = {1, 0, 0, 0};  // ��Ԫ����ʼ��
float I_ex, I_ey, I_ez;  // ������
euler_param_t eulerAngle;

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
        get_icm20602_gyro();    // ��ȡ�����ǽ��ٶ�
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
    get_icm20602_accdata();
    get_icm20602_gyro();    // ��ȡ�����ǽ��ٶ�
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

void icmAHRSupdate(icm_param_t* icm)
{


    float icm_kp= 50;    // ���ٶȼƵ��������ʱ�������
    float icm_ki= 0.2;   // �������������ʵĻ�������

    float halfT = 0.5 * delta_T;    // ��������һ��
    float vx, vy, vz;               // ��ǰ��̬��������������������ϵķ���
    float ex, ey, ez;               // ��ǰ���ټƲ�õ��������ٶ��������ϵķ������õ�ǰ��̬��������������������ϵķ��������

    float q0 = Q_info.q0;  //��Ԫ��
    float q1 = Q_info.q1;
    float q2 = Q_info.q2;
    float q3 = Q_info.q3;

    float q0q0 = q0 * q0;  //����ˣ������������
    float q0q1 = q0 * q1;
    float q0q2 = q0 * q2;
//    float q0q3 = q0 * q3;
    float q1q1 = q1 * q1;
//    float q1q2 = q1 * q2;
    float q1q3 = q1 * q3;
    float q2q2 = q2 * q2;
    float q2q3 = q2 * q3;
    float q3q3 = q3 * q3;

    // ������ֹ״̬Ϊ-g ����������
    if(icm->acc_x * icm->acc_y * icm->acc_z == 0) // �Ӽƴ�����������״̬ʱ(��ʱg = 0)��������̬���㣬��Ϊ�������ĸ���������
        return;

    // �Լ��ٶ����ݽ��й�һ�� �õ���λ���ٶ� (a^b -> ��������ϵ�µļ��ٶ�)
    float norm = sqrt(icm->acc_x * icm->acc_x + icm->acc_y * icm->acc_y + icm->acc_z * icm->acc_z);
    icm->acc_x = icm->acc_x / norm;
    icm->acc_y = icm->acc_y / norm;
    icm->acc_z = icm->acc_z / norm;

    // ��������ϵ���������������ϵķ���
    vx = 2 * (q1q3 - q0q2);
    vy = 2 * (q0q1 + q2q3);
    vz = q0q0 - q1q1 - q2q2 + q3q3;

    // g^b �� a^b ��������ˣ��õ������ǵ�У����������e��ϵ��
    ex = icm->acc_y * vz - icm->acc_z * vy;
    ey = icm->acc_z * vx - icm->acc_x * vz;
    ez = icm->acc_x * vy - icm->acc_y * vx;

    // ����ۼ�
    I_ex += halfT * ex;
    I_ey += halfT * ey;
    I_ez += halfT * ez;

    // ʹ��PI�������������������(������Ư�����)
    icm->gyro_x = icm->gyro_x + icm_kp* ex + icm_ki* I_ex;
    icm->gyro_y = icm->gyro_y + icm_kp* ey + icm_ki* I_ey;
    icm->gyro_z = icm->gyro_z + icm_kp* ez + icm_ki* I_ez;

    // һ����������������Ԫ��΢�ַ��̣�����halfTΪ�������ڵ�1/2��gx gy gzΪbϵ�����ǽ��ٶȡ�
    q0 = q0 + (-q1 * icm->gyro_x - q2 * icm->gyro_y - q3 * icm->gyro_z) * halfT;
    q1 = q1 + (q0 * icm->gyro_x + q2 * icm->gyro_z - q3 * icm->gyro_y) * halfT;
    q2 = q2 + (q0 * icm->gyro_y - q1 * icm->gyro_z + q3 * icm->gyro_x) * halfT;
    q3 = q3 + (q0 * icm->gyro_z + q1 * icm->gyro_y - q2 * icm->gyro_x) * halfT;

    // ��λ����Ԫ���ڿռ���תʱ�������죬������ת�Ƕȣ������㷨�������Դ�����������任
    norm = sqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
    Q_info.q0 = q0 / norm;
    Q_info.q1 = q1 / norm;
    Q_info.q2 = q2 / norm;
    Q_info.q3 = q3 / norm;  // ��ȫ�ֱ�����¼��һ�μ������Ԫ��ֵ


    eulerAngle.pitch = asin(-2*q1*q3 + 2*q0*q2) * 180/PI; // pitch
    eulerAngle.roll = atan2(2*q2*q3 + 2*q0*q1, -2*q1*q1 - 2*q2*q2 + 1) * 180/PI; // roll
    eulerAngle.yaw = atan2(2*q1*q2 + 2*q0*q3, -2*q2*q2 - 2*q3*q3 + 1) * 180/PI; // yaw��

    ips200_showfloat(0,0,eulerAngle.pitch,5,5);

}

float get_pitch()
{
    float Pitch=eulerAngle.pitch;

    return Pitch;
}



