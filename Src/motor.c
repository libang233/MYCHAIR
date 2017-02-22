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

// ������ �����е������������
// ����   ����
// ����ֵ ����
// ע��   : δ���� �˺�����ʱδ�����������䣬������մ�����Ȼδ��ӿ���䣬Ҳ���Խ��˴�������������
//void allMotorsGoOn(void)
//{
//	switch( mySerial.action_N )
//	{
//		case ATUO_ONE : 
//				myEvnt.Bit.IsAuto_One = true ;						// �����Զ�ģʽ1
//			break ;
//		
//		case ATUO_TWO : 
//				myEvnt.Bit.IsAuto_Two = true ;						// �����Զ�ģʽ2
//			break ;
//		
//		case ATUO_THREE : 
//				myEvnt.Bit.IsAuto_Three = true ;					// �����Զ�ģʽ3
//			break ;
//		
//		case PER_KNE :
//				myEvnt.Bit.IsPerKne = true ;		    			// ����ͬʱ��Ħ�ʹ���
//		    break ;
//		
//		case KNE :
//				myEvnt.Bit.IsKne = true ;							// ��������
//			break ;
//		
//		case PER :
//				myEvnt.Bit.IsPer = true ;							// ���봷��
//			break ;
//		
//		default : break ;
//	}
//}


// ������ ���������
// ����   ���� 
// ����ֵ ����
// ע��   : �ѵ���

void ChangeWidth(void)
{
    u8 Last_AngleCount;
    Last_AngleCount = myMassage.AngleCount ;
	
    if(Last_AngleCount<5)
    {
	     while( myMassage.AngleCount < Last_AngleCount + 3)
		 {
			CCAP0H = WiDTH_SPEED;
			CCAP0L = WiDTH_SPEED;
		 }
		
		CCAP0H = 0;
		CCAP0L = 0;
	}
	else
	{	
	    while( myMassage.AngleCount != 0)
	    {
			CCAP0H = WiDTH_SPEED ; 
			CCAP0L = WiDTH_SPEED ;
		}
		
	    CCAP0H = 0;
		CCAP0L = 0;
	}   
}

// ������ ���Զ�ģʽ1
// ����   ���� 
// ����ֵ ����

void auto_one(void)
{
    switch(myMassage.autoNum)
	{
	    case 0x00:
		     myEvnt.Bit.IsAllMotorsStop = true;
	 		 if(upCheck)
			 {
			     upm = 0;
			 }
			 else
			 {
			     upm = 1;
			     myMassage.autoNum = 0x01;
			 }
			 break;
         case 0x01:
		     if(dnCheck)
			 {
			     dnm = 0;
				 myMassage.speed = INIT_SPEED;
		         myEvnt.Bit.IsPer = true; 
			 }
			 else
			 {
			     dnm = 1;
				 myEvnt.Bit.IsAllMotorsStop = true;
				 myMassage.autoNum = 0x02;
			 }
		      
			 break; 
		 case 0x02 :
		     if( true == myEvnt.Bit.IsAutoBegin)
			 {
				 myEvnt.Bit.IsChangeWidth = true;
				 myMassage.nowTime[0] = myTime.Counter[2];
				 myMassage.nowTime[1] = myTime.Display;
				 myEvnt.Bit.IsAutoBegin = false;
			 }
			 else
			 {
			     myMassage.speed = HIGH_SPEED;
				 myEvnt.Bit.IsPer = true;
			     myMassage.DTime = myTime.Counter[2] - myMassage.nowTime[0] + ( myMassage.nowTime[1] - myTime.Display) * 60;
			     if( myMassage.DTime >= 5)
				 {
				     myEvnt.Bit.IsAllMotorsStop = true;
					 myEvnt.Bit.IsAutoBegin = true;
					 myMassage.autoNum = 0x03;
				 }
			     
			 }
			 break;

	     case 0x03:
		     if(upCheck)
			 {
			     upm = 0;   
			 }
			 else
			 {
				 myMassage.autoNum = 0x04;
			 }
			 break;
    }    
		       
}

// ������ ���Զ�ģʽ1
// ����   ���� 
// ����ֵ ����

void auto_two(void)
{
     switch(myMassage.autoNum)
	 {
	     case 0x00:

		     myMassage.CycleUpDown = 0;
			 myEvnt.Bit.IsAutoBegin = false;
			 dnm = 0;
			 myMassage.autoNum = 0x01;
			 break;

	     case 0x01:
		     
			 if( 10 <= myMassage.CycleUpDown)
			 {
			     dnm = 1;
			 }
			 break;

		 
			 
	 }
}


void reset(void)  
{
	
	if(upCheck)					         		// û�дﵽ��ˣ���ʼ����Ҫ�ﵽ���
	{
		upm = 0; 									// �����˶�ֱ������
		myEvnt.Bit.IsReset_F = true ;
	}
	else
	{
	    upm = 1;
		
	}


	
	
}


		