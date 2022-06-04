/* FILENAME: HDCM_interface  
*  Author:  Ali El Bana
*  Version:  V1.0
*  DATE:   Fri 06/03/2022
*/
#ifndef _HDCM_interface_H
#define _HDCM_interface_H






void HDCM_vRotateMotor	( u8 A_u8PortNum, u8 A_u8PinNum1, u8 A_u8PinNum2, u8 A_u8Rotate ) 	;

void HDCM_vRotate_CW 	( void ) 															;

void HDCM_vRotate_CCW 	( void ) 															;

void HDCM_vStopMotor	( u8 A_u8PortNum, u8 A_u8PinNum1, u8 A_u8PinNum2 ) 					;




#define CW 	1

#define CCW 2











#endif //_HDCM_interface_H
