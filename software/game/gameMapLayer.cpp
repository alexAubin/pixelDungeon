/********************************

          Pixel Dungeon
           by Djidane


     Game map layer methods

********************************/

/**
 *	@author Djidane
 * 	@file gameMapLayer.cpp
 *  @brief Game map layer methods
 */

#include "gameMapLayer.h"

gameObject::Color gameMapLayer::getColor(int x, int y)
{
	return layer[x*GAME_MAP_WIDTH + y]->getColor();
}

gameObject::Type  gameMapLayer::getType(int x, int y)
{
	return layer[x*GAME_MAP_WIDTH + y]->getType();
}
