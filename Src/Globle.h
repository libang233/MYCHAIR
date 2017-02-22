// 文件名 ：Globle.h
// 作者   : 赵成华 赵成华 陈统 何立邦 何立邦
// 日期   : 2017年 2月 15日

#include "newtype.h"

#ifndef _GLOBAL_H_
#define _GLOBAL_H_

//
//常量宏定义
//
#define pe		0x00
#define kn	  	0x01
#define pk	  	0x02
#define up_dn   0x03
#define stop	0x00
#define up	    0x01
#define dn	    0x02

#define TIME_DOG  	4							// 看门狗计数器
#define TIME_SEC    16							// 1秒定时
#define TIME_MIN    60							// 1分钟定时
#define TIMER0_ORG  0x1F						// 定时器0初始化装载值

#define ADD_SPEED   50							// 每次按键增加的速度
#define INIT_SPEED	105							// 揉捏拍打初始化速度
#define HIGH_SPEED	205							// 揉捏拍打高速度	
#define MAX_SPEED   205 						// 最大速度
#define WiDTH_SPEED 155                         // 宽度调整速度
#define DIFFERENT_SPEED 0					    // 揉捏和拍打速度差

#define ATUO_ONE    0x01				    	// 自动模式1 的动作编号
#define ATUO_TWO    0x02						// 自动模式2 的动作编号
#define ATUO_THREE  0x03						// 自动模式3 的动作编号
#define PER_KNE     0x04						// 同时进行揉捏敲打 动作编号
#define KNE         0x05 						// 按摩的动作编号 
#define PER         0x06						// 敲打的动作编号


//定义端口

sbit flapm     =P3^7;   //pwm
sbit kneadm    =P2^0;   //pwm
sbit backm_up  =P1^7;
sbit backm_dn  =P1^6;
sbit seatm_up  =P1^5;
sbit seatm_dn  =P1^4;
sbit upm       =P1^3;   //pwm
sbit dnm       =P1^2;   //pwm
sbit upCheck   =P2^4;
sbit dnCheck   =P2^5;
sbit mda_pin   =P3^4;
sbit mdb_pin   =P3^3;


#endif