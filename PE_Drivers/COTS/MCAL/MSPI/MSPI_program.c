/* FILENAME: MSPI_program 
*  Author:  Ali El Bana
*  Version:  V1.0
*  DATE:   Wed 08/03/2022
*/

#include "../../LIB/LSTD_TYPES.h"
#include "../../LIB/LBITMATH.h"

#include "../MDIO/MDIO_inter.h"

#include "MSPI_interface.h"
#include "MSPI_private.h"
#include "MSPI_config.h"



static void ( *GS_Global_SPI_CallBack )(void) = NULL ;


/*************************************************************/
/*************************************************************/

void MSPI_vInit( void )
{

	// Write your configurable code here.
	u8 L_u8SPCR_Settings = Initialized_by_Zero ;

	// 1-SPI Interrupt Enable/DISABLE.
	#if SPI_Interrupt_Mode == ENABLE

		SET_BIT( L_u8SPCR_Settings, SPCR_SPIE ) ;

	#elif SPI_Interrupt_Mode == DISABLE

		CLR_BIT( L_u8SPCR_Settings, SPCR_SPIE ) ;

	#endif



	// 2-SPI Enable.
	SET_BIT( L_u8SPCR_Settings, SPCR_SPE ) ;



	// 3-Data Order.
	#if  Data_Order_Direction == LSB_Transmitted_First

		SET_BIT( L_u8SPCR_Settings, SPCR_DORD ) ; // When the DORD bit is written to one, the LSB of the data word is transmitted first.

	#elif Data_Order_Direction == MSB_Transmitted_First

		CLR_BIT( L_u8SPCR_Settings, SPCR_DORD ) ; // When the DORD bit is written to zero, the MSB of the data word is transmitted first.

	#endif



	// 4-Master/Slave Select.
	#if 	Master_Slave_Select == Master_SPI_Mode

			MDIO_vSetPinDirection( SPI_PORT, MOSI_PIN, MDIO_OUTPUT ) ; // MOSI OUTPUT.
			MDIO_vSetPinDirection( SPI_PORT, SCK_PIN , MDIO_OUTPUT ) ; // SCK  OUTPUT.
			MDIO_vSetPinDirection( SPI_PORT, SS_PIN  , MDIO_OUTPUT ) ; // SS   OUTPUT.
			MDIO_vSetPinDirection( SPI_PORT, MISO_PIN, MDIO_INPUT  ) ; // MISO INPUT .

			SET_BIT( L_u8SPCR_Settings, SPCR_MSTR ) ;


	#elif 	Master_Slave_Select == Slave_SPI_Mode

			MDIO_vSetPinDirection( SPI_PORT, MOSI_PIN, MDIO_INPUT  ) ; // MOSI INPUT .
			MDIO_vSetPinDirection( SPI_PORT, SCK_PIN , MDIO_INPUT  ) ; // SCK  INPUT .
			MDIO_vSetPinDirection( SPI_PORT, SS_PIN  , MDIO_INPUT  ) ; // SS  INPUT  .
			MDIO_vSetPinDirection( SPI_PORT, MISO_PIN, MDIO_OUTPUT ) ; // MISO OUTPUT.

			CLR_BIT( L_u8SPCR_Settings, SPCR_MSTR ) ;

	#endif



	// 5-Select SPI Mode (CPOL and CPHA Functionality).

	// CPOL = 0, CPHA = 0 -> Sample (Rising) Setup (Falling).
	#if SPI_MODE == Sample_Rising_Leading

		CLR_BIT( L_u8SPCR_Settings, SPCR_CPOL ) ;
		CLR_BIT( L_u8SPCR_Settings, SPCR_CPHA ) ;

	// CPOL = 0, CPHA = 1 -> Setup (Rising) Sample (Falling).
	#elif SPI_MODE == Setup_Rising_Leading

		CLR_BIT( L_u8SPCR_Settings, SPCR_CPOL ) ;
		SET_BIT( L_u8SPCR_Settings, SPCR_CPHA ) ;

	// CPOL = 1, CPHA = 0 -> Sample (Falling) Setup (Rising).
	#elif SPI_MODE == Sample_Falling_Leading

		SET_BIT( L_u8SPCR_Settings, SPCR_CPOL ) ;
		CLR_BIT( L_u8SPCR_Settings, SPCR_CPHA ) ;

	// CPOL = 1, CPHA = 1 -> Setup (Falling) Sample (Rising)
	#elif SPI_MODE == Setup_Falling_Leading

		SET_BIT( L_u8SPCR_Settings, SPCR_CPOL ) ;
		SET_BIT( L_u8SPCR_Settings, SPCR_CPHA ) ;

	#endif



	// 6-SPI Clock Rate.
	#if SPI_CLK_Rate == Fosc_Dividedby_4

		CLR_BIT( SPSR, SPSR_SPI2X ) ;
		CLR_BIT( L_u8SPCR_Settings, SPCR_SPR1  ) ;
		CLR_BIT( L_u8SPCR_Settings, SPCR_SPR0  ) ;

	#elif SPI_CLK_Rate == Fosc_Dividedby_16

		CLR_BIT( SPSR, SPSR_SPI2X ) ;
		CLR_BIT( L_u8SPCR_Settings, SPCR_SPR1  ) ;
		SET_BIT( L_u8SPCR_Settings, SPCR_SPR0  ) ;

	#elif SPI_CLK_Rate == Fosc_Dividedby_64

		CLR_BIT( SPSR, SPSR_SPI2X ) ;
		SET_BIT( L_u8SPCR_Settings, SPCR_SPR1  ) ;
		CLR_BIT( L_u8SPCR_Settings, SPCR_SPR0  ) ;

	#elif SPI_CLK_Rate == Fosc_Dividedby_128

		CLR_BIT( SPSR, SPSR_SPI2X ) ;
		SET_BIT( L_u8SPCR_Settings, SPCR_SPR1  ) ;
		SET_BIT( L_u8SPCR_Settings, SPCR_SPR0  ) ;

	#elif SPI_CLK_Rate == Fosc_Dividedby_2

		SET_BIT( SPSR, SPSR_SPI2X ) ;
		CLR_BIT( L_u8SPCR_Settings, SPCR_SPR1  ) ;
		CLR_BIT( L_u8SPCR_Settings, SPCR_SPR0  ) ;

	#elif SPI_CLK_Rate == Fosc_Dividedby_8

		SET_BIT( SPSR, SPSR_SPI2X ) ;
		CLR_BIT( L_u8SPCR_Settings, SPCR_SPR1  ) ;
		SET_BIT( L_u8SPCR_Settings, SPCR_SPR0  ) ;

	#elif SPI_CLK_Rate == Fosc_Dividedby_32

		SET_BIT( SPSR, SPSR_SPI2X ) ;
		SET_BIT( L_u8SPCR_Settings, SPCR_SPR1  ) ;
		CLR_BIT( L_u8SPCR_Settings, SPCR_SPR0  ) ;

	#elif SPI_CLK_Rate == Fosc2_Dividedby_64

		SET_BIT( SPSR, SPSR_SPI2X ) ;
		SET_BIT( L_u8SPCR_Settings, SPCR_SPR1  ) ;
		SET_BIT( L_u8SPCR_Settings, SPCR_SPR0  ) ;

	#endif



	// 7-Write COLlision Flag.

	// The WCOL bit is set if the SPI Data Register (SPDR) is written during a data transfer.
	#if Write_Collision_Flag == ENABLE

		SET_BIT( SPSR, SPSR_WCOL )	;

	/* The WCOL bit (and the SPIF bit) are cleared by first reading the SPI Status Register
			with WCOL set, and then accessing the SPI Data Register. */
	#elif Write_Collision_Flag == DISABLE

		CLR_BIT( SPSR, SPSR_WCOL )	;

	#endif


	// Assign our settings on the SPCR register.
	SPCR = L_u8SPCR_Settings ;


}

/*************************************************************/
/*************************************************************/

u8 MSPI_u8Transecieve( u8 A_u8Data )
{

	// Start transmission.
	SPDR = A_u8Data ;

	// Wait for transmission complete.
	while( !( SPSR & (1 << SPSR_SPIF) ) ) ;

	// Wait for reception complete.
	while( !( SPSR & (1 << SPSR_SPIF) ) ) ;

	// Return data register.
	return SPDR ;

}

/*************************************************************/
/*************************************************************/

void MSPI_vMasterTransmit( u8 A_u8Data )
{

	// Start transmission.
	SPDR = A_u8Data ;

	// Wait for transmission complete.
	while( !( SPSR & (1 << SPSR_SPIF) ) ) ;

}

/*************************************************************/
/*************************************************************/

u8 MSPI_u8MasterRecieve( void )
{

	// Wait for reception complete.
	while( !( SPSR & (1 << SPSR_SPIF) ) ) ;

	// Return data register.
	return SPDR ;

}

/*************************************************************/
/*************************************************************/

void MSPI_vSlaveTransmit( u8 A_u8Data )
{

	// Start transmission.
	SPDR = A_u8Data ;

	// Wait for transmission complete.
	while( !( SPSR & (1 << SPSR_SPIF) ) ) ;

}

/*************************************************************/
/*************************************************************/

u8 MSPI_u8SlaveRecieve( void )
{

	// Wait for reception complete.
	while( !( SPSR & (1 << SPSR_SPIF) ) ) ;

	// Return data register.
	return SPDR ;

}

/*************************************************************/
/*************************************************************/

void MSPI_vENABLE( void )
{
	SET_BIT( SPCR, SPCR_SPE ) ;
}

/*************************************************************/
/*************************************************************/

void MSPI_vDISABLE( void )
{
	CLR_BIT( SPCR, SPCR_SPE ) ;
}

/*************************************************************/
/*************************************************************/

void MSPI_vSetCallBack( void (*A_Fptr) (void) )
{

	GS_Global_SPI_CallBack = A_Fptr ;

}

/*************************************************************/
/*************************************************************/

ISP_STC_ISR
{

	if( GS_Global_SPI_CallBack != NULL )
	{

		GS_Global_SPI_CallBack ( ) ;

	}

}

/*************************************************************/
/*************************************************************/


































