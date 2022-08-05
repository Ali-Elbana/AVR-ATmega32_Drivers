/* FILENAME: MWatchDogTimer_interface  
*  Author:  Ali El Bana
*  Version:  V1.0
*  DATE:   Mon 08/01/2022
*/
#ifndef _MWatchDogTimer_interface_H
#define _MWatchDogTimer_interface_H

#include "MWatchDogTimer_private.h"

void MWDT_vTurnOn( u8 A_u8TimeOut ) ;

void MWDT_vTurnOff( void ) ;



/**********************************************************************************/

/*options:
 *1-WDT_16ms_5V
 *2-WDT_33ms_5V
 *3-WDT_65ms_5V
 *4-WDT_130ms_5V
 *5-WDT_260ms_5V
 *6-WDT_520ms_5V
 *7-WDT_1s_5V
 *8-WDT_2s_5V
 */
#define WDT_PrescaleSelect WDT_128K_130ms_5V

/**********************************************************************************/

#define WDT_16ms_5V  WDT_16ms
#define WDT_33ms_5V  WDT_33ms
#define WDT_65ms_5V  WDT_65ms
#define WDT_130ms_5V WDT_130ms
#define WDT_260ms_5V WDT_260ms
#define WDT_520ms_5V WDT_520ms
#define WDT_1s_5V  	 WDT_1s
#define WDT_2s_5V 	 WDT_2s




#endif //_MWatchDogTimer_interface_H
