  #include "mohuduoji.h"

MH      MHstruct;

MH      MHstructFastCar = 
{

    // {14.0, 18.4, 24.0, 39.6, 46.0, 55.2, 64.0 },//舵机P值表L
    // {14.0, 18.4, 24.0, 39.6, 46.0, 55.2, 64.0 },//舵机P值表R

//    {16.0, 23.0, 28.0, 32.0, 33.0, 34.0, 35.0},//舵机P值表L
//    {16.0, 23.0, 28.0, 32.0, 33.0, 34.0, 35.0},//舵机P值表R
//    {17.0, 18.0, 19.0, 21.0, 23.0, 26.0, 27.0},//舵机P值表L
//    {17.0, 19.0, 19.0, 21.0, 23.0, 26.0, 27.0},//舵机P值表R
    {11.0, 12.0, 13.0, 14.0, 16.0, 18.0, 20.0},//舵机P值表L
    {11.0, 12.0, 13.0, 14.0, 16.0, 18.0, 20.0},//舵机P值表R


  //模糊表|-*-纵轴：反向可视距离递增-*-|-*-横轴：中值偏差变化递增-*-|
   {
    {
      {
        //L-IN
        { 0, 1, 2, 3, },
        { 1, 2, 3, 4, },
        { 3, 4, 5, 6, },
        { 5, 6, 6, 6, }
      }  
    },
    
    {
      {
        //R-IN
//        { 1, 2, 3, 5, },
//        { 2, 3, 4, 5, },
//        { 4, 5, 6, 6, },
//        { 5, 6, 6, 6, }
        { 0, 1, 2, 3, },
        { 1, 2, 3, 4, },
        { 3, 4, 5, 6, },
        { 5, 6, 6, 6, }
      }  
    },
    
    {
      {
        //L-OUT
        { 0, 1, 2, 3, },
        { 1, 2, 3, 4, },
        { 3, 4, 5, 6, },
        { 5, 6, 6, 6, }   
      }  
    },
    
    {
      {
        //R-OUT
        { 0, 1, 2, 3, },
        { 1, 2, 3, 4, },
        { 3, 4, 5, 6, },
        { 5, 6, 6, 6, }
      }  
    }
   },
     
  //电机P值表
  { 120, 150, 170, 220, 320, 420, 520 },
  //电机I值表
  { 10, 16.625, 21.25, 32.5, 55, 77.5, 100 },
  //{ 10, 16.625, 21.25, 32.5, 55, 77.5, 100 }{ 50, 59.375, 68.75, 87.5, 125, 162.5, 200 },
  //模糊表|-*-纵轴：反向可视距离递增-*-|-*-横轴：脉冲偏差变化递增-*-|
  {
    {
      {
        //ADD-IN
        { 0, 1, 2, 3, },
        { 1, 2, 3, 4, },
        { 3, 4, 5, 6, },
        { 5, 6, 6, 6, }
      }  
    }, 
    
    {
      {
        //SUB-IN
        { 0, 1, 2, 4, },
        { 1, 3, 5, 6, },
        { 3, 5, 6, 6, },
        { 5, 6, 6, 6, }
      }  
    },
    
    {
      {
        //ADD-OUT
        { 0, 1, 2, 4, },
        { 1, 3, 5, 6, },
        { 3, 5, 6, 6, },
        { 5, 6, 6, 6, }
      }  
    },
    
    {
      {
        //SUB-OUT
        { 0, 1, 2, 3, },
        { 1, 2, 3, 4, },
        { 3, 4, 5, 6, },
        { 5, 6, 6, 6, }
      }  
    },
  }
};
/************************************************************************
函数名：模糊表初始化
************************************************************************/
void InitMH (void) 
{
    MHstruct = MHstructFastCar;
    MHstruct.f_SizeOfViewE = 40;
    MHstruct.f_SizeOfViewH = 50;
    MHstruct.f_SizeOfPulseE = 50.0;
    MHstruct.i16_ViewH = H_Min;
}

/************************************************************************
函数名：获取舵机P值
功能：通过反向可视距离和中值偏差得出不同P值
参数：i32p_P------舵机P指针
      i16_ViewH---反向可视距离
      i16_ViewE---中值偏差
************************************************************************/
void DuoJi_GetP (float* i32p_P, int16 i16_ViewH, int16 i16_ViewE) 
{
  float P_approximation = 6.0 * abs(i16_ViewE) / 40 ;
  if(P_approximation>6)P_approximation=6;
  else if(P_approximation<0)P_approximation=0;

  int8 P1 = (int)P_approximation;

  if (P1 > P_approximation) 
  {
    P1 --;
  }

  int8 P2 = P1 + 1;
  
  if (i16_ViewE > 0) 
  {
    *i32p_P = (MHstruct.f_DuoJiP_TableL[P2] - MHstruct.f_DuoJiP_TableL[P1]) 
    * (P_approximation - P1) + MHstruct.f_DuoJiP_TableL[P1];
  } 
  else 
  {
    *i32p_P = (MHstruct.f_DuoJiP_TableR[P2] - MHstruct.f_DuoJiP_TableR[P1]) 
    * (P_approximation - P1) + MHstruct.f_DuoJiP_TableR[P1];
  }
  // *i32p_P=22.0;
  // PRINTF("\n%f,%f--%f--%f",P_approximation,MHstruct.f_DuoJiP_TableL[P1],*i32p_P,MHstruct.f_DuoJiP_TableL[P2]);
}

/************************************************************************
函数名：获取电机P值
功能：通过反向可视距离和脉冲偏差得出不同P值
参数：i16_ViewH----反向可视距离
      i16_PulseE---脉冲偏差
返回值：电机P值
************************************************************************/
void DianJi_GetPI (float* i32p_P, float* i32p_I, 
                   int16 i16_ViewH, int16 i16_PulseE) 
{
  
  MHstruct.ui8_IOLR = MHstruct.ui8_IO ? (i16_PulseE > 0 ? MH_DianJi_IA : MH_DianJi_IS) 
                                      : (i16_PulseE > 0 ? MH_DianJi_OA : MH_DianJi_OS);
  
  float VH = f_Get_H_approximation(i16_ViewH - H_Min);
  float VE = f_Get_E_approximation(i16_PulseE, MHstruct.f_SizeOfPulseE);
  
  int8 VH1 = (int) VH;

  if (VH1 > VH) 
  {
    VH --;
  }

  int8 VH2 = VH1 + 1;
  
  int8 VE1 = (int) VE;

  if (VE1 > VE) 
  {
    VE1 --;
  }

  int8 VE2 = VE1 + 1;
  
  float X2Y = 0;
  float X1Y = 0;
  float Y2X = 0;
  float Y1X = 0;
  
  if(VH1 > 3)
  {
    VH1 = 3;
  }
  
  if(VH2 > 3)
  {
    VH2 = 3;
  }
  
  if(VE1 > 3)
  {
    VE1 = 3;
  }
  
  if(VE2 > 3)
  {
    VE2 = 3;
  }
  
  X2Y = (MHstruct.mt_DianJi[MHstruct.ui8_IOAS].ui8_Table[VH1][VE2] 
         - MHstruct.mt_DianJi[MHstruct.ui8_IOAS].ui8_Table[VH1][VE1]) 
    * (VE - VE1) + MHstruct.mt_DianJi[MHstruct.ui8_IOAS].ui8_Table[VH1][VE1];
  X1Y = (MHstruct.mt_DianJi[MHstruct.ui8_IOAS].ui8_Table[VH2][VE2] 
         - MHstruct.mt_DianJi[MHstruct.ui8_IOAS].ui8_Table[VH2][VE1]) 
    * (VE - VE1) + MHstruct.mt_DianJi[MHstruct.ui8_IOAS].ui8_Table[VH2][VE1];
  Y2X = (MHstruct.mt_DianJi[MHstruct.ui8_IOAS].ui8_Table[VH2][VE1] 
         - MHstruct.mt_DianJi[MHstruct.ui8_IOAS].ui8_Table[VH1][VE1]) 
    * (VH - VH1) + MHstruct.mt_DianJi[MHstruct.ui8_IOAS].ui8_Table[VH1][VE1];
  Y1X = (MHstruct.mt_DianJi[MHstruct.ui8_IOAS].ui8_Table[VH2][VE2] 
         - MHstruct.mt_DianJi[MHstruct.ui8_IOAS].ui8_Table[VH1][VE2]) 
    * (VH - VH1) + MHstruct.mt_DianJi[MHstruct.ui8_IOAS].ui8_Table[VH1][VE2];
    
  float PI_approximation = (X2Y + X1Y + Y2X + Y1X) / 4.0;
  
  int8 PI1 = (int)PI_approximation;

  if (PI1 > PI_approximation) 
  {
    PI1 --;
  }

  int8 PI2 = PI1 + 1;
  *i32p_P = (MHstruct.f_DianJiP_Table[PI2] - MHstruct.f_DianJiP_Table[PI1]) 
    * (PI_approximation - PI1) + MHstruct.f_DianJiP_Table[PI1];
  
  *i32p_I = (MHstruct.f_DianJiI_Table[PI2] - MHstruct.f_DianJiI_Table[PI1]) 
    * (PI_approximation - PI1) + MHstruct.f_DianJiI_Table[PI1];
}

/************************************************************************
函数名：获取横轴似坐标
功能：获取get_p()函数所需变量
接口：无
调用：通过get_p()被动调用
************************************************************************/
float f_Get_H_approximation(int16 i16_ViewH) 
{
  float H_approximation;
  
  if (i16_ViewH < 0) 
  {
    i16_ViewH = 0;
  }
  
  H_approximation = i16_ViewH * 3 / MHstruct.f_SizeOfViewH;
  
  return H_approximation;
}

/************************************************************************
函数名：获取纵轴近似坐标
功能：获取get_p()函数所需变量
接口：无
调用：通过get_p()被动调用
************************************************************************/
float f_Get_E_approximation(int16 i16_E, float f_E_Size)
{
  float E_approximation;
  
  if(i16_E < 0)
  {
    i16_E = - i16_E;
  }
  
  E_approximation = i16_E * 3 / f_E_Size;
  
  return E_approximation;
}
