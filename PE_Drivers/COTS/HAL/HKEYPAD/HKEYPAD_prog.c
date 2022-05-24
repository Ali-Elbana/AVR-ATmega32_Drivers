/*
 * kpad_prog.c
 *
 *  Created on: Sep 18, 2021
 *      Author: Ali El Bana
 */



#include "../../LIB/LSTD_TYPES.h"
#include "../../MCAL/MDIO/MDIO_inter.h"

#include "HKEYPAD_config.h"
#include "HKEYPAD_private.h"
#include "HKEYPAD_inter.h"

#include<util/delay.h>





u8 kmap[4][4]=
{

	{ K1 ,  K2 ,  K3 ,  K4  } ,

	{ K5 ,  K6 ,  K7 ,  K8  } ,

	{ K9 ,  K10,  K11,  K12 } ,

	{ K13,  K14,  K15,  K16 }

};



/**************************************************************************************************************/
/*************************************************************************************************************/


void HKEYPAD_vInit( void )
{

	MDIO_vSetPortDirection( HKEYPAD_PORT, MDIO_SET_NibbleLow ) ;

	MDIO_vSetPortValue	  ( HKEYPAD_PORT, MDIO_PORT_HIGH )	 ;

}



/**************************************************************************************************************/
/*************************************************************************************************************/



u8 HKEYPAD_u8Getpressed( void )
{



	u8 L_u8PressedKey = -1 ;


	for(u8 L_u8Column = Initialized_by_Zero ; L_u8Column <4 ; L_u8Column++ )
	{

		MDIO_vSetPinValue( HKEYPAD_PORT, L_u8Column, MDIO_PIN_LOW ) ;


		for( u8 L_u8Row = Initialized_by_Zero ; L_u8Row <4 ; L_u8Row++ )
		{


			// Button is pressed
			if( MDIO_u8GetPinValue(HKEYPAD_PORT, L_u8Row+4) == HBUTTON_Pressed )
			{


				L_u8PressedKey = kmap[L_u8Row][L_u8Column] ;


			}


			while( MDIO_u8GetPinValue(HKEYPAD_PORT, L_u8Row+4) == HBUTTON_Pressed ) ;

			_delay_ms(5);

		}


		MDIO_vSetPinValue( HKEYPAD_PORT, L_u8Column, MDIO_PIN_HIGH ) ;

	}



	return L_u8PressedKey ;


}
