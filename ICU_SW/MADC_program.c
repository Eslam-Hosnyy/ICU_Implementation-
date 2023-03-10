/************************************/
/*	Author	  :	ESLAM_HOSNY			*/
/*	SWC		  : ADC					*/
/*  Layer	  : MCAL				*/
/*	Version	  :	1.0		  			*/
/*	Date	  :	December 1, 2022	*/
/*	Last Edit : N/A					*/
/************************************/
#include "LSTD_types.h"
#include "LBIT_math.h"
#include "MADC_confg.h"
#include "MADC_private.h"
#include "MADC_interface.h"

static u8 MADC_u8State=IDLE;
static u16 *MADC_u16ADCReading=NULL;
static u32 *MADC_u32ADCMillVol=NULL;
static void(*MADCpNotification)(void)=NULL;

void MADC_voidInit(void)
{
	/* Check The Voltage Reference */
#if 1==MADC_VOLTAGE_REF
	CLEAR_BIT(MADC_ADMUX,ADMUX_REFS0);
	CLEAR_BIT(MADC_ADMUX,ADMUX_REFS1);
#elif 2==MADC_VOLTAGE_REF
	SET_BIT(MADC_ADMUX,ADMUX_REFS0);
	CLEAR_BIT(MADC_ADMUX,ADMUX_REFS1);
#elif 3==MADC_VOLTAGE_REF
	SET_BIT(MADC_ADMUX,ADMUX_REFS0);
	SET_BIT(MADC_ADMUX,ADMUX_REFS1);
#else
#error "Wrong Voltage Reference"
#endif

	/* Check The ADC conversion result in ADLAR_bit (ADC Reslution) */
#if 1==MADC_RESELUTION
	SET_BIT(MADC_ADMUX,ADMUX_ADLAR);
#elif 2==MADC_RESELUTION
	CLEAR_BIT(MADC_ADMUX,ADMUX_ADLAR);
#else
#error "Wrong ADC Reslution Convertion"
#endif

	/* Check ADC Convertion Mode */
#if 1==MADC_CONVERSTION_MODE
	/* Clear Interrupt And Trigger Bits */
	CLEAR_BIT(MADC_ADCSRA,ADCSRA_ADATE);
	CLEAR_BIT(MADC_ADCSRA,ADCSRA_ADIE);
#elif 2==MADC_CONVERSTION_MODE
	/* Set Interrupt And Trigger Bits */
	SET_BIT(MADC_ADCSRA,ADCSRA_ADATE);
	SET_BIT(MADC_ADCSRA,ADCSRA_ADIE);
	/* Set Auto_Trigger Source */
	MADC_SFIOR &= SFIOR_MASK;
	MADC_SFIOR |= MADC_ATUOTRRIGER;
	/* Stert First Conversion */
	SET_BIT(MADC_ADCSRA,ADCSRA_ADSC);
#else
#error "Wrong ADC Convertion Mode"
#endif

	/* Initialize ADC Channel */
	MADC_ADMUX &= ADMUX_MASK;
	/*CLEAR ADC Prescaler Select Bits */
	MADC_ADCSRA &= ADCSRA_MASK;
	/* SET The Prescaler Bits */
	MADC_ADCSRA |= MADC_Prescaler;
	/* Enable ADC Converter */
	SET_BIT(MADC_ADCSRA,ADCSRA_ADEN);

}

u8 MADC_u8StartConversionSynch(u8 ARG_u8Channal,u16 *ARG_u8Reading,u32 *ARG_u32MillVolT)
{
	u32 L_u32Counter=0;
	u8 L_u8ErrorState=OK;
	if(IDLE==MADC_u8State)
	{
		/* Make ADC Busy (Not Working in next Conversion Until Finishing The Current Conversion) */
		MADC_u8State=BUSY;
		if(NULL == ARG_u8Reading)
		{
			L_u8ErrorState = NULL_POINTER;
		}
		else
		{
			/* CLEAR ADC Channel */
			MADC_ADMUX &= ADMUX_MASK;
			/* SET The Channel Bits */
			MADC_ADMUX |= ARG_u8Channal;

			/* ADC Start Conversion */
			SET_BIT(MADC_ADCSRA,ADCSRA_ADSC);

			/* Polling (Busy Wating) Until The Conversion Complete Flag is Set */
			while((GET_BIT(MADC_ADCSRA,ADCSRA_ADIF)==0) && (L_u32Counter!=ADC_TimeOUT))
			{
				L_u32Counter++;
			}
			if(ADC_TimeOUT==L_u32Counter)
			{
				//Loop is Broken Because The Time is Reached
				L_u8ErrorState = NOK;
			}
			else
			{
				//Loop is broken because Flage is Raised

				/* Clear The Conversion Flag */
				SET_BIT(MADC_ADCSRA,ADCSRA_ADIF);

				/* Return The Digital Value */
				if(1==MADC_RESELUTION)
				{
					*ARG_u32MillVolT = ((MADC_ADCH*MADC_MAX)/256.0)*1000;
					*ARG_u8Reading = MADC_ADCH;
				}
				if (2==MADC_RESELUTION)
				{
					*ARG_u32MillVolT = ((MADC*MADC_MAX)/1024.0)*1000;
					*ARG_u8Reading = MADC;
				}
			}
		}
		/* Return ADC To IDLE */
		MADC_u8State=IDLE;
	}
	else
	{
		L_u8ErrorState = BUSY_FUNCTION;
	}

	return L_u8ErrorState;
}


u8 MADC_u8StartConversionASynch(u8 ARG_u8Channal,u16 *ARG_u8Reading,u32 *ARG_u32MillVolT, void(*ARG_pNotification)(void))
{
	u8 L_u8ErrorState=OK;
	if(IDLE==MADC_u8State)
	{
		/* Make ADC Busy (Not Working in next Conversion Until Finishing The Current Conversion) */
		MADC_u8State=BUSY;
		if((NULL==ARG_u8Reading) || (NULL==ARG_pNotification))
		{
			L_u8ErrorState=NULL_POINTER;
		}
		else
		{
			/* Initialize The Reading And Notification Globally */
			MADC_u16ADCReading=ARG_u8Reading;
			MADC_u32ADCMillVol=ARG_u32MillVolT;
			MADCpNotification=ARG_pNotification;
			/* CLEAR ADC Channel */
			MADC_ADMUX &= ADMUX_MASK;
			/* SET The Channel Bits */
			MADC_ADMUX |= ARG_u8Channal;
			/* ADC Start Conversion */
			SET_BIT(MADC_ADCSRA,ADCSRA_ADSC);
			/*Enable ADC_Interrupt*/
			SET_BIT(MADC_ADCSRA,ADCSRA_ADIE);
		}
	}
	else
	{
		L_u8ErrorState = BUSY_FUNCTION;
	}

	return L_u8ErrorState;
}

void __vector_16 (void)  __attribute__((signal));
void __vector_16 (void)
{
	/* Read ADC Result */
	if(1==MADC_RESELUTION)
	{
		*MADC_u32ADCMillVol = ((MADC_ADCH*MADC_MAX)/256.0)*1000;
		*MADC_u16ADCReading = MADC_ADCH;
	}
	if (2==MADC_RESELUTION)
	{
		*MADC_u32ADCMillVol = ((MADC*MADC_MAX)/1024.0)*1000;
		*MADC_u16ADCReading = MADC;
	}

	/* Return ADC To IDLE */
	MADC_u8State=IDLE;
	/* Invoke The Notification Finction */
	MADCpNotification();
	/*Disnable ADC_Interrupt*/
	CLEAR_BIT(MADC_ADCSRA,ADCSRA_ADIE);

}







s32 MAP(s32 ARG_s32IMin, s32 ARG_s32IMax, s32 ARG_s32OMin, s32 ARG_s32OMax, s32 ARG_s32Val, u8 ARG_u8Relationship)
{
	s32 L_u32ReturnedVal=0;
	if(POSITIVE == ARG_u8Relationship)
	{
		L_u32ReturnedVal = (ARG_s32OMax-ARG_s32OMin)*(ARG_s32Val-ARG_s32IMin);
		L_u32ReturnedVal /= (ARG_s32IMax-ARG_s32IMin);
		L_u32ReturnedVal += ARG_s32OMin;
	}
	if(INVERSE == ARG_u8Relationship)
	{
		L_u32ReturnedVal = (ARG_s32OMin-ARG_s32OMax)*(ARG_s32Val-ARG_s32IMin);
		L_u32ReturnedVal /= (ARG_s32IMax-ARG_s32IMin);
		L_u32ReturnedVal += ARG_s32OMax;
	}

	return L_u32ReturnedVal;
}
