/* FILENAME: MTimers_private  
*  Author:  Ali El Bana
*  Version:  V1.0
*  DATE:   Fri 07/22/2022
*/
#ifndef _MTimers_private_H
#define _MTimers_private_H


/*****************************_TIMER0 Registers_*******************************************/


#define TCCR0 *( (volatile u8*) (0x53) )

#define TCCR0_FOC0  7
#define TCCR0_WGM00 6
#define TCCR0_COM01 5
#define TCCR0_COM00 4
#define TCCR0_WGM01 3
#define TCCR0_CS02  2
#define TCCR0_CS01  1
#define TCCR0_CS00  0


#define TCNT0 *( (volatile u8*) (0x52) )


#define TIMSK *( (volatile u8*) (0x59) )

#define TIMSK_OCIE2	 7
#define TIMSK_TOIE2	 6
#define TIMSK_TICIE1 5 // Bit 5 – TICIE1: Timer/Counter1, Input Capture Interrupt Enable.
#define TIMSK_OCIE1A 4
#define TIMSK_OCIE1B 3
#define TIMSK_TOIE1	 2
#define TIMSK_OCIE0  1
#define TIMSK_TOIE0  0


#define OCR0 *( (volatile u8*) (0x5C) )

#define TIFR *( (volatile u8*) (0x58) )

#define TIFR_OCF0  1
#define TIFR_TOV0  0


#define SFIOR *( (volatile u8*) (0x50) )

#define SFIOR_PSR10  0



#define TIMER0_NORMAL_MODE 		1
#define TIMER0_PWM_PhaseCorrect 2
#define TIMER0_CTC 				3
#define TIMER0_FastPWM 			4


#define TIMER0_COMP_NonPWM  		1
#define TIMER0_COMP_FastPWM         2
#define TIMER0_COMP_PhaseCorrectPWM 3


#define TIMER0_NORMAL_MODE  1
#define TIMER0_ToggleOnCOMP 2
#define TIMER0_ClearOnCOMP  3
#define TIMER0_SetOnCOMP    4


#define NoClockSource 				1
#define NoPrescaling 				2
#define DivisionBy_8prescaler 		3
#define DivisionBy_64prescaler  	4
#define DivisionBy_256prescaler 	5
#define DivisionBy_1024prescaler  	6
#define ExtClk_FallingEdge  		7
#define ExtClk_RisingEdge  			8

#define TIMER0_ISR_OVF 0
#define TIMER0_ISR_CTC 1


#define TIMER0_OVF_ISR 	void __vector_11(void) __attribute__((signal));\
						void __vector_11(void)


#define TIMER0_COMP_ISR void __vector_10(void) __attribute__((signal));\
						void __vector_10(void)



/*****************************_TIMER1 Registers_*******************************************/


#define TCCR1A				*( (volatile u8*)    (0x4F))

#define TCCR1A_COM1A1		7
#define TCCR1A_COM1A0		6
#define TCCR1A_COM1B1		5
#define TCCR1A_COM1B0		4
#define TCCR1A_FOC1A		3
#define TCCR1A_FOC1B		2
#define TCCR1A_WGM11		1
#define TCCR1A_WGM10		0


#define TCCR1B				*( (volatile u8*)    (0x4E))

#define TCCR1B_ICNC1		7
#define TCCR1B_ICES1		6
#define TCCR1B_WGM13		4
#define TCCR1B_WGM12		3
#define TCCR1B_CS12			2
#define TCCR1B_CS11			1
#define TCCR1B_CS10			0


#define TCNT1				*( (volatile u16*)   (0x4C))
#define OCR1A				*( (volatile u16*)   (0x4A))
#define OCR1B				*( (volatile u16*)   (0x48))
#define ICR1				*( (volatile u16*)   (0x46))


#define TIMER1_NORMAL_MODE	1
#define TIMER1_ToggleOnCOMP	2
#define TIMER1_ClearOnCOMP	3
#define TIMER1_SetOnCOMP	4


#define TIMER1_COMP_NonPWM			1
#define TIMER1_COMP_FastPWM			2
#define TIMER1_COMP_PhaseCorrectPWM	3


#define TIMER1_Normal                    				1
#define TIMER1_PWM_PHASE_CORRECT_8_bit                  2
#define TIMER1_PWM_PHASE_CORRECT_9_bit                  3
#define TIMER1_PWM_PHASE_CORRECT_10_bit                 4
#define TIMER1_CTC_OCR1A                                5
#define TIMER1_Fast_PWM_8_bit                           6
#define TIMER1_Fast_PWM_9_bit                           7
#define TIMER1_Fast_PWM_10_bit                          8
#define TIMER1_PWM_Phase_and_Frequency_Correct_ICR1     9
#define TIMER1_PWM_Phase_and_Frequency_Correct_OCR1A    10
#define TIMER1_PWM_Phase_Correct_ICR1                   11
#define TIMER1_PWM_Phase_Correct_OCR1A                  12
#define TIMER1_CTC_ICR1                                 13
#define TIMER1_Fast_PWM_ICR1                            14
#define TIMER1_Fast_PWM_OCR1A                           15


#define SET_ON_ICR1  1
#define SET_ON_OCR1A 2

#define Register_1A  1
#define Register_1B  2

#define TIMER1_ISR_ICU 		0
#define TIMER1_ISR_CTC1A	1
#define TIMER1_ISR_CTC1B	2
#define TIMER1_ISR_OVF		3


#define ICU_Rising_Edge  1
#define ICU_Falling_Edge 2


#define ENABLE  1
#define DISABLE 2



#define TIMER1_CAPT_ISR 	void __vector_6(void) __attribute__((signal));\
							void __vector_6(void)

#define TIMER1_COMPA_ISR 	void __vector_7(void) __attribute__((signal));\
							void __vector_7(void)

#define TIMER1_COMPB_ISR 	void __vector_8(void) __attribute__((signal));\
							void __vector_8(void)

#define TIMER1_OVF_ISR 		void __vector_9(void) __attribute__((signal));\
							void __vector_9(void)



/*****************************_TIMER2 Registers_*******************************************/



#define TCNT2 *( (volatile u8*) (0x44) )


#define TCCR2 *( (volatile u8*) (0x45) )

#define TCCR2_CS20  0
#define TCCR2_CS21  1
#define TCCR2_CS22  2
#define TCCR2_WGM21 3
#define TCCR2_COM20 4
#define TCCR2_COM21 5
#define TCCR2_WGM20 6
#define TCCR2_FOC2  7



#define ASSR *( (volatile u8*) (0x42) )

#define ASSR_TCR2UB  0
#define ASSR_OCR2UB  1
#define ASSR_TCN2UB  2
#define ASSR_AS2 	 3




#define OCR2 *( (volatile u8*) (0x43) )







#define TIMER2_NORMAL_MODE 		1
#define TIMER2_PWM_PhaseCorrect 2
#define TIMER2_CTC 				3
#define TIMER2_FastPWM 			4


#define TIMER2_COMP_NonPWM  		1
#define TIMER2_COMP_FastPWM         2
#define TIMER2_COMP_PhaseCorrectPWM 3


#define TIMER2_NORMAL_MODE  1
#define TIMER2_ToggleOnCOMP 2
#define TIMER2_ClearOnCOMP  3
#define TIMER2_SetOnCOMP    4





#define TIMER2_ISR_OVF 0
#define TIMER2_ISR_CTC 1






#define TIMER2_COMP_ISR void __vector_4(void) __attribute__((signal));\
						void __vector_4(void)

#define TIMER2_OVF_ISR 	void __vector_5(void) __attribute__((signal));\
						void __vector_5(void)















#endif //_MTimers_private_H
