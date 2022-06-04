/*
 * SSD_program.c
 *
 *  Created on: Sep 4, 2021
 *      Author: rotana
 */


#include "../../LIB/LSTD_TYPES.h"
#include "../../LIB/LBITMATH.h"

#include "../../MCAL/MDIO/MDIO_inter.h"

#include "HSSD_inter.h"
#include "HSSD_config.h"
#include "HSSD_private.h"



static const u8 SCG_u8SSD_Nums[ ]=
{

	DISP_ZERO , //0
	DISP_ONE  , //1
	DISP_TWO  , //2
	DISP_THREE, //3
	DISP_FOUR , //4
	DISP_FIVE , //5
	DISP_SIX  , //6
	DISP_SEVEN, //7
	DISP_EIGHT, //8
	DISP_NINE   //9

};


/**************************************************************************************************************/
/*************************************************************************************************************/


void  HSSD_vDispNum( u8 A_u8PortNum, u8 A_u8Num )
{

	// Input validation
	if( A_u8Num < 10 )
	{


		MDIO_vSetPortDirection( A_u8PortNum, MDIO_OUTPUT ) ;


		#if COM_CATHODE == HSSD_Type


			MDIO_vSetPortValue( A_u8PortNum, SCG_u8SSD_Nums[ A_u8Num ] ) ;


		#elif HSSD_Type == COM_ANODE


			MDIO_vSetPortValue( A_u8PortNum, ~SCG_u8SSD_Nums[ A_u8Num ] ) ;


		#endif



	}




}



/**************************************************************************************************************/
/*************************************************************************************************************/


void  HSSD_vTurnOFF( u8 A_u8PortNum )
{


	#if COM_CATHODE == HSSD_Type


		MDIO_vSetPortValue( MDIO_PORTA, MDIO_PORT_LOW ) ;


	#elif HSSD_Type == COM_ANODE


		MDIO_vSetPortValue( MDIO_PORTA, MDIO_PORT_HIGH ) ;


	#endif


}





/**************************************************************************************************************/
/*************************************************************************************************************/




































