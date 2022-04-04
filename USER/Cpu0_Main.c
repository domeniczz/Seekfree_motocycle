/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ����Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		main
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		ADS v1.2.2
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 ********************************************************************************************************************/


#include "hal_include.h"
#include "icm20602.h"
#pragma section all "cpu0_dsram"
extern LadderMovePoint         L_Move;//�������������㷨���
extern LadderMovePoint         R_Move;//�������������㷨�ҵ�
extern Dispose_Image DI;//ͼ����ṹ������
extern EulerAngleTypedef      SystemAttitude;            /////��̬��
extern float Distance;
extern float SumAngle;
extern uint16 Write_Point;
extern float AccZAngle;

//ѹ��ͼ������ת��ֵ��
uint8 image[60][80]; //ѹ��������
void Zip_Image(){
  float K_W=MT9V03X_W/80;
  for(uint8 i=0;i<60;i++){
    for(uint8 j=0;j<80;j++){
      if(mt9v03x_image[i][(uint8)(j*K_W)]>190/*190�Ƕ�ֵ������ֵimage_threshold*/){ //HAL_i16_FlashReadInt16(Image_Ithreshold_Addr)){
         image[i][j]=255;
         DI.ui8_ImageArray[i][j]=1; // ��ֵ��֮���
      }
      else
      {
         image[i][j]=0;
         DI.ui8_ImageArray[i][j]=0;
      }
      //  mt9v03x_csi_image[i][(uint8)(j*K_W)];
    }
  }
}
uint8  Run=0;
uint8 Chuku_flag=0;
uint16 dt=780;
int core0_main(void)
{
    get_clk();//��ȡʱ��Ƶ��  ��ر���
	//�û��ڴ˴����ø��ֳ�ʼ��������

    //�ȴ����к��ĳ�ʼ�����
	IfxCpu_emitEvent(&g_cpuSyncEvent);
	IfxCpu_waitEvent(&g_cpuSyncEvent, 0xFFFF);


	enableInterrupts();

	InitAll();

	gyro_param_t GyroOffset=gyroOffsetInit();

	while (TRUE)
	{
	      Zip_Image();
	      DisposeImage();
//	      printf("before_display");
//	      Display_ImageData();
//	      printf("after_display");

	       for(uint8 Y=0;Y<=DI.ui8_DisposeScopeDown;Y++){
	            image[Y][DI.ui8_LPoint[Y]]=0;
	            image[Y][DI.ui8_RPoint[Y]]=0;
	            image[Y][(DI.ui8_LPoint[Y]+DI.ui8_RPoint[Y])/2]=0;
	          }
	      for(uint8 Y=0;Y<=9;Y++){
	            for(uint8 X=DI.ui8_LPoint[DI.ui8_ScanLineY[Y]];X<=DI.ui8_RPoint[DI.ui8_ScanLineY[Y]];X++){
	              image[DI.ui8_ScanLineY[Y]][X]=0;
	            }
	      }
	          if(OK) {
	          BeeOn;//��������
	          systick_delay_ms(STM0,500);
	          BeeOff;
	          Run=1;
	      }

/*	    lcd_displayimage032(image[0], 80,/ 60);
	    lcd_showint16(0,7,poserror);
	    lcd_showint16(0,6,Write_Point);
	    lcd_showint16(0,5,SumAngle);
	    lcd_showint16(0,4,street_len_40);*/

//	      Get_GY901S_Angle();
//	      Get_GY901S_Gyro();
//	    lcd_showfloat(0,0,GY901_gyro_x,3,3);
//	    lcd_showfloat(20,1,GY901_roll,3,3);
//	    lcd_showfloat(0,2,GY901_gyro_z,3,3);

	    icm_param_t icmdata=icmGetValues(GyroOffset);
	          icmAHRSupdate(&icmdata);
//	   gtm_pwm_init(ATOM1_CH1_P33_9, 50, DUOJI_MID_DUTY);//DUOJI_MID_DUTY
//	    lcd_showuint16(0,3,dt);
//	    if(Up){
//	        systick_delay_ms(STM0,250);           //�����ʱ
//	        dt+=10;
//	    }
//	       // lcd_showfloat(0,3,AccZAngle,3,3);
//	        if(OK){
//	            systick_delay_ms(STM0,250);           //�����ʱ
//	            dt-=10;
//	        }
//	        // lcd_showfloat(0,3,AccZAngle,3,3);
//	         if(Down){
//	             systick_delay_ms(STM0,250);           //�����ʱ
//	             dt+=1;
//	         }
//	         // lcd_showfloat(0,3,AccZAngle,3,3);
//	           if(Right){
//	               systick_delay_ms(STM0,250);           //�����ʱ
//	               dt-=1;
//	           }
//	           DuojiDuty(dt);




	}
}


#pragma section all restore


