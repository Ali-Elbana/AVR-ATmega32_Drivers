/* FILENAME: MEXTI_config  
*  Author:  Ali El Bana
*  Version:  V1.0
*  DATE:   Sat 06/04/2022
*/
#ifndef _MEXTI_config_H
#define _MEXTI_config_H






#define EXTI_INT0 Enable

#define EXTI_INT1 Disable

#define EXTI_INT2 Disable



/**
 * Options:
 * EXTI_FallingEdge ,
 * EXTI_RisingEdge	,
 * EXTI_LowLevel	,
 * EXTI_OnChange
 */
#define EXTI_INT0_SENSE_CTRL EXTI_FallingEdge


/**
 * Options:
 * EXTI_FallingEdge ,
 * EXTI_RisingEdge	,
 * EXTI_LowLevel	,
 * EXTI_OnChange
 */
#define EXTI_INT1_SENSE_CTRL EXTI_FallingEdge


/**
 * Options:
 * EXTI_FallingEdge ,
 * EXTI_RisingEdge
 */
#define EXTI_INT2_SENSE_CTRL EXTI_FallingEdge



#define Enable 	1
#define Disable 2



#define ISR_INT0  	INT0_VectorNum


#define ISR_INT1  	INT1_VectorNum


#define ISR_INT2  	INT2_VectorNum



#endif //_MEXTI_config_H
