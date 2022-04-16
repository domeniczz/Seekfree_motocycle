#ifndef HAL_INCLUDE_H_
#define HAL_INCLUDE_H_

#include "headfile.h"

//初始化部分
#include "Init.h"
//陀螺仪部分
//#include "GY901S.h"
#include "SoftIIC.h"
#include "Attitude_Calculation.h"
//速度相关
#include "speed_measure.h"
//图像相关
#include "image_processing.h"
#include "select_median.h"
#include "situation.h"
////直立环
#include "Angle_handle.h"
//转向环
#include "direction.h"
//菜单
#include "data_sheet.h"
//#include "data_menu.h"
//#include "data_flash.h"
////显示
//#include "OLED_display.h"
////示波器
//#include "VisualScope.h"
////电磁
//#include "Electro.h"
////加速算法
//#include "My_math.h"
//模糊算法
#include "mohuduoji.h"
//舵机
#include "duoji.h"
////上位机
//#include "niming.h"
//加速度转换
#define GYRO_RATE 0.061035
#define ACC_RATE 0.002392578125
#endif
