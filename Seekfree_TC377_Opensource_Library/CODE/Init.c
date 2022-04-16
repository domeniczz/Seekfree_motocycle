#include "Init.h"

//���򿪹س�ʼ��
void Five_Init(){
//  gpio_init(C1, GPI, 1, GPI_PULL_UP);
    gpio_init(P22_0, GPI, 0, PUSHPULL);
    gpio_init(P22_1, GPI, 0, PUSHPULL);
    gpio_init(P22_2, GPI, 0, PUSHPULL);
    gpio_init(P22_3, GPI, 0, PUSHPULL);
}
//
////�����������뿪��
void My_gpioInit(){
  //������
     gpio_init(P33_10, GPO, 0, PUSHPULL);
     //���뿪��
     gpio_init(P33_12, GPO, 1, PUSHPULL);
     gpio_init(P33_13, GPO, 1, PUSHPULL);
}
//�����ʼ��
void Motor_Init(){
        gpio_init(P21_2, GPO, 1, PUSHPULL);
        gpio_init(P21_4, GPO, 1, PUSHPULL);
        gtm_pwm_init(ATOM0_CH1_P21_3, 10000, 0);
        gtm_pwm_init(ATOM0_CH3_P21_5, 10000, 0);
}
//��������ʼ��
void Encoder_Init(){
    gpt12_init(GPT12_T2, GPT12_T2INB_P33_7, GPT12_T2EUDB_P33_6);
    gpt12_init(GPT12_T4, GPT12_T4INA_P02_8, GPT12_T4EUDA_P00_9);
}
////pit��ʼ��2ms
void PIT_Init(){
    //pit_interrupt_ms(CCU6_0, PIT_CH0, 5);											// ��ʼ��TIM1Ƶ��2Hz�ж����ȼ�3 								// ��ʼ������Ϊ������� Ĭ�ϸߵ�ƽ
    pit_interrupt_ms(CCU6_0, PIT_CH0, 4.27);
}




//void BootSet(){
//  Motor_Init();
//  oled_init();    //��ʾ��
//  Five_Init();    //���򿪹�
//  InitMenu();     //�˵�
//  My_gpioInit();  //�����������뿪��
//  while(!OK);   //�ȴ�ȷ�Ͽ���
//  oled_fill(0x00);//�����ź�
//}






/**********��ʼ������******/
void InitAll(){

   systick_delay_ms(STM0,50);           //�����ʱ

   Five_Init();
   My_gpioInit();
   Motor_Init();

//   lcd_init();
   Duoji_Init();
   Duoji_Data_Init();

   ips200_init();


 //  GY901S_Init();
   while(!OK);   //�ȴ�ȷ�Ͽ���

   BeeOn;

   systick_delay_ms(STM0,200);

   mt9v03x_init();
   PIT_Init();
   Encoder_Init();              //��������ʼ��
   InitDisposeImageData ();
   icm20602_init();

   BeeOff;

}




