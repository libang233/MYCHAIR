// �ļ��� ��main.c
// ����   : �Գɻ� ��ͳ ������
// ����   : 2017�� 2�� 15��

#include "STC12C5410AD.H"
#include "newtype.h"
#include "Globle.h"
#include "motor.h"	
#include "Serial.h"
#include "string.h"
#include "Timer.h"

union nt_uEVNT   myEvnt ;                                	// �¼���־λ���� ȫ��
nt_Massage		 myMassage ;								// ��Ħ������ݽṹ ȫ��
nt_Serial		 mySerial ;									// ���ڵ����ݽṹ  ȫ��
nt_Time          myTime ;									// ��ʱ�����ݽṹ  ȫ��

u8 SendMsg[] = {0x00,0x00,0x78,0x1E,0X00,0x00,0xBB} ;		// ��������

// ������ ��ȫ�ֱ�����ʼ������
// ����   ���� 
// ����ֵ ����
// ע��   : �� 

void Reset_Global(void)					
{
	myEvnt.ALL =0;											// myEvnt�����б�־��ʼ��
	memset( &mySerial ,0 ,sizeof(mySerial)) ;				// mySerial �����б�־��ʼ��
	memset( &myMassage ,0 ,sizeof(myMassage)) ;				// myMassage �����б�־��ʼ��
	memset( &myTime ,0 ,sizeof(myTime)) ;					// myTime �����б�־��ʼ��
	
    SendMsg[0] = SendMsg[0] & 0x01;
	SendMsg[1] = 0x00;
	SendMsg[2] = 0x78;
	SendMsg[3] = 0x1E;			                          	// �������ݳ�ʼ��

	myTime.Display = SendMsg[3] ; 							// Ϊ��ʾʱ�丳��ֵ
}

// ������ ��ϵͳʼ������
// ����   ���� 
// ����ֵ ����
// ע��   : ��
void SysInit(void)
{
	WDT_CONTR = 0x3c;									    	// ����ι��
	
	Init_Serial() ;										    	// ���ڳ�ʼ��
	Init_Timer();												// ��ʱ����ʼ��
	Init_Motor();												// �����ʼ��
    Init_PWM() ;												// PWM����ʼ��
}

// ������ ��������
// ����   ���� 
// ����ֵ ����
// ע��   : ��

void main (void)										
{
	
	myEvnt.Bit.IsReset_F = true ;										// ���뿪������
	
	while (1)
	{	
		{																// �����:Ӳ���������
			while(!upCheck && !dnCheck)
			{
				allMotorsStop();
			}
			
			if (!upCheck)
				upm=1;
			if (!dnCheck)
				dnm=1;
		}
		
		if( true == myEvnt.Bit.IsPOWER_OFF ) 							// �ػ�
		{
			myEvnt.Bit.IsPOWER_OFF = false ;					
			allMotorsStop() ;
			myEvnt.Bit.IsStoping = true;
		}
		
		if( true == myEvnt.Bit.IsReset_F )								// ��ʼ����
		{
			myEvnt.Bit.IsReset_F = false ;	
	    	Reset_Global() ;
            SysInit() ;
			reset() ;													
		}

		if( true == myEvnt.Bit.IsSerial_RX )							// ��ʼ���ڴ���
		{
			myEvnt.Bit.IsSerial_RX = false ;
			SerialAnalysis() ;											// �������ݴ���
		}
	
		if( true == myEvnt.Bit.IsAllMotorsStop )			          	// ���е��ֹͣ����
		{
			myEvnt.Bit.IsAllMotorsStop = false ;
			allMotorsStop() ;											// ���е��ֹͣ����
		}
		
		
		if( true == myEvnt.Bit.IsChangeWidth )				            // �����Ĵ��ȵ���
		{
			myEvnt.Bit.IsChangeWidth = false ;
			ChangeWidth();		
		}
		
		if( true == myEvnt.Bit.IsPer && false == myEvnt.Bit.IsStoping ) 	   		     	   		// �����Ĵ��ñ�
		{																													 
			myEvnt.Bit.IsPer = false ;			
			per();				
		}
		
		if( true == myEvnt.Bit.IsKne && false == myEvnt.Bit.IsStoping ) 			 		    	// ��������Ħ
		{
			myEvnt.Bit.IsKne = false ;						
			kne() ;				
		}
		
		if( true == myEvnt.Bit.IsPerKne && false == myEvnt.Bit.IsStoping ) 							// ��������Ħ���Ĵ��ñ�
		{
			myEvnt.Bit.IsPerKne = false ;					
			per_kne() ;				
		} 
	    
        if( true == myEvnt.Bit.IsAuto_One && false == myEvnt.Bit.IsStoping )
		{																			
		   auto_one();												                                 //�����Զ�1
		}

		if( true == myEvnt.Bit.IsAuto_Two && false == myEvnt.Bit.IsStoping )
		{
		    auto_two();											                              		 //�����Զ�2
		}
				
//		SendMsg[3] = myTime.Display ;							                                     // ʱ��ˢ�·��͵���ʾʱ��
	}
}

