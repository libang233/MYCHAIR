// �ļ��� ��newtype.h
// ����   : �Գɻ� ��ͳ ������
// ����   : 2017�� 2�� 15��

#ifndef _EXTERN_H_
#define _EXTERN_H_
/************************************�ⲿȫ�ֱ�������****************************************/
// ȫ�ֱ������� �� main.c

	extern union   nt_uEVNT   	myEvnt ;                            // �¼���־λ���� ȫ��
	extern   nt_Time 			myTime;													// ��ʱ�ṹ����� ȫ��
	extern   nt_Serial			mySerial;							// �������ݽṹ�� ȫ��
	extern   nt_Massage		    myMassage ;							// ��Ħ������ݽṹ ȫ��
  
  extern   u8 SendMsg[7];												// ��������	
#endif