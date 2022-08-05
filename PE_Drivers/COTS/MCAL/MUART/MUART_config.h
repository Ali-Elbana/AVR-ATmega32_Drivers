/* FILENAME: MUART_config  
*  Author:  Ali El Bana
*  Version:  V1.0
*  DATE:   Mon 08/01/2022
*/
#ifndef _MUART_config_H
#define _MUART_config_H



/**********************************************************************************/

/*options:
 *Asynchronous_Operation
 *Synchronous_Operation
 */
#define USART_Mode_Select Asynchronous_Operation

/**********************************************************************************/

/*options:
 *Parity_Disabled
 *Enabled_EvenParity
 *Enabled_OddParity
 */
#define Parity_Mode Parity_Disabled

/**********************************************************************************/

/*options:
 *One_StopBit
 *Two_StopBits
 */
#define Stop_Bit_Select One_StopBit

/**********************************************************************************/

/*options:
 *CharacterSize_5bits
 *CharacterSize_6bits
 *CharacterSize_7bits
 *CharacterSize_8bits
 *CharacterSize_9bits
 */
#define Data_Character_Size CharacterSize_8bits

/**********************************************************************************/

/*options:
 *RisingTx_FallingRx
 *FallingTx_RisingRx
 */
#define Clock_Polarity_Status RisingTx_FallingRx

/**********************************************************************************/

/*options:
 *BaudRate_2400
 *BaudRate_4800
 *BaudRate_9600
 *BaudRate_14k
 *BaudRate_19k
 *BaudRate_28k
 *BaudRate_38k
 *BaudRate_57k
 *BaudRate_76k
 *BaudRate_115k
 *BaudRate_230k
 *BaudRate_250k
 *BaudRate_HalfM
 */
#define BaudRate_Options BaudRate_9600

/**********************************************************************************/

/*options:
 *ENABLE
 *DISABLE
 */
#define RX_Interrupt_Mode DISABLE

/**********************************************************************************/

/*options:
 *ENABLE
 *DISABLE
 */
#define TX_Interrupt_Mode DISABLE

/**********************************************************************************/

/*options:
 *ENABLE
 *DISABLE
 */
#define DataRegister_Interrupt_Mode DISABLE

/**********************************************************************************/







#endif //_MUART_config_H
