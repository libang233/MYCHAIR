// �ļ��� ��Serial.c
// ����   : �Գɻ� ��ͳ ������
// ����   : 2017�� 2�� 15��

#include "Serial.h"


// ������ �����ڳ�ʼ������
// ����   ���� 
// ����ֵ ����
// ע��   : ��Ҫ�ο��ֲ� �ϻ���Ҫ���

void Init_Serial(void)
{	
	ES = 0 ;										// �رմ����ж�
	
	TMOD = 0X21;     								// ��Ϊ��ʱ��T1������ʽ2(���ڴ���ͨѶ),��ʱ��T0��ʽ1
	TH1  = 0XFD;      								// ��������Ϊ9600
	TL1  = 0XFD;      
	TR1  = 1;         								// �򿪶�ʱ��1
	SCON = 0X50;     								// ��Ϊ���ڹ�����ʽ1
	
	ES = 1;	        								// �������ж�
}	

// ������ �������жϺ���
// ����   ���� 
// ����ֵ ����
// ע��   : �ѽ��յ������ݴ�ŵ�ȫ�ֱ���

void Serial() interrupt 4  									// �����жϷ������
{

	RI = 0;                    								// ���ձ��λ����
	mySerial.Res = SBUF;										// ���ڽ�����ɣ������ڽ��յ���ֵ����ڴ��ڽ������ݽṹ

	myEvnt.Bit.IsSerial_RX = true;							// ���ڽ�����ɣ��������ݴ���
}


// ������ �����ڽ�������
// ����   ���� 
// ����ֵ ����
// ע��   : ��Ҫ�ο��ֲ� �ϻ���Ҫ���

void SerialAnalysis (void)
{
	u8 i;													
	
    switch( mySerial.Res )      										// �жϴ�������ֵ
	{
		case 0xAA :														// ��ʱ���յ��ֿذ崮��ָ��
				ES = 0;
				for(i=0;i<7;i++)
				{
					SBUF = SendMsg[i];									// 7λ���ݴ���Ӧ����
					while( !TI );
						TI=0;
				}
						ES = 1;
			break;
	
		case 0X03 :														// ���յ���������ť
				if( !(SendMsg[0] & 0x01) ) 								// Ŀǰ�ػ�״̬�յ�����ָ��
				{		
					SendMsg[0] = SendMsg[0] | 0x01 ;		
				}
				else
				{
					SendMsg[0] = SendMsg[0] & (~0x01) ;
				}
				mySerial.action_N = 0x00;
				myEvnt.Bit.IsReset_F = true ;          					// ��������	
			break;	
		
		case 0x01 :														// ���յ���ʱ����
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
		
		case 0x02 : 													// PAUSE��ͣ
				if(SendMsg[1] & 0x01)
				{
                    SendMsg[1] = SendMsg[1] & 0xF0;
					myEvnt.Bit.IsChange = true ;
				}
				else
				{
                    SendMsg[1] = SendMsg[1] & 0xF0 | 0x01;
					
				}
				myEvnt.Bit.IsAllMotorsStop = true ;					// �������е��ֹͣ����
			break;  														
		
		case 0x04 : 
					SendMsg[0]=SendMsg[0] & 0xF0 | 0x09;				// vibratig ��Ħ����
			break;  													
		
		case 0x05 : 													// neck&shouder�ĳ�auto_2
					SendMsg[0]=SendMsg[0] & 0x0F | 0x20 ;
					SendMsg[1]=SendMsg[1] & 0x00 ;
					
					myEvnt.Bit.IsAllMotorsStop = true ;					// �������е��ֹͣ����
					myEvnt.Bit.IsAuto_Two = true ;						// �����Զ�ģʽ2
					mySerial.action_N = 0x02;							// �������2
					
					myMassage.CycleKne = 0 ;							// ����Ȧ����������
					myMassage.AngleCount = 0 ; 							// ����Ƕȼ�������
			break;  													

		case 0x06 : 
					SendMsg[0]=SendMsg[0] & 0x0F | 0x10;				// back&waist�ĳ�auto_3
					SendMsg[1]=SendMsg[1] & 0x00 ;
					
					myEvnt.Bit.IsAllMotorsStop = true ;					// �������е��ֹͣ����
					myEvnt.Bit.IsAuto_Three = true ;					// �����Զ�ģʽ3
					mySerial.action_N = 0x03;							// �������3		
			break;  
	
		case 0x07 : 													// pause�ĳ�auto_1
					SendMsg[1] = SendMsg[1] & 0x00 | 0x40;
					SendMsg[0] = SendMsg[0] & 0x0F;
					
					myEvnt.Bit.IsAllMotorsStop = true ;					// �������е��ֹͣ����
					myEvnt.Bit.IsAuto_One = true ;						// �����Զ�ģʽ1
					mySerial.action_N = 0x01;							// �������1
			break;  
		
		case 0x09 :													    // ����percussion
					SendMsg[1] = SendMsg[1] & 0x00;
					SendMsg[0] = SendMsg[0] & 0x0F | 0x80;
		
					myEvnt.Bit.IsAllMotorsStop = true ;					// �������е��ֹͣ����		
					myEvnt.Bit.IsPer = true ;							// ���봷��
					
					mySerial.action_N = 0x06;
			break;  
		
		case 0x0A : 													// percussion+knead	�����Ͱ�Ħ
					SendMsg[0] = SendMsg[0] & 0x0F;
					SendMsg[1] = SendMsg[1] & 0x00 | 0x02;
					
					myEvnt.Bit.IsAllMotorsStop = true ;					// �������е��ֹͣ����
					myEvnt.Bit.IsPerKne = true ;		    			// ����ͬʱ��Ħ�ʹ���
						
					mySerial.action_N = 0x04;
			
			break; 
		
		case 0x0B :														// �ٶȵ������� 
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
					
					myEvnt.Bit.IsChange = true ;
					
			break;  
									
		case 0x0C : 
					seatm_up =0  ;
					seatm_dn =1  ;					
			break;  													// seat��ǰ�ƶ�     //0C AA... 0C 1E
		
		case 0X0D : 													// kneading ��Ħ����
					SendMsg[1] = SendMsg[1] & 0x00;
					SendMsg[0] = SendMsg[0] & 0x0F | 0x40;
				
					myEvnt.Bit.IsAllMotorsStop = true;					// �������е��ֹͣ����
		     		myEvnt.Bit.IsKne =  true;													 // ��������
					mySerial.action_N=0x05;	 
			break;  
		
		case 0x0E : 																// ���밴Ħ��ȵ���
					myEvnt.Bit.IsChangeWidth = true ;											
			break;  																
		
		case 0x0F : 
					if(upCheck)
				 	{
					 	upm=0;
					}
			
			break; 																	// upper ����       // 0F AA... 0F 1F 
		
		case 0x10 : 
					seatm_up =1  ;
					seatm_dn =0  ;
			break;  																// seat����ƶ�     // 10 AA... 10 20 
		
		case 0x11 : 
					backm_up  =0 ;
					backm_dn  =1 ;
			break; 																	// back����ƶ�     // 11 AA... 11 21
		
		case 0x12 : 
					backm_up  =1 ;
					backm_dn  =0 ;
			break;  																// back��ǰ�ƶ�     // 12 AA... 12 22 
		
		case 0x13 :
					if(dnCheck)
					{
					    dnm=0;
					} 		
			break; 																	// lower�½�        // 13 AA... 13 23
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




