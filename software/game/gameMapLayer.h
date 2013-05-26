/********************************

          Pixel Dungeon
           by Djidane


     Game map layer definition

********************************/

/**
 *	@author Djidane
 * 	@file gameMapLayer.h
 *  @brief Game map layer definition
 */

#ifndef GAME_MAP_LAYER_H_
#define GAME_MAP_LAYER_H_

#include "gameCommon.h"
#include "gameObject.h"

class gameMapLayer
{
	private:

		gameObject* layer[GAME_MAP_WIDTH * GAME_MAP_HEIGHT];

	public:

		// Constructor
		gameMapLayer();

		// Destructor
		~gameMapLayer();

		gameObject::Color getColor(int x, int y);

		gameObject::Type getType(int x, int y);
};

#endif
