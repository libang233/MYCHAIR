// 文件名 ：newtype.h
// 作者   : 赵成华 陈统 何立邦
// 日期   : 2017年 2月 15日

#ifndef _EXTERN_H_
#define _EXTERN_H_
/************************************外部全局变量声明****************************************/
// 全局变量声明 在 main.c

	extern union   nt_uEVNT   	myEvnt ;                            // 事件标志位别名 全局
	extern   nt_Time 			myTime;													// 定时结构体别名 全局
	extern   nt_Serial			mySerial;							// 串口数据结构体 全局
	extern   nt_Massage		    myMassage ;							// 按摩相关数据结构 全局
  
  extern   u8 SendMsg[7];												// 串口数据	
#endif