#include "Init.h"

//五向开关初始化
void Five_Init(){
//  gpio_init(C1, GPI, 1, GPI_PULL_UP);
    gpio_init(P22_0, GPI, 0, PUSHPULL);
    gpio_init(P22_1, GPI, 0, PUSHPULL);
    gpio_init(P22_2, GPI, 0, PUSHPULL);
    gpio_init(P22_3, GPI, 0, PUSHPULL);
}
//
////蜂鸣器。拨码开关
void My_gpioInit(){
  //蜂鸣器
     gpio_init(P33_10, GPO, 0, PUSHPULL);
     //拨码开关
     gpio_init(P33_12, GPO, 1, PUSHPULL);
     gpio_init(P33_13, GPO, 1, PUSHPULL);
}
//电机初始化
void Motor_Init(){
        gpio_init(P21_2, GPO, 1, PUSHPULL);
        gpio_init(P21_4, GPO, 1, PUSHPULL);
        gtm_pwm_init(ATOM0_CH1_P21_3, 10000, 0);
        gtm_pwm_init(ATOM0_CH3_P21_5, 10000, 0);
}
//编码器初始化
void Encoder_Init(){
    gpt12_init(GPT12_T2, GPT12_T2INB_P33_7, GPT12_T2EUDB_P33_6);
    gpt12_init(GPT12_T4, GPT12_T4INA_P02_8, GPT12_T4EUDA_P00_9);
}
////pit初始化2ms
void PIT_Init(){
    //pit_interrupt_ms(CCU6_0, PIT_CH0, 5);											// 初始化TIM1频率2Hz中断优先级3 								// 初始化引脚为推挽输出 默认高电平
    pit_interrupt_ms(CCU6_0, PIT_CH0, 4.27);
}




//void BootSet(){
//  Motor_Init();
//  oled_init();    //显示屏
//  Five_Init();    //五向开关
//  InitMenu();     //菜单
//  My_gpioInit();  //蜂鸣器、拨码开关
//  while(!OK);   //等待确认开机
//  oled_fill(0x00);//开机信号
//}






/**********初始化部分******/
void InitAll(){

   systick_delay_ms(STM0,50);           //务必延时

   Five_Init();
   My_gpioInit();
   Motor_Init();

//   lcd_init();
   Duoji_Init();
   Duoji_Data_Init();

   ips200_init();


 //  GY901S_Init();
   while(!OK);   //等待确认开机

   BeeOn;

   systick_delay_ms(STM0,200);

   mt9v03x_init();
   PIT_Init();
   Encoder_Init();              //编码器初始化
   InitDisposeImageData ();
   icm20602_init();

   BeeOff;

}




