/* FILENAME: MADC_private  
*  Author:  Ali El Bana
*  Version:  V1.0
*  DATE:   Sun 07/10/2022
*/
#ifndef _MADC_private_H
#define _MADC_private_H


#define ADMUX   *( (volatile u8*)(0x27) )

#define ADMUX_MUX0   0
#define ADMUX_MUX1   1
#define ADMUX_MUX2   2
#define ADMUX_MUX3   3
#define ADMUX_MUX4   4
#define ADMUX_ADLAR  5
#define ADMUX_REFS0  6
#define ADMUX_REFS1  7




#define ADCSRA   *( (volatile u8*)(0x26) )

#define ADCSRA_ADPS0  0
#define ADCSRA_ADPS1  1
#define ADCSRA_ADPS2  2
#define ADCSRA_ADIE   3
#define ADCSRA_ADIF   4
#define ADCSRA_ADATE  5
#define ADCSRA_ADSC	  6
#define ADCSRA_ADEN   7



#define ADCL	*( (volatile u8*)(0x24) )
#define ADCH	*( (volatile u8*)(0x25) )

#define ADC0  0
#define ADC1  1
#define ADC2  2
#define ADC3  3
#define ADC4  4
#define ADC5  5
#define ADC6  6
#define ADC7  7
#define ADC8  8
#define ADC9  9


#define SFIOR	*( (volatile u8*)(0x50) )

#define ADTS0  5
#define ADTS1  6
#define ADTS2  7


#define ADC_Data *( (volatile u16*)(0x24) )



#define AVCC 			1
#define AREF 			2
#define Internal_Volt 	3


#define RIGHT_Adjust	1
#define LEFT_Adjust		2

#define Prescaler_Bit_Manipulation 			0xF8
#define AutoTrigger_Bit_Manipulation 		0X1F
#define ChannelSelectionBits_Manipulation 	0xE0
#define ChannelNumBits_Manipulation 		0x1F

#define PrescalerMode_2   0b000
#define PrescalerMode_4   0b010
#define PrescalerMode_8   0b011
#define PrescalerMode_16  0b100
#define PrescalerMode_32  0b101
#define PrescalerMode_64  0b110
#define PrescalerMode_128 0b111


#define ENABLE 	1
#define DISABLE 2


#define FreeRunningMode				0b000
#define AnalogComparator			0b001
#define External_InterruptRequest0	0b010
#define TimerCounter0_CompareMatch	0b011
#define TimerCounter0_Overflow		0b100
#define TimerCounterCompare_MatchB	0b101
#define TimerCounter1_Overflow		0b110
#define TimerCounter1_CaptureEvent	0b111


#define ADC_VectorNum void __vector_16(void) __attribute__((signal)); void __vector_16(void)



#endif //_MADC_private_H
