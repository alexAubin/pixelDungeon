/*
 ##############################################################################
 #                                                                            #
 #    This file is part of PixelDungeon.                                      #
 #                                                                            #
 #    PixelDungeon is free software: you can redistribute it and/or modify    #
 #    it under the terms of the GNU General Public License as published by    #
 #    the Free Software Foundation, either version 3 of the License, or       #
 #     (at your option) any later version.                                    #
 #                                                                            #
 #    PixelDungeon is distributed in the hope that it will be useful,         #
 #    but WITHOUT ANY WARRANTY; without even the implied warranty of          #
 #    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           #
 #    GNU General Public License for more details.                            #
 #                                                                            #
 #    You should have received a copy of the GNU General Public License       #
 #    along with PixelDungeon.  If not, see <http://www.gnu.org/licenses/>.   #
 #                                                                            #
 ##############################################################################
*/

/**
 *	@author Alexandre Aubin
 *  @brief  Keys management functions
*/

#include "hal/keys.h"

// *********************************************************************
//  		Include / defines for pinChangeInterrupt utilization
// *********************************************************************

#define NO_PORTB_PINCHANGES
#define NO_PORTC_PINCHANGES

#define PINMODE
#define FLASH

#include "lib/pinChangeInt/ByteBuffer.h"
#include "lib/pinChangeInt/PinChangeInt.h"


void upInterruptHandler()
{
	if (digitalRead(UP_KEY)) return;
    //delay(200);
    //if (digitalRead(UP_KEY)) return;

    theGame.upKey();
}

void downInterruptHandler()
{
	if (digitalRead(DOWN_KEY)) return;
    //delay(200);
    //if (digitalRead(DOWN_KEY)) return;

    theGame.downKey();
}

void leftInterruptHandler()
{
	if (digitalRead(LEFT_KEY)) return;
    //delay(200);
    //if (digitalRead(LEFT_KEY)) return;

    theGame.leftKey();
}

void rightInterruptHandler()
{
	if (digitalRead(RIGHT_KEY)) return;
    //delay(200);
    //if (digitalRead(RIGHT_KEY)) return;

    theGame.rightKey();
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
