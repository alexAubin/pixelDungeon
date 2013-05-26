
/********************************

          Pixel Dungeon
           by Djidane

    Keys management functions

********************************/

/**
 *	@author Djidane
 * 	@file halKeys.cpp
 *  @brief Keys management functions
 */

#include "hal_keys.h"

void upInterruptHandler()
{
	if (digitalRead(UP_KEY)) return;
    //delay(200);
    //if (digitalRead(UP_KEY)) return;

    upKey();
}

void downInterruptHandler()
{
	if (digitalRead(DOWN_KEY)) return;
    //delay(200);
    //if (digitalRead(DOWN_KEY)) return;

    downKey();
}

void leftInterruptHandler()
{
	if (digitalRead(LEFT_KEY)) return;
    //delay(200);
    //if (digitalRead(LEFT_KEY)) return;

    leftKey();
}

void rightInterruptHandler()
{
	if (digitalRead(RIGHT_KEY)) return;
    //delay(200);
    //if (digitalRead(RIGHT_KEY)) return;

    rightKey();
}



void initKeys()
{
	pinMode(UP_KEY, INPUT); digitalWrite(UP_KEY, HIGH);
	pinMode(DOWN_KEY, INPUT); digitalWrite(DOWN_KEY, HIGH);
	pinMode(LEFT_KEY, INPUT); digitalWrite(LEFT_KEY, HIGH);
	pinMode(RIGHT_KEY, INPUT); digitalWrite(RIGHT_KEY, HIGH);

	PCintPort::attachInterrupt(UP_KEY, &upInterruptHandler, FALLING);
	PCintPort::attachInterrupt(DOWN_KEY, &downInterruptHandler, FALLING);
	PCintPort::attachInterrupt(LEFT_KEY, &leftInterruptHandler, FALLING);
	PCintPort::attachInterrupt(RIGHT_KEY, &rightInterruptHandler, FALLING);
}
