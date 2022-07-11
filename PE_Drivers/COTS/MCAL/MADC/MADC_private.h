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




#define ADCH	*( (volatile u8*)(0x25) )

#define ADCL	*( (volatile u8*)(0x24) )

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


#define SFIOR	*( (volatile u8*)(0x24) )

#define ADTS0  5
#define ADTS1  6
#define ADTS2  7


#define ADC 	*( (volatile u16*)( (0x04) + 0x20) )



#define PrescalerMode_64 0b110




#endif //_MADC_private_H
