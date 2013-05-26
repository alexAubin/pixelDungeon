
/********************************

          Pixel Dungeon
           by Djidane

    Display-related definitions

********************************/

/**
 *	@author Djidane
 * 	@file halDisplay.h
 *  @brief Display-related definitions
 */

#ifndef HAL_DISPLAY_H_
#define HAL_DISPLAY_H_

#include "common.h"

// *********************************************************************
//                         Misc
// *********************************************************************

#define DISPLAY_WIDTH 8
#define DISPLAY_NPIX DISPLAY_WIDTH*DISPLAY_WIDTH

// *********************************************************************
//                         Colors
// *********************************************************************

#define EMPTY_ID    0
#define WHITE_ID    1
#define RED_ID      2
#define GREEN_ID    3
#define BLUE_ID     4
#define YELLOW_ID   5
#define MAGENTA_ID  6
#define CYAN_ID     7
#define ORANGE_ID   8
#define VIOLET_ID   9
#define KINGBLUE_ID 10

// *********************************************************************
//                         		Misc
// *********************************************************************

#define PRINTCOLOR_WAIT_UNIT delayMicroseconds(150)

// *********************************************************************
//                         IO config (pin numbers)
// *********************************************************************

#define X0 A0
#define X1 A1
#define X2 A2
#define Y0 A3
#define Y1 A4
#define Y2 A5

#define REDLED   11
#define GREENLED 12
#define BLUELED  13

// *********************************************************************
//                           Current display
// *********************************************************************

extern int currentPixel;
extern int currentDisplay[DISPLAY_NPIX];

// *********************************************************************
//                           Prototypes
// *********************************************************************


void displayRefreshNextPixel();
void displayColor(int color);

#endif
