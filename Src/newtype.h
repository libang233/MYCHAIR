// �ļ��� ��newtype.h
// ����   : �Գɻ� ��ͳ ������
// ����   : 2017�� 2�� 15��

#ifndef _NEWTYPE_H_
#define _NEWTYPE_H_

#include "STC12C5410AD.H"

typedef unsigned char u8;
typedef unsigned int  u16;
typedef unsigned long u32;

#define true  	1
#define false 	0
#define TRUE  	1
#define FALSE 	0

//
// �¼���־λ ������
//
union nt_uEVNT
{       	
	u8	ALL ;													// ���嶨�壬�������帳ֵ
	struct														// ����λ����
	{
		volatile u8 IsPOWER_OFF	  		    	:1; 			// �ػ���־λ 1 = ����ػ�
		volatile u8 IsReset_F	  				:1; 			// ���ñ�־λ 1 =��������
		volatile u8 IsAllMotorsStop			    :1;				// ���е��ֹͣ	1 =�������е��ֹͣ 
//		volatile u8 IsAllMotorsGoOn			    :1;				// ���е������	1 =�������е������ 
		volatile u8 IsSerial_RX		    	    :1;				// ���ڽ�����ɣ���������¼���־λ 	1 =���봮�����ݽ��� 
		volatile u8 IsChangeWidth	  	    	:1; 			// ��Ħ��ȵ�����־λ 1 =�����ȵ���
		
		volatile u8 IsAuto_One	  				:1; 			// �Զ�����1��־λ 1 =�����Զ�ģʽ1����
		volatile u8 IsAuto_Two	  				:1; 			// �Զ�����2��־λ 1 =�����Զ�ģʽ2����
		volatile u8 IsAuto_Three	  			:1; 			// �Զ�����3��־λ 1 =�����Զ�ģʽ3����
		
		volatile u8 IsPerKne		    		:1; 			// ͬʱ���а�Ħ�ʹ��� 1 =����ͬʱ��Ħ�ʹ���
		volatile u8 IsPer   		  			:1; 			// ���д��� 1 =���봷��
		volatile u8 IsKne   		  			:1; 			// ��������Ħ 1 =��������Ħ

		volatile u8 IsAutoBegin		    	    :1;			    // �Զ�ģʽ�µļ�ʱ�ж�
		volatile u8 IsStoping                   :1;             // �Ƿ�����ͣ

		
	}Bit ;
};

//
// ��Ħ������ݽṹ
//
typedef struct 
{
	u8 	CycleUpDown;											// ����Ȧ������
	u8 	CycleKne;												// ����Ȧ������
	u16 AngleCount;												// ����ĽǶȼ���
	u8  width_F;												// �౳�Ŀ�� 
	u8  speed ;													// ����Ħ�ĵ��� PWM��
	u8  autoNum	;												// ִ�е��Զ�״̬���
	u8  nowTime[2] ;								    		// ��¼��ǰʱ��
	u8  DTime ;													// ʱ����
}nt_Massage ;

//
// ��ʱ�ṹ��
//
typedef struct
{
	u8 Counter[3] ;												// ��ʱ������
	u8 Sec ;													// �������λ
	u8 Display ;												// ��ʾʱ�� �������Ĺ���ʱ�䣬��ͣʱҪֹͣ�ۼӣ�
}nt_Time ;

//
// �������ݽṹ��
//

typedef struct
{
	u8 Res ;													// ���ڽ��յ���ֵ
	u8 action_N ;												// ��������
	
}nt_Serial ;

#endif

