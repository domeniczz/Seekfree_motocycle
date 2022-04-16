#include "situation.h"
//������ʼ��-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
//�������������㷨���

extern LadderMovePoint         L_Move;
//�������������㷨�ҵ�
extern LadderMovePoint         R_Move;

//ͼ����ṹ������
extern Dispose_Image DI;

extern uint8 Run;
extern float Distance;
extern uint8 Record_Dis;
extern float SumAngle;      //�Ƕ�
extern uint8 Record_Angle; // �Ƕȼ�¼��־λ
//������ʼ��-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
//��״̬����
uint8 Statu=1;
 //��������
#define Big 0
#define Little 1
uint8  Open_Ring=1;
uint16  Times=0;
uint8   Time=0;
uint8  L_Ring_flag0=0;
uint8  L_Ring_flag1=0;
uint8  L_Ring_delay_flag1=0;
uint8  L_Ring_flag2=0;
uint8  L_Ring_delay_flag2=0;
uint8  L_Ring_flag3=0;
uint8  L_Ring_delay_flag3=0;
uint8  L_Ring_flag4=0;
uint8  L_Ring_delay_flag4=0;
uint8  L_Ring_flag5=0;
uint8  L_Ring_delay_flag5=0;
uint8  L_Ring_flag6=0;
uint8  L_Ring_delay_flag6=0;
uint8  IN_LRing=0;

uint8  R_Ring_flag1=0;
uint8  R_Ring_delay_flag1=0;
uint8  R_Ring_flag2=0;
uint8  R_Ring_delay_flag2=0;
uint8  R_Ring_flag3=0;
uint8  R_Ring_delay_flag3=0;
uint8  R_Ring_flag4=0;
uint8  R_Ring_delay_flag4=0;
uint8  R_Ring_flag5=0;
uint8  R_Ring_delay_flag5=0;
uint8  R_Ring_flag6=0;
uint8  R_Ring_delay_flag6=0;
uint8 IN_RRing=1;
 uint8 Ring_flag=0;
 uint8 have_ring=0;
//ֱ������
uint8 ui8_CacuLineToL[10]={0};
uint8 ui8_CacuLineToR[10]={0};
int S_Left=0;   //���׼��
int S_Right=0;  //�ұ�׼��
float k_r=0;   //����б��
float k_l=0;   //����б��
//��·����
uint8 CHALU_count=0;   //  ��·����
uint8 ChaLu_flag0=0;
uint8 ChaLu_delay_flag0=0;
uint8 ChaLu_flag1=0;
uint8 ChaLu_delay_flag1=0;
uint8 ChaLu_flag2=0;
uint8 ChaLu_delay_flag2=0;
uint8 ChaLu_flag3=0;
uint8 ChaLu_delay_flag3=0;
//���⴦��
uint8 Zebra_delay_flag1=0;
uint8 Zebra_flag1=0;
uint8 Zebra_delay_flag2=0;
uint8 Zebra_flag2=0;
uint8 Zerbra_Dir=0;  // Ĭ����
//�µ�����
uint8 Podao_flag1=0;
uint8 Podao_delay_flag1=0;
uint8 Podao_flag2=0;
uint8 Podao_delay_flag2=0;
uint8 Podao_flag3=0;
uint8 Podao_delay_flag3=0;
uint8 Podao_flag4=0;
uint8 Podao_delay_flag4=0;
uint8 have_podao=0;
//ʮ�ֱ���
uint8 Cross_flag0 = 0;
uint8 Cross_delay_flag0 = 0;
uint8 Cross_flag1=0;
uint8 Cross_delay_flag1=0;
uint8 Cross_flag2=0;
uint8 Cross_delay_flag2=0;

//������
uint8 line_length = 32;
/*
***********************************************************************
����������ȡ��ʼ��ֵ
���ܣ��жϵ�·���ͷֱ���õ���ʼ��ֵ
��������λ��
***********************************************************************
***********************************************************************
************************************************************************/
void SelectMid(void)
{
  NormalTreatment();
}
/*
//uint8  MAX(int a, int b){
//  if(a>b) return a;
//  else return b;
//}
***��Ŷ�ȡ����**
*/
//ֱ���ж�
void  Straight_Judge (void)
{
  S_Left=0;
  S_Right=0;
   k_l=(DI.ui8_ScanLineY[1]- DI.ui8_ScanLineY[5])*1.0/(DI.ui8_ScanLineToL[5]-DI.ui8_ScanLineToL[1]);
   k_r=(DI.ui8_ScanLineY[1]- DI.ui8_ScanLineY[5])*1.0/(DI.ui8_ScanLineToR[1]-DI.ui8_ScanLineToR[5]);
  for(uint8 ui8_I=2;ui8_I<=7;ui8_I++){
     ui8_CacuLineToL[ui8_I]=(uint8)(DI.ui8_ScanLineToL[1]+(DI.ui8_ScanLineY[1]- DI.ui8_ScanLineY[ui8_I])/k_l); //���ۼ���ֱ����߽�
     ui8_CacuLineToR[ui8_I]=(uint8)(DI.ui8_ScanLineToR[1]-(DI.ui8_ScanLineY[1]- DI.ui8_ScanLineY[ui8_I])/k_r);
     S_Left+=(DI.ui8_ScanLineToL[ui8_I]-ui8_CacuLineToL[ui8_I]); //������ʵ�ʵ�����ۼƣ��ܴ��������
     S_Right+=(DI.ui8_ScanLineToR[ui8_I]-ui8_CacuLineToR[ui8_I]);
  }
}

/*
*Բ���ж�*
//  uint8 Ring_Judge (void)
//{
//    //���Բ���ж�
//  if(!DI.ui8_ImageArray[DI.ui8_DisposeScopeDown-5][DI.ui8_DisposeScopeLeft+1] && !DI.ui8_ImageArray[DI.ui8_DisposeScopeDown-10][DI.ui8_DisposeScopeLeft+1]  //ǰ10�к�ɫ
//      &&DI.ui8_ImageArray[DI.ui8_DisposeScopeDown-30][DI.ui8_DisposeScopeLeft+3] && DI.ui8_ImageArray[DI.ui8_DisposeScopeDown-32][DI.ui8_DisposeScopeLeft+3]  //����ȫ�ǰ�ɫ
//       && DI.ui8_ImageArray[DI.ui8_DisposeScopeDown-34][DI.ui8_DisposeScopeLeft+3] && DI.ui8_ImageArray[DI.ui8_DisposeScopeDown-36][DI.ui8_DisposeScopeLeft+3]
//        && DI.ui8_ImageArray[DI.ui8_DisposeScopeDown-38][DI.ui8_DisposeScopeLeft+3] && DI.ui8_ImageArray[DI.ui8_DisposeScopeDown-40][DI.ui8_DisposeScopeLeft+3]
//         && !DI.ui8_ImageArray[DI.ui8_DisposeScopeDown-35][DI.ui8_DisposeScopeRight-3] && !DI.ui8_ImageArray[DI.ui8_DisposeScopeDown-40][DI.ui8_DisposeScopeRight-3]
//             && S_Right<=20 && S_Right>=0 &&street_len_40>=55 && Open_Ring)
//    {
//      Statu=LRing;
//      L_Ring_flag1=1;
//    }
//  //��Բ���ж�
////    if(!DI.ui8_ImageArray[DI.ui8_DisposeScopeDown-5][DI.ui8_DisposeScopeRight-1] && !DI.ui8_ImageArray[DI.ui8_DisposeScopeDown-10][DI.ui8_DisposeScopeRight-1]
////      &&DI.ui8_ImageArray[DI.ui8_DisposeScopeDown-30][DI.ui8_DisposeScopeRight-3] && DI.ui8_ImageArray[DI.ui8_DisposeScopeDown-32][DI.ui8_DisposeScopeRight-3]
////       && DI.ui8_ImageArray[DI.ui8_DisposeScopeDown-34][DI.ui8_DisposeScopeRight-3] && DI.ui8_ImageArray[DI.ui8_DisposeScopeDown-36][DI.ui8_DisposeScopeRight-3]
////        && DI.ui8_ImageArray[DI.ui8_DisposeScopeDown-38][DI.ui8_DisposeScopeRight-3] && DI.ui8_ImageArray[DI.ui8_DisposeScopeDown-40][DI.ui8_DisposeScopeRight-3]
////         && !DI.ui8_ImageArray[DI.ui8_DisposeScopeDown-35][DI.ui8_DisposeScopeLeft+3] && !DI.ui8_ImageArray[DI.ui8_DisposeScopeDown-40][DI.ui8_DisposeScopeLeft+3]
////             && S_Left>=-20 && S_Left<=5 &&street_len_40>=55 &&  Open_Ring)
////    {
////      Statu=RRing;
////      R_Ring_flag1=1;
////     // BeeOn;
////    }
//}
 * */
//Բ���ж�
  uint8 Ring_Judge (void)
{
      if(DI.ui8_ImageArray[DI.ui8_DisposeScopeDown-2][DI.ui8_DisposeScopeLeft+5] && DI.ui8_ImageArray[DI.ui8_DisposeScopeDown-4][DI.ui8_DisposeScopeLeft+5]
         &&DI.ui8_ImageArray[DI.ui8_DisposeScopeDown-6][DI.ui8_DisposeScopeLeft+5] && DI.ui8_ImageArray[DI.ui8_DisposeScopeDown-8][DI.ui8_DisposeScopeLeft+5]
           && DI.ui8_ImageArray[DI.ui8_DisposeScopeDown-10][DI.ui8_DisposeScopeLeft+5] && DI.ui8_ImageArray[DI.ui8_DisposeScopeDown-12][DI.ui8_DisposeScopeLeft+5]
              && DI.ui8_ImageArray[DI.ui8_DisposeScopeDown-14][DI.ui8_DisposeScopeLeft+5] && DI.ui8_ImageArray[DI.ui8_DisposeScopeDown-16][DI.ui8_DisposeScopeLeft+5]
                &&  DI.ui8_ImageArray[DI.ui8_DisposeScopeDown-18][DI.ui8_DisposeScopeLeft+5] && DI.ui8_ImageArray[DI.ui8_DisposeScopeDown-20][DI.ui8_DisposeScopeLeft+5]
                 &&   DI.ui8_ImageArray[DI.ui8_DisposeScopeDown-22][DI.ui8_DisposeScopeLeft+5] && DI.ui8_ImageArray[DI.ui8_DisposeScopeDown-24][DI.ui8_DisposeScopeLeft+5]
                   &&  DI.ui8_ImageArray[DI.ui8_DisposeScopeDown-26][DI.ui8_DisposeScopeLeft+5] && DI.ui8_ImageArray[DI.ui8_DisposeScopeDown-28][DI.ui8_DisposeScopeLeft+5]
                    &&  !DI.ui8_ImageArray[DI.ui8_DisposeScopeDown-40][DI.ui8_DisposeScopeLeft+5] && !DI.ui8_ImageArray[DI.ui8_DisposeScopeDown-42][DI.ui8_DisposeScopeLeft+5]
                       &&  !DI.ui8_ImageArray[DI.ui8_DisposeScopeDown-44][DI.ui8_DisposeScopeLeft+5] && !DI.ui8_ImageArray[DI.ui8_DisposeScopeDown-46][DI.ui8_DisposeScopeLeft+5]
                         && DI.ui8_ScanLineToR[2]<78 && DI.ui8_ScanLineToR[3]<78 && DI.ui8_ScanLineToR[4]<78  && DI.ui8_ScanLineToR[5]<78 && DI.ui8_ScanLineToR[6]<78 && DI.ui8_ScanLineToR[7]<78
                && S_Right<=10 && S_Right>=0  && S_Left<=-10 &&street_len_40>=50
                   && Open_Ring && Statu==Normals)
        {
          BeeOn;
          Statu=LRing;
          L_Ring_flag1=1;
        }
}
 uint16 Write_Point=0;
//��·�ж�
  //}
  uint8 ChaLu_Judge(void){
               uint8 Start_y1=59-street_len_40;
               uint8 Start_x1=40;
               uint8 len_Lukou,len_Lukou_pre=0;
               uint8 X1,X2=0;
               Write_Point=0;
               if(street_len_40<=45 && Statu==Normals){  //���Ӿ���+״̬����
               for(uint8 Y=Start_y1-3;Y>=Start_y1-8;Y--){   //��5�г�������
                       for (uint8 X=0;X<=DI.ui8_DisposeScopeRight;X++){
                           if(!DI.ui8_ImageArray[Y][X] && !DI.ui8_ImageArray[Y][X+1]){   //��ɫ����
                               X1=X;
                               break;
                           }
                           else{
                               if(X==DI.ui8_DisposeScopeRight-3)  return 0;
                           }
                           }
                       for (uint8 X=X1;X<=DI.ui8_DisposeScopeRight;X++){               //��ɫ����
                           if(DI.ui8_ImageArray[Y][X] && DI.ui8_ImageArray[Y][X+1]){
                               X2=X;
                               break;
                           }
                           else{
                               if(X==DI.ui8_DisposeScopeRight-3)  return 0;
                           }
                           }
                       len_Lukou=X2-X1;
                       if(len_Lukou<=len_Lukou_pre) return 0;       //������������

                       }
                     //������15�а׵���
                       for(uint8 Y=Start_y1;Y<=Start_y1+15;Y++){   //��15��
                           for (uint8 X=0;X<=DI.ui8_DisposeScopeRight;X=X+2){
                               if(!DI.ui8_ImageArray[Y][X]){
                                   Write_Point++;
                               }
                             }
                            }
                       if(Write_Point>100) return 0;
                       //��������Ǻ�ɫ
                       for(uint8 Y=57-street_len_40;Y>DI.ui8_DisposeScopeUp;Y--){
                         if(DI.ui8_ImageArray[Y][40]){
                           return 0;
                         }
                         else{
                           if(Y==DI.ui8_DisposeScopeUp+3){
                             CHALU_count++;
                             Statu=Lukou;
                             ChaLu_flag0=1;
                             BeeOn;return 1;
                             break;
                          }
                         }
     }
                           }
                   }

    /*
                   }
                 Seek_point(Start_y-1);
                 if(Change_time>2){
                   Seek_point(Start_y-2);
                    if(Change_time>2){
                      Seek_point(Start_y-3);
                      if(Change_time>=2){
                      if(
                         DI.ui8_ImageArray[20][5] && DI.ui8_ImageArray[20][75]
                        && DI.ui8_ImageArray[15][5] && DI.ui8_ImageArray[15][75]
//                         && DI.ui8_ImageArray[Start_y+3][5] && DI.ui8_ImageArray[Start_y+3][75]
//                         && DI.ui8_ImageArray[Start_y+4][5] && DI.ui8_ImageArray[Start_y+4][75]
//                           && DI.ui8_ImageArray[Start_y+5][5] && DI.ui8_ImageArray[Start_y+5][75]
  //                              && !DI.ui8_ImageArray[56][4] && !DI.ui8_ImageArray[56][78]
  //                                 && !DI.ui8_ImageArray[57][3] && !DI.ui8_ImageArray[57][78]
  //                                    && !DI.ui8_ImageArray[58][2] && !DI.ui8_ImageArray[58][78]
  //                              && !DI.ui8_ImageArray[42][2] && !DI.ui8_ImageArray[42][78]
  //                                && !DI.ui8_ImageArray[44][2] && !DI.ui8_ImageArray[44][78]
  //                           && DI.ui8_ScanLineToL[6]<DI.ui8_ScanLineL[6]  && DI.ui8_ScanLineToR[6]>DI.ui8_ScanLineR[6]
  //                           && DI.ui8_ScanLineToL[8]<DI.ui8_ScanLineL[8]  && DI.ui8_ScanLineToR[8]>DI.ui8_ScanLineR[8]
                            // && S_Left>0 && S_Right<0
  //                          && !DI.ui8_ImageArray[44][2] && !DI.ui8_ImageArray[44][78]
  //                              && !DI.ui8_ImageArray[46][2] && !DI.ui8_ImageArray[46][78]
  //                              && !DI.ui8_ImageArray[42][2] && !DI.ui8_ImageArray[42][78]
  //                                && !DI.ui8_ImageArray[44][2] && !DI.ui8_ImageArray[44][78]
                                  &&   street_len_40<=45 &&
                                     Statu==Normals
                                      ){
                                      for(uint8 Y=57-street_len_40;Y>DI.ui8_DisposeScopeUp;Y--){
                                        if(DI.ui8_ImageArray[Y][40]){
                                          break;
                                        }
                                        else{
                                          if(Y==DI.ui8_DisposeScopeUp+3){
                                            Statu=Lukou;
                                            //Chalu_flag=1;
                                            ChaLu_flag0=1;
                                         //   Record_Angle=1;
                                            BeeOn;return 1;
                                            break;
                                         }
                                        }
                    }
                  }
                 }
               }
             }
             return 0;
  }*/


//---------------------------------ƥ���˲�-��·�ж��봦��---------------------------------------------
//������ͺ���
/*
//x1<x2,y1<y2�������
void Line_sum(uint8 x1,uint8 x2,uint8 y1,uint8 y2,float line_sum[]){
  float sum_max = 1;
  float sum0 = 0;
  for(int8 i = x1;i<x2;i++){
    float sum = 0;
    for(int8 j = y1;j<y2;j++){
      sum = sum + (DI.ui8_ImageArray[i][j]+1)%2;
    }
    if(i==x1) sum0 = sum;
    if(sum>sum_max) sum_max = sum;
    line_sum[i-x1] = (sum-sum0)/sum_max;//ȥ��ֱ�� ,��һ��   
  }
}
//���
float conv(float model[],float test[]){
 
  float conv_sum = 0;
  for(int i = 0;i<line_length;i++){
    conv_sum = conv_sum + model[i]*test[line_length-i-1];
  }
  return conv_sum;
}
//��·�ж�
uint8 Chalu_num = 0; //Ϊ1,�������·��Ϊ2�������·
uint8 Cross_num = 0;
float left = 0  ;
float right = 0 ;
uint16 match_threshold = 170;
float left_A[3]={0};
float right_A[3]={0};
uint8 ChaLu_Judge(void){
  float model[32] = {0.0, 1.0, 1.0, 2.0, 3.0, 3.0, 4.0, 4.0, 5.0, 5.0, 6.0, 6.0, 7.0, 8.0, 8.0, 9.0, 10.0, 10.0, 11.0, 11.0, 12.0, 12.0, 13.0, 14.0, 14.0, 14.0, 13.0, 10.0, 8.0, 4.0, 1.0, 0.0};
  float left_sum[32] = {0};
  float right_sum[32] = {0};
  Line_sum(23,56,1,30,left_sum);
  Line_sum(23,56,50,79,right_sum);
  for(int i = 2;i>0;i--){
    left_A[i] = left_A[i-1];
    right_A[i] = right_A[i-1];
  }
  left = conv(model,left_sum);
  right = conv(model,right_sum);
  left_A[0] = left;
  right_A[0] = right;
  if(left+right>200){//���
        uint8 Start_y=59-street_len_40;
        for(uint8 Y=57-street_len_40;Y>DI.ui8_DisposeScopeUp;Y--){
          if(DI.ui8_ImageArray[Y][40]){
            break;
          }
          else{
            if(Y==DI.ui8_DisposeScopeUp+2){
                Statu = Lukou;
                ChaLu_flag1 = 1;
                Chalu_num++;
                return 1;
              BeeOn;
           }
  }
  }
  }
  else if(left>=0 && right>30 && street_len_40>40 && street_len_40<50){//���
      uint8 Start_y=59-street_len_40;
      for(uint8 Y=57-street_len_40;Y>DI.ui8_DisposeScopeUp;Y--){
        if(DI.ui8_ImageArray[Y][40]){
          break;
        }
        else{
          if(Y==DI.ui8_DisposeScopeUp+2){
              Statu = Lukou;
              ChaLu_flag1 = 1;
              Chalu_num++;
              return 1;
              BeeOn;
         }
        }
     }
  }
  else if(right>=0&&left>30&& street_len_40>40&& street_len_40<50 ){//�ұ� && street_len_40>40
      uint8 Start_y=59-street_len_40;
      for(uint8 Y=57-street_len_40;Y>DI.ui8_DisposeScopeUp;Y--){
        if(DI.ui8_ImageArray[Y][40]){
          break;
        }
        else{
          if(Y==DI.ui8_DisposeScopeUp+2){
              Statu = Lukou;
              ChaLu_flag1 = 1;
              Chalu_num++;
              return 1;
              BeeOn;
         }
        }
     }
  }
   else if(right<=-170 && left>100 && street_len_40>50&&poserror>-9){//�ұ� && street_len_40>40
       uint8 Start_y=59-street_len_40;
       for(uint8 Y=57-street_len_40;Y>DI.ui8_DisposeScopeUp;Y--){
         if(DI.ui8_ImageArray[Y][40]){
           break;
         }
         else{
           if(Y==DI.ui8_DisposeScopeUp+2){
               Statu = Lukou;
               ChaLu_flag1 = 1;
               Chalu_num++;
               return 1;
               BeeOn;
          }
         }
      }
  }
  else if(DI.ui8_ImageArray[59][3] && DI.ui8_ImageArray[59][76] &&
          DI.ui8_ImageArray[54][3] && DI.ui8_ImageArray[54][76] && 
            DI.ui8_ImageArray[49][3] && DI.ui8_ImageArray[49][76] && 
              DI.ui8_ImageArray[44][3] && DI.ui8_ImageArray[44][76] &&  Special_type[SC]==Crosses&& poserror>-8){
              Statu = Cross;
              Cross_flag0 = 1;
              Cross_num++;
              return 1;
              }
                
                
  else{return 0;} 
  //else Statu = Normals; 
}    
//��ȥ��
*/
/*uint8 ChaLu_OutJudge(void){
  float model[32] = {0.0, 1.0, 1.0, 2.0, 3.0, 3.0, 4.0, 4.0, 5.0, 5.0, 6.0, 6.0, 7.0, 8.0, 8.0, 9.0, 10.0, 10.0, 11.0, 11.0, 12.0, 12.0, 13.0, 14.0, 14.0, 14.0, 13.0, 10.0, 8.0, 4.0, 1.0, 0.0};
  float left_sum[32] = {0};
  float right_sum[32] = {0};
  Line_sum(23,56,1,30,left_sum);
  Line_sum(23,56,50,79,right_sum);
  for(int i = 2;i>0;i--){
    left_A[i] = left_A[i-1];
    right_A[i] = right_A[i-1];
  }
  left = conv(model,left_sum);
  right = conv(model,right_sum);
  left_A[0] = left;
  right_A[0] = right;
  if(left+right>200){//���
    if(Special_type[SC]==L_SANCHA || Special_type[SC]==R_SANCHA ){
    return 1;
  }
  }
  else if(left>=0 && right>30 && street_len_40>40 && street_len_40<50){//���
     if(Special_type[SC]==L_SANCHA || Special_type[SC]==R_SANCHA ){
     return 1;
  }
  }
  else if(right>=0 && left>30 && street_len_40>40&& street_len_40<50){//�ұ�
     if(Special_type[SC]==L_SANCHA || Special_type[SC]==R_SANCHA ){    

     return 1;
 }
  }else{return 0;} 

}*/
/*
 * */
//*�µ��ж�*
uint8  Ramp_Judge(){
  if( DI.ui8_ScanDirection==Mstart && street_len_40>=58 && (DI.ui8_ScanLineR[9]-DI.ui8_ScanLineL[9])-DI.ui8_LineWidth[DI.ui8_ScanLineY[9]]>=10 
       && (DI.ui8_ScanLineR[9]-DI.ui8_ScanLineL[9])-DI.ui8_LineWidth[DI.ui8_ScanLineY[8]]>=14
         && (DI.ui8_ScanLineR[8]-DI.ui8_ScanLineL[8])-DI.ui8_LineWidth[DI.ui8_ScanLineY[7]]>=10
           && (DI.ui8_ScanLineR[7]-DI.ui8_ScanLineL[7])-DI.ui8_LineWidth[DI.ui8_ScanLineY[6]]>=8
            // && (DI.ui8_ScanLineR[4]-DI.ui8_ScanLineL[4])-DI.ui8_LineWidth[DI.ui8_ScanLineY[4]]>=6 
               &&  S_Left<=20 && S_Left>=-20 && S_Right<=20 && S_Right>=-20 ){
             for(uint8 Y=DI.ui8_DisposeScopeDown-10;Y>1;Y--){
               if(Y==2 && !DI.ui8_ImageArray[Y][3] && !DI.ui8_ImageArray[Y][76]){
                     BeeOn;
                    Statu=Ramps;
                    Podao_flag1=1;
                    Record_Dis=1;
                    return 1;
               }
               else if(DI.ui8_ImageArray[Y][3]&& DI.ui8_ImageArray[Y][76]){
                 break;
               }
             }
  }
  return 0;
}
/*
*ʮ���ж�*
void Cross_Judge(){//�м��������+�����߱�׼������
  if(DI.ui8_ImageArray[25][5] && DI.ui8_ImageArray[25][75] && 
      DI.ui8_ImageArray[27][5] && DI.ui8_ImageArray[27][75] && 
       DI.ui8_ImageArray[29][5] && DI.ui8_ImageArray[29][75] && 
        DI.ui8_ImageArray[31][5] && DI.ui8_ImageArray[31][75] && 
         DI.ui8_ImageArray[33][5] && DI.ui8_ImageArray[33][75] && 
           DI.ui8_ImageArray[35][5] && DI.ui8_ImageArray[35][75] &&  
             Statu!=LRing &&  Statu!=RRing && S_Left<=-80 && S_Right>=80 ){ 
                  Statu=Cross;
                   Small=1;
                   Record_Dis=1;
                     BeeOn;
                    }
    if(  Distance>=50&&
         Statu!=LRing &&  Statu!=RRing){
            Small=0;
         Statu=Normals;
         BeeOff;
       }
}
     */
//�������ж�
uint8 Zebra_Judge (void) {   
   if(DI.ui16_counter[ZebraF]>60   &&  Statu==Normals){
  //�����߾�������������
  if (DI.i8_StatusFlag[ZebraF] < DI.ui8_ScanLineY[1]) {
    //�����ߴ���
    uint8 ui8_ZebraTimes = 0;
    
    //���ҽ��˰�����
    for (uint8 ui8_I = 0; ui8_I < 2; ui8_I ++) {
      //��߽������߽���
      if (DI.ui8_ScanLineL[ui8_I] < DI.ui8_ScanLineToL[ui8_I]
          || DI.ui8_ScanLineR[ui8_I] > DI.ui8_ScanLineToR[ui8_I]) {
        //��ɫ���
        uint8 ui8_BlackWidth = 0;
        //��һ����ɫ
        uint8 ui8_LastColor = 
          DI.ui8_ImageArray[DI.ui8_ScanLineY[ui8_I]][DI.ui8_ScanLineToL[ui8_I]];
        
        //��������
        for (uint8 ui8_X = DI.ui8_ScanLineToL[ui8_I]; 
             ui8_X > DI.ui8_ScanLineL[ui8_I]; ui8_X --) {
          //��ɫ��
          if (DI.ui8_ImageArray[DI.ui8_ScanLineY[ui8_I]][ui8_X]) {
            //�Ƿ�ڱ��
            if (ui8_LastColor == Black) {
              //��ɫ��ȴ��ڰ����߿��
              if (ui8_BlackWidth >= ZebraWidth) {
                ui8_ZebraTimes ++;
              }
              ui8_BlackWidth = 0;
            }
            ui8_LastColor = White;
          } else {
            ui8_LastColor = Black;
            ui8_BlackWidth ++;
          }
        }
        
        ui8_BlackWidth = 0;
        ui8_LastColor = 
          DI.ui8_ImageArray[DI.ui8_ScanLineY[ui8_I]][DI.ui8_ScanLineToR[ui8_I]];
        
        //��������
        for (uint8 ui8_X = DI.ui8_ScanLineToR[ui8_I]; 
             ui8_X < DI.ui8_ScanLineR[ui8_I]; ui8_X ++) {
          //��ɫ��
          if (DI.ui8_ImageArray[DI.ui8_ScanLineY[ui8_I]][ui8_X]) {
            //�Ƿ�ڱ��
            if (ui8_LastColor == Black) {
              //��ɫ��ȴ��ڰ����߿��
              if (ui8_BlackWidth >= ZebraWidth) {
                ui8_ZebraTimes ++;
              }
              ui8_BlackWidth = 0;
            }
            ui8_LastColor = White;
          } else {
            ui8_LastColor = Black;
            ui8_BlackWidth ++;
          }
        }
      }
      //�Ƿ��㹻������
      if (ui8_ZebraTimes > ZebraTimes) {
          DI.i8_StatusFlag[ZebraF] = FlagZebra(DI.ui8_ScanLineY[ui8_I]);
           Statu=Zebra;
        return TRUE;
      } else {
        ui8_ZebraTimes = 0;
      }
    }
    
    //û����⵽������
    if (DI.i8_StatusFlag[ZebraF] == FALSE) {
      //�������
      uint8 ui8_ChangeTimes = 0;
      
      //����Զ�˰�����
      for (uint8 ui8_I = 2; ui8_I < 10; ui8_I ++) {
        //��߽������߽���
        if (DI.ui8_ScanLineL[ui8_I] < DI.ui8_ScanLineToL[ui8_I]
            || DI.ui8_ScanLineR[ui8_I] > DI.ui8_ScanLineToR[ui8_I]) {
          //��һ����ɫ
          uint8 ui8_LastColor = 
          DI.ui8_ImageArray[DI.ui8_ScanLineY[ui8_I]][DI.ui8_ScanLineToL[ui8_I]];
          
          //��������
          for (uint8 ui8_X = DI.ui8_ScanLineL[ui8_I] 
                              + DI.ui8_ScanLineR[ui8_I] >> 1;
               ui8_X > DI.ui8_ScanLineL[ui8_I]; ui8_X --) {
            //��ɫ��
            if (DI.ui8_ImageArray[DI.ui8_ScanLineY[ui8_I]][ui8_X]) {
              //�Ƿ�ڱ��
              if (ui8_LastColor == Black) {
                ui8_ChangeTimes ++;
              }
              ui8_LastColor = White;
            } else {
              ui8_LastColor = Black;
            }
          }
          
          ui8_LastColor = 
          DI.ui8_ImageArray[DI.ui8_ScanLineY[ui8_I]][DI.ui8_ScanLineToR[ui8_I]];
          
          //��������
          for (uint8 ui8_X = DI.ui8_ScanLineL[ui8_I] 
                              + DI.ui8_ScanLineR[ui8_I] >> 1;
               ui8_X < DI.ui8_ScanLineR[ui8_I]; ui8_X ++) {
            //��ɫ��
            if (DI.ui8_ImageArray[DI.ui8_ScanLineY[ui8_I]][ui8_X]) {
              //�Ƿ�ڱ��
              if (ui8_LastColor == Black) {
                ui8_ChangeTimes ++;
              }
              ui8_LastColor = White;
            } else {
              ui8_LastColor = Black;
            }
          }
        }
        //�Ƿ��㹻����������
        if (ui8_ChangeTimes > ZebraTimes) {
            DI.i8_StatusFlag[ZebraF] = FlagZebra(DI.ui8_ScanLineY[ui8_I]);
           // DI.i16p_dataImage[State] = Zebra;
            if(DI.ui8_ScanLineY[7]<50){
            Statu=Zebra;
            Zebra_delay_flag1=1;
            BeeOn;
          return TRUE;
          }
        } else {
          ui8_ChangeTimes = 0;
        }
      }
      
      return FALSE;
    } else {
      return TRUE;
    }
  } else {
//      Statu=Zebra;
//      BeeOn;
    return TRUE;
  }
   }else{
     DI.ui16_counter[ZebraF]++;
     return FALSE;
   }
}
/*
*·���ж�*
void Judgu_Typeof_Road()
{
  Straight_Judge();   //ֱ���ж�,������б�ʡ�������ֱ���ı�׼��
  if(Statu==Normals){
   Zebra_Judge();       //�������ж�
   Cross_Judge();      //ʮ���ж�
   Ring_Judge();       //Բ���ж�
   Ramp_Judge();       //�µ��ж�
   //ChaLu_Judge();       //��·�ж�
   ChaLuJudge();
  }
}


   
   
   
 */
/***********************************************************************
����������������
***********************************************************************/
  void NormalTreatment (void)
{
  //ֱ��
      for (uint8 ui8_I = 0; ui8_I < 10; ui8_I ++) {


          
        //��ͨ�׶�
   //  else{
  //    �����б߽�
      if (DI.ui8_ScanLineL[ui8_I] 
          >  DI.ui8_DisposeScopeLeft
          && DI.ui8_ScanLineR[ui8_I] 
          <  DI.ui8_DisposeScopeRight) {
      DI.i16_Mid[ui8_I] = (DI.ui8_ScanLineL[ui8_I] 
                           + DI.ui8_ScanLineR[ui8_I]) >> 1;
      //����б߽�
      } 
      else if (DI.ui8_ScanLineL[ui8_I]
                  > DI.ui8_DisposeScopeLeft) {
        DI.i16_Mid[ui8_I] = DI.ui8_ScanLineL[ui8_I]
                            + (DI.ui8_LineWidth[DI.ui8_ScanLineY[ui8_I]]>> 1);
      //�ұ��б߽�
      } else if (DI.ui8_ScanLineR[ui8_I]
                  < DI.ui8_DisposeScopeRight) {
        DI.i16_Mid[ui8_I] = DI.ui8_ScanLineR[ui8_I]
          - (DI.ui8_LineWidth[DI.ui8_ScanLineY[ui8_I]]>> 1);}

      }
  //  }
}          

//*���⴦��
void ZebraTreatment(){
  if(Zebra_delay_flag1|| Zebra_flag1){
    Zebra_flag1=0;
    Zebra_delay_flag1=1;
    
    if((DI.ui8_ImageArray[35][78] && DI.ui8_ImageArray[35][78])||
       (DI.ui8_ImageArray[33][1] && DI.ui8_ImageArray[33][78])){
         Zebra_delay_flag1=0;         
         Zebra_flag2=1;
         Record_Angle=1;
         Record_Dis=1;
       }
//    else{
//      if(Zerbra_Dir==R_go){
//      uint8 R_Y2=0;
//      uint8 R_X2=0;
//      for(uint8 Y=DI.ui8_DisposeScopeUp+5;Y<DI.ui8_DisposeScopeDown-10;Y++){
//        if(DI.ui8_ImageArray[Y][70] && DI.ui8_ImageArray[Y+1][70]
//           && DI.ui8_ImageArray[Y+2][70] && DI.ui8_ImageArray[Y+3][70]
//             && DI.ui8_ImageArray[Y+4][70]){
//               R_Y2=Y-3;
//               break;
//             }
//      }
//      R_X2=DI.ui8_RPoint[R_Y2];
//      while(1){
//                if(R_Y2>=59 || R_X2>79){
//                  break;
//                }
//                else if(!DI.ui8_ImageArray[R_Y2+1][R_X2])
//                
//               { //�����Ǻ�ɫ
//                    R_Y2++;
//                }
//                else if(!DI.ui8_ImageArray[R_Y2+1][R_X2+1]){
//                    R_Y2++;
//                    R_X2++;
//                }
//                else if(!DI.ui8_ImageArray[R_Y2+1][R_X2+2]){
//                    R_Y2++;
//                    R_X2+=2;
//                }
//               else if(!DI.ui8_ImageArray[R_Y2+1][R_X2+3]){
//                    R_Y2++;
//                    R_X2+=3;
//                }                
//                else{
//               break;
//             }
//           }
//     for(uint8 Y=R_Y2+7;Y<DI.ui8_DisposeScopeDown-5;Y++){
//        if(!DI.ui8_ImageArray[Y][70] && !DI.ui8_ImageArray[Y+1][70]){
//               //R_Y1=Y;
//               break;
//             }
//        else{
//         //R_Y1=DI.ui8_DisposeScopeDown;
//        }  
//      }
//     //R_X1=DI.ui8_LPoint[R_Y1];
//      Fits(DI.ui8_DisposeScopeLeft+1,40,DI.ui8_DisposeScopeDown,59-street_len_40);
//      Ladder();
//      FitRoad();//��û�п��ǻ���
//      Get_len();
//      DetermineScanLine();      //ȷ��ɨ����
//      NormalControl();
//    }
//    else{
//      uint8 R_Y2=0;
//      uint8 R_X2=0;
//      for(uint8 Y=DI.ui8_DisposeScopeUp+5;Y<DI.ui8_DisposeScopeDown-10;Y++){
//        if(DI.ui8_ImageArray[Y][10] && DI.ui8_ImageArray[Y+1][10]
//           && DI.ui8_ImageArray[Y+2][10] && DI.ui8_ImageArray[Y+3][10]
//             && DI.ui8_ImageArray[Y+4][10]){
//               R_Y2=Y-3;
//               break;
//             }
//      }
//      R_X2=DI.ui8_LPoint[R_Y2];
//      while(1){
//                if(R_Y2>=59 || R_X2<0){
//                  break;
//                }
//                else if(!DI.ui8_ImageArray[R_Y2+1][R_X2])
//                
//               { //�����Ǻ�ɫ
//                    R_Y2++;
//                }
//                else if(!DI.ui8_ImageArray[R_Y2+1][R_X2-1]){
//                    R_Y2++;
//                    R_X2--;
//                }
//                else if(!DI.ui8_ImageArray[R_Y2+1][R_X2-2]){
//                    R_Y2++;
//                    R_X2-=2;
//                }
//               else if(!DI.ui8_ImageArray[R_Y2+1][R_X2-3]){
//                    R_Y2++;
//                    R_X2-=3;
//                }                
//                else{
//               break;
//             }
//           }
//     for(uint8 Y=R_Y2+7;Y<DI.ui8_DisposeScopeDown-5;Y++){
//        if(!DI.ui8_ImageArray[Y][10] && !DI.ui8_ImageArray[Y+1][10]){
//               //R_Y1=Y;
//               break;
//             }
//        else{
//         //R_Y1=DI.ui8_DisposeScopeDown;
//        }  
//      }
//     //R_X1=DI.ui8_LPoint[R_Y1];
//      Fits(DI.ui8_DisposeScopeLeft+1,40,DI.ui8_DisposeScopeDown,59-street_len_40);
//      Ladder();
//      FitRoad();//��û�п��ǻ���
//      Get_len();
    else{
      DetermineScanLine();      //ȷ��ɨ����
      NormalControl();
    }
//    }
//        
 //   }
               
  }
  if(Zebra_delay_flag2|| Zebra_flag2){
    Zebra_flag2=0;
    Zebra_delay_flag2=1;
    if(Zerbra_Dir==R_go){
    if( SumAngle>500 ||  SumAngle<=-500){
             SumAngle=0;
             Distance=0;
             Record_Angle=0;
             BeeOff;
             Zebra_delay_flag2=0;          
             Run=0;
           }
    Fit(DI.ui8_DisposeScopeLeft,75,DI.ui8_DisposeScopeDown,59-street_len_75);
    for(uint8 Y=DI.ui8_DisposeScopeDown;Y>59-street_len_75;Y--){
      DI.ui8_RPoint[Y]=79;
    }
    poserror=30;//(DI.ui8_LPoint[72-street_len_75]+DI.ui8_RPoint[72-street_len_75]+DI.ui8_LPoint[71-street_len_75]+DI.ui8_RPoint[71-street_len_75]+DI.ui8_LPoint[70-street_len_75]+DI.ui8_RPoint[70-street_len_75])/6-30;
    }
      else{
         if( SumAngle<=-500 || SumAngle>500  ){
             SumAngle=0;
             Distance=0;
             Record_Angle=0;
             BeeOff;
             Zebra_delay_flag2=0;          
             Run=0;
           }
    Fit(DI.ui8_DisposeScopeRight,5,DI.ui8_DisposeScopeDown,59-street_len_5);
    for(uint8 Y=DI.ui8_DisposeScopeDown;Y>59-street_len_5;Y--){
      DI.ui8_LPoint[Y]=5;
    }
    poserror=-30;//(DI.ui8_LPoint[72-street_len_5]+DI.ui8_RPoint[72-street_len_5]+DI.ui8_LPoint[71-street_len_5]+DI.ui8_RPoint[71-street_len_5]+DI.ui8_LPoint[70-street_len_5]+DI.ui8_RPoint[70-street_len_5])/6-50;
      }
    }
    
    
  }
    
       


/***********************************************************************
����������������
***********************************************************************/
void LRingTreatment(){
  //�����ܵ��뻷��
  if((L_Ring_flag1|| L_Ring_delay_flag1)){
     L_Ring_flag1=0;
     L_Ring_delay_flag1=1;
     Record_Dis=1;
     Record_Angle=1;
     if((street_len_5>30 && street_len_5<=55 && !DI.ui8_ImageArray[57-street_len_5][5] && !DI.ui8_ImageArray[55-street_len_5][5] &&  !DI.ui8_ImageArray[53-street_len_5][5] && Distance>=35)|| Distance>60){
       Record_Dis=0;
       Distance=0;
       L_Ring_delay_flag1=0;
       L_Ring_flag2=1;
       BeeOff;
     }
           
  }
  
  //�뻷,���뻷����
   if((L_Ring_flag2 || L_Ring_delay_flag2)){
     L_Ring_flag2=0;
     L_Ring_delay_flag2=1;
     if(SumAngle>400){
       BeeOff;
       L_Ring_delay_flag2=0;
       L_Ring_flag3=1;
     }
     if(street_len_5>20){
       uint8 L_Y1=DI.ui8_DisposeScopeDown-1;
       uint8 L_X1=DI.ui8_DisposeScopeRight-1;
       uint8 L_Y3=60-street_len_5;
       L_Y3=L_Y3-7;
       uint8 L_X3=DI.ui8_LPoint[L_Y3];
       while(1){
                if(L_Y3>=59 || L_X3<=0){
                  break;
                }
                else if(!DI.ui8_ImageArray[L_Y3+1][L_X3])
                
               { //�����Ǻ�ɫ
                    L_Y3++;
                }
                else if(!DI.ui8_ImageArray[L_Y3+1][L_X3-1]){
                    L_Y3++;
                    L_X3--;
                }
                else if(!DI.ui8_ImageArray[L_Y3+1][L_X3-2]){
                    L_Y3++;
                    L_X3-=2;
                }
               else if(!DI.ui8_ImageArray[L_Y3+1][L_X3-3]){
                    L_Y3++;
                    L_X3-=3;
                }                
                else{
               break;
             }
           }
       Vistable_scale=L_Y3;
       for(uint8 ui8_Y=L_Y1-1;ui8_Y>L_Y3;ui8_Y--){
          DI.ui8_LPoint[ui8_Y]=0;
         }
       Fit(L_X1,L_X3,L_Y1,L_Y3);
     }
     else{//��ɫ����
       uint8 L_Y1=DI.ui8_DisposeScopeDown-1;
       uint8 L_X1=DI.ui8_DisposeScopeRight-1;
       uint8 L_Y3=59-street_len_5;
       uint8 L_X3=DI.ui8_LPoint[L_Y3];
       for(uint8 Y=L_Y3-1;Y>DI.ui8_DisposeScopeUp;Y--){
         if(DI.ui8_ImageArray[Y][5] && DI.ui8_ImageArray[Y-1][5]){
           L_Y3=Y;
           break;
         }
       }
       for(uint8 Y=L_Y3-1;Y>DI.ui8_DisposeScopeUp;Y--){
         if(!DI.ui8_ImageArray[Y][5] && !DI.ui8_ImageArray[Y-1][5]){
           L_Y3=Y;
           break;
         }
       }
        L_Y3=L_Y3-7;
       L_X3=DI.ui8_LPoint[L_Y3];
       while(1){
                if(L_Y3>=59 || L_X3<=0){
                  break;
                }
                else if(!DI.ui8_ImageArray[L_Y3+1][L_X3])
                
               { //�����Ǻ�ɫ
                    L_Y3++;
                }
                else if(!DI.ui8_ImageArray[L_Y3+1][L_X3-1]){
                    L_Y3++;
                    L_X3--;
                }
                else if(!DI.ui8_ImageArray[L_Y3+1][L_X3-2]){
                    L_Y3++;
                    L_X3-=2;
                }
               else if(!DI.ui8_ImageArray[L_Y3+1][L_X3-3]){
                    L_Y3++;
                    L_X3-=3;
                }                
                else{
               break;
             }
           }
       Vistable_scale=L_Y3;
       for(uint8 ui8_Y=L_Y1-1;ui8_Y>L_Y3;ui8_Y--){
          DI.ui8_LPoint[ui8_Y]=0;
         }
       Fit(L_X1,L_X3,L_Y1,L_Y3);
       
     }
     for(uint8 Y=Vistable_scale;Y>DI.ui8_DisposeScopeUp;Y--){
       if(DI.ui8_ImageArray[Y][3] && DI.ui8_ImageArray[Y][4]){
         for( uint8 X=4;X<DI.ui8_DisposeScopeRight;X++){
           if(!DI.ui8_ImageArray[Y][X]){
              DI.ui8_RPoint[Y]=X;
              DI.ui8_LPoint[Y]=0;
              break;
           }
         }
       }
       else{
         Vistable_scale=Y+1;
         break;
       }
     }
      //һ����ֵ����
     if(DI.ui8_ImageArray[59][5] && DI.ui8_ImageArray[58][5] )
       Vistable_scale=59-street_len_5;
       
      DetermineScanLine();      //ȷ��ɨ����
      NormalControl();
   }

  if((L_Ring_flag3 || L_Ring_delay_flag3)){
     L_Ring_flag3=0;
     L_Ring_delay_flag3=1;
     if((SumAngle>=2100)||(DI.ui8_ScanLineToR[5]>=70 && DI.ui8_ScanLineToR[7]>=70  && DI.ui8_ScanLineToR[6]>=70
                          && SumAngle>=1500  )){

       L_Ring_delay_flag3=0;
       L_Ring_flag4=1;
       BeeOn;
       SumAngle=0;
     }
     NormalControl();
     if(poserror<=-40) poserror=-40;
     if(poserror>=40) poserror=40;
}
//�����ڳ���

   if((L_Ring_flag4 || L_Ring_delay_flag4)){
     L_Ring_flag4=0;
     L_Ring_delay_flag4=1;
     if(SumAngle>=400
          ){
       L_Ring_delay_flag4=0;
       L_Ring_flag5=1;
       Record_Dis=1;
       
     }
   if(!DI.ui8_ImageArray[59][78] && !DI.ui8_ImageArray[55][78] && street_len_75<=15)
   {
      //ȷ��ͻ���
     uint8 Jump_PointL=54;
     for(uint8 Y=54;Y>0;Y--){
       if(DI.ui8_ImageArray[Y-1][DI.ui8_RPoint[Y]] && DI.ui8_ImageArray[Y-2][DI.ui8_RPoint[Y]]){
         Jump_PointL=Y;
         break;
       }
     }
       float k=(DI.ui8_RPoint[59]-DI.ui8_RPoint[55])/4.0;
       for(uint8 Y=Jump_PointL;Y>0;Y--){
         DI.ui8_RPoint[Y]=(int8)(DI.ui8_RPoint[55]-(55-Y)*k);
         if(!DI.ui8_ImageArray[Y][DI.ui8_RPoint[Y]] && !DI.ui8_ImageArray[Y-1][DI.ui8_RPoint[Y]]){
           Vistable_scale=59-street_len_40;
             break;
         }
       }
   }
     else{  
       int L_Y1=DI.ui8_DisposeScopeDown-10;
       int L_X1=DI.ui8_DisposeScopeRight-1;
       int L_Y3=59-street_len_5;
       int L_X3=5;
       //���ȫ��Ϊ0
       for(uint8 ui8_Y=L_Y1-1;ui8_Y>L_Y3;ui8_Y--){
          DI.ui8_LPoint[ui8_Y]=0;
         }
      //����
       Fit(L_X1,L_X3,L_Y1,L_Y3);
        Vistable_scale=L_Y3;
   }
         DetermineScanLine();      //ȷ��ɨ����
      NormalControl();
   
     
  }
     if(L_Ring_flag5 || L_Ring_delay_flag5){
     L_Ring_flag5=0;
     L_Ring_delay_flag5=1;
     if(Distance>=60){
       BeeOff;
       L_Ring_delay_flag5=0;
       Ring_flag=0;
       have_ring=1;
       Record_Dis=0;
       Record_Angle=0;
       Distance=0;
       SumAngle=0;
       Statu=Normals;
     }
    // if(Ring_Size==Big){
       if(street_len_5>=7){
       int L_Y1=54;
       int L_X1=0;//79-(79-DI.ui8_LineWidth[54]-DI.ui8_LPoint[54]);
       int L_Y3=59-street_len_5;
       int L_X3=15;
         for(uint8 X=5;X<79;X++){
           if(DI.ui8_ImageArray[L_Y3-2][X] && DI.ui8_ImageArray[L_Y3-2][X+1]){
             L_X3=X;
             break;
           }
         }
        Fit(L_X1,L_X3,L_Y1,L_Y3);
           DetermineScanLine();      //ȷ��ɨ����
          NormalControl();
       }
       else{
                poserror=(DI.ui8_RPoint[20]+DI.ui8_RPoint[21]+DI.ui8_RPoint[22]
                +DI.ui8_LPoint[20]+DI.ui8_LPoint[21]+DI.ui8_LPoint[22])/6-40;
       }
          
   
  }
}

/*

//�һ�������
void RRingTreatment (void)
{
   if((R_Ring_flag1|| R_Ring_delay_flag1)){
       R_Ring_flag1=0;
     R_Ring_delay_flag1=1;
     Record_Dis=1;
     if(  (street_len_75>=30 && street_len_75<=55 && !DI.ui8_ImageArray[59-street_len_75][74] && !DI.ui8_ImageArray[58-street_len_75][74])
         ||(Distance>=30 && Ring_Size==Little) ||(Distance>=50 && Ring_Size==Big)){
       R_Ring_delay_flag1=0;
       R_Ring_flag2=1;
       Record_Dis=0;
       Distance=0;
     }
     if(Ring_Size==Little){
       //Ѱ�Ҿ��������
         uint8 R_Y2=20;
         uint8 R_X2=DI.ui8_RPoint[R_Y2];
         for(uint8 Y=DI.ui8_DisposeScopeUp+1;Y<DI.ui8_DisposeScopeDown;Y++){
           if(DI.ui8_ImageArray[Y][60] && DI.ui8_ImageArray[Y+1][60]
               && DI.ui8_ImageArray[Y+2][60] && DI.ui8_ImageArray[Y+3][60]){
                 R_Y2=Y-1;
                 break;
               }
         }
         for(uint8 X=59;X>1;X--){
           if(DI.ui8_ImageArray[R_Y2][X] && DI.ui8_ImageArray[R_Y2][X-1]){
             R_X2=X;
             break;
           }
         }
         uint8 R_Y1=DI.ui8_DisposeScopeDown-1;
         uint8 R_X1=DI.ui8_DisposeScopeLeft+1;
         Fit(R_X1,R_X2,R_Y1,R_Y2);
         Vistable_scale=R_Y2;
         for(uint8 ui8_Y=R_Y1-1;ui8_Y>R_Y2;ui8_Y--){
          DI.ui8_RPoint[ui8_Y]=79;
         }
       if(DI.ui8_ImageArray[50][75] && DI.ui8_ImageArray[51][75] )
       Vistable_scale=59-street_len_75;
         DetermineScanLine();      //ȷ��ɨ����
         NormalControl();
        if(poserror<=-20) poserror=-20;
        if(poserror>=20) poserror=20;
     }
     else poserror=10;
  }
  //GAI!
  //�뻷,���뻷����
   if((R_Ring_flag2 || R_Ring_delay_flag2)){
     R_Ring_flag2=0;
     R_Ring_delay_flag2=1;
     if(SumAngle>=200 ){
       BeeOff;
       R_Ring_delay_flag2=0;
       R_Ring_flag3=1;
     }
      if(street_len_75>20){
       uint8 R_Y1=DI.ui8_DisposeScopeDown-1;
       uint8 R_X1=DI.ui8_DisposeScopeLeft+1;
       uint8 R_Y3=60-street_len_75;
       R_Y3=R_Y3-7;
       uint8 R_X3=DI.ui8_RPoint[R_Y3];
       while(1){
                if(R_Y3>=59 || R_X3>79){
                  break;
                }
                else if(!DI.ui8_ImageArray[R_Y3+1][R_X3])
                
               { //�����Ǻ�ɫ
                    R_Y3++;
                }
                else if(!DI.ui8_ImageArray[R_Y3+1][R_X3+1]){
                    R_Y3++;
                    R_X3++;
                }
                else if(!DI.ui8_ImageArray[R_Y3+1][R_X3+2]){
                    R_Y3++;
                    R_X3+=2;
                }
               else if(!DI.ui8_ImageArray[R_Y3+1][R_X3+3]){
                    R_Y3++;
                    R_X3+=3;
                }                
                else{
               break;
             }
           }
       Vistable_scale=R_Y3;
       for(uint8 ui8_Y=R_Y1-1;ui8_Y>R_Y3;ui8_Y--){
          DI.ui8_RPoint[ui8_Y]=79;
         }
       Fit(R_X1,R_X3,R_Y1,R_Y3);
     }
     else{//��ɫ����
       uint8 R_Y1=DI.ui8_DisposeScopeDown-1;
       uint8 R_X1=DI.ui8_DisposeScopeLeft+1;
       uint8 R_Y3=59-street_len_75;
       uint8 R_X3=DI.ui8_RPoint[R_Y3];
       for(uint8 Y=R_Y3-1;Y>DI.ui8_DisposeScopeUp;Y--){
         if(DI.ui8_ImageArray[Y][75] && DI.ui8_ImageArray[Y-1][75]){
           R_Y3=Y;
           break;
         }
       }
       for(uint8 Y=R_Y3-1;Y>DI.ui8_DisposeScopeUp;Y--){
         if(!DI.ui8_ImageArray[Y][75] && !DI.ui8_ImageArray[Y-1][75]){
           R_Y3=Y;
           break;
         }
       }
       R_Y3=R_Y3-7;
       R_X3=DI.ui8_RPoint[R_Y3];
       while(1){
                if(R_Y3>=59 || R_X3>79){
                  break;
                }
                else if(!DI.ui8_ImageArray[R_Y3+1][R_X3])
                
               { //�����Ǻ�ɫ
                    R_Y3++;
                }
                else if(!DI.ui8_ImageArray[R_Y3+1][R_X3+1]){
                    R_Y3++;
                    R_X3++;
                }
                else if(!DI.ui8_ImageArray[R_Y3+1][R_X3+2]){
                    R_Y3++;
                    R_X3+=2;
                }
               else if(!DI.ui8_ImageArray[R_Y3+1][R_X3+3]){
                    R_Y3++;
                    R_X3+=3;
                }                
                else{
               break;
             }
           }
       Vistable_scale=R_Y3;
       for(uint8 ui8_Y=R_Y1-1;ui8_Y>R_Y3;ui8_Y--){
          DI.ui8_RPoint[ui8_Y]=79;
         }
       Fit(R_X1,R_X3,R_Y1,R_Y3);
       
     }
     for(uint8 Y=Vistable_scale;Y>DI.ui8_DisposeScopeUp;Y--){
       if(DI.ui8_ImageArray[Y][78] && DI.ui8_ImageArray[Y][77]){
         for( uint8 X=76;X>DI.ui8_DisposeScopeLeft;X--){
           if(!DI.ui8_ImageArray[Y][X]){
              DI.ui8_LPoint[Y]=X;
              DI.ui8_RPoint[Y]=79;
              break;
           }
         }
       }
       else{
         Vistable_scale=Y+1;
         break;
       }
     }
      //һ����ֵ����
     if(DI.ui8_ImageArray[59][75] && DI.ui8_ImageArray[58][75] )
       Vistable_scale=59-street_len_75;
       
      DetermineScanLine();      //ȷ��ɨ����
      NormalControl();
       
           
       if(Ring_Size==Big)  {
          if(poserror>20) poserror=20;
          if(poserror<10) poserror=10;
       }
       else{
         if(poserror>40) poserror=40;
         if(poserror<30) poserror=30;
          }
   }

//  
  if((R_Ring_flag3 || R_Ring_delay_flag3)){
     R_Ring_flag3=0;
     R_Ring_delay_flag3=1;
     if((SumAngle>=1280)||(DI.ui8_ScanLineToL[5]<=10 && DI.ui8_ScanLineToL[7]<=10  && DI.ui8_ScanLineToL[6]<=10)){
       R_Ring_delay_flag3=0;
       R_Ring_flag4=1;
       SumAngle=0;
       BeeOn;
     }
     NormalControl();
     if(poserror<=-40) poserror=-40;
     if(poserror>=40) poserror=40;
}
//�����ڳ���
   if((R_Ring_flag4 || R_Ring_delay_flag4)){
     R_Ring_flag4=0;
     R_Ring_delay_flag4=1;
     if((SumAngle>250 && Ring_Size==Little)|| (SumAngle>300 && Ring_Size==Big) ){
       BeeOff;
       R_Ring_delay_flag4=0;
       R_Ring_flag5=1;
       Record_Dis=1;
     }
   if(!DI.ui8_ImageArray[59][1] && !DI.ui8_ImageArray[55][1] && street_len_5<=15)
   {
      //ȷ��ͻ���
     uint8 Jump_PointR=54;
     for(uint8 Y=54;Y>0;Y--){
       if(DI.ui8_ImageArray[Y-1][DI.ui8_LPoint[Y]] && DI.ui8_ImageArray[Y-2][DI.ui8_LPoint[Y]]){
         Jump_PointR=Y;
         break;
       }
     }
       float k=(DI.ui8_LPoint[55]-DI.ui8_LPoint[59])/4.0;
       for(uint8 Y=Jump_PointR;Y>0;Y--){
         DI.ui8_LPoint[Y]=(int8)(DI.ui8_LPoint[55]+(55-Y)*k);
         if(!DI.ui8_ImageArray[Y][DI.ui8_LPoint[Y]] && !DI.ui8_ImageArray[Y-1][DI.ui8_LPoint[Y]]){
           Vistable_scale=59-street_len_40;
             break;
         }
       }
   }
   else{          
       int L_Y1=DI.ui8_DisposeScopeDown-10;
       int L_X1=DI.ui8_DisposeScopeLeft+1;
       int L_Y3=59-street_len_75;
       int L_X3=75;
       //���ȫ��Ϊ0
       for(uint8 ui8_Y=L_Y1-1;ui8_Y>L_Y3;ui8_Y--){
          DI.ui8_RPoint[ui8_Y]=79;
         }
      //����
       Fit(L_X1,L_X3,L_Y1,L_Y3);
        Vistable_scale=L_Y3;
   }
      DetermineScanLine();      //ȷ��ɨ����
      NormalControl();
   if(Ring_Size==Big){
     if(poserror<=10) poserror=10;
     if(poserror>=20) poserror=20;

   }
   else{       
     if(poserror<=20) poserror=20;
     if(poserror>=35) poserror=35;
   }
  }
  
   if(R_Ring_flag5 || R_Ring_delay_flag5){
     R_Ring_flag5=0;
     R_Ring_delay_flag5=1;
     if((Distance>=90 && Ring_Size==Big) || (Distance>=80 && Ring_Size==Little) ){
       BeeOff;
       R_Ring_delay_flag5=0;
       Ring_flag=0;
       have_ring=1;
       Record_Angle=0;
       Distance=0;
       SumAngle=0;
       Statu=Normals;
       SC++;
       if(SC>=Special_Count) SC=0;
           // Run=0;
     }
    // if(Ring_Size==Big){
       if(street_len_75>=8){
       int R_Y1=54;
       int R_X1=79;//79-(79-DI.ui8_LineWidth[54]-DI.ui8_LPoint[54]);
       int R_Y3=59-street_len_75;
       int R_X3=65;
         for(uint8 X=75;X>0;X--){
           if(DI.ui8_ImageArray[R_Y3][X] && DI.ui8_ImageArray[R_Y3][X-1]){
             R_X3=X;
             break;
           }
         }
        Fit(R_X1,R_X3,R_Y1,R_Y3);
        DetermineScanLine();      //ȷ��ɨ����
          NormalControl();
       }
      else{
                poserror=(DI.ui8_RPoint[20]+DI.ui8_RPoint[21]+DI.ui8_RPoint[22]
                +DI.ui8_LPoint[20]+DI.ui8_LPoint[21]+DI.ui8_LPoint[22])/6-40;
       }
   if(Ring_Size==Big){
     if(poserror<=-20) poserror=-20;
     if(poserror>20) poserror=20;
   }
   else{
     if(poserror<=-40) poserror=-40;
     if(poserror>=40) poserror=40;
   } 
       
   }
}
  
*/
//�µ�
void  RampsTreatment(){
  if(Distance>=140){
      Distance=0;
      Record_Dis=0;
      BeeOff;
      Statu=Normals;
      have_podao=1;
  }
}
      
/*

      
 //״̬����  
void Treatment_Status(){
  switch(Statu)
 {
   case Zebra:  ZebraTreatment();  break;//��⴦��
   case Cross:  CrossTreatment();  break;
   case LRing:  LRingTreatment();  break;
   case RRing:  RRingTreatment();  break;   
   case Lukou:  ChaLuTreatment();  break;
   case Ramps:  RampsTreatment();  break;
   default:    NormalTreatment ();
 }
}
*/
uint8 CHALU_TIME =1;//1:���ҹ� 2:�����
void ChaLuTreatment(void){
  if(ChaLu_flag0||ChaLu_delay_flag0){
    ChaLu_flag0=0;
    ChaLu_delay_flag0=1;
    if(street_len_40<=50){
      ChaLu_flag1=1;
      ChaLu_delay_flag0=0;
    }
   }
      
  if(ChaLu_flag1||ChaLu_delay_flag1){
    Record_Angle=1;
    Record_Dis=1;
    BeeOn;
    ChaLu_flag1=0;
    ChaLu_delay_flag1=1;
    if(SumAngle>=400 || SumAngle<=-400 || Distance>=50){
           SumAngle=0;
           Record_Angle=0;
           //BeeOff;
           ChaLu_delay_flag1=0;
           ChaLu_flag2=1;
         }
    //����
    else{
      if(CHALU_TIME==1){
            Fits(DI.ui8_DisposeScopeLeft+1,40,DI.ui8_DisposeScopeDown,59-street_len_40);
              Ladder();
              FitRoad();//��û�п��ǻ���
              Get_len();
            DetermineScanLine();      //ȷ��ɨ����
            NormalControl();
             //if(poserror>=20) poserror=20;
      }
      else{
             Fits(DI.ui8_DisposeScopeRight-1,40,DI.ui8_DisposeScopeDown,59-street_len_40);
              Ladder();
              FitRoad();//��û�п��ǻ���
              Get_len();
             DetermineScanLine();      //ȷ��ɨ����
             NormalControl();
           // if(poserror<=-20) poserror=-20;
      }
    }
}

  
  
 if(ChaLu_flag2||ChaLu_delay_flag2){
    ChaLu_flag2=0;
    ChaLu_delay_flag2=1;
    if( DI.ui8_ImageArray[55][0] && DI.ui8_ImageArray[55][78]
       &&  DI.ui8_ImageArray[53][0] && DI.ui8_ImageArray[53][0]
       &&  DI.ui8_ImageArray[50][0] && DI.ui8_ImageArray[50][0] && Distance>=150){
                  
                  ChaLu_delay_flag2=0;
                  ChaLu_flag3=1;
                  Record_Dis=1;
                  Distance=0;
    }
    else{
       NormalControl(); 
    }
  }
 
 if(ChaLu_flag3||ChaLu_delay_flag3){
   BeeOff; 
   Record_Angle=1;
    ChaLu_flag3=0;
    ChaLu_delay_flag3=1;
     if( SumAngle>=100 ||  SumAngle<=-100 || Distance>=80){
          ChaLu_delay_flag3=0;
          Record_Angle=0;
          Record_Dis=0;
          SumAngle=0;
          Distance=0;
          Statu=Normals;
         CHALU_TIME++;
          if(CHALU_TIME==2) CHALU_TIME=0;
         }
    //����
    else{
      if(CHALU_TIME==1 && street_len_40<=30){
           Fits(DI.ui8_DisposeScopeLeft+1,40,DI.ui8_DisposeScopeDown,59-street_len_40);
              Ladder();
              FitRoad();//��û�п��ǻ���
              Get_len();
            DetermineScanLine();      //ȷ��ɨ����
            NormalControl();
             if(poserror>=20) poserror=20;
      }      
      else if(CHALU_TIME==0 && street_len_40<=30){
             Fits(DI.ui8_DisposeScopeRight-1,40,DI.ui8_DisposeScopeDown,59-street_len_40);
              Ladder();
              FitRoad();//��û�п��ǻ���
              Get_len();
             DetermineScanLine();      //ȷ��ɨ����
             NormalControl();
            if(poserror<=-20) poserror=-20;
      }else{NormalControl();}
    }
  }

}
/*
void CrossTreatment(void){
    if(Cross_flag0||Cross_delay_flag0){
      BeeOn;
      Cross_flag0=0;
      Cross_delay_flag0=1;
      Record_Dis=1;
      if(Distance>=100){
         BeeOff;
          Cross_delay_flag0=0;
          Distance = 0;
          Record_Dis = 0;
          NormalControl(); 
          Statu=Normals;
          SC++;
          if(SC>=Special_Count) {SC=0;Run=0;}
           Cross_num = 0; 
      }else{NormalControl();}//�ڲ�·�ڲ���������
   }
//   if(Cross_flag1||Cross_delay_flag1){
//      Cross_flag1=0;
//      Cross_delay_flag1=1;
//      Record_Angle = 1;      
//      if( (SumAngle>=700 || SumAngle<=-700)&&ChaLu_Judge()==1 ){
//          Cross_delay_flag1=0;
//          Cross_flag2=1;
//          SumAngle=0;
//          Record_Angle = 0;    
//        NormalControl();
//      }else{NormalControl();}//�ڲ�·�ڲ���������
//   } 
//   if(Cross_flag2||Cross_delay_flag2){
//      BeeOn;
//      Cross_flag2=0;
//      Cross_delay_flag2=1;
//      Record_Dis=1;
//      if(Distance>=30){
//          BeeOff;
//          Cross_delay_flag2=0;
//          Distance = 0;
//          Record_Dis = 0;
//          NormalControl(); 
//          Statu=Normals;
//          SC++;
//          if(SC>=Special_Count) {SC=0;Run=0;}
//           Cross_num = 0; 
//      }else{NormalControl();}//�ڲ�·�ڲ���������
//   }   
}
*/
