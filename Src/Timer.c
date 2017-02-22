// �ļ��� ��Timer.c
// ����   : �Գɻ� ��ͳ ������
// ����   : 2017�� 2�� 15��

#include "Timer.h"

// ������ ����ʱ����ʼ������
// ����   ���� 
// ����ֵ ����
// ע��   : Ϊ�ο��ֲ� �ϻ���Ҫ���

void Init_Timer (void)
{
	EA = 0; 										// �ر����ж�	
	
	TH0 = TIMER0_ORG;      							// ����ʱ��0װ��ֵ��11.0594M����ʱʱ��Ϊ62.5ms
	TL0 = 0X00;
	TR0 = 1;         								// ���ն�ʱ��0
	ET0 = 1;         								// ����ʱ��0�ж�
	
	IT0 = 1;         								// �½��ش���
	IT1 = 1;         								// �½��ش���
	EX0 = 1;         								// ���ⲿ�ж�0
	EX1 = 1;         								// ���ⲿ�ж�1
	
	EA = 1;          								// �����ж�
}

// ������ ����ʱ��0�жϺ���
// ����   ���� 
// ����ֵ ����
// ע��   : ��

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
	TH0 = TIMER0_ORG;      							// ����ʱ��0װ��ֵ��11.0594M����ʱʱ��Ϊ62.5ms
	TL0 = 0X00;
	
	// ��ʱ��0������ 
	myTime.Counter[0] ++ ;							// ι����ʱ��
	myTime.Counter[1] ++ ;							// ���ʱ��
	
	if( TIME_DOG == myTime.Counter[0] )				// ������Ϊ��ֵ��ߴ�����ݴ���
	{
		WDT_CONTR = 0x3c;							// 250msι��
		myTime.Counter[0]=0;										
	}
	
	if( TIME_SEC == myTime.Counter[1] )				// �����ʱ�� 62.5ms
	{
		myTime.Counter[1] = 0 ;	
		myTime.Counter[2] ++ ;						// �����������
		
		// �˴���������1���¼�
	}
	
	if( TIME_MIN == myTime.Counter[2] )				
	{
		myTime.Counter[2] = 0 ;	
		// �˴���������1�����¼�									
		if( 0 == (SendMsg[1] & 0x01) )				    // û�а�����ͣ��ʱ�򣬵���ʱ			
		{	
			myTime.Display -- ;						// һ���ӵ���ʱ	
		}
		
		if( 0 == myTime.Display )
		{
			myEvnt.Bit.IsPOWER_OFF = true ; 	   	// ����ػ� 
 		}
	}
	
}

// ������ ���ⲿ�ж�0����
// ����   ���� 
// ����ֵ ����
// ע��   : ��

void ext0() interrupt 0 
{
	myMassage.CycleUpDown ++ ;
}


// ������ ���ⲿ�ж�1����
// ����   ���� 
// ����ֵ ����
// ע��   : ��
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

