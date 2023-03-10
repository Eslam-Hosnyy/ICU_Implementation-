/************************************/
/*	Author	  :	ESLAM_HOSNY			*/
/*	SWC		  : TIMERS				*/
/*  Layer	  : MCAL				*/
/*	Version	  :	1.0		  			*/
/*	Date	  :	December 8, 2022	*/
/*	Last Edit : N/A					*/
/************************************/
#ifndef _MTIM_PRIVATE_H_
#define _MTIM_PRIVATE_H_


/*Timer_0 Registers*/
#define MTIM_TCCR0		*((volatile u8*)0x53)			//Timer0/Counter Control Register
#define TCCR0_FOC0		7								//Force Output Compare
#define TCCR0_WGM00		6								//Waveform Generation Mode_pin0
#define TCCR0_COM01		5								//Compare Match Output Mode_pin0
#define TCCR0_COM00		4								//Compare Match Output Mode_pin1
#define TCCR0_WGM01		3								//Waveform Generation Mode_pin1
#define TCCR0_CS02		2								//Clock Select_pin2
#define TCCR0_CS01		1								//Clock Select_pin1
#define TCCR0_CS00		0								//Clock Select_pin0

#define MTIM_TCNT0  	*((volatile u8*)0x52)			//Timer/Counter Register(Preload) Register

#define MTIM_OCR0 		*((volatile u8*)0x5C)			//Output Compare Register(CTC) Register

/*Timer_1 Registers*/
#define MTIM_TCCR1A		*((volatile u8*)0x4F)			//Timer1/Counter Control Register
#define TCCR1A_WGM10	0
#define TCCR1A_WGM11	1
#define TCCR1A_FOC1B	2
#define TCCR1A_FOC1A	3
#define TCCR1A_COM1B0	4
#define TCCR1A_COM1B1	5
#define TCCR1A_COM1A0	6
#define TCCR1A_COM1A1	7

#define	MTIM_TCCR1B 	*((volatile u8*)0x4E)
#define TCCR1B_CS10		0
#define TCCR1B_CS11		1
#define TCCR1B_CS12		2
#define TCCR1B_WGM12	3
#define TCCR1B_WGM13	4
#define TCCR1B_ICES1	6
#define TCCR1B_ICNC1	7

#define	MTIM_TCNT1H	 	*((volatile u8*)0x4D)
#define	MTIM_TCNT1L	 	*((volatile u8*)0x4C)
#define	MTIM_TCNT1	 	*((volatile u16*)0x4C)

#define	MTIM_OCR1BH  	*((volatile u8*)0x49)
#define	MTIM_OCR1BL  	*((volatile u8*)0x48)
#define	MTIM_OCR1B  	*((volatile u16*)0x48)
#define	MTIM_OCR1AH  	*((volatile u8*)0x4B)
#define	MTIM_OCR1AL  	*((volatile u8*)0x4A)
#define	MTIM_OCR1A  	*((volatile u16*)0x4A)

#define	MTIM_ICR1H   	*((volatile u16*)0x47)
#define	MTIM_ICR1L  	*((volatile u16*)0x46)
#define	MTIM_ICR1   	*((volatile u16*)0x46)

/* INTERRUPT_REGISTERS */
#define MTIM_TIMSK  	*((volatile u8*)0x59)			//Timer/Counter Interrupt Mask Register
#define TIMSK_TOIE0		0								//Timer/Counter0 Overflow Interrupt Enable
#define TIMSK_OCIE0		1								//Timer/Counter0 Output Compare Match Interrupt Enable
#define TIMSK_TOIE1		2
#define TIMSK_OCIE1B	3
#define TIMSK_OCIE1A	4
#define TIMSK_TICIE1	5
#define TIMSK_TOIE2		6
#define TIMSK_OCIE2		7

#define MTIM_TIFR		*((volatile u8*)0x58)			//Timer/Counter Interrupt Flag Register
#define TIFR_TOV0		0								//Timer/Counter0 Overflow Flag
#define TIFR_OCF0		1								//Output Compare Flag 0
#define TIFR_TOV1		2
#define TIFR_OCF1B		3
#define TIFR_OCF1A		4
#define TIFR_ICF1		5
#define TIFR_TOV2		6
#define TIFR_OCF2		7


#endif
