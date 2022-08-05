/* FILENAME: MWatchDogTimer_program 
*  Author:  Ali El Bana
*  Version:  V1.0
*  DATE:   Mon 08/01/2022
*/

#include "../../LIB/LSTD_TYPES.h"
#include "../../LIB/LBITMATH.h"

#include "MWatchDogTimer_interface.h"
#include "MWatchDogTimer_private.h"
#include "MWatchDogTimer_config.h"



void MWDT_vTurnOn( u8 A_u8TimeOut )
{

	// Set timeout.
	WDTCR = ( WDTCR & SetTimeout_BitMask ) | ( A_u8TimeOut ) ;

	// When the WDE is written to logic one, the Watchdog Timer is enabled.
	SET_BIT( WDTCR, WDTCR_WDE ) ;

}


/****************************************************************************************/
/***************************************************************************************/


void MWDT_vTurnOff( void )
{

	// Write logical one to WDTOE and WDE.
	WDTCR = ( 1 << WDTCR_WDTOE ) | ( 1 << WDTCR_WDE ) ;

	// Turn off WDT.
	WDTCR = CLR_WDTCR ;

}


/****************************************************************************************/
/***************************************************************************************/




