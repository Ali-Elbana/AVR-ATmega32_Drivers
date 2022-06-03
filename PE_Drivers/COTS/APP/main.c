/*
 * main.c
 *
 *  Created on: May 18, 2022
 *      Author: Ali El-bana
 */

#include "../LIB/LBITMATH.h"
#include "../LIB/LSTD_TYPES.h"

#include "../MCAL/MDIO/MDIO_inter.h"
#include "../HAL/HSSD/HSSD_inter.h"
#include "../HAL/HKEYPAD/HKEYPAD_inter.h"
#include "../HAL/HLCD/HLCD_inter.h"
#include "../HAL/HDCM/HDCM_interface.h"

#include "util/delay.h"


#define KEYPAD 			STOP

#define LCD				STOP

#define MOVING_NAME 	STOP

#define Stepper_Motor 	STOP

#define DC_MOTOR 		RUN






#if DC_MOTOR == RUN


int main(void)
{




	while( TRUE )
	{

		HDCM_vRotateMotor ( MDIO_PORTA, MDIO_PIN0, MDIO_PIN2, CW ) 	 ;

		HDCM_vRotateMotor ( MDIO_PORTD, MDIO_PIN0, MDIO_PIN2, CCW  ) ;

	}



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

				_delay_ms( 3 ) ;


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
