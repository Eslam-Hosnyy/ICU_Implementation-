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
//static u8 MTIM_u8Timer2Clock=0;

static u8 MTIM_u8Timer0Mode=0;
static u8 MTIM_u8Timer1Mode=0;
//static u8 MTIM_u8Timer2Mode=0;

static u16 MTIM_u16Timer0OCMCount = 0;
static u16 MTIM_u16Timer1OCMCount_A = 0;
static u16 MTIM_u16Timer1OCMCount_B = 0;
//static u16 MTIM_u16Timer2OCMCount = 0;
static u16 MTIM_u16Timer0OVFCount = 0;
static u16 MTIM_u16Timer1OVFCount = 0;
//static u16 MTIM_u16Timer2OVFCount = 0;
static u8 MTIM_u8Timer0Preload = 0;
static u16 MTIM_u16Timer1Preload = 0;
//static u8 MTIM_u8Timer2Preload = 0;

static u8 MTIM_u8OCR0 =   0;
static u16 MTIM_u16OCR1_A = 0;
static u16 MTIM_u16OCR1_B = 0;
//static u8 MTIM_u8OCR2 =   0;

static void(*MTIM_pvoidfuserFunctionT0OVF)(void) = NULL;
static void(*MTIM_pvoidfuserFunctionT0OCM)(void) = NULL;
static void(*MTIM_pvoidfuserFunctionT1OVF)(void) = NULL;
static void(*MTIM_pvoidfuserFunctionT1OCMB)(void)= NULL;
static void(*MTIM_pvoidfuserFunctionT1OCMA)(void)= NULL;
static void(*MTIM_pvoidfuserFunctionT1ICU)(void) = NULL;
//static void(*MTIM_pvoidfuserFunctionT2OVF)(void) = NULL;
//static void(*MTIM_pvoidfuserFunctionT2OCM)(void) = NULL;

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
		case MTIM_MODE_CTC0:
		{
			CLEAR_BIT(MTIM_TCCR0, TCCR0_WGM00);
			SET_BIT(MTIM_TCCR0, TCCR0_WGM01);
			break;
		}
		case MTIM_MODE_FASTPWM0:
		{
			SET_BIT(MTIM_TCCR0, TCCR0_WGM01);
			SET_BIT(MTIM_TCCR0, TCCR0_WGM00);
			break;
		}
		case MTIM_MODE_PHASECORRECTPWM0:
		{
			CLEAR_BIT(MTIM_TCCR0, TCCR0_WGM01);
			SET_BIT(MTIM_TCCR0, TCCR0_WGM00);
			break;
		}
		default:
			break; //report an error
		}
		/* CARRY THE MODE IN GLOBAL */
		MTIM_u8Timer0Mode=ARG_u8Mode;

		/* SET Hardware PIN _MODE */
		MTIM_TCCR0 &= 0b11001111;
		MTIM_TCCR0 |= ((ARG_u8HWPinMode & 0b00000011) << 4);
		/*Passing Timer_Clock As Global */
		MTIM_u8Timer0Clock = ARG_u8ClockSelect;
		break;

	}
	case MTIM_TIMER1:
	{
		switch(ARG_u8Mode)
		{
		case MTIM_MODE_NORMAL:
		{
			CLEAR_BIT(MTIM_TCCR0, TCCR1A_WGM10);
			CLEAR_BIT(MTIM_TCCR0, TCCR1A_WGM11);
			CLEAR_BIT(MTIM_TCCR0, TCCR1B_WGM12);
			CLEAR_BIT(MTIM_TCCR0, TCCR1B_WGM13);
			break;
		}
		case MTIM_MODE_CTC_8:
		{
			SET_BIT(MTIM_TCCR0, TCCR1A_WGM10);
			CLEAR_BIT(MTIM_TCCR0, TCCR1A_WGM11);
			CLEAR_BIT(MTIM_TCCR0, TCCR1B_WGM12);
			CLEAR_BIT(MTIM_TCCR0, TCCR1B_WGM13);
			break;
		}
		case MTIM_MODE_CTC_9:
		{
			CLEAR_BIT(MTIM_TCCR0, TCCR1A_WGM10);
			SET_BIT(MTIM_TCCR0, TCCR1A_WGM11);
			CLEAR_BIT(MTIM_TCCR0, TCCR1B_WGM12);
			CLEAR_BIT(MTIM_TCCR0, TCCR1B_WGM13);
			break;
		}
		case MTIM_MODE_CTC_10:
		{
			SET_BIT(MTIM_TCCR0, TCCR1A_WGM10);
			SET_BIT(MTIM_TCCR0, TCCR1A_WGM11);
			CLEAR_BIT(MTIM_TCCR0, TCCR1B_WGM12);
			CLEAR_BIT(MTIM_TCCR0, TCCR1B_WGM13);
			break;
		}
		case MTIM_MODE_CTC1:
		{
			CLEAR_BIT(MTIM_TCCR0, TCCR1A_WGM10);
			CLEAR_BIT(MTIM_TCCR0, TCCR1A_WGM11);
			SET_BIT(MTIM_TCCR0, TCCR1B_WGM12);
			CLEAR_BIT(MTIM_TCCR0, TCCR1B_WGM13);
			break;
		}
		case MTIM_MODE_FASTPWM_8:
		{
			SET_BIT(MTIM_TCCR0, TCCR1A_WGM10);
			CLEAR_BIT(MTIM_TCCR0, TCCR1A_WGM11);
			SET_BIT(MTIM_TCCR0, TCCR1B_WGM12);
			CLEAR_BIT(MTIM_TCCR0, TCCR1B_WGM13);
			break;
		}
		case MTIM_MODE_FASTPWM_9:
		{
			CLEAR_BIT(MTIM_TCCR0, TCCR1A_WGM10);
			SET_BIT(MTIM_TCCR0, TCCR1A_WGM11);
			SET_BIT(MTIM_TCCR0, TCCR1B_WGM12);
			CLEAR_BIT(MTIM_TCCR0, TCCR1B_WGM13);
			break;
		}
		case MTIM_MODE_FASTPWM_10:
		{
			SET_BIT(MTIM_TCCR0, TCCR1A_WGM10);
			SET_BIT(MTIM_TCCR0, TCCR1A_WGM11);
			SET_BIT(MTIM_TCCR0, TCCR1B_WGM12);
			CLEAR_BIT(MTIM_TCCR0, TCCR1B_WGM13);
			break;
		}
		case MTIM_MODE_PHASECORRECTPWM_ICR:
		{
			CLEAR_BIT(MTIM_TCCR0, TCCR1A_WGM10);
			SET_BIT(MTIM_TCCR0, TCCR1A_WGM11);
			CLEAR_BIT(MTIM_TCCR0, TCCR1B_WGM12);
			SET_BIT(MTIM_TCCR0, TCCR1B_WGM13);
			break;
		}
		case MTIM_MODE_PHASECORRECTPWM1:
		{
			SET_BIT(MTIM_TCCR0, TCCR1A_WGM10);
			SET_BIT(MTIM_TCCR0, TCCR1A_WGM11);
			CLEAR_BIT(MTIM_TCCR0, TCCR1B_WGM12);
			SET_BIT(MTIM_TCCR0, TCCR1B_WGM13);
			break;
		}
		case MTIM_MODE_CTC_ICR:
		{
			CLEAR_BIT(MTIM_TCCR0, TCCR1A_WGM10);
			CLEAR_BIT(MTIM_TCCR0, TCCR1A_WGM11);
			SET_BIT(MTIM_TCCR0, TCCR1B_WGM12);
			SET_BIT(MTIM_TCCR0, TCCR1B_WGM13);
			break;
		}
		case MTIM_MODE_FASTPWM_ICR:
		{
			CLEAR_BIT(MTIM_TCCR0, TCCR1A_WGM10);
			SET_BIT(MTIM_TCCR0, TCCR1A_WGM11);
			SET_BIT(MTIM_TCCR0, TCCR1B_WGM12);
			SET_BIT(MTIM_TCCR0, TCCR1B_WGM13);
			break;
		}
		case MTIM_MODE_FASTPWM1:
		{
			SET_BIT(MTIM_TCCR0, TCCR1A_WGM10);
			SET_BIT(MTIM_TCCR0, TCCR1A_WGM11);
			SET_BIT(MTIM_TCCR0, TCCR1B_WGM12);
			SET_BIT(MTIM_TCCR0, TCCR1B_WGM13);
			break;
		}
		default:
			break; //report an error
		}
		/* Passing Timer_Mode As Global */
		MTIM_u8Timer1Mode=ARG_u8Mode;

		/* SET Hardware PIN _MODE */
		MTIM_TCCR1A &= 0b00001111;
		MTIM_TCCR1A |= (((ARG_u8HWPinMode*5) & 0b00001111) << 4);
		/*Passing Timer_Clock As Global */
		MTIM_u8Timer1Clock = ARG_u8ClockSelect;
		break;
	}
	default:
	{
		break; //report an error
	}
	}


}

void MTIM_voidForceOutput(u8 ARG_u8TimerNo, u8 ARG_u8Channel) //task
{
	switch(ARG_u8TimerNo)
	{
	case MTIM_TIMER0 :
	{
		if(NO_CHANNELS==ARG_u8Channel)
		{
			SET_BIT(MTIM_TCCR0, TCCR0_FOC0);
		}
		break;
	}
	case MTIM_TIMER1 :
	{
		if(CHANNEL_A==ARG_u8Channel)
		{
			SET_BIT(MTIM_TCCR1A, TCCR1A_FOC1A);
		}
		else if(CHANNEL_B==ARG_u8Channel)
		{
			SET_BIT(MTIM_TCCR1B, TCCR1A_FOC1B);
		}
		break;
	}

	}

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
	case MTIM_INTERRUPT_T1_ICU:
	{
		MTIM_pvoidfuserFunctionT1ICU = ARG_pvoidfUserFunction;
		break;
	}
	case MTIM_INTERRUPT_T1_OCMA:
	{
		MTIM_pvoidfuserFunctionT1OCMA = ARG_pvoidfUserFunction;
		break;
	}
	case MTIM_INTERRUPT_T1_OCMB:
	{
		MTIM_pvoidfuserFunctionT1OCMB = ARG_pvoidfUserFunction;
		break;
	}
	case MTIM_INTERRUPT_T1_OVF:
	{
		MTIM_pvoidfuserFunctionT1OVF = ARG_pvoidfUserFunction;
		break;
	}
	default:
		break; //report an error
	}
}

void MTIM_voidTimerDelay(u8 ARG_u8TimerNo, u32 ARG_u32Delay)
{
	f32 L_f32TickTime, L_f32OVFTime,L_f32OCMFTime,L_f32OCMFTime_B;
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
		switch(MTIM_u8Timer1Clock)
		{
		case MTIM_CS_NO_PRESCALING:		L_u16Prescaler = 1;		break;
		case MTIM_CS_PRESCALER_8:		L_u16Prescaler = 8;		break;
		case MTIM_CS_PRESCALER_64:		L_u16Prescaler = 64;	break;
		case MTIM_CS_PRESCALER_256:		L_u16Prescaler = 256;	break;
		case MTIM_CS_PRESCALER_1024:	L_u16Prescaler = 1024;	break;
		}
		if(MTIM_MODE_NORMAL==MTIM_u8Timer1Mode)
		{
			L_f32TickTime = (f32)L_u16Prescaler / MTIM_IO_CLOCK;
			L_f32OVFTime = (f32)L_f32TickTime * 256;
			MTIM_u16Timer1OVFCount = (f32)(((f32)ARG_u32Delay/1000) / L_f32OVFTime);
			MTIM_u16Timer1Preload = 256 - ((ARG_u32Delay/1000) % (u32)L_f32OVFTime);
			MTIM_TCNT1 = MTIM_u16Timer1Preload;
		}
		else
		{
			L_f32TickTime = (f32)L_u16Prescaler / MTIM_IO_CLOCK;
			L_f32OCMFTime=(f32)L_f32TickTime*MTIM_u16OCR1_A;
			L_f32OCMFTime_B=(f32)L_f32TickTime*MTIM_u16OCR1_B;
			MTIM_u16Timer1OCMCount_A = (f32)(((f32)ARG_u32Delay/1000) / L_f32OCMFTime);
			MTIM_u16Timer1OCMCount_B = (f32)(((f32)ARG_u32Delay/1000) / L_f32OCMFTime_B);
		}
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
		MTIM_TCCR1B &= 0b11111000;
		MTIM_TCCR1B |= (MTIM_u8Timer1Clock & 0b00000111);
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
		MTIM_TCCR1B &= 0b11111000;
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

void MTIM_voidSetOCR(u8 ARG_u8TimerNo, u16 ARG_u8OCRValue, u8 ARG_u8Channel)
{
	switch(ARG_u8TimerNo)
	{
	case MTIM_TIMER0:
	{
		if(NO_CHANNELS==ARG_u8Channel)
		{
			MTIM_OCR0=(u8)ARG_u8OCRValue;
			MTIM_u8OCR0=MTIM_OCR0;
		}
		break;
	}
	case MTIM_TIMER1:
	{
		if(CHANNEL_A==ARG_u8Channel)
		{
			MTIM_OCR1A=(u8)ARG_u8OCRValue;
			MTIM_u16OCR1_A=MTIM_OCR1A;
		}
		else if(CHANNEL_B==ARG_u8Channel)
		{
			MTIM_OCR1B=(u8)ARG_u8OCRValue;
			MTIM_u16OCR1_B=MTIM_OCR1B;
		}
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

void MTIM_voidICUINT(void)
{
	/*SET Trigger Source To Rising initially*/
	SET_BIT(MTIM_TCCR1B,TCCR1B_ICES1);
	/*Enable Input Capture Interrupt*/
	SET_BIT(MTIM_TIMSK,TIMSK_TICIE1);
}
void MTIM_voidSetICUEdge(u8 ARG_u8SelectEdge)
{
	if(ARG_u8SelectEdge==ICU_RISING)
	{
		SET_BIT(MTIM_TCCR1B,TCCR1B_ICES1);
	}
	else if(ARG_u8SelectEdge==ICU_FALLING)
	{
		CLEAR_BIT(MTIM_TCCR1B,TCCR1B_ICES1);
	}
}

u16 MTIM_u16ReadICU(void)
{
	return MTIM_ICR1;
}


/* ISR FUNCTIONS */
void __vector_6(void)__attribute__((signal));
void __vector_6(void)
{
	(*MTIM_pvoidfuserFunctionT1ICU)();
}

void __vector_7(void)__attribute__((signal));
void __vector_7(void)
{
	static volatile u16 L_u16OCMCounter = 0;
	if(L_u16OCMCounter < MTIM_u16Timer1OCMCount_A)
	{
		L_u16OCMCounter++;
	}
	else
	{
		L_u16OCMCounter = 0;
		(*MTIM_pvoidfuserFunctionT1OCMA)();
	}

}

void __vector_8(void)__attribute__((signal));
void __vector_8(void)
{
	static volatile u16 L_u16OCMCounter = 0;
	if(L_u16OCMCounter < MTIM_u16Timer1OCMCount_B)
	{
		L_u16OCMCounter++;
	}
	else
	{
		L_u16OCMCounter = 0;
		(*MTIM_pvoidfuserFunctionT1OCMB)();
	}

}


void __vector_9(void)__attribute__((signal));
void __vector_9(void)
{
	static volatile u16 L_u16OVFCounter = 0;
	if(L_u16OVFCounter < MTIM_u16Timer1OVFCount)
	{
		L_u16OVFCounter++;
	}
	else
	{
		L_u16OVFCounter = 0;
		MTIM_TCNT1 = MTIM_u16Timer1Preload;
		(*MTIM_pvoidfuserFunctionT1OVF)();
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




