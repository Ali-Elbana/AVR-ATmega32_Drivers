/*
 * MTimer2_config.h
 *
 *  Created on: Jul 28, 2022
 *      Author: Ali El Bana
 */

#ifndef COTS_MCAL_MTIMERS_MTIMER2_CONFIG_H_
#define COTS_MCAL_MTIMERS_MTIMER2_CONFIG_H_



/**********************************************************************************/

/*options:
 *TIMER2_NORMAL_MODE
 *TIMER2_PWM_PhaseCorrect
 *TIMER2_CTC
 *TIMER2_FastPWM
 */
#define TIMER2_WAVEFORM_GENERATION_MODE TIMER2_FastPWM

/**********************************************************************************/

/*options:
 *TIMER2_COMP_NonPWM
 *TIMER2_COMP_FastPWM
 *TIMER2_COMP_PhaseCorrectPWM
 */
#define TIMER2_COMP_MODE TIMER2_COMP_FastPWM

/**********************************************************************************/

/*options:
 *TIMER2_NORMAL_MODE
 *TIMER2_ToggleOnCOMP
 *TIMER2_ClearOnCOMP
 *TIMER2_SetOnCOMP
 */
#define TIMER2_COMP_NonPWM_MODE TIMER2_NORMAL_MODE

/**********************************************************************************/

/*options:
 *TIMER2_NORMAL_MODE
 *TIMER2_ClearOnCOMP
 *TIMER2_SetOnCOMP
 */
#define TIMER2_COMP_FastPWM_MODE TIMER2_ClearOnCOMP

/**********************************************************************************/

/*options:
 *TIMER2_NORMAL_MODE
 *TIMER2_ClearOnCOMP
 *TIMER2_SetOnCOMP
 */
#define TIMER2_COMP_PhaseCorrectPWM_MODE TIMER2_ClearOnCOMP

/**********************************************************************************/

/*options:
 *1-TIMER2_NoClockSource
 *2-TIMER2_NoPrescaling
 *3-TIMER2_DivisionBy_8prescaler
 *4-TIMER2_DivisionBy_64prescaler
 *5-TIMER2_DivisionBy_256prescaler
 *6-TIMER2_DivisionBy_1024prescaler
 *7-TIMER2_ExtClk_FallingEdge
 *8-TIMER2_ExtClk_RisingEdge
 */
#define TIMER2_ClockSelectBit TIMER2_DivisionBy_8prescaler

/**********************************************************************************/

/*options:
 *ENABLE
 *DISABLE
 */
#define TIMER2_ToBe_Asynch DISABLE

/**********************************************************************************/






#define TIMER2_ISR_Options 2



#endif /* COTS_MCAL_MTIMERS_MTIMER2_CONFIG_H_ */
