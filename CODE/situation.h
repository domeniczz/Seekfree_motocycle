#ifndef __SITUATION_H
#define __SITUATION_H

#include "hal_include.h"

/*��ȡ��ʼ��ֵ*/
void SelectMid(void);

/*��ȡAD*/
void Get_AD();
/*��ȡ���ֵ**/
void Get_MaxAD();
/*��ű궨ֵ*/
void Get_TrueAD();
/*Ԫ���ж�*/
void Judgu_Typeof_Road(void);
/*�µ��ж�*/
uint8  Ramp_Judge (void);
/*ʮ���ж�*/
 void Cross_Judge(void);

/*�������ж�*/
uint8 Zebra_Judge (void);
/*��·�ж�*/
uint8 ChaLu_Judge(void);
uint8 ChaLu_OutJudge(void);
/*���·���ж�*/
uint8 Ring_Judge();
/*״̬����*/
void Treatment_Status (void);
/*ֱ��**/
void  Straight_Judge (void);
/*ʮ�ִ���*/
 void CrossTreatment(void);
/*��������*/
void LRingTreatment (void);
void RRingTreatment (void);
/*��·����*/
void ChaLuTreatment(void);
/*�µ�����*/
void RampsTreatment(void);
/*���⴦��*/
void ZebraTreatment(void);

/*��������*/
void NormalTreatment (void);

/*״̬����********************************************************************/


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
//����
#define L_go 0
#define R_go 1
extern uint8 Zerbra_Dir;


extern uint16  Max_LAD;
extern uint16  Max_MAD;
extern uint16  Max_RAD;
extern int S_Left;
extern int S_Right;
extern float k_r;   //����б��
extern float k_l;   //����б��
extern float SumAngle;      //�Ƕ�
extern uint8 Record_Angle; // �Ƕȼ�¼��־λ
extern uint8 CHALU_TIME;
//----------------ƥ���˲�-����·��---------------
void Line_sum(uint8 x1,uint8 x2,uint8 y1,uint8 y2,float line_sum[]);
float conv(float model[],float test[]);
void ChaLuJudge(void);
extern uint8 line_length;
extern float left  ;
extern float right ;
extern uint16 match_threshold;

 void CrossTreatment(void);
#endif
