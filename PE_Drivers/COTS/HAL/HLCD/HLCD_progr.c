/*
 * LCD_programme.c
 *
 *  Created on: Sep 11, 2021
 *      Author: Ali El Bana
 */

#include "../../LIB/LSTD_TYPES.h"

#include "../../MCAL/MDIO/MDIO_inter.h"

#include "../../HAL/HLCD/HLCD_inter.h"
#include "../../HAL/HLCD/HLCD_config.h"
#include "../../HAL/HLCD/HLCD_private.h"

#include <util/delay.h>






void HLCD_vInit(void)
{


	_delay_ms(1000);

	// Set your pin directions.
	MDIO_vSetPinDirection ( HLCD_CTRL_PORT, HLCD_RS_PIN, MDIO_OUTPUT ) ;
	MDIO_vSetPinDirection ( HLCD_CTRL_PORT, HLCD_RW_PIN, MDIO_OUTPUT ) ;
	MDIO_vSetPinDirection ( HLCD_CTRL_PORT, HLCD_EN_PIN, MDIO_OUTPUT ) ;
	MDIO_vSetPortDirection( HLCD_DATA_PORT, MDIO_PORT_HIGH ) 		   ;


	// Start initialization sequence.
	_delay_ms(50);

	HLCD_vSendCommand( HLCD_FuctionSet_Cmd ) 	;

	_delay_ms(1);

	HLCD_vSendCommand( HLCD_DispOnOffCTRL_Cmd ) ;

	_delay_ms(1);

	HLCD_vSendCommand( HLCD_DispClear_Cmd ) 	;

	_delay_ms(3);

	HLCD_vSendCommand( HLCD_EntryModeSet_Cmd ) 	;

	_delay_ms(1);


}



/**************************************************************************************************************/
/*************************************************************************************************************/



void HLCD_vSendCommand(u8 A_u8Cmd)
{

	// Set RS pin low to send a command.
	MDIO_vSetPinValue( HLCD_CTRL_PORT, HLCD_RS_PIN, MDIO_PIN_LOW) ;

	// Set RW pin low to write the command.
	MDIO_vSetPinValue( HLCD_CTRL_PORT, HLCD_RW_PIN, MDIO_PIN_LOW) ;

	_delay_ms(1);

	// Put the command on the data bus.
	MDIO_vSetPortValue( HLCD_DATA_PORT, A_u8Cmd ) ;

	_delay_ms(1);

	// Set the enable pin high.
	MDIO_vSetPinValue( HLCD_CTRL_PORT, HLCD_EN_PIN, MDIO_PIN_HIGH ) ;

	_delay_ms(1);

	// Set the enable pin low.
	MDIO_vSetPinValue( HLCD_CTRL_PORT, HLCD_EN_PIN, MDIO_PIN_LOW ) ;

	_delay_ms(1);


}



/**************************************************************************************************************/
/*************************************************************************************************************/



void HLCD_vSendData(u8 A_u8Data)
{

	// Set RS pin high to send data.
	MDIO_vSetPinValue( HLCD_CTRL_PORT, HLCD_RS_PIN, MDIO_PIN_HIGH ) ;

	// Set RW pin low to write the data.
	MDIO_vSetPinValue( HLCD_CTRL_PORT, HLCD_RW_PIN, MDIO_PIN_LOW ) ;

	_delay_ms(1);

	// Put the data on the data bus.
	MDIO_vSetPortValue( HLCD_DATA_PORT, A_u8Data ) ;

	_delay_ms(1);

	// Set the enable pin high.
	MDIO_vSetPinValue( HLCD_CTRL_PORT, HLCD_EN_PIN, MDIO_PIN_HIGH ) ;

	_delay_ms(1);

	// Set the enable pin low.
	MDIO_vSetPinValue( HLCD_CTRL_PORT, HLCD_EN_PIN, MDIO_PIN_LOW) ;

	_delay_ms(1);


}



/**************************************************************************************************************/
/*************************************************************************************************************/



void HLCD_vClear(void)
{

	_delay_us( 0.5 );

	HLCD_vSendCommand( HLCD_DispClear_Cmd ) ;

	_delay_ms(1);



}



/**************************************************************************************************************/
/*************************************************************************************************************/


void HLCD_vDispString( c8 *A_c8Char )
{


	for( u8 L_u8I = 0 ; A_c8Char[L_u8I] != '\0' ; L_u8I++ )
	{


		HLCD_vSendData( A_c8Char[L_u8I] ) ;


	}



}



/**************************************************************************************************************/
/*************************************************************************************************************/


void HLCD_vDispNumber(s32 A_s32Num)
{


	u8 L_u8Counter 		=  	0  	;

	u8 LR_u8Digits[10] 	= 	{0} ;


	// In case the number is signed.
	if ( A_s32Num < 0 )
	{

		HLCD_vSendData( '-' ) ;

		A_s32Num = A_s32Num * ( -1 ) ;

	}


	// In case the number the number contains zeros.
	if( A_s32Num == 0 )
	{
		HLCD_vSendData( '0' ) ;

	}


	// Save reversed digits in the array.
	for( L_u8Counter = 0 ; A_s32Num != 0 ; L_u8Counter++ )
	{

		LR_u8Digits[L_u8Counter] = A_s32Num % 10 ;

		A_s32Num /= 10 ;

	}


	// For arrangement the digits.
	for ( s8 L_s8ArrangedNums = (L_u8Counter-1) ; L_s8ArrangedNums >= 0 ; L_s8ArrangedNums-- )
	{

		HLCD_vSendData( '0' + LR_u8Digits[ L_s8ArrangedNums ] ) ;

	}




}



/**************************************************************************************************************/
/*************************************************************************************************************/



//void HLCD_vDispNum(s32 A_s32Num)
//{
//
//
//	u32 L_u32Rev = 0 ;
//
//	while( A_s32Num >0 )
//	{
//
//		L_u32Rev = L_u32Rev*10 + (A_s32Num % 10) ;
//
//		A_s32Num /= 10 ;
//
//	}
//
//
//	while( L_u32Rev >0 )
//	{
//
//		HLCD_vSendData( (L_u32Rev % 10) + '0' ) ; // Convert from integer to char.
//
//		L_u32Rev /= 10 ;
//
//	}
//
//
//
//
//}



/**************************************************************************************************************/
/*************************************************************************************************************/



void HLCD_vSaveCustomChar( u8 A_u8Address, u8 *A_u8CustomChar )
{

	// 1-Set CGRAM Address.
	HLCD_vSendCommand( SET_CGRAM_AC_MASK + (NumOf_CGRAM_Patterns * A_u8Address) ) ;

	// 2- Send custom char data.
	for( u8 L_u8I = FirstByteInCGRAM_Pattern ; L_u8I < LastByteInCGRAM_Pattern ; L_u8I++ )
	{

		HLCD_vSendData( A_u8CustomChar[L_u8I] ) ;

	}

	// 3-Set DDRAM address
	HLCD_vSendCommand( SET_DDRAM_AC_MASK ) ;

}



/**************************************************************************************************************/
/*************************************************************************************************************/


void HLCD_vGoTo( u8 A_u8Row, u8 A_u8Col )
{



	// Valid Range.
	if ( (A_u8Row <= MAX_IDX_OF_ROWS) && (A_u8Col <= MAX_IDX_OF_COL) )
	{

		switch( A_u8Row )
		{

			case 0:	HLCD_vSendCommand( SET_DDRAM_AC_MASK + A_u8Col + FIRST_ROW_START ) ; break;


			case 1: HLCD_vSendCommand( SET_DDRAM_AC_MASK + A_u8Col + SEC_ROW_START 	 ) ; break;


		}


	}


	else
	{

		// Do Nothing

	}



}



/**************************************************************************************************************/
/*************************************************************************************************************/


void HLCD_vSetShiftLeftOn(void)
{

	_delay_ms(500);

	HLCD_vSendCommand( HLCD_EntryModeSet_ShiftLeftOn_Cmd ) ;

	_delay_ms(500);



}


/**************************************************************************************************************/
/*************************************************************************************************************/




void HLCD_vSetDispOFF(void)
{

	_delay_ms(500);

	HLCD_vSendCommand( HLCD_DispOff_Cmd ) ;

	_delay_ms(500);



}




/**************************************************************************************************************/
/*************************************************************************************************************/


void HLCD_vDispCursorWithBlinking(void)
{

	_delay_ms(500);

	HLCD_vSendCommand( HLCD_DispCursorWithBlinking_Cmd ) ;

	_delay_ms(500);



}


/**************************************************************************************************************/
/*************************************************************************************************************/



void HLCD_vSetCursorBlinkingOFF(void)
{

	_delay_ms(500);

	HLCD_vSendCommand( HLCD_SetCursorBlinkingOFF_Cmd ) ;

	_delay_ms(500);



}



/**************************************************************************************************************/
/*************************************************************************************************************/

void HLCD_vDispShiftLeftString( c8 *A_c8Char )
{

	u8 L_u8I = 0 ;


	for( L_u8I = 0 ; A_c8Char[L_u8I] != '\0' ; L_u8I++ )
	{


		HLCD_vSendData( A_c8Char[L_u8I] ) ;


	}


	_delay_ms(500);


	if( L_u8I > HLCD_CharactersNums )
	{

		for( register u8 i = 0 ; i < L_u8I - HLCD_CharactersNums ; i++ )
		{

			HLCD_vSetShiftLeftOn() ;

		}

	}



}



/**************************************************************************************************************/
/*************************************************************************************************************/


