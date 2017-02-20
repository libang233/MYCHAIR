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
	u16	ALL ;													// ���嶨�壬�������帳ֵ
	struct														// ����λ����
	{
		volatile u16 IsPOWER_OFF	  			:1; 			// �ػ���־λ 1 = ����ػ�
		volatile u16 IsReset_F	  				:1; 			// ���ñ�־λ 1 =��������
		volatile u16 IsAllMotorsStop			:1;				// ���е��ֹͣ	1 =�������е��ֹͣ 
		volatile u16 IsSerial_RX		    	:1;				// ���ڽ�����ɣ���������¼���־λ 	1 =���봮�����ݽ��� 
		volatile u16 IsChangeWidth	  	    	:1; 			// ��Ħ��ȵ�����־λ 1 =�����ȵ���
		
		volatile u16 IsAuto_One	  				:1; 			// �Զ�����1��־λ 1 =�����Զ�ģʽ1����
		volatile u16 IsAuto_Two	  				:1; 			// �Զ�����2��־λ 1 =�����Զ�ģʽ2����
		volatile u16 IsAuto_Three	  			:1; 			// �Զ�����3��־λ 1 =�����Զ�ģʽ3����
		
		volatile u16 IsPerKne		    		:1; 			// ͬʱ���а�Ħ�ʹ��� 1 =����ͬʱ��Ħ�ʹ���
		volatile u16 IsPer   		  			:1; 			// ���д��� 1 =���봷��
		volatile u16 IsKne   		  			:1; 			// ��������Ħ 1 =��������Ħ

		volatile u16 IsChange				:1;				//�ٶ��Ƿ����ı�
		
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
	u16 speed ;													// ����Ħ�ĵ��� PWM��
}nt_Massage ;

//
// ��ʱ�ṹ��
//
typedef struct
{
	u8 Counter[3] ;												// ��ʱ������
	u8 Sec ;															// �������λ
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

