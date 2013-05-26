
/********************************

          Pixel Dungeon
           by Djidane

         Main functions

********************************/

/**
 *	@author Djidane
 * 	@file main.pde
 *  @brief Main functions
 */

#include "common.h"

// *********************************************************************

void setup()
{
	initDisplay();
	initKeys();
	initGame();
	initTimer();
}

// *********************************************************************

void loop()
{
	displayRefreshNextPixel();
}

// *********************************************************************

void initTimer()
{
	Timer1.initialize(100000);
	Timer1.attachInterrupt(timerInterrupt);
}

void timerInterrupt()
{
	//delay(1000);
}
