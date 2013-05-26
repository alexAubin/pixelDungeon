
/********************************

          Pixel Dungeon
           by Djidane

     Game-specific definitions

********************************/

/**
 *	@author Djidane
 * 	@file game.h
 *  @brief Game-specific definitions
 */

#ifndef GAME_GENERAL_H_
#define GAME_GENERAL_H_

#include "common.h"
#include "hal_display.h"
#include "game_objects.h"

// *********************************************************************
//                           MISC
// *********************************************************************

enum { UP, DOWN, LEFT, RIGHT };

// *********************************************************************
//                           Map
// *********************************************************************

#define GAME_MAP_WIDTH  16
#define GAME_MAP_HEIGHT 13

int gameMapObjectType[GAME_MAP_WIDTH*GAME_MAP_HEIGHT] =
{
//      0 1 2 3 4 5 6 7 8 9 101112131415
/*0 */  0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,
/*1 */	0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,
/*2 */	0,0,1,1,0,1,0,1,0,1,1,0,0,0,0,0,
/*3 */	0,1,1,0,0,1,0,1,0,0,1,1,1,1,1,0,
/*4 */	0,1,0,0,1,1,0,1,1,0,1,0,0,0,1,0,
/*5 */	1,1,0,1,1,0,0,0,1,0,3,0,5,0,1,0,
/*6 */	1,6,0,0,1,0,9,0,1,1,1,0,0,0,1,0,
/*7 */	1,0,2,0,1,0,0,0,1,0,1,0,1,1,1,0,
/*8 */	1,0,0,0,1,1,1,1,1,0,1,0,1,0,0,0,
/*9 */	1,1,1,1,1,0,8,0,1,1,1,0,1,0,0,0,
/*10*/	0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,
/*11*/	0,0,0,0,1,0,7,0,1,1,1,1,1,0,0,0,
/*12*/	0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0
};

int   gameMapObjectId[GAME_MAP_WIDTH*GAME_MAP_HEIGHT] =
{
//      0 1 2 3 4 5 6 7 8 9 101112131415
/*0 */	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
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

int gameHero_iBegin = 6;
int gameHero_jBegin = 6;

int prevHeroTileId = 0;
int prevHeroTileType = 0;

// *********************************************************************
//                           Prototypes
// *********************************************************************

int getGameMapType(int i, int j);
int getGameMapId(int i, int j);
void setGameMapType(int i, int j, int type);
void setGameMapId(int i, int j, int id);
void moveHero(int direction);
void setGameCurrentDisplay(int i, int j);

void upKey();
void downKey();
void leftKey();
void rightKey();

// *********************************************************************
//                           Macros
// *********************************************************************

#define getGameMapType(I,J) gameMapObjectType[(I) + (J)*GAME_MAP_WIDTH]
/*
int getGameMapType(int i, int j)
{
	return gameMapObjectType[i + j*GAME_MAP_WIDTH];
}
*/
#define getGameMapId(I,J) gameMapObjectId[(I) + (J)*GAME_MAP_WIDTH]
/*
int getGameMapId(int i, int j)
{
	return gameMapObjectId[i + j*GAME_MAP_WIDTH];
}
*/
#define setGameMapType(I,J,TYPE) gameMapObjectType[(I) + (J)*GAME_MAP_WIDTH] = (TYPE);
/*
void setGameMapType(int i, int j, int type)
{
	gameMapObjectType[i + j*GAME_MAP_WIDTH] = type;
}
*/
#define setGameMapId(I,J,ID) gameMapObjectId[(I) + (J)*GAME_MAP_WIDTH] = (ID);
/*
void setGameMapId(int i, int j, int id)
{
	gameMapObjectId[i + j*GAME_MAP_WIDTH] = id;
}
*/

#endif
