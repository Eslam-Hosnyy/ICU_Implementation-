/************************************/
/*	Author	  :	ESLAM_HOSNY			*/
/*	SWC		  : ADC					*/
/*  Layer	  : MCAL				*/
/*	Version	  :	1.0		  			*/
/*	Date	  :	December 1, 2022	*/
/*	Last Edit : N/A					*/
/************************************/
#ifndef _MADC_CONFIG_
#define _MADC_CONFIG_

/* Voltage Reference Selection
 * 1 For Voltage Reference
 * 2 For AVCC Voltage (with external capacitor at AREF pin)
 * 3 For Internal_voltage ((2.56v) with external capacitor at AREF pin)*/
#define MADC_VOLTAGE_REF	2

/* ADC MAX_VOLTAGE(IN VOLT) */
#define MADC_MAX	5

/* ADC conversion ADIUST in the ADC Data_Register
 * 1 For Left_Adjust the result  (For 8-bits)
 * 2 For Right_Adjust the result (For 10-bits) */
#define MADC_RESELUTION		1

/* ADC Convertion Mode
 * 1 For Single_Converstion
 * 2 For Auto_Trigger*/
#define MADC_CONVERSTION_MODE		1

/* ADC Auto_Trigger Source (Only in Auto Trigger Mode)
 * 0 For Free Running Mode
 * 1 For Analog Comparator
 * 2 For External Interrupt Request 0
 * 3 For Timer/Counter0 Compare Match
 * 4 For Timer/Counter0 Overflow
 * 5 For Timer/Counter Compare Match B
 * 6 For Timer/Counter1 Overflow
 * 7 For Timer/Counter1 Capture Event  */
#define MADC_ATUOTRRIGER	0

/* Analog Channel and Gain Selection Bits [Choose and Write in ANALOG_CHANNAL One Of The Next Options]
 * SEADC0
 * SEADC1				* SEADC2				* SEADC3
 * SEADC4				* SEADC5				* SEADC6
 * SEADC7				* SEVbg					* SEGND
 * PDADC0_NDADC0x10		* PDADC1_NDADC0x10		* PDADC0_NDADC0x200
 * PDADC1_NDADC0x200	* PDADC2_NDADC2x10		* PDADC3_NDADC2x10
 * PDADC2_NDADC2x200	* PDADC3_NDADC2x200		* PDADC0_NDADC1x1
 * PDADC1_NDADC1x1		* PDADC2_NDADC1x1		* PDADC3_NDADC1x1
 * PDADC4_NDADC1x1		* PDADC5_NDADC1x1		* PDADC6_NDADC1x1
 * PDADC7_NDADC1x1		* PDADC0_NDADC2x1		* PDADC1_NDADC2x1
 * PDADC2_NDADC2x1		* PDADC3_NDADC2x1		* PDADC4_NDADC2x1
 * PDADC5_NDADC2x1  	*/
 #define ANALOG_CHANNAL	SEADC0  				//Choose One Of The Above Options

/* These bits determine the division factor between the XTAL frequency
 * and the input clock to the ADC (ADC Prescaler Select Bits).
* Prescalerx2			* Prescalerxx2
* Prescalerx4			* Prescalerx8
* Prescalerx16			* Prescalerx32
* Prescalerx64			* Prescalerx128			*/
#define MADC_Prescaler	Prescalerx2			//Choose One Of The Above Options

#define ADC_TimeOUT 50000


#endif
