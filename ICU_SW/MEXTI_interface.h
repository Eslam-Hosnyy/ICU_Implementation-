/************************************/
/*	Author	  :	ESLAM_HOSNY			*/
/*	SWC		  : EXTI				*/
/*  Layer	  : MCAL				*/
/*	Version	  :	1.1		  			*/
/*	Date	  :	November 21, 2022	*/
/************************************/

#ifndef _MEXTI_INTERFACE_H_
#define _MEXTI_INTERFACE_H_

#define MEXTI_INT0	6
#define MEXTI_INT1	7
#define MEXTI_INT2	5

#define MEXTI_MODE_LOW		0
#define MEXTI_MODE_IOC		1
#define MEXTI_MODE_FALLING	2
#define MEXTI_MODE_RISING	3

void MEXTI_voidInit(u8 ARG_u8InterruptNo, u8 ARG_u8InterruptMode);

void MEXTI_voidEnableInterrupt(u8 ARG_u8InterruptNo);

void MEXTI_voidDisableInterrupt(u8 ARG_u8InterruptNo);

void MEXTI_voidSetCallBackINT0(void (*ARG_pvoidfUserFunctionINT0)(void));

void MEXTI_voidSetCallBackINT1(void (*ARG_pvoidfUserFunctionINT1)(void));

void MEXTI_voidSetCallBackINT2(void (*ARG_pvoidfUserFunctionINT2)(void));

#endif
