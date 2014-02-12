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
 *  @brief Methods for Monster AI 
*/

#include "gameMonsterAI.h"

short int           gameMonsterAI::miniMap[GAME_AI_MINIMAP_SIZE];
gameMap*            gameMonsterAI::theMap;
gameObject_Hero*    gameMonsterAI::theHero;
gameObject_Monster* gameMonsterAI::activeMonster;

void gameMonsterAI::doMonsterAction()
{

    if (activeMonster == 0) return;

    // Disable interrupts
    noInterrupts();

    // If we're right next to the hero, attack him
    if (distance(activeMonster->getX(),activeMonster->getY(),theHero->getX(),theHero->getY()) == 1)
    {
        theHero->receiveAttack();
        theMap->updateTileDisplay(theHero->getX(),theHero->getY());
    }
    // Otherwise, try to find a path/best direction to go to the hero
    else
    {
        Direction bestWay = findBestWay(activeMonster->getX(),activeMonster->getY(),theHero->getX(),theHero->getY());
        //bestWay = UP;
        
        int prev_x = activeMonster->getX();
        int prev_y = activeMonster->getY();

        if (theMap->moveCreature(activeMonster,bestWay))
        {
            theMap->updateTileDisplay(prev_x,prev_y);
            theMap->updateTileDisplay(activeMonster->getX(),activeMonster->getY());
        }
    }

    // Re-enable interrupts
    interrupts();
   

}


Direction gameMonsterAI::findBestWay(int begin_x, int begin_y, int end_x, int end_y)
{
    int offset_x = begin_x - GAME_AI_PATH_DEPTH;
    int offset_y = begin_y - GAME_AI_PATH_DEPTH;


    
    // Fill minimap with walkable/nonwalkable flags
    for (short int i = 0 ; i < GAME_AI_MINIMAP_WIDTH ; i++) { short int x = offset_x + i;
    for (short int j = 0 ; j < GAME_AI_MINIMAP_WIDTH ; j++) { short int y = offset_y + j;

        // If outside the map or non walkable : put -2
        if (    (x < 0) || (x >= GAME_MAP_HEIGHT)
             || (y < 0) || (y >= GAME_MAP_WIDTH ) 
             || (!theMap->isWalkable(GAME_TILE(x,y)))
           )
            miniMap[MINIMAP_TILE(i,j)] = -2;
        
        // If walkable : put - 1
        else  
            miniMap[MINIMAP_TILE(i,j)] = -1;
    } }

    // Init center of map with 0 (= begin point)
    miniMap[MINIMAP_TILE(GAME_AI_PATH_DEPTH,GAME_AI_PATH_DEPTH)] = 0;
    
    // Actually run the "best-way" algorithm
    short int best_i = -1;
    short int best_j = -1;
          int best_dist = 999;
    short int max_d = 0;
    for (short int d = 0 ; d < GAME_AI_PATH_DEPTH ; d++)
    {
        for (short int i = GAME_AI_PATH_DEPTH - d ; (i <= GAME_AI_PATH_DEPTH + d) && (best_i == -1) ; i++)
        for (short int j = GAME_AI_PATH_DEPTH - d ; (j <= GAME_AI_PATH_DEPTH + d) && (best_i == -1) ; j++)
        {
            if (miniMap[MINIMAP_TILE(i,j)] != d) continue;
           
            // Expand the tile
            if (miniMap[MINIMAP_TILE(i,j+1)] == -1) { miniMap[MINIMAP_TILE(i,j+1)] = d+1; max_d = d+1; }
            if (miniMap[MINIMAP_TILE(i,j-1)] == -1) { miniMap[MINIMAP_TILE(i,j-1)] = d+1; max_d = d+1; }
            if (miniMap[MINIMAP_TILE(i+1,j)] == -1) { miniMap[MINIMAP_TILE(i+1,j)] = d+1; max_d = d+1; }
            if (miniMap[MINIMAP_TILE(i-1,j)] == -1) { miniMap[MINIMAP_TILE(i-1,j)] = d+1; max_d = d+1; }
 
            // If tile is in front of hero, 
            if (distance(offset_x + i, offset_y + j, end_x, end_y) == 1)
            {
                best_i = i;
                best_j = j;
                max_d = d+1;
            }           
        }

        if (best_i != -1) break;
    }

    // Now find which node is closer to objective if we haven't find a tile meanwhile with dist = 1

    if (best_i == -1)
    for (short int i = 0 ; i < GAME_AI_MINIMAP_WIDTH ; i++)
    for (short int j = 0 ; j < GAME_AI_MINIMAP_WIDTH ; j++)
    {
        if (miniMap[MINIMAP_TILE(i,j)] != max_d) continue;

        int tmp_dist = distance(offset_x + i, offset_y + j, end_x, end_y);
        
        if (tmp_dist < best_dist)
        {
            best_i = i;
            best_j = j;
            best_dist = tmp_dist;
        }
    }

    // Go back to determine which direction to go
    for (int d = max_d ; d != 1 ; d--)
    {
        if (miniMap[MINIMAP_TILE(best_i,best_j+1)] == d-1) best_j++;
        if (miniMap[MINIMAP_TILE(best_i,best_j-1)] == d-1) best_j--; 
        if (miniMap[MINIMAP_TILE(best_i+1,best_j)] == d-1) best_i++;
        if (miniMap[MINIMAP_TILE(best_i-1,best_j)] == d-1) best_i--;
    }


      if (best_i - 1 == GAME_AI_PATH_DEPTH) return UP;
      else if (best_i + 1 == GAME_AI_PATH_DEPTH) return DOWN;
      else if (best_j - 1 == GAME_AI_PATH_DEPTH) return RIGHT;
      else if (best_j + 1 == GAME_AI_PATH_DEPTH) return LEFT;
       else
       return NOMOVE;



}
