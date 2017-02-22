// 文件名 ：motor.h
// 作者   : 赵成华 陈统 何立邦
// 日期   : 2017年 2月 17日

#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "newtype.h"
#include "extern.h"
#include "Globle.h"
#include "STC12C5410AD.H"

/************************************** 函数公开 ********************************************/

void auto_one(void);
void auto_two(void);
//void auto_3(void);
void kne(void);
void per(void);
void per_kne(void);
void ChangeWidth(void);
void Init_PWM(void);
void allMotorsStop(void);
void Init_Motor(void);
//void allMotorsGoOn(void) ;
void reset(void);

#endif