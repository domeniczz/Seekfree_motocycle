#ifndef HAL_INCLUDE_H_
#define HAL_INCLUDE_H_

#include "headfile.h"

//��ʼ������
#include "Init.h"
//�����ǲ���
//#include "GY901S.h"
#include "SoftIIC.h"
#include "Attitude_Calculation.h"
//�ٶ����
#include "speed_measure.h"
//ͼ�����
#include "image_processing.h"
#include "select_median.h"
#include "situation.h"
////ֱ����
#include "Angle_handle.h"
//ת��
#include "direction.h"
//�˵�
#include "data_sheet.h"
//#include "data_menu.h"
//#include "data_flash.h"
////��ʾ
//#include "OLED_display.h"
////ʾ����
//#include "VisualScope.h"
////���
//#include "Electro.h"
////�����㷨
//#include "My_math.h"
//ģ���㷨
#include "mohuduoji.h"
//���
#include "duoji.h"
////��λ��
//#include "niming.h"
//���ٶ�ת��
#define GYRO_RATE 0.061035
#define ACC_RATE 0.002392578125
#endif
