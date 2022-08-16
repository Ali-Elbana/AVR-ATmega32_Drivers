/* FILENAME: MI2C_interface  
*  Author:  Ali El Bana
*  Version:  V1.0
*  DATE:   Sat 08/06/2022
*/
#ifndef _MI2C_interface_H
#define _MI2C_interface_H


void MI2C_vInit( void ) ;

u8 MI2C_u8SendStartCondition( void ) ;

u8 MI2C_u8SendRepeatedStartCondition( void ) ;

u8 MI2C_u8SendSlaveAddressRW( u8 A_u8Sla, u8 A_u8Rw ) ;

u8 MI2C_u8SendByte( u8 A_u8Byte ) ;

u8 MI2C_u8RecieveByte( u8 *A_Pu8Byte, u8 A_u8Ack ) ;

u8 MI2C_u8SendStopCondition( void ) ;

u8 MI2C_u8GetStatus( void ) ;

void MI2C_vSetBitRate( u32 A_u32MyBitRate ) ;

void MI2C_vSetSLA( u32 A_u32MySLA ) ;



#define MI2C_READ  1
#define MI2C_WRITE 0

#define MI2C_ACK  1
#define MI2C_NACK 0









#endif //_MI2C_interface_H
