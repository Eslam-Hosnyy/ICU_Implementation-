/************************************/
/*	Author	  :	ESLAM-HOSNY			*/
/*	SWC		  : TIMER				*/
/*  Layer	  : MCAL				*/
/*	Version	  :	1.0		  			*/
/*	Date	  :	December 9, 2022	*/
/************************************/
#include "LSTD_types.h"
#include "LBIT_math.h"
#include "MTIM_private.h"
#include "MTIM_interface.h"


static u8 MTIM_u8Timer0Clock=0;
static u8 MTIM_u8Timer1Clock=0;
static u8 MTIM_u8Timer2Clock=0;

static u8 MTIM_u8Timer0Mode=0;
static u8 MTIM_u8Timer1Mode=0;
static u8 MTIM_u8Timer2Mode=0;

static u16 MTIM_u16Timer0OCMCount = 0;
static u16 MTIM_u16Timer1OCMCount = 0;
static u16 MTIM_u16Timer2OCMCount = 0;
static u16 MTIM_u16Timer0OVFCount = 0;
static u16 MTIM_u16Timer1OVFCount = 0;
static u16 MTIM_u16Timer2OVFCount = 0;
static u8 MTIM_u8Timer0Preload = 0;
static u16 MTIM_u16Timer1Preload = 0;
static u8 MTIM_u8Timer2Preload = 0;

static u8 MTIM_u8OCR0 = 0;
static u8 MTIM_u8OCR1 = 0;
static u8 MTIM_u8OCR2 = 0;

static void(*MTIM_pvoidfuserFunctionT0OVF)(void) = NULL;
static void(*MTIM_pvoidfuserFunctionT0OCM)(void) = NULL;
static void(*MTIM_pvoidfuserFunctionT1OVF)(void) = NULL;
static void(*MTIM_pvoidfuserFunctionT1OCMB)(void)= NULL;
static void(*MTIM_pvoidfuserFunctionT1OCMA)(void)= NULL;
static void(*MTIM_pvoidfuserFunctionT1ICU)(void) = NULL;
static void(*MTIM_pvoidfuserFunctionT2OVF)(void) = NULL;
static void(*MTIM_pvoidfuserFunctionT2OCM)(void) = NULL;

void MTIIM_voidInit(u8 ARG_u8TimerNo,u8 ARG_u8ClockSelect, u8 ARG_u8Mode, u8 ARG_u8HWPinMode)
{
	switch(ARG_u8TimerNo)
	{
	case MTIM_TIMER0:
	{
		switch(ARG_u8Mode)
		{
		case MTIM_MODE_NORMAL:
		{
			CLEAR_BIT(MTIM_TCCR0, TCCR0_WGM01);
			CLEAR_BIT(MTIM_TCCR0, TCCR0_WGM00);
			break;
		}
		case MTIM_MODE_CTC:
		{
			CLEAR_BIT(MTIM_TCCR0, TCCR0_WGM00);
			SET_BIT(MTIM_TCCR0, TCCR0_WGM01);
			break;
		}
		case MTIM_MODE_FASTPWM:
		{
			SET_BIT(MTIM_TCCR0, TCCR0_WGM01);
			SET_BIT(MTIM_TCCR0, TCCR0_WGM00);
			break;
		}
		case MTIM_MODE_PHASECORRECTPWM:
		{
			CLEAR_BIT(MTIM_TCCR0, TCCR0_WGM01);
			SET_BIT(MTIM_TCCR0, TCCR0_WGM00);
			break;
		}
		default:
			break; //report an error
		}
		MTIM_u8Timer0Mode=ARG_u8Mode;
		break;
	}
	case MTIM_TIMER1:
	{
		break;
	}

	default:
		break; //report an error
	}

	/* SET Hardware PIN _MODE */
	MTIM_TCCR0 &= 0b11001111;
	MTIM_TCCR0 |= ((ARG_u8HWPinMode & 0b00000011) << 4);
	/*Passing Timer_Clock As Global */
	MTIM_u8Timer0Clock = ARG_u8ClockSelect;
}

void MTIM_voidForceOutput(void) //task
{
	SET_BIT(MTIM_TCCR0, TCCR0_FOC0);
}

void MTIM_voidEnableInterrupt(u8 ARG_u8InterruptSource)
{
	SET_BIT(MTIM_TIMSK, ARG_u8InterruptSource);
}

void MTIM_voidDisableInterrupt(u8 ARG_u8InterruptSource)//task
{
	CLEAR_BIT(MTIM_TIMSK, ARG_u8InterruptSource);
}

void MTIM_voidSetCallback(u8 ARG_u8InterruptSource, void(*ARG_pvoidfUserFunction)(void))//task
{
	switch(ARG_u8InterruptSource)
	{
	case MTIM_INTERRUPT_T0_OVF:
	{
		MTIM_pvoidfuserFunctionT0OVF = ARG_pvoidfUserFunction;
		break;
	}
	case MTIM_INTERRUPT_T0_OCM:
	{
		MTIM_pvoidfuserFunctionT0OCM = ARG_pvoidfUserFunction;
		break;
	}
	default:
		break; //report an error
	}
}

void MTIM_voidTimerDelay(u8 ARG_u8TimerNo, u32 ARG_u32Delay)
{
	f32 L_f32TickTime, L_f32OVFTime,L_f32OCMFTime;
	u16 L_u16Prescaler;

	switch(ARG_u8TimerNo)
	{
	case MTIM_TIMER0:
	{
		switch(MTIM_u8Timer0Clock)
		{
		case MTIM_CS_NO_PRESCALING:		L_u16Prescaler = 1;		break;
		case MTIM_CS_PRESCALER_8:		L_u16Prescaler = 8;		break;
		case MTIM_CS_PRESCALER_64:		L_u16Prescaler = 64;	break;
		case MTIM_CS_PRESCALER_256:		L_u16Prescaler = 256;	break;
		case MTIM_CS_PRESCALER_1024:	L_u16Prescaler = 1024;	break;
		}
		if(MTIM_MODE_NORMAL==MTIM_u8Timer0Mode)
		{
			L_f32TickTime = (f32)L_u16Prescaler / MTIM_IO_CLOCK;
			L_f32OVFTime = (f32)L_f32TickTime * 256;
			MTIM_u16Timer0OVFCount = (f32)(((f32)ARG_u32Delay/1000) / L_f32OVFTime);
			MTIM_u8Timer0Preload = 256 - ((ARG_u32Delay/1000) % (u32)L_f32OVFTime);
			MTIM_TCNT0 = MTIM_u8Timer0Preload;
		}
		else
		{
			L_f32TickTime = (f32)L_u16Prescaler / MTIM_IO_CLOCK;
			L_f32OCMFTime=(f32)L_f32TickTime*MTIM_u8OCR0;
			MTIM_u16Timer0OCMCount = (f32)(((f32)ARG_u32Delay/1000) / L_f32OCMFTime);
		}
		break;
	}
	case MTIM_TIMER1:
	{
		break;
	}
	case MTIM_TIMER2:
	{
		break;
	}
	default:
		break; //report an error

	}

}

void MTIM_voidStartTimer(u8 ARG_u8TimerNo)//task
{

	switch(ARG_u8TimerNo)
	{
	case MTIM_TIMER0:
	{
		MTIM_TCCR0 &= 0b11111000;
		MTIM_TCCR0 |= (MTIM_u8Timer0Clock & 0b00000111);
		break;
	}
	case MTIM_TIMER1:
	{
		break;
	}
	case MTIM_TIMER2:
	{
		break;
	}
	default:
		break;// report an error

	}
}

void MTIM_voidStopTimer(u8 ARG_u8TimerNo)//task
{
	switch(ARG_u8TimerNo)
	{
	case MTIM_TIMER0:
	{
		MTIM_TCCR0 &= 0b11111000;
		break;
	}
	case MTIM_TIMER1:
	{
		break;
	}
	case MTIM_TIMER2:
	{
		break;
	}
	default:
		break;// report an error

	}
}

void MTIM_voidSetOCR(u8 ARG_u8TimerNo, u16 ARG_u8OCRValue)
{
	switch(ARG_u8TimerNo)
	{
	case MTIM_TIMER0:
	{
		MTIM_OCR0=(u8)ARG_u8OCRValue;
		MTIM_u8OCR0=MTIM_OCR0;
		break;
	}
	case MTIM_TIMER1:
	{
		break;
	}
	case MTIM_TIMER2:
	{
		break;
	}
	default:
		break;// report an error

	}
}

void __vector_10(void)__attribute__((signal));
void __vector_10(void)
{
	static volatile u16 L_u16OCMCounter = 0;
	if(L_u16OCMCounter < MTIM_u16Timer0OCMCount)
	{
		L_u16OCMCounter++;
	}
	else
	{
		L_u16OCMCounter = 0;
		(*MTIM_pvoidfuserFunctionT0OCM)();
	}
}

void __vector_11(void)__attribute__((signal));
void __vector_11(void)
{
	static volatile u16 L_u16OVFCounter = 0;
	if(L_u16OVFCounter < MTIM_u16Timer0OVFCount)
	{
		L_u16OVFCounter++;
	}
	else
	{
		L_u16OVFCounter = 0;
		MTIM_TCNT0 = MTIM_u8Timer0Preload;
		(*MTIM_pvoidfuserFunctionT0OVF)();
	}

}

