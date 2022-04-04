#include "duoji.h"

SteeringData Duoji;
extern Dispose_Image DI;    //图像处理结构体声明
int16* i16p_dataDuoJi;       //舵机控制量指针
extern int poserror;

/*舵机初始化*/
void Duoji_Init()
{
    gtm_pwm_init(ATOM1_CH1_P33_9, 50, DUOJI_MID_DUTY);//DUOJI_MID_DUTY
}

/*舵机数据初始化*/
void Duoji_Data_Init(void)
{
    InitMH ();
    Duoji.P = 40.0;
    Duoji.D = 3.0;
    Duoji.Mid = MID_POINT;
    Duoji.MidDuty = DUOJI_MID_DUTY;
    Duoji.MaxDuty = DUOJI_MAX_DUTY;
    Duoji.MinDuty = DUOJI_MIN_DUTY;
    Duoji.Duty = Duoji.MidDuty;
}

/*舵机工作*/
void Duoji_Work(void)
{

    Duoji_Error(poserror);//参数：当前赛道中值， 递推舵机偏差
    Duoji_Duty_Get();//获取舵机占空比
    Duoji_Control(); 
}

/*舵机递推记录偏差*/
void Duoji_Error(int16 i16_Midpoint)
{
    for(uint8 i = 9; i > 0; i --)
    {
    Duoji.MidEr[i] = Duoji.MidEr[i - 1];
    }

  Duoji.MidEr[0] = i16_Midpoint;
}

/*舵机获取占空比*/   
void Duoji_Duty_Get(void)
{
  //模糊P  传入舵机P值地址  舵机当前偏差
 // DuoJi_GetP((float *) &Duoji.P, Vistable_scale , (int16)Duoji.MidEr[0]); //反向可是距离为啥要-6
  Duoji.P=15;
 // if(i16_GetMv()>=130) Duoji.P=Duoji.P+Duoji.P*((i16_GetMv()-130)/200);
  Duoji.D = 4; //D = P ?

////比例式PD控制
   Duoji.Duty = (int) (DUOJI_MID_DUTY - (Duoji.P * Duoji.MidEr[0]
                      + Duoji.D * (Duoji.MidEr[0] - Duoji.MidEr[2])   
                      )/2);
 

}

/*舵机控制*/
void Duoji_Control(void)
{
//  Duoji.Duty += DUOJI_MID_DUTY;
    //限定打脚范围
  if(Duoji.Duty > Duoji.MaxDuty)
  {
    Duoji.Duty = Duoji.MaxDuty;
  }
  else if(Duoji.Duty < Duoji.MinDuty)
  {
    Duoji.Duty = Duoji.MinDuty;
  }
  // if(DI.i16p_dataImage[Run]==STOP)DuojiDuty(DUOJI_MID_DUTY);
  // else 
  DuojiDuty(Duoji.Duty);
}
