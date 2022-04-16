#ifndef __ATTITUDE_CALCULATION_H
#define __ATTITUDE_CALCULATION_H
#include "hal_include.h"

#define  PI            3.1415926
#define  PERIODHZ      (float)200     /////����Ƶ��
#define  PERIODS       (float)0.005       ////��������

typedef struct{
  float W;
  float X;
  float Y;
  float Z;
}QuaternionTypedef;

typedef struct{ 
  float Pitch;  //������
  float Yaw;    //ƫ����
  float Roll;   //������
}EulerAngleTypedef;

typedef struct{
  float Xdata;
  float Ydata;
  float Zdata;
}AttitudeDatatypedef;

extern QuaternionTypedef    Quaternion;   //��Ԫ��
extern EulerAngleTypedef    EulerAngle;   //ŷ����
extern QuaternionTypedef    AxisAngle;    //���
extern EulerAngleTypedef    EulerAngleRate;//��ǰŷ�����ٶ�

extern QuaternionTypedef    MeaQuaternion;
extern EulerAngleTypedef    MeaEulerAngle;
extern QuaternionTypedef    MeaAxisAngle;

extern QuaternionTypedef    ErrQuaternion;
extern EulerAngleTypedef    ErrEulerAngle;
extern QuaternionTypedef    ErrAxisAngle;
extern AttitudeDatatypedef         Acc;
extern AttitudeDatatypedef         Gyro;


extern void Quaternion_init();

extern void Attitude_UpdateGyro(void);

extern void Attitude_UpdateAcc(void);

void Angle_adjust_out();

//�Ƕ��ں�
extern float Angle;
extern void Complementary_Filter(float Accel,float Gyro);
extern void GetAngle(void);

typedef struct
{
  float GYROXdata;
  float GYROYdata;
  float GYROZdata;
  float ACCXdata;
  float ACCYdata;
  float ACCZdata;
}Icm20602Datatypedef;
#endif
