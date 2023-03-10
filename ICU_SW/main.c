/************************************/
/*	Author		: Eslam_Hosny		*/
/*	SWC			: N/A				*/
/*	Layer		: N/A				*/
/*	Version   	: 0.0				*/
/*	Date	  	: N/A				*/
/*	Last Edit 	: N/A				*/
/************************************/
#define F_CPU	8000000UL
#include <util/delay.h>
#include "LSTD_types.h"
#include "LBIT_math.h"
#include "MDIO_interface.h"
#include "PORT_interface.h"
#include "MADC_interface.h"
#include "MEXTI_interface.h"
#include "MGIE_interface.h"
#include "MTIM_interface.h"
#include "CLCD_interface.h"

#define	TCCR1A   *((volatile u8*)0x4F)
#define	TCCR1B   *((volatile u8*)0x4E)
#define	TCNT1H   *((volatile u8*)0x4D)
#define	TCNT1L   *((volatile u8*)0x4C)
#define	TCNT1	 *((volatile u16*)0x4C)

void Step_1(void);
void Step_2(void);
void Step_3(void);

volatile f32 Ton=0,Toff=0;
volatile u8 flag=0;

int main (void)
{
	u16 ARG_u8Reading;
	f32 Freq;
	u32 Duty=0;
	u32 ARG_u32MillVolT;

	PORT_voidInit();
	MADC_voidInit();
	CLCD_voidInit();

	MTIIM_voidInit(MTIM_TIMER0, MTIM_CS_PRESCALER_256, MTIM_MODE_FASTPWM, MTIM_HWPIN_NONINVERTING_PWM);

	MEXTI_voidInit(MEXTI_INT0,MEXTI_MODE_RISING);
	MEXTI_voidSetCallBackINT0(&Step_1);
	MEXTI_voidEnableInterrupt(MEXTI_INT0);

	CLCD_voidSendStringXY(0, 0, "Freq: ");
	CLCD_voidSendStringXY(1, 0, "Duty: ");

	MTIM_voidStartTimer(MTIM_TIMER0);
	MGIE_voidEnableGIE();

	while(1)
	{

		MADC_u8StartConversionSynch(0, &ARG_u8Reading, &ARG_u32MillVolT);
		MTIM_voidSetOCR(MTIM_TIMER0, ARG_u8Reading);

		if(1==flag)
		{
			Freq=(1/(Ton+Toff)*8000000);
			Duty=(Ton/(Ton+Toff))*100;
			CLCD_voidGoToXY(0, 6);
			CLCD_voidSendString("              ");
			CLCD_voidGoToXY(0, 6);
			CLCD_voidWriteNumber(Freq);
			CLCD_voidGoToXY(1, 6);
			CLCD_voidSendString("   ");
			CLCD_voidGoToXY(1, 6);
			CLCD_voidWriteNumber(Duty);
			CLCD_voidSendString("%");
		}
		_delay_ms(100);

	}

	return 0;
}

void Step_1(void)
{
	TCCR1B=0x01;
	TCNT1=0;
	flag=0;
	MEXTI_voidInit(MEXTI_INT0, MEXTI_MODE_FALLING);
	MEXTI_voidSetCallBackINT0(Step_2);
}

void Step_2(void)
{
	Ton=TCNT1;
	TCNT1=0;
	flag=0;
	MEXTI_voidInit(MEXTI_INT0, MEXTI_MODE_RISING);
	MEXTI_voidSetCallBackINT0(Step_3);
}

void Step_3(void)
{
	MDIO_u8SetPinValue(MDIO_PORTB, 0, 1);

	Toff=TCNT1;
	TCNT1=0;
	flag=1;
	MEXTI_voidInit(MEXTI_INT0, MEXTI_MODE_FALLING);
	MEXTI_voidSetCallBackINT0(Step_2);
}
