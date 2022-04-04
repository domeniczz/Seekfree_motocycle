#ifndef GY901S_H
#define GY901S_H

#include "hal_include.h"
//设备地址
#define GY901S_YYMM			0x30
#define GY901S_DDHH			0x31
#define GY901S_MMSS	        	0x32
#define GY901S_MS			0x33
#define GY901S_AX			0x34
#define GY901S_AY			0x35
#define GY901S_AZ			0x36
#define GY901S_GX			0x37
#define GY901S_GY			0x38
#define GY901S_GZ			0x39
#define GY901S_HX			0x3a
#define GY901S_HY			0x3b
#define GY901S_HZ			0x3c			
#define GY901S_Roll			0x3d
#define GY901S_Pitch		        0x3e
#define GY901S_Yaw			0x3f
#define GY901S_TEMP			0x40
#define GY901S_D0Status		        0x41
#define GY901S_D1Status		        0x42
#define GY901S_D2Status		        0x43
#define GY901S_D3Status		        0x44
#define GY901S_PressureL		0x45
#define GY901S_PressureH		0x46
#define GY901S_HeightL			0x47
#define GY901S_HeightH			0x48
#define GY901S_LonL		        0x49
#define GY901S_LonH			0x4a
#define GY901S_LatL			0x4b
#define GY901S_LatH			0x4c
#define GY901S_GPSHeight                0x4d
#define GY901S_GPSYAW                   0x4e
#define GY901S_GPSVL			0x4f
#define GY901S_GPSVH			0x50
#define GY901S_IICAddr                  0x50

extern void GY901S_Init();
extern void Get_GY901S_Acc();
extern void Get_GY901S_Gyro();
extern void Get_GY901S_Mag();
extern void Get_GY901S_Angle();
extern void Get_GY901S_Dates();
extern float GY901_gyro_x,GY901_gyro_y,GY901_gyro_z;//陀螺仪
extern float GY901_acc_x, GY901_acc_y, GY901_acc_z;//加速度
extern float GY901_mag_x,GY901_mag_y,GY901_mag_z;//磁场
extern float GY901_pitch, GY901_roll,  GY901_yaw;//偏角
extern uint16 YY,MM,DD,HH,MIN,SS,MS;//年、月、日、时、分、秒、毫秒



#endif