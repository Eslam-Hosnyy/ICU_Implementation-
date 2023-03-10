/************************************/
/*	Author	  :	ESLAM-HOSNY			*/
/*	SWC		  : TIMER				*/
/*  Layer	  : MCAL				*/
/*	Version	  :	1.0		  			*/
/*	Date	  :	December 9, 2022	*/
/************************************/

#ifndef _MTIM_INTERFACE_H_
#define _MTIM_INTERFACE_H_

#ifndef F_CPU
#define F_CPU	1000000UL
#warning F_CPU not define, assuming 1MHz clock.
#endif

#define MTIM_IO_CLOCK  					F_CPU

#define NO_CHANNELS						0
#define CHANNEL_A						1
#define CHANNEL_B						2

#define ICU_RISING						0
#define ICU_FALLING						1

#define MTIM_TIMER0						0
#define MTIM_TIMER1						1
#define MTIM_TIMER2						2

/* ARGUMENTS FOR TIMER0 */
#define MTIM_MODE_NORMAL				0
#define MTIM_MODE_CTC0					1
#define MTIM_MODE_FASTPWM0				2
#define MTIM_MODE_PHASECORRECTPWM0		3

/* ARGUMENTS FOR TIMER1 */
#define MTIM_MODE_NORMAL				0
#define MTIM_MODE_CTC_8					1
#define MTIM_MODE_CTC_9					2
#define MTIM_MODE_CTC_10				3
#define MTIM_MODE_CTC1					4
#define MTIM_MODE_FASTPWM_8				5
#define MTIM_MODE_FASTPWM_9				6
#define MTIM_MODE_FASTPWM_10			7
#define MTIM_MODE_PHASECORRECTPWM_ICR	10
#define MTIM_MODE_PHASECORRECTPWM1		11
#define MTIM_MODE_CTC_ICR				12
#define MTIM_MODE_FASTPWM_ICR			14
#define MTIM_MODE_FASTPWM1				15


#define MTIM_CS_NO_CLOCK				0
#define MTIM_CS_NO_PRESCALING			1
#define MTIM_CS_PRESCALER_8				2
#define MTIM_CS_PRESCALER_64			3
#define MTIM_CS_PRESCALER_256			4
#define MTIM_CS_PRESCALER_1024			5
#define MTIM_CS_T0_FALLING				6
#define MTIM_CS_T0_RISING				7

#define MTIM_HWPIN_DiSCONNECTED			0
#define MTIM_HWPIN_TOGGLE				1
#define MTIM_HWPIN_CLEAR				2
#define MTIM_HWPIN_SET					3
#define MTIM_HWPIN_INVERTING_PWM		3
#define MTIM_HWPIN_NONINVERTING_PWM		2


#define MTIM_INTERRUPT_T0_OVF			0
#define MTIM_INTERRUPT_T0_OCM			1
#define MTIM_INTERRUPT_T1_OVF			2
#define MTIM_INTERRUPT_T1_OCMB			3
#define MTIM_INTERRUPT_T1_OCMA			4
#define MTIM_INTERRUPT_T1_ICU			5
#define MTIM_INTERRUPT_T2_OVF			6
#define MTIM_INTERRUPT_T2_OCM			7



void MTIIM_voidInit(u8 ARG_u8TimerNo,u8 ARG_u8ClockSelect, u8 ARG_u8Mode, u8 ARG_u8HWPinMode);

void MTIM_voidForceOutput(u8 ARG_u8TimerNo, u8 ARG_u8Channel);

void MTIM_voidEnableInterrupt(u8 ARG_u8InterruptSource);

void MTIM_voidDisableInterrupt(u8 ARG_u8InterruptSource);

void MTIM_voidSetCallback(u8 ARG_u8InterruptSource, void(*ARG_pvoidfUserFunction)(void));

void MTIM_voidStartTimer(u8 ARG_u8TimerNo);

void MTIM_voidStopTimer(u8 ARG_u8TimerNo);

void MTIM_voidSetOCR(u8 ARG_u8TimerNo, u16 ARG_u8OCRValue, u8 ARG_u8Channel);

void MTIM_voidTimerDelay(u8 ARG_u8TimerNo, u32 ARG_u32Delay);

void MTIM_voidSetICUEdge(u8 ARG_u8SelectEdge);

void MTIM_voidICUINT(void);

u16 MTIM_u16ReadICU(void);


#endif
