#include "direction.h"
float price_PWM=0;
float ZX_kp=6.5;
float ZX_ki=0;
float ZX_kd=6.5;
int Differduty_old=0;
int Differduty_new=0;
int Differduty=0;
uint8         IN_L=3;
uint8         IN_R=3;
float       Total_AngleL=0;  //ת��ǶȻ���
float       Total_AngleR=0;  //ת��ǶȻ���
uint8 COUNTS=0;
float target_vel_z=0;
float target_vel_z_pre=0;
int poserror_pre=0;
extern uint8 Statu;
/**********ת�򻷿���**********/
void DifferControl(){
//ת���⻷6ms,ת���ڻ�2ms
  if(COUNTS==3){
    COUNTS=0;
    DerectError_Get();//��ȡƫ��  
  }
  COUNTS++;
  target_vel_z=target_vel_z_pre+(target_vel_z-target_vel_z_pre)*COUNTS/3;
  Direction_out(); //ƫ��PWM��ȡ
}



void DerectError_Get(void)  //�⻷   ,P����
{ 
     float out_P=5.0;
     if(Statu==Zebra) out_P=10.0;
     target_vel_z=out_P*poserror+(out_P*0.3)*(poserror-poserror_pre);
     poserror_pre=poserror;
     target_vel_z_pre=target_vel_z;
}

/**
 * @file		�����ڻ�
 * @note      	        ����
 * @brief		mm32
 * @author		NUDT
 * @date		2020��5��17��
 */
void Direction_out(void)
{
  float error;
  static  float last_error;
  float price_Differention;
  float price_Proportion;
  static float Pre1_Error[4];
  float Direct_Parameter;
  ZX_kp=0.45;
  ZX_kd=0.45;
  error = target_vel_z*10.3+icm_gyro_z*0.29; //ͼ��ƫ��+������10.3  0.19
  price_Proportion=ZX_kp * error;
  price_Differention= ZX_kd* (error - last_error);
  Direct_Parameter =price_Proportion  + price_Differention ;//(1+error*error*0.000000001f)
  last_error =  error; 
  Pre1_Error[3]=Pre1_Error[2];
  Pre1_Error[2]=Pre1_Error[1];
  Pre1_Error[1]=Pre1_Error[0];
  Pre1_Error[0]=Direct_Parameter;//0����������
  Direct_Parameter=Pre1_Error[0]*0.8+Pre1_Error[1]*0.1+Pre1_Error[2]*0.06+Pre1_Error[3]*0.04 ;
  price_PWM=(int16)(Direct_Parameter);
  if(price_PWM>=550) price_PWM=550;
  if(price_PWM<=-550) price_PWM=-550;
      if(price_PWM>=550) price_PWM=550;
  if(price_PWM<=-550) price_PWM=-550;
  }


