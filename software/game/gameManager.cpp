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
 *    @author Alexandre Aubin
 *  @brief  Game-management methods
 */

#include "game/gameManager.h"
#include <avr/pgmspace.h>

PROGMEM const short int initMap[GAME_MAP_WIDTH*GAME_MAP_HEIGHT] =
{
//      0 1 2 3 4 5 6 7 8 9 101112131415
/*0 */  0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,
/*1 */	0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,
/*2 */	0,0,1,1,0,1,0,1,0,1,1,0,0,0,0,0,
/*3 */	0,1,1,0,0,1,0,1,0,0,1,1,1,1,1,0,
/*4 */	0,1,0,0,1,1,0,1,1,0,1,0,0,0,1,0,
/*5 */	1,1,0,1,1,0,0,0,1,0,2,0,0,4,1,0,
/*6 */	1,0,0,0,1,0,6,0,1,1,1,0,0,0,1,0,
/*7 */	1,0,3,0,1,0,0,0,1,0,1,7,1,1,1,0,
/*8 */	1,5,0,0,1,1,1,1,1,0,1,0,1,0,0,0,
/*9 */	1,1,1,1,1,0,0,0,1,1,1,0,1,0,0,0,
/*10*/	0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,
/*11*/	0,0,0,0,1,0,0,0,1,1,1,1,1,0,0,0,
/*12*/	0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0
};

gameMap          gameManager::theMap;
gameObject*      gameManager::theObjectCollection[THEGAME_TOTALNUMBEROFOBJECTS];
gameObject_Hero* gameManager::theHero;
short int        gameManager::gameOver = -1;
bool             gameManager::attackMode = false;

gameObject_Monster* gameManager::init()
{
    // Dirty temporary system for map initialization
    // TODO : more generic/developper friendly way to implement map

    theObjectCollection[0] = new gameObject_Empty  ();         
    theObjectCollection[1] = new gameObject_Wall   ();          
    theObjectCollection[2] = new gameObject_Door   (false);    
    theObjectCollection[3] = new gameObject_Switch (false,theObjectCollection[2],false);
    theObjectCollection[4] = new gameObject_Monster(5,13,8);
    theObjectCollection[5] = new gameObject_Hppot  (4);
    theObjectCollection[6] = new gameObject_Hero   (6,6);
    theObjectCollection[7] = new gameObject_Door   (false);    

    theHero = (gameObject_Hero*) theObjectCollection[6];

    for (int i = 0 ; i < GAME_MAP_WIDTH*GAME_MAP_HEIGHT ; i++)
    {
        theMap.setTile(i,theObjectCollection[pgm_read_word_near(initMap+i)]);
    }

    theMap.setCurrentDisplay(theHero);

    return (gameObject_Monster*) theObjectCollection[4];
}

void gameManager::heroMove(Direction dir)
{
    if (gameManager::getGameOverStatus() != -1) return;
    
    // Disable interrupts
    noInterrupts();

    if (theMap.moveCreature(theHero,dir))
    {
        // Update display
        theMap.setCurrentDisplay(theHero);
    }

    // Re-enable interrupts
    interrupts();
    
}

void gameManager::heroAttack(Direction dir)
{
    if (gameManager::getGameOverStatus() != -1) return;

    noInterrupts();
    
    if (theMap.heroAttack(theHero,dir))
    {
        // Update display
        theMap.setCurrentDisplay(theHero);
    }

    interrupts();

}

void gameManager::triggerGameOver()
{
    gameOver = 0;
    
	for (short int k = 0 ; k < DISPLAY_WIDTH ; k++)
	for (short int l = 0 ; l < DISPLAY_WIDTH ; l++)
	{
		currentDisplay[DISPLAY_PIXEL(k,l)] = DISPLAYCOLOR_EMPTY;
	}
}




