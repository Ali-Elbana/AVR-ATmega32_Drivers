/*
 * DIO_programe.c
 *
 *  Created on: Sep 10, 2021
 *      Author: Ali El Bana
 */


#include "../../LIB/LSTD_TYPES.h"
#include "../../LIB/LBITMATH.h"

#include "MDIO_config.h"
#include "MDIO_private.h"
#include "MDIO_inter.h"




void MDIO_vSetPinDirection( u8 A_u8PortNum, u8 A_u8PinNum, u8 A_u8Dir )
{

	if( MDIO_OUTPUT == A_u8Dir )
	{

		switch( A_u8PortNum )
		{

			case MDIO_PORTA: SET_BIT( DDRA, A_u8PinNum ); break;

			case MDIO_PORTB: SET_BIT( DDRB, A_u8PinNum ); break;

			case MDIO_PORTC: SET_BIT( DDRC, A_u8PinNum ); break;

			case MDIO_PORTD: SET_BIT( DDRD, A_u8PinNum ); break;

		}



	}


	else if( MDIO_INPUT == A_u8Dir )
	{

		switch( A_u8PortNum )
		{

			case MDIO_PORTA: CLR_BIT( DDRA, A_u8PinNum); break;

			case MDIO_PORTB: CLR_BIT( DDRB, A_u8PinNum); break;

			case MDIO_PORTC: CLR_BIT( DDRC, A_u8PinNum); break;

			case MDIO_PORTD: CLR_BIT( DDRD, A_u8PinNum); break;

		}


	}




}


/**************************************************************************************************************/
/*************************************************************************************************************/

void MDIO_vSetPortDirection( u8 A_u8PortNum, u8 A_u8Dir )
{

	switch( A_u8PortNum )
	{

		case MDIO_PORTA: DDRA = A_u8Dir; break;

		case MDIO_PORTB: DDRB = A_u8Dir; break;

		case MDIO_PORTC: DDRC = A_u8Dir; break;

		case MDIO_PORTD: DDRD = A_u8Dir; break;
	}


}



/**************************************************************************************************************/
/*************************************************************************************************************/



void MDIO_vSetPinValue( u8 A_u8PortNum, u8 A_u8PinNum, u8 A_u8Val )
{

	if( MDIO_PIN_HIGH == A_u8Val )
	{

		switch( A_u8PortNum )
		{

			case MDIO_PORTA: SET_BIT( PORTA, A_u8PinNum ); break;

			case MDIO_PORTB: SET_BIT( PORTB, A_u8PinNum ); break;

			case MDIO_PORTC: SET_BIT( PORTC, A_u8PinNum ); break;

			case MDIO_PORTD: SET_BIT( PORTD, A_u8PinNum ); break;

		}



	}


	else if( MDIO_PIN_LOW == A_u8Val )
	{

		switch( A_u8PortNum )
		{

			case MDIO_PORTA: CLR_BIT( PORTA, A_u8PinNum ); break;

			case MDIO_PORTB: CLR_BIT( PORTB, A_u8PinNum ); break;

			case MDIO_PORTC: CLR_BIT( PORTC, A_u8PinNum ); break;

			case MDIO_PORTD: CLR_BIT( PORTD, A_u8PinNum ); break;

		}


	}




}



/**************************************************************************************************************/
/*************************************************************************************************************/


void MDIO_vSetPortValue( u8 A_u8PortNum, u8 A_u8Val )
{

	switch( A_u8PortNum )
	{

			case MDIO_PORTA: PORTA = A_u8Val; break;

			case MDIO_PORTB: PORTB = A_u8Val; break;

			case MDIO_PORTC: PORTC = A_u8Val; break;

			case MDIO_PORTD: PORTD = A_u8Val; break;

	}


}


/**************************************************************************************************************/
/*************************************************************************************************************/

u8  MDIO_u8GetPinValue( u8 A_u8PortNum, u8 A_u8PinNum )
{

	u8 L_u8PinValue = Initialized_by_Zero ;

	switch( A_u8PortNum )
	{

		case MDIO_PORTA: L_u8PinValue = GET_BIT( PINA, A_u8PinNum ); break;

		case MDIO_PORTB: L_u8PinValue = GET_BIT( PINB, A_u8PinNum ); break;

		case MDIO_PORTC: L_u8PinValue = GET_BIT( PINC, A_u8PinNum ); break;

		case MDIO_PORTD: L_u8PinValue = GET_BIT( PIND, A_u8PinNum ); break;

	}



	return L_u8PinValue;


}


/**************************************************************************************************************/
/*************************************************************************************************************/

u8  MDIO_u8GetPortValue( u8 A_u8PortNum )
{


	u8 L_u8PortValue = Initialized_by_Zero ;


	switch( A_u8PortNum )
	{

		case MDIO_PORTA: L_u8PortValue = PORTA; break;

		case MDIO_PORTB: L_u8PortValue = PORTB; break;

		case MDIO_PORTC: L_u8PortValue = PORTC; break;

		case MDIO_PORTD: L_u8PortValue = PORTD; break;

	}



	return L_u8PortValue;


}




