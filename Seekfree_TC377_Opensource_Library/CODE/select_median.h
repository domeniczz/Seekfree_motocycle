#ifndef __SELECT_MEDIAN_H
#define __SELECT_MEDIAN_H

#include "hal_include.h"

extern int poserror ;
extern int poserror_array[4];
/*起始控制********************************************************************/
/*图像处理函数*/
void DisposeImage (void);
/*起始控制********************************************************************/

/*共用处理********************************************************************/
/*正常提取中值*/
void NormalControl (void);

/*确定最后中值*/
void DetermineMid (void);

void LostWayControl (void);
/*共用处理********************************************************************/

/*行处理**********************************************************************/
/*确定权重*/
void DetermineWeight (void);

/*确定扫描行*/
void DetermineScanLine (void);
/*行处理**********************************************************************/

/*入环处理*/
void  InRingControl(void);

/*出环处理*/
void  OutRingControl(void);

/*环岛中*/
void  RingControl(void);
/*ruku*/
void InChekuControl(void);
//元素定义声明
#define   OUT_PARK  0  //出车库
#define   IN_PARK   1 //进入车库
#define   L_Little  2  //左小环
#define   R_Little  3  //右小环
#define   L_Big  4  //左大环
#define   R_Big  5  //右大环
#define   RAMP  6  //坡道
#define   L_SANCHA  7 //左入三叉
#define   R_SANCHA  8 //右入三叉
#define   Crosses   9//十字路口
extern uint16 Goal_Speed;
extern uint8 Special_Count;
extern uint8 Special_type[12];//元素数组

#endif
