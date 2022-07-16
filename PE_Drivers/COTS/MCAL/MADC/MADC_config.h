/* FILENAME: MADC_config  
*  Author:  Ali El Bana
*  Version:  V1.0
*  DATE:   Sun 07/10/2022
*/
#ifndef _MADC_config_H
#define _MADC_config_H

/*options:
 * 1-AVCC
 * 2-AREF
 * 3-Internal_Volt
 */
#define ADC_REF_VOLT 		AVCC


/*options:
 * 1-RIGHT_Adjust
 * 2-LEFT_Adjust
 */
#define ADC_Data_Adjustment RIGHT_Adjust


/*options:
 *1-PrescalerMode_2
 *2-PrescalerMode_4
 *3-PrescalerMode_8
 *4-PrescalerMode_16
 *5-PrescalerMode_32
 *6-PrescalerMode_64
 *7-PrescalerMode_128
 */
#define ADC_Prescaler PrescalerMode_64


/*options:
 * 1-ENABLE
 * 2-DISABLE
 */
#define AUTO_TRIGGER  DISABLE


/*options:
 * 1-ENABLE
 * 2-DISABLE
 */
#define INTERRUPT  DISABLE


/*options:
 * 1-ENABLE
 * 2-DISABLE
 */
#define ADC_Peripheral ENABLE


/*options:
 * 1-FreeRunningMode
 * 2-AnalogComparator
 * 3-External_InterruptRequest0
 * 4-TimerCounter0_CompareMatch
 * 5-TimerCounter0_Overflow
 * 6-TimerCounterCompare_MatchB
 * 7-TimerCounter1_Overflow
 * 8-TimerCounter1_CaptureEvent
 */
#define TriggerSource_Option FreeRunningMode


#define ADC_ISR ADC_VectorNum





#endif //_MADC_config_H
