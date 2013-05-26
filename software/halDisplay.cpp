
/********************************

          Pixel Dungeon
           by Djidane

    Display-related functions

********************************/

/**
 *	@author Djidane
 * 	@file halDisplay.cpp
 *  @brief Display-related functions
 */

 #include "halDisplay.h"

// *********************************************************************

/*
int currentDisplay[DISPLAY_NPIX] =
{
   4, 4, 0, 4, 4, 0, 4, 4,
   4, 4, 0, 4, 4, 0, 4, 4,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 4, 4,
   0, 0, 0, 0, 0, 0, 4, 4,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 4, 4, 0, 0, 0,
   0, 0, 0, 4, 4, 0, 0, 0
};*/


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

/*
int currentDisplay[DISPLAY_NPIX] =
{
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 2, 2, 0, 0, 0,
   0, 0, 2, 2, 2, 2, 0, 0,
   0, 2, 2, 2, 2, 2, 2, 0,
   2, 2, 2, 2, 2, 2, 2, 2,
   2, 2, 2, 2, 2, 2, 2, 2,
   2, 2, 2, 2, 2, 2, 2, 2,
   0, 2, 2, 0, 0, 2, 2, 0
};*/

/*
int currentDisplay[DISPLAY_NPIX] =
{
   0, 0, 0, 4, 4, 0, 0, 0,
   0, 0, 3, 3, 3, 3, 0, 0,
   0, 3, 2, 2, 2, 2, 3, 0,
   4, 3, 2, 1, 1, 2, 3, 4,
   4, 3, 2, 1, 1, 2, 3, 4,
   0, 3, 2, 2, 2, 2, 3, 0,
   0, 0, 3, 3, 3, 3, 0, 0,
   0, 0, 0, 4, 4, 0, 0, 0
};*/

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
  if (color == EMPTY_ID) return;

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
    if (color == WHITE_ID)
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
    else if (color == RED_ID)
    {
      digitalWrite(REDLED, HIGH);
      PRINTCOLOR_WAIT_UNIT;
     // PRINTCOLOR_WAIT_UNIT;
      digitalWrite(REDLED, LOW);
    }
    else if (color == GREEN_ID)
    {
      digitalWrite(GREENLED, HIGH);
      PRINTCOLOR_WAIT_UNIT;
      PRINTCOLOR_WAIT_UNIT;
      digitalWrite(GREENLED, LOW);
    }
    else if (color == BLUE_ID)
    {
      digitalWrite(BLUELED, HIGH);
      PRINTCOLOR_WAIT_UNIT;
      PRINTCOLOR_WAIT_UNIT;
      digitalWrite(BLUELED, LOW);
    }
    else if (color == YELLOW_ID)
    {
      digitalWrite(REDLED, HIGH);
      digitalWrite(GREENLED, HIGH);
      PRINTCOLOR_WAIT_UNIT;
      PRINTCOLOR_WAIT_UNIT;
      digitalWrite(REDLED, LOW);
      digitalWrite(GREENLED, LOW);
    }
    else if (color == MAGENTA_ID)
    {
      digitalWrite(BLUELED, HIGH);
      digitalWrite(REDLED, HIGH);
      PRINTCOLOR_WAIT_UNIT;
      digitalWrite(BLUELED, LOW);
      PRINTCOLOR_WAIT_UNIT;
      digitalWrite(REDLED, LOW);
    }
    else if (color == CYAN_ID)
    {
      digitalWrite(GREENLED, HIGH);
      digitalWrite(BLUELED, HIGH);
      PRINTCOLOR_WAIT_UNIT;
      PRINTCOLOR_WAIT_UNIT;
      digitalWrite(GREENLED, LOW);
      digitalWrite(BLUELED, LOW);
    }
    else if (color == ORANGE_ID)
    {
      digitalWrite(REDLED, HIGH);
      digitalWrite(GREENLED, HIGH);
     PRINTCOLOR_WAIT_UNIT;
      digitalWrite(GREENLED, LOW);
     PRINTCOLOR_WAIT_UNIT;
      digitalWrite(REDLED, LOW);
    }
    else if (color == VIOLET_ID)
    {
	  digitalWrite(BLUELED, HIGH);
      digitalWrite(REDLED, HIGH);
      PRINTCOLOR_WAIT_UNIT;
      digitalWrite(REDLED, LOW);
      PRINTCOLOR_WAIT_UNIT;
	  digitalWrite(BLUELED, LOW);
    }
    else if (color == KINGBLUE_ID)
    {
      digitalWrite(BLUELED, HIGH);
      digitalWrite(GREENLED, HIGH);
      PRINTCOLOR_WAIT_UNIT;
      digitalWrite(GREENLED, LOW);
      PRINTCOLOR_WAIT_UNIT;
      digitalWrite(BLUELED, LOW);
    }
}
