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
	return map[tile]->getColor();
}

void gameMap::triggerFromAction(int tile)
{
    return map[tile]->triggerFromAction();
}

void gameMap::setTile(int tile,gameObject* object)
{
    map[tile] = object;
}

bool gameMap::isWalkable(int tile) const
{
   return map[tile]->isWalkable();
}

bool gameMap::moveCreature(gameObject_Creature* theCreature, Direction dir)
{
   
    int prev_x = theCreature->getX();
    int prev_y = theCreature->getY();

    int new_x = prev_x;
    int new_y = prev_y;

         if (dir == UP)    new_x++;
    else if (dir == DOWN)  new_x--;
    else if (dir == LEFT)  new_y--;
    else if (dir == RIGHT) new_y++;
   
    if (isWalkable(GAME_TILE(new_x,new_y)))
    {

        // Trigger action on the new tile
        triggerFromAction(GAME_TILE(new_x,new_y));

        // Actually move the creature

            // Replace previous tile with the object the creature is standing on
            setTile(GAME_TILE(prev_x,prev_y), theCreature->getObjectStandingOn());

            // Set the new "object standing on" for the creature according to new tile
            theCreature->setObjectStandingOn(map[GAME_TILE(new_x,new_y)]);

            // Set the position of the creature to the new tile
            setTile(GAME_TILE(new_x ,new_y ), theCreature);
            theCreature->setPosition(new_x,new_y);
        
        return true;
    }
    else
    {
        return false;
    }

}

bool gameMap::heroAttack(gameObject_Hero* theHero, Direction dir)
{
    int target_x = theHero->getX();
    int target_y = theHero->getY();

         if (dir == UP)    target_x++;
    else if (dir == DOWN)  target_x--;
    else if (dir == LEFT)  target_y--;
    else if (dir == RIGHT) target_y++;
    
    if (map[GAME_TILE(target_x,target_y)]->getType() == OBJECTTYPE_MONSTER)
    {
        ((gameObject_Monster*) map[GAME_TILE(target_x,target_y)])->receiveAttack();
        return true;
    }

    return false;
}


