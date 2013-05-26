
/********************************

          Pixel Dungeon
           by Djidane

    Keys management definitions

********************************/

/**
 *	@author Djidane
 * 	@file halKeys.h
 *  @brief Keys management definitions
 */

#ifndef HAL_KEYS_H_
#define HAL_KEYS_H_

#include "common.h"

// *********************************************************************
//  		Include / defines for pinChangeInterrupt utilization
// *********************************************************************

#define NO_PORTB_PINCHANGES
#define NO_PORTC_PINCHANGES

#define PINMODE
#define FLASH

#include "lib/pinChangeInt/ByteBuffer.h"
#include "lib/pinChangeInt/PinChangeInt.h"

// *********************************************************************
//                         IO config (pin numbers)
// *********************************************************************

#define UP_KEY 4
#define DOWN_KEY 3
#define LEFT_KEY 5
#define RIGHT_KEY 2

// *********************************************************************
//                           Prototypes
// *********************************************************************

void upInterruptHandler();
void downInterruptHandler();
void leftInterruptHandler();
void rightInterruptHandler();

extern void upKey();
extern void downKey();
extern void leftKey();
extern void rightKey();

#endif
