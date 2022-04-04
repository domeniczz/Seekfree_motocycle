#ifndef __SITUATION_H
#define __SITUATION_H

#include "hal_include.h"

/*提取初始中值*/
void SelectMid(void);

/*读取AD*/
void Get_AD();
/*获取最大值**/
void Get_MaxAD();
/*电磁标定值*/
void Get_TrueAD();
/*元素判定*/
void Judgu_Typeof_Road(void);
/*坡道判定*/
uint8  Ramp_Judge (void);
/*十字判定*/
 void Cross_Judge(void);

/*斑马线判定*/
uint8 Zebra_Judge (void);
/*岔路判定*/
uint8 ChaLu_Judge(void);
uint8 ChaLu_OutJudge(void);
/*横断路障判定*/
uint8 Ring_Judge();
/*状态处理*/
void Treatment_Status (void);
/*直到**/
void  Straight_Judge (void);
/*十字处理*/
 void CrossTreatment(void);
/*环岛处理*/
void LRingTreatment (void);
void RRingTreatment (void);
/*岔路处理*/
void ChaLuTreatment(void);
/*坡道处理*/
void RampsTreatment(void);
/*车库处理*/
void ZebraTreatment(void);

/*正常处理*/
void NormalTreatment (void);

/*状态处理********************************************************************/


#define  Normals         1
#define  Straight        2
#define  Ramps           3
#define  LRing           4
#define  RRing           5
#define  Lukou           6
#define  Cross           7
#define  Zebra           8
#define  Stops           9
extern uint16 L;
extern uint16 M;
extern uint16 R;
//车库
#define L_go 0
#define R_go 1
extern uint8 Zerbra_Dir;


extern uint16  Max_LAD;
extern uint16  Max_MAD;
extern uint16  Max_RAD;
extern int S_Left;
extern int S_Right;
extern float k_r;   //左线斜率
extern float k_l;   //右线斜率
extern float SumAngle;      //角度
extern uint8 Record_Angle; // 角度记录标志位
extern uint8 CHALU_TIME;
//----------------匹配滤波-三岔路口---------------
void Line_sum(uint8 x1,uint8 x2,uint8 y1,uint8 y2,float line_sum[]);
float conv(float model[],float test[]);
void ChaLuJudge(void);
extern uint8 line_length;
extern float left  ;
extern float right ;
extern uint16 match_threshold;

 void CrossTreatment(void);
#endif
