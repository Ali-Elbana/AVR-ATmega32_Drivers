/* FILENAME: MUART_interface  
*  Author:  Ali El Bana
*  Version:  V1.0
*  DATE:   Mon 08/01/2022
*/
#ifndef _MUART_interface_H
#define _MUART_interface_H



void MUART_vInit( void ) ;

void UART_vSetBAUDRate( u8 A_u8UBRR_Value ) ;

void MUART_vTransmit( u8 A_u8Data ) ;

u8   MUART_u8Receive( void ) ;

void MUART_vENABLE( void ) ;

void MUART_vDISABLE( void ) ;

s8 	 MUART_s8GetUDR( void ) ;

void MUART_vRecieveString( c8 A_c8YourString[] ) ;

void MUART_vTransmitString( c8 *A_c8MyString ) ;

u8   MUART_u8CompareString( c8 *String1, c8 *String2 ) ;

void MUART_vFlush( void ) ;


/*************************** Interrupt APIs *******************************/

void MUART_vEnableInterrupt( u8 A_u8InterruptID ) ;

void MUART_vDisableInterrupt( u8 A_u8InterruptID ) ;

void MUART_vTransmit_Asynch( c8 A_c8MyString[], void (*A_Fptr)(void) ) ;

void MUART_vRecieve_Asynch ( c8 A_c8YourString[], void (*A_Fptr)(void) ) ;

void MUART_vSetCallBack( u8 A_u8ISR_ID, void (*A_Fptr)(void) ) ;

/*************************************************************************/


#define BaudRate_2400 	207
#define BaudRate_4800 	103
#define BaudRate_9600 	51
#define BaudRate_14k 	34
#define BaudRate_19k 	25
#define BaudRate_28k 	16
#define BaudRate_38k 	12
#define BaudRate_57k 	8
#define BaudRate_76k 	6
#define BaudRate_115k 	3
#define BaudRate_230k 	1
#define BaudRate_250k 	1
#define BaudRate_HalfM 	0


#define UART_ISR_RXC 	0 // USART, Rx Complete.
#define UART_ISR_UDRE 	1 // USART Data Register Empty.
#define UART_ISR_TXC 	2 // USART, Tx Complete.


#define Equal_Strings 		0
#define Not_Equal_Strings 	1


#define RXC_ISR 	1
#define UDRE_ISR	2
#define TXC_ISR		3

#define RXC_INT 	1
#define UDRE_INT	2
#define TXC_INT		3




#endif //_MUART_interface_H
