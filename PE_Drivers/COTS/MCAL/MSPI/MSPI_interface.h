/* FILENAME: MSPI_interface  
*  Author:  Ali El Bana
*  Version:  V1.0
*  DATE:   Wed 08/03/2022
*/
#ifndef _MSPI_interface_H
#define _MSPI_interface_H




void MSPI_vInit( void ) ;

u8   MSPI_u8Transecieve( u8 A_u8Data ) ;

void MSPI_vMasterTransmit( u8 A_u8Data ) ;

u8 	 MSPI_u8MasterRecieve( void ) ;

void MSPI_vSlaveTransmit( u8 A_u8Data ) ;

u8 	 MSPI_u8SlaveRecieve( void ) ;

void MSPI_vENABLE( void ) ;

void MSPI_vDISABLE( void ) ;

void MSPI_vSetCallBack( void (*A_Fptr)(void) ) ;




















#endif //_MSPI_interface_H
