/* FILENAME: MADC_program 
*  Author:  Ali El Bana
*  Version:  V1.0
*  DATE:   Sun 07/10/2022
*/


#include "../../LIB/LSTD_TYPES.h"
#include "../../LIB/LBITMATH.h"

#include "../MDIO/MDIO_inter.h"
#include "MADC_interface.h"
#include "MADC_private.h"
#include "MADC_config.h"


/********************************************************************************************************************/
/*******************************************************************************************************************/

void MADC_vInit( void )
{

	// 1-Vref selection.

	CLR_BIT( ADMUX, ADMUX_REFS1 ) ;

	SET_BIT( ADMUX, ADMUX_REFS0 ) ;


	// 2-Data adjustment direction(Right OR Left).

	CLR_BIT( ADMUX, ADMUX_ADLAR ) ;


	// 3-Select prescaler bits.

	ADCSRA = ( ADCSRA & 0xF8 ) | ( ADC_Prescaler ) ;


	// 4-Enable auto trigger.

	CLR_BIT( ADCSRA , ADCSRA_ADATE ) ;

	// 5-Select auto trigger source.


	// 6- Enable/Disable Interrupt.

	CLR_BIT( ADCSRA , ADCSRA_ADEN ) ;


	// 7-Enable ADC peripheral.

	SET_BIT( ADCSRA , ADCSRA_ADEN ) ;


}



/********************************************************************************************************************/
/*******************************************************************************************************************/

u16 MADC_u16ConvertAnalog_to_Digital ( u8 A_u8ChannelNum )
{

	// 1-Select channel.

	ADMUX = ( ADMUX & 0xE0 ) | ( A_u8ChannelNum & 0x1F ) ;


	// 2-Start conversion.

	SET_BIT( ADCSRA, ADCSRA_ADSC ) ;


	// 3-Poll on flag.

	while( GET_BIT( ADCSRA, ADCSRA_ADIF ) != Flag_is_Set ) ;


	// 4-Clear flag.

	SET_BIT( ADCSRA, ADCSRA_ADIF ) ;


	// 5-Return ADC data.

	return ADC ;



}


/********************************************************************************************************************/
/*******************************************************************************************************************/


























