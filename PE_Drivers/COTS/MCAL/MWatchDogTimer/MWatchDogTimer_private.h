/* FILENAME: MWatchDogTimer_private  
*  Author:  Ali El Bana
*  Version:  V1.0
*  DATE:   Mon 08/01/2022
*/
#ifndef _MWatchDogTimer_private_H
#define _MWatchDogTimer_private_H




#define WDTCR	*( ( volatile u8* )(0x41) )

#define WDTCR_WDTOE 4
#define WDTCR_WDE 	3
#define WDTCR_WDP2 	2
#define WDTCR_WDP1 	1
#define WDTCR_WDP0 	0


#define SetTimeout_BitMask 0xF8

#define WDT_16ms 	0b000
#define WDT_33ms 	0b001
#define WDT_65ms 	0b010
#define WDT_130ms 	0b011
#define WDT_260ms 	0b100
#define WDT_520ms 	0b101
#define WDT_1s   	0b110
#define WDT_2s 	 	0b111


#define CLR_WDTCR 	0x00


#endif //_MWatchDogTimer_private_H
