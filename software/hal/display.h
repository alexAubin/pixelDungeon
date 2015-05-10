/*
 ##############################################################################
 #                                                                            #
 #    This file is part of PixelDungeon.                                      #
 #                                                                            #
 #    PixelDungeon is free software: you can redistribute it and/or modify    #
 #    it under the terms of the GNU General Public License as published by    #
 #    the Free Software Foundation, either version 3 of the License, or       #
 #     (at your option) any later version.                                    #
 #                                                                            #
 #    PixelDungeon is distributed in the hope that it will be useful,         #
 #    but WITHOUT ANY WARRANTY; without even the implied warranty of          #
 #    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           #
 #    GNU General Public License for more details.                            #
 #                                                                            #
 #    You should have received a copy of the GNU General Public License       #
 #    along with PixelDungeon.  If not, see <http://www.gnu.org/licenses/>.   #
 #                                                                            #
 ##############################################################################
*/

/**
 *	@author Alexandre Aubin
 *  @brief Display-related definitions
*/

#ifndef HAL_DISPLAY_H_
#define HAL_DISPLAY_H_

#include "common.h"

// *********************************************************************
//                         Misc
// *********************************************************************

#define DISPLAY_WIDTH 8
#define DISPLAY_NPIX DISPLAY_WIDTH*DISPLAY_WIDTH
#define DISPLAY_PIXEL(x,y) ((y) + DISPLAY_WIDTH * (x))

// *********************************************************************
//                         Colors
// *********************************************************************

#define DISPLAYCOLOR_EMPTY      0b000000
#define DISPLAYCOLOR_WHITE      0b101110
#define DISPLAYCOLOR_RED        0b110000
#define DISPLAYCOLOR_GREEN      0b001100
#define DISPLAYCOLOR_BLUE       0b000011
#define DISPLAYCOLOR_YELLOW     0b111100
#define DISPLAYCOLOR_MAGENTA    0b110011
#define DISPLAYCOLOR_CYAN       0b001110
#define DISPLAYCOLOR_ORANGE     0b110100
#define DISPLAYCOLOR_VIOLET     0b110010
#define DISPLAYCOLOR_KINGBLUE   0b001111
#define DISPLAYCOLOR_LIGHTGREEN 0b011100
#define DISPLAYCOLOR_RED_HIGH   0b100000
#define DISPLAYCOLOR_RED_MEDIUM 0b010000
#define DISPLAYCOLOR_RED_LOW    0b010100

// *********************************************************************
//                         IO config (pin numbers)
// *********************************************************************

#define HAL_ANODE_INPUT_PIN  A0
#define HAL_ANODE_SHIFT_PIN  A1
#define HAL_ANODE_UPDATE_PIN A2
#define HAL_COLOR_SHIFT_PIN  A3
#define HAL_COLOR_UPDATE_PIN A4

#define HAL_RED_INPUT_PIN    13
#define HAL_GREEN_INPUT_PIN  12
#define HAL_BLUE_INPUT_PIN   11

// *********************************************************************
//                           Current display
// *********************************************************************

extern short int currentDisplay[DISPLAY_NPIX];

// *********************************************************************
//                           Prototypes
// *********************************************************************

extern void display();

#endif
