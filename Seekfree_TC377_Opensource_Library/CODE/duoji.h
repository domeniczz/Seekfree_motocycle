#ifndef __DUOJI_H
#define __DUOJI_H

#include "hal_include.h"

#define DUOJI_MIN_DUTY 790 //������Ҵ���510
#define DUOJI_MAX_DUTY 1112 //����������990
#define DUOJI_MID_DUTY 943//��������м�770
#define DUOJI_HALF_DUTY 161 //���ռ�ձ�220

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
/*�����ʼ��*/
void Duoji_Init(void);

/*������ݳ�ʼ��*/
void Duoji_Data_Init(void);

/*�������*/
void Duoji_Work(void);

/*�����¼ƫ��*/
void Duoji_Error(int16 i16_Midpoint);

/*�����ȡռ�ձ�*/
void Duoji_Duty_Get(void);

/*�������*/
void Duoji_Control(void);
void Duoji_Control_Dianci(void);
void PassDianciDuojiDutyToDianji();


 

#endif
