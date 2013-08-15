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

short int gameMonsterAI::miniMap[GAME_AI_MINIMAP_SIZE];
gameMap*  gameMonsterAI::theMap;

void gameMonsterAI::findBestWay(int begin_x, int begin_y, int end_x, int end_y)
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
    for (short int d = 0 ; d < GAME_AI_PATH_DEPTH ; d++)
    {
        for (short int i = GAME_AI_PATH_DEPTH - d ; i <= GAME_AI_PATH_DEPTH + d ; i++)
        for (short int j = GAME_AI_PATH_DEPTH - d ; j <= GAME_AI_PATH_DEPTH + d ; j++)
        {
            if (miniMap[MINIMAP_TILE(i,j)] != d) continue;
            
            // Expand the tile
            if (miniMap[MINIMAP_TILE(i,j+1)] == -1) miniMap[MINIMAP_TILE(i,j+1)] = d+1;
            if (miniMap[MINIMAP_TILE(i,j-1)] == -1) miniMap[MINIMAP_TILE(i,j-1)] = d+1;
            if (miniMap[MINIMAP_TILE(i+1,j)] == -1) miniMap[MINIMAP_TILE(i+1,j)] = d+1;
            if (miniMap[MINIMAP_TILE(i-1,j)] == -1) miniMap[MINIMAP_TILE(i-1,j)] = d+1;
            
        }
    }


    // Now find which node is closer to objective
    short int best_i = -1;
    short int best_j = -1;
          int best_d = 999;
    for (short int i = 0 ; i < GAME_AI_MINIMAP_WIDTH ; i++)
    for (short int j = 0 ; j < GAME_AI_MINIMAP_WIDTH ; j++)
    {
        if (miniMap[MINIMAP_TILE(i,j)] != GAME_AI_PATH_DEPTH) continue;

        int tmp_d = distance(offset_x + i, offset_y + j, end_x, end_y);
        
        if (tmp_d < best_d)
        {
            best_i = i;
            best_j = j;
            best_d = tmp_d;
        }
    }
    /*
    #ifdef DEBUG
        delay(100);
        Serial.println("   > Best found :");
        delay(100);
        Serial.println("x :");
        delay(100);
        Serial.println(offset_x + best_i);
        delay(100);
        Serial.println("y :");
        delay(100);
        Serial.println(offset_y + best_j);
        delay(100);
    #endif
    */
}
