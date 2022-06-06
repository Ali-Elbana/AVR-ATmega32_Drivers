/* FILENAME: MEXTI_private  
*  Author:  Ali El Bana
*  Version:  V1.0
*  DATE:   Sat 06/04/2022
*/
#ifndef _MEXTI_private_H
#define _MEXTI_private_H




#define MCUCR   *((volatile u8*)(0x55))

#define MCUCR_ISC00  0
#define MCUCR_ISC01  1
#define MCUCR_ISC10  2
#define MCUCR_ISC11  3



#define MCUCSR  *((volatile u8*)(0x54))

#define MCUCSR_ISC2   6



#define GICR    *((volatile u8*)(0x5B))

#define GICR_INT0   6
#define GICR_INT1   7
#define GICR_INT2   5



#define GIFR    *((volatile u8*)(0x5A))

#define GIFR_INTF0  6
#define GIFR_INTF1  7
#define GIFR_INTF2  5





#define INT0_VectorNum 	void __vector_1 (void) __attribute__((signal)) ; void __vector_1 (void)

#define INT1_VectorNum 	void __vector_2 (void) __attribute__((signal)) ; void __vector_2 (void)

#define INT2_VectorNum 	void __vector_3 (void) __attribute__((signal)) ; void __vector_3 (void)









#endif //_MEXTI_private_H
