#ifndef _DATA_SHEET_H
#define _DATA_SHEET_H

#include "hal_include.h"
/*----------------���˵�------------------------------------------------------------------------------*/
//ͼ����ֵ
#define Ithreshold     (uint8)d_GetItemValue(Image_Order, Image_Ithreshold_Order)     //����ֵ����
#define DJ_p    (double)d_GetItemValue(Image_Order, BaseWeight_5_Order)//���P
#define DJ_i (double)d_GetItemValue(Image_Order, BaseWeight_6_Order)//���I
#define Out_P (double)d_GetItemValue(Image_Order, Image_IthresholdL_Order)//���I
#define Base_Speed (uint16)d_GetItemValue(Dianji_Order, Dianji_PulseBase_Order)

/*---------------------------------------------------------------------------------------------------*/


//*ͼ�����********************************************************************/
#define SIZE_HRE  60   //ͼ������
#define MID_POINT 40    //��ֵ
#define Lstart                  1
#define Rstart                  2
#define Mstart                  3
#define White                   1
#define Black                   0



//*��̬��ֵ****************************/

#define HtoE            0.15//���Ӿ����ƫ��Ӱ��
#define VtoLine         0.003//�ٶȶ�Ȩ��Ӱ��
//*��̬��ֵ****************************/


/*״̬****************************/
//ֱ��
#define Straight                2
//���
#define Curve                   3  
//Բ��
#define Ring                    4
//ʮ��·
//#define Cross                   5
//�µ�
#define Ramp                    6
//��·
#define Breaker                 7  
//���·��
#define Roadblock               8
/*״̬*****************************/

/*״̬��־*****************************/
//*��ֱ��**************************/
#define LSF                     1
//��ֱ���ж���ֹ��
#define LSEndLine               40
//��ֱ���ж�������ֹ��
#define LSEndLineLR             40
//�������ֵ
#define LSMaxVariance           2
//ֱ�����ƫ��
#define LSWidthEr               5
//*��ֱ��**************************/

//*����**************************/
#define RingF                   2
#define RightRing               1
#define LeftRing                2

/**************************************/
#define Ring_flag1              1





//*�µ�**************************/
#define RampF                   3
#define RAMP_In_Flag            1
#define RAMP_On_Flag            2
#define RAMP_ToOut_Flag         3
#define RAMP_Out_Flag           4
#define RAMP_Speed              230
#define Ramp_MinLine            16
//*�µ�**************************/

//*������**************************/
#define ZebraF                  4
#define ZebraTimes              5//��С�������
#define FlagZebra(x)            x//������������
#define ZebraWidth              3//��������С���
#define END_SpeedPluse          100
#define END_COUNT               11
//*�µ�**************************/


//��ȫ�ȼ����־���(mm) 
#define Blue_Distance          1000            
#define Yellow_Distance        900  
#define Orange_Distance        600
#define Red_Distance           400
#define Unable_Distance        270
#define Max_Distance           2000
#define HD_SpeedPluse          70
#define HD_MINLINE              13//·����С����
//*�µ�**************************/

//�����������
#define STUCK_TIMES             500


//*��ǰ��ֵ************************/
#define Mid_point               0
/*��ǰ��ֵ*************************/

//*���Ӿ���***********************/
#define Height                  1
/*���Ӿ���************************/

//*״̬****************************/
#define State                   2
/*״̬*****************************/
#define BeeOn                   gpio_set(P33_10,1)
#define BeeOff                  gpio_set(P33_10,0)
//����
#define OK                     !gpio_get(P22_1)
#define Up                     !gpio_get(P22_0)
#define Down                   !gpio_get(P22_2)
#define Right                  !gpio_get(P22_3)



#endif
