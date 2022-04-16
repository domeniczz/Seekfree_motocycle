#ifndef _SPEED_MEASURE_
#define _SPEED_MEASURE_
#include "hal_include.h"
extern int16 N_R;//右轮脉冲数
extern int16 N_L;//左轮脉冲数
extern float V_R;//右轮速度
extern float V_L;//左轮速度
extern float V_R_pre; //右轮前一次速度
extern float V_L_pre;  //左轮前一次速度
extern float V_Avg;    //车速
extern int16 Out_PWM;
extern float Out_PWM_pre;
extern float DJ_kp;       //电机P
extern float DJ_ki;       //电机I
extern float DJ_kd;       //电机D
extern void Get_Speed();
extern void speed_PID(uint16 Goal);//闭环
extern void Dianji_Out(int16 Out_PWM,int16 Diff_PWM);
extern int16 i16_GetMv (void);


#endif


