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
#include "MGIE_interface.h"
#include "MTIM_interface.h"
#include "CLCD_interface.h"

volatile u32 Period=0,Ton=0;
volatile u8 flag=0;
volatile f32 Freq=0;
volatile u32 Duty=0;
void ICU_HW(void);
int main (void)
{
	u16 ARG_u8Reading;
	u32 ARG_u32MillVolT;

	PORT_voidInit();
	MADC_voidInit();
	CLCD_voidInit();

	MTIM_voidICUINT();
	MTIM_voidSetCallback(MTIM_INTERRUPT_T1_ICU, &ICU_HW);
	MTIM_voidEnableInterrupt(MTIM_INTERRUPT_T1_ICU);
	MTIIM_voidInit(MTIM_TIMER0, MTIM_CS_PRESCALER_8, MTIM_MODE_FASTPWM0, MTIM_HWPIN_NONINVERTING_PWM);
	MTIIM_voidInit(MTIM_TIMER1, MTIM_CS_NO_PRESCALING, MTIM_MODE_NORMAL, MTIM_HWPIN_DiSCONNECTED);


	CLCD_voidSendStringXY(0, 0, "Freq: ");
	CLCD_voidSendStringXY(1, 0, "Duty: ");

	MTIM_voidStartTimer(MTIM_TIMER0);
	MTIM_voidStartTimer(MTIM_TIMER1);

	MGIE_voidEnableGIE();

	while(1)
	{

		MADC_u8StartConversionSynch(0, &ARG_u8Reading, &ARG_u32MillVolT);
		MTIM_voidSetOCR(MTIM_TIMER0, 64, NO_CHANNELS);

		CLCD_voidGoToXY(0, 6);
		CLCD_voidSendString("              ");
		CLCD_voidGoToXY(0, 6);
		CLCD_voidWriteNumber(Freq);
		CLCD_voidGoToXY(1, 6);
		CLCD_voidSendString("              ");
		CLCD_voidGoToXY(1, 6);
		CLCD_voidWriteNumber(Duty);
		CLCD_voidSendString("%");

		_delay_ms(100);

	}

	return 0;
}

void ICU_HW(void)
{
	static volatile u16 L_Reading1,L_Reading2,L_Reading3;
	static volatile u8 Counter=0;
	Counter++;

	if(1==Counter)
	{
		L_Reading1=MTIM_u16ReadICU();
	}
	else if(2==Counter)
	{

		L_Reading2=MTIM_u16ReadICU();
		Period=L_Reading2-L_Reading1;
		MTIM_voidSetICUEdge(ICU_FALLING);
	}
	else if(3==Counter)
	{
		L_Reading3=MTIM_u16ReadICU();
		Ton=L_Reading3-L_Reading2;

		Freq=(1/(Period)*8000000);
		Duty=(Ton/(Period))*100;
		Counter=0;
		MTIM_voidSetICUEdge(ICU_RISING);
	}

}
