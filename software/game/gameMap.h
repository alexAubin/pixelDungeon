/********************************

          Pixel Dungeon
           by Djidane

      Map class for the game

********************************/

/**
 *	@author Djidane
 * 	@file gameMap.h
 *  @brief Map-of the game management class
 */

#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#include "gameCommon.h"

class gameMap
{
	private:

		gameMap layer1;
		gameMap layer0;

		int positionCurrentDisplay_x;
		int positionCurrentDisplay_y;

	public:

		// Constructor
		gameMap();

		// Destructor
		~gameMap();

		gameObject::Color getColor(int x, int y);

		bool isTileVisibleByHero(int x,int y);

		void triggerAction(int x, int y);

		void updateCornerCurrentDisplay();

		void setGameCurrentDisplay(int x, int y);
};

#endif
