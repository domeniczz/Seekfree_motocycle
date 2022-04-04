#include  "image_processing.h"
#include "math.h"


 LadderMovePoint         L_Move;
//�������������㷨�ҵ�
 LadderMovePoint         R_Move;
 Dispose_Image            DI={
   /*��������״̬�ж�����*/ 
  {FALSE},  
   /*(ֱ������������*/ 
  {FALSE},
     /*(ֱ������������*/ 
  {FALSE},
    /*ͼ����Χ*/
  /*��*/ 0, /*��*/ 59, /*��*/ 5, /*��*/ 74,
    /*ֱ���о�*/   
  { 55.0, 44.0, 37.0, 28.0, 20.0, 13.0, 8.0, 4.0, 2.0, 1.0 },
};

uint8 ui8_LineWidthWaiGua1[60] = 
{
2,2,2,2,2,2,2,9,10,11,12,14,
15,17,18,18,19,21,21,22,23,25,25,27,
28,30,31,31,32,33,34,35,36,37,39,41,
41,42,43,44,46,47,48,48,50,51,53,53,
54,55,57,58,59,60,61,62,63,64,65,66,

};
//80*60�궨
uint8 ui8_LineWidthWaiGua[60] = 
{
1,1,3,5,5,8,9,10,11,13,14,16,
19,21,23,25,27,29,31,33,36,38,40,42,
44,46,48,50,52,55,57,59,61,63,65,68,
70,71,72,74,75,76,77,77,77,77,77,77,
78,78,78,78,78,78,78,78,78,78,78,78
};
uint8 street_len_40; //��40�ߵ�ֱ������
uint8 street_len_5; //��10�ߵ�ֱ������
uint8 street_len_75; //��70�ߵ�ֱ������
uint8 image_threshold= 96;
uint8 Image_threshold[3]={130,130,130};  //4��
uint8 Vistable_scale=0;
uint8 img_x=0;
uint8 img_y=0;
uint8 Small=0;//Ĭ��160*60
uint8 Change_time=0;
uint8 L_point=2;
uint8 R_point=78;



void Soft_Binarization(void)
{  

     dispose_D_to_B(mt9v03x_image[0],180);
}
/***ͼ���ʼ��***/
void InitDisposeImageData (void) {
 // DI.i16p_dataImage         =       i16p_GetData();
  DI.i16_Mid[0]             =            MID_POINT;
  DI.i16_Mid[1]             =            MID_POINT;
  DI.i16_Mid[2]             =            MID_POINT;
  DI.i16_Mid[3]             =            MID_POINT;
  DI.i16_Mid[4]             =            MID_POINT;
  DI.i16_FinallyMid[0]      =            MID_POINT;
  DI.i16_FinallyMid[1]      =            MID_POINT;
  DI.i16_FinallyMid[2]      =            MID_POINT;
  DI.i16_FinallyMid[3]      =            MID_POINT;
  DI.i16_FinallyMid[4]      =            MID_POINT;
  //DI.i16p_dataImage[State]  =                FALSE;
  DI.ui8_LPoint[DI.ui8_DisposeScopeDown] =      0;
  DI.ui8_RPoint[DI.ui8_DisposeScopeDown] =      79;
  //Ȩ������

  DI.f_BaseLineWeight[0]=0;
  DI.f_BaseLineWeight[1]=1;
  DI.f_BaseLineWeight[2]=1;
  DI.f_BaseLineWeight[3]=2;
  DI.f_BaseLineWeight[4]=2;
  DI.f_BaseLineWeight[5]=3;
  DI.f_BaseLineWeight[6]=1;
  DI.f_BaseLineWeight[7]=1;
  DI.f_BaseLineWeight[8]=0;
  DI.f_BaseLineWeight[9]=0;
    DI.ui8_LineWidth=ui8_LineWidthWaiGua;
  DI.f_LineWeight[0] = DI.f_BaseLineWeight[0];
}
/************************************************************************
����������ȡ��ֵ
����ֵ����ֵ
���ܣ����ȷ����ֵ
************************************************************************/
uint8 otsuThreshold(uint8 *image, uint16 col, uint16 row)
{
    #define GrayScaleMAX 170//110
    #define GrayScaleMIN 100  //50
    uint16 width = col;
    uint16 height = row;
    int pixelCount[GrayScaleMAX];
    float pixelPro[GrayScaleMAX];
    int i, j, pixelSum = width * height/8;
    uint8 threshold = 0;
    uint8* data = image;  //ָ���������ݵ�ָ��
    for (i =GrayScaleMIN; i < GrayScaleMAX; i++)
    {
        pixelCount[i] = 0;
        pixelPro[i] = 0;
    }
    
    uint32 gray_sum=0;
    //ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���  
    for (i = 0; i < height; i+=2)
    {
        for (j = 0; j < width; j+=4)
        {
          if(data[i * width + j]>=GrayScaleMAX) data[i * width + j]=GrayScaleMAX;
          else if(data[i * width + j]<=GrayScaleMIN) data[i * width + j]=GrayScaleMIN; 
          
            pixelCount[(int)data[i * width + j]]++;  //����ǰ�ĵ������ֵ��Ϊ����������±�
            gray_sum+=(int)data[i * width + j];       //�Ҷ�ֵ�ܺ�
        }
    }
                      
    //����ÿ������ֵ�ĵ�������ͼ���еı���  
  
    for (i = GrayScaleMIN; i < GrayScaleMAX; i++)
    {
        pixelPro[i] = (float)pixelCount[i] / pixelSum;
        
    }

    //�����Ҷȼ�[0,255]  
    float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;
    
     
        w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
        for (j = GrayScaleMIN; j < GrayScaleMAX; j++)         
        {
            
                w0 += pixelPro[j];  //��������ÿ���Ҷ�ֵ�����ص���ռ����֮��   ���������ֵı���
                u0tmp += j * pixelPro[j];  //�������� ÿ���Ҷ�ֵ�ĵ�ı��� *�Ҷ�ֵ 
           
               w1=1-w0;
               u1tmp=gray_sum/pixelSum-u0tmp;
        
                u0 = u0tmp / w0;              //����ƽ���Ҷ�
                u1 = u1tmp / w1;              //ǰ��ƽ���Ҷ�
                u = u0tmp + u1tmp;            //ȫ��ƽ���Ҷ�
                deltaTmp = w0 * pow((u0 - u), 2) + w1 * pow((u1 - u), 2);
                if (deltaTmp > deltaMax)
                {
                    deltaMax = deltaTmp;
                    threshold = j;
                }
                if (deltaTmp < deltaMax)
                {
                break;
                }
          
         }

    return threshold;
}
/************************************************************************
��������ͼ���ֵ��
���ܣ����ݸ�����ֵ��ֵ��
************************************************************************/
void dispose_D_to_B(uint8 *p,uint8 value)
{
  uint8 i,j;
  for(i=0;i<ROW;i++)
    for(j=0;j<COL;j++)
    {
     if(*(p+i*MT9V03X_W+j*2)>value)
      DI.ui8_ImageArray[i][j]=1;
     else
      DI.ui8_ImageArray[i][j]=0; 
    }

  
}


/***����������***/
void ConstructImage (void) {
  //Soft_Binarization(); // ͼ��ѹ��Zip_Image֮�󣬶�ֵ���ǲ���Ҫ��
  Ladder();
  FitRoad();//��û�п��ǻ���
  Get_len();
  GetReverseVisualRange();//��ȡ���Ӿ���
}
void Ladder (void) {
  uint8 ui8_LF[SIZE_HRE] = {0}; //��¼���޼������������˸�ֵΪ1��û�д�����Ϊ0
  uint8 ui8_RF[SIZE_HRE] = {0};
  
  L_Move.ui8_ImageX     = DI.ui8_DisposeScopeLeft;
  L_Move.ui8_ImageY     = DI.ui8_DisposeScopeDown;
  L_Move.ui8_MaxY       = DI.ui8_DisposeScopeDown;
  L_Move.ui8_AllMaxY    = DI.ui8_DisposeScopeDown;
  
  R_Move.ui8_ImageX     = DI.ui8_DisposeScopeRight;
  R_Move.ui8_ImageY     = DI.ui8_DisposeScopeDown;
  R_Move.ui8_MaxY       = DI.ui8_DisposeScopeDown;
  R_Move.ui8_AllMaxY    = DI.ui8_DisposeScopeDown;
  
  //�������
  while (LeftPointLadder(ui8_LF) 
         && L_Move.ui8_ImageY > DI.ui8_DisposeScopeUp
           && L_Move.ui8_ImageX < DI.ui8_DisposeScopeRight) {
    if (L_Move.ui8_ImageX < MID_POINT && L_Move.ui8_MaxY > L_Move.ui8_ImageY) {
      L_Move.ui8_MaxY = L_Move.ui8_ImageY;
    }
  }
    
  //�ҵ�����
  while (RightPointLadder(ui8_RF)
         && R_Move.ui8_ImageY > DI.ui8_DisposeScopeUp
           && R_Move.ui8_ImageX > DI.ui8_DisposeScopeLeft) {
    if (R_Move.ui8_ImageX > MID_POINT && R_Move.ui8_MaxY > R_Move.ui8_ImageY) {
      R_Move.ui8_MaxY = R_Move.ui8_ImageY;
    }
  }
  //��ֵ��ȡ���
    if (L_Move.ui8_MaxY < R_Move.ui8_MaxY) {
    DI.ui8_ScanDirection =  Lstart;
  } else if (L_Move.ui8_MaxY > R_Move.ui8_MaxY) {
    DI.ui8_ScanDirection =  Rstart;
  } else {
    DI.ui8_ScanDirection =  Mstart;
  }

}

/************************************************************************
���������������
���ܣ�����¼�߽�
����ֵ���ܷ�����ƶ�
************************************************************************/
uint8 LeftPointLadder (uint8* ui8p_LF) {
  if (!DI.ui8_ImageArray[L_Move.ui8_ImageY][L_Move.ui8_ImageX])                                //�ڵ�������
  {
        while (L_Move.ui8_ImageX < DI.ui8_DisposeScopeRight
               && !DI.ui8_ImageArray[L_Move.ui8_ImageY][L_Move.ui8_ImageX + 1])
        {
          L_Move.ui8_ImageX ++;
        }
                if (L_Move.ui8_ImageX < DI.ui8_DisposeScopeRight)
                {
                  L_Move.ui8_ImageX ++;
                  return TRUE;
                } else 
                {
                  return FALSE;
                }
   } 
  
  else if (DI.ui8_ImageArray[L_Move.ui8_ImageY - 1][L_Move.ui8_ImageX])                     //���ϻ��ǰ���
  {
        if (L_Move.ui8_ImageY == DI.ui8_DisposeScopeDown 
            && DI.ui8_LPoint[L_Move.ui8_ImageY] - DI.ui8_DisposeScopeLeft > MID_POINT >> 2
            && DI.ui8_LPoint[L_Move.ui8_ImageY] - L_Move.ui8_ImageX > MID_POINT >> 2) //����һ֡��ͼ����жԱ�
        {
            L_Move.ui8_ImageX = (DI.ui8_LPoint[L_Move.ui8_ImageY] + L_Move.ui8_ImageX) / 2;//���½ǳ�����㣬�����ϴ����Ƚ�����
        }
        else 
        {
          if (!ui8p_LF[L_Move.ui8_ImageY]) 
          {
            DI.ui8_LPoint[L_Move.ui8_ImageY] = L_Move.ui8_ImageX;//�ҵ�����¼������
            L_Move.ui8_AllMaxY = L_Move.ui8_ImageY;
            ui8p_LF[L_Move.ui8_ImageY] = 1;
          }
            L_Move.ui8_ImageY --;
        }
    return TRUE;
  }
  
  else if (DI.ui8_ImageArray[L_Move.ui8_ImageY][L_Move.ui8_ImageX + 1])                 //�����Ǻ�������
 {
        L_Move.ui8_ImageX ++;
        return TRUE;
  }
  
  else if (L_Move.ui8_ImageY < DI.ui8_DisposeScopeDown                                  //�����Ҳ����׵㣬�������Ҳ����׵㣬�򷵻���
             && DI.ui8_ImageArray[L_Move.ui8_ImageY + 1][L_Move.ui8_ImageX]) 
  {
        while (L_Move.ui8_ImageY < DI.ui8_DisposeScopeDown
               && DI.ui8_ImageArray[L_Move.ui8_ImageY + 1][L_Move.ui8_ImageX]
                 && !DI.ui8_ImageArray[L_Move.ui8_ImageY + 1][L_Move.ui8_ImageX + 1]) 
        {
          L_Move.ui8_ImageY ++;
        }
        if (L_Move.ui8_ImageY < DI.ui8_DisposeScopeDown)
        {
          L_Move.ui8_ImageY ++;
          L_Move.ui8_ImageX ++;
          return TRUE;
        } else 
        {
          return FALSE;
        }
  }
  
  else {
    return FALSE;
  }
}

/************************************************************************
���������ҵ�����
���ܣ��ҵ��¼�߽�
����ֵ���ܷ�����ƶ�
************************************************************************/
uint8 RightPointLadder (uint8* ui8p_RF) {
  if (!DI.ui8_ImageArray[R_Move.ui8_ImageY][R_Move.ui8_ImageX]) {
    while (R_Move.ui8_ImageX > DI.ui8_DisposeScopeLeft
           && !DI.ui8_ImageArray[R_Move.ui8_ImageY][R_Move.ui8_ImageX - 1]) {
      R_Move.ui8_ImageX --;
    }
    if (R_Move.ui8_ImageX > DI.ui8_DisposeScopeLeft) {
      R_Move.ui8_ImageX --;
      return TRUE;
    } else {
      return FALSE;
    }
  } else if (DI.ui8_ImageArray[R_Move.ui8_ImageY - 1][R_Move.ui8_ImageX]) {
    if (R_Move.ui8_ImageY == DI.ui8_DisposeScopeDown 
        && DI.ui8_DisposeScopeRight - DI.ui8_RPoint[R_Move.ui8_ImageY] > MID_POINT >> 2
        && R_Move.ui8_ImageX - DI.ui8_RPoint[R_Move.ui8_ImageY] > MID_POINT >> 2) {
      R_Move.ui8_ImageX = (DI.ui8_RPoint[R_Move.ui8_ImageY] + R_Move.ui8_ImageX) / 2;
    } else {
      if (!ui8p_RF[R_Move.ui8_ImageY]) {
        DI.ui8_RPoint[R_Move.ui8_ImageY] = R_Move.ui8_ImageX;
        R_Move.ui8_AllMaxY = R_Move.ui8_ImageY;
        ui8p_RF[R_Move.ui8_ImageY] = 1;
      }
      R_Move.ui8_ImageY --;
    }
    return TRUE;
  } else if (DI.ui8_ImageArray[R_Move.ui8_ImageY][R_Move.ui8_ImageX - 1]) {
    R_Move.ui8_ImageX --;
    return TRUE;
  } else if (R_Move.ui8_ImageY < DI.ui8_DisposeScopeDown 
             && DI.ui8_ImageArray[R_Move.ui8_ImageY + 1][R_Move.ui8_ImageX]) {
    while (R_Move.ui8_ImageY < DI.ui8_DisposeScopeDown
           && DI.ui8_ImageArray[R_Move.ui8_ImageY + 1][R_Move.ui8_ImageX]
             && !DI.ui8_ImageArray[R_Move.ui8_ImageY + 1][R_Move.ui8_ImageX - 1]) {
      R_Move.ui8_ImageY ++;
    }
    if (R_Move.ui8_ImageY < DI.ui8_DisposeScopeDown) {
      R_Move.ui8_ImageY ++;
      R_Move.ui8_ImageX --;
      return TRUE;
    } else {
      return FALSE;
    }
  } else {
    return FALSE;
  }
}

           
/************************************************************************
���������������
���ܣ����������н�·��   //ע�⣺����Ҫ���з���char����
************************************************************************/
void FitRoad (void) {
  /*����߽�************************************************************/
  int8  i8_UpLpX = - 1;
  uint8 ui8_UpLpY;
  int8  i8_EndLpX = - 1;
  uint8 ui8_EndLpY;
  
  int8  i8_UpRpX = - 1;
  uint8 ui8_UpRpY;
  int8  i8_EndRpX = - 1;
  uint8 ui8_EndRpY;
   
  
  if (DI.ui8_ScanDirection == Rstart) {//�ҹղ�����
    for (uint8 ui8_Y = DI.ui8_DisposeScopeDown - 1; ui8_Y > L_Move.ui8_AllMaxY; ui8_Y --) {
      if (i8_UpLpX == - 1 && DI.ui8_LPoint[ui8_Y] <= DI.ui8_LPoint[ui8_Y + 1]) {
        ui8_UpLpY = ui8_Y + 1;
        i8_UpLpX = DI.ui8_LPoint[ui8_UpLpY];
      } else if (i8_UpLpX != - 1 
                 && i8_EndLpX == - 1 
                   && DI.ui8_LPoint[ui8_Y] > DI.ui8_LPoint[ui8_Y + 1]) {
        ui8_EndLpY = ui8_Y;
       // if(L_Ring_delay_flag5) ui8_EndLpY=ui8_EndLpY-3;
        i8_EndLpX = DI.ui8_LPoint[ui8_EndLpY];
      } else if (i8_UpLpX != - 1 && i8_EndLpX != - 1) {
      //�ҵ������յ�������������Ѱ�ҹյ�
        Fit(i8_UpLpX, i8_EndLpX, ui8_UpLpY, ui8_EndLpY);
        i8_UpLpX = - 1;
        i8_EndLpX = - 1;
      }
    }
  } else if (DI.ui8_ScanDirection == Lstart) {//��ղ�����
    for (uint8 ui8_Y = DI.ui8_DisposeScopeDown - 1; ui8_Y > R_Move.ui8_AllMaxY; ui8_Y --) {
      if (i8_UpRpX == - 1 && DI.ui8_RPoint[ui8_Y] >= DI.ui8_RPoint[ui8_Y + 1]) {
        ui8_UpRpY = ui8_Y + 1;
        i8_UpRpX = DI.ui8_RPoint[ui8_UpRpY];
      } else if (i8_UpRpX != - 1
                 && i8_EndRpX == - 1
                   && DI.ui8_RPoint[ui8_Y] < DI.ui8_RPoint[ui8_Y + 1]) {
        ui8_EndRpY = ui8_Y;
       // if(R_Ring_delay_flag5) ui8_EndRpY=ui8_EndRpY-3;
        i8_EndRpX = DI.ui8_RPoint[ui8_EndRpY];
      } else if (i8_UpRpX != - 1 && i8_EndRpX != - 1) {
        // 
        Fit(i8_UpRpX, i8_EndRpX, ui8_UpRpY, ui8_EndRpY);
        i8_UpRpX = - 1;
        i8_EndRpX = - 1;
      }
    }
  } else {
    for (uint8 ui8_Y = DI.ui8_DisposeScopeDown - 1; ui8_Y > L_Move.ui8_AllMaxY; ui8_Y --) {
      if (i8_UpLpX == - 1 && DI.ui8_LPoint[ui8_Y] <= DI.ui8_LPoint[ui8_Y + 1]) {
        ui8_UpLpY = ui8_Y + 1;
        i8_UpLpX = DI.ui8_LPoint[ui8_UpLpY];
      } else if (i8_UpLpX != - 1 
                 && i8_EndLpX == - 1 
                   && DI.ui8_LPoint[ui8_Y] > DI.ui8_LPoint[ui8_Y + 1]) {
        ui8_EndLpY = ui8_Y;
       // if(L_Ring_delay_flag5) ui8_EndLpY=ui8_EndLpY-3;
        i8_EndLpX = DI.ui8_LPoint[ui8_EndLpY];
      } else if (i8_UpLpX != - 1 && i8_EndLpX != - 1) {
        //
        Fit(i8_UpLpX, i8_EndLpX, ui8_UpLpY, ui8_EndLpY);
        i8_UpLpX = - 1;
        i8_EndLpX = - 1;
      }
    }
    
    for (uint8 ui8_Y = DI.ui8_DisposeScopeDown - 1; ui8_Y > R_Move.ui8_AllMaxY; ui8_Y --) {
      if (i8_UpRpX == - 1 && DI.ui8_RPoint[ui8_Y] >= DI.ui8_RPoint[ui8_Y + 1]) {
        ui8_UpRpY = ui8_Y + 1;
        i8_UpRpX = DI.ui8_RPoint[ui8_UpRpY];
      } else if (i8_UpRpX != - 1
                 && i8_EndRpX == - 1
                   && DI.ui8_RPoint[ui8_Y] < DI.ui8_RPoint[ui8_Y + 1]) {
        ui8_EndRpY = ui8_Y;
       //if(R_Ring_delay_flag5) ui8_EndRpY=ui8_EndRpY-3;
        i8_EndRpX = DI.ui8_RPoint[ui8_EndRpY];
      } else if (i8_UpRpX != - 1 && i8_EndRpX != - 1) {
        Fit(i8_UpRpX, i8_EndRpX, ui8_UpRpY, ui8_EndRpY);
        i8_UpRpX = - 1;
        i8_EndRpX = - 1;
      }
    }
  }
}

/************************************************************************
�����������
���ܣ����������������
************************************************************************/
void Fit (int8 i8_X1, int8 i8_X2, uint8 ui8_Y1, uint8 ui8_Y2) {
  float f_X = 0;
  
  if (i8_X1 < i8_X2) 
  {
    float f_Dx = (i8_X2 - i8_X1) / ((ui8_Y1 - ui8_Y2 - 1) * 1.0);
    for (uint8 ui8_Y = ui8_Y1 - 1; ui8_Y > ui8_Y2; ui8_Y --) 
    {
      f_X += f_Dx;
      DI.ui8_LPoint[ui8_Y] = (int) (DI.ui8_LPoint[ui8_Y1] + f_X);
    }
  }
  else 
  {
    float f_Dx = (i8_X1 - i8_X2) / ((ui8_Y1 - ui8_Y2 - 1) * 1.0);
    for (uint8 ui8_Y = ui8_Y1 - 1; ui8_Y > ui8_Y2; ui8_Y --) 
    {
      f_X += f_Dx;
      DI.ui8_RPoint[ui8_Y] = (int) (DI.ui8_RPoint[ui8_Y1] - f_X);
    }
  }
}             

/************************************************************************
���������任
���ܣ����׵��Ϊ�ڵ�
************************************************************************/
void Fits (int8 i8_X1, int8 i8_X2, uint8 ui8_Y1, uint8 ui8_Y2) {
    float f_X = 0;
  
  if (i8_X1 < i8_X2) 
  {
    float f_Dx = (i8_X2 - i8_X1) / ((ui8_Y1 - ui8_Y2 - 1) * 1.0);
    for (uint8 ui8_Y = ui8_Y1 - 1; ui8_Y > ui8_Y2; ui8_Y --) 
    {
      f_X += f_Dx;
      DI.ui8_LPoint[ui8_Y] = (int) (DI.ui8_LPoint[ui8_Y1] + f_X);
      for(uint8 X=DI.ui8_LPoint[ui8_Y];X>0;X--)
        DI.ui8_ImageArray[ui8_Y][X]=0; 
    }
  }
  else 
  {
    float f_Dx = (i8_X1 - i8_X2) / ((ui8_Y1 - ui8_Y2 - 1) * 1.0);
    for (uint8 ui8_Y = ui8_Y1 - 1; ui8_Y > ui8_Y2; ui8_Y --) 
    {
      f_X += f_Dx;
      DI.ui8_RPoint[ui8_Y] = (int) (DI.ui8_RPoint[ui8_Y1] - f_X);
      for(uint8 X=DI.ui8_RPoint[ui8_Y];X<79;X++)
        DI.ui8_ImageArray[ui8_Y][X]=0; 
    
    }
  }
}

/************************************************************************
����������ȡ������Ӿ���
���ܣ�������ֵ��������������Ӿ���
����ֵ��������Ӿ��루��ȷ��СS��ֱ����
************************************************************************/
void GetReverseVisualRange (void) {
  //ɨ��ͳ��
  uint16 ui16_SumY = 0;
  //��ʼ��X
  int16 i16_StartPointX;
  
  DI.ui8_MinH = DI.ui8_DisposeScopeUp;
  
  if (DI.ui8_LPoint[DI.ui8_DisposeScopeDown] > DI.ui8_DisposeScopeLeft
      && DI.ui8_RPoint[DI.ui8_DisposeScopeDown] < DI.ui8_DisposeScopeRight) {
    i16_StartPointX = DI.ui8_LPoint[DI.ui8_DisposeScopeDown] 
                      + DI.ui8_RPoint[DI.ui8_DisposeScopeDown] >> 1;
  } else if (DI.ui8_LPoint[DI.ui8_DisposeScopeDown] > DI.ui8_DisposeScopeLeft) {
    i16_StartPointX = DI.ui8_LPoint[DI.ui8_DisposeScopeDown] 
                      + (DI.ui8_LineWidth[DI.ui8_DisposeScopeDown] >> 1);
  } else if (DI.ui8_RPoint[DI.ui8_DisposeScopeDown] < DI.ui8_DisposeScopeRight) {
    i16_StartPointX = DI.ui8_RPoint[DI.ui8_DisposeScopeDown] 
                      - (DI.ui8_LineWidth[DI.ui8_DisposeScopeDown] >> 1);
  } else {
    i16_StartPointX = MID_POINT;
  }
  
  if (i16_StartPointX > 69) {
    i16_StartPointX = 69;
  } else if (i16_StartPointX < 10) {
    i16_StartPointX = 10;
  }//����ʮ������ɨ��
  
  for (uint8 ui8_X = 1; ui8_X <= 10; ui8_X ++) {
    uint8 ui8_Y = DI.ui8_DisposeScopeDown;
    uint8 ui8_LX = i16_StartPointX - ui8_X;
    uint8 ui8_RX = i16_StartPointX + ui8_X;
    
    while (-- ui8_Y > DI.ui8_DisposeScopeUp + 2
            && (DI.ui8_ImageArray[ui8_Y][ui8_LX]
                || DI.ui8_ImageArray[ui8_Y - 1][ui8_LX])
            && ui8_LX > DI.ui8_LPoint[ui8_Y]
            && ui8_LX < DI.ui8_RPoint[ui8_Y]) {}
    
    ui16_SumY += ui8_Y;
    
    if (DI.ui8_MinH < ui8_Y && ui8_Y != 57) {
      DI.i8_MinHX = ui8_LX;
      DI.ui8_MinH = ui8_Y;
    }
    
    ui8_Y = DI.ui8_DisposeScopeDown;
    
    while (-- ui8_Y > DI.ui8_DisposeScopeUp + 2
            && (DI.ui8_ImageArray[ui8_Y][ui8_RX]
                || DI.ui8_ImageArray[ui8_Y - 1][ui8_RX])
            && ui8_RX > DI.ui8_LPoint[ui8_Y]
            && ui8_RX < DI.ui8_RPoint[ui8_Y]) {}
    
    ui16_SumY += ui8_Y;
    
    if (DI.ui8_MinH < ui8_Y && ui8_Y != 57) {
      DI.i8_MinHX = ui8_RX;
      DI.ui8_MinH = ui8_Y;
    }
  }
    //ƽ��ֵΪ���Ӿ���
    Vistable_scale = ui16_SumY / 20;
  
  
  if (DI.ui8_MinH <Vistable_scale) {
    DI.ui8_MinH =Vistable_scale;
    DI.i8_MinHX = MID_POINT;
  }
}
/************************************************************************
��������Get_len()
���ܣ���ȡ���Ӿ����Բ�����ߵ�
����ֵ��len
***********************************************************************/
void Get_len(){
  for( img_y=50;img_y>1;img_y--){
    if(DI.ui8_ImageArray[img_y][40]==0 && DI.ui8_ImageArray[img_y-1][40]==0){
      break;
    }
  }
  //Vistable_scale=img_y;
   street_len_40=59-img_y;//��·�а�ɫ�ĳ���
    for( img_y=50;img_y>1;img_y--){
    if(DI.ui8_ImageArray[img_y][5]==0&& DI.ui8_ImageArray[img_y-1][5]==0){
      break;
    }
  }
   street_len_5=59-img_y;
   
     for( img_y=50;img_y>1;img_y--){
    if(DI.ui8_ImageArray[img_y][75]==0&& DI.ui8_ImageArray[img_y-1][75]==0){
      break;
    }
     }
   street_len_75=59-img_y;
//DI.i16p_dataImage[Height]=60-street_len_40;
}

uint8 ui8_LineWidth[60]={0};
//��ʾ����ҳ
uint8 ui8_Page = 0;

/************************************************************************
������������·��
���ܣ����ݿ��Ӿ���ȷ��·��
************************************************************************/
void MeasureLineWidth (void) { 
  for(uint8 ui8_I=0;ui8_I<60;ui8_I++)
  {
    if(DI.ui8_RPoint[ui8_I]>DI.ui8_LPoint[ui8_I])
    {
      ui8_LineWidth[ui8_I]=DI.ui8_RPoint[ui8_I]-DI.ui8_LPoint[ui8_I];
    }
  }
}
//*�궨

//void Display_ImageData(void)
//{
//    //��ʾ���ݵ���
//  if (LEFT && ui8_Page > 0) {
//    Delay_Ms(100);
//    ui8_Page --;
//    while (LEFT) ;
//
//    Delay_Ms(100);
//  } else if (RIGHT && ui8_Page < 4) {
//    Delay_Ms(100);
//    ui8_Page ++;
//    while (RIGHT) ;
//    Delay_Ms(100);
//  } if (DOWN ) {
//    MeasureLineWidth();
//    while (!RIGHT) ;
//  }
//    if (ui8_Page == 0) {
//    ips200_showint32 (0,0,ui8_LineWidth[ui8_Page*12+0],3);
//    ips200_showint32 (0,2,ui8_LineWidth[ui8_Page*12+1],6);
//    ips200_showint32 (0,4,ui8_LineWidth[ui8_Page*12+2],6);
//    ips200_showint32 (0,6,ui8_LineWidth[ui8_Page*12+3],6);
//    ips200_showint32 (40,0,ui8_LineWidth[ui8_Page*12+4],6);
//    ips200_showint32 (40,2,ui8_LineWidth[ui8_Page*12+5],6);
//    ips200_showint32 (40,4,ui8_LineWidth[ui8_Page*12+6],6);
//    ips200_showint32 (40,6,ui8_LineWidth[ui8_Page*12+7],6);
//    ips200_showint32 (80,0,ui8_LineWidth[ui8_Page*12+8],6);
//    ips200_showint32 (80,2,ui8_LineWidth[ui8_Page*12+9],6);
//    ips200_showint32 (80,4,ui8_LineWidth[ui8_Page*12+10],6);
//    ips200_showint32 (80,6,ui8_LineWidth[ui8_Page*12+11],6);
//  } else if (ui8_Page == 1) {
//    oled_printf_int32 (0,0,ui8_LineWidth[ui8_Page*12+0],3);
//    oled_printf_int32 (0,2,ui8_LineWidth[ui8_Page*12+1],6);
//    oled_printf_int32 (0,4,ui8_LineWidth[ui8_Page*12+2],6);
//    oled_printf_int32 (0,6,ui8_LineWidth[ui8_Page*12+3],6);
//    oled_printf_int32 (40,0,ui8_LineWidth[ui8_Page*12+4],6);
//    oled_printf_int32 (40,2,ui8_LineWidth[ui8_Page*12+5],6);
//    oled_printf_int32 (40,4,ui8_LineWidth[ui8_Page*12+6],6);
//    oled_printf_int32 (40,6,ui8_LineWidth[ui8_Page*12+7],6);
//    oled_printf_int32 (80,0,ui8_LineWidth[ui8_Page*12+8],6);
//    oled_printf_int32 (80,2,ui8_LineWidth[ui8_Page*12+9],6);
//    oled_printf_int32 (80,4,ui8_LineWidth[ui8_Page*12+10],6);
//    oled_printf_int32 (80,6,ui8_LineWidth[ui8_Page*12+11],6);
//  } else if (ui8_Page == 2) {
//    oled_printf_int32 (0,0,ui8_LineWidth[ui8_Page*12+0],3);
//    oled_printf_int32 (0,2,ui8_LineWidth[ui8_Page*12+1],6);
//    oled_printf_int32 (0,4,ui8_LineWidth[ui8_Page*12+2],6);
//    oled_printf_int32 (0,6,ui8_LineWidth[ui8_Page*12+3],6);
//    oled_printf_int32 (40,0,ui8_LineWidth[ui8_Page*12+4],6);
//    oled_printf_int32 (40,2,ui8_LineWidth[ui8_Page*12+5],6);
//    oled_printf_int32 (40,4,ui8_LineWidth[ui8_Page*12+6],6);
//    oled_printf_int32 (40,6,ui8_LineWidth[ui8_Page*12+7],6);
//    oled_printf_int32 (80,0,ui8_LineWidth[ui8_Page*12+8],6);
//    oled_printf_int32 (80,2,ui8_LineWidth[ui8_Page*12+9],6);
//    oled_printf_int32 (80,4,ui8_LineWidth[ui8_Page*12+10],6);
//    oled_printf_int32 (80,6,ui8_LineWidth[ui8_Page*12+11],6);
//  }  else if (ui8_Page == 3) {
//    oled_printf_int32 (0,0,ui8_LineWidth[ui8_Page*12+0],3);
//    oled_printf_int32 (0,2,ui8_LineWidth[ui8_Page*12+1],6);
//    oled_printf_int32 (0,6,ui8_LineWidth[ui8_Page*12+3],6);
//    oled_printf_int32 (40,0,ui8_LineWidth[ui8_Page*12+4],6);
//    oled_printf_int32 (40,2,ui8_LineWidth[ui8_Page*12+5],6);
//    oled_printf_int32 (40,4,ui8_LineWidth[ui8_Page*12+6],6);
//    oled_printf_int32 (40,6,ui8_LineWidth[ui8_Page*12+7],6);
//    oled_printf_int32 (80,0,ui8_LineWidth[ui8_Page*12+8],6);
//    oled_printf_int32 (80,2,ui8_LineWidth[ui8_Page*12+9],6);
//    oled_printf_int32 (80,4,ui8_LineWidth[ui8_Page*12+10],6);
//    oled_printf_int32 (80,6,ui8_LineWidth[ui8_Page*12+11],6);
//  }  else if (ui8_Page == 4) {
//    oled_printf_int32 (0,0,ui8_LineWidth[ui8_Page*12+0],3);
//    oled_printf_int32 (0,2,ui8_LineWidth[ui8_Page*12+1],6);
//    oled_printf_int32 (0,4,ui8_LineWidth[ui8_Page*12+2],6);
//    oled_printf_int32 (0,6,ui8_LineWidth[ui8_Page*12+3],6);
//    oled_printf_int32 (40,0,ui8_LineWidth[ui8_Page*12+4],6);
//    oled_printf_int32 (40,2,ui8_LineWidth[ui8_Page*12+5],6);
//    oled_printf_int32 (40,4,ui8_LineWidth[ui8_Page*12+6],6);
//    oled_printf_int32 (40,6,ui8_LineWidth[ui8_Page*12+7],6);
//    oled_printf_int32 (80,0,ui8_LineWidth[ui8_Page*12+8],6);
//    oled_printf_int32 (80,2,ui8_LineWidth[ui8_Page*12+9],6);
//    oled_printf_int32 (80,4,ui8_LineWidth[ui8_Page*12+10],6);
//    oled_printf_int32 (80,6,ui8_LineWidth[ui8_Page*12+11],6);
//  }
//}
/**�ұ߽��***/
void Seek_point(uint8 Y){
  //uint8 x1=0,x2=0,Bx3=0,Bx4=0,Wx3=0,Wx4=0;
  uint8 x1=0,x2=0,Bx3=0,Bx4=0;
  //uint8 Wlength=0,WMax_length=0;   //��ɫ������
  uint8 Blength=0,BMax_length=0;   //��ɫ������
  Change_time=0;
  L_point=2;
  R_point=78;
  //������ȡ��
  while(x1<79){
      if(!DI.ui8_ImageArray[Y][x1]){   //��һ���Ǻ�ɫ,���ȿ�ʼ��ɫ���ɫ�ƶ�
          x2=Seek_Write_point(x1,Y);
          Blength=x2-x1; 
          if(Blength>BMax_length){   //��¼��󳤶�,����¼����
              Bx4=x2;
              Bx3=x1;
              BMax_length=Blength;
          }
      }
      else{
          x2=Seek_Black_point(x1,Y);
         // x2=Seek_Write_point(x1,Y);
          Blength=x2-x1; 
          if(Blength<=10) Change_time--;
          if(Blength>BMax_length){   //��¼��󳤶�,����¼����
              Bx4=x2;
              Bx3=x1;
              BMax_length=Blength;
          }
        }
              x1=x2;
      }
        L_point=Bx3;
        R_point=Bx4;
  
}
    
    
        
      
     
//��ɫ���ɫ,���ذ�ɫ��X2
uint8 Seek_Write_point(uint8 x1,uint8 Y){
  for(img_x=x1;img_x<=78;img_x++){
    if(DI.ui8_ImageArray[Y][img_x] && DI.ui8_ImageArray[Y][img_x+1]){
       Change_time++;                           //ÿ�κڰ��������+1
       return img_x;
     }
    }
       return 79;
  }
//��ɫ���ɫ,���غڵ�X2
uint8 Seek_Black_point(uint8 x1,uint8 Y){
  for(img_x=x1;img_x<=78;img_x++){
    if(!DI.ui8_ImageArray[Y][img_x] && !DI.ui8_ImageArray[Y][img_x+1]){
       Change_time++;                         //ÿ�κڰ��������+1
       return img_x;
     }
  }
    return 79;
}
