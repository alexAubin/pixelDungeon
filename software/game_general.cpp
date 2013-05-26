
/********************************

          Pixel Dungeon
           by Djidane

     Game-specific functions

********************************/

/**
 *	@author Djidane
 * 	@file game.cpp
 *  @brief Game-specific functions
 */

#include "game_general.h"

int cornerCurrentDisplay_i;
int cornerCurrentDisplay_j;

int gameHero_i = gameHero_iBegin;
int gameHero_j = gameHero_jBegin;

void initGame()
{


	cornerCurrentDisplay_i = 2;
	cornerCurrentDisplay_j = 2;

	setGameCurrentDisplay(cornerCurrentDisplay_i,
						  cornerCurrentDisplay_j);
}


void setGameCurrentDisplay(int i, int j)
{

	int currentTileColor;

	for (int k = 0 ; k < DISPLAY_WIDTH ; k++)
	for (int l = 0 ; l < DISPLAY_WIDTH ; l++)
	{
		currentTileColor = getGameObjectTypeColor(getGameMapType(k+i,l+j));

		// If the object is not visible, we set the tile to OBJECT_EMPTY_COLOR
		if (currentTileColor != GAME_OBJECT_EMPTY_COLOR) && (!isVisibleByHero(k+i,l+j))
			currentTileColor == GAME_OBJECT_EMPTY_COLOR;

		currentDisplay[k + l*DISPLAY_WIDTH] = currentTileColor;
	}

}

// Inspired by Bresenham's line algorithm
int isVisibleByHero(int x,int y)
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
	if ((Dx == 0) || (Dy == 0)) return 1;

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
			if (isSolid(currentStep_x,currentStep_y)) return 0;

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
			if (isSolid(currentStep_x,currentStep_y)) return 0;

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
	return 1;
}

void makeAction(int i, int j)
{
	if (getGameMapType(i,j) == GAME_OBJECT_SWITCH)
	{
		setGameMapType(10,5, GAME_OBJECT_DOOR_OPEN);
		setGameMapType(i,j,  GAME_OBJECT_SWITCH_ON);

	}
	else if (getGameMapType(i,j) == GAME_OBJECT_SWITCH_ON)
	{
		setGameMapType(i,j,  GAME_OBJECT_SWITCH);

		setGameMapType(10,5, GAME_OBJECT_DOOR);
	}

}

void moveHero(int direction)
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

void updateCornerCurrentDisplay()
{
	if (gameHero_i < DISPLAY_WIDTH/2) cornerCurrentDisplay_i = 0;
	else if (gameHero_i > GAME_MAP_WIDTH - DISPLAY_WIDTH/2) cornerCurrentDisplay_i = GAME_MAP_WIDTH - DISPLAY_WIDTH;
	else cornerCurrentDisplay_i = gameHero_i - DISPLAY_WIDTH/2;

	if (gameHero_j < DISPLAY_WIDTH/2) cornerCurrentDisplay_j = 0;
    else if (gameHero_j > GAME_MAP_HEIGHT  - DISPLAY_WIDTH/2) cornerCurrentDisplay_j = GAME_MAP_HEIGHT  - DISPLAY_WIDTH;
	else cornerCurrentDisplay_j = gameHero_j - DISPLAY_WIDTH/2;

}

// ####################################
// #            Tools & misc          #
// ####################################

void upKey()
{
	moveHero(UP);
}

void downKey()
{
	moveHero(DOWN);
}

void rightKey()
{
	moveHero(RIGHT);
}

void leftKey()
{
	moveHero(LEFT);
}








/*
void getVisibleMap(int globalMap_i, int globalMap_j, int* visibilityMask)
{
	int floodingMap[DISPLAY_PIX];

	int xStack[DISPLAY_NPIX];
	int yStack[DISPLAY_NPIX];

	int nStack = 0;
	int toReadCurrent = 0;
	int toReadNext = 0;

	int currentStep = 0;


	// Init with hero being in 0,0

	nStack++;
	toReadCurrent++;
	xStack[nStack]=0;
	yStack[nStack]=0;

	while (currentStep < 3)
	{

	}



}
*/
/*
void getVisibleMap(int globalMap_i, int globalMap_j, int* visibilityMask)
{

	int accessibilityMask[DISPLAY_NPIX];
	int c = 4;

	// Initiate accessibilityMask to 0
	for (int i = 0 ; i < DISPLAY_NPIX ; i++) accessibility[i] = 0;

	// Fill the first 4 adjacent case to hero (square of size 1)
	if (getGameMapType(globalMap_i+1,globalMap_j) == GAME_OBJECT_EMPTY)
		accessibilityMask[(c+1) + c * DISPLAY_WIDTH ] = 1;
	if (getGameMapType(globalMap_i-1,globalMap_j) == GAME_OBJECT_EMPTY)
		accessibilityMask[(c-1) + c * DISPLAY_WIDTH ] = 1;
	if (getGameMapType(globalMap_i,globalMap_j+1) == GAME_OBJECT_EMPTY)
		accessibilityMask[c + (c+1) * DISPLAY_WIDTH ] = 1;
	if (getGameMapType(globalMap_i,globalMap_j-1) == GAME_OBJECT_EMPTY)
		accessibilityMask[c + (c-1) * DISPLAY_WIDTH ] = 1;

	// Go on with square of size (2*deep + 1) until max DEEPNESS is reached
	for (int deep = 1 ; deep <= VISIBLITY_DEEPNESS ; deep++)
	for (int k = -deep ; k < deep ; k++)
	{
		// Check first side
		if (accessibilityMask[(c+deep) + (c+k) * DISPLAY_WIDTH ])
		{
			// Check 3 non-trivial adjacent case
			if (getGameMapType(globalMap_i+deep,globalMap_j+k+1) == GAME_OBJECT_EMPTY)
				accessibilityMask[(c+deep) + (c+k) * DISPLAY_WIDTH ] = 1;
		}

		// Same for the 3 other side
		if (accessibilityMask[(c-deep) + (c+k) * DISPLAY_WIDTH ])
		if (accessibilityMask[(c+k) + (c+deep) * DISPLAY_WIDTH ])
		if (accessibilityMask[(c+k) + (c-deep) * DISPLAY_WIDTH ])
	}



}
*/


/*
void getVisibleMap(int recursivityIndex, int globalMap_i, int globalMap_j, int* visibilityLocalMap, int localMap_i, int localMap_j)
{
	visibilityLocalMap[localMap_i + localMap_j*DISPLAY_WIDTH]++;

	if (recursivityIndex)
	{
		if (localMap_i > 0)
			if ((getGameMapType(globalMap_i-1,globalMap_j) == GAME_OBJECT_EMPTY) && (visibilityLocalMap[localMap_i-1 + localMap_j*DISPLAY_WIDTH]))

				getVisibleMap(recursivityIndex-1,globalMap_i-1,globalMap_j,visibilityLocalMap,localMap_i-1,localMap_j);
	}
}
*/
