
/********************************

          Pixel Dungeon
           by Djidane

       General definitions

********************************/

/**
 *	@author Djidane
 * 	@file common.h
 *  @brief General definitions
 */


#ifndef COMMON_H_
#define COMMON_H_

#include <Arduino.h>
#include "lib/TimerOne/TimerOne.h"

// *********************************************************************
//                         Prototypes
// *********************************************************************

void initDisplay();
void initKeys();
void initGame();

void displayRefreshNextPixel();

void updateCornerCurrentDisplay();

void initTimer();
void timerInterrupt();

// *********************************************************************

#endif
