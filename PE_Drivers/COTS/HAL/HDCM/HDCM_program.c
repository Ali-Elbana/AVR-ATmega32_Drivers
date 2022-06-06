/* FILENAME: HDCM_program 
*  Author:  Ali El Bana
*  Version:  V1.0
*  DATE:   Fri 06/03/2022
*/



#include "../../LIB/LSTD_TYPES.h"
#include "../../LIB/LSTD_TYPES.h"

#include "../../MCAL/MDIO/MDIO_inter.h"

#include "HDCM_interface.h"
#include "HDCM_private.h"
#include "HDCM_config.h"






/*****************************************************************************************************************************************/
/****************************************************************************************************************************************/


void HDCM_vRotateMotor ( u8 A_u8PortNum, u8 A_u8PinNum1, u8 A_u8PinNum2, u8 A_u8Rotate )
{



	MDIO_vSetPinDirection( A_u8PortNum, A_u8PinNum1, MDIO_OUTPUT );

	MDIO_vSetPinDirection( A_u8PortNum, A_u8PinNum2, MDIO_OUTPUT );



	switch( A_u8Rotate )
	{

		case CW:  MDIO_vSetPinValue( A_u8PortNum, A_u8PinNum1, MDIO_PIN_HIGH ); MDIO_vSetPinValue( A_u8PortNum, A_u8PinNum2, MDIO_PIN_LOW  ); break;

		case CCW: MDIO_vSetPinValue( A_u8PortNum, A_u8PinNum1, MDIO_PIN_LOW  ); MDIO_vSetPinValue( A_u8PortNum, A_u8PinNum2, MDIO_PIN_HIGH ); break;

	}



	// TODO: Setup speed control pin.



}


/*****************************************************************************************************************************************/
/****************************************************************************************************************************************/


void HDCM_vRotate_CW( void )
{

	// TODO: Implement speed as input.








}


/*****************************************************************************************************************************************/
/****************************************************************************************************************************************/


void HDCM_vRotate_CCW( void )
{


	// TODO: Implement speed as input.






}


/*****************************************************************************************************************************************/
/****************************************************************************************************************************************/


void HDCM_vStopMotor ( u8 A_u8PortNum, u8 A_u8PinNum1, u8 A_u8PinNum2 )
{


	MDIO_vSetPinValue( A_u8PortNum, A_u8PinNum1, MDIO_PIN_LOW );

	MDIO_vSetPinValue( A_u8PortNum, A_u8PinNum2, MDIO_PIN_LOW );

}


/*****************************************************************************************************************************************/
/****************************************************************************************************************************************/
