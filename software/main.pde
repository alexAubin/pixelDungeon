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
 *  @brief Main functions
*/

#include "common.h"

// *********************************************************************

extern int __bss_end;
extern int* __brkval;

int get_free_memory()
{
    int free_memory;

    if((int)__brkval == 0)
        free_memory = ((int)&free_memory) - ((int)&__bss_end);
    else
        free_memory = ((int)&free_memory) - ((int)__brkval);

    return free_memory;
}




void setup()
{

    #ifdef DEBUG
        Serial.begin(9600);
        Serial.println(" ");
        Serial.println(" > Starting ... ");
        Serial.println(" Init display ");
    #endif
    
    initDisplay();

    #ifdef DEBUG
        Serial.println(" Init keys ");
    #endif
  
    initKeys();

    #ifdef DEBUG
        Serial.println(" Init game ");
    #endif

    initGame();

    #ifdef DEBUG
        Serial.println(" Init timers ");
        delay(1000);
    #endif

    initTimer();

    #ifdef DEBUG
        Serial.println(" > Success. Waitin for inputs. ");
    #endif

	
}

// *********************************************************************

void loop()
{
	displayRefreshNextPixel();
}

// *********************************************************************

void initTimer()
{
	Timer1.initialize(1000000);
	Timer1.attachInterrupt(gameTimerHandler);
}

