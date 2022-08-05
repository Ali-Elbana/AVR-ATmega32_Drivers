/*
 * main.c
 *
 *  Created on: May 18, 2022
 *      Author: Ali El-bana
 */

#include "../LIB/LBITMATH.h"
#include "../LIB/LSTD_TYPES.h"

#include "../MCAL/MDIO/MDIO_inter.h"
#include "../MCAL/MGIE/MGIE_interface.h"
#include "../MCAL/MEXTI/MEXTI_interface.h"
#include "../MCAL/MADC/MADC_interface.h"
#include "../MCAL/MTimers/MTimers_interface.h"
#include "../MCAL/MWatchDogTimer/MWatchDogTimer_interface.h"
#include "../MCAL/MUART/MUART_interface.h"
#include "../MCAL/MSPI/MSPI_interface.h"

#include "../HAL/HSSD/HSSD_inter.h"
#include "../HAL/HKEYPAD/HKEYPAD_inter.h"
#include "../HAL/HLCD/HLCD_inter.h"
#include "../HAL/HDCM/HDCM_interface.h"
#include "../HAL/HLM35/HLM35_interface.h"
#include "../HAL/HLDR/HLDR_interface.h"

#include "util/delay.h"

#define KEYPAD 			STOP
#define LCD				STOP
#define MOVING_NAME 	STOP
#define Stepper_Motor 	STOP
#define DC_MOTOR 		STOP
#define Interrupt 		STOP
#define ADC_INTERRUPT 	STOP
#define LM35_POLLING 	STOP
#define LDR_POLLING 	STOP
#define ADC_MAPPING		STOP
#define TIMER0_APP		STOP
#define TIMER1_APP		STOP
#define ICU_APP			STOP
#define WDT_APP			STOP
#define UART_APP		STOP
#define SPI_APP			RUN




#if SPI_APP == RUN

int main(void)
{

	u8 L_u8Char = Initialized_by_Zero ;

	MDIO_vSetPinDirection( MDIO_PORTB, MDIO_PIN3, MDIO_OUTPUT ) ; // LED for testing.

	MDIO_vSetPinValue( MDIO_PORTB, MDIO_PIN3, MDIO_PIN_LOW ) ;

	MSPI_vInit( ) ;

	L_u8Char = MSPI_u8Transecieve( 'A' ) ;


	if( L_u8Char == 'A' )
	{
		MDIO_vSetPinValue( MDIO_PORTB, MDIO_PIN3, MDIO_PIN_HIGH ) ;
	}

	else
	{
		MDIO_vSetPinValue( MDIO_PORTB, MDIO_PIN3, MDIO_PIN_LOW ) ;
	}


	while( TRUE )
	{



	}


}


#endif





#if UART_APP == RUN




int main(void)
{

	MUART_vInit( ) ;

	MUART_vTransmit( 'A' ) ;

	while( TRUE )
	{


	}


}


#endif





#if WDT_APP == RUN




int main(void)
{

	MDIO_vSetPinDirection( MDIO_PORTD, MDIO_PIN0, MDIO_OUTPUT ) ;

	MWDT_vTurnOn( WDT_1s_5V ) ;

	MDIO_vSetPinValue( MDIO_PORTD, MDIO_PIN0, MDIO_PIN_HIGH ) ;

	_delay_ms( 500 ) ;

	MDIO_vSetPinValue( MDIO_PORTD, MDIO_PIN0, MDIO_PIN_LOW ) ;

	MWDT_vTurnOff( ) ;

	while( TRUE )
	{


	}


}


#endif




#if ICU_APP == RUN


void ReadPWM ( void ) ;

volatile u8 G_u8ReadingFlag 	= Initialized_by_Zero ;

volatile u16 G_u16PeriodicTime 	= Initialized_by_Zero ;

volatile u16 G_u16OnTime     	= Initialized_by_Zero ;




int main(void)
{

	MDIO_vSetPinDirection( MDIO_PORTB, MDIO_PIN3, MDIO_OUTPUT ) ; // OC0

	MDIO_vSetPinDirection( MDIO_PORTD, MDIO_PIN6, MDIO_OUTPUT ) ; // ICP1

	//MDIO_vSetPinDirection( MDIO_PORTD, MDIO_PIN5, MDIO_OUTPUT ) ; // OC1A

	MTIMERS_vSetCallBack( TIMER1, TIMER1_ICU_INT, ReadPWM ) ;

	MTIMER0_vInit( ) ;

	MTIMER1_vInit( ) ;

	HLCD_vInit	 ( ) ;

	MTIMERS_vSetCompareValue( TIMER0, 127) ;

	MTIMERS_vStartTimer( TIMER0 ) ;

	MTIMERS_vStartTimer( TIMER1 ) ;

	MGIE_vEnableGlobalInterrupt( ) ;


	while( TRUE )
	{


		if( G_u8ReadingFlag == Flag_is_Set )
		{

			G_u8ReadingFlag = Flag_is_Cleared ;

			HLCD_vClear( ) ;

			_delay_ms(100);

			HLCD_vDispNumber( G_u16OnTime ) ;

			HLCD_vGoTo( HLCD_LINE2, HLCD_Square1 ) ;

			HLCD_vDispNumber( G_u16PeriodicTime ) ;

			MTIMERS_vEnableInterrupt( TIMER1, TIMER1_ICU_INT ) ;

		}






	}


}




void ReadPWM ( void )
{

	static u8 LS_u8Counter 				= Initialized_by_Zero ;

	static u16 LS_u16TimerReadings[3] 	= { Initialized_by_Zero } ;

	LS_u8Counter++ ;

	switch( LS_u8Counter )
	{

		case 1 :

			LS_u16TimerReadings[ 0 ] = MTIMERS_u16GetCapturedValue(  ) ;

			MTIMERS_vSetICU_Trigger( ICU_Rising ) ;

		break;



		case 2 :

			LS_u16TimerReadings[ 1 ] = MTIMERS_u16GetCapturedValue(  ) ;

			MTIMERS_vSetICU_Trigger( ICU_Falling ) ;

			G_u16PeriodicTime = LS_u16TimerReadings[ 1 ] - LS_u16TimerReadings[ 0 ] ;

		break;



		case 3 :

			LS_u16TimerReadings[ 2 ] = MTIMERS_u16GetCapturedValue(  ) ;

			MTIMERS_vDisableInterrupt( TIMER1, TIMER1_ICU_INT ) ;

			G_u16OnTime = LS_u16TimerReadings[ 2 ] - LS_u16TimerReadings[ 1 ] ;

			LS_u8Counter = Initialized_by_Zero ;

			G_u8ReadingFlag = Flag_is_Set ;

		break;





	}





}




#endif






#if TIMER1_APP == RUN


//void TogglePinValue (void) ;

int main(void)
{


	MDIO_vSetPinDirection( MDIO_PORTD, MDIO_PIN5, MDIO_OUTPUT ) ;

	MTIMER1_vInit( ) ;

	MTIMERS_vStartTimer( TIMER1 ) ;

	MTIMER1_vSetTopValue( TIMER1_TopValue ) ;

	//s32 L_s32ServoAngle = Initialized_by_Zero ;

	MTIMERS_vSetCompareValue( TIMER1, 2000 ) ;

	while( TRUE )
	{


		for( u16 L_u16Iteration = 1000; L_u16Iteration <= 2000; L_u16Iteration++ )
		{

			MTIMERS_vSetCompareValue( TIMER1, L_u16Iteration ) ;

			_delay_ms(10);

		}


	}


}


#endif






#if TIMER0_APP == RUN


//void TogglePinValue (void) ;

int main(void)
{


	MDIO_vSetPinDirection( MDIO_PORTB, MDIO_PIN3, MDIO_OUTPUT ) ;

	MTIMER0_vInit( ) ;

	//MTIMERS_vSetInterval_CTC_Asynch( TIMER0, TIMER0_CompareValue, TIMER0_IntervalCounts, TogglePinValue ) ;

	//MGIE_vEnableGlobalInterrupt();

	MTIMERS_vStartTimer( TIMER0 ) ;

	while( TRUE )
	{

		//fade in
		for( u8 L_u8Iteration = Initialized_by_Zero; L_u8Iteration < 255; L_u8Iteration++ )
		{

			MTIMERS_vSetCompareValue( TIMER0, L_u8Iteration ) ;
			_delay_ms(100);

		}


	}


}



//void TogglePinValue (void)
//{
//
//	MDIO_vTogglePinValue( MDIO_PORTB, MDIO_PIN0 ) ;
//
//	_delay_ms(100);
//
//}




#endif




#if ADC_MAPPING == RUN


int main(void)
{

	MADC_vInit();

	HLCD_vInit();

	u16 L_u16ADCValue = Initialized_by_Zero ;

	u32 ADC_Output = Initialized_by_Zero ;

	MDIO_vSetPortDirection( MDIO_PORTD, MDIO_OUTPUT ) ;

	while( TRUE )
	{

		L_u16ADCValue = MADC_u16ConvertAnalog_to_Digital( CHANNEL_00 ) ;

		ADC_Output = MDIO_u32MappingValue( L_u16ADCValue, Input_Min, Input_Max, Output_Min, Output_Max ) ;


		if( ADC_Output > 32 )  { MDIO_vSetPinValue( MDIO_PORTD, MDIO_PIN0, MDIO_PIN_HIGH ) ; }

		if( ADC_Output > 64 )  { MDIO_vSetPinValue( MDIO_PORTD, MDIO_PIN1, MDIO_PIN_HIGH ) ; }

		if( ADC_Output > 96 )  { MDIO_vSetPinValue( MDIO_PORTD, MDIO_PIN2, MDIO_PIN_HIGH ) ; }

		if( ADC_Output > 128 ) { MDIO_vSetPinValue( MDIO_PORTD, MDIO_PIN3, MDIO_PIN_HIGH ) ; }

		if( ADC_Output > 160 ) { MDIO_vSetPinValue( MDIO_PORTD, MDIO_PIN4, MDIO_PIN_HIGH ) ; }

		if( ADC_Output > 192 ) { MDIO_vSetPinValue( MDIO_PORTD, MDIO_PIN5, MDIO_PIN_HIGH ) ; }

		if( ADC_Output > 224 ) { MDIO_vSetPinValue( MDIO_PORTD, MDIO_PIN6, MDIO_PIN_HIGH ) ; }

		if( ADC_Output > 254 ) { MDIO_vSetPinValue( MDIO_PORTD, MDIO_PIN7, MDIO_PIN_HIGH ) ; }


		HLCD_vClear();

		HLCD_vDispNumber( L_u16ADCValue ) ;

		HLCD_vGoTo( HLCD_LINE2, HLCD_Square1 ) ;

		HLCD_vDispNumber( ADC_Output ) ;

		_delay_ms( 300 ) ;

	}




}


#endif






#if LDR_POLLING == RUN



int main(void)
{

	MADC_vInit();

	HLCD_vInit();

	u16 L_u16ADCValue = Initialized_by_Zero ;

	MDIO_vSetPinDirection( MDIO_PORTA, MDIO_PIN7, MDIO_OUTPUT ) ;

	while( TRUE )
	{

		L_u16ADCValue = MADC_u16ConvertAnalog_to_Digital( CHANNEL_00 ) ;

		if( L_u16ADCValue < Vavg )
		{

			MDIO_vSetPinValue( MDIO_PORTA, MDIO_PIN7, MDIO_PIN_HIGH ) ;

		}

		else{  MDIO_vSetPinValue( MDIO_PORTA, MDIO_PIN7, MDIO_PIN_LOW ) ;  }


		_delay_ms( 300 ) ;

		HLCD_vClear();

		HLCD_vDispNumber( L_u16ADCValue ) ;

		_delay_ms( 300 ) ;

	}


}


#endif





#if LM35_POLLING == RUN




int main(void)
{

	MADC_vInit();

	HLCD_vInit();

	while( TRUE )
	{

		u16 L_u16Temperature = HLM35_u16GetTemperature( CHANNEL_00, Vref, BitNums );

		_delay_ms( 300 ) ;

		HLCD_vClear();

		HLCD_vDispNumber( L_u16Temperature ) ;

		_delay_ms( 300 ) ;

	}


}


#endif





#if ADC_INTERRUPT == RUN


volatile u16 G_u16ADC_Data = Initialized_by_Zero ;

volatile u8 G_u8StartConversionFlag = Initialized_by_Zero ;

void ADC_APP (void) ;


int main(void)
{

	MADC_vSetCallBack( ADC_APP ) ;
	MADC_vInit();
	HLCD_vInit();

	//u16 L_u16ADCValue = Initialized_by_Zero ;

	MADC_vStartConversion( CHANNEL_01 ) ;

	MGIE_vEnableGlobalInterrupt( ) ;

	while( TRUE )
	{

		//L_u16ADCValue = MADC_u16ConvertAnalog_to_Digital( CHANNEL_00 ) ;
		if( G_u8StartConversionFlag == Flag_is_Set )
		{

			G_u8StartConversionFlag = Flag_is_Cleared ;

			HLCD_vClear();

			HLCD_vDispNumber( G_u16ADC_Data ) ;

			_delay_ms( 300 ) ;

		}

	}


}


//ADC_ISR
//{
//
//	 G_u16ADC_Data = MADC_GetADCData();
//
//}



void ADC_APP (void)
{

	 G_u16ADC_Data = MADC_GetADCData();

	 MADC_vStartConversion( CHANNEL_01 ) ;

	 G_u8StartConversionFlag = Flag_is_Set ;

}




#endif







#if Interrupt == RUN



//void TOGGLE ( void ) ;




int main(void)
{



	MDIO_vSetPinDirection( MDIO_PORTD, MDIO_PIN2, MDIO_INPUT ) ;

	MDIO_vSetPinValue( MDIO_PORTD, MDIO_PIN2, MDIO_PIN_HIGH ) ;

	MDIO_vSetPinDirection( MDIO_PORTA, MDIO_PIN0, MDIO_OUTPUT ) ;

//	MEXTI_vSetCallBack( INT0, &TOGGLE ) ;

	MEXTI_vEnableInterrupt( INT0 ) ;

	MEXTI_vSetSenseControl( INT0, EXTI_FallingEdge ) ;

	MGIE_vEnableGlobalInterrupt( ) ;



	while( TRUE )
	{




	}



}


ISR_INT0
{


	MDIO_vTogglePinValue( MDIO_PORTA, MDIO_PIN0 ) ;


}


//void TOGGLE ( void )
//{
//
//
//	MDIO_vTogglePinValue( MDIO_PORTA, MDIO_PIN0 ) ;
//
//
//}


#endif





#if DC_MOTOR == RUN


int main(void)
{


	MDIO_vSetPinDirection( MDIO_PORTD, MDIO_PIN2, MDIO_INPUT ) ;

	MDIO_vSetPinValue( MDIO_PORTD, MDIO_PIN2, MDIO_PIN_HIGH ) ;

	MEXTI_vEnableInterrupt( INT0 ) ;

	MEXTI_vSetSenseControl( INT0, EXTI_FallingEdge ) ;

	MGIE_vEnableGlobalInterrupt( ) ;


	while( TRUE )
	{

		HDCM_vRotateMotor ( MDIO_PORTA, MDIO_PIN0, MDIO_PIN2, CW ) 	 ;

		HDCM_vRotateMotor ( MDIO_PORTD, MDIO_PIN0, MDIO_PIN1, CCW  ) ;


	}



}




ISR_INT0
{


	HDCM_vStopMotor( MDIO_PORTD, MDIO_PIN0, MDIO_PIN2 );


	_delay_ms( 3000 ) ;

}




#endif







#if Stepper_Motor == RUN



int main(void)
{



	MDIO_vSetPortDirection	( MDIO_PORTA, MDIO_SET_NibbleLow ) ;



	u8 LR_u8Steps[4] = { 1, 2, 4, 8 };



	while( TRUE )
	{

		for( u8 L_u8J = 0 ; L_u8J < 16 ; L_u8J++ )
		{

			for( u8 L_u8I = 0 ; L_u8I < 4 ; L_u8I++ )
			{


				MDIO_vSetPortValue( MDIO_PORTA, LR_u8Steps[ L_u8I ] );

				_delay_ms( 100 ) ;


			}


		}


	}



}



#endif










#if MOVING_NAME == RUN





int main(void)
{


	s8 L_s8KeyValue = -1 			;

	s8 L_s8PositionX = HLCD_Square8 ;

	s8 L_s8PositionY = HLCD_LINE1	;

	u8 LR_u8Ali[] = { 0b00000100, 0b00000100, 0b00001101, 0b00010110, 0b00010111, 0b00010000, 0b00001000, 0b00000100 };

	HLCD_vInit    ( ) ;

	HKEYPAD_vInit ( ) ;


	HLCD_vSaveCustomChar( CGRAM_AddressOfPattern0, LR_u8Ali ) ;

	HLCD_vGoTo( L_s8PositionY, L_s8PositionX );

	HLCD_vSendData( CGRAM_AddressOfPattern0 ) ;


	while( TRUE )
	{



		// In case he passed the max number of columns --> return him to the first column.
		if( L_s8PositionX > MAX_IDX_OF_COL )
		{

			HLCD_vClear();

			L_s8PositionX = HLCD_Square1;

			 HLCD_vGoTo( L_s8PositionY, L_s8PositionX ); HLCD_vSendData( CGRAM_AddressOfPattern0 );

			L_s8KeyValue = -1 ;

			L_s8KeyValue = HKEYPAD_u8Getpressed( );

			if( L_s8KeyValue != -1)
			{

				switch( L_s8KeyValue )
				{

					case K2:  HLCD_vClear() ; HLCD_vGoTo( -- L_s8PositionY ,    L_s8PositionX  ); HLCD_vSendData( 0 ) ; break; // UP

					case K10: HLCD_vClear() ; HLCD_vGoTo( ++ L_s8PositionY ,    L_s8PositionX  ); HLCD_vSendData( 0 ) ; break; // DOWN

					case K7:  HLCD_vClear() ; HLCD_vGoTo(    L_s8PositionY , ++ L_s8PositionX  ); HLCD_vSendData( 0 ) ; break; // RIGHT

					case K5:  HLCD_vClear() ; HLCD_vGoTo(    L_s8PositionY , -- L_s8PositionX  ); HLCD_vSendData( 0 ) ; break; // LEFT

					default:  break;

				}

			}

		}



		// In case he passed the max number of rows --> return him to the first row.
		else if( L_s8PositionY > MAX_IDX_OF_ROWS )
		{

			HLCD_vClear();

			L_s8PositionY = HLCD_LINE1 ;

			 HLCD_vGoTo( L_s8PositionY, L_s8PositionX ); HLCD_vSendData( 0 );

			L_s8KeyValue = -1 ;

			L_s8KeyValue = HKEYPAD_u8Getpressed( );

			if( L_s8KeyValue != -1)
			{

				switch( L_s8KeyValue )
				{

					case K2:  HLCD_vClear() ; HLCD_vGoTo( -- L_s8PositionY ,    L_s8PositionX  ); HLCD_vSendData( CGRAM_AddressOfPattern0 ) ; break; // UP

					case K10: HLCD_vClear() ; HLCD_vGoTo( ++ L_s8PositionY ,    L_s8PositionX  ); HLCD_vSendData( CGRAM_AddressOfPattern0 ) ; break; // DOWN

					case K7:  HLCD_vClear() ; HLCD_vGoTo(    L_s8PositionY , ++ L_s8PositionX  ); HLCD_vSendData( CGRAM_AddressOfPattern0 ) ; break; // RIGHT

					case K5:  HLCD_vClear() ; HLCD_vGoTo(    L_s8PositionY , -- L_s8PositionX  ); HLCD_vSendData( CGRAM_AddressOfPattern0 ) ; break; // LEFT

					default:  break;

				}

			}


		}



		// In case he passed the minimum number of columns --> go to the last column.
		else if( L_s8PositionX < HLCD_Square1 )
		{

			HLCD_vClear();

			L_s8PositionX = HLCD_Square16;

			 HLCD_vGoTo( L_s8PositionY, L_s8PositionX ); HLCD_vSendData( CGRAM_AddressOfPattern0 );

			L_s8KeyValue = -1 ;

			L_s8KeyValue = HKEYPAD_u8Getpressed( );

			if( L_s8KeyValue != -1)
			{

				switch( L_s8KeyValue )
				{

					case K2:  HLCD_vClear() ; HLCD_vGoTo( -- L_s8PositionY ,    L_s8PositionX  ); HLCD_vSendData( CGRAM_AddressOfPattern0 ) ; break; // UP

					case K10: HLCD_vClear() ; HLCD_vGoTo( ++ L_s8PositionY ,    L_s8PositionX  ); HLCD_vSendData( CGRAM_AddressOfPattern0 ) ; break; // DOWN

					case K7:  HLCD_vClear() ; HLCD_vGoTo(    L_s8PositionY , ++ L_s8PositionX  ); HLCD_vSendData( CGRAM_AddressOfPattern0 ) ; break; // RIGHT

					case K5:  HLCD_vClear() ; HLCD_vGoTo(    L_s8PositionY , -- L_s8PositionX  ); HLCD_vSendData( CGRAM_AddressOfPattern0 ) ; break; // LEFT

					default:  break;

				}

			}


		}



		// In case he passed the minimum number of rows --> go to the second row.
		else if( L_s8PositionY < HLCD_LINE1 )
		{

			HLCD_vClear();

			L_s8PositionY = HLCD_LINE2 ;

			 HLCD_vGoTo( L_s8PositionY, L_s8PositionX ); HLCD_vSendData( CGRAM_AddressOfPattern0 );

			L_s8KeyValue = -1 ;

			L_s8KeyValue = HKEYPAD_u8Getpressed( );

			if( L_s8KeyValue != -1)
			{

				switch( L_s8KeyValue )
				{

					case K2:  HLCD_vClear() ; HLCD_vGoTo( -- L_s8PositionY ,    L_s8PositionX  ); HLCD_vSendData( CGRAM_AddressOfPattern0 ) ; break; // UP

					case K10: HLCD_vClear() ; HLCD_vGoTo( ++ L_s8PositionY ,    L_s8PositionX  ); HLCD_vSendData( CGRAM_AddressOfPattern0 ) ; break; // DOWN

					case K7:  HLCD_vClear() ; HLCD_vGoTo(    L_s8PositionY , ++ L_s8PositionX  ); HLCD_vSendData( CGRAM_AddressOfPattern0 ) ; break; // RIGHT

					case K5:  HLCD_vClear() ; HLCD_vGoTo(    L_s8PositionY , -- L_s8PositionX  ); HLCD_vSendData( CGRAM_AddressOfPattern0 ) ; break; // LEFT

					default:  break;

				}

			}

		}



		else
		{

			HLCD_vGoTo( L_s8PositionY, L_s8PositionX ); HLCD_vSendData( CGRAM_AddressOfPattern0 );

			L_s8KeyValue = -1 ;

			L_s8KeyValue = HKEYPAD_u8Getpressed( );

			if( L_s8KeyValue != -1)
			{


				switch( L_s8KeyValue )
				{



					case K2:  HLCD_vClear() ; HLCD_vGoTo( -- L_s8PositionY ,    L_s8PositionX  ); HLCD_vSendData( CGRAM_AddressOfPattern0 ) ; break; // UP

					case K10: HLCD_vClear() ; HLCD_vGoTo( ++ L_s8PositionY ,    L_s8PositionX  ); HLCD_vSendData( CGRAM_AddressOfPattern0 ) ; break; // DOWN

					case K7:  HLCD_vClear() ; HLCD_vGoTo(    L_s8PositionY , ++ L_s8PositionX  ); HLCD_vSendData( CGRAM_AddressOfPattern0 ) ; break; // RIGHT

					case K5:  HLCD_vClear() ; HLCD_vGoTo(    L_s8PositionY , -- L_s8PositionX  ); HLCD_vSendData( CGRAM_AddressOfPattern0 ) ; break; // LEFT

					default:  break;


				}


			}


		}




	} // while( TRUE )





} // main





#endif















#if LCD == RUN



int main(void)
{


	HLCD_vInit() ;

	//HLCD_vDispCursorWithBlinking() ;




	while( TRUE )
	{




		HLCD_vDispString( "Name: " ) ;

		_delay_ms(700) ;

		HLCD_vSetCursor( HLCD_LINE2, HLCD_Square1 );

		HLCD_vDispShiftLeftString( "Ali El-bana" ) ;

		_delay_ms(1000) ;

		HLCD_vClear() ;



		HLCD_vDispString( "age: " ) ;

		_delay_ms(700) ;

		HLCD_vSetCursor( HLCD_LINE2, HLCD_Square1 );

		HLCD_vDispShiftLeftString( "22 years old" ) ;

		_delay_ms(1000) ;

		HLCD_vClear() ;



		HLCD_vDispString( "University: " ) ;

		_delay_ms(700) ;

		HLCD_vSetCursor( HLCD_LINE2, HLCD_Square1 );

		HLCD_vDispShiftLeftString( "Zagazig university" ) ;

		_delay_ms(1000) ;

		HLCD_vClear() ;



		HLCD_vDispString( "Field of study: " ) ;

		_delay_ms(700) ;

		HLCD_vSetCursor( HLCD_LINE2, HLCD_Square1 );

		HLCD_vDispShiftLeftString( "Mechatronics Engineering" ) ;

		_delay_ms(1000) ;

		HLCD_vClear() ;



		HLCD_vDispString( "Specified in: " ) ;

		_delay_ms(700) ;

		HLCD_vSetCursor( HLCD_LINE2, HLCD_Square1 );

		HLCD_vDispShiftLeftString( "Embedded Software Engineering" ) ;

		_delay_ms(1000) ;

		HLCD_vClear() ;


		HLCD_vSetDispOFF();




	}





}















//
//	HLCD_vInit() ;
//
//
//
//
//	u8 heart[]=
//	{
//
//		0b00000000,
//		0b00001010,
//		0b00011111,
//		0b00011111,
//		0b00001110,
//		0b00000100,
//		0b00000000,
//		0b00000000
//
//	};
//
//
//
//	 HLCD_vSaveCustomChar( 0, heart ) ;
//
//
//	static u8 manup[]=
//	{
//
//	 	0b00000100,
//	 	0b00000000,
//	 	0b00001010,
//	 	0b00000001,
//	 	0b00000110,
//	 	0b00001100,
//	 	0b00010100,
//		0b00000100
//
//	 };
//
//
//
//	 HLCD_vSaveCustomChar( 1, manup ) ;
//
//
//	static u8 mandwn[]=
//	{
//
//		0b00000100,
//		0b00000100,
//		0b00000100,
//		0b00000100,
//		0b00001010,
//		0b00001010,
//		0b00010001,
//		0b00000000
//
//	};
//
//
//	HLCD_vSaveCustomChar( 2, mandwn ) ;
//
//
//
//	static	u8 wup[]=
//	{
//
//		0b00000100,
//		0b00001010,
//		0b00011011,
//		0b00010101,
//		0b00000100,
//		0b00001110,
//		0b00010101,
//		0b00000100
//
//	};
//
//
//	HLCD_vSaveCustomChar( 3, wup ) ;
//
//
//
//
//	static u8 wfalup[]=
//	{
//
//	   0b00000000,
//	   0b00000000,
//	   0b00001000,
//	   0b00000100,
//	   0b00001110,
//	   0b00001010,
//	   0b00001110,
//	   0b00010001
//
//	};
//
//
//	HLCD_vSaveCustomChar( 5, wfalup ) ;
//
//
//	static u8 wfaldwn[]=
//	{
//
//		0b00000001,
//		0b00000010,
//		0b00011100,
//		0b00000100,
//		0b00001000,
//		0b00000000,
//		0b00000000,
//		0b00000000
//
//
//	};
//
//
//	HLCD_vSaveCustomChar( 6, wfaldwn ) ;
//
//
//
//	static u8 wdedup[]=
//	{
//
//		0b00000000,
//		0b00000000,
//		0b00010000,
//		0b00001000,
//		0b00000110,
//		0b00011001,
//		0b00000110,
//		0b00011000
//
//
//	};
//
//
//	HLCD_vSaveCustomChar( 4, wdedup ) ;
//
//
//	static	u8 wdedwn[]=
//	{
//
//		0b00000000,
//		0b00000000,
//		0b00000000,
//		0b00000000,
//		0b00011000,
//		0b00000111,
//		0b00011000,
//
//
//	};
//
//
//	HLCD_vSaveCustomChar( 7, wdedwn ) ;




//	u8 aeen[]=
//	{
//
//		0b00000110,
//		0b00001000,
//		0b00001000,
//		0b00000110,
//		0b00001000,
//		0b00001000,
//		0b00000111,
//		0b00000000
//
//	};
//
//	HLCD_vSaveCustomChar(1,aeen);
//
//
//	u8 lam[]=
//	{
//
//		0b00000000,
//		0b00000100,
//		0b00000100,
//		0b00000100,
//		0b00010100,
//		0b00010100,
//		0b00011000,
//		0b00000000
//
//	};
//
//	HLCD_vSaveCustomChar(2,lam);
//
//
//	u8 ya2[]=
//	{
//
//		0b00000000,
//		0b00000010,
//		0b00000101,
//		0b00010100,
//		0b00010010,
//		0b00010010,
//		0b00001100,
//		0b00000000
//
//	};
//
//	HLCD_vSaveCustomChar(3,ya2);
//
//
//	u8 ali[]=
//	{
//
//		0b00000100,
//		0b00000100,
//		0b00001101,
//		0b00010110,
//		0b00010111,
//		0b00010000,
//		0b00001000,
//		0b00000100
//
//	};
//
//	HLCD_vSaveCustomChar(4,ali);








//	vLCD_Init();
//
//	u8 heart[]=
//	{
//
//		0b00000000,
//		0b00001010,
//		0b00011111,
//		0b00011111,
//		0b00001110,
//		0b00000100,
//		0b00000000,
//		0b00000000
//
//	};
//
//	HLCD_vSaveCustomChar(0,heart);
//
//	for(int y=0;y<2;y++)
//	{
//		for(int x=0;x<16;x++)
//		{
//
//			HLCD_vSetCursor(x,y);
//			HLCD_vSendData(0);
//			HLCD_vClear();
//
//		}
//
//
//	}








//	vLCD_Init();
//
//
//	u8 heart[]=
//	{
//
//		0b00000000,
//		0b00001010,
//		0b00011111,
//		0b00011111,
//		0b00001110,
//		0b00000100,
//		0b00000000,
//		0b00000000
//	};
//
//	HLCD_vSaveCustomChar(0,heart);
//
//	HLCD_vSendData(0);





//	while( TRUE )
//	{
//
//
//		u8 x;
//
//		for( x = 3 ; x <11 ; x++ )
//		{
//
//
//			HLCD_vSetCursor( 2, 0 ) ;
//			HLCD_vSendData( 1 ) ;
//
//			HLCD_vSetCursor( 2, 1 ) ;
//			HLCD_vSendData( 2 ) ;
//
//			HLCD_vSetCursor( 11, 0 ) ;
//			HLCD_vSendData( 3 ) ;
//
//			HLCD_vSetCursor( 11, 1 ) ;
//			HLCD_vSendData( 2 ) ;
//
//			_delay_ms(250);
//
//			HLCD_vSetCursor( x, 0 ) ;
//			HLCD_vSendData( 0 ) ;
//
//			_delay_ms(250);
//
//
//
//		}
//
//
//
//		HLCD_vClear();
//
//
//
//		HLCD_vSetCursor(12,0);
//		HLCD_vSendData(5);
//
//		HLCD_vSetCursor(11,1);
//		HLCD_vSendData(6);
//
//		_delay_ms(1000);
//
//		HLCD_vClear();
//
//		HLCD_vSetCursor(12,1);
//		HLCD_vSendData(4);
//
//		HLCD_vSetCursor(11,1);
//		HLCD_vSendData(7);
//
//		_delay_ms(1000);
//
//		HLCD_vClear();
//		HLCD_vDispString( "SHE PASSED AWAY" ) ;
//
//		_delay_ms(1000);
//
//		HLCD_vClear();
//
//		_delay_ms(900);
//
//
//
//
//
//
//
//
//
////		int x,y;
////
////
////
////		for( x=0 ; x<16 ; x++ )
////		{
////
////
////			x--;
////
////
////
////			for(y=0;y<2;y++)
////			{
////
////
////
////
////				HLCD_vSetCursor(x,y);
////
////
////
////				HLCD_vSendData(4);
////
////
////				_delay_ms(250);
////
////
////				x++;
////
////
////			}
////
////
////
////		}
////
////		HLCD_vClear();
////
//
//	}
//
//




#endif





















#if KEYPAD == RUN


int main (void)
{



	HKEYPAD_vInit() ;


	u8 L_u8KeyValue = Initialized_by_Zero ;



	while( TRUE )
	{


	    L_u8KeyValue = HKEYPAD_u8Getpressed() ;


	    if( 0 != L_u8KeyValue )
	    {


	    	switch( L_u8KeyValue )
	    	{



				case K1:  HSSD_vDispNum( MDIO_PORTA, NUM_ZERO ); HSSD_vDispNum( MDIO_PORTB, NUM_ONE   );  break; //01

				case K2:  HSSD_vDispNum( MDIO_PORTA, NUM_ZERO ); HSSD_vDispNum( MDIO_PORTB, NUM_TWO   );  break; //02

				case K3:  HSSD_vDispNum( MDIO_PORTA, NUM_ZERO ); HSSD_vDispNum( MDIO_PORTB, NUM_THREE );  break; //03

				case K4:  HSSD_vDispNum( MDIO_PORTA, NUM_ZERO ); HSSD_vDispNum( MDIO_PORTB, NUM_FOUR  );  break; //04

				case K5:  HSSD_vDispNum( MDIO_PORTA, NUM_ZERO ); HSSD_vDispNum( MDIO_PORTB, NUM_FIVE  );  break; //05

				case K6:  HSSD_vDispNum( MDIO_PORTA, NUM_ZERO ); HSSD_vDispNum( MDIO_PORTB, NUM_SIX   );  break; //06

				case K7:  HSSD_vDispNum( MDIO_PORTA, NUM_ZERO ); HSSD_vDispNum( MDIO_PORTB, NUM_SEVEN );  break; //07

				case K8:  HSSD_vDispNum( MDIO_PORTA, NUM_ZERO ); HSSD_vDispNum( MDIO_PORTB, NUM_EIGHT );  break; //08

				case K9:  HSSD_vDispNum( MDIO_PORTA, NUM_ZERO ); HSSD_vDispNum( MDIO_PORTB, NUM_NINE  );  break; //09

				case K10: HSSD_vDispNum( MDIO_PORTA, NUM_ONE  ); HSSD_vDispNum( MDIO_PORTB, NUM_ZERO  );  break; //10

				case K11: HSSD_vDispNum( MDIO_PORTA, NUM_ONE  ); HSSD_vDispNum( MDIO_PORTB, NUM_ONE   );  break; //11

				case K12: HSSD_vDispNum( MDIO_PORTA, NUM_ONE  ); HSSD_vDispNum( MDIO_PORTB, NUM_TWO   );  break; //12

				case K13: HSSD_vDispNum( MDIO_PORTA, NUM_ONE  ); HSSD_vDispNum( MDIO_PORTB, NUM_THREE );  break; //13

				case K14: HSSD_vDispNum( MDIO_PORTA, NUM_ONE  ); HSSD_vDispNum( MDIO_PORTB, NUM_FOUR  );  break; //14

				case K15: HSSD_vDispNum( MDIO_PORTA, NUM_ONE  ); HSSD_vDispNum( MDIO_PORTB, NUM_FIVE  );  break; //15

				case K16: HSSD_vDispNum( MDIO_PORTA, NUM_ONE  ); HSSD_vDispNum( MDIO_PORTB, NUM_SIX   );  break; //16



	    	}





	    }





	}









}


#endif
