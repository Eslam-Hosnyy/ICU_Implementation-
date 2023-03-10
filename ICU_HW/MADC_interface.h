/************************************/
/*	Author	  :	ESLAM_HOSNY			*/
/*	SWC		  : ADC					*/
/*  Layer	  : MCAL				*/
/*	Version	  :	1.0		  			*/
/*	Date	  :	December 1, 2022	*/
/*	Last Edit : N/A					*/
/************************************/

#ifndef _MADC_INTERFACE_
#define _MADC_INTERFACE_


void MADC_voidInit(void);

u8 MADC_u8StartConversionSynch(u8 ARG_u8Channal,u16 *ARG_u8Reading,u32 *ARG_u32MillVolT);

u8 MADC_u8StartConversionASynch(u8 ARG_u8Channal,u16 *ARG_u8Reading,u32 *ARG_u32MillVolT, void(*ARG_pNotification)(void));



#endif
