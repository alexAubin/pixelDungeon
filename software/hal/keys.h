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
 *  @brief Keys management definitions
*/

#ifndef HAL_KEYS_H_
#define HAL_KEYS_H_

#include "common.h"
#include "game/gameManager.h"

// *********************************************************************
//                         IO config (pin numbers)
// *********************************************************************

#define UP_KEY 4
#define DOWN_KEY 3
#define LEFT_KEY 5
#define RIGHT_KEY 2

// *********************************************************************
//                           Prototypes
// *********************************************************************

void upInterruptHandler();
void downInterruptHandler();
void leftInterruptHandler();
void rightInterruptHandler();


#endif
