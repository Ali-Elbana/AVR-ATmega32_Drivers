/* FILENAME: MADC_interface  
*  Author:  Ali El Bana
*  Version:  V1.0
*  DATE:   Sun 07/10/2022
*/
#ifndef _MADC_interface_H
#define _MADC_interface_H

#include "MADC_private.h"



/* Polling based APIs */

void MADC_vInit( void ) ;

u16 MADC_u16ConvertAnalog_to_Digital( u8 A_u8ChannelNum ) ;


/* Interrupt based APIs */

void MADC_vStartConversion( u8 A_u8ChannelNum ) ;

u16 MADC_GetADCData( void );

void MADC_vSetCallBack( void (*MEXTI_vpPointerTo_ISR_function) (void) ) ;


#define CHANNEL_00 0
#define CHANNEL_01 1
#define CHANNEL_02 2
#define CHANNEL_03 3
#define CHANNEL_04 4
#define CHANNEL_05 5
#define CHANNEL_06 6
#define CHANNEL_07 7

#define CHANNEL_P0_N0_G10 8
#define CHANNEL_P1_N0_G10 9


#define Hash_Define_Methode 	RUN
#if 	Hash_Define_Methode == 	RUN

	#define ADC_ISR ADC_VectorNum

#endif






#endif //_MADC_interface_H
