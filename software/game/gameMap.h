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
 *  @brief Map-of the game management class
*/

#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#include "gameCommon.h"
#include "gameObject.h"

class gameMap
{
	private:

		gameObject*  map[GAME_MAP_WIDTH * GAME_MAP_HEIGHT];

		int positionCurrentDisplay_x;
		int positionCurrentDisplay_y;

	public:

		gameMap();

        void setCurrentDisplay(gameObject_Hero* theHero);
		void updateCurrentDisplay(int x, int y);
        void updateTileDisplay(int x, int y);

		ObjectColor getColor(int tile)   const;
        bool        isWalkable(int tile) const;
        
        void setTile(int tile,gameObject* object);
		void triggerAction(int tile);
        
        bool moveCreature(gameObject_Creature* theCreature, Direction dir);
};
#endif
