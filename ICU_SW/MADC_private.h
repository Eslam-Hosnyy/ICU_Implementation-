/************************************/
/*	Author	  :	ESLAM_HOSNY			*/
/*	SWC		  : ADC					*/
/*  Layer	  : MCAL				*/
/*	Version	  :	1.0		  			*/
/*	Date	  :	December 1, 2022	*/
/*	Last Edit : N/A					*/
/************************************/

#ifndef _MADC_PRIVATE_
#define _MADC_PRIVATE_

#define MADC_ADMUX		*((volatile u8*)0x27)		//ADC multiplexer selection Register
#define ADMUX_REFS1		7							//Reference Selection bit1
#define ADMUX_REFS0		6							//Reference Selection bit0
#define ADMUX_ADLAR		5							//ADC left adjust result
#define ADMUX_MASK		0b11100000

#define MADC_ADCSRA		*((volatile u8*)0x26)		//ADC control and status register A
#define ADCSRA_ADEN		7							//ADC enable
#define ADCSRA_ADSC		6							//Start conversion
#define ADCSRA_ADATE	5							//Auto Trigger enable
#define ADCSRA_ADIF		4							//Interrupt flag
#define ADCSRA_ADIE		3							//Interrupt enable
#define ADCSRA_ADPS2	2							//Prescaler bit2
#define ADCSRA_ADPS1	1							//Prescaler bit1
#define ADCSRA_ADPS0	0							//Prescaler bit0
#define ADCSRA_MASK		0b11111000

#define MADC_SFIOR		*((volatile u8*)0x50)
#define SFIOR_ADTS2		7
#define SFIOR_ADTS1		6
#define SFIOR_ADTS0		5
#define SFIOR_MASK		0b00011111

#define MADC_ADCH		*((volatile u8*)0x25)		//ADC high register
#define MADC_ADCL		*((volatile u8*)0x24)		//ADC Low register
#define MADC			*((volatile u16*)0x24)		//FOR 10-Bits Result_Mode

#define IDLE			0
#define BUSY			1


#define SEADC0				00000
#define SEADC1				00001
#define SEADC2				00010
#define SEADC3				00011
#define SEADC4				00100
#define SEADC5				00101
#define SEADC6				00110
#define SEADC7				00111
#define SEVbg				11110
#define SEGND				11111
#define PDADC0_NDADC0x10	01000
#define PDADC1_NDADC0x10	01001
#define PDADC0_NDADC0x200	01010
#define PDADC1_NDADC0x200	01011
#define PDADC2_NDADC2x10	01100
#define PDADC3_NDADC2x10	01101
#define PDADC2_NDADC2x200	01110
#define PDADC3_NDADC2x200	01111
#define PDADC0_NDADC1x1		10000
#define PDADC1_NDADC1x1		10001
#define PDADC2_NDADC1x1		10010
#define PDADC3_NDADC1x1		10011
#define PDADC4_NDADC1x1		10100
#define PDADC5_NDADC1x1		10101
#define PDADC6_NDADC1x1		10110
#define PDADC7_NDADC1x1		10111
#define PDADC0_NDADC2x1		11000
#define PDADC1_NDADC2x1		11001
#define PDADC2_NDADC2x1		11010
#define PDADC3_NDADC2x1		11011
#define PDADC4_NDADC2x1		11100
#define PDADC5_NDADC2x1		11101

#define Prescalerx2			0
#define Prescalerxx2		1
#define Prescalerx4			2
#define Prescalerx8			3
#define Prescalerx16		4
#define Prescalerx32		5
#define Prescalerx64		6
#define Prescalerx128		7
#endif

