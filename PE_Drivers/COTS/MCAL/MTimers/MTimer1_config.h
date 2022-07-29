/*
 * MTimer1_config.h
 *
 *  Created on: Jul 28, 2022
 *      Author: Ali El Bana
 */

#ifndef COTS_MCAL_MTIMERS_MTIMER1_CONFIG_H_
#define COTS_MCAL_MTIMERS_MTIMER1_CONFIG_H_



/*options:
 *TIMER1_COMP_NonPWM
 *TIMER1_COMP_FastPWM
 *TIMER1_COMP_PhaseCorrectPWM
 */
#define TIMER1_COMP_MODE TIMER1_COMP_NonPWM

/**********************************************************************************/

/*options:
 *TIMER1_NORMAL_MODE
 *TIMER1_ToggleOnCOMP
 *TIMER1_ClearOnCOMP
 *TIMER1_SetOnCOMP
 */
#define TIMER1_COMP_NonPWM_MODE TIMER1_NORMAL_MODE

/**********************************************************************************/

/*options:
 *TIMER1_NORMAL_MODE
 *TIMER1_ToggleOnCOMP
 *TIMER1_ClearOnCOMP
 *TIMER1_SetOnCOMP
 */
#define TIMER1_COMP_FastPWM_MODE TIMER1_ClearOnCOMP

/**********************************************************************************/

/*options:
 *TIMER1_NORMAL_MODE
 *TIMER1_ToggleOnCOMP
 *TIMER1_ClearOnCOMP
 *TIMER1_SetOnCOMP
 */
#define TIMER1_COMP_PhaseCorrectPWM_MODE TIMER1_SetOnCOMP

/**********************************************************************************/

/*options:
 *1- TIMER1_Normal
 *2- TIMER1_PWM_PHASE_CORRECT_8_bit
 *3- TIMER1_PWM_PHASE_CORRECT_9_bit
 *4- TIMER1_PWM_PHASE_CORRECT_10_bit
 *5- TIMER1_CTC_OCR1A
 *6- TIMER1_Fast_PWM_8_bit
 *7- TIMER1_Fast_PWM_9_bit
 *8- TIMER1_Fast_PWM_10_bit
 *9- TIMER1_PWM_Phase_and_Frequency_Correct_ICR1
 *10-TIMER1_PWM_Phase_and_Frequency_Correct_OCR1A
 *11-TIMER1_PWM_Phase_Correct_ICR1
 *12-TIMER1_PWM_Phase_Correct_OCR1A
 *13-TIMER1_CTC_ICR1
 *14-TIMER1_Fast_PWM_ICR1
 *15-TIMER1_Fast_PWM_OCR1A
 */
#define TIMER1_WAVEFORM_GENERATION_MODE TIMER1_Normal

/**********************************************************************************/

/*options:
 *ENABLE
 *DISABLE
 */
#define TIMER1_ICU ENABLE

/**********************************************************************************/

/*options:
 *ENABLE
 *DISABLE
 */
#define ICU_NoiseCanceler ENABLE

/**********************************************************************************/

/*options:
 *ICU_Rising_Edge
 *ICU_Falling_Edge
 */
#define ICU_Edge_Select ICU_Rising_Edge

/**********************************************************************************/

/*options:
 *1-TIMER1_NoClockSource
 *2-TIMER1_NoPrescaling
 *3-TIMER1_DivisionBy_8prescaler
 *4-TIMER1_DivisionBy_64prescaler
 *5-TIMER1_DivisionBy_256prescaler
 *6-TIMER1_DivisionBy_1024prescaler
 *7-TIMER1_ExtClk_FallingEdge
 *8-TIMER1_ExtClk_RisingEdge
 */
#define TIMER1_ClockSelectBit TIMER1_DivisionBy_8prescaler

/**********************************************************************************/

/*options:
 * SET_ON_ICR1
 * SET_ON_OCR1A
 */
#define Set_TOP_Value SET_ON_ICR1

/**********************************************************************************/

/*options:
 * Register_1A
 * Register_1B
 */
#define Compare_Register Register_1A

/**********************************************************************************/


/**********************************************************************************/


#define TIMER1_ISR_Options 4














#endif /* COTS_MCAL_MTIMERS_MTIMER1_CONFIG_H_ */
