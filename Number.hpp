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


#ifndef __NUMBER_HPP
#define __NUMBER_HPP


#include "Common.hpp"


class Number
{
   public:
      enum 
      {
         DIGITS = 10,
         MAX_POINTS = 10,
      };

      Number();
      ~Number();
      void Draw(SDL_Renderer* SdlRenderer);
      void SetLocation(int NewxOffset, int NewyOffset, int NewScale, long NewTextColour);
      long GetNumber();
      void SetNumber(long NewNumber);

   private:
      int xOffset;
      int yOffset;
      int Scale;
	  	int Width;
      long TextColour;
      long NumberValue;
      SDL_Point Decimal[DIGITS][MAX_POINTS+1];
      SDL_Point DisplayFrame[DIGITS][MAX_POINTS+1];
};


#endif
