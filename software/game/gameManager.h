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
 *  @author Alexandre Aubin
 *  @brief  Game-management class
*/

#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_

#include "game/gameCommon.h"
#include "game/gameMap.h"
#include "game/gameData.h"
#include "game/gameMonsterAI.h"

class gameManager
{
    
    public:

        // Constructor
        gameManager() 
        { 
            gameMonsterAI::setLinkToTheMap( &(theMap) );
        };

        void init();

        // Interface with the Keys HAL

        void upKey()    { moveHero(UP);    }
        void downKey()  { moveHero(DOWN);  }
        void rightKey() { moveHero(RIGHT); }
        void leftKey()  { moveHero(LEFT);  }

    private:

        // Attributes

        gameMap          theMap;
        gameObject*      theObjectCollection[THEGAME_TOTALNUMBEROFOBJECTS];
        gameObject_Hero* theHero;

        // Methods

        void moveHero(Direction dir);


};

extern gameManager theGame;

void initGame();
void testPath();

#endif
