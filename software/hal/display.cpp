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
 *  @brief  Display-related functions
*/

#include "hal/display.h"

// *********************************************************************

int currentDisplay[DISPLAY_NPIX] =
{
   7, 7, 0, 2, 2, 0, 8, 8,
   7, 7, 0, 2, 2, 0, 8, 8,
   0, 0, 0, 0, 0, 0, 0, 0,
  10,10, 0, 6, 6, 0, 5, 5,
  10,10, 0, 6, 6, 0, 5, 5,
   0, 0, 0, 0, 0, 0, 0, 0,
   4, 4, 0, 9, 9, 0, 3, 3,
   4, 4, 0, 9, 9, 0, 3, 3
};

// *********************************************************************

int currentPixel = 1;

void initDisplay()
{
  // initialize the digital pin as an output.

  pinMode(X0, OUTPUT);
  pinMode(X1, OUTPUT);
  pinMode(X2, OUTPUT);
  pinMode(Y0, OUTPUT);
  pinMode(Y1, OUTPUT);
  pinMode(Y2, OUTPUT);

  pinMode(REDLED, OUTPUT);
  pinMode(GREENLED, OUTPUT);
  pinMode(BLUELED, OUTPUT);

  // set led display off

  digitalWrite(REDLED, LOW);
  digitalWrite(GREENLED, LOW);
  digitalWrite(BLUELED, LOW);
}

void displayRefreshNextPixel()
{

  currentPixel++;
  if (currentPixel == DISPLAY_NPIX) currentPixel = 0;

  int color = currentDisplay[currentPixel];
  if (color == DISPLAYCOLOR_EMPTY) return;

  digitalWrite(X0, bitRead(currentPixel,0));
  digitalWrite(X1, bitRead(currentPixel,1));
  digitalWrite(X2, bitRead(currentPixel,2));
  digitalWrite(Y0, bitRead(currentPixel,3));
  digitalWrite(Y1, bitRead(currentPixel,4));
  digitalWrite(Y2, bitRead(currentPixel,5));

  displayColor(color);

}

void displayColor(int color)
{
    if (color == DISPLAYCOLOR_WHITE)
    {
      digitalWrite(REDLED, HIGH);
      digitalWrite(GREENLED, HIGH);
      digitalWrite(BLUELED, HIGH);
	  PRINTCOLOR_WAIT_UNIT;
	  PRINTCOLOR_WAIT_UNIT;
	  digitalWrite(REDLED, LOW);
	  digitalWrite(BLUELED, LOW);
	  digitalWrite(GREENLED, LOW);
    }
    else if (color == DISPLAYCOLOR_RED)
    {
      digitalWrite(REDLED, HIGH);
      PRINTCOLOR_WAIT_UNIT;
     // PRINTCOLOR_WAIT_UNIT;
      digitalWrite(REDLED, LOW);
    }
    else if (color == DISPLAYCOLOR_GREEN)
    {
      digitalWrite(GREENLED, HIGH);
      PRINTCOLOR_WAIT_UNIT;
      PRINTCOLOR_WAIT_UNIT;
      digitalWrite(GREENLED, LOW);
    }
    else if (color == DISPLAYCOLOR_BLUE)
    {
      digitalWrite(BLUELED, HIGH);
      PRINTCOLOR_WAIT_UNIT;
      PRINTCOLOR_WAIT_UNIT;
      digitalWrite(BLUELED, LOW);
    }
    else if (color == DISPLAYCOLOR_YELLOW)
    {
      digitalWrite(REDLED, HIGH);
      digitalWrite(GREENLED, HIGH);
      PRINTCOLOR_WAIT_UNIT;
      PRINTCOLOR_WAIT_UNIT;
      digitalWrite(REDLED, LOW);
      digitalWrite(GREENLED, LOW);
    }
    else if (color == DISPLAYCOLOR_MAGENTA)
    {
      digitalWrite(BLUELED, HIGH);
      digitalWrite(REDLED, HIGH);
      PRINTCOLOR_WAIT_UNIT;
      digitalWrite(BLUELED, LOW);
      PRINTCOLOR_WAIT_UNIT;
      digitalWrite(REDLED, LOW);
    }
    else if (color == DISPLAYCOLOR_CYAN)
    {
      digitalWrite(GREENLED, HIGH);
      digitalWrite(BLUELED, HIGH);
      PRINTCOLOR_WAIT_UNIT;
      PRINTCOLOR_WAIT_UNIT;
      digitalWrite(GREENLED, LOW);
      digitalWrite(BLUELED, LOW);
    }
    else if (color == DISPLAYCOLOR_ORANGE)
    {
      digitalWrite(REDLED, HIGH);
      digitalWrite(GREENLED, HIGH);
     PRINTCOLOR_WAIT_UNIT;
      digitalWrite(GREENLED, LOW);
     PRINTCOLOR_WAIT_UNIT;
      digitalWrite(REDLED, LOW);
    }
    else if (color == DISPLAYCOLOR_VIOLET)
    {
	  digitalWrite(BLUELED, HIGH);
      digitalWrite(REDLED, HIGH);
      PRINTCOLOR_WAIT_UNIT;
      digitalWrite(REDLED, LOW);
      PRINTCOLOR_WAIT_UNIT;
	  digitalWrite(BLUELED, LOW);
    }
    else if (color == DISPLAYCOLOR_KINGBLUE)
    {
      digitalWrite(BLUELED, HIGH);
      digitalWrite(GREENLED, HIGH);
      PRINTCOLOR_WAIT_UNIT;
      digitalWrite(GREENLED, LOW);
      PRINTCOLOR_WAIT_UNIT;
      digitalWrite(BLUELED, LOW);
    }
}
