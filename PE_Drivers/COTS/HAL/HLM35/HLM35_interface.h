/* FILENAME: HLM35_interface  
*  Author:  Ali El Bana
*  Version:  V1.0
*  DATE:   Fri 07/15/2022
*/
#ifndef _HLM35_interface_H
#define _HLM35_interface_H


u16 HLM35_u16GetTemperature( u8 A_u8ADCChannel, u32 A_u32Vref, u32 A_32BitNums ) ;


#define Vref 	5

#define BitNums 10


#endif //_HLM35_interface_H
