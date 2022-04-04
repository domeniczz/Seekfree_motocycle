#ifndef SOFTIIC_H
#define SOFTIIC_H

#include "common.h"
#include "stdbool.h"
#include "hal_include.h"



#define IICDelay        120
#define SEEKFREE_SCL1    P20_11
#define SEEKFREE_SDA1    P20_14



#define IIC_SDA_OUT()    gpio_dir(SEEKFREE_SDA1, GPO, PUSHPULL);//设置P00_0为推挽输出模式
#define IIC_SDA_IN()     gpio_dir(SEEKFREE_SDA1, GPI, PULLUP);//设置P00_0为推挽输出模式
#define IIC_DATA        gpio_get  (SEEKFREE_SDA1)
#define IIC_SDA_H       gpio_set  (SEEKFREE_SDA1, 1)
#define IIC_SCL_H       gpio_set  (SEEKFREE_SCL1, 1)
#define IIC_SDA_L       gpio_set  (SEEKFREE_SDA1, 0)
#define IIC_SCL_L       gpio_set  (SEEKFREE_SCL1, 0)


static uint8 IIC_Read_Bytes(unsigned char ack);
uint8 IIC_Read_Buff(uint8 addr, uint8 offset, uint8* buff, uint8 size);
void IIC_init(void);
#endif
