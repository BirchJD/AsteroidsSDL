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


#ifndef __BUTTON_HPP
#define __BUTTON_HPP


#include "Common.hpp"
#include "Text.hpp"


class Button
{
   public:
      enum
      {
         FRAME_POINTS = 5,
      };

      void SetLocation(unsigned short xPos, unsigned short yPos, unsigned short xLen, unsigned short yLen, const char* Text, long NewColour);
      short GetVisible();
      void SetVisible(short NewVisible);
      short CheckClick(int xClick, int yClick);
      void Draw(SDL_Renderer* SdlRenderer);

   private:
      short Visible;
      unsigned short xPos;
      unsigned short yPos;
      unsigned short xLen;
      unsigned short yLen;
      long Colour;
      Text ButtonText;
      SDL_Point DisplayFrame[FRAME_POINTS];
};


#endif
