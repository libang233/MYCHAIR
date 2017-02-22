// 文件名 ：Timer.c
// 作者   : 赵成华 陈统 何立邦
// 日期   : 2017年 2月 15日

#include "Timer.h"

// 函数名 ：定时器初始化函数
// 参数   ：无 
// 返回值 ：无
// 注释   : 为参考手册 上机需要检测

void Init_Timer (void)
{
	EA = 0; 										// 关闭总中断	
	
	TH0 = TIMER0_ORG;      							// 给定时器0装初值，11.0594M晶振定时时间为62.5ms
	TL0 = 0X00;
	TR0 = 1;         								// 开闭定时器0
	ET0 = 1;         								// 开定时器0中断
	
	IT0 = 1;         								// 下降沿触发
	IT1 = 1;         								// 下降沿触发
	EX0 = 1;         								// 开外部中断0
	EX1 = 1;         								// 开外部中断1
	
	EA = 1;          								// 开总中断
}

// 函数名 ：定时器0中断函数
// 参数   ：无 
// 返回值 ：无
// 注释   : 无

void Timer0() interrupt 1 
{

	if(!upCheck)
	{
	 	upm=1;
	}
	if(!dnCheck)
	{
	    dnm=1;
	}    
	TH0 = TIMER0_ORG;      							// 给定时器0装初值，11.0594M晶振定时时间为62.5ms
	TL0 = 0X00;
	
	// 计时器0的意义 
	myTime.Counter[0] ++ ;							// 喂狗计时器
	myTime.Counter[1] ++ ;							// 秒计时器
	
	if( TIME_DOG == myTime.Counter[0] )				// 常量作为左值提高代码的容错性
	{
		WDT_CONTR = 0x3c;							// 250ms喂狗
		myTime.Counter[0]=0;										
	}
	
	if( TIME_SEC == myTime.Counter[1] )				// 毫秒计时器 62.5ms
	{
		myTime.Counter[1] = 0 ;	
		myTime.Counter[2] ++ ;						// 秒计数器计数
		
		// 此处可以申请1秒事件
	}
	
	if( TIME_MIN == myTime.Counter[2] )				
	{
		myTime.Counter[2] = 0 ;	
		// 此处可以申请1分钟事件									
		if( 0 == (SendMsg[1] & 0x01) )				    // 没有按下暂停的时候，倒计时			
		{	
			myTime.Display -- ;						// 一分钟倒计时	
		}
		
		if( 0 == myTime.Display )
		{
			myEvnt.Bit.IsPOWER_OFF = true ; 	   	// 申请关机 
 		}
	}
	
}

// 函数名 ：外部中断0函数
// 参数   ：无 
// 返回值 ：无
// 注释   : 无

void ext0() interrupt 0 
{
	myMassage.CycleUpDown ++ ;
}


// 函数名 ：外部中断1函数
// 参数   ：无 
// 返回值 ：无
// 注释   : 无
void ext1() interrupt 2 
{
	myMassage.AngleCount ++ ;
	
	if( 0 == mda_pin )
	{
		myMassage.CycleKne ++ ;
		myMassage.AngleCount = 0;
		//msg[3]--;
	}
}

