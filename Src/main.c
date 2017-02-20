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
	
	myMassage.speed = INIT_SPEED ;		                      	// ����ٶȳ�ʼ��
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
		if( true == myEvnt.Bit.IsReset_F )								// ��ʼ����
		{
			myEvnt.Bit.IsReset_F = false ;	
	    	Reset_Global() ;
            SysInit();// ��ȷλ���ж�δ����
		}

		if( true == myEvnt.Bit.IsSerial_RX )							// ��ʼ���ڴ���
		{
			myEvnt.Bit.IsSerial_RX = false ;
			SerialAnalysis() ;											// �������ݴ���
		}
	
		if( true == myEvnt.Bit.IsAllMotorsStop)			            	// ���е��ֹͣ����
		{
			myEvnt.Bit.IsAllMotorsStop = false ;
			allMotorsStop() ;											// ���е��ֹͣ����
		}
		
		if( true == myEvnt.Bit.IsChangeWidth && 0x06 == mySerial.action_N )				                                    // �����Ĵ��ȵ���
		{
			myEvnt.Bit.IsChangeWidth = false ;
			changeWidth();		
		}
		
		if( true == myEvnt.Bit.IsPer || ( 0x06 == mySerial.action_N && true == myEvnt.Bit.IsChange )) 	   		     	    // �����Ĵ��ñ�
		{																													 
			myEvnt.Bit.IsPer = false ;
			myEvnt.Bit.IsChange = false ;					
			per();				
		}
		
		if( true == myEvnt.Bit.IsKne || ( 0x05 == mySerial.action_N && true == myEvnt.Bit.IsChange )) 			 		    // ��������Ħ
		{
			myEvnt.Bit.IsKne = false ;
			myEvnt.Bit.IsChange = false ; 						
			kne() ;				
		}
		
		if( true == myEvnt.Bit.IsPerKne || ( 0x04 == mySerial.action_N && true == myEvnt.Bit.IsChange )) 				// ��������Ħ���Ĵ��ñ�
		{
			myEvnt.Bit.IsPerKne = false ;
			myEvnt.Bit.IsChange = false ;  						
			per_kne() ;				
		}
	}
}

