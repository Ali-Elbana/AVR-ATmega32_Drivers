/* FILENAME: MUART_private  
*  Author:  Ali El Bana
*  Version:  V1.0
*  DATE:   Mon 08/01/2022
*/
#ifndef _MUART_private_H
#define _MUART_private_H



#define UDR 	*((volatile u8*)(0x2C))


#define UCSRA  	*((volatile u8*)(0x2B))

#define UCSRA_RXC 	7
#define UCSRA_TXC 	6
#define UCSRA_UDRE 	5
#define UCSRA_FE 	4
#define UCSRA_DOR 	3
#define UCSRA_PE 	2
#define UCSRA_U2X	1
#define UCSRA_MPCM	0


#define UCSRB  	*((volatile u8*)(0x2A))

#define UCSRB_RXCIE 7
#define UCSRB_TXCIE	6
#define UCSRB_UDRIE 5
#define UCSRB_RXEN 	4
#define UCSRB_TXEN 	3
#define UCSRB_UCSZ2 2
#define UCSRB_RXB8 	1
#define UCSRB_TXB8 	0


#define UCSRC  	*((volatile u8*)(0x40))

#define UCSRC_URSEL	7
#define UCSRC_UMSEL 6
#define UCSRC_UPM1 	5
#define UCSRC_UPM0 	4
#define UCSRC_USBS 	3
#define UCSRC_UCSZ1 2
#define UCSRC_UCSZ0 1
#define UCSRC_UCPOL 0


#define UBRRH  	*((volatile u8*)(0x40))

#define UBRRH_URSEL 15


#define UBRRL 	*((volatile u8*)(0x29))




#define Asynchronous_Operation 1
#define Synchronous_Operation  2

#define Parity_Disabled 	1
#define Enabled_EvenParity 	2
#define Enabled_OddParity 	3

#define One_StopBit	 1
#define Two_StopBits 2

#define CharacterSize_5bits 1
#define	CharacterSize_6bits	2
#define CharacterSize_7bits 3
#define CharacterSize_8bits 4
#define CharacterSize_9bits	5

#define RisingTx_FallingRx 	1
#define FallingTx_RisingRx	2

#define ENABLE  1
#define DISABLE 2


#define UART_ISR_Options 3


#define UART_RXC_ISR 	void __vector_13(void) __attribute__((signal));\
						void __vector_13(void)

#define UART_UDRE_ISR 	void __vector_14(void) __attribute__((signal));\
						void __vector_14(void)

#define UART_TXC_ISR 	void __vector_15(void) __attribute__((signal));\
						void __vector_15(void)











#endif //_MUART_private_H
