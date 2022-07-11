/* FILENAME: MEXTI_program 
*  Author:  Ali El Bana
*  Version:  V1.0
*  DATE:   Sat 06/04/2022
*/


#include "../../LIB/LSTD_TYPES.h"
#include "../../LIB/LBITMATH.h"

#include "../MDIO/MDIO_inter.h"

#include "MEXTI_interface.h"
#include "MEXTI_private.h"
#include "MEXTI_config.h"





// Global ISR pointer to functions.
void ( *MEXTI_vpPointerTo_INT0_function ) (void) = NULL ;

void ( *MEXTI_vpPointerTo_INT1_function ) (void) = NULL ;

void ( *MEXTI_vpPointerTo_INT2_function ) (void) = NULL ;



/********************************************************************************************************************/
/*******************************************************************************************************************/


void MEXTI_vInit( void )
{

	// Choose to enable INT0.
	#if EXTI_INT0 == Enable

			// Set sense control for INT0.
			#if EXTI_INT0_SENSE_CTRL == EXTI_FallingEdge

				// Falling Edge for INT0.
				SET_BIT( MCUCR, MCUCR_ISC01 ) ;
				CLR_BIT( MCUCR, MCUCR_ISC00 ) ;

			// Rising Edge for INT0.
			#elif EXTI_INT0_SENSE_CTRL == EXTI_RisingEdge

				SET_BIT( MCUCR, MCUCR_ISC01 ) ;
				SET_BIT( MCUCR, MCUCR_ISC00 ) ;

			// On change for INT0.
			#elif EXTI_INT0_SENSE_CTRL == EXTI_OnChange

				CLR_BIT( MCUCR, MCUCR_ISC01 ) ;
				SET_BIT( MCUCR, MCUCR_ISC00 ) ;

			// Low level for INT0.
			#elif EXTI_INT0_SENSE_CTRL == EXTI_LowLevel

				CLR_BIT( MCUCR, MCUCR_ISC01 ) ;
				CLR_BIT( MCUCR, MCUCR_ISC00 ) ;

			#else
s
				#error "Sense Control for INT0 must be Falling edge, Rising edge, On change or Low level.And no one else."

			#endif


		// Enable EXTI_PIE for INT0.
		SET_BIT( GICR, GICR_INT0 ) ;

	#endif


	// Choose to enable INT1.
	#if EXTI_INT1 == Enable

			// Set sense control for INT1.
			#if EXTI_INT1_SENSE_CTRL == EXTI_FallingEdge

				// Falling Edge for INT1.
				SET_BIT( MCUCR, MCUCR_ISC11 ) ;
				CLR_BIT( MCUCR, MCUCR_ISC10 ) ;

			// Rising Edge for INT1.
			#elif EXTI_INT1_SENSE_CTRL == EXTI_RisingEdge

				SET_BIT( MCUCR, MCUCR_ISC11 ) ;
				SET_BIT( MCUCR, MCUCR_ISC10 ) ;

			// On change for INT1.
			#elif EXTI_INT1_SENSE_CTRL == EXTI_OnChange

				CLR_BIT( MCUCR, MCUCR_ISC11 ) ;
				SET_BIT( MCUCR, MCUCR_ISC10 ) ;

			// Low level for INT1.
			#elif EXTI_INT1_SENSE_CTRL == EXTI_LowLevel

				CLR_BIT( MCUCR, MCUCR_ISC11 ) ;
				CLR_BIT( MCUCR, MCUCR_ISC10 ) ;

			#else

				#error "Sense Control for INT1 must be Falling edge, Rising edge, On change or Low level.And no one else."

			#endif


		// Enable EXTI_PIE for INT1.
		SET_BIT( GICR, GICR_INT1 ) ;

	#endif


	// Choose to enable INT2.
	#if EXTI_INT2 == Enable

			// Set sense control for INT2.
			#if EXTI_INT2_SENSE_CTRL == EXTI_FallingEdge

				// Falling Edge for INT2.
				CLR_BIT( MCUCSR, MCUCSR_ISC2 ) ;

			// Rising Edge for INT2.
			#elif EXTI_INT2_SENSE_CTRL == EXTI_RisingEdge

				SET_BIT( MCUCSR, MCUCSR_ISC2 ) ;


			#else

				#error "Sense Control for INT2 must be Falling or Rising edge.And no one else."

			#endif


		// Enable EXTI_PIE for INT2.
		SET_BIT( GICR, GICR_INT2 ) ;

	#endif






}



/********************************************************************************************************************/
/*******************************************************************************************************************/


void MEXTI_vEnableInterrupt( u8 A_u8EXTI_INTx )
{


	switch ( A_u8EXTI_INTx )
	{

		case INT0: SET_BIT( GICR, GICR_INT0 ); break;

		case INT1: SET_BIT( GICR, GICR_INT1 ); break;

		case INT2: SET_BIT( GICR, GICR_INT2 ); break;

		default: break;

	}



}


/********************************************************************************************************************/
/*******************************************************************************************************************/



void MEXTI_vDisableInterrupt( u8 A_u8EXTI_INTx )
{


	switch ( A_u8EXTI_INTx )
	{

		case INT0: CLR_BIT( GICR, GICR_INT0 ); break;

		case INT1: CLR_BIT( GICR, GICR_INT1 ); break;

		case INT2: CLR_BIT( GICR, GICR_INT2 ); break;

		default: break;

	}


}


/********************************************************************************************************************/
/*******************************************************************************************************************/



void MEXTI_vSetSenseControl( u8 A_u8EXTI_INTx, u8 A_u8SenseCtrl )
{


	switch( A_u8EXTI_INTx )
	{


		case INT0 :


			switch( A_u8SenseCtrl )
			{

				case EXTI_FallingEdge	: SET_BIT( MCUCR, MCUCR_ISC01 ) ; CLR_BIT( MCUCR, MCUCR_ISC00 ) ; break;

				case EXTI_RisingEdge	: SET_BIT( MCUCR, MCUCR_ISC01 ) ; SET_BIT( MCUCR, MCUCR_ISC00 ) ; break;

				case EXTI_OnChange		: CLR_BIT( MCUCR, MCUCR_ISC01 ) ; SET_BIT( MCUCR, MCUCR_ISC00 ) ; break;

				case EXTI_LowLevel		: CLR_BIT( MCUCR, MCUCR_ISC01 ) ; CLR_BIT( MCUCR, MCUCR_ISC00 ) ; break;

				default: break;

			}


		break;



		case INT1 :


			switch( A_u8SenseCtrl )
			{

				case EXTI_FallingEdge	: SET_BIT( MCUCR, MCUCR_ISC11 ) ; CLR_BIT( MCUCR, MCUCR_ISC10 ) ; break;

				case EXTI_RisingEdge	: SET_BIT( MCUCR, MCUCR_ISC11 ) ; SET_BIT( MCUCR, MCUCR_ISC10 ) ; break;

				case EXTI_OnChange		: CLR_BIT( MCUCR, MCUCR_ISC11 ) ; SET_BIT( MCUCR, MCUCR_ISC10 ) ; break;

				case EXTI_LowLevel		: CLR_BIT( MCUCR, MCUCR_ISC11 ) ; CLR_BIT( MCUCR, MCUCR_ISC10 ) ; break;

				default: break;

			}


		break;



		case INT2 :


			switch( A_u8SenseCtrl )
			{

				case EXTI_FallingEdge	: CLR_BIT( MCUCSR, MCUCSR_ISC2 ) ; break;

				case EXTI_RisingEdge	: SET_BIT( MCUCSR, MCUCSR_ISC2 ) ; break;

				default: break;

			}


		break;


		default: break;


	}




}



/********************************************************************************************************************/
/*******************************************************************************************************************/


//pointer to function
void MEXTI_vSetCallBack( u8 A_u8EXTI_INTx, void (*MEXTI_vpPointerTo_ISR_function) (void) )
{

	switch( A_u8EXTI_INTx )
	{

		case INT0: MEXTI_vpPointerTo_INT0_function = MEXTI_vpPointerTo_ISR_function ; break;

		case INT1: MEXTI_vpPointerTo_INT1_function = MEXTI_vpPointerTo_ISR_function ; break;

		case INT2: MEXTI_vpPointerTo_INT2_function = MEXTI_vpPointerTo_ISR_function ; break;

		default: break;

	}


}


/********************************************************************************************************************/
/*******************************************************************************************************************/

#define Func_to_Ptr_Method 		STOP

#if 	Func_to_Ptr_Method == 	RUN



//ISR implementation <standard_for_AVR_compiler>
ISR_INT0
{

	if( MEXTI_vpPointerTo_INT0_function != NULL )
	{

		MEXTI_vpPointerTo_INT0_function( ) ;

	}


	else
	{


	}



}



/********************************************************************************************************************/
/*******************************************************************************************************************/


ISR_INT1
{

	if( MEXTI_vpPointerTo_INT1_function != NULL )
	{

		MEXTI_vpPointerTo_INT1_function( ) ;

	}


	else
	{


	}



}


/********************************************************************************************************************/
/*******************************************************************************************************************/

ISR_INT2
{


	if( MEXTI_vpPointerTo_INT2_function != NULL )
	{

		MEXTI_vpPointerTo_INT2_function( ) ;

	}


	else
	{


	}



}


/********************************************************************************************************************/
/*******************************************************************************************************************/





#endif












