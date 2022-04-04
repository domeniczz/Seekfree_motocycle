#include "select_median.h"
#include "stdlib.h"
//ͼ����ṹ������
extern Dispose_Image DI;
//��ű�־����
int poserror=0;
uint16  COUNTTS=0; //������
uint16 Goal_Speed=60;
//uint16 Base_Speed=240;
uint16 Add_speed=130;
extern float Distance;
extern uint8 Record_Dis;
extern uint8 have_ring;
extern uint8 street_len_45; 
extern uint8 street_len_5; //��10�ߵ�ֱ������
extern uint8 street_len_75; //��70�ߵ�ֱ������
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
extern LadderMovePoint         L_Move;  //�������������㷨���
extern LadderMovePoint         R_Move;  //�������������㷨�ҵ�
extern uint8 CHALU_count;
extern uint8 have_podao;
int poserror_array[4]={0};
//Ԫ�ش�����
uint8 SC=0;   //��ǰԪ�ظ���
uint8 Special_Count=4;
//uint8 Special_type[12]={L_Big,R_Little,L_SANCHA,L_Little,RAMP,IN_PARK};//,IN_PARK};//Ԫ������
uint16 t=0;
//uint8 Special_type[12]={L_Big,R_Little,L_SANCHA,L_Little,RAMP,IN_PARK};//Ԫ������


extern uint8 Cross_num;
/************************************************************************
��������ͼ������
���ܣ�ͼ��������
************************************************************************/
void DisposeImage (void)
{
     ConstructImage();  //ͼ����
     DetermineScanLine();      //ȷ��ɨ����
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
   

     

//�������˲�
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

 
 



/*��ʼ����-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/

/*���ô���-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/************************************************************************
����������������
************************************************************************/
void NormalControl (void) {  
  DetermineWeight ();
  SelectMid();              //��ȡ��ʼ��ֵ
  DetermineMid();           //ȷ�������ֵ

}


/************************************************************************
��������ȷ�������ֵ
���ܣ����ݵ�·״������ֵ�仯ȷ����Ч��         //�ж��������ת���������д     oo
��������λ��
************************************************************************/
void DetermineMid (void) {
  double i32_Mid = 0;
  double d_SumWeight = 0;
  for (uint8 ui8_I = 0; ui8_I < 10; ui8_I ++) {
    DI.i16_FinallyMid[ui8_I] = (int) (DI.i16_Mid[ui8_I]
                               + HtoE * (DI.i16_Mid[ui8_I] - MID_POINT)
                                      * DI.ui8_ScanLineY[ui8_I] / DI.f_BaseY[ui8_I]);//��ֵ

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
/*���ô���-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/

/*�д���-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/************************************************************************
��������ȷ��Ȩ��
���ܣ������ٶȸı�Ȩ��     
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
��������ȷ��ɨ����
���ܣ����ݿ��Ӿ���ȷ��ɨ������ȷ��ɨ��������ȷ
************************************************************************/
double f_E_H=0;
 double d_Y =0;
void DetermineScanLine (void){
  //��ȷ���ھ��в���
 // if(Statu!=LRing && Statu!=RRing && !ChaLu_delay_flag1  ){
  if(59-street_len_5<Vistable_scale && street_len_5>street_len_75 )   DI.ui8_ScanLineY[9] =60-street_len_5;
  else if(59-street_len_75<Vistable_scale && street_len_75>street_len_5)    DI.ui8_ScanLineY[9] =60-street_len_75;
    else
  DI.ui8_ScanLineY[9] = Vistable_scale + 1; 
//}
//else
  DI.ui8_ScanLineY[9] = Vistable_scale + 1; 
  DI.ui8_ScanLineL[9] = DI.ui8_LPoint[DI.ui8_ScanLineY[9]];//��Զ����
  DI.ui8_ScanLineR[9] = DI.ui8_RPoint[DI.ui8_ScanLineY[9]];
  
  DI.ui8_ScanLineToL[9] = 
      (DI.ui8_ScanLineL[9] + DI.ui8_ScanLineR[9])/2;
  //·�����
 // DI.ui8_ScanLineWidth[9]= DI.ui8_ScanLineR[9]-DI.ui8_ScanLineL[9];
  
  DI.ui8_ScanLineToR[9] = DI.ui8_ScanLineToL[9];
  
  while (DI.ui8_ScanLineToL[9] > DI.ui8_DisposeScopeLeft //����߽�
         && (DI.ui8_ImageArray[DI.ui8_ScanLineY[9]]
             [DI.ui8_ScanLineToL[9] --]
             || DI.ui8_ImageArray[DI.ui8_ScanLineY[9]]
                [DI.ui8_ScanLineToL[9]])) {}
  
  if (!DI.ui8_ImageArray[DI.ui8_ScanLineY[9]][DI.ui8_ScanLineToL[9]]
      && DI.ui8_ScanLineToL[9] < DI.ui8_DisposeScopeRight) {
    DI.ui8_ScanLineToL[9] ++;//�ҵ��߽������һ��
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
//  //�ٴ���ȡ·��
//  //��һ��2�߶����ױ�
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
    d_Y = d_Y + (9 - i8_I) * f_E_H;//ʮ�ȷ� ÿ�ֿ��Ϊ1,2,3,4,5,6,7,8,9�ʷ�Ϊ45С��
    //�ɼ�ɨ����λ��
    DI.ui8_ScanLineY[i8_I] = (int) (d_Y + 0.5);
    
    //�ɼ�ɨ������߽磨���ߣ�
    DI.ui8_ScanLineL[i8_I] = DI.ui8_LPoint[DI.ui8_ScanLineY[i8_I]];
    //�ɼ�ɨ�����ұ߽磨���ߣ�
    DI.ui8_ScanLineR[i8_I] = DI.ui8_RPoint[DI.ui8_ScanLineY[i8_I]];
    //�ɼ�ɨ������߽�
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


