// �ļ��� ��Globle.h
// ����   : �Գɻ� �Գɻ� ��ͳ ������ ������
// ����   : 2017�� 2�� 15��

//#include "globle.h"

#ifndef _GLOBAL_H_
#define _GLOBAL_H_

//
//�����궨��
//
#define pe		0x00
#define kn	  	0x01
#define pk	  	0x02
#define up_dn   0x03
#define stop	0x00
#define up	    0x01
#define dn	    0x02

#define TIME_DOG  	4								// ���Ź�������
#define TIME_SEC    16							// 1�붨ʱ
#define TIME_MIN    60							// 1���Ӷ�ʱ
#define TIMER0_ORG  0x1F						// ��ʱ��0��ʼ��װ��ֵ

#define ADD_SPEED   50							// ÿ�ΰ������ӵ��ٶ�
#define INIT_SPEED	105							// �����Ĵ��ʼ���ٶ�
#define HIGH_SPEED	205							// �����Ĵ���ٶ�	
#define MAX_SPEED   255 						// ����ٶ�
#define WiDTH_SPEED 105                         // ��ȵ����ٶ�
#define DIFFERENT_SPEED 50					    //������Ĵ��ٶȲ�

//����˿�

sbit flapm     =P3^7;   //pwm
sbit kneadm    =P2^0;   //pwm
sbit backm_up  =P1^7;
sbit backm_dn  =P1^6;
sbit seatm_up  =P1^5;
sbit seatm_dn  =P1^4;
sbit upm       =P1^3;   //pwm
sbit dnm       =P1^2;   //pwm
sbit upCheck   =P2^4;
sbit dnCheck   =P2^5;
sbit mda_pin   =P3^4;
sbit mdb_pin   =P3^3;


#endif