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

class gameManager
{

    public:

        // Constructor (not used)
        gameManager()
        {
        };

        static void init();

        // Accessors

        static gameMap*         getTheMap()              { return &theMap;             }
        static gameObject**     getTheObjectCollection() { return theObjectCollection; }

        // Interface with the Keys HAL

        static void upKey()    { if (attackMode) heroAttack(UP);    else heroMove(UP);   }
        static void downKey()  { if (attackMode) heroAttack(DOWN);  else heroMove(DOWN);  }
        static void rightKey() { if (attackMode) heroAttack(RIGHT); else heroMove(RIGHT); }
        static void leftKey()  { if (attackMode) heroAttack(LEFT);  else heroMove(LEFT);  }
        static void aFallKey() { attackMode = true; }
        static void aRiseKey() { attackMode = false;  }

        static void triggerGameOver();
        static short int getGameOverStatus() { if (gameOver != -1) gameOver++; return gameOver; }

        static void triggerReboot() { wdt_enable(WDTO_15MS); while (1) { } }

    private:

        // Attributes

        static gameMap          theMap;
        static gameObject*      theObjectCollection[THEGAME_TOTALNUMBEROFOBJECTS];

        static short int gameOver;

        // Methods

        static void heroMove(Direction dir);
        static void heroAttack(Direction dir);

        static bool attackMode;

};

#endif
