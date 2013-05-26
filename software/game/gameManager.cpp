/********************************

          Pixel Dungeon
           by Djidane

     Game-management methods

********************************/

/**
 *	@author Djidane
 * 	@file gameManager.cpp
 *  @brief Game-management methods
 */

#include "gameManager.h"

void gameManager::init()
{
	setGameCurrentDisplay(2,2);
}

void gameManager::moveHero(int direction)
{
	int prev_i = gameHero_i;
	int prev_j = gameHero_j;

	int new_i = prev_i;
	int new_j = prev_j;

		 if (direction == UP)    new_j++;
	else if (direction == DOWN)  new_j--;
	else if (direction == LEFT)  new_i--;
	else if (direction == RIGHT) new_i++;

	if (isWalkable(getGameMapType(new_i,new_j)))
	{

		// Make action on the case if there's one

		makeAction(new_i,new_j);

		// Save next tile and recover previous one
		int tmpNextId = getGameMapId(new_i,new_j);
		int tmpNextType = getGameMapType(new_i,new_j);

		setGameMapId(prev_i,prev_j,prevHeroTileId);
		setGameMapType(prev_i,prev_j,prevHeroTileType);

		prevHeroTileType = tmpNextType;
		prevHeroTileId = tmpNextId;


		// Actually move hero
		setGameMapType(new_i,new_j,GAME_OBJECT_HERO);
		gameHero_i = new_i;
		gameHero_j = new_j;

		// Update display
		updateCornerCurrentDisplay();
		setGameCurrentDisplay(cornerCurrentDisplay_i,cornerCurrentDisplay_j);
	}
}
