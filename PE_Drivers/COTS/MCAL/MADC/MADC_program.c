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



// Global ISR pointer to function.
void ( *MADC_vpPointerToFunction ) (void) = NULL ;



/********************************************************************************************************************/
/*******************************************************************************************************************/

void MADC_vInit( void )
{

	// 1-Vref selection.

	#if ADC_REF_VOLT == AVCC

		CLR_BIT( ADMUX, ADMUX_REFS1 ) ;
		SET_BIT( ADMUX, ADMUX_REFS0 ) ;

	#elif ADC_REF_VOLT == AREF

		CLR_BIT( ADMUX, ADMUX_REFS1 ) ;
		CLR_BIT( ADMUX, ADMUX_REFS0 ) ;

	#elif ADC_REF_VOLT == Internal_Volt

		SET_BIT( ADMUX, ADMUX_REFS1 ) ;
		SET_BIT( ADMUX, ADMUX_REFS0 ) ;

	#else

		#error "Please, select correct refrence voltage"

	#endif


	// 2-Data adjustment direction(Right OR Left).

	#if ADC_Data_Adjustment == RIGHT_Adjust

		CLR_BIT( ADMUX, ADMUX_ADLAR ) ;

	#elif ADC_Data_Adjustment == LEFT_Adjust

		SET_BIT( ADMUX, ADMUX_ADLAR ) ;

	#else

		#error "Please, select correct data adjustment direction(Right OR Left)"

	#endif


	// 3-Select prescaler bits.

	ADCSRA = ( ADCSRA & Prescaler_Bit_Manipulation ) | ( ADC_Prescaler ) ;


	// 4-Enable/Disable auto trigger.

	#if AUTO_TRIGGER == ENABLE

		SET_BIT( ADCSRA , ADCSRA_ADATE ) ;

	#elif AUTO_TRIGGER == DISABLE

		CLR_BIT( ADCSRA , ADCSRA_ADATE ) ;

	#else

		#error "Please, select correct ENABLE/DISABLE auto trigger choice"

	#endif

	// 5-Select auto trigger source.

		SFIOR = ( SFIOR & AutoTrigger_Bit_Manipulation ) | ( TriggerSource_Option << 5 ) ;

	// 6- Enable/Disable Interrupt.

	#if INTERRUPT == ENABLE

		SET_BIT( ADCSRA , ADCSRA_ADIE ) ;

	#elif INTERRUPT == DISABLE

		CLR_BIT( ADCSRA , ADCSRA_ADIE ) ;

	#else

		#error "Please, select correct ENABLE/DISABLE Interrupt choice"

	#endif

	// 7-Enable/Disable ADC peripheral.

	#if ADC_Peripheral == ENABLE

		SET_BIT( ADCSRA , ADCSRA_ADEN ) ;

	#elif ADC_Peripheral == DISABLE

		CLR_BIT( ADCSRA , ADCSRA_ADEN ) ;

	#else

		#error "Please, select correct ENABLE/DISABLE ADC peripheral choice"

	#endif



}



/********************************************************************************************************************/
/*******************************************************************************************************************/

u16 MADC_u16ConvertAnalog_to_Digital ( u8 A_u8ChannelNum )
{

	// 1-Select channel.

	ADMUX = ( ADMUX & ChannelSelectionBits_Manipulation ) | ( A_u8ChannelNum & ChannelNumBits_Manipulation ) ;


	// 2-Start conversion.

	SET_BIT( ADCSRA, ADCSRA_ADSC ) ;


	// 3-Poll on flag.

	while( GET_BIT( ADCSRA, ADCSRA_ADIF ) != Flag_is_Set ) ;


	// 4-Clear flag.

	SET_BIT( ADCSRA, ADCSRA_ADIF ) ;


	// 5-Return ADC data.

	return ADC_Data ;



}


/********************************************************************************************************************/
/*******************************************************************************************************************/

void MADC_vStartConversion ( u8 A_u8ChannelNum )
{


	// 1-Select channel.

	ADMUX = ( ADMUX & ChannelSelectionBits_Manipulation ) | ( A_u8ChannelNum & ChannelNumBits_Manipulation ) ;


	// 2-Start conversion.

	SET_BIT( ADCSRA, ADCSRA_ADSC ) ;


}

/********************************************************************************************************************/
/*******************************************************************************************************************/

u16 MADC_GetADCData( void )
{

	// 5-Return ADC data.

	return ADC_Data ;

}

/********************************************************************************************************************/
/*******************************************************************************************************************/


//pointer to function
void MADC_vSetCallBack( void (*MEXTI_vpPointerTo_ISR_function) (void) )
{

	MADC_vpPointerToFunction = MEXTI_vpPointerTo_ISR_function ;

}


/********************************************************************************************************************/
/*******************************************************************************************************************/

#define Func_to_Ptr_Method 		STOP
#if 	Func_to_Ptr_Method == 	RUN

ADC_ISR
{


	if( MEXTI_vpPointerTo_ADC_function != NULL )
	{

		MADC_vpPointerToFunction( ) ;

	}


	else
	{


	}



}

#endif

/********************************************************************************************************************/
/*******************************************************************************************************************/















