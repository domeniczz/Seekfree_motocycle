#ifndef _INIT_H
#define _INIT_H

#include "hal_include.h"
//#define BeeOn  gpio_set(C9,1)
//#define BeeOff gpio_set(C9,0)
//#define PWM_TIM				TIM_2
//#define PWM_CH1				TIM_2_CH1_A00
//#define PWM_CH2				TIM_2_CH2_A01
//#define PWM_CH3				TIM_2_CH3_A02
//#define PWM_CH4				TIM_2_CH4_A03
//#define ENCODER_L					TIM_3
//#define ENCODER_L_A					TIM_3_ENC1_B04
//#define ENCODER_L_B					TIM_3_ENC2_B05
//#define ENCODER_R					TIM_4
//#define ENCODER_R_A					TIM_4_ENC1_B06
//#define ENCODER_R_B					TIM_4_ENC2_B07
//
//#define DS1 !gpio_get(G4)
//#define DS2 !gpio_get(G5)
//#define DS3 !gpio_get(G2)
//#define DS4 !gpio_get(G3)
//
//extern void BootSet();
 void InitAll(void);

#endif
