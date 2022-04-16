#ifndef _MOHUDUOJI_H_ 
#define _MOHUDUOJI_H_

#include "hal_include.h"

#define MH_DianJi_IA            0
#define MH_DianJi_IS            1
#define MH_DianJi_OA            2
#define MH_DianJi_OS            3
#define MH_DuoJi_IL             0
#define MH_DuoJi_IR             1
#define MH_DuoJi_OL             2
#define MH_DuoJi_OR             3
#define H_Min                   4  

typedef struct 
{
  //����ģ����
  uint8         ui8_Table[4][4];
} MH_Table;

typedef struct 
{
  //���Pֵ��L
  float         f_DuoJiP_TableL[7];
  //���Pֵ��R
  float         f_DuoJiP_TableR[7];
  //���ģ����
  MH_Table      mt_Duoji[4];
    //���Pֵ��
  float         f_DianJiP_Table[7];
  //���Iֵ��
  float         f_DianJiI_Table[7];
  //���ģ����
  MH_Table      mt_DianJi[4];  
  //�������־
  uint8         ui8_IO;
  //���ҳ������־
  uint8         ui8_IOLR;
  //������Ӽ��ٱ�־
  uint8         ui8_IOAS;
  //������Ӿ���仯��Χ
  float         f_SizeOfViewH;
  //��ֵƫ��仯��Χ
  float         f_SizeOfViewE;
    //����ƫ��仯��Χ
  float         f_SizeOfPulseE;
  //�ϴη�����Ӿ���
  int16         i16_ViewH;
  //
} MH;

/*ģ�����ʼ��*/
void InitMH (void);

/*��ȡ���Pֵ*/
void DuoJi_GetP (float* i32p_P, int16 i16_ViewH, int16 i16_ViewE);

/*��ȡ���Pֵ*/
void DianJi_GetPI (float* i32p_P, float* i32p_I, int16 i16_ViewH, int16 i16_PulseE);

/*��ȡX��������*/
float f_Get_H_approximation (int16 i16_ViewH);

/*��ȡY��������*/
float f_Get_E_approximation (int16 i16_E, float f_E_Size);

#endif