#ifndef __IMAGE__H
#define __IMAGE__H
#include "hal_include.h"
#define TRUE               1		
#define FALSE               0	
//����
#define Height                  1
#define ROW                  60
#define COL                  80

typedef struct {
  //ͼ��X����
  uint8 ui8_ImageX;
  //ͼ��Y����
  uint8 ui8_ImageY;
  //ͼ�񵥱���Զ��
  uint8 ui8_MaxY;
  //ͼ����Զ��
  uint8 ui8_AllMaxY;
} LadderMovePoint;

typedef struct {
    //״̬�жϼ���
  uint16        ui16_counter[5];
  //״̬��־
  int8          i8_StatusFlag[9];
  //״̬�������
  int8          i8_StatusHandle[9];
  //ͼ����Χ
  uint8         ui8_DisposeScopeUp;
  uint8         ui8_DisposeScopeDown;
  uint8         ui8_DisposeScopeLeft;
  uint8         ui8_DisposeScopeRight;
    //ֱ����λ��
  float        f_BaseY[10];
    //��׼����
  uint8*        ui8_LineWidth;
    //��׼Ȩ��
  float        f_BaseLineWeight[10];
      //��Ȩ��
  float        f_LineWeight[10];
  //����������
  int16*        i16p_dataImage;
  //ͼ������
  uint8         ui8_ImageArray[ROW][COL];
  //��߽�
  int8         ui8_LPoint[ROW];  // ��ߵ�xֵ
  //�ұ߽�
  int8         ui8_RPoint[ROW];  // �ұߵ�xֵ
  //ɨ���о���
  uint8         ui8_ScanLineY[10];
  //ɨ������߽�(����)
  uint8         ui8_ScanLineL[10];
  //ɨ�����ұ߽�(����)
  uint8         ui8_ScanLineR[10];
  //ɨ������߽�(��߽�)
  uint8         ui8_ScanLineToL[10];
  //ɨ�����ұ߽�(��߽�)
  uint8         ui8_ScanLineToR[10];
  //ɨ���������
  uint8         ui8_ScanLineWidth[10];
  //��ֵ��ȡ���
  uint8         ui8_ScanDirection;
  //��ʼ��ֵ
  int16         i16_Mid[10];
  //������ֵ
  int16         i16_FinallyMid[10];
  //��С���Ӿ���
  uint8         ui8_MinH;
  int8          i8_MinHX;
  //������Ӿ���
  uint8         VisitableScope;
  //������Զ��
  uint8        MaxPoint;
} Dispose_Image;
extern uint8 street_len_40; //��40�ߵ�ֱ������
extern uint8 street_len_5; //��10�ߵ�ֱ������
extern uint8 street_len_75; //��70�ߵ�ֱ������;
extern uint8 L_point;
extern uint8 R_point;
extern uint8 Vistable_scale;
extern uint8 Small;
extern uint8 Change_time;
extern void ConstructImage (void);
extern void Ladder (void) ;
extern uint8 LeftPointLadder (uint8* ui8p_LF);
extern uint8 image_threshold;
extern uint8 RightPointLadder (uint8* ui8p_RF);
extern void FitRoad (void);
extern void Fit (int8 i8_X1, int8 i8_X2, uint8 ui8_Y1, uint8 ui8_Y2);
extern void Fits (int8 i8_X1, int8 i8_X2, uint8 ui8_Y1, uint8 ui8_Y2);
extern void GetReverseVisualRange(void);
extern void Soft_Binarization(void);    
extern uint8 otsuThreshold(uint8 *image, uint16 col, uint16 row);
extern void dispose_D_to_B(uint8 *p,uint8 value1);
extern void dispose_D_to_B1(uint8 *p,uint8 value1,uint8 value2,uint8 value3);
extern void Get_len(void);
extern void InitDisposeImageData (void);
extern void Display_ImageData(void);
void Seek_point(uint8 Y);
uint8 Seek_Write_point(uint8 x1,uint8 Y);
uint8 Seek_Black_point(uint8 x1,uint8 Y);
#endif


