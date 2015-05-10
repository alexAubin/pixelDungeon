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
 *  @author Alexandre Aubin
 *  @brief  Display-related functions
*/

#include "hal/display.h"

// *********************************************************************

#define NUMBER_OF_COLOR_LEVELS 4

short int currentDisplay[DISPLAY_NPIX] =
{
   0b000000, 0b000100, 0b001000, 0b001100, 0b010000, 0b010100, 0b011000, 0b011100,
   0b000001, 0b000101, 0b001001, 0b001101, 0b010001, 0b010101, 0b011001, 0b011101,
   0b000010, 0b000110, 0b001010, 0b001110, 0b010010, 0b010110, 0b011010, 0b011110,
   0b000011, 0b000111, 0b001011, 0b001111, 0b010011, 0b010111, 0b011011, 0b011111,
   0b100000, 0b100100, 0b101000, 0b101100, 0b110000, 0b110100, 0b111000, 0b111100,
   0b100001, 0b100101, 0b101001, 0b101101, 0b110001, 0b110101, 0b111001, 0b111101,
   0b100010, 0b100110, 0b101010, 0b101110, 0b110010, 0b110110, 0b111010, 0b111110,
   0b100011, 0b100111, 0b101011, 0b101111, 0b110011, 0b110111, 0b111011, 0b111111,

/*
   0b000000, 0b000000, 0b000000, 0b000000, 0b000000, 0b000000, 0b000000, 0b000000,
   0b000000, 0b000000, 0b000000, 0b000000, 0b000000, 0b001100, 0b001100, 0b000000,
   0b000000, 0b000000, 0b000000, 0b000000, 0b000000, 0b001100, 0b001100, 0b000000,
   0b000000, 0b000000, 0b000000, 0b000000, 0b000000, 0b000000, 0b000000, 0b000000,
   0b000000, 0b000000, 0b000000, 0b000000, 0b000000, 0b000000, 0b000000, 0b000000,
   0b000000, 0b110000, 0b110000, 0b000000, 0b000000, 0b000011, 0b000011, 0b000000,
   0b000000, 0b110000, 0b110000, 0b000000, 0b000000, 0b000011, 0b000011, 0b000000,
   0b000000, 0b000000, 0b000000, 0b000000, 0b000000, 0b000000, 0b000000, 0b000000,
*/

};

short int displayCopy[DISPLAY_NPIX];

// *********************************************************************
inline void shiftCurrentColumn()  { digitalWrite(HAL_ANODE_SHIFT_PIN,  HIGH); digitalWrite(HAL_ANODE_SHIFT_PIN,  LOW); }
inline void shiftCurrentColor()   { digitalWrite(HAL_COLOR_SHIFT_PIN,  HIGH); digitalWrite(HAL_COLOR_SHIFT_PIN,  LOW); }
inline void updateCurrentColumn() { digitalWrite(HAL_ANODE_UPDATE_PIN, HIGH); digitalWrite(HAL_ANODE_UPDATE_PIN, LOW); }
inline void updateCurrentColor()  { digitalWrite(HAL_COLOR_UPDATE_PIN, HIGH); digitalWrite(HAL_COLOR_UPDATE_PIN, LOW); }

void initDisplay()
{
  // set pins as outputs, and set them to be inactive (LOW for anode, HIGH for colors).

  pinMode(HAL_ANODE_INPUT_PIN,  OUTPUT);  digitalWrite(HAL_ANODE_INPUT_PIN,  LOW);
  pinMode(HAL_RED_INPUT_PIN,    OUTPUT);  digitalWrite(HAL_RED_INPUT_PIN,    HIGH);
  pinMode(HAL_GREEN_INPUT_PIN,  OUTPUT);  digitalWrite(HAL_GREEN_INPUT_PIN,  HIGH);
  pinMode(HAL_BLUE_INPUT_PIN,   OUTPUT);  digitalWrite(HAL_BLUE_INPUT_PIN,   HIGH);

  pinMode(HAL_ANODE_SHIFT_PIN,  OUTPUT);  digitalWrite(HAL_ANODE_SHIFT_PIN,  LOW );
  pinMode(HAL_COLOR_SHIFT_PIN,  OUTPUT);  digitalWrite(HAL_COLOR_SHIFT_PIN,  LOW );
  pinMode(HAL_ANODE_UPDATE_PIN, OUTPUT);  digitalWrite(HAL_ANODE_UPDATE_PIN, LOW );
  pinMode(HAL_COLOR_UPDATE_PIN, OUTPUT);  digitalWrite(HAL_COLOR_UPDATE_PIN, LOW );

  // Shift and update the whole register with init values
  for (int i = 0 ; i < DISPLAY_WIDTH ; i++)
  {
        shiftCurrentColumn();
        shiftCurrentColor();
  }
  updateCurrentColumn();
  updateCurrentColor();

}

void display()
{

    // Make a copy of current display
    for (int p = 0 ; p < DISPLAY_NPIX ; p++)
    {
        displayCopy[p] = currentDisplay[p];
    }

    // Loop on columns
    for (int c = 0 ; c < DISPLAY_WIDTH ; c++)
    {
        if (c == 0)
        {
            digitalWrite(HAL_ANODE_INPUT_PIN,  HIGH);
            shiftCurrentColumn();
            digitalWrite(HAL_ANODE_INPUT_PIN,  LOW);
        }
        else
            shiftCurrentColumn();

        // Loop on color levels : same color is updated multiple time,
        // to vary the color composition and obtain things like 1 red + 0.25 blue + 0.5 green
        for (int l = 0 ; l < NUMBER_OF_COLOR_LEVELS ; l++)
        {
            // Loop on row, or pixels, inside the column
            for (int r = 0 ; r < DISPLAY_WIDTH ; r++)
            {
                // Decompose color in red, green and blue
                short int pixelColor = displayCopy[c * DISPLAY_WIDTH + r];
                bool red   = (bitRead(pixelColor,4) + bitRead(pixelColor,5) > 0);
                bool blue  = (bitRead(pixelColor,0) + bitRead(pixelColor,1) > 0);

                // For green, we gotta do it in reverse order because of hardware mapping
                short int pixelColor2 = displayCopy[(c+1) * DISPLAY_WIDTH - r - 1];
                bool green = (bitRead(pixelColor2,2) + bitRead(pixelColor2,3) > 0);

                // Put this on the pin
                digitalWrite(HAL_RED_INPUT_PIN,   red   ? LOW : HIGH);
                digitalWrite(HAL_GREEN_INPUT_PIN, green ? LOW : HIGH);
                digitalWrite(HAL_BLUE_INPUT_PIN,  blue  ? LOW : HIGH);

                // Shift the color in register
                shiftCurrentColor();

                // Remove one unit of each color used
                displayCopy[ c    * DISPLAY_WIDTH + r    ] -= (blue * 1) + (red * 16);
                displayCopy[(c+1) * DISPLAY_WIDTH - r - 1] -= (green * 4);
            }

            //delay(1000);
            // Update the display of the column
            updateCurrentColumn();
            updateCurrentColor();
        }
    }

    shiftCurrentColumn();
    updateCurrentColumn();
    return;

}
