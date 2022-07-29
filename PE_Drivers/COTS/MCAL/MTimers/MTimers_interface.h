/* FILENAME: MTimers_interface  
*  Author:  Ali El Bana
*  Version:  V1.0
*  DATE:   Fri 07/22/2022
*/
#ifndef _MTimers_interface_H
#define _MTimers_interface_H


typedef enum
{

	ICU_Falling ,

	ICU_Rising

}ICU_TriggerType;



void MTIMER0_vInit( void ) ;

void MTIMER1_vInit( void ) ;

void MTIMER2_vInit( void ) ;


void MTIMER1_vSetTopValue( u16 A_u16TopValue ) ;

void MTIMERS_vSetPreloadValue( u8 A_u8TimerID, u16 A_u16PreloadValue ) ;

void MTIMERS_vSetCompareValue( u8 A_u8TimerID, u16 A_u16CompareValue ) ;


void MTIMERS_vSetInterval_OVF_Asynch( u8 A_u8TimerID, u16 A_u16IntervalCounts,
										void(* A_Fptr_MTIMERS )(void) ) ;

void MTIMERS_vSetInterval_CTC_Asynch( u8 A_u8TimerID, u16 A_u16CompareValue,
								u16 A_u16IntervalCounts, void(* A_Fptr_MTIMERS )(void) ) ;


void MTIMERS_vStartTimer   ( u8 A_u8TimerID ) ;

void MTIMERS_vStopTimer    ( u8 A_u8TimerID ) ;


u16 MTIMERS_u16GetCapturedValue( void ) ;

u16 MTIMERS_u16GetElapsedTime( u8 A_u8TimerID ) ;

void MTIMERS_vSetICU_Trigger  ( ICU_TriggerType A_xICU_Trigger       ) ;

void MTIMERS_vEnableInterrupt ( u8 A_u8TimerID, u8 A_u8InterruptType ) ;

void MTIMERS_vDisableInterrupt( u8 A_u8TimerID, u8 A_u8InterruptType ) ;

void MTIMERS_vSetCallBack( u8 A_u8TimerID, u8 A_u8InterruptType, void (*A_Fptr)(void) ) ;



/*************************************TIMER0 INTERFACE MACROS*********************************************/

#define TIMER0 1
#define TIMER1 2
#define TIMER2 3

#define TIMER0_OVF 		1
#define TIMER0_COMP 	2

#define TIMER0_OVF_INT 1
#define TIMER0_CTC_INT 2

#define TIMER0_IntervalCounts  2000
#define TIMER0_PreloadValue 	0

#define TIMER0_CompareValue		250


/****************************************TIMER1 INTERFACE MACROS******************************************/

#define TIMER1 2


#define TIMER1_TopValue 	20000

#define TIMER1_CompareValue	1000

#define TIMER1_ICU_INT		1
#define TIMER1_CTC1A_INT	2
#define TIMER1_CTC1B_INT	3
#define TIMER1_OVF_INT		4


/*****************************************TIMER2 INTERFACE MACROS*****************************************/

#define TIMER2 3


#define TIMER2_OVF_INT 1
#define TIMER2_CTC_INT 2












/**********************************************************************************/

#endif //_MTimers_interface_H
