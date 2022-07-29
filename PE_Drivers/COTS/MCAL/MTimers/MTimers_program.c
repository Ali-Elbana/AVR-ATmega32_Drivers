/* FILENAME: MTimers_program 
*  Author:  Ali El Bana
*  Version:  V1.0
*  DATE:   Fri 07/22/2022
*/

#include "../../LIB/LSTD_TYPES.h"
#include "../../LIB/LBITMATH.h"

#include "MTimer0_config.h"
#include "MTimer1_config.h"
#include "MTimer2_config.h"
#include "MTimers_interface.h"
#include "MTimers_private.h"


// Global ISR pointer to function.
static void ( *GS_TIMER0_vpPtrToFunction[TIMER0_ISR_Options] ) (void) = { NULL, NULL } ;

static void ( *GS_TIMER1_vpPtrToFunction[TIMER1_ISR_Options] ) (void) = { NULL, NULL, NULL, NULL } ;

static void ( *GS_TIMER2_vpPtrToFunction[TIMER2_ISR_Options] ) (void) = { NULL, NULL } ;

u32 G_u32IntervalCounts = Initialized_by_Zero ;


/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/


void MTIMER0_vInit( void )
{


	// To compatible Force Output Compare
	CLR_BIT( TCCR0, TCCR0_FOC0 ) ;


	#if TIMER0_WAVEFORM_GENERATION_MODE == TIMER0_NORMAL_MODE

		CLR_BIT( TCCR0, TCCR0_WGM00 ) ;
		CLR_BIT( TCCR0, TCCR0_WGM01 ) ;

		/***************************************************************/

	#elif TIMER0_WAVEFORM_GENERATION_MODE == TIMER0_PWM_PhaseCorrect

		SET_BIT( TCCR0, TCCR0_WGM00 ) ;
		CLR_BIT( TCCR0, TCCR0_WGM01 ) ;

		/***************************************************************/

	#elif TIMER0_WAVEFORM_GENERATION_MODE == TIMER0_CTC

		CLR_BIT( TCCR0, TCCR0_WGM00 ) ;
		SET_BIT( TCCR0, TCCR0_WGM01 ) ;

		/***************************************************************/

	#elif TIMER0_WAVEFORM_GENERATION_MODE == TIMER0_FastPWM

		SET_BIT( TCCR0, TCCR0_WGM00 ) ;
		SET_BIT( TCCR0, TCCR0_WGM01 ) ;

	#endif // End the options of TIMER0 modes

	/************************************************************************************************/

		// Clock Select Bit Description == No Clock Source(TIMER0 Stopped)
		CLR_BIT( TCCR0, TCCR0_CS00 ) ;
		CLR_BIT( TCCR0, TCCR0_CS01 ) ;
		CLR_BIT( TCCR0, TCCR0_CS02 ) ;

	/***********************************************************************************************/

		// Compare Output Modes:

	#if TIMER0_COMP_MODE == TIMER0_COMP_NonPWM

		// Normal port operation, OC0 disconnected.
		#if TIMER0_COMP_NonPWM_MODE == TIMER0_NORMAL_MODE

				CLR_BIT( TCCR0, TCCR0_COM00 ) ;
				CLR_BIT( TCCR0, TCCR0_COM01 ) ;

			/***************************************************************/

		// Toggle OC0 on compare match.
		#elif TIMER0_COMP_NonPWM_MODE == TIMER0_ToggleOnCOMP

				SET_BIT( TCCR0, TCCR0_COM00 ) ;
				CLR_BIT( TCCR0, TCCR0_COM01 ) ;

			/***************************************************************/

		// Clear OC0 on compare match.
		#elif TIMER0_COMP_NonPWM_MODE == TIMER0_ClearOnCOMP

				CLR_BIT( TCCR0, TCCR0_COM00 ) ;
				SET_BIT( TCCR0, TCCR0_COM01 ) ;

			/***************************************************************/

		// Set OC0 on compare match.
		#elif TIMER0_COMP_NonPWM_MODE == TIMER0_SetOnCOMP

				SET_BIT( TCCR0, TCCR0_COM00 ) ;
				SET_BIT( TCCR0, TCCR0_COM01 ) ;

			/***************************************************************/

		#endif //end of Compare Output Mode, non-PWM options.

		/***********************************************************************************************/

	#elif TIMER0_COMP_MODE == TIMER0_COMP_FastPWM

		// Normal port operation, OC0 disconnected.
		#if TIMER0_COMP_FastPWM_MODE == TIMER0_NORMAL_MODE

				CLR_BIT( TCCR0, TCCR0_COM00 ) ;
				CLR_BIT( TCCR0, TCCR0_COM01 ) ;

			/***************************************************************/

		// Clear OC0 on compare match, set OC0 at TOP.
		#elif TIMER0_COMP_FastPWM_MODE == TIMER0_ClearOnCOMP

				CLR_BIT( TCCR0, TCCR0_COM00 ) ;
				SET_BIT( TCCR0, TCCR0_COM01 ) ;

			/***************************************************************/

		// Set OC0 on compare match, clear OC0 at TOP.
		#elif TIMER0_COMP_FastPWM_MODE == TIMER0_SetOnCOMP

				SET_BIT( TCCR0, TCCR0_COM00 ) ;
				SET_BIT( TCCR0, TCCR0_COM01 ) ;

			/***************************************************************/

		#endif //end of Compare Output Mode, non-PWM options.

		/***********************************************************************************************/


	#elif TIMER0_COMP_MODE == TIMER0_COMP_PhaseCorrectPWM

		// Normal port operation, OC0 disconnected.
		#if TIMER0_COMP_PhaseCorrectPWM_MODE == TIMER0_NORMAL_MODE

				CLR_BIT( TCCR0, TCCR0_COM00 ) ;
				CLR_BIT( TCCR0, TCCR0_COM01 ) ;

			/***************************************************************/

		// Clear OC0 on compare match when up-counting. Set OC0 on compare match when down counting.
		#elif TIMER0_COMP_PhaseCorrectPWM_MODE == TIMER0_ClearOnCOMP

				CLR_BIT( TCCR0, TCCR0_COM00 ) ;
				SET_BIT( TCCR0, TCCR0_COM01 ) ;

			/***************************************************************/

		// Set OC0 on compare match when up-counting. Clear OC0 on compare match when down counting.
		#elif TIMER0_COMP_PhaseCorrectPWM_MODE == TIMER0_SetOnCOMP

				SET_BIT( TCCR0, TCCR0_COM00 ) ;
				SET_BIT( TCCR0, TCCR0_COM01 ) ;

			/***************************************************************/

		#endif //end of Compare Output Mode, non-PWM options.

		/***********************************************************************************************/


	#endif //end of Compare Output Mode options.


}


/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/

void MTIMER1_vInit( void )
{


	// To compatible Force Output Compare
	CLR_BIT( TCCR1A, TCCR1A_FOC1A ) ;
	CLR_BIT( TCCR1A, TCCR1A_FOC1B ) ;


	#if TIMER1_COMP_MODE == TIMER1_COMP_NonPWM

		// Normal port operation, OC1A/OC1B disconnected.
		#if TIMER1_COMP_NonPWM_MODE == TIMER1_NORMAL_MODE

				CLR_BIT( TCCR1A, TCCR1A_COM1A1 ) ;
				CLR_BIT( TCCR1A, TCCR1A_COM1A0 ) ;
				CLR_BIT( TCCR1A, TCCR1A_COM1B1 ) ;
				CLR_BIT( TCCR1A, TCCR1A_COM1B0 ) ;

			/***************************************************************/

		// Toggle OC1A/OC1B on compare match.
		#elif TIMER1_COMP_NonPWM_MODE == TIMER1_ToggleOnCOMP

				CLR_BIT( TCCR1A, TCCR1A_COM1A1 ) ;
				SET_BIT( TCCR1A, TCCR1A_COM1A0 ) ;
				CLR_BIT( TCCR1A, TCCR1A_COM1B1 ) ;
				SET_BIT( TCCR1A, TCCR1A_COM1B0 ) ;

			/***************************************************************/

		// Clear OC1A/OC1B on compare match (Set output to low level).
		#elif TIMER1_COMP_NonPWM_MODE == TIMER1_ClearOnCOMP

				SET_BIT( TCCR1A, TCCR1A_COM1A1 ) ;
				CLR_BIT( TCCR1A, TCCR1A_COM1A0 ) ;
				SET_BIT( TCCR1A, TCCR1A_COM1B1 ) ;
				CLR_BIT( TCCR1A, TCCR1A_COM1B0 ) ;

			/***************************************************************/

		//Set OC1A/OC1B on compare match (Set output to high level).
		#elif TIMER1_COMP_NonPWM_MODE == TIMER1_SetOnCOMP

				SET_BIT( TCCR1A, TCCR1A_COM1A1 ) ;
				SET_BIT( TCCR1A, TCCR1A_COM1A0 ) ;
				SET_BIT( TCCR1A, TCCR1A_COM1B1 ) ;
				SET_BIT( TCCR1A, TCCR1A_COM1B0 ) ;

			/***************************************************************/

		#endif //end of Compare Output Mode, non-PWM options.

	/**************************************************************************************/

	#elif TIMER1_COMP_MODE == TIMER1_COMP_FastPWM

		// Normal port operation, OC1A/OC1B disconnected.
		#if TIMER1_COMP_FastPWM_MODE == TIMER1_NORMAL_MODE

				CLR_BIT( TCCR1A, TCCR1A_COM1A1 ) ;
				CLR_BIT( TCCR1A, TCCR1A_COM1A0 ) ;
				CLR_BIT( TCCR1A, TCCR1A_COM1B1 ) ;
				CLR_BIT( TCCR1A, TCCR1A_COM1B0 ) ;

			/***************************************************************/

		// WGM13:0 = 15: Toggle OC1A on Compare Match, OC1B disconnected (normal port operation).
		#elif TIMER1_COMP_FastPWM_MODE == TIMER1_ToggleOnCOMP

				CLR_BIT( TCCR1A, TCCR1A_COM1A1 ) ;
				SET_BIT( TCCR1A, TCCR1A_COM1A0 ) ;
				CLR_BIT( TCCR1A, TCCR1A_COM1B1 ) ;
				SET_BIT( TCCR1A, TCCR1A_COM1B0 ) ;

			/***************************************************************/

		// Clear OC1A/OC1B on compare match, set OC1A/OC1B at TOP.
		#elif TIMER1_COMP_FastPWM_MODE == TIMER1_ClearOnCOMP

				SET_BIT( TCCR1A, TCCR1A_COM1A1 ) ;
				CLR_BIT( TCCR1A, TCCR1A_COM1A0 ) ;
				SET_BIT( TCCR1A, TCCR1A_COM1B1 ) ;
				CLR_BIT( TCCR1A, TCCR1A_COM1B0 ) ;

			/***************************************************************/

		//Set OC1A/OC1B on compare match (Set output to high level).
		#elif TIMER1_COMP_FastPWM_MODE == TIMER1_SetOnCOMP

				SET_BIT( TCCR1A, TCCR1A_COM1A1 ) ;
				SET_BIT( TCCR1A, TCCR1A_COM1A0 ) ;
				SET_BIT( TCCR1A, TCCR1A_COM1B1 ) ;
				SET_BIT( TCCR1A, TCCR1A_COM1B0 ) ;

			/***************************************************************/

		#endif //end of Compare Output Mode, FAST PWM options.

	/**************************************************************************************/

	#elif TIMER1_COMP_MODE == TIMER1_COMP_PhaseCorrectPWM

		// Normal port operation, OC1A/OC1B disconnected.
		#if TIMER1_COMP_PhaseCorrectPWM_MODE == TIMER1_NORMAL_MODE

				CLR_BIT( TCCR1A, TCCR1A_COM1A1 ) ;
				CLR_BIT( TCCR1A, TCCR1A_COM1A0 ) ;
				CLR_BIT( TCCR1A, TCCR1A_COM1B1 ) ;
				CLR_BIT( TCCR1A, TCCR1A_COM1B0 ) ;

			/***************************************************************/

		// WGM13:0 = 15: Toggle OC1A on Compare Match, OC1B disconnected (normal port operation).
		#elif TIMER1_COMP_PhaseCorrectPWM_MODE == TIMER1_ToggleOnCOMP

				CLR_BIT( TCCR1A, TCCR1A_COM1A1 ) ;
				SET_BIT( TCCR1A, TCCR1A_COM1A0 ) ;
				CLR_BIT( TCCR1A, TCCR1A_COM1B1 ) ;
				SET_BIT( TCCR1A, TCCR1A_COM1B0 ) ;

			/***************************************************************/

		// Clear OC1A/OC1B on compare match, set OC1A/OC1B at TOP.
		#elif TIMER1_COMP_PhaseCorrectPWM_MODE == TIMER1_ClearOnCOMP

				SET_BIT( TCCR1A, TCCR1A_COM1A1 ) ;
				CLR_BIT( TCCR1A, TCCR1A_COM1A0 ) ;
				SET_BIT( TCCR1A, TCCR1A_COM1B1 ) ;
				CLR_BIT( TCCR1A, TCCR1A_COM1B0 ) ;

			/***************************************************************/

		//Set OC1A/OC1B on compare match (Set output to high level).
		#elif TIMER1_COMP_PhaseCorrectPWM_MODE == TIMER1_SetOnCOMP

				SET_BIT( TCCR1A, TCCR1A_COM1A1 ) ;
				SET_BIT( TCCR1A, TCCR1A_COM1A0 ) ;
				SET_BIT( TCCR1A, TCCR1A_COM1B1 ) ;
				SET_BIT( TCCR1A, TCCR1A_COM1B0 ) ;

			/***************************************************************/

		#endif //end of Compare Output Mode, Phase Correct PWM options.


	#endif //end of TIMER1 MODE options.



	// WAVE GENERATION MODE
	#if TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_Normal

					CLR_BIT(TCCR1A, TCCR1A_WGM10) ;
					CLR_BIT(TCCR1A, TCCR1A_WGM11) ;
					CLR_BIT(TCCR1B, TCCR1B_WGM12) ;
					CLR_BIT(TCCR1B, TCCR1B_WGM13) ;

		/**************************************************************************************************/

	#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_CORRECT_8_bit

					SET_BIT(TCCR1A, TCCR1A_WGM10) ;
					CLR_BIT(TCCR1A, TCCR1A_WGM11) ;
					CLR_BIT(TCCR1B, TCCR1B_WGM12) ;
					CLR_BIT(TCCR1B, TCCR1B_WGM13) ;

		/**************************************************************************************************/

	#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_CORRECT_9_bit

					CLR_BIT(TCCR1A, TCCR1A_WGM10) ;
					SET_BIT(TCCR1A, TCCR1A_WGM11) ;
					CLR_BIT(TCCR1B, TCCR1B_WGM12) ;
					CLR_BIT(TCCR1B, TCCR1B_WGM13) ;

		/**************************************************************************************************/

	#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_CORRECT_10_bit

					SET_BIT(TCCR1A, TCCR1A_WGM10) ;
					SET_BIT(TCCR1A, TCCR1A_WGM11) ;
					CLR_BIT(TCCR1B, TCCR1B_WGM12) ;
					CLR_BIT(TCCR1B, TCCR1B_WGM13) ;

		/**************************************************************************************************/

	#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_CTC_OCR1A

					CLR_BIT(TCCR1A, TCCR1A_WGM10) ;
					CLR_BIT(TCCR1A, TCCR1A_WGM11) ;
					SET_BIT(TCCR1B, TCCR1B_WGM12) ;
					CLR_BIT(TCCR1B, TCCR1B_WGM13) ;

		/**************************************************************************************************/

	#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_Fast_PWM_8_bit

					SET_BIT(TCCR1A, TCCR1A_WGM10) ;
					CLR_BIT(TCCR1A, TCCR1A_WGM11) ;
					SET_BIT(TCCR1B, TCCR1B_WGM12) ;
					CLR_BIT(TCCR1B, TCCR1B_WGM13) ;

		/**************************************************************************************************/

	#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_Fast_PWM_9_bit

					CLR_BIT(TCCR1A, TCCR1A_WGM10) ;
					SET_BIT(TCCR1A, TCCR1A_WGM11) ;
					SET_BIT(TCCR1B, TCCR1B_WGM12) ;
					CLR_BIT(TCCR1B, TCCR1B_WGM13) ;

		/**************************************************************************************************/

	#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_Fast_PWM_10_bit

					SET_BIT(TCCR1A, TCCR1A_WGM10) ;
					SET_BIT(TCCR1A, TCCR1A_WGM11) ;
					SET_BIT(TCCR1B, TCCR1B_WGM12) ;
					CLR_BIT(TCCR1B, TCCR1B_WGM13) ;

		/**************************************************************************************************/

	#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_Phase_and_Frequency_Correct_ICR1

					CLR_BIT(TCCR1A, TCCR1A_WGM10) ;
					CLR_BIT(TCCR1A, TCCR1A_WGM11) ;
					CLR_BIT(TCCR1B, TCCR1B_WGM12) ;
					SET_BIT(TCCR1B, TCCR1B_WGM13) ;

		/**************************************************************************************************/

	#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_Phase_and_Frequency_Correct_OCR1A

					SET_BIT(TCCR1A, TCCR1A_WGM10) ;
					CLR_BIT(TCCR1A, TCCR1A_WGM11) ;
					CLR_BIT(TCCR1B, TCCR1B_WGM12) ;
					SET_BIT(TCCR1B, TCCR1B_WGM13) ;

		/**************************************************************************************************/

	#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_Phase_Correct_ICR1

					CLR_BIT(TCCR1A, TCCR1A_WGM10) ;
					SET_BIT(TCCR1A, TCCR1A_WGM11) ;
					CLR_BIT(TCCR1B, TCCR1B_WGM12) ;
					SET_BIT(TCCR1B, TCCR1B_WGM13) ;

		/**************************************************************************************************/

	#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_Phase_Correct_OCR1A

					SET_BIT(TCCR1A, TCCR1A_WGM10) ;
					SET_BIT(TCCR1A, TCCR1A_WGM11) ;
					CLR_BIT(TCCR1B, TCCR1B_WGM12) ;
					SET_BIT(TCCR1B, TCCR1B_WGM13) ;

		/**************************************************************************************************/

	#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_CTC_ICR1

					CLR_BIT(TCCR1A, TCCR1A_WGM10) ;
					CLR_BIT(TCCR1A, TCCR1A_WGM11) ;
					SET_BIT(TCCR1B, TCCR1B_WGM12) ;
					SET_BIT(TCCR1B, TCCR1B_WGM13) ;

		/**************************************************************************************************/

	#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_Fast_PWM_ICR1

					CLR_BIT(TCCR1A, TCCR1A_WGM10) ;
					SET_BIT(TCCR1A, TCCR1A_WGM11) ;
					SET_BIT(TCCR1B, TCCR1B_WGM12) ;
					SET_BIT(TCCR1B, TCCR1B_WGM13) ;

		/**************************************************************************************************/

	#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_Fast_PWM_OCR1A

					SET_BIT(TCCR1A, TCCR1A_WGM10) ;
					SET_BIT(TCCR1A, TCCR1A_WGM11) ;
					SET_BIT(TCCR1B, TCCR1B_WGM12) ;
					SET_BIT(TCCR1B, TCCR1B_WGM13) ;

	#endif

	/**************************************************************************************************/

	// Clock Select Bit Description == No Clock Source(TIMER1 Stopped)
	CLR_BIT( TCCR1B, TCCR1B_CS10 ) ;
	CLR_BIT( TCCR1B, TCCR1B_CS11 ) ;
	CLR_BIT( TCCR1B, TCCR1B_CS12 ) ;

	/**************************************************************************************************/

	#if TIMER1_ICU == ENABLE


		#if ICU_NoiseCanceler == ENABLE

			SET_BIT( TCCR1B, TCCR1B_ICNC1 ) ;

			/***************************************************************/

		#elif ICU_NoiseCanceler == DISABLE

			CLR_BIT( TCCR1B, TCCR1B_ICNC1 ) ;

		#endif

	/**************************************************************************************************/

		// Select the beginning of the ICU edge.
		#if ICU_Edge_Select == ICU_Rising_Edge

			SET_BIT( TCCR1B, TCCR1B_ICES1 );

			/***************************************************************/

		#elif ICU_Edge_Select == ICU_Falling_Edge

			CLR_BIT( TCCR1B, TCCR1B_ICES1 );

	#endif

	/**************************************************************************************************/


#endif



}

/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/

void MTIMER2_vInit( void )
{

	// To compatible Force Output Compare
	CLR_BIT( TCCR2, TCCR2_FOC2 ) ;


	#if TIMER2_WAVEFORM_GENERATION_MODE == TIMER2_NORMAL_MODE

		CLR_BIT( TCCR2, TCCR2_WGM20 ) ;
		CLR_BIT( TCCR2, TCCR2_WGM21 ) ;

		/***************************************************************/

	#elif TIMER2_WAVEFORM_GENERATION_MODE == TIMER2_PWM_PhaseCorrect

		SET_BIT( TCCR2, TCCR2_WGM20 ) ;
		CLR_BIT( TCCR2, TCCR2_WGM21 ) ;

		/***************************************************************/

	#elif TIMER2_WAVEFORM_GENERATION_MODE == TIMER2_CTC

		CLR_BIT( TCCR2, TCCR2_WGM20 ) ;
		SET_BIT( TCCR2, TCCR2_WGM21 ) ;

		/***************************************************************/

	#elif TIMER2_WAVEFORM_GENERATION_MODE == TIMER2_FastPWM

		SET_BIT( TCCR2, TCCR2_WGM20 ) ;
		SET_BIT( TCCR2, TCCR2_WGM21 ) ;

	#endif // End the options of TIMER2 modes

	/**************************************************************************************************/

		// Compare Output Modes:
	#if TIMER2_COMP_MODE == TIMER2_COMP_NonPWM

		// Normal port operation, OC2 disconnected.
		#if TIMER2_COMP_NonPWM_MODE == TIMER2_NORMAL_MODE

				CLR_BIT( TCCR2, TCCR2_COM20 ) ;
				CLR_BIT( TCCR2, TCCR2_COM21 ) ;

			/***************************************************************/

		// Toggle OC2 on compare match.
		#elif TIMER2_COMP_NonPWM_MODE == TIMER2_ToggleOnCOMP

				SET_BIT( TCCR2, TCCR2_COM20 ) ;
				CLR_BIT( TCCR2, TCCR2_COM21 ) ;

			/***************************************************************/

		// Clear OC2 on compare match.
		#elif TIMER2_COMP_NonPWM_MODE == TIMER2_ClearOnCOMP

				CLR_BIT( TCCR2, TCCR2_COM20 ) ;
				SET_BIT( TCCR2, TCCR2_COM21 ) ;

			/***************************************************************/

		// Set OC2 on compare match.
		#elif TIMER2_COMP_NonPWM_MODE == TIMER2_SetOnCOMP

				SET_BIT( TCCR2, TCCR2_COM20 ) ;
				SET_BIT( TCCR2, TCCR2_COM21 ) ;

			/***************************************************************/

		#endif //end of Compare Output Mode, non-PWM options.

		/***********************************************************************************************/

	#elif TIMER2_COMP_MODE == TIMER2_COMP_FastPWM

		// Normal port operation, OC2 disconnected.
		#if TIMER2_COMP_FastPWM_MODE == TIMER2_NORMAL_MODE

				CLR_BIT( TCCR2, TCCR2_COM20 ) ;
				CLR_BIT( TCCR2, TCCR2_COM21 ) ;

			/***************************************************************/

		// Clear OC2 on compare match, set OC2 at TOP.
		#elif TIMER2_COMP_FastPWM_MODE == TIMER2_ClearOnCOMP

				CLR_BIT( TCCR2, TCCR2_COM20 ) ;
				SET_BIT( TCCR2, TCCR2_COM21 ) ;

			/***************************************************************/

		// Set OC2 on compare match, clear OC2 at TOP.
		#elif TIMER2_COMP_FastPWM_MODE == TIMER2_SetOnCOMP

				SET_BIT( TCCR2, TCCR2_COM20 ) ;
				SET_BIT( TCCR2, TCCR2_COM21 ) ;

			/***************************************************************/

		#endif //end of Compare Output Mode, non-PWM options.

		/***********************************************************************************************/


	#elif TIMER2_COMP_MODE == TIMER2_COMP_PhaseCorrectPWM

		// Normal port operation, OC2 disconnected.
		#if TIMER2_COMP_PhaseCorrectPWM_MODE == TIMER2_NORMAL_MODE

				CLR_BIT( TCCR2, TCCR2_COM20 ) ;
				CLR_BIT( TCCR2, TCCR2_COM21 ) ;

			/***************************************************************/

		// Clear OC2 on compare match when up-counting. Set OC2 on compare match when down counting.
		#elif TIMER2_COMP_PhaseCorrectPWM_MODE == TIMER2_ClearOnCOMP

				CLR_BIT( TCCR2, TCCR2_COM20 ) ;
				SET_BIT( TCCR2, TCCR2_COM21 ) ;

			/***************************************************************/

		// Set OC2 on compare match when up-counting. Clear OC2 on compare match when down counting.
		#elif TIMER2_COMP_PhaseCorrectPWM_MODE == TIMER2_SetOnCOMP

				SET_BIT( TCCR2, TCCR2_COM20 ) ;
				SET_BIT( TCCR2, TCCR2_COM21 ) ;

			/***************************************************************/

		#endif //end of Compare Output Mode, non-PWM options.

		/***********************************************************************************************/


	#endif //end of Compare Output Mode options.

	/***********************************************************************************************/

	// Asynchronous Timer/Counter2
	#if TIMER2_ToBe_Asynch == ENABLE

			SET_BIT( ASSR, ASSR_AS2 ) ; // Timer/Counter2 is clocked from a Crystal Oscillator connected to the Timer Oscillator1 (TOSC1) pin.

		/***************************************************************/

	#elif TIMER2_ToBe_Asynch == DISABLE

			CLR_BIT( ASSR, ASSR_AS2 ) ; // Timer/Counter2 is clocked from the I/O clock, clkI/O.

	#endif // end of Asynchronous Timer/Counter2 enable/disable.

	/***********************************************************************************************/


}


/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/

void MTIMERS_vSetPreloadValue( u8 A_u8TimerID, u16 A_u16PreloadValue )
{

	switch( A_u8TimerID )
	{

		case TIMER0 :

			// Set preload value
			TCNT0 = A_u16PreloadValue ;

		break;

		/**********************************************************************************/

		case TIMER1 :

			// Set preload value
			TCNT1 = A_u16PreloadValue ;

		break;

		/**********************************************************************************/

		case TIMER2 :

			// Set preload value
			TCNT2 = A_u16PreloadValue ;

		break;

	}


}

/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/

void MTIMERS_vSetCompareValue( u8 A_u8TimerID, u16 A_u16CompareValue )
{

	switch( A_u8TimerID )
	{

		case TIMER0 :

			OCR0 = A_u16CompareValue ;

		break;

		/**********************************************************************************/

		case TIMER1 :


			#if  Compare_Register == Register_1A

				OCR1A = A_u16CompareValue ;

			#elif Compare_Register == Register_1B


				OCR1B = A_u16CompareValue ;

			#endif



		break;

		/**********************************************************************************/

		case TIMER2 :

			OCR2 = A_u16CompareValue ;

		break;



	}


}

/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/

void MTIMER1_vSetTopValue( u16 A_u16TopValue )
{

	#if  Set_TOP_Value == SET_ON_ICR1

		ICR1 = A_u16TopValue ;

	#elif Set_TOP_Value == SET_ON_OCR1A


		OCR1A = A_u16TopValue ;

	#endif


}



/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/

void MTIMERS_vSetInterval_OVF_Asynch( u8 A_u8TimerID, u16 A_u16IntervalCounts,
										void(* A_Fptr_MTIMERS )(void) )
{


	switch( A_u8TimerID )
	{

		case TIMER0 :

			G_u32IntervalCounts = A_u16IntervalCounts ;

			GS_TIMER0_vpPtrToFunction[TIMER0_ISR_OVF] = A_Fptr_MTIMERS ;

			// Start timer
			MTIMERS_vStartTimer( TIMER0 ) ;

		break;

		/**********************************************************************************/

		case TIMER1 :

			G_u32IntervalCounts = A_u16IntervalCounts ;

			GS_TIMER1_vpPtrToFunction[TIMER1_ISR_OVF] = A_Fptr_MTIMERS ;

			// Start timer
			MTIMERS_vStartTimer( TIMER1 ) ;


		break;

		/**********************************************************************************/

		case TIMER2 :

			G_u32IntervalCounts = A_u16IntervalCounts ;

			GS_TIMER2_vpPtrToFunction[TIMER2_ISR_OVF] = A_Fptr_MTIMERS ;

			// Start timer
			MTIMERS_vStartTimer( TIMER2 ) ;


		break;



	}



}


/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/

void MTIMERS_vSetInterval_CTC_Asynch( u8 A_u8TimerID, u16 A_u16CompareValue,
								u16 A_u16IntervalCounts, void(* A_Fptr_MTIMERS )(void) )
{


	switch( A_u8TimerID )
	{

		case TIMER0 :

			G_u32IntervalCounts = A_u16IntervalCounts ;

			GS_TIMER0_vpPtrToFunction[TIMER0_ISR_CTC] = A_Fptr_MTIMERS ;

			MTIMERS_vSetCompareValue( TIMER0, A_u16CompareValue ) ;

			// Start timer
			MTIMERS_vStartTimer( TIMER0 ) ;

		break;

		/**********************************************************************************/

		case TIMER1 :

			G_u32IntervalCounts = A_u16IntervalCounts ;

			GS_TIMER1_vpPtrToFunction[TIMER1_ISR_CTC1A] = A_Fptr_MTIMERS ;

			MTIMERS_vSetCompareValue( TIMER1, A_u16CompareValue ) ;

			// Start timer
			MTIMERS_vStartTimer( TIMER1 ) ;


		break;

		/**********************************************************************************/

		case TIMER2 :

			G_u32IntervalCounts = A_u16IntervalCounts ;

			GS_TIMER2_vpPtrToFunction[TIMER2_ISR_CTC] = A_Fptr_MTIMERS ;

			MTIMERS_vSetCompareValue( TIMER2, A_u16CompareValue ) ;

			// Start timer
			MTIMERS_vStartTimer( TIMER2 ) ;


		break;



	}



}



/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/

void MTIMERS_vStartTimer( u8 A_u8TimerID )
{

	switch( A_u8TimerID )
	{

	  case TIMER0 :

			// Clock Select Bit Description
			#if   TIMER0_ClockSelectBit == TIMER0_NoClockSource

				CLR_BIT( TCCR0, TCCR0_CS00 ) ;
				CLR_BIT( TCCR0, TCCR0_CS01 ) ;
				CLR_BIT( TCCR0, TCCR0_CS02 ) ;

			#elif TIMER0_ClockSelectBit == TIMER0_NoPrescaling

				SET_BIT( TCCR0, TCCR0_CS00 ) ;
				CLR_BIT( TCCR0, TCCR0_CS01 ) ;
				CLR_BIT( TCCR0, TCCR0_CS02 ) ;

			#elif TIMER0_ClockSelectBit == TIMER0_DivisionBy_8prescaler

				CLR_BIT( TCCR0, TCCR0_CS00 ) ;
				SET_BIT( TCCR0, TCCR0_CS01 ) ;
				CLR_BIT( TCCR0, TCCR0_CS02 ) ;

			#elif TIMER0_ClockSelectBit == TIMER0_DivisionBy_64prescaler

				SET_BIT( TCCR0, TCCR0_CS00 ) ;
				SET_BIT( TCCR0, TCCR0_CS01 ) ;
				CLR_BIT( TCCR0, TCCR0_CS02 ) ;

			#elif TIMER0_ClockSelectBit == TIMER0_DivisionBy_256prescaler

				CLR_BIT( TCCR0, TCCR0_CS00 ) ;
				CLR_BIT( TCCR0, TCCR0_CS01 ) ;
				SET_BIT( TCCR0, TCCR0_CS02 ) ;

			#elif TIMER0_ClockSelectBit == TIMER0_DivisionBy_1024prescaler

				SET_BIT( TCCR0, TCCR0_CS00 ) ;
				CLR_BIT( TCCR0, TCCR0_CS01 ) ;
				SET_BIT( TCCR0, TCCR0_CS02 ) ;

			#elif TIMER0_ClockSelectBit == TIMER0_ExtClk_FallingEdge.

				CLR_BIT( TCCR0, TCCR0_CS00 ) ;
				SET_BIT( TCCR0, TCCR0_CS01 ) ;
				SET_BIT( TCCR0, TCCR0_CS02 ) ;

			#elif TIMER0_ClockSelectBit == TIMER0_ExtClk_RisingEdge.

				SET_BIT( TCCR0, TCCR0_CS00 ) ;
				SET_BIT( TCCR0, TCCR0_CS01 ) ;
				SET_BIT( TCCR0, TCCR0_CS02 ) ;



	 	 	#endif

	  break;

	  /*******************************************************/

	  case TIMER1 :


			// Clock Select Bit Description
			#if   TIMER1_ClockSelectBit == TIMER1_NoClockSource

				CLR_BIT( TCCR1B, TCCR1B_CS10 ) ;
				CLR_BIT( TCCR1B, TCCR1B_CS11 ) ;
				CLR_BIT( TCCR1B, TCCR1B_CS12 ) ;

			#elif TIMER1_ClockSelectBit == TIMER1_NoPrescaling

				SET_BIT( TCCR1B, TCCR1B_CS10 ) ;
				CLR_BIT( TCCR1B, TCCR1B_CS11 ) ;
				CLR_BIT( TCCR1B, TCCR1B_CS12 ) ;

			#elif TIMER1_ClockSelectBit == TIMER1_DivisionBy_8prescaler

				CLR_BIT( TCCR1B, TCCR1B_CS10 ) ;
				SET_BIT( TCCR1B, TCCR1B_CS11 ) ;
				CLR_BIT( TCCR1B, TCCR1B_CS12 ) ;

			#elif TIMER1_ClockSelectBit == TIMER1_DivisionBy_64prescaler

				SET_BIT( TCCR1B, TCCR1B_CS10 ) ;
				SET_BIT( TCCR1B, TCCR1B_CS11 ) ;
				CLR_BIT( TCCR1B, TCCR1B_CS12 ) ;

			#elif TIMER1_ClockSelectBit == TIMER1_DivisionBy_256prescaler

				CLR_BIT( TCCR1B, TCCR1B_CS10 ) ;
				CLR_BIT( TCCR1B, TCCR1B_CS11 ) ;
				SET_BIT( TCCR1B, TCCR1B_CS12 ) ;

			#elif TIMER1_ClockSelectBit == TIMER1_DivisionBy_1024prescaler

				SET_BIT( TCCR1B, TCCR1B_CS10 ) ;
				CLR_BIT( TCCR1B, TCCR1B_CS11 ) ;
				SET_BIT( TCCR1B, TCCR1B_CS12 ) ;

			#elif TIMER1_ClockSelectBit == TIMER1_ExtClk_FallingEdge.

				CLR_BIT( TCCR1B, TCCR1B_CS10 ) ;
				SET_BIT( TCCR1B, TCCR1B_CS11 ) ;
				SET_BIT( TCCR1B, TCCR1B_CS12 ) ;

			#elif TIMER1_ClockSelectBit == TIMER1_ExtClk_RisingEdge.

				SET_BIT( TCCR1B, TCCR1B_CS10 ) ;
				SET_BIT( TCCR1B, TCCR1B_CS11 ) ;
				SET_BIT( TCCR1B, TCCR1B_CS12 ) ;



	 	 	#endif



	  break;


	  /*******************************************************/

	  case TIMER2 :


			// Clock Select Bit Description
			#if   TIMER2_ClockSelectBit == TIMER2_NoClockSource

				CLR_BIT( TCCR2, TCCR2_CS20 ) ;
				CLR_BIT( TCCR2, TCCR2_CS21 ) ;
				CLR_BIT( TCCR2, TCCR2_CS22 ) ;

			#elif TIMER2_ClockSelectBit == TIMER2_NoPrescaling

				SET_BIT( TCCR2, TCCR2_CS20 ) ;
				CLR_BIT( TCCR2, TCCR2_CS21 ) ;
				CLR_BIT( TCCR2, TCCR2_CS22 ) ;

			#elif TIMER2_ClockSelectBit == TIMER2_DivisionBy_8prescaler

				CLR_BIT( TCCR2, TCCR2_CS20 ) ;
				SET_BIT( TCCR2, TCCR2_CS21 ) ;
				CLR_BIT( TCCR2, TCCR2_CS22 ) ;

			#elif TIMER2_ClockSelectBit == TIMER2_DivisionBy_64prescaler

				SET_BIT( TCCR2, TCCR2_CS20 ) ;
				SET_BIT( TCCR2, TCCR2_CS21 ) ;
				CLR_BIT( TCCR2, TCCR2_CS22 ) ;

			#elif TIMER2_ClockSelectBit == TIMER2_DivisionBy_256prescaler

				CLR_BIT( TCCR2, TCCR2_CS20 ) ;
				CLR_BIT( TCCR2, TCCR2_CS21 ) ;
				SET_BIT( TCCR2, TCCR2_CS22 ) ;

			#elif TIMER2_ClockSelectBit == TIMER2_DivisionBy_1024prescaler

				SET_BIT( TCCR2, TCCR2_CS20 ) ;
				CLR_BIT( TCCR2, TCCR2_CS21 ) ;
				SET_BIT( TCCR2, TCCR2_CS22 ) ;

			#elif TIMER2_ClockSelectBit == TIMER2_ExtClk_FallingEdge.

				CLR_BIT( TCCR2, TCCR2_CS20 ) ;
				SET_BIT( TCCR2, TCCR2_CS21 ) ;
				SET_BIT( TCCR2, TCCR2_CS22 ) ;

			#elif TIMER2_ClockSelectBit == TIMER2_ExtClk_RisingEdge.

				SET_BIT( TCCR2, TCCR2_CS20 ) ;
				SET_BIT( TCCR2, TCCR2_CS21 ) ;
				SET_BIT( TCCR2, TCCR2_CS22 ) ;



	 	 	#endif



	  break;




	}



}

/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/

void MTIMERS_vStopTimer( u8 A_u8TimerID )
{


	switch( A_u8TimerID )
		{

			  case TIMER0 :

					// Clock Select Bit Description == No Clock Source(TIMER0 Stopped)
					CLR_BIT( TCCR0, TCCR0_CS00 ) ;
					CLR_BIT( TCCR0, TCCR0_CS01 ) ;
					CLR_BIT( TCCR0, TCCR0_CS02 ) ;

			  break;

			  /*******************************************************/

			  case TIMER1 :

					// Clock Select Bit Description == No Clock Source(TIMER1 Stopped)
					CLR_BIT( TCCR1B, TCCR1B_CS10 ) ;
					CLR_BIT( TCCR1B, TCCR1B_CS11 ) ;
					CLR_BIT( TCCR1B, TCCR1B_CS12 ) ;

			  break;

			  /*******************************************************/

			  case TIMER2 :

					// Clock Select Bit Description == No Clock Source(TIMER2 Stopped)
					CLR_BIT( TCCR2, TCCR2_CS20 ) ;
					CLR_BIT( TCCR2, TCCR2_CS21 ) ;
					CLR_BIT( TCCR2, TCCR2_CS22 ) ;

			  break;

		}


}


/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/

u16 MTIMERS_u16GetCapturedValue( void )
{

	return ICR1 ;

}


/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/

u16 MTIMERS_u16GetElapsedTime( u8 A_u8TimerID )
{

	u16 L_u16ElapsedTime = Initialized_by_Zero ;

	switch( A_u8TimerID )
	{

		case TIMER0:  L_u16ElapsedTime = TCNT0 ;  break;

		case TIMER1:  L_u16ElapsedTime = TCNT1 ;  break;

		case TIMER2:  L_u16ElapsedTime = TCNT2 ;  break;

	}


	return L_u16ElapsedTime ;

}


/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/

void MTIMERS_vSetICU_Trigger  ( ICU_TriggerType A_xICU_Trigger )
{

	switch( A_xICU_Trigger )
	{

		case ICU_Falling:  CLR_BIT( TCCR1B, TCCR1B_ICES1 ) ;    break;

		case ICU_Rising:   SET_BIT( TCCR1B, TCCR1B_ICES1 ) ;    break;

	}

}


/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/

void MTIMERS_vEnableInterrupt ( u8 A_u8TimerID, u8 A_u8InterruptType )
{


	switch( A_u8TimerID )
	{

		case TIMER0:

			switch( A_u8InterruptType )
			{

				case TIMER0_OVF_INT:  SET_BIT( TIMSK, TIMSK_TOIE0 ) ;  break;

				case TIMER0_CTC_INT:  SET_BIT( TIMSK, TIMSK_OCIE0 ) ;  break;

			}

		break;

	/*******************************************************/

		case TIMER1:

			switch( A_u8InterruptType )
			{

				case TIMER1_ICU_INT:   SET_BIT( TIMSK, TIMSK_TICIE1 ) ; break;

				case TIMER1_CTC1A_INT: SET_BIT( TIMSK, TIMSK_OCIE1A ) ;	break;

				case TIMER1_CTC1B_INT: SET_BIT( TIMSK, TIMSK_OCIE1B ) ;	break;

				case TIMER1_OVF_INT:   SET_BIT( TIMSK, TIMSK_TOIE1  ) ;	break;
			}


		break;

	/*******************************************************/

		case TIMER2:

			switch( A_u8InterruptType )
			{

				case TIMER2_OVF_INT:  SET_BIT( TIMSK, TIMSK_TOIE2 ) ;  break;

				case TIMER2_CTC_INT:  SET_BIT( TIMSK, TIMSK_OCIE2 ) ;  break;

			}


		break;

	}


}


/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/

void MTIMERS_vDisableInterrupt( u8 A_u8TimerID, u8 A_u8InterruptType )
{


	switch( A_u8TimerID )
	{

		case TIMER0:

			switch( A_u8InterruptType )
			{

				case TIMER0_OVF_INT:  CLR_BIT( TIMSK, TIMSK_TOIE0 ) ;  break;

				case TIMER0_CTC_INT:  CLR_BIT( TIMSK, TIMSK_OCIE0 ) ;  break;

			}

		break;

	/*******************************************************/

		case TIMER1:

			switch( A_u8InterruptType )
			{

				case TIMER1_ICU_INT:   CLR_BIT( TIMSK, TIMSK_TICIE1 ) ; break;

				case TIMER1_CTC1A_INT: CLR_BIT( TIMSK, TIMSK_OCIE1A ) ;	break;

				case TIMER1_CTC1B_INT: CLR_BIT( TIMSK, TIMSK_OCIE1B ) ;	break;

				case TIMER1_OVF_INT:   CLR_BIT( TIMSK, TIMSK_TOIE1  ) ;	break;
			}


		break;

	/*******************************************************/

		case TIMER2:

			switch( A_u8InterruptType )
			{

				case TIMER2_OVF_INT:  CLR_BIT( TIMSK, TIMSK_TOIE2 ) ;  break;

				case TIMER2_CTC_INT:  CLR_BIT( TIMSK, TIMSK_OCIE2 ) ;  break;

			}


		break;

	}



}


/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/

void MTIMERS_vSetCallBack( u8 A_u8TimerID, u8 A_u8InterruptType, void (*A_Fptr)(void) )
{




	switch( A_u8TimerID )
	{

		case TIMER0:

			switch( A_u8InterruptType )
			{

				case TIMER0_OVF_INT:  GS_TIMER0_vpPtrToFunction[TIMER0_ISR_OVF] = A_Fptr ;  break;

				case TIMER0_CTC_INT:  GS_TIMER0_vpPtrToFunction[TIMER0_ISR_CTC] = A_Fptr ;  break;

			}

		break;

	/*******************************************************/

		case TIMER1:

			switch( A_u8InterruptType )
			{

				case TIMER1_ICU_INT:   GS_TIMER1_vpPtrToFunction[TIMER1_ISR_ICU]   = A_Fptr ;  break;

				case TIMER1_CTC1A_INT: GS_TIMER1_vpPtrToFunction[TIMER1_ISR_CTC1A] = A_Fptr ;  break;

				case TIMER1_CTC1B_INT: GS_TIMER1_vpPtrToFunction[TIMER1_ISR_CTC1B] = A_Fptr ;  break;

				case TIMER1_OVF_INT:   GS_TIMER1_vpPtrToFunction[TIMER1_ISR_OVF]   = A_Fptr ;  break;
			}


		break;

	/*******************************************************/

		case TIMER2:

			switch( A_u8InterruptType )
			{

				case TIMER2_OVF_INT:  GS_TIMER2_vpPtrToFunction[TIMER2_ISR_OVF] = A_Fptr ;  break;

				case TIMER2_CTC_INT:  GS_TIMER2_vpPtrToFunction[TIMER2_ISR_CTC] = A_Fptr ;  break;

			}


		break;

	}




}


/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/

TIMER0_OVF_ISR
{

	static u32 LS_u32OVF_Counter = 0 ;

	LS_u32OVF_Counter++ ;

	if( LS_u32OVF_Counter == G_u32IntervalCounts )
	{
		if( GS_TIMER0_vpPtrToFunction[TIMER0_ISR_OVF] != NULL )
		{

			GS_TIMER0_vpPtrToFunction[TIMER0_ISR_OVF]() ;

			LS_u32OVF_Counter = 0 ;

		}

	}

}


/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/

TIMER0_COMP_ISR
{

	static u32 LS_u32CTC_Counter = 0 ;

	LS_u32CTC_Counter++ ;

	if( LS_u32CTC_Counter == G_u32IntervalCounts )
	{
		if( GS_TIMER0_vpPtrToFunction[TIMER0_ISR_CTC] != NULL )
		{

			GS_TIMER0_vpPtrToFunction[TIMER0_ISR_CTC]() ;

			LS_u32CTC_Counter = 0 ;

		}

	}


}


/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/

TIMER1_CAPT_ISR
{

	GS_TIMER1_vpPtrToFunction[TIMER1_ISR_ICU] ( ) ;


}


/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/

TIMER1_COMPA_ISR
{

	GS_TIMER1_vpPtrToFunction[TIMER1_ISR_CTC1A] ( ) ;

}


/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/

TIMER1_COMPB_ISR
{

	GS_TIMER1_vpPtrToFunction[TIMER1_ISR_CTC1B] ( ) ;

}


/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/

TIMER1_OVF_ISR
{


	GS_TIMER1_vpPtrToFunction[TIMER1_ISR_OVF] ( ) ;


}


/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/

TIMER2_COMP_ISR
{

	GS_TIMER2_vpPtrToFunction[TIMER2_ISR_CTC] ( ) ;


}


/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/

TIMER2_OVF_ISR
{

	GS_TIMER2_vpPtrToFunction[TIMER2_ISR_OVF] ( ) ;

}


/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/









































