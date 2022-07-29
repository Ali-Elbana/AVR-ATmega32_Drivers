/* FILENAME: MTimers_config  
*  Author:  Ali El Bana
*  Version:  V1.0
*  DATE:   Fri 07/22/2022
*/
#ifndef _MTimers_config_H
#define _MTimers_config_H



/**********************************************************************************/

/*options:
 *TIMER0_NORMAL_MODE
 *TIMER0_PWM_PhaseCorrect
 *TIMER0_CTC
 *TIMER0_FastPWM
 */
#define TIMER0_WAVEFORM_GENERATION_MODE TIMER0_FastPWM

/**********************************************************************************/

/*options:
 *1-TIMER0_NoClockSource
 *2-TIMER0_NoPrescaling
 *3-TIMER0_DivisionBy_8prescaler
 *4-TIMER0_DivisionBy_64prescaler
 *5-TIMER0_DivisionBy_256prescaler
 *6-TIMER0_DivisionBy_1024prescaler
 *7-TIMER0_ExtClk_FallingEdge
 *8-TIMER0_ExtClk_RisingEdge
 */
#define TIMER0_ClockSelectBit TIMER0_DivisionBy_8prescaler

/**********************************************************************************/

/*options:
 *TIMER0_COMP_NonPWM
 *TIMER0_COMP_FastPWM
 *TIMER0_COMP_PhaseCorrectPWM
 */
#define TIMER0_COMP_MODE TIMER0_COMP_FastPWM

/**********************************************************************************/

/*options:
 *TIMER0_NORMAL_MODE
 *TIMER0_ToggleOnCOMP
 *TIMER0_ClearOnCOMP
 *TIMER0_SetOnCOMP
 */
#define TIMER0_COMP_NonPWM_MODE TIMER0_NORMAL_MODE

/**********************************************************************************/

/*options:
 *TIMER0_NORMAL_MODE
 *TIMER0_ClearOnCOMP
 *TIMER0_SetOnCOMP
 */
#define TIMER0_COMP_FastPWM_MODE TIMER0_ClearOnCOMP

/**********************************************************************************/

/*options:
 *TIMER0_NORMAL_MODE
 *TIMER0_ClearOnCOMP
 *TIMER0_SetOnCOMP
 */
#define TIMER0_COMP_PhaseCorrectPWM_MODE TIMER0_ClearOnCOMP

/**********************************************************************************/




#define TIMER0_ISR_Options 2









#endif //_MTimers_config_H
