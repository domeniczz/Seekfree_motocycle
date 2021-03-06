#include  "image_processing.h"
#include "math.h"


 LadderMovePoint         L_Move;
//左右两点爬梯算法右点
 LadderMovePoint         R_Move;
 Dispose_Image            DI={
   /*（环岛）状态判定计数*/ 
  {FALSE},  
   /*(直道）（环岛）*/ 
  {FALSE},
     /*(直道）（环岛）*/ 
  {FALSE},
    /*图像处理范围*/
  /*上*/ 0, /*下*/ 59, /*左*/ 5, /*右*/ 74,
    /*直道行距*/   
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
//80*60标定
uint8 ui8_LineWidthWaiGua[60] = 
{
1,1,3,5,5,8,9,10,11,13,14,16,
19,21,23,25,27,29,31,33,36,38,40,42,
44,46,48,50,52,55,57,59,61,63,65,68,
70,71,72,74,75,76,77,77,77,77,77,77,
78,78,78,78,78,78,78,78,78,78,78,78
};
uint8 street_len_40; //中40线的直道长度
uint8 street_len_5; //中10线的直道长度
uint8 street_len_75; //中70线的直道长度
uint8 image_threshold= 96;
uint8 Image_threshold[3]={130,130,130};  //4块
uint8 Vistable_scale=0;
uint8 img_x=0;
uint8 img_y=0;
uint8 Small=0;//默认160*60
uint8 Change_time=0;
uint8 L_point=2;
uint8 R_point=78;



void Soft_Binarization(void)
{  

     dispose_D_to_B(mt9v03x_image[0],180);
}
/***图像初始化***/
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
  //权重设置

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
函数名：获取阈值
返回值：阈值
功能：大津法确定阈值
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
    uint8* data = image;  //指向像素数据的指针
    for (i =GrayScaleMIN; i < GrayScaleMAX; i++)
    {
        pixelCount[i] = 0;
        pixelPro[i] = 0;
    }
    
    uint32 gray_sum=0;
    //统计灰度级中每个像素在整幅图像中的个数  
    for (i = 0; i < height; i+=2)
    {
        for (j = 0; j < width; j+=4)
        {
          if(data[i * width + j]>=GrayScaleMAX) data[i * width + j]=GrayScaleMAX;
          else if(data[i * width + j]<=GrayScaleMIN) data[i * width + j]=GrayScaleMIN; 
          
            pixelCount[(int)data[i * width + j]]++;  //将当前的点的像素值作为计数数组的下标
            gray_sum+=(int)data[i * width + j];       //灰度值总和
        }
    }
                      
    //计算每个像素值的点在整幅图像中的比例  
  
    for (i = GrayScaleMIN; i < GrayScaleMAX; i++)
    {
        pixelPro[i] = (float)pixelCount[i] / pixelSum;
        
    }

    //遍历灰度级[0,255]  
    float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;
    
     
        w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
        for (j = GrayScaleMIN; j < GrayScaleMAX; j++)         
        {
            
                w0 += pixelPro[j];  //背景部分每个灰度值的像素点所占比例之和   即背景部分的比例
                u0tmp += j * pixelPro[j];  //背景部分 每个灰度值的点的比例 *灰度值 
           
               w1=1-w0;
               u1tmp=gray_sum/pixelSum-u0tmp;
        
                u0 = u0tmp / w0;              //背景平均灰度
                u1 = u1tmp / w1;              //前景平均灰度
                u = u0tmp + u1tmp;            //全局平均灰度
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
函数名：图像二值化
功能：根据给定阈值二值化
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


/***主函数处理***/
void ConstructImage (void) {
  //Soft_Binarization(); // 图像压缩Zip_Image之后，二值化是不需要的
  Ladder();
  FitRoad();//还没有考虑环岛
  Get_len();
  GetReverseVisualRange();//获取可视距离
}
void Ladder (void) {
  uint8 ui8_LF[SIZE_HRE] = {0}; //记录有无计算过，处理过了赋值为1，没有处理则为0
  uint8 ui8_RF[SIZE_HRE] = {0};
  
  L_Move.ui8_ImageX     = DI.ui8_DisposeScopeLeft;
  L_Move.ui8_ImageY     = DI.ui8_DisposeScopeDown;
  L_Move.ui8_MaxY       = DI.ui8_DisposeScopeDown;
  L_Move.ui8_AllMaxY    = DI.ui8_DisposeScopeDown;
  
  R_Move.ui8_ImageX     = DI.ui8_DisposeScopeRight;
  R_Move.ui8_ImageY     = DI.ui8_DisposeScopeDown;
  R_Move.ui8_MaxY       = DI.ui8_DisposeScopeDown;
  R_Move.ui8_AllMaxY    = DI.ui8_DisposeScopeDown;
  
  //左点爬梯
  while (LeftPointLadder(ui8_LF) 
         && L_Move.ui8_ImageY > DI.ui8_DisposeScopeUp
           && L_Move.ui8_ImageX < DI.ui8_DisposeScopeRight) {
    if (L_Move.ui8_ImageX < MID_POINT && L_Move.ui8_MaxY > L_Move.ui8_ImageY) {
      L_Move.ui8_MaxY = L_Move.ui8_ImageY;
    }
  }
    
  //右点爬梯
  while (RightPointLadder(ui8_RF)
         && R_Move.ui8_ImageY > DI.ui8_DisposeScopeUp
           && R_Move.ui8_ImageX > DI.ui8_DisposeScopeLeft) {
    if (R_Move.ui8_ImageX > MID_POINT && R_Move.ui8_MaxY > R_Move.ui8_ImageY) {
      R_Move.ui8_MaxY = R_Move.ui8_ImageY;
    }
  }
  //中值求取起点
    if (L_Move.ui8_MaxY < R_Move.ui8_MaxY) {
    DI.ui8_ScanDirection =  Lstart;
  } else if (L_Move.ui8_MaxY > R_Move.ui8_MaxY) {
    DI.ui8_ScanDirection =  Rstart;
  } else {
    DI.ui8_ScanDirection =  Mstart;
  }

}

/************************************************************************
函数名：左点爬梯
功能：左点记录边界
返回值：能否继续移动
************************************************************************/
uint8 LeftPointLadder (uint8* ui8p_LF) {
  if (!DI.ui8_ImageArray[L_Move.ui8_ImageY][L_Move.ui8_ImageX])                                //黑点进入白区
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
  
  else if (DI.ui8_ImageArray[L_Move.ui8_ImageY - 1][L_Move.ui8_ImageX])                     //向上还是白区
  {
        if (L_Move.ui8_ImageY == DI.ui8_DisposeScopeDown 
            && DI.ui8_LPoint[L_Move.ui8_ImageY] - DI.ui8_DisposeScopeLeft > MID_POINT >> 2
            && DI.ui8_LPoint[L_Move.ui8_ImageY] - L_Move.ui8_ImageX > MID_POINT >> 2) //和上一帧的图像进行对比
        {
            L_Move.ui8_ImageX = (DI.ui8_LPoint[L_Move.ui8_ImageY] + L_Move.ui8_ImageX) / 2;//左下角出现噪点，根据上次左点比较跳变
        }
        else 
        {
          if (!ui8p_LF[L_Move.ui8_ImageY]) 
          {
            DI.ui8_LPoint[L_Move.ui8_ImageY] = L_Move.ui8_ImageX;//找到并记录！！！
            L_Move.ui8_AllMaxY = L_Move.ui8_ImageY;
            ui8p_LF[L_Move.ui8_ImageY] = 1;
          }
            L_Move.ui8_ImageY --;
        }
    return TRUE;
  }
  
  else if (DI.ui8_ImageArray[L_Move.ui8_ImageY][L_Move.ui8_ImageX + 1])                 //向上是黑则向右
 {
        L_Move.ui8_ImageX ++;
        return TRUE;
  }
  
  else if (L_Move.ui8_ImageY < DI.ui8_DisposeScopeDown                                  //向上找不到白点，且向右找不到白点，则返回找
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
函数名：右点爬梯
功能：右点记录边界
返回值：能否继续移动
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
函数名：拟合赛道
功能：调整出可行进路线   //注意：编译要用有符号char类型
************************************************************************/
void FitRoad (void) {
  /*横向边界************************************************************/
  int8  i8_UpLpX = - 1;
  uint8 ui8_UpLpY;
  int8  i8_EndLpX = - 1;
  uint8 ui8_EndLpY;
  
  int8  i8_UpRpX = - 1;
  uint8 ui8_UpRpY;
  int8  i8_EndRpX = - 1;
  uint8 ui8_EndRpY;
   
  
  if (DI.ui8_ScanDirection == Rstart) {//右拐补左线
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
      //找到两个拐点连起来，继续寻找拐点
        Fit(i8_UpLpX, i8_EndLpX, ui8_UpLpY, ui8_EndLpY);
        i8_UpLpX = - 1;
        i8_EndLpX = - 1;
      }
    }
  } else if (DI.ui8_ScanDirection == Lstart) {//左拐补右线
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
函数名：拟合
功能：拟合赛道调整函数
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
函数名：变换
功能：将白点变为黑点
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
函数名：获取反向可视距离
功能：根据中值处理计算出反向可视距离
返回值：反向可视距离（可确定小S、直道）
************************************************************************/
void GetReverseVisualRange (void) {
  //扫描统计
  uint16 ui16_SumY = 0;
  //起始点X
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
  }//留出十条竖线扫描
  
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
    //平均值为可视距离
    Vistable_scale = ui16_SumY / 20;
  
  
  if (DI.ui8_MinH <Vistable_scale) {
    DI.ui8_MinH =Vistable_scale;
    DI.i8_MinHX = MID_POINT;
  }
}
/************************************************************************
函数名：Get_len()
功能：获取可视距离和圆环补线点
返回值：len
***********************************************************************/
void Get_len(){
  for( img_y=50;img_y>1;img_y--){
    if(DI.ui8_ImageArray[img_y][40]==0 && DI.ui8_ImageArray[img_y-1][40]==0){
      break;
    }
  }
  //Vistable_scale=img_y;
   street_len_40=59-img_y;//道路中白色的长度
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
//显示数据页
uint8 ui8_Page = 0;

/************************************************************************
函数名：测量路宽
功能：根据可视距离确定路宽
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
//*标定

//void Display_ImageData(void)
//{
//    //显示数据调整
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
/**找边界点***/
void Seek_point(uint8 Y){
  //uint8 x1=0,x2=0,Bx3=0,Bx4=0,Wx3=0,Wx4=0;
  uint8 x1=0,x2=0,Bx3=0,Bx4=0;
  //uint8 Wlength=0,WMax_length=0;   //白色区域宽度
  uint8 Blength=0,BMax_length=0;   //黑色区域宽度
  Change_time=0;
  L_point=2;
  R_point=78;
  //遍历所取行
  while(x1<79){
      if(!DI.ui8_ImageArray[Y][x1]){   //第一点是黑色,首先开始黑色向白色移动
          x2=Seek_Write_point(x1,Y);
          Blength=x2-x1; 
          if(Blength>BMax_length){   //记录最大长度,并记录坐标
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
          if(Blength>BMax_length){   //记录最大长度,并记录坐标
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
    
    
        
      
     
//黑色向白色,返回白色点X2
uint8 Seek_Write_point(uint8 x1,uint8 Y){
  for(img_x=x1;img_x<=78;img_x++){
    if(DI.ui8_ImageArray[Y][img_x] && DI.ui8_ImageArray[Y][img_x+1]){
       Change_time++;                           //每次黑白跳变次数+1
       return img_x;
     }
    }
       return 79;
  }
//白色向黑色,返回黑点X2
uint8 Seek_Black_point(uint8 x1,uint8 Y){
  for(img_x=x1;img_x<=78;img_x++){
    if(!DI.ui8_ImageArray[Y][img_x] && !DI.ui8_ImageArray[Y][img_x+1]){
       Change_time++;                         //每次黑白跳变次数+1
       return img_x;
     }
  }
    return 79;
}
