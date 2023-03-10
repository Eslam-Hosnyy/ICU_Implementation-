/************************************/
/*	Author		: ESLAM_HOSNY		*/
/*	SWC			: PORT     			*/
/*	Layer		: MCAL				*/
/*	Version   	: 1.0				*/
/*	Date	  	: October 26, 2022	*/
/*	Last Edit 	: N/A           	*/
/************************************/

#ifndef	_PORT_INTERFACE_H_
#define	_PORT_INTERFACE_H_

#define POSITIVE		1
#define INVERSE			2

void PORT_voidInit(void);

s32 MAP(s32 ARG_s32IMin, s32 ARG_s32IMax, s32 ARG_s32OMin, s32 ARG_s32OMax, s32 ARG_s32Val, u8 ARG_u8Relationship);

#endif
