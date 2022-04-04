#include "select_median.h"
#include "stdlib.h"
//图像处理结构体声明
extern Dispose_Image DI;
//电磁标志声明
int poserror=0;
uint16  COUNTTS=0; //计数器
uint16 Goal_Speed=60;
//uint16 Base_Speed=240;
uint16 Add_speed=130;
extern float Distance;
extern uint8 Record_Dis;
extern uint8 have_ring;
extern uint8 street_len_45; 
extern uint8 street_len_5; //中10线的直道长度
extern uint8 street_len_75; //中70线的直道长度
/*extern uint8  L_Ring_delay_flag1;
extern uint8  L_Ring_delay_flag2;
extern uint8  L_Ring_delay_flag3;
extern uint8  L_Ring_delay_flag4;
extern uint8  L_Ring_delay_flag5;
extern uint8  L_Ring_delay_flag6;
extern uint8  R_Ring_delay_flag1;
extern uint8  R_Ring_delay_flag2;
extern uint8  R_Ring_delay_flag3;
extern uint8  R_Ring_delay_flag4;
extern uint8  R_Ring_delay_flag6;
extern uint8 ChaLu_delay_flag1;
extern uint8 ChaLu_delay_flag2;
extern uint8 ChaLu_delay_flag3;
extern uint8 Zebra_delay_flag2;*/
extern uint8  CHALU_TIME;

extern uint8  Statu;
extern float Delta_point;
extern float  Rate_error;
extern LadderMovePoint         L_Move;  //左右两点爬梯算法左点
extern LadderMovePoint         R_Move;  //左右两点爬梯算法右点
extern uint8 CHALU_count;
extern uint8 have_podao;
int poserror_array[4]={0};
//元素处理函数
uint8 SC=0;   //当前元素个数
uint8 Special_Count=4;
//uint8 Special_type[12]={L_Big,R_Little,L_SANCHA,L_Little,RAMP,IN_PARK};//,IN_PARK};//元素数组
uint16 t=0;
//uint8 Special_type[12]={L_Big,R_Little,L_SANCHA,L_Little,RAMP,IN_PARK};//元素数组


extern uint8 Cross_num;
/************************************************************************
函数名：图像处理函数
功能：图像处理流程
************************************************************************/
void DisposeImage (void)
{
     ConstructImage();  //图像构造
     DetermineScanLine();      //确定扫描行
     NormalControl ();
     Straight_Judge ();
     Ring_Judge();
     ChaLu_Judge();
     Ramp_Judge();
     if(CHALU_count==2) Zebra_Judge ();
    if(Statu==LRing) LRingTreatment();
    if(Statu==Lukou) ChaLuTreatment();
    if(Statu==Zebra) ZebraTreatment();
    if(Statu==Ramps)  {
        RampsTreatment();
        Goal_Speed=30;
    }
    else if(Statu==Zebra){
        Goal_Speed=25;
    }
    else
        Goal_Speed=50;

 }
   

     

//卡尔曼滤波
float kalmanFilter_A(float inData){
  static float prevData = 0;
  static float p=10, q=0.0001, r=0.005, kGain=0;
  //static float p=10, q=0.0001, r=0.005, kGain=0;
  p = p+q;
  kGain = p/(p+r);
  
  inData = prevData + kGain*(inData-prevData);
  p = (1-kGain)*p;
  
  prevData = inData;
  return inData;
} 

 
 



/*起始控制-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/

/*共用处理-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/************************************************************************
函数名：正常控制
************************************************************************/
void NormalControl (void) {  
  DetermineWeight ();
  SelectMid();              //提取初始中值
  DetermineMid();           //确定最后中值

}


/************************************************************************
函数名：确定最后中值
功能：根据道路状况和中值变化确定有效性         //判断阳光进行转电磁在这里写     oo
参数：行位置
************************************************************************/
void DetermineMid (void) {
  double i32_Mid = 0;
  double d_SumWeight = 0;
  for (uint8 ui8_I = 0; ui8_I < 10; ui8_I ++) {
    DI.i16_FinallyMid[ui8_I] = (int) (DI.i16_Mid[ui8_I]
                               + HtoE * (DI.i16_Mid[ui8_I] - MID_POINT)
                                      * DI.ui8_ScanLineY[ui8_I] / DI.f_BaseY[ui8_I]);//比值

    i32_Mid = i32_Mid+DI.i16_FinallyMid[ui8_I] * DI.f_BaseLineWeight[ui8_I];
                 
    d_SumWeight =d_SumWeight+ DI.f_BaseLineWeight[ui8_I] ;
  }
  
  i32_Mid =i32_Mid/ d_SumWeight;
  
//  if(IN_L==2){
//      if (i32_Mid < DI.ui8_DisposeScopeLeft ) {
//    i32_Mid = DI.ui8_DisposeScopeLeft ;
//  } 
// }
//  else if(IN_R==2){
//    if(i32_Mid > DI.ui8_DisposeScopeRight){
//    i32_Mid = DI.ui8_DisposeScopeRight;
//    }
//  }
    
  if (i32_Mid < DI.ui8_DisposeScopeLeft - 10) {
    i32_Mid = DI.ui8_DisposeScopeLeft - 10;
  } 
  else if (i32_Mid > DI.ui8_DisposeScopeRight + 10){
    i32_Mid = DI.ui8_DisposeScopeRight + 10;
  }
  
  poserror=(int)(i32_Mid-MID_POINT);
  
  for(int i=0;i<3;i++){
    poserror_array[i+1] = poserror_array[i];    
  }
  poserror_array[0] = poserror;
  
}
/*共用处理-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/

/*行处理-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/************************************************************************
函数名：确定权重
功能：根据速度改变权重     
************************************************************************/
void DetermineWeight (void) {
  double d_k_v = VtoLine * (V_Avg-180) + 1;
  if (d_k_v > 0) {
    double d_AddWeight = 1;
    for (uint8 ui8_I = 5; ui8_I < 10; ui8_I ++) {
      d_AddWeight = d_AddWeight*d_k_v;
      DI.f_LineWeight[ui8_I] = DI.f_BaseLineWeight[ui8_I] + d_AddWeight - 1;      
    }
  }
    else{
    for (uint8 ui8_I = 0; ui8_I < 10; ui8_I ++) {
      DI.f_LineWeight[ui8_I] = DI.f_BaseLineWeight[ui8_I] ;      
    }
    

    }
      
 //   DI.f_LineWeight[4] 
  
}

/************************************************************************
函数名：确定扫描行
功能：根据可视距离确定扫描行以确保扫描区域正确
************************************************************************/
double f_E_H=0;
 double d_Y =0;
void DetermineScanLine (void){
  //先确定第九行参数
 // if(Statu!=LRing && Statu!=RRing && !ChaLu_delay_flag1  ){
  if(59-street_len_5<Vistable_scale && street_len_5>street_len_75 )   DI.ui8_ScanLineY[9] =60-street_len_5;
  else if(59-street_len_75<Vistable_scale && street_len_75>street_len_5)    DI.ui8_ScanLineY[9] =60-street_len_75;
    else
  DI.ui8_ScanLineY[9] = Vistable_scale + 1; 
//}
//else
  DI.ui8_ScanLineY[9] = Vistable_scale + 1; 
  DI.ui8_ScanLineL[9] = DI.ui8_LPoint[DI.ui8_ScanLineY[9]];//由远及近
  DI.ui8_ScanLineR[9] = DI.ui8_RPoint[DI.ui8_ScanLineY[9]];
  
  DI.ui8_ScanLineToL[9] = 
      (DI.ui8_ScanLineL[9] + DI.ui8_ScanLineR[9])/2;
  //路宽计算
 // DI.ui8_ScanLineWidth[9]= DI.ui8_ScanLineR[9]-DI.ui8_ScanLineL[9];
  
  DI.ui8_ScanLineToR[9] = DI.ui8_ScanLineToL[9];
  
  while (DI.ui8_ScanLineToL[9] > DI.ui8_DisposeScopeLeft //找最边界
         && (DI.ui8_ImageArray[DI.ui8_ScanLineY[9]]
             [DI.ui8_ScanLineToL[9] --]
             || DI.ui8_ImageArray[DI.ui8_ScanLineY[9]]
                [DI.ui8_ScanLineToL[9]])) {}
  
  if (!DI.ui8_ImageArray[DI.ui8_ScanLineY[9]][DI.ui8_ScanLineToL[9]]
      && DI.ui8_ScanLineToL[9] < DI.ui8_DisposeScopeRight) {
    DI.ui8_ScanLineToL[9] ++;//找到边界便找下一行
  }
  
  while (DI.ui8_ScanLineToR[9] < DI.ui8_DisposeScopeRight 
         && (DI.ui8_ImageArray[DI.ui8_ScanLineY[9]]
             [DI.ui8_ScanLineToR[9] ++]
             || DI.ui8_ImageArray[DI.ui8_ScanLineY[9]]
                [DI.ui8_ScanLineToR[9]])) {}
  
  if (!DI.ui8_ImageArray[DI.ui8_ScanLineY[9]][DI.ui8_ScanLineToR[9]]
      && DI.ui8_ScanLineToR[9] > DI.ui8_DisposeScopeLeft) {
    DI.ui8_ScanLineToR[9] --;
  }
//  //再次求取路宽
//  //第一种2边都到白边
//  if(DI.ui8_ScanLineToR[9]<DI.ui8_DisposeScopeRight -3 && DI.ui8_ScanLineToL[9]>DI.ui8_DisposeScopeLeft+3
//     && (DI.ui8_ScanLineToR[9]-DI.ui8_RPoint[DI.ui8_ScanLineY[9]]>=3 ||  DI.ui8_LPoint[DI.ui8_ScanLineY[9]]-DI.ui8_ScanLineToL[9]>=3){
//        DI.ui8_ScanLineWidth[9]=DI.ui8_ScanLineToR[9]-DI.ui8_ScanLineToL[9];
//     }
//  else if(DI.ui8_ScanLineToR[9]<DI.ui8_DisposeScopeRight-3 && DI.ui8_ScanLineToL[9]>DI.ui8_DisposeScopeLeft+3
//          && (DI.ui8_ScanLineToR[9]-DI.ui8_RPoint[DI.ui8_ScanLineY[9]]<3 ||  DI.ui8_LPoint[DI.ui8_ScanLineY[9]]-DI.ui8_ScanLineToL[9]<3){
//            
//       
//  if(DI.ui8_ScanLineToR[9]>=DI.ui8_DisposeScopeRight -3 && DI.ui8_ScanLineToL[9]<= DI.ui8_DisposeScopeLeft+3){
    // DI.[9]=(uint8)(DI.ui8_LineWidth[DI.ui8_ScanLineY[9]]*Rate_error);
  //}

  
  uint8 ui8_LineWidth = DI.ui8_DisposeScopeDown - DI.ui8_ScanLineY[9];
   f_E_H = ui8_LineWidth / 45.0;
   d_Y = DI.ui8_ScanLineY[9];
  
  for (int8 i8_I = 8; i8_I >= 0; i8_I --) {
    d_Y = d_Y + (9 - i8_I) * f_E_H;//十等分 每分宽度为1,2,3,4,5,6,7,8,9故分为45小分
    //采集扫描行位置
    DI.ui8_ScanLineY[i8_I] = (int) (d_Y + 0.5);
    
    //采集扫描行左边界（补线）
    DI.ui8_ScanLineL[i8_I] = DI.ui8_LPoint[DI.ui8_ScanLineY[i8_I]];
    //采集扫描行右边界（补线）
    DI.ui8_ScanLineR[i8_I] = DI.ui8_RPoint[DI.ui8_ScanLineY[i8_I]];
    //采集扫描行最边界
    DI.ui8_ScanLineToL[i8_I] = 
      DI.ui8_ScanLineL[i8_I] + DI.ui8_ScanLineR[i8_I] >> 1;
    DI.ui8_ScanLineToR[i8_I] = DI.ui8_ScanLineToL[i8_I];
    
    while (DI.ui8_ScanLineToL[i8_I] > DI.ui8_DisposeScopeLeft 
           && (DI.ui8_ImageArray[DI.ui8_ScanLineY[i8_I]]
               [DI.ui8_ScanLineToL[i8_I] --]
               || DI.ui8_ImageArray[DI.ui8_ScanLineY[i8_I]]
                  [DI.ui8_ScanLineToL[i8_I]])) {}
    
    if (!DI.ui8_ImageArray[DI.ui8_ScanLineY[i8_I]][DI.ui8_ScanLineToL[i8_I]]
        && DI.ui8_ScanLineToL[i8_I] < DI.ui8_DisposeScopeRight) {
      DI.ui8_ScanLineToL[i8_I] ++;
    }
    
    while (DI.ui8_ScanLineToR[i8_I] < DI.ui8_DisposeScopeRight 
           && (DI.ui8_ImageArray[DI.ui8_ScanLineY[i8_I]]
               [DI.ui8_ScanLineToR[i8_I] ++]
               || DI.ui8_ImageArray[DI.ui8_ScanLineY[i8_I]]
                  [DI.ui8_ScanLineToR[i8_I]])) {}
    
    if (!DI.ui8_ImageArray[DI.ui8_ScanLineY[i8_I]][DI.ui8_ScanLineToR[i8_I]]
        && DI.ui8_ScanLineToR[i8_I] > DI.ui8_DisposeScopeLeft) {
      DI.ui8_ScanLineToR[i8_I] --;
    }
  }
}


