/*********************************************************************************************************************

 *
 * @file       		MPU6050
 * @version    		v2.0
 * @Software 		IAR 7.7 or MDK 5.23
 * @Target core		S9KEA128AMLK
 * @date       		2018-4-7
 * @note	
					接线定义
					------------------------------------ 
						SCL                 查看OverU_IIC文件内的OverU_SCL宏定义
						SDA                 查看OverU_IIC文件内的OverU_SDA宏定义
					------------------------------------ 
 ********************************************************************************************************************/

#include "Angle_handle.h"
#include "icm20602.h"
float        Angle=0;      //角度
float        Angle_pre=26.0;
int16        Angle_duty=0;//输出PWM
float        Angle_P=1800 ;//700//1800
float        Angle_I=3;//0.2//3
float        Angle_D=-25 ;//-20//-100
float        Angle_speed_P=-17;  //-13//-30//-15
float        Angle_speed_I=-0.05;  //-0.1//-0.05
//float        Angle_acc_P=-1800 ;//-1500
//float        Angle_acc_I=-35 ;//-35
//float        Angle_acc_D=-420 ;//-420
uint16       Angle_max=8000;
float       Z_Angle_goal_first=0.6;
int8         Min_Angle=-30;
int8         Max_Angle=42;
//float       bias_last;
//float       bias;
extern      int16                  Out_PWM;
extern      uint8                  Run;
extern      uint8            Statu;
extern      uint8            COUNT_2ms;
//---------------------------角度环5ms----------------------------------
float II=0;
float speed_I=0;
void Angle_adjust_out()
{
  Angle=get_pitch() ;
//  printf("%f\n",Angle);
  float  Z_Angle_goal= Z_Angle_goal_first;//+(DUOJI_MID_DUTY-Duoji.Duty)*0.02;//+0.003*V_L;
  float PP;
  float DD;
  float error=0;
  float error_pre=0;
  error=(float)(Angle-Z_Angle_goal);
//  poserror=error;
  if(error>=10) error=10;
  else if (error<=-10) error=-10;
  PP=Angle_P*error;
  II+=error*Angle_I;

//  if(II>=300) II=0;
//  else if(II<=-300) II=0;

  DD=Angle_D*icm_gyro_y;
//  printf("%d\n",icm_gyro_y);
//  printf("%f\n",Angle);
  error_pre=error;
  Angle_duty=(int16)(PP+II+DD);
  speed_I+=V_L*Angle_speed_I;

//  if(speed_I > +1500) speed_I = 0;                    //积分限幅
  //if(speed_I < -1500) speed_I = 0;

  float Angle_speed_duty=Angle_speed_P*V_L+speed_I;
  Angle_duty=Angle_duty-Angle_speed_duty;
  if(Angle_duty>Angle_max)
    Angle_duty=Angle_max;
  if(Angle_duty<-Angle_max)
    Angle_duty=-Angle_max;
  if(error>=7) Angle_duty=0;
  else if (error<=-7) Angle_duty=0;
}

//float Angle_acc(int16 Angle_duty){
//    bias=Angle_duty-icm_gyro_y;
//    static float error_acc;
//    error_acc+=bias;
//    float PWM_final=Angle_acc_P*bias+Angle_acc_I*error_acc+Angle_acc_D*(bias-bias_last);
//    bias_last=bias;
//    return PWM_final;
//}
  
  
  
  
  

