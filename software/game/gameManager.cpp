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

gameManager theGame;

#include <avr/pgmspace.h>

PROGMEM prog_uint16_t initLayer0[GAME_MAP_WIDTH*GAME_MAP_HEIGHT] =
{
//      0 1 2 3 4 5 6 7 8 9 101112131415
/*0 */  0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,
/*1 */	0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,
/*2 */	0,0,1,1,0,1,0,1,0,1,1,0,0,0,0,0,
/*3 */	0,1,1,0,0,1,0,1,0,0,1,1,1,1,1,0,
/*4 */	0,1,0,0,1,1,0,1,1,0,1,0,0,0,1,0,
/*5 */	1,1,0,1,1,0,0,0,1,0,2,0,0,0,1,0,
/*6 */	1,0,0,0,1,0,0,0,1,1,1,0,0,0,1,0,
/*7 */	1,0,3,0,1,0,0,0,1,0,1,0,1,1,1,0,
/*8 */	1,0,0,0,1,1,1,1,1,0,1,0,1,0,0,0,
/*9 */	1,1,1,1,1,0,0,0,1,1,1,0,1,0,0,0,
/*10*/	0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,
/*11*/	0,0,0,0,1,0,0,0,1,1,1,1,1,0,0,0,
/*12*/	0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0
};


PROGMEM prog_uint16_t initLayer1[GAME_MAP_WIDTH*GAME_MAP_HEIGHT] =
{
//      0 1 2 3 4 5 6 7 8 9 101112131415
/*0 */  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
/*1 */	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
/*2 */	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
/*3 */	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
/*4 */	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
/*5 */	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
/*6 */	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
/*7 */	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
/*8 */	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
/*9 */	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
/*10*/	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
/*11*/	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
/*12*/	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

void initGame() { theGame.init(); };

void gameManager::init()
{
    // Dirty temporary system for map initialization
    // TODO : more generic/developper friendly way to implement map

    gameObject_Empty*  empty  = new gameObject_Empty(0);         
    gameObject_Wall*   wall   = new gameObject_Wall(1);          
    gameObject_Door*   door   = new gameObject_Door(2,false);    
    gameObject_Switch* switc  = new gameObject_Switch(3,false,2);
  
    theObjectCollection[0] = empty;
    theObjectCollection[1] = wall;
    theObjectCollection[2] = door;
    theObjectCollection[3] = switc;

    for (int i = 0 ; i < GAME_MAP_WIDTH*GAME_MAP_HEIGHT ; i++)
    {
        theMap.setTileLayer0(i,theObjectCollection[pgm_read_word_near(initLayer0+i)]);
        theMap.setTileLayer1(i,theObjectCollection[pgm_read_word_near(initLayer0+i)]);
    }


    theHero = new gameObject_Hero(4,6,6);         
    theObjectCollection[4] = theHero;
    theMap.setTileLayer1(6+GAME_MAP_WIDTH*6,theHero);
     
    theMap.setGameCurrentDisplay(2,2);
}

void gameManager::moveHero(Direction dir)
{
    #ifdef DEBUG
         if (dir == UP)    Serial.println(" > Moving hero : Up ");
    else if (dir == DOWN)  Serial.println(" > Moving hero : Down ");
    else if (dir == LEFT)  Serial.println(" > Moving hero : Left ");
    else if (dir == RIGHT) Serial.println(" > Moving hero : Right ");
    #endif
   
    int prev_x = theHero->getX();
    int prev_y = theHero->getY();

    int new_x = prev_x;
    int new_y = prev_y;

         if (dir == UP)    new_y++;
    else if (dir == DOWN)  new_y--;
    else if (dir == LEFT)  new_x--;
    else if (dir == RIGHT) new_x++;
   
    if (theMap.isWalkable(new_x,new_y))
    {

        // Trigger action on the case if there's one
        //theMap.triggerAction(new_x,new_y);

        // Move the hero
        theMap.setTileLayer1(prev_y+GAME_MAP_WIDTH*prev_x,theObjectCollection[0]);
        theMap.setTileLayer1(new_y +GAME_MAP_WIDTH*new_x, theHero);

        theHero->setX(new_x);
        theHero->setY(new_y);

        // Update display
        theMap.updateCurrentDisplay(theHero);
        
    }
    
}

