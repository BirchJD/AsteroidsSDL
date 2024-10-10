// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


#include <stdlib.h>
#include <SDL2/SDL.h>
#include "Number.hpp"
#include "Asteroids.hpp"



Number::Number()
{
   NumberValue = 0;
   xOffset = 0;
   yOffset = 0;
   Scale = 0;
}



Number::~Number()
{
}



void Number::Draw(SDL_Renderer* SdlRenderer)
{
   short Digit;
   short Count;
   ldiv_t Divide;
   long TempNumber;

  /*******************************/
 /* Plot current numeric value. */
/*******************************/
   TempNumber = NumberValue;
   SDL_SetRenderDrawColor(SdlRenderer, (TextColour >> 16) & 0xFF, (TextColour >> 8) & 0xFF, TextColour & 0xFF, 255);
   for (Digit = 0; Digit < 10; ++Digit)
   {
      Divide = div(TempNumber, (long)10);
      TempNumber = Divide.quot;
      for (Count = 0; Count < Decimal[Divide.rem][MAX_POINTS].x; ++Count)
      {
         DisplayFrame[Digit][Count].x = Decimal[Divide.rem][Count].x + xOffset + (10 - Digit) * 3*Scale;
         DisplayFrame[Digit][Count].y = Decimal[Divide.rem][Count].y + yOffset;
      }
      DisplayFrame[Digit][MAX_POINTS].x = Decimal[Divide.rem][MAX_POINTS].x;
		SDL_RenderDrawLines(SdlRenderer, DisplayFrame[Digit], DisplayFrame[Digit][MAX_POINTS].x);
   }
}



void Number::SetLocation(int NewxOffset, int NewyOffset, int NewScale, long NewTextColour)
{
   xOffset = NewxOffset;
   yOffset = NewyOffset;
   Scale = NewScale;
   TextColour = NewTextColour;

  /****************************************************/
 /* Create shapes for numbers at the specified size. */
/****************************************************/
// 0
   Decimal[0][MAX_POINTS].x = 6;
   Decimal[0][0].x = 2*Scale;
   Decimal[0][0].y = 0*Scale;
   Decimal[0][1].x = 0*Scale;
   Decimal[0][1].y = 0*Scale;
   Decimal[0][2].x = 0*Scale;
   Decimal[0][2].y = 4*Scale;
   Decimal[0][3].x = 2*Scale;
   Decimal[0][3].y = 4*Scale;
   Decimal[0][4].x = 2*Scale;
   Decimal[0][4].y = 0*Scale;
   Decimal[0][5].x = 0*Scale;
   Decimal[0][5].y = 4*Scale;
// 1
   Decimal[1][MAX_POINTS].x = 2;
   Decimal[1][0].x = 1*Scale;
   Decimal[1][0].y = 0*Scale;
   Decimal[1][1].x = 1*Scale;
   Decimal[1][1].y = 4*Scale;
// 2
   Decimal[2][MAX_POINTS].x = 6;
   Decimal[2][0].x = 0*Scale;
   Decimal[2][0].y = 0*Scale;
   Decimal[2][1].x = 2*Scale;
   Decimal[2][1].y = 0*Scale;
   Decimal[2][2].x = 2*Scale;
   Decimal[2][2].y = 2*Scale;
   Decimal[2][3].x = 0*Scale;
   Decimal[2][3].y = 2*Scale;
   Decimal[2][4].x = 0*Scale;
   Decimal[2][4].y = 4*Scale;
   Decimal[2][5].x = 2*Scale;
   Decimal[2][5].y = 4*Scale;
// 3
   Decimal[3][MAX_POINTS].x = 7;
   Decimal[3][0].x = 0*Scale;
   Decimal[3][0].y = 0*Scale;
   Decimal[3][1].x = 2*Scale;
   Decimal[3][1].y = 0*Scale;
   Decimal[3][2].x = 2*Scale;
   Decimal[3][2].y = 2*Scale;
   Decimal[3][3].x = 0*Scale;
   Decimal[3][3].y = 2*Scale;
   Decimal[3][4].x = 2*Scale;
   Decimal[3][4].y = 2*Scale;
   Decimal[3][5].x = 2*Scale;
   Decimal[3][5].y = 4*Scale;
   Decimal[3][6].x = 0*Scale;
   Decimal[3][6].y = 4*Scale;
// 4
   Decimal[4][MAX_POINTS].x = 5;
   Decimal[4][0].x = 0*Scale;
   Decimal[4][0].y = 0*Scale;
   Decimal[4][1].x = 0*Scale;
   Decimal[4][1].y = 2*Scale;
   Decimal[4][2].x = 2*Scale;
   Decimal[4][2].y = 2*Scale;
   Decimal[4][3].x = 2*Scale;
   Decimal[4][3].y = 0*Scale;
   Decimal[4][4].x = 2*Scale;
   Decimal[4][4].y = 4*Scale;
// 5
   Decimal[5][MAX_POINTS].x = 6;
   Decimal[5][0].x = 2*Scale;
   Decimal[5][0].y = 0*Scale;
   Decimal[5][1].x = 0*Scale;
   Decimal[5][1].y = 0*Scale;
   Decimal[5][2].x = 0*Scale;
   Decimal[5][2].y = 2*Scale;
   Decimal[5][3].x = 2*Scale;
   Decimal[5][3].y = 2*Scale;
   Decimal[5][4].x = 2*Scale;
   Decimal[5][4].y = 4*Scale;
   Decimal[5][5].x = 0*Scale;
   Decimal[5][5].y = 4*Scale;
// 6
   Decimal[6][MAX_POINTS].x = 6;
   Decimal[6][0].x = 2*Scale;
   Decimal[6][0].y = 0*Scale;
   Decimal[6][1].x = 0*Scale;
   Decimal[6][1].y = 0*Scale;
   Decimal[6][2].x = 0*Scale;
   Decimal[6][2].y = 4*Scale;
   Decimal[6][3].x = 2*Scale;
   Decimal[6][3].y = 4*Scale;
   Decimal[6][4].x = 2*Scale;
   Decimal[6][4].y = 2*Scale;
   Decimal[6][5].x = 0*Scale;
   Decimal[6][5].y = 2*Scale;
// 7
   Decimal[7][MAX_POINTS].x = 3;
   Decimal[7][0].x = 0*Scale;
   Decimal[7][0].y = 0*Scale;
   Decimal[7][1].x = 2*Scale;
   Decimal[7][1].y = 0*Scale;
   Decimal[7][2].x = 2*Scale;
   Decimal[7][2].y = 4*Scale;
// 8
   Decimal[8][MAX_POINTS].x = 7;
   Decimal[8][0].x = 0*Scale;
   Decimal[8][0].y = 0*Scale;
   Decimal[8][1].x = 2*Scale;
   Decimal[8][1].y = 0*Scale;
   Decimal[8][2].x = 2*Scale;
   Decimal[8][2].y = 4*Scale;
   Decimal[8][3].x = 0*Scale;
   Decimal[8][3].y = 4*Scale;
   Decimal[8][4].x = 0*Scale;
   Decimal[8][4].y = 0*Scale;
   Decimal[8][5].x = 0*Scale;
   Decimal[8][5].y = 2*Scale;
   Decimal[8][6].x = 2*Scale;
   Decimal[8][6].y = 2*Scale;
// 9
   Decimal[9][MAX_POINTS].x = 6;
   Decimal[9][0].x = 0*Scale;
   Decimal[9][0].y = 4*Scale;
   Decimal[9][1].x = 2*Scale;
   Decimal[9][1].y = 4*Scale;
   Decimal[9][2].x = 2*Scale;
   Decimal[9][2].y = 0*Scale;
   Decimal[9][3].x = 0*Scale;
   Decimal[9][3].y = 0*Scale;
   Decimal[9][4].x = 0*Scale;
   Decimal[9][4].y = 2*Scale;
   Decimal[9][5].x = 2*Scale;
   Decimal[9][5].y = 2*Scale;
}



long Number::GetNumber()
{
   return NumberValue;
}



void Number::SetNumber(long NewNumber)
{
   NumberValue = NewNumber;
}
