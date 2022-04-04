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
  //基础模糊表
  uint8         ui8_Table[4][4];
} MH_Table;

typedef struct 
{
  //舵机P值表L
  float         f_DuoJiP_TableL[7];
  //舵机P值表R
  float         f_DuoJiP_TableR[7];
  //舵机模糊表
  MH_Table      mt_Duoji[4];
    //电机P值表
  float         f_DianJiP_Table[7];
  //电机I值表
  float         f_DianJiI_Table[7];
  //电机模糊表
  MH_Table      mt_DianJi[4];  
  //出入弯标志
  uint8         ui8_IO;
  //左右出入弯标志
  uint8         ui8_IOLR;
  //出入弯加减速标志
  uint8         ui8_IOAS;
  //反向可视距离变化范围
  float         f_SizeOfViewH;
  //中值偏差变化范围
  float         f_SizeOfViewE;
    //脉冲偏差变化范围
  float         f_SizeOfPulseE;
  //上次反向可视距离
  int16         i16_ViewH;
  //
} MH;

/*模糊表初始化*/
void InitMH (void);

/*获取舵机P值*/
void DuoJi_GetP (float* i32p_P, int16 i16_ViewH, int16 i16_ViewE);

/*获取电机P值*/
void DianJi_GetPI (float* i32p_P, float* i32p_I, int16 i16_ViewH, int16 i16_PulseE);

/*获取X近似坐标*/
float f_Get_H_approximation (int16 i16_ViewH);

/*获取Y近似坐标*/
float f_Get_E_approximation (int16 i16_E, float f_E_Size);

#endif