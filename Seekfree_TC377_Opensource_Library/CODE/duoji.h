#ifndef __DUOJI_H
#define __DUOJI_H

#include "hal_include.h"

#define DUOJI_MIN_DUTY 790 //舵机往右打死510
#define DUOJI_MAX_DUTY 1112 //舵机往左打死990
#define DUOJI_MID_DUTY 943//舵机打在中间770
#define DUOJI_HALF_DUTY 161 //半程占空比220

#define DuojiDuty(x)   pwm_duty(ATOM1_CH1_P33_9 , x)

typedef struct{
  float P;
  float D;
  int8 Mid;
  int16 MidEr[10];
  uint16 MidDuty;
  uint16 MaxDuty;
  uint16 MinDuty;
  int16 Duty;
}SteeringData;
extern SteeringData Duoji;

extern float Dp;
extern uint16 DuojiDuty;
/*舵机初始化*/
void Duoji_Init(void);

/*电机数据初始化*/
void Duoji_Data_Init(void);

/*舵机工作*/
void Duoji_Work(void);

/*舵机记录偏差*/
void Duoji_Error(int16 i16_Midpoint);

/*舵机获取占空比*/
void Duoji_Duty_Get(void);

/*舵机控制*/
void Duoji_Control(void);
void Duoji_Control_Dianci(void);
void PassDianciDuojiDutyToDianji();


 

#endif
