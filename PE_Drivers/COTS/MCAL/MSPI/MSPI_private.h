/* FILENAME: MSPI_private  
*  Author:  Ali El Bana
*  Version:  V1.0
*  DATE:   Wed 08/03/2022
*/
#ifndef _MSPI_private_H
#define _MSPI_private_H




#define SPCR  *( (volatile u8*) (0x2D) )

#define SPCR_SPIE 		7
#define SPCR_SPE 		6
#define SPCR_DORD 		5
#define SPCR_MSTR 		4
#define SPCR_CPOL 		3
#define SPCR_CPHA 		2
#define SPCR_SPR1 		1
#define SPCR_SPR0 		0


#define SPSR  *( (volatile u8*) (0x2E) )

#define SPSR_SPIF 		7
#define SPSR_WCOL 		6
#define SPSR_SPI2X 		0


#define SPDR  *( (volatile u8*) (0x2F) )



#define ENABLE  1
#define DISABLE 2


#define LSB_Transmitted_First 1
#define MSB_Transmitted_First 2

#define Rising_Leading_Edge  1
#define Falling_Leading_Edge 2

#define Sample_Leading_Edge 1
#define Setup_Leading_Edge  2


#define Fosc_Dividedby_4	1
#define Fosc_Dividedby_16	2
#define Fosc_Dividedby_64	3
#define Fosc_Dividedby_128	4
#define Fosc_Dividedby_2	5
#define Fosc_Dividedby_8	6
#define Fosc_Dividedby_32	7
#define Fosc2_Dividedby_64	8


#define Sample_Rising_Leading  	1
#define Setup_Rising_Leading  	2
#define Sample_Falling_Leading	3
#define Setup_Falling_Leading 	4


#define Master_SPI_Mode 1
#define Slave_SPI_Mode  2


//Serial Transfer Complete
#define ISP_STC_ISR  void __vector_12(void) __attribute__((signal));\
					 void __vector_12(void)













#endif //_MSPI_private_H
