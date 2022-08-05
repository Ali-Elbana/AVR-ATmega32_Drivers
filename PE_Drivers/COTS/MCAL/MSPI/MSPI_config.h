/* FILENAME: MSPI_config  
*  Author:  Ali El Bana
*  Version:  V1.0
*  DATE:   Wed 08/03/2022
*/
#ifndef _MSPI_config_H
#define _MSPI_config_H





/**********************************************************************************/

/*options:
 *ENABLE
 *DISABLE
 */
#define SPI_Interrupt_Mode DISABLE

/**********************************************************************************/

/*options:
 *LSB_Transmitted_First
 *MSB_Transmitted_First
 */
#define Data_Order_Direction MSB_Transmitted_First

/**********************************************************************************/

/*options:
 *Master_SPI_Mode
 *Slave_SPI_Mode
 */
#define Master_Slave_Select Master_SPI_Mode

/**********************************************************************************/
//
///*options:
// *Rising_Leading_Edge
// *Falling_Leading_Edge
// */
//#define CLK_Polarity_Option Rising_Leading_Edge
//
///**********************************************************************************/
//
///*options:
// *Sample_Leading_Edge
// *Setup_Leading_Edge
// */
//#define CLK_Phase_Option Sample_Leading_Edge

/**********************************************************************************/

/*options:
 *Fosc_Dividedby_4
 *Fosc_Dividedby_16
 *Fosc_Dividedby_64
 *Fosc_Dividedby_128
 *Fosc_Dividedby_2
 *Fosc_Dividedby_8
 *Fosc_Dividedby_32
 *Fosc2_Dividedby_64
 */
#define SPI_CLK_Rate Fosc_Dividedby_64

/**********************************************************************************/

/*options:
 *Sample_Rising_Leading
 *Setup_Rising_Leading
 *Sample_Falling_Leading
 *Setup_Falling_Leading
 */
#define SPI_MODE Setup_Falling_Leading

/**********************************************************************************/

/*options:
 *ENABLE
 *DISABLE
 */
#define Write_Collision_Flag DISABLE

/**********************************************************************************/

#define SPI_PORT 	MDIO_PORTB
#define SS_PIN		MDIO_PIN4
#define MOSI_PIN 	MDIO_PIN5
#define MISO_PIN 	MDIO_PIN6
#define SCK_PIN 	MDIO_PIN7























#endif //_MSPI_config_H
