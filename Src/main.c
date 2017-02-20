// 文件名 ：main.c
// 作者   : 赵成华 陈统 何立邦
// 日期   : 2017年 2月 15日

#include "STC12C5410AD.H"
#include "newtype.h"
#include "Globle.h"
#include "motor.h"	
#include "Serial.h"
#include "string.h"
#include "Timer.h"

union nt_uEVNT   myEvnt ;                                	// 事件标志位别名 全局
nt_Massage		 myMassage ;								// 按摩相关数据结构 全局
nt_Serial		 mySerial ;									// 串口的数据结构  全局
nt_Time          myTime ;									// 定时器数据结构  全局

u8 SendMsg[] = {0x00,0x00,0x78,0x1E,0X00,0x00,0xBB} ;		// 串口数据

// 函数名 ：全局变量初始化函数
// 参数   ：无 
// 返回值 ：无
// 注释   : 无 

void Reset_Global(void)					
{
	myEvnt.ALL =0;											// myEvnt内所有标志初始化
	memset( &mySerial ,0 ,sizeof(mySerial)) ;				// mySerial 内所有标志初始化
	memset( &myMassage ,0 ,sizeof(myMassage)) ;				// myMassage 内所有标志初始化
	memset( &myTime ,0 ,sizeof(myTime)) ;					// myTime 内所有标志初始化
	
    SendMsg[0] = SendMsg[0] & 0x01;
	SendMsg[1] = 0x00;
	SendMsg[2] = 0x78;
	SendMsg[3] = 0x1E;			                          	// 串口数据初始化		
}

// 函数名 ：系统始化函数
// 参数   ：无 
// 返回值 ：无
// 注释   : 无
void SysInit(void)
{
	WDT_CONTR = 0x3c;									    	// 开机喂狗
	
	Init_Serial() ;										    	// 串口初始化
	Init_Timer();												// 定时器初始化
	Init_Motor();												// 电机初始化
    Init_PWM() ;												// PWM波初始化
	
	myMassage.speed = INIT_SPEED ;		                      	// 电机速度初始化
}

// 函数名 ：主函数
// 参数   ：无 
// 返回值 ：无
// 注释   : 无

void main (void)										
{
	
	myEvnt.Bit.IsReset_F = true ;										// 申请开机重置
	
	while (1)
	{
		if( true == myEvnt.Bit.IsReset_F )								// 开始重置
		{
			myEvnt.Bit.IsReset_F = false ;	
	    	Reset_Global() ;
            SysInit();// 正确位置判断未加入
		}

		if( true == myEvnt.Bit.IsSerial_RX )							// 开始串口处理
		{
			myEvnt.Bit.IsSerial_RX = false ;
			SerialAnalysis() ;											// 串口数据处理
		}
	
		if( true == myEvnt.Bit.IsAllMotorsStop)			            	// 所有电机停止处理
		{
			myEvnt.Bit.IsAllMotorsStop = false ;
			allMotorsStop() ;											// 所有电机停止工作
		}
		
		if( true == myEvnt.Bit.IsChangeWidth && 0x06 == mySerial.action_N )				                                    // 申请拍打宽度调整
		{
			myEvnt.Bit.IsChangeWidth = false ;
			changeWidth();		
		}
		
		if( true == myEvnt.Bit.IsPer || ( 0x06 == mySerial.action_N && true == myEvnt.Bit.IsChange )) 	   		     	    // 申请拍打敲背
		{																													 
			myEvnt.Bit.IsPer = false ;
			myEvnt.Bit.IsChange = false ;					
			per();				
		}
		
		if( true == myEvnt.Bit.IsKne || ( 0x05 == mySerial.action_N && true == myEvnt.Bit.IsChange )) 			 		    // 申请揉捏按摩
		{
			myEvnt.Bit.IsKne = false ;
			myEvnt.Bit.IsChange = false ; 						
			kne() ;				
		}
		
		if( true == myEvnt.Bit.IsPerKne || ( 0x04 == mySerial.action_N && true == myEvnt.Bit.IsChange )) 				// 申请揉捏按摩和拍打敲背
		{
			myEvnt.Bit.IsPerKne = false ;
			myEvnt.Bit.IsChange = false ;  						
			per_kne() ;				
		}
	}
}

