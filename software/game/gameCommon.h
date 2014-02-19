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
 *  @brief  Common definition
 */

#ifndef GAME_COMMON_H_
#define GAME_COMMON_H_

	#include "hal/display.h"
    #include <avr/wdt.h>

    #define GAME_MAP_WIDTH  16
	#define GAME_MAP_HEIGHT 13
        
    #define THEGAME_TOTALNUMBEROFOBJECTS 7

    #define GAME_TILE(x,y) ((y) + GAME_MAP_WIDTH * (x))

    enum Direction
    {
        UP, DOWN, RIGHT, LEFT, NOMOVE
    };

    void initGame(); 
    void gameTimerHandler();

    int distance(int a_x, int a_y, int b_x, int b_y);

#endif
