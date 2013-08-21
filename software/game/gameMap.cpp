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

gameMap::gameMap() 
{ 
};

void gameMap::setCurrentDisplay(gameObject_Hero* theHero)
{
    int positionNewDisplay_x, positionNewDisplay_y;

    // Manage borders on the X axis
	if (theHero->getX() < DISPLAY_WIDTH/2) 
         positionNewDisplay_x = 0;
	else if (theHero->getX() > GAME_MAP_HEIGHT - DISPLAY_WIDTH/2) 
         positionNewDisplay_x = GAME_MAP_HEIGHT - DISPLAY_WIDTH;
	else 
         positionNewDisplay_x = theHero->getX() - DISPLAY_WIDTH/2;

    // Manage borders on the Y axis
	if (theHero->getY() < DISPLAY_WIDTH/2) 
         positionNewDisplay_y = 0;
	else if (theHero->getY() > GAME_MAP_WIDTH  - DISPLAY_WIDTH/2) 
         positionNewDisplay_y = GAME_MAP_WIDTH - DISPLAY_WIDTH;
	else 
         positionNewDisplay_y = theHero->getY() - DISPLAY_WIDTH/2;

    updateCurrentDisplay(positionNewDisplay_x,positionNewDisplay_y);

}

void gameMap::updateCurrentDisplay(int x, int y)
{

	// Update the (x,y) current display position
	positionCurrentDisplay_x = x;
	positionCurrentDisplay_y = y;

	for (short int k = 0 ; k < DISPLAY_WIDTH ; k++)
	for (short int l = 0 ; l < DISPLAY_WIDTH ; l++)
	{
		currentDisplay[DISPLAY_PIXEL(k,l)] = getColor(GAME_TILE(k+x,l+y));
	}
}

void gameMap::updateTileDisplay(int x, int y)
{

	// Update the (x,y) current display position
	short int k = x - positionCurrentDisplay_x;
    short int l = y - positionCurrentDisplay_y;

    if ((k < 0) || (l < 0) || (k >= DISPLAY_WIDTH) || (l >= DISPLAY_WIDTH)) return;

	currentDisplay[DISPLAY_PIXEL(k,l)] = getColor(GAME_TILE(x,y));
}

ObjectColor gameMap::getColor(int tile) const
{
	if (layer1.getType(tile) == OBJECTTYPE_EMPTY)
		return layer0.getColor(tile);
	else
		return layer1.getColor(tile);
}

void gameMap::triggerAction(int tile)
{
    layer0.triggerAction(tile);
}

void gameMap::setTileLayer0(int tile,gameObject* object)
{
    layer0.setTile(tile,object);
}

void gameMap::setTileLayer1(int tile,gameObject* object)
{
    layer1.setTile(tile,object);
}

bool gameMap::isWalkable(int tile) const
{
   return (layer0.isWalkable(tile) && layer1.isWalkable(tile));
}

bool gameMap::moveCreature(gameObject_Creature* theCreature, Direction dir, gameObject* emptyObject)
{
   
    int prev_x = theCreature->getX();
    int prev_y = theCreature->getY();

    int new_x = prev_x;
    int new_y = prev_y;

    bool actuallyMoved = false;

         if (dir == UP)    new_x++;
    else if (dir == DOWN)  new_x--;
    else if (dir == LEFT)  new_y--;
    else if (dir == RIGHT) new_y++;
   
    if (isWalkable(GAME_TILE(new_x,new_y)))
    {

        // Trigger action on this tile
        triggerAction(GAME_TILE(new_x,new_y));

        // Move the creature
        layer1.setTile(GAME_TILE(prev_x,prev_y), emptyObject);
        layer1.setTile(GAME_TILE(new_x ,new_y ), theCreature);
        theCreature->setPosition(new_x,new_y);
        
        actuallyMoved = true;
    }

    return actuallyMoved;
    
}

