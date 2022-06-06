/* FILENAME: MEXTI_interface  
*  Author:  Ali El Bana
*  Version:  V1.0
*  DATE:   Sat 06/04/2022
*/
#ifndef _MEXTI_interface_H
#define _MEXTI_interface_H


#include "MEXTI_private.h"



void MEXTI_vInit				( void )															;

void MEXTI_vEnableInterrupt		( u8 A_u8EXTI_INTx )												;

void MEXTI_vDisableInterrupt	( u8 A_u8EXTI_INTx )												;

void MEXTI_vSetSenseControl		( u8 A_u8EXTI_INTx, u8 A_u8SenseCtrl )								;

void MEXTI_vSetCallBack			( u8 A_u8EXTI_INTx, void (*MEXTI_vpPointerTo_ISR_function) (void) ) ;



#define INT0 1

#define INT1 2

#define INT2 3



#define EXTI_FallingEdge 1

#define EXTI_RisingEdge  2

#define EXTI_LowLevel 	 3

#define EXTI_OnChange 	 4



#define Hash_Define_Methode 	RUN

#if 	Hash_Define_Methode == 	RUN


	#define ISR_INT0  	INT0_VectorNum


	#define ISR_INT1  	INT1_VectorNum


	#define ISR_INT2  	INT2_VectorNum


#endif







#endif //_MEXTI_interface_H
