/* FILENAME: HLM35_program 
*  Author:  Ali El Bana
*  Version:  V1.0
*  DATE:   Fri 07/15/2022
*/

#include "../../LIB/LSTD_TYPES.h"
#include "../../LIB/LBITMATH.h"

#include "HLM35_interface.h"
#include "HLM35_private.h"
#include "HLM35_config.h"

#include "../../MCAL/MADC/MADC_interface.h"



u16 HLM35_u16GetTemperature( u8 A_u8ADCChannel, u32 A_u32Vref, u32 A_32BitNums )
{

	u16 L_u16ADCValue = MADC_u16ConvertAnalog_to_Digital( CHANNEL_00 ) ;

	u16 L_u16Temperature = ( (u32)L_u16ADCValue * ( (u32)A_u32Vref * 100 ) ) / (u32)( 1 << A_32BitNums ) ;

	return L_u16Temperature ;

}



