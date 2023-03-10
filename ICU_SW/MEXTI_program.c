/************************************/
/*	Author	  :	ESLAM_HOSNY			*/
/*	SWC		  : EXTI				*/
/*  Layer	  : MCAL				*/
/*	Version	  :	1.1		  			*/
/*	Date	  :	November 21, 2022	*/
/************************************/
#include "LSTD_types.h"
#include "LBIT_math.h"
#include "MEXTI_private.h"
#include "MEXTI_interface.h"

void (*MEXTI_pvoidfUserFunctionINT0)(void) = NULL;
void (*MEXTI_pvoidfUserFunctionINT1)(void) = NULL;
void (*MEXTI_pvoidfUserFunctionINT2)(void) = NULL;

void MEXTI_voidInit(u8 ARG_u8InterruptNo, u8 ARG_u8InterruptMode)
{
	/* Set Sence Control for INT0  && Prepheral Interrupt Enable */
	switch(ARG_u8InterruptNo)
	{
		case MEXTI_INT0:
			{
				switch(ARG_u8InterruptMode)
				{
					case MEXTI_MODE_LOW:
						{
							CLEAR_BIT(MCUCR, ISC00);
							CLEAR_BIT(MCUCR, ISC01);
							break;
						}
					case MEXTI_MODE_IOC:
						{
							SET_BIT(MCUCR, ISC00);
							CLEAR_BIT(MCUCR, ISC01);
							break;
						}
					case MEXTI_MODE_FALLING:
						{
							CLEAR_BIT(MCUCR, ISC00);
							SET_BIT(MCUCR, ISC01);
							break;
						}
					case MEXTI_MODE_RISING:
						{
							SET_BIT(MCUCR, ISC00);
							SET_BIT(MCUCR, ISC01);
							break;
						}
				}
				break;
			}
			
		case MEXTI_INT1:
			{
				switch(ARG_u8InterruptMode)
				{
					case MEXTI_MODE_LOW:
						{
							CLEAR_BIT(MCUCR, ISC10);
							CLEAR_BIT(MCUCR, ISC11);
							break;
						}
					case MEXTI_MODE_IOC:
						{
							SET_BIT(MCUCR, ISC10);
							CLEAR_BIT(MCUCR, ISC11);
							break;
						}
					case MEXTI_MODE_FALLING:
						{
							CLEAR_BIT(MCUCR, ISC10);
							SET_BIT(MCUCR, ISC11);
							break;
						}
					case MEXTI_MODE_RISING:
						{
							SET_BIT(MCUCR, ISC10);
							SET_BIT(MCUCR, ISC11);
							break;
						}
				}
				break;
			}
		case MEXTI_INT2:
			{
				switch(ARG_u8InterruptMode)
				{
					case MEXTI_MODE_FALLING:
						{
							CLEAR_BIT(MCUCSR, ICS2);
							break;
						}
					case MEXTI_MODE_RISING:
						{
							SET_BIT(MCUCSR, ICS2);
							break;
						}
				}
				break;
			}		
	}
}

void MEXTI_voidEnableInterrupt(u8 ARG_u8InterruptNo)
{
	SET_BIT(GICR, ARG_u8InterruptNo);
}

void MEXTI_voidDisableInterrupt(u8 ARG_u8InterruptNo)
{
	CLEAR_BIT(GICR, ARG_u8InterruptNo);
}

void MEXTI_voidSetCallBackINT0(void (*ARG_pvoidfUserFunctionINT0)(void))
{
	MEXTI_pvoidfUserFunctionINT0 = ARG_pvoidfUserFunctionINT0;
}

void MEXTI_voidSetCallBackINT1(void (*ARG_pvoidfUserFunctionINT1)(void))
{
	MEXTI_pvoidfUserFunctionINT1 = ARG_pvoidfUserFunctionINT1;
}

void MEXTI_voidSetCallBackINT2(void (*ARG_pvoidfUserFunctionINT2)(void))
{
	MEXTI_pvoidfUserFunctionINT2 = ARG_pvoidfUserFunctionINT2;
}

void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
	(*MEXTI_pvoidfUserFunctionINT0)();
}

void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{
	(*MEXTI_pvoidfUserFunctionINT1)();
}

void __vector_3(void) __attribute__((signal));
void __vector_3(void)
{
	(*MEXTI_pvoidfUserFunctionINT2)();
}
