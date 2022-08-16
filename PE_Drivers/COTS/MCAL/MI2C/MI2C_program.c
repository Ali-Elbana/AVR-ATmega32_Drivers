/* FILENAME: MI2C_program 
*  Author:  Ali El Bana
*  Version:  V1.0
*  DATE:   Sat 08/06/2022
*/

#include "../../LIB/LSTD_TYPES.h"
#include "../../LIB/LBITMATH.h"

#include "MI2C_interface.h"
#include "MI2C_private.h"
#include "MI2C_config.h"






/*************************************************************/
/*************************************************************/

void MI2C_vInit( void )
{

	// 1-Selecting the division factor for the bit rate generator.
	TWBR = I2C_Prescaler ;


	// 2-Write Collision Flag Enable/DISABLE.
	#if WriteCollisionFlag_Mode == Enable

		SET_BIT( TWCR, TWCR_TWWC ) ;

	#elif WriteCollisionFlag_Mode == DISABLE

		CLR_BIT( TWCR, TWCR_TWWC ) ;

	#endif


	// 3-Interrupt Enable/DISABLE.
	#if MI2C_Interrupt_Mode == Enable

		SET_BIT( TWCR, TWCR_TWIE ) ;

	#elif MI2C_Interrupt_Mode == DISABLE

		CLR_BIT( TWCR, TWCR_TWIE ) ;

	#endif


	// 4-Enable I2C Peripheral.
	SET_BIT( TWCR, TWCR_TWEN ) ;

}

/*************************************************************/
/*************************************************************/

u8 MI2C_u8SendStartCondition( void )
{

	u8 L_u8MyStatus = Initialized_by_Zero ;

	TWCR = (1 << TWCR_TWINT) | (1 << TWCR_TWSTA) | (1 << TWCR_TWEN) ;

	// Wait for TWINT Flag set. This indicates that the START condition has been transmitted.
	while( !( TWCR & (1 << TWCR_TWINT) ) ) ;

	// Check the status code.
	L_u8MyStatus = ( TWSR & 0xF8 ) ;

	return L_u8MyStatus ;

}

/*************************************************************/
/*************************************************************/

u8 MI2C_u8SendRepeatedStartCondition( void )
{

	u8 L_u8MyStatus = Initialized_by_Zero ;

	TWCR = (1 << TWCR_TWINT) | (1 << TWCR_TWSTA) | (1 << TWCR_TWEN) ;

	// Wait for TWINT Flag set. This indicates that the START condition has been transmitted.
	while( !( TWCR & (1 << TWCR_TWINT) ) ) ;

	// Check the status code.
	L_u8MyStatus = ( TWSR & 0xF8 ) ;

	return L_u8MyStatus ;

}

/*************************************************************/
/*************************************************************/

u8 MI2C_u8SendSlaveAddressRW( u8 A_u8Sla, u8 A_u8Rw )
{

	u8 L_u8MyStatus = Initialized_by_Zero ;

	TWDR = (A_u8Sla << 1) | (A_u8Rw) ;

	TWCR = (1 << TWCR_TWINT) | (1 << TWCR_TWEN) ;

	// Clear the start bit.
	CLR_BIT( TWCR, TWCR_TWSTA ) ;

	while( !( TWCR & (1 << TWCR_TWINT) ) ) ;

	L_u8MyStatus = ( TWSR & 0xF8 ) ;

	return L_u8MyStatus ;

}

/*************************************************************/
/*************************************************************/

u8 MI2C_u8SendByte( u8 A_u8Byte )
{

	u8 L_u8MyStatus = Initialized_by_Zero ;

	TWDR = A_u8Byte ;

	TWCR = (1 << TWCR_TWINT) | (1 << TWCR_TWEN) ;

	while( !( TWCR & (1 << TWCR_TWINT) ) ) ;

	L_u8MyStatus = ( TWSR & 0xF8 ) ;

	return L_u8MyStatus ;

}

/*************************************************************/
/*************************************************************/

u8 MI2C_u8RecieveByte( u8 *A_Pu8Byte, u8 A_u8Ack )
{

	u8 L_u8MyStatus = Initialized_by_Zero ;

	switch( A_u8Ack )
	{
		case MI2C_ACK : TWCR = (1 << TWCR_TWINT) | (1 << TWCR_TWEN) | (1 << TWCR_TWEA) ; break ;

		case MI2C_NACK: TWCR = (1 << TWCR_TWINT) | (1 << TWCR_TWEN) ; CLR_BIT( TWCR, TWCR_TWEA ) ; break ;
	}

	while( !( TWCR & (1 << TWCR_TWINT) ) ) ;

	*A_Pu8Byte = TWDR ;

	L_u8MyStatus = ( TWSR & 0xF8 ) ;

	return L_u8MyStatus ;

}

/*************************************************************/
/*************************************************************/

u8 MI2C_u8SendStopCondition( void )
{

	u8 L_u8MyStatus = Initialized_by_Zero ;

	TWCR = (1 << TWCR_TWINT) | (1 << TWCR_TWEN) | (1 << TWCR_TWSTO) ;

	L_u8MyStatus = ( TWSR & 0xF8 ) ;

	return L_u8MyStatus ;

}

/*************************************************************/
/*************************************************************/

u8 MI2C_u8GetStatus( void )
{

	u8 L_u8MyStatus = Initialized_by_Zero ;

	L_u8MyStatus = ( TWSR & 0xF8 ) ;

	return L_u8MyStatus ;

}

/*************************************************************/
/*************************************************************/






































