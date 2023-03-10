/************************************/
/*	Author	  :	ESLAM_HOSNY 		*/
/*	SWC		  : GIE					*/
/*  Layer	  : MCAL				*/
/*	Version	  :	1.0		  			*/
/*	Date	  :	November 19, 2022	*/
/************************************/

#include "LSTD_types.h"
#include "LBIT_math.h"
#include "MGIE_interface.h"
#include "MGIE_private.h"

void MGIE_voidEnableGIE(void)
{
	SET_BIT(SREG, IBIT);
}

void MGIE_voidDisableGIE(void)
{
	CLEAR_BIT(SREG, IBIT);
}
