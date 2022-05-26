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




#define FIRST_ROW_IDX   			0

#define FIRST_ROW_START 			0x00

#define SEC_ROW_START   			0x40

#define SET_DDRAM_AC_MASK   		0x80

#define SET_CGRAM_AC_MASK			0x40

#define NumOf_CGRAM_Patterns 		8

#define FirstByteInCGRAM_Pattern	0

#define LastByteInCGRAM_Pattern		8





#endif /* LCD_LCD_CONFIG_H_ */
