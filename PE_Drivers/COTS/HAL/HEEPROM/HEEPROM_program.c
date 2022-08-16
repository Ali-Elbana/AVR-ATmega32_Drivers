/* FILENAME: HEEPROM_program 
*  Author:  Ali El Bana
*  Version:  V1.0
*  DATE:   Mon 08/15/2022
*/

#include "../../LIB/LSTD_TYPES.h"
#include "../../LIB/LBITMATH.h"

#include "HEEPROM_interface.h"
#include "HEEPROM_private.h"
#include "HEEPROM_config.h"

#include "../../MCAL/MI2C/MI2C_interface.h"




/*************************************************************/
/*************************************************************/

void HEEPROM_vWriteByte( u8 A_u8MyByte, u16 A_u16Address )
{

	u8 L_u8SLA 			= Initialized_by_Zero ;

	u8 L_u8AddressLow 	= Initialized_by_Zero ;

	u8 L_u8AddressHigh 	= Initialized_by_Zero ;


	L_u8AddressLow = ( A_u16Address & 0x00ff ) ;

	L_u8AddressHigh = ( (u16) ( A_u16Address & 0x0300 ) ) >> 8 ;

	L_u8SLA = ( EEPROM_ADDRESS ) | ( L_u8AddressHigh ) ;

	MI2C_u8SendStartCondition( ) ;

	MI2C_u8SendSlaveAddressRW( L_u8SLA, MI2C_WRITE ) ;

	MI2C_u8SendByte( L_u8AddressLow ) ;

    MI2C_u8SendByte( A_u8MyByte ) ;

    MI2C_u8SendStopCondition( ) ;

}

/*************************************************************/
/*************************************************************/

u8 HEEPROM_u8ReadByte( u16 A_u16Address )
{

	u8 L_u8YourByte 	= Initialized_by_Zero ;

	u8 L_u8SLA 			= Initialized_by_Zero ;

	u8 L_u8AddressLow 	= Initialized_by_Zero ;

	u8 L_u8AddressHigh 	= Initialized_by_Zero ;


	L_u8AddressLow = ( A_u16Address & 0x00ff ) ;

	L_u8AddressHigh = ( (u16) (A_u16Address & 0x0300) ) >> 8 ;

	L_u8SLA = ( EEPROM_ADDRESS ) | ( L_u8AddressHigh ) ;

	MI2C_u8SendStartCondition( ) ;

	MI2C_u8SendSlaveAddressRW( L_u8SLA, MI2C_WRITE ) ;

	MI2C_u8SendByte( L_u8AddressLow ) ;

	MI2C_u8SendRepeatedStartCondition( ) ;

	MI2C_u8SendSlaveAddressRW( L_u8SLA, MI2C_READ ) ;

	MI2C_u8RecieveByte( &L_u8YourByte, MI2C_NACK ) ;

	MI2C_u8SendStopCondition( ) ;

	return L_u8YourByte ;

}

/*************************************************************/
/*************************************************************/





