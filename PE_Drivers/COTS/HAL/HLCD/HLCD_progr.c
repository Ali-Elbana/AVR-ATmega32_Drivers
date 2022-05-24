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

#include<util/delay.h>






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


	u8 count   =  0  ;

	u8 arr[10] = {0} ;


	if( A_s32Num == 0 )
	{
		HLCD_vSendData( '0' ) ;

	}


	if ( A_s32Num < 0 )
	{

		HLCD_vSendData( '-' ) ;

		A_s32Num = A_s32Num * ( -1 ) ;

	}


	for( u8 i = 0 ; A_s32Num != 0 ; i++ )
	{

		count++ ;

		arr[i] = A_s32Num % 10 ;

		A_s32Num /= 10 ;


	}

	// For arrangement
	for ( s8 i = (count-1) ; i >= 0 ; i-- )
	{

		HLCD_vSendData( '0' + arr[i] ) ;


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

	HLCD_vSendCommand( 0x40 + (8*A_u8Address) ) ; //save in CGRAM


	for( u8 L_u8I = 0 ; L_u8I <8 ; L_u8I++ )
	{

		HLCD_vSendData( A_u8CustomChar[L_u8I] ) ;

	}


	HLCD_vSendCommand( 0x80 ) ; //Set DDRAM address

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

			case 0:	HLCD_vSendCommand( 0x80 + A_u8Col + 0 )  ; break;


			case 1: HLCD_vSendCommand( 0X80 + A_u8Col + 64 ) ; break;


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


