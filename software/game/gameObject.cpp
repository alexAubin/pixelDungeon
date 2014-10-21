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
 *  @brief Game objects methods
*/

#include "gameObject.h"
#include "gameManager.h"
#include "gameMonsterAI.h"

gameObject_Hero* gameObject::theHero = 0;
gameObject* gameObject::emptyObject = 0;

void gameObject_Hero::triggerFromDeath() 
{
    gameManager::triggerGameOver();
}

void gameObject_Monster::triggerFromLink() 
{
    gameMonsterAI::activate(this);
}

void gameObject_Monster::triggerFromDeath() 
{
    gameMonsterAI::deactivate(this);
     
    for (int i = 0 ; i < nDeathLinks ; i++)
    {
        if (deathLinks[i]) deathLinks[i]->triggerFromLink();
    }

    gameManager::getTheMap()->setTile(GAME_TILE(x,y), gameObject::emptyObject);
}



