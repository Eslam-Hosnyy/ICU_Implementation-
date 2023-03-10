/************************************/
/*	Author		: ESLAM_HOSNY		*/
/*	SWC			: PORT     			*/
/*	Layer		: MCAL				*/
/*	Version   	: 1.0				*/
/*	Date	  	: October 26, 2022	*/
/*	Last Edit 	: N/A           	*/
/************************************/

#include "LSTD_types.h"
#include "PORT_config.h"
#include "PORT_private.h"
#include "PORT_interface.h"

void PORT_voidInit(void)
{
    GPIOA_DDR = PORTA_DIR;
    GPIOB_DDR = PORTB_DIR;
    GPIOC_DDR = PORTC_DIR;
    GPIOD_DDR = PORTD_DIR;

    GPIOA_PORT = PORTA_INIT_VALUE;
    GPIOB_PORT = PORTB_INIT_VALUE;
    GPIOC_PORT = PORTC_INIT_VALUE;
    GPIOD_PORT = PORTD_INIT_VALUE;
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
