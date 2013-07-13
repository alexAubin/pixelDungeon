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
 *  @brief Map methods for the game
*/

#include "gameMap.h"

void gameMap::updateCurrentDisplay(gameObject_Hero* theHero)
{
	if (theHero->getX() < DISPLAY_WIDTH/2) 
         positionCurrentDisplay_x = 0;
	else if (theHero->getX() > GAME_MAP_WIDTH - DISPLAY_WIDTH/2) 
         positionCurrentDisplay_x = GAME_MAP_WIDTH - DISPLAY_WIDTH;
	else 
         positionCurrentDisplay_x = theHero->getX() - DISPLAY_WIDTH/2;

	if (theHero->getY() < DISPLAY_WIDTH/2) 
         positionCurrentDisplay_y = 0;
	else if (theHero->getY() > GAME_MAP_HEIGHT  - DISPLAY_WIDTH/2) 
         positionCurrentDisplay_y = GAME_MAP_HEIGHT  - DISPLAY_WIDTH;
	else 
         positionCurrentDisplay_y = theHero->getY() - DISPLAY_WIDTH/2;

    for (int k = 0 ; k < DISPLAY_WIDTH ; k++)
	for (int l = 0 ; l < DISPLAY_WIDTH ; l++)
	{
		currentDisplay[k + l*DISPLAY_WIDTH] = getColor(positionCurrentDisplay_x+k,positionCurrentDisplay_y+l);
	}
}

void gameMap::setGameCurrentDisplay(int x, int y)
{

	// Update the (x,y) current displa position
	positionCurrentDisplay_x = x;
	positionCurrentDisplay_y = y;

	for (int k = 0 ; k < DISPLAY_WIDTH ; k++)
	for (int l = 0 ; l < DISPLAY_WIDTH ; l++)
	{
		currentDisplay[k + l*DISPLAY_WIDTH] = getColor(k+x,l+y);
	}
}

ObjectColor gameMap::getColor(int x, int y)
{
	if (layer1.getType(x,y) == OBJECTTYPE_EMPTY)
		return layer0.getColor(x,y);
	else
		return layer1.getColor(x,y);
}

void gameMap::triggerAction(int x, int y)
{
}

void gameMap::setTileLayer0(int tile,gameObject* object)
{
    layer0.setTile(tile,object);
}

void gameMap::setTileLayer1(int tile,gameObject* object)
{
    layer1.setTile(tile,object);
}

bool gameMap::isWalkable(int x, int y) const
{
   int tile = x + GAME_MAP_WIDTH*y;
   return (layer0.isWalkable(tile) && layer1.isWalkable(tile));
}
