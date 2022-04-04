#include "duoji.h"

SteeringData Duoji;
extern Dispose_Image DI;    //ͼ����ṹ������
int16* i16p_dataDuoJi;       //���������ָ��
extern int poserror;

/*�����ʼ��*/
void Duoji_Init()
{
    gtm_pwm_init(ATOM1_CH1_P33_9, 50, DUOJI_MID_DUTY);//DUOJI_MID_DUTY
}

/*������ݳ�ʼ��*/
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

/*�������*/
void Duoji_Work(void)
{

    Duoji_Error(poserror);//��������ǰ������ֵ�� ���ƶ��ƫ��
    Duoji_Duty_Get();//��ȡ���ռ�ձ�
    Duoji_Control(); 
}

/*������Ƽ�¼ƫ��*/
void Duoji_Error(int16 i16_Midpoint)
{
    for(uint8 i = 9; i > 0; i --)
    {
    Duoji.MidEr[i] = Duoji.MidEr[i - 1];
    }

  Duoji.MidEr[0] = i16_Midpoint;
}

/*�����ȡռ�ձ�*/   
void Duoji_Duty_Get(void)
{
  //ģ��P  ������Pֵ��ַ  �����ǰƫ��
 // DuoJi_GetP((float *) &Duoji.P, Vistable_scale , (int16)Duoji.MidEr[0]); //������Ǿ���ΪɶҪ-6
  Duoji.P=15;
 // if(i16_GetMv()>=130) Duoji.P=Duoji.P+Duoji.P*((i16_GetMv()-130)/200);
  Duoji.D = 4; //D = P ?

////����ʽPD����
   Duoji.Duty = (int) (DUOJI_MID_DUTY - (Duoji.P * Duoji.MidEr[0]
                      + Duoji.D * (Duoji.MidEr[0] - Duoji.MidEr[2])   
                      )/2);
 

}

/*�������*/
void Duoji_Control(void)
{
//  Duoji.Duty += DUOJI_MID_DUTY;
    //�޶���ŷ�Χ
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
