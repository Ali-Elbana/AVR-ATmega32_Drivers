/* FILENAME: HEEPROM_interface  
*  Author:  Ali El Bana
*  Version:  V1.0
*  DATE:   Mon 08/15/2022
*/
#ifndef _HEEPROM_interface_H
#define _HEEPROM_interface_H


void HEEPROM_vWriteByte( u8 A_u8MyByte, u16 A_u16Address ) ;

u8 HEEPROM_u8ReadByte( u16 A_u16Address ) ;


#define EEPROM_ADDRESS 0x50



#endif //_HEEPROM_interface_H
