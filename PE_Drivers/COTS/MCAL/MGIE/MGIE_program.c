/* FILENAME: MGIE_program 
*  Author:  Ali El Bana
*  Version:  V1.0
*  DATE:   Sat 06/04/2022
*/

#include "../../LIB/LSTD_TYPES.h"
#include "../../LIB/LBITMATH.h"

#include "../MDIO/MDIO_inter.h"

#include "MGIE_interface.h"
#include "MGIE_private.h"
#include "MGIE_config.h"




void MGIE_vEnableGlobalInterrupt( void )
{

	SET_BIT( SREG, SREG_I ) ;

}


/********************************************************************************************************************/
/*******************************************************************************************************************/


void MGIE_vDisableGlobalInterrupt( void )
{

	CLR_BIT( SREG, SREG_I ) ;

}






































