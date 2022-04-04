#include "speed_measure.h"
uint8 COUNT=0;
int16 N_R=0;//右轮脉冲数
int16 N_L=0;//左轮脉冲数
float V_R=0;//右轮速度
float V_L=0;//左轮速度
float V_R_f=0;//编码器计算
float V_L_f=0;
float V_R_pre=0; //右轮前一次速度
float V_L_pre=0;  //左轮前一次速度
float V_Avg=0;    //车速
int16 Out_PWM=0;
float Out_PWM_pre=0;
float DJ_kp=5;//0.01;     //电机P
float DJ_ki=0.15;     //电机I
float DJ_kd= 0  ;    //电机D

/***函数部分***/
/***主控速函数***/
void Get_Speed(){
  N_L= -gpt12_get(GPT12_T2);	// 采集对应编码器数据
//  printf("%d\n",N_L);
  gpt12_clear(GPT12_T2);													// 清除对应计数
  N_R =gpt12_get(GPT12_T4);							// 采集对应编码器数据
  gpt12_clear(GPT12_T4);
  V_R= N_R*20.4/(2355.2*0.008);//右轮速度=脉冲数*周长/2368*周期;30
  V_L= N_L*20.4/(2355.2*0.008);//左轮速度=脉冲数*周长/2368*周期;
    V_L_f=V_L;
    V_R_f=V_R;
  if(V_R_pre-V_R>=50){
    V_R=V_R_pre-50;
  }
  else if(V_R-V_R_pre>=50){
       V_R=V_R_pre+50;
  }
    
  if(V_L_pre-V_L>=50){
    V_L=V_L_pre-50;
  }
  else if(V_L-V_L_pre>=50){
       V_L=V_L_pre+50;
  }
  if(V_L>=350) V_L=350;
  if(V_R>=350) V_R=350;
  V_Avg=(V_R+V_L)/2;         //平均速度
  V_R_pre=V_R; 
  V_L_pre=V_L;
}


int16 i16_GetMv (void)
{
  return (int16)(V_R+V_L)/2;
}



 float error_pres=0;
 float error_pre_pres=0;
void speed_PID(uint16 Goal){ //固定PI控制
  //启动时加速，慢慢低头
 float errors=0;
 float P,I,D;
  Out_PWM_pre=Out_PWM;
  errors=(float)(Goal)-V_Avg;
  P=DJ_kp*(errors-error_pres);
  I=DJ_ki*errors;
//  P=DJ_p*(errors-error_pres);
//  I=DJ_i*errors;
  D=DJ_kd*(errors-2*error_pres+error_pre_pres);
  if(I>=200) I=0;
  else if(I<=-200)  I=0;
  Out_PWM+=(int16)(P+I+D);
  error_pre_pres=error_pres;
  error_pres=errors;
  if(Out_PWM>800){
    Out_PWM=800;
  }
  else if(Out_PWM<-800){
    Out_PWM=-800;
  }
}



void Dianji_Out(int16 L_outPWM,int16 R_outPWM){
   if(L_outPWM<=-8000){
     L_outPWM=-8000;
   }
   if(R_outPWM<=-5000){
     R_outPWM=-5000;
   }
   if(L_outPWM>=8000){
     L_outPWM=8000;
   }
   if(R_outPWM>=5000){
     R_outPWM=5000;
   }

  if(L_outPWM<0){
      L_outPWM=-L_outPWM;
      gpio_set(P21_4,0);
      pwm_duty(ATOM0_CH3_P21_5, L_outPWM);

  }
 else{
     gpio_set(P21_4,1);
     pwm_duty(ATOM0_CH3_P21_5, L_outPWM);

  }
  if(R_outPWM<0){
         R_outPWM=-R_outPWM;
         gpio_set(P21_2,0);
         pwm_duty(ATOM0_CH1_P21_3, R_outPWM);
  }
  else{
      gpio_set(P21_2,1);
      pwm_duty(ATOM0_CH1_P21_3, R_outPWM);

  }
}

