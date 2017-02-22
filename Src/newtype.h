// 文件名 ：newtype.h
// 作者   : 赵成华 陈统 何立邦
// 日期   : 2017年 2月 15日

#ifndef _NEWTYPE_H_
#define _NEWTYPE_H_

#include "STC12C5410AD.H"

typedef unsigned char u8;
typedef unsigned int  u16;
typedef unsigned long u32;

#define true  	1
#define false 	0
#define TRUE  	1
#define FALSE 	0

//
// 事件标志位 联合体
//
union nt_uEVNT
{       	
	u8	ALL ;													// 总体定义，用于总体赋值
	struct														// 各个位定义
	{
		volatile u8 IsPOWER_OFF	  		    	:1; 			// 关机标志位 1 = 申请关机
		volatile u8 IsReset_F	  				:1; 			// 重置标志位 1 =申请重置
		volatile u8 IsAllMotorsStop			    :1;				// 所有电机停止	1 =申请所有电机停止 
//		volatile u8 IsAllMotorsGoOn			    :1;				// 所有电机继续	1 =申请所有电机继续 
		volatile u8 IsSerial_RX		    	    :1;				// 串口接受完成，申请解析事件标志位 	1 =申请串口数据解析 
		volatile u8 IsChangeWidth	  	    	:1; 			// 按摩宽度调整标志位 1 =申请宽度调整
		
		volatile u8 IsAuto_One	  				:1; 			// 自动按键1标志位 1 =申请自动模式1操作
		volatile u8 IsAuto_Two	  				:1; 			// 自动按键2标志位 1 =申请自动模式2操作
		volatile u8 IsAuto_Three	  			:1; 			// 自动按键3标志位 1 =申请自动模式3操作
		
		volatile u8 IsPerKne		    		:1; 			// 同时进行按摩和捶背 1 =申请同时按摩和捶背
		volatile u8 IsPer   		  			:1; 			// 进行捶背 1 =申请捶背
		volatile u8 IsKne   		  			:1; 			// 进行揉捏按摩 1 =申请揉捏按摩

		volatile u8 IsAutoBegin		    	    :1;			    // 自动模式下的计时判断
		volatile u8 IsStoping                   :1;             // 是否处于暂停

		
	}Bit ;
};

//
// 按摩相关数据结构
//
typedef struct 
{
	u8 	CycleUpDown;											// 上下圈数计数
	u8 	CycleKne;												// 揉捏圈数计数
	u16 AngleCount;												// 揉捏的角度计数
	u8  width_F;												// 揉背的宽度 
	u8  speed ;													// 揉捏按摩的调节 PWM波
	u8  autoNum	;												// 执行的自动状态编号
	u8  nowTime[2] ;								    		// 记录当前时间
	u8  DTime ;													// 时间间隔
}nt_Massage ;

//
// 定时结构体
//
typedef struct
{
	u8 Counter[3] ;												// 定时计数器
	u8 Sec ;													// 秒计数单位
	u8 Display ;												// 显示时间 （机器的工作时间，暂停时要停止累加）
}nt_Time ;

//
// 串口数据结构体
//

typedef struct
{
	u8 Res ;													// 串口接收到的值
	u8 action_N ;												// 动作编码
	
}nt_Serial ;

#endif

