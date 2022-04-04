#ifndef _DATA_SHEET_H
#define _DATA_SHEET_H

#include "hal_include.h"
/*----------------本菜单------------------------------------------------------------------------------*/
//图像阈值
#define Ithreshold     (uint8)d_GetItemValue(Image_Order, Image_Ithreshold_Order)     //定阈值有用
#define DJ_p    (double)d_GetItemValue(Image_Order, BaseWeight_5_Order)//电机P
#define DJ_i (double)d_GetItemValue(Image_Order, BaseWeight_6_Order)//电机I
#define Out_P (double)d_GetItemValue(Image_Order, Image_IthresholdL_Order)//电机I
#define Base_Speed (uint16)d_GetItemValue(Dianji_Order, Dianji_PulseBase_Order)

/*---------------------------------------------------------------------------------------------------*/


//*图像相关********************************************************************/
#define SIZE_HRE  60   //图像行数
#define MID_POINT 40    //中值
#define Lstart                  1
#define Rstart                  2
#define Mstart                  3
#define White                   1
#define Black                   0



//*动态中值****************************/

#define HtoE            0.15//可视距离对偏差影响
#define VtoLine         0.003//速度对权重影响
//*动态中值****************************/


/*状态****************************/
//直道
#define Straight                2
//弯道
#define Curve                   3  
//圆环
#define Ring                    4
//十字路
//#define Cross                   5
//坡道
#define Ramp                    6
//断路
#define Breaker                 7  
//横断路障
#define Roadblock               8
/*状态*****************************/

/*状态标志*****************************/
//*长直道**************************/
#define LSF                     1
//长直道判定终止行
#define LSEndLine               40
//长直道判定左右终止行
#define LSEndLineLR             40
//波动最大值
#define LSMaxVariance           2
//直道宽度偏差
#define LSWidthEr               5
//*长直道**************************/

//*环岛**************************/
#define RingF                   2
#define RightRing               1
#define LeftRing                2

/**************************************/
#define Ring_flag1              1





//*坡道**************************/
#define RampF                   3
#define RAMP_In_Flag            1
#define RAMP_On_Flag            2
#define RAMP_ToOut_Flag         3
#define RAMP_Out_Flag           4
#define RAMP_Speed              230
#define Ramp_MinLine            16
//*坡道**************************/

//*斑马线**************************/
#define ZebraF                  4
#define ZebraTimes              5//最小跳变次数
#define FlagZebra(x)            x//斑马线所在行
#define ZebraWidth              3//斑马线最小宽度
#define END_SpeedPluse          100
#define END_COUNT               11
//*坡道**************************/


//安全等级划分距离(mm) 
#define Blue_Distance          1000            
#define Yellow_Distance        900  
#define Orange_Distance        600
#define Red_Distance           400
#define Unable_Distance        270
#define Max_Distance           2000
#define HD_SpeedPluse          70
#define HD_MINLINE              13//路障最小距离
//*坡道**************************/

//电机卡死计数
#define STUCK_TIMES             500


//*当前中值************************/
#define Mid_point               0
/*当前中值*************************/

//*可视距离***********************/
#define Height                  1
/*可视距离************************/

//*状态****************************/
#define State                   2
/*状态*****************************/
#define BeeOn                   gpio_set(P33_10,1)
#define BeeOff                  gpio_set(P33_10,0)
//按键
#define OK                     !gpio_get(P22_1)
#define Up                     !gpio_get(P22_0)
#define Down                   !gpio_get(P22_2)
#define Right                  !gpio_get(P22_3)



#endif
