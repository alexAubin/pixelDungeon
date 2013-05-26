/********************************

          Pixel Dungeon
           by Djidane

     Game-management class

********************************/

/**
 *	@author Djidane
 * 	@file gameManager.h
 *  @brief Game-management class
 */

#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_

#include "gameCommon.h"

class gameManager
{
	private:

	// Attributes

		gameMap	theMap;

		gameObject*	theObjectCollection[THEGAME_TOTALNUMBEROFOBJECTS];

		gameObject_Hero theHero;


	// Methods

		// Constructor
		gameManager();

		// Destructor
		~gameManager();

		void init();

		void moveHero(int direction);

	public:

		// Interface with rest of the program

		void upKey() 	{ moveHero(UP); }
		void downKey() 	{ moveHero(DOWN); }
		void rightKey() { moveHero(RIGHT); }
		void leftKey() 	{ moveHero(LEFT); }

};

gameManager theGame;

void initGame() { theGame.init() };

#endif
