/*
 * LCD_config.h
 *
 *  Created on: Sep 11, 2021
 *      Author: Ali El Bana
 */

#ifndef LCD_LCD_CONFIG_H_
#define LCD_LCD_CONFIG_H_

#include "../../HAL/HLCD/HLCD_private.h"



#define HLCD_DATA_PORT	MDIO_PORTC

#define HLCD_CTRL_PORT 	MDIO_PORTB

#define HLCD_RS_PIN   	MDIO_PIN0

#define HLCD_RW_PIN 	MDIO_PIN1

#define HLCD_EN_PIN 	MDIO_PIN2





#define HLCD_FuctionSet_Cmd 				FuctionSetCmd

#define HLCD_DispOnOffCTRL_Cmd 				DispOnOffCTRLCmd

#define HLCD_DispOff_Cmd					DispOffCmd

#define HLCD_DispCursorWithBlinking_Cmd 	DispCursorWithBlinkingCmd

#define HLCD_SetCursorBlinkingOFF_Cmd 		SetCursorBlinkingOFFCmd

#define HLCD_DispClear_Cmd  				DispClearCmd

#define HLCD_EntryModeSet_Cmd				EntryModeSet_Cmd

#define HLCD_EntryModeSet_ShiftLeftOn_Cmd	EntryModeSet_ShiftLeftOn_Cmd



#define HLCD_CharactersNums 	16









#endif /* LCD_LCD_CONFIG_H_ */
