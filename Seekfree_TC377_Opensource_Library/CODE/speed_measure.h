#ifndef _SPEED_MEASURE_
#define _SPEED_MEASURE_
#include "hal_include.h"
extern int16 N_R;//����������
extern int16 N_L;//����������
extern float V_R;//�����ٶ�
extern float V_L;//�����ٶ�
extern float V_R_pre; //����ǰһ���ٶ�
extern float V_L_pre;  //����ǰһ���ٶ�
extern float V_Avg;    //����
extern int16 Out_PWM;
extern float Out_PWM_pre;
extern float DJ_kp;       //���P
extern float DJ_ki;       //���I
extern float DJ_kd;       //���D
extern void Get_Speed();
extern void speed_PID(uint16 Goal);//�ջ�
extern void Dianji_Out(int16 Out_PWM,int16 Diff_PWM);
extern int16 i16_GetMv (void);


#endif


