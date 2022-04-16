/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * All rights reserved.
 *国防科技大学宣谱
 *
 * @file       		GY901S九轴陀螺仪
 * @author     		Laplace
 * @version    		v1.0
 * @Software 		IAR 8.32
 * @date       		2021-12-4
 ********************************************************************************************************************/
#include "GY901S.h"
#include "SoftIIC.h"
float GY901_gyro_x,GY901_gyro_y,GY901_gyro_z;//陀螺仪
float GY901_acc_x, GY901_acc_y, GY901_acc_z;//加速度
float GY901_mag_x,GY901_mag_y,GY901_mag_z;//磁场
float GY901_pitch, GY901_roll,  GY901_yaw;//偏角
uint16 YY,MM,DD,HH,MIN,SS,MS;//年、月、日、时、分、秒、毫秒

//-------------------------------------------------------------------------------------------------------------------
// @brief		初始化GY901S
// @param		NULL
// @return		void
// @since		v1.0
// Sample usage:				调用该函数前，请先调用模拟IIC的初始化
//-------------------------------------------------------------------------------------------------------------------
void GY901S_Init(){
    IIC_init();
	systick_delay_ms(STM0,100);
}


//-------------------------------------------------------------------------------------------------------------------
// @brief		获取GY901S加速度
// @param		NULL
// @return		void
// @since		v1.0
// Sample usage:				调用该函数前，请先调用模拟IIC的初始化
//-------------------------------------------------------------------------------------------------------------------
void Get_GY901S_Acc(){
    uint8 dats[6]={0};
  IIC_Read_Buff(GY901S_IICAddr, GY901S_AX, dats, 6);  
  GY901_acc_x = (float)((int16)(dats[1]<<8 )| dats[0]);
  GY901_acc_y =  (float)((int16)(dats[3]<<8 )| dats[2]);
  GY901_acc_z =  (float)((int16)(dats[5]<<8 )| dats[4]);
  GY901_acc_x=GY901_acc_x*16.00*9.81/32768;
  GY901_acc_y=GY901_acc_y*16.00*9.81/32768;
  GY901_acc_z=GY901_acc_z*16.00*9.81/32768;
  
}
//-------------------------------------------------------------------------------------------------------------------
// @brief		获取GY901S角速度
// @param		NULL
// @return		void
// @since		v1.0
// Sample usage:				调用该函数前，请先调用模拟IIC的初始化
//-------------------------------------------------------------------------------------------------------------------
void Get_GY901S_Gyro(){
    uint8 dats[6]={0};
  IIC_Read_Buff(GY901S_IICAddr, GY901S_GX, dats, 6);  
  GY901_gyro_x = (float)((int16)(dats[1]<<8 )| dats[0]);
  GY901_gyro_y =  (float)((int16)(dats[3]<<8 )| dats[2]);
  GY901_gyro_z =  (float)((int16)(dats[5]<<8 )| dats[4]);
  GY901_gyro_x=GY901_gyro_x*2000.00/32768;
  GY901_gyro_y=GY901_gyro_y*2000.00/32768;
  GY901_gyro_z=GY901_gyro_z*2000.00/32768;
}
//-------------------------------------------------------------------------------------------------------------------
// @brief		获取GY901S磁力计
// @param		NULL
// @return		void
// @since		v1.0
// Sample usage:				调用该函数前，请先调用模拟IIC的初始化
//-------------------------------------------------------------------------------------------------------------------
void Get_GY901S_Mag(){
    uint8 dats[6]={0};
  IIC_Read_Buff(GY901S_IICAddr, GY901S_HX, dats, 6);  
  GY901_mag_x = (float)((int16)(dats[1]<<8 )| dats[0]);
  GY901_mag_y =  (float)((int16)(dats[3]<<8 )| dats[2]);
  GY901_mag_z =  (float)((int16)(dats[5]<<8 )| dats[4]);
} 
//-------------------------------------------------------------------------------------------------------------------
// @brief		获取GY901S的角度
// @param		NULL
// @return		void
// @since		v1.0
// Sample usage:				调用该函数前，请先调用模拟IIC的初始化
//-------------------------------------------------------------------------------------------------------------------
void Get_GY901S_Angle(){
    uint8 dats[6]={0};
   IIC_Read_Buff(GY901S_IICAddr, GY901S_Roll, dats, 6);  
   GY901_roll = (float)((int16)(dats[1]<<8 )| dats[0]);
   GY901_pitch =  (float)((int16)(dats[3]<<8 )| dats[2]);
   GY901_yaw =  (float)((int16)(dats[5]<<8 )| dats[4]);
   GY901_roll=GY901_roll*180.00/32768;
   GY901_pitch=GY901_pitch*180.00/32768;
   GY901_yaw=GY901_yaw*180.00/32768;
}
//-------------------------------------------------------------------------------------------------------------------
// @brief		获取GY901S时间
// @param		NULL
// @return		void
// @since		v1.0
// Sample usage:				调用该函数前，请先调用模拟IIC的初始化
//-------------------------------------------------------------------------------------------------------------------
void Get_GY901S_Dates(){
    uint8 dates[8]={0};
   IIC_Read_Buff(GY901S_IICAddr, GY901S_YYMM, dates, 8);  
   YY = dates[0];
   MM = dates[1];
   DD = dates[2];
   HH = dates[3];
   MIN = dates[4];
   SS = dates[5];
   MS=  (uint16)((int16)(dates[7]<<8 )| dates[6]);
}
