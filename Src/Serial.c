// 文件名 ：Serial.c
// 作者   : 赵成华 陈统 何立邦
// 日期   : 2017年 2月 15日

#include "Serial.h"


// 函数名 ：串口初始化函数
// 参数   ：无 
// 返回值 ：无
// 注释   : 需要参考手册 上机需要检测

void Init_Serial(void)
{	
	ES = 0 ;										// 关闭串口中断
	
	TMOD = 0X21;     								// 设为定时器T1工作方式2(用于串口通讯),定时器T0方式1
	TH1  = 0XFD;      								// 波特率设为9600
	TL1  = 0XFD;      
	TR1  = 1;         								// 打开定时器1
	SCON = 0X50;     								// 设为串口工作方式1
	
	ES = 1;	        								// 开串口中断
}	

// 函数名 ：串口中断函数
// 参数   ：无 
// 返回值 ：无
// 注释   : 把接收到的数据存放到全局变量

void Serial() interrupt 4  									// 接收中断服务程序
{

	RI = 0;                    								// 接收标记位清零
	mySerial.Res = SBUF;									// 串口接收完成，将串口接收到的值存放在串口接收数据结构

	myEvnt.Bit.IsSerial_RX = true;							// 串口接收完成，申请数据处理
}


// 函数名 ：串口解析函数
// 参数   ：无 
// 返回值 ：无
// 注释   : 需要参考手册 上机需要检测

void SerialAnalysis (void)
{
	u8 i;													
	
    switch( mySerial.Res )      										// 判断串口数据值
	{
		case 0xAA :														// 定时接收到手控板串口指令
				ES = 0;
				for(i=0;i<7;i++)
				{
					SBUF = SendMsg[i];									// 7位数据串口应答发送
					while( !TI );
						TI=0;
				}
				ES = 1;
			break;
	
		case 0X03 :														// 接收到开机键按钮
				if( !(SendMsg[0] & 0x01) ) 								// 目前关机状态收到开机指令
				{		
					SendMsg[0] = SendMsg[0] | 0x01 ;
					myEvnt.Bit.IsReset_F = true ;          				// 申请重置
				}
				else
				{
					SendMsg[0] = SendMsg[0] & (~0x01) ;					// 第二次按开机键申请关机
					myEvnt.Bit.IsPOWER_OFF = true ;
				}
		
		case 0x01 :														// 接收到定时按键
				if( SendMsg[3] == 0x1E)
				{
					SendMsg[3] = 0x0A;
				}
				else if(SendMsg[3] == 0x0A)
				{			
					SendMsg[3]=0x14;
				}
				else 
				{
					SendMsg[3]=0x1E;
				}
			break;																
		
		case 0x02 : 													// PAUSE暂停
				if(SendMsg[1] & 0x01)									
				{														// 第二次按下暂停键 恢复工作
					SendMsg[1] = SendMsg[1] & 0xF0;
					myEvnt.Bit.IsStoping = false ;
					switch(mySerial.action_N)
					{
					 		case PER_KNE :
				                    myEvnt.Bit.IsPerKne = true ;		    			// 申请同时按摩和捶背
							    break ;
							
							case KNE :
									myEvnt.Bit.IsKne = true ;							// 申请揉捏
								break ;
							
							case PER :
									myEvnt.Bit.IsPer = true ;							// 申请捶背
								break ;
							
							default : break ;
					}
					
				}
				else													// 第一次按下暂停键
				{
				    SendMsg[1] = SendMsg[1] & 0xF0 | 0x01;
					myEvnt.Bit.IsStoping = true ;
					myEvnt.Bit.IsAllMotorsStop = true ;					// 申请所有电机停止工作					
					

				}
				
			break;  														
		
		case 0x04 : 
					SendMsg[0]=SendMsg[0] & 0xF0 | 0x09;				// vibratig 按摩椅震动
			break;  													
		
		case 0x05 : 													// neck&shouder改成auto_2
//					SendMsg[0]=SendMsg[0] & 0x0F | 0x20 ;
//					SendMsg[1]=SendMsg[1] & 0x00 ;

					if(false == myEvnt.Bit.IsAuto_Two)
					{  			
				     	SendMsg[0]=SendMsg[0] & 0x0F | 0x20 ;
				    	SendMsg[1]=SendMsg[1] & 0x00 ;
					    mySerial.action_N = ATUO_TWO;					// 动作编号2
						myEvnt.Bit.IsAutoBegin = true ;					// 初始化计时判断
						myEvnt.Bit.IsAuto_Two = true ;		  		    // 申请自动模式2							
						myMassage.autoNum = 0x00;						// 初始化自动状态编号
					    myEvnt.Bit.IsAuto_One = false ;		  		    
						myEvnt.Bit.IsAuto_Three = false ;
						myEvnt.Bit.IsStoping = false ;	
					}
					else
					{
					    SendMsg[0] = SendMsg[0] & 0xDF;
					    myEvnt.Bit.IsAuto_Two = false;					// 申请关闭自动模式2
						myEvnt.Bit.IsStoping = true ;
					}
					myEvnt.Bit.IsAllMotorsStop = true ;					// 申请所有电机停止工作
			break;  													

		case 0x06 : 
					SendMsg[0]=SendMsg[0] & 0x0F | 0x10;				// back&waist改成auto_3
					SendMsg[1]=SendMsg[1] & 0x00 ;
					
					myEvnt.Bit.IsAllMotorsStop  = true ;				// 申请所有电机停止工作
					myEvnt.Bit.IsAuto_Three = true ;					// 申请自动模式3
					mySerial.action_N = ATUO_THREE;						// 动作编号3		
			break;  
	
		case 0x07 : 													// pause改成auto_1
//					SendMsg[0] = SendMsg[0] & 0x0F;
					
					if(false == myEvnt.Bit.IsAuto_One)
					{  			
					    SendMsg[1] = SendMsg[1] & 0x00 | 0x40;
				    	SendMsg[0] = SendMsg[0] & 0x0F;
					    mySerial.action_N = ATUO_ONE;					// 动作编号1
						myMassage.autoNum = 0x00;						// 初始化自动状态编号
						myEvnt.Bit.IsAutoBegin = true ;					// 初始化计时判断
						myEvnt.Bit.IsAuto_One = true ;		  		    // 申请自动模式1
						myEvnt.Bit.IsAuto_Two = false ;		  		    
						myEvnt.Bit.IsAuto_Three = false ;
						myEvnt.Bit.IsStoping = false ;		  		
	
					}
					else
					{
					    SendMsg[1] = SendMsg[1] & 0x00;
					    myEvnt.Bit.IsAuto_One = false ;					// 申请关闭自动模式1
					    myEvnt.Bit.IsStoping = true ;
					}
					myEvnt.Bit.IsAllMotorsStop = true ;					// 申请所有电机停止工作

			break;  
		
		case 0x09 :													    // 捶背percussion
					SendMsg[1] = SendMsg[1] & 0x00;
					SendMsg[0] = SendMsg[0] & 0x0F | 0x80;
					myEvnt.ALL = 0;
					myEvnt.Bit.IsAllMotorsStop = true ;					// 申请所有电机停止工作		
					myEvnt.Bit.IsPer = true ;							// 申请捶背
					myEvnt.Bit.IsStoping = false ;
					
					mySerial.action_N = PER ;
			break;  
		
		case 0x0A : 													// percussion+knead	捶背和按摩
					SendMsg[0] = SendMsg[0] & 0x0F;
					SendMsg[1] = SendMsg[1] & 0x00 | 0x02;
					myEvnt.ALL = 0;
					myEvnt.Bit.IsAllMotorsStop = true ;					// 申请所有电机停止工作
					myEvnt.Bit.IsPerKne = true ;		    			// 申请同时按摩和捶背
					myEvnt.Bit.IsStoping = false ;
						
					mySerial.action_N = PER_KNE;
			
			break; 
		
		case 0x0B :														// 速度调整按键 
					if( myMassage.speed < MAX_SPEED )
					{		
						if( myMassage.speed <= HIGH_SPEED )
						{
							myMassage.speed = myMassage.speed + ADD_SPEED;
						}
						else
						{
						 	myMassage.speed = INIT_SPEED ;
						} 	
					}
					else
					{
						myMassage.speed = INIT_SPEED ;
					}
					switch(mySerial.action_N)
					{
					 		case PER_KNE :
				                    myEvnt.Bit.IsPerKne = true ;		    			// 申请同时按摩和捶背
							    break ;
							
							case KNE :
									myEvnt.Bit.IsKne = true ;							// 申请揉捏
								break ;
							
							case PER :
									myEvnt.Bit.IsPer = true ;							// 申请捶背
								break ;
							
							default : break ;
					}

					
			break;  
									
		case 0x0C : 													// seat向前移动     //0C AA... 0C 1E
					seatm_up =0  ;
					seatm_dn =1  ;					
			break;  													
		
		case 0X0D : 													// kneading 按摩揉捏
					SendMsg[1] = SendMsg[1] & 0x00;
					SendMsg[0] = SendMsg[0] & 0x0F | 0x40;
					myEvnt.ALL =0;
					myEvnt.Bit.IsAllMotorsStop = true;					// 申请所有电机停止工作
		     		myEvnt.Bit.IsKne =  true;						    // 申请揉捏
					mySerial.action_N = KNE ;
					myEvnt.Bit.IsStoping = false ;	 
			break;  
		
		case 0x0E : 																// 申请按摩宽度调整
					myEvnt.Bit.IsChangeWidth = true ;											
			break;  																
		
		case 0x0F : 
					if(upCheck && (ATUO_ONE != mySerial.action_N || ATUO_TWO != mySerial.action_N || ATUO_THREE != mySerial.action_N))
				 	{
					 	upm=0;
					}
			
			break; 																	// upper 上升       // 0F AA... 0F 1F 
		
		case 0x10 : 
					seatm_up =1  ;
					seatm_dn =0  ;
			break;  																// seat向后移动     // 10 AA... 10 20 
		
		case 0x11 : 
					backm_up  =0 ;
					backm_dn  =1 ;
			break; 																	// back向后移动     // 11 AA... 11 21
		
		case 0x12 : 
					backm_up  =1 ;
					backm_dn  =0 ;
			break;  																// back向前移动     // 12 AA... 12 22 
		
		case 0x13 :
					if(dnCheck && (ATUO_ONE != mySerial.action_N || ATUO_TWO != mySerial.action_N || ATUO_THREE != mySerial.action_N))
					{
					    dnm=0;
					} 		
			break; 																	// lower下降        // 13 AA... 13 23
		case 0x1E : 
					seatm_up =1  ;
					seatm_dn =1;
			break;  //
		case 0x1F : 
					upm=1;
			break;  //
		case 0x20 : 
					seatm_up =1  ;
					seatm_dn =1;
			break;  //
		case 0x21 :	
					backm_up =1 ;
					backm_dn =1 ;
			break;  //
		case 0x22 :	
					backm_up =1 ;
					backm_dn =1 ;
			break;  //
		case 0x23 : 
					dnm=1;
			break;  //
		
		default : break ;
		}
}




