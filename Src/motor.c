// 文件名 ：motor.c
// 作者   : 赵成华 陈统 何立邦
// 日期   : 2017年 2月 17日

#include "motor.h"

// 函数名 ：pwm波初始化函数
// 参数   ：无 
// 返回值 ：无
// 注释   : 已调试

void Init_PWM(void)
{
		CCON = 0;                       								//Initial PCA control register
																		//PCA timer stop running
																		//Clear CF flag
																		//Clear all module interrupt flag
		CL = 0;                         								//Reset PCA base timer
		CH = 0;
		CMOD = 0x02;                    								//Set PCA timer clock source as Fosc/2
																		//Disable PCA timer overflow interrupt
		CCAP0H = CCAP0L = 0x00;         								//PWM0 port output 50% duty cycle square wave
		CCAPM0 = 0x42;                  								//PCA module-0 work in 8-bit PWM mode and no PCA interrupt

		CCAP2H = CCAP2L = 0x00;         								//PWM1 port output 0% duty cycle square wave
		CCAPM2 = 0x42;                  								//PCA module-1 work in 8-bit PWM mode and no PCA interrupt

		CR = 1;                         								//PCA timer start run
}

// 函数名 ：电机初始化函数
// 参数   ：无 
// 返回值 ：无
// 注释   : 已调试

void Init_Motor(void)  
{
	myMassage.speed = 55 ;   								// 开机初始化电机pwm值			
}

// 函数名 ：揉捏函数
// 参数   ：无 
// 返回值 ：无
// 注释   : 已调试

void kne(void)
{
	SendMsg[0] = SendMsg[0] | 0x40;
	SendMsg[0] = SendMsg[0] & ~0x80;
	SendMsg[1] = SendMsg[1] & ~0x02;
	
	CCAP0H = myMassage.speed ;
	CCAP0L = myMassage.speed ;
	CCAP2H = 0 ;
	CCAP2L = 0 ;
}

// 函数名 ：捶背敲打函数
// 参数   ：无 
// 返回值 ：无
// 注释   : 已调试

void per()
{
	SendMsg[0] = SendMsg[0] | 0x80;
	SendMsg[0] = SendMsg[0] & ~0x40;
	SendMsg[1] = SendMsg[1] & ~0x02;
	CCAP2H = myMassage.speed - DIFFERENT_SPEED ;
	CCAP2L = myMassage.speed - DIFFERENT_SPEED ;
	CCAP0H = 0;
	CCAP0L = 0 ;
}

// 函数名 ：揉拍函数
// 参数   ：无 
// 返回值 ：无
// 注释   : 已调试

void per_kne()
{
	SendMsg[1] = SendMsg[1] | 0x02;
	SendMsg[0] = SendMsg[0] & ~0x80;
	SendMsg[0] = SendMsg[0] & ~0x40;
	CCAP2H = myMassage.speed ;
	CCAP2L = myMassage.speed ;
	CCAP0H = myMassage.speed ;
	CCAP0L = myMassage.speed ;
}

// 函数名 ：所有电机都停止
// 参数   ：所需要的实时速度 
// 返回值 ：无
// 注释   : 已调试

void allMotorsStop(void)
{
	CCAP0H = 0x00 ;
	CCAP0L = 0x00 ;
	CCAP2H = 0x00 ;
	CCAP2L = 0x00 ;
	backm_up  = 1 ;
	backm_dn  = 1 ;
	upm=1;
	dnm=1;
	// sec=0;
}

// 函数名 ：调整宽度
// 参数   ：无 
// 返回值 ：无
// 注释   : 已调试

void changeWidth(void)
{
    u8 i1;
    i1 = myMassage.AngleCount ;
    if(i1<5)
    {
	     while( myMassage.AngleCount < i1 + 3)
		 CCAP0H = CCAP0L= myMassage.speed;
		 CCAP0H = CCAP0L=0;
	}
	else
	{	
	    while( myMassage.AngleCount != 0)
	    CCAP0H = CCAP0L= WiDTH_SPEED;
	    CCAP0H = CCAP0L=0;
	}   
}

// 函数名 ：自动模式1
// 参数   ：无 
// 返回值 ：无

void auto_1(void)
{
       
}

//void handle(void)
//{
//   	   if(reset_F)
//			reset();
//		else if(SendMsg[0] & 0x01 && !(SendMsg[1] & 0x01))    //开启电源且未暂停
//		{
//       if(action_N==0x01)
//					auto_1();	
//			 if(action_N==0x02)
//					auto_2();	
//			 if(action_N==0x03)
//					auto_3();	
//			 if(action_N==0x04)
//					per_kne(speed);	
//			 if(action_N==0x05)
//					kne(speed);	
//			 if(action_N==0x06)
//					per(speed);	
//			 if(action_N==0x06 && width_F)    //width宽度调整按钮按下
//			 { 
//				u8 i1;
//				 width_F=0;
//				 i1=mdb;
//				 if( i1 <5)
//				 {
//					 while(mdb<i1+3)
//					 CCAP0H = CCAP0L=speed;
//					 CCAP0H = CCAP0L=0;
//				 }
//				 else
//				 {	while(mdb!=0)
//					 CCAP0H = CCAP0L=speed;
//					 CCAP0H = CCAP0L=0;
//				 }
//							
//				}
//					 
//		}	
//		if(SendMsg[1] & 0x01)  //暂停
//			allMotorsStop();
//}

//void reset(void)  //重置
//{
//	allMotorsStop();
//	init();
//	reset_F=0;
//}


		