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
 *  @brief Monster AI class
*/

#ifndef GAME_MONSTER_AI_H_
#define GAME_MONSTER_AI_H_

#include "gameCommon.h"
#include "gameMap.h"

#define GAME_AI_PATH_DEPTH 3
#define GAME_AI_MINIMAP_WIDTH (GAME_AI_PATH_DEPTH * 2 + 1)
#define GAME_AI_MINIMAP_SIZE GAME_AI_MINIMAP_WIDTH*GAME_AI_MINIMAP_WIDTH
#define MINIMAP_TILE(x,y) ((y) + GAME_AI_MINIMAP_WIDTH * (x))

class gameMonsterAI
{
	private:

        static short int miniMap[GAME_AI_MINIMAP_SIZE];
        static gameMap*  theMap;

	public:

		gameMonsterAI();
        static void findBestWay(int begin_x, int begin_y, int end_x, int end_y);
        static void setLinkToTheMap(gameMap* theMap_) { theMap = theMap_; };

};

#endif
