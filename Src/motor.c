// �ļ��� ��motor.c
// ����   : �Գɻ� ��ͳ ������
// ����   : 2017�� 2�� 17��

#include "motor.h"

// ������ ��pwm����ʼ������
// ����   ���� 
// ����ֵ ����
// ע��   : �ѵ���

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

// ������ �������ʼ������
// ����   ���� 
// ����ֵ ����
// ע��   : �ѵ���

void Init_Motor(void)  
{
	myMassage.speed = 55 ;   								// ������ʼ�����pwmֵ			
}

// ������ ��������
// ����   ���� 
// ����ֵ ����
// ע��   : �ѵ���

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

// ������ �������ô���
// ����   ���� 
// ����ֵ ����
// ע��   : �ѵ���

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

// ������ �����ĺ���
// ����   ���� 
// ����ֵ ����
// ע��   : �ѵ���

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

// ������ �����е����ֹͣ
// ����   ������Ҫ��ʵʱ�ٶ� 
// ����ֵ ����
// ע��   : �ѵ���

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

// ������ ���������
// ����   ���� 
// ����ֵ ����
// ע��   : �ѵ���

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

// ������ ���Զ�ģʽ1
// ����   ���� 
// ����ֵ ����

void auto_1(void)
{
       
}

//void handle(void)
//{
//   	   if(reset_F)
//			reset();
//		else if(SendMsg[0] & 0x01 && !(SendMsg[1] & 0x01))    //������Դ��δ��ͣ
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
//			 if(action_N==0x06 && width_F)    //width��ȵ�����ť����
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
//		if(SendMsg[1] & 0x01)  //��ͣ
//			allMotorsStop();
//}

//void reset(void)  //����
//{
//	allMotorsStop();
//	init();
//	reset_F=0;
//}


		