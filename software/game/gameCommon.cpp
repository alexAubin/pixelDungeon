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

#include "gameCommon.h"
#include "gameManager.h"
#include "gameMonsterAI.h"

void initGame() 
{ 
    gameObject_Monster* monster = gameManager::init();
    // Temporary "monster" in argument until activation is done automatically
    gameMonsterAI::init(monster);
};

void gameTimerHandler() 
{
    short int gameOverStatus = gameManager::getGameOverStatus();

    if (gameOverStatus == -1)
        gameMonsterAI::doMonsterAction();
    else if (gameOverStatus >= 5) 
        gameManager::triggerReboot();
};


int distance(int a_x, int a_y, int b_x, int b_y)
{
    int d_x = a_x - b_x;
    int d_y = a_y - b_y;

    return (d_x * d_x + d_y * d_y);
}

