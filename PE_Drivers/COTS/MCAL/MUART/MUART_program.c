/* FILENAME: MUART_program 
*  Author:  Ali El Bana
*  Version:  V1.0
*  DATE:   Mon 08/01/2022
*/

#include "../../LIB/LSTD_TYPES.h"
#include "../../LIB/LBITMATH.h"

#include "MUART_interface.h"
#include "MUART_private.h"
#include "MUART_config.h"

#include "string.h"


static void (*GS_Global_UART_CallBack[UART_ISR_Options])(void) = { NULL } ;

static u8* GS_Pu8Internal_TXBuffer = NULL ;

static u16 GS_u16TXBufferCounter = Initialized_by_Zero ;

static u8* GS_Pu8Internal_RXBuffer = NULL ;

static u16 GS_u16RXBufferCounter = Initialized_by_Zero ;

/*************************************************************/
/*************************************************************/

void MUART_vInit( void )
{

	// 1-ENABLE/DISABLE interrupt sources.

	// 1a-ENABLE/DISABLE RX complete.
	#if RX_Interrupt_Mode == ENABLE

		SET_BIT( UCSRB, UCSRB_RXCIE );

	#elif RX_Interrupt_Mode == DISABLE

		CLR_BIT( UCSRB, UCSRB_RXCIE );

	#endif

	// 1b-ENABLE/DISABLE TX complete.
	#if TX_Interrupt_Mode == ENABLE

		SET_BIT( UCSRB, UCSRB_TXCIE );

	#elif TX_Interrupt_Mode == DISABLE

		CLR_BIT( UCSRB, UCSRB_TXCIE );

	#endif

	// 1c-ENABLE/DISABLE TX empty.
	#if DataRegister_Interrupt_Mode == ENABLE

		SET_BIT( UCSRB, UCSRB_UDRIE );

	#elif DataRegister_Interrupt_Mode == DISABLE

		CLR_BIT( UCSRB, UCSRB_UDRIE );

	#endif


	// 2-ENABLE RX and TX.
	SET_BIT( UCSRB, UCSRB_RXEN ) ;
	SET_BIT( UCSRB, UCSRB_TXEN ) ;


	// 3-Set character size -> 5,6,7,8,9.
	#if Data_Character_Size == CharacterSize_5bits

	CLR_BIT( UCSRB, UCSRB_UCSZ2 ) ;

	UCSRC = ( (1 << UCSRC_URSEL) & ~(1 << UCSRC_UCSZ1) & ~(1 << UCSRC_UCSZ0) ) ;

	CLR_BIT( UCSRB, UCSRB_RXB8 ) ;
	CLR_BIT( UCSRB, UCSRB_TXB8 ) ;

	#elif Data_Character_Size == CharacterSize_6bits

	CLR_BIT( UCSRB, UCSRB_UCSZ2 ) ;

	UCSRC = ( (1 << UCSRC_URSEL) & ~(1 << UCSRC_UCSZ1) | (1 << UCSRC_UCSZ0) ) ;

	CLR_BIT( UCSRB, UCSRB_RXB8 ) ;
	CLR_BIT( UCSRB, UCSRB_TXB8 ) ;

	#elif Data_Character_Size == CharacterSize_7bits

	CLR_BIT( UCSRB, UCSRB_UCSZ2 ) ;

	UCSRC = ( (1 << UCSRC_URSEL) | (1 << UCSRC_UCSZ1) & ~(1 << UCSRC_UCSZ0) ) ;

	CLR_BIT( UCSRB, UCSRB_RXB8 ) ;
	CLR_BIT( UCSRB, UCSRB_TXB8 ) ;

	#elif Data_Character_Size == CharacterSize_8bits

	CLR_BIT( UCSRB, UCSRB_UCSZ2 ) ;

	UCSRC = ( (1 << UCSRC_URSEL) | (1 << UCSRC_UCSZ1) | (1 << UCSRC_UCSZ0) ) ;

	CLR_BIT( UCSRB, UCSRB_RXB8 ) ;
	CLR_BIT( UCSRB, UCSRB_TXB8 ) ;

	#elif Data_Character_Size == CharacterSize_9bits

	SET_BIT( UCSRB, UCSRB_UCSZ2 ) ;

	UCSRC = ( (1 << UCSRC_URSEL) | (1 << UCSRC_UCSZ1) | (1 << UCSRC_UCSZ0) ) ;

	SET_BIT( UCSRB, UCSRB_RXB8 ) ;
	SET_BIT( UCSRB, UCSRB_TXB8 ) ;

	#endif


	// 4-Set UART mode: ASYNC OR SYNC
	#if USART_Mode_Select == Asynchronous_Operation

	CLR_BIT( UCSRC, UCSRC_UMSEL ) ;

	#elif USART_Mode_Select == Synchronous_Operation

	SET_BIT( UCSRC, UCSRC_UMSEL ) ;

	#endif


	// 5-Set parity mode : DIS, EVEN ,ODD
	#if Parity_Mode == Parity_Disabled

	CLR_BIT( UCSRC, UCSRC_UPM1 ) ;
	CLR_BIT( UCSRC, UCSRC_UPM0 ) ;

	#elif Parity_Mode == Enabled_EvenParity

	SET_BIT( UCSRC, UCSRC_UPM1 ) ;
	CLR_BIT( UCSRC, UCSRC_UPM0 ) ;

	#elif Parity_Mode == Enabled_OddParity

	SET_BIT( UCSRC, UCSRC_UPM1 ) ;
	SET_BIT( UCSRC, UCSRC_UPM0 ) ;

	#endif


	// 6-Set num of stop bits: 1,2
	#if Stop_Bit_Select == One_StopBit

	CLR_BIT( UCSRC, UCSRC_USBS ) ;

	#elif Stop_Bit_Select == Two_StopBits

	SET_BIT( UCSRC, UCSRC_USBS ) ;

	#endif


	//7-set CLK polarity -> with synch. mode only
	#if USART_Mode_Select == Synchronous_Operation

		#if Clock_Polarity_Status == RisingTx_FallingRx

			CLR_BIT( UCSRC, UCSRC_UCPOL) ;

		#elif Clock_Polarity_Status == FallingTx_RisingRx

			SET_BIT( UCSRC, UCSRC_UCPOL) ;

		#endif

	#endif


	// 8-Set BAUD RATE
	UBRRL = BaudRate_Options ;


}

/*************************************************************/
/*************************************************************/

void UART_vSetBAUDRate( u8 A_u8UBRR_Value )
{

	UBRRL = A_u8UBRR_Value ;

}


/*************************************************************/
/*************************************************************/

void MUART_vTransmit( u8 A_u8Data )
{

	// Wait for empty transmit buffer.
	while ( !( UCSRA & (1 << UCSRA_UDRE)) ) ;

	// Put data into buffer, sends the data.
	UDR = A_u8Data ;

}

/*************************************************************/
/*************************************************************/

u8 MUART_u8Receive( void )
{

	// Wait for data to be received.
	while ( !(UCSRA & (1 << UCSRA_RXC)) ) ;

	// Get and return received data from buffer.
	return UDR;

}

/*************************************************************/
/*************************************************************/

void MUART_vENABLE( void )
{

	// ENABLE RX and TX.
	SET_BIT( UCSRB, UCSRB_RXEN ) ;
	SET_BIT( UCSRB, UCSRB_TXEN ) ;

}

/*************************************************************/
/*************************************************************/

void MUART_vDISABLE( void )
{

	// DISABLE RX and TX.
	CLR_BIT( UCSRB, UCSRB_RXEN ) ;
	CLR_BIT( UCSRB, UCSRB_TXEN ) ;

}

/*************************************************************/
/*************************************************************/

s8 MUART_s8GetUDR( void )
{
	return UDR ;
}

/*************************************************************/
/*************************************************************/

void MUART_vRecieveString( c8 A_c8YourString[] )
{

	u32 L_u32Counter = Initialized_by_Zero ;

	A_c8YourString[L_u32Counter] = MUART_u8Receive( ) ;

	while( A_c8YourString[L_u32Counter] != '\0' )
	{

		L_u32Counter++ ;

		A_c8YourString[L_u32Counter] = MUART_u8Receive( ) ;

		if( (A_c8YourString[L_u32Counter] == '\n') || (A_c8YourString[L_u32Counter] == '\r') )
		{
			A_c8YourString[L_u32Counter] = '\0' ;
		}

	}

}

/*************************************************************/
/*************************************************************/

void MUART_vTransmitString( c8 *A_c8MyString )
{

	while ( *A_c8MyString )
	{

		MUART_vTransmit( *A_c8MyString ++ ) ;

	}

}

/*************************************************************/
/*************************************************************/

u8 MUART_u8CompareString( c8 *String1, c8 *String2 )
{

	u8 L_u8TheComparingResult = Initialized_by_Zero ;


    if( strcmp( String1, String2 ) == Equal_Strings )
	{

    	L_u8TheComparingResult =  Equal_Strings ; // the strings compare

    }


    else
	{
    	L_u8TheComparingResult = Not_Equal_Strings ;
    }



	return L_u8TheComparingResult ;

}

/*************************************************************/
/*************************************************************/

void MUART_vFlush( void )
{

	u8 L_u8Dummy ;

	while ( UCSRA & (1 << UCSRA_RXC) )
	{

		L_u8Dummy = UDR;

	}

}


/*************************************************************/
/*************************************************************/

void MUART_vEnableInterrupt( u8 A_u8InterruptID )
{

	switch( A_u8InterruptID )
	{

		case RXC_INT :  SET_BIT( UCSRB, UCSRB_RXCIE ) ; break;

	    case UDRE_INT:  SET_BIT( UCSRB, UCSRB_UDRIE ) ; break;

	    case TXC_INT :  SET_BIT( UCSRB, UCSRB_TXCIE ) ; break;

	}

}

/*************************************************************/
/*************************************************************/

void MUART_vDisableInterrupt( u8 A_u8InterruptID )
{

	switch( A_u8InterruptID )
	{

		case RXC_INT :  CLR_BIT( UCSRB, UCSRB_RXCIE ) ; break;

	    case UDRE_INT:  CLR_BIT( UCSRB, UCSRB_UDRIE ) ; break;

	    case TXC_INT :  CLR_BIT( UCSRB, UCSRB_TXCIE ) ; break;

	}

}

/*************************************************************/
/*************************************************************/

void MUART_vTransmit_Asynch( c8 A_c8MyString[], void (*A_Fptr)(void) )
{

	GS_Global_UART_CallBack[UART_ISR_TXC]  = A_Fptr ;

	GS_Pu8Internal_TXBuffer = A_c8MyString ;

	MUART_vEnableInterrupt( TXC_INT ) ;

	// In case empty transmit buffer.
	if ( GET_BIT(UCSRA, UCSRA_UDRE) == 0 )
	{

		UDR = A_c8MyString[0] ;

		GS_u16TXBufferCounter++ ;

	}

	else
	{

		// #error "The transmit buffer isn't empty yet"

	}

}

/*************************************************************/
/*************************************************************/

void MUART_vRecieve_Asynch( c8 A_c8YourString[], void (*A_Fptr)(void) )
{

	GS_Global_UART_CallBack[UART_ISR_RXC]  = A_Fptr ;

	GS_Pu8Internal_RXBuffer = A_c8YourString ;

	MUART_vEnableInterrupt( RXC_INT ) ;

}

/*************************************************************/
/*************************************************************/

void MUART_vSetCallBack( u8 A_u8ISR_ID, void (*A_Fptr)(void) )
{

	switch( A_u8ISR_ID )
	{

		case RXC_ISR:  GS_Global_UART_CallBack[UART_ISR_RXC]  = A_Fptr ; break;

		case UDRE_ISR: GS_Global_UART_CallBack[UART_ISR_UDRE] = A_Fptr ; break;

		case TXC_ISR:  GS_Global_UART_CallBack[UART_ISR_TXC]  = A_Fptr ; break;

	}

}

/*************************************************************/
/*************************************************************/

UART_RXC_ISR
{

	if ( GS_Global_UART_CallBack[UART_ISR_RXC] != NULL )
	{

		GS_Global_UART_CallBack[UART_ISR_RXC]( ) ;

	}

	if( (GS_Pu8Internal_RXBuffer[GS_u16RXBufferCounter] != '\n') ||
		(GS_Pu8Internal_RXBuffer[GS_u16RXBufferCounter] != '\r') )
	{
		GS_Pu8Internal_RXBuffer[GS_u16RXBufferCounter] = UDR ;

		GS_u16RXBufferCounter ++ ;
	}

	else
	{
		GS_Pu8Internal_RXBuffer[GS_u16RXBufferCounter] = '\0' ;
	}

}

/*************************************************************/
/*************************************************************/

UART_UDRE_ISR
{


	if ( GS_Global_UART_CallBack[UART_ISR_UDRE] != NULL )
	{

		GS_Global_UART_CallBack[UART_ISR_UDRE]( ) ;

	}



}

/*************************************************************/
/*************************************************************/

UART_TXC_ISR
{

	if ( GS_Global_UART_CallBack[UART_ISR_TXC] != NULL )
	{

		GS_Global_UART_CallBack[UART_ISR_TXC]( ) ;

	}

	if( GS_Pu8Internal_TXBuffer[GS_u16TXBufferCounter] != '\0' )
	{
		UDR = GS_Pu8Internal_TXBuffer[ GS_u16TXBufferCounter ] ;

		GS_u16TXBufferCounter++ ;
	}

	else
	{

		MUART_vDisableInterrupt( TXC_INT ) ;

	}



}

/*************************************************************/
/*************************************************************/

























