/********************************

          Pixel Dungeon
           by Djidane

      Map methods for the game

********************************/

/**
 *	@author Djidane
 * 	@file gameMap.cpp
 *  @brief Map methods for the game
 */

#include "gameMap.h"

bool gameMap::isTileVisibleByHero(int x,int y)
{
	int Dx = x - gameHero_i;
	int Dy = y - gameHero_j;

	int absDx = abs(Dx);
	int absDy = abs(Dy);

	int sgnDx = 1; if (Dx < 0) sgnDx = -1;
	int sgnDy = 1; if (Dy < 0) sgnDy = -1;

	int xDominated = 1;
	if (absDy > absDx)
		xDominated = 0;

	// TODO ! fix this
	if ((Dx == 0) || (Dy == 0)) return true;

	int currentStep_x = gameHero_i;
	int currentStep_y = gameHero_j;

	float deviation = 0;

	if (xDominated)
	{
		float yDeviationByStep = abs((float) Dy / (float) Dx);

		for (int dx = 1 ; dx < absDx  ; dx++)
		{
			currentStep_x += sgnDx;

			// Check if object on tile is solid (= block vision)
			if (isSolid(currentStep_x,currentStep_y)) return false;

			// Increment y-deviation
			deviation +=yDeviationByStep;

			if (deviation >= 0.5)
			{
				currentStep_y += sgnDy;
			    deviation -= 1.0;
			}
		}
	}
	// yDominated
	else
	{
		float xDeviationByStep = abs((float) Dx / (float) Dy);

		for (int dy = 1 ; dy < absDy  ; dy++)
		{
			currentStep_y += sgnDy;

			// Check if object on tile is solid (= block vision)
			if (isSolid(currentStep_x,currentStep_y)) return false;

			// Increment x-deviation
			deviation += xDeviationByStep;

			if (deviation >= 0.5)
			{
				currentStep_x += sgnDx;
			    deviation -= 1.0;
			}
		}
	}

	// If we get here, it means nothing blocked vision
	return true;
}

void gameMap::updateCornerCurrentDisplay()
{
	if (gameHero_i < DISPLAY_WIDTH/2) cornerCurrentDisplay_i = 0;
	else if (gameHero_i > GAME_MAP_WIDTH - DISPLAY_WIDTH/2) cornerCurrentDisplay_i = GAME_MAP_WIDTH - DISPLAY_WIDTH;
	else cornerCurrentDisplay_i = gameHero_i - DISPLAY_WIDTH/2;

	if (gameHero_j < DISPLAY_WIDTH/2) cornerCurrentDisplay_j = 0;
	else if (gameHero_j > GAME_MAP_HEIGHT  - DISPLAY_WIDTH/2) cornerCurrentDisplay_j = GAME_MAP_HEIGHT  - DISPLAY_WIDTH;
	else cornerCurrentDisplay_j = gameHero_j - DISPLAY_WIDTH/2;

}

void gameMap::setGameCurrentDisplay(int x, int y)
{

	// Update the (x,y) current displa position
	positionCurrentDisplay_x = x;
	positionCurrentDisplay_y = y;

	// Update each pixel according to objects on the portion of the map
	int currentTileColor;

	for (int k = 0 ; k < DISPLAY_WIDTH ; k++)
	for (int l = 0 ; l < DISPLAY_WIDTH ; l++)
	{
		currentTileColor = getColor(k+x,l+y);

		// If the object is not visible by the hero,
		// we set the tile to OBJECT_EMPTY_COLOR

		//if (currentTileColor != GAME_OBJECT_EMPTY_COLOR) && (!isVisibleByHero(k+x,l+y))
		//	currentTileColor == GAME_OBJECT_EMPTY_COLOR;

		currentDisplay[k + l*DISPLAY_WIDTH] = currentTileColor;
	}
}

gameObject::Color gameMap::getColor(int x, int y)
{
	if (layer1.getType(x,y) == gameObject::Type::EMPTY)
		return layer1.getColor(x,y);
	else
		return layer0.getColor(x,y);
}

void gameMap::triggerAction(int x, int y);
