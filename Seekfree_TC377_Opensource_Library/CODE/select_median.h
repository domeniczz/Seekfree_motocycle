#ifndef __SELECT_MEDIAN_H
#define __SELECT_MEDIAN_H

#include "hal_include.h"

extern int poserror ;
extern int poserror_array[4];
/*��ʼ����********************************************************************/
/*ͼ������*/
void DisposeImage (void);
/*��ʼ����********************************************************************/

/*���ô���********************************************************************/
/*������ȡ��ֵ*/
void NormalControl (void);

/*ȷ�������ֵ*/
void DetermineMid (void);

void LostWayControl (void);
/*���ô���********************************************************************/

/*�д���**********************************************************************/
/*ȷ��Ȩ��*/
void DetermineWeight (void);

/*ȷ��ɨ����*/
void DetermineScanLine (void);
/*�д���**********************************************************************/

/*�뻷����*/
void  InRingControl(void);

/*��������*/
void  OutRingControl(void);

/*������*/
void  RingControl(void);
/*ruku*/
void InChekuControl(void);
//Ԫ�ض�������
#define   OUT_PARK  0  //������
#define   IN_PARK   1 //���복��
#define   L_Little  2  //��С��
#define   R_Little  3  //��С��
#define   L_Big  4  //���
#define   R_Big  5  //�Ҵ�
#define   RAMP  6  //�µ�
#define   L_SANCHA  7 //��������
#define   R_SANCHA  8 //��������
#define   Crosses   9//ʮ��·��
extern uint16 Goal_Speed;
extern uint8 Special_Count;
extern uint8 Special_type[12];//Ԫ������

#endif
