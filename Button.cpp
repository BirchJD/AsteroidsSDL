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


#include "Button.hpp"


void Button::SetLocation(unsigned short NewXPos, unsigned short NewYPos, unsigned short NewXLen, unsigned short NewYLen, const char* Text, long NewColour)
{
   Visible = false;
   xPos = NewXPos;
   yPos = NewYPos;
   xLen = NewXLen;
   yLen = NewYLen;
   Colour = NewColour;
   ButtonText.SetLocation(xPos + (xLen - strlen(Text) * TEXT_SCALE * Text::TEXT_X_UNITS) / 2, yPos + (yLen - TEXT_SCALE * Text::TEXT_Y_UNITS) / 2, TEXT_SCALE, 0, false, Text, Colour);
   ButtonText.SetVisible(true);
   DisplayFrame[0].x = xPos;
   DisplayFrame[0].y = yPos;
   DisplayFrame[1].x = xPos + xLen - 1;
   DisplayFrame[1].y = yPos;
   DisplayFrame[2].x = xPos + xLen - 1;
   DisplayFrame[2].y = yPos + yLen - 1;
   DisplayFrame[3].x = xPos;
   DisplayFrame[3].y = yPos + yLen - 1;
   DisplayFrame[4].x = xPos;
   DisplayFrame[4].y = yPos;
}


short Button::GetVisible()
{
   return Visible;
}



void Button::SetVisible(short NewVisible)
{
   Visible = NewVisible;
}



void Button::Draw(SDL_Renderer* SdlRenderer)
{
   short Count;

   if (Visible)
   {
      SDL_SetRenderDrawColor(SdlRenderer, (Colour >> 16) & 0xFF, (Colour >> 8) & 0xFF, Colour & 0xFF, 255);
      SDL_RenderDrawLines(SdlRenderer, DisplayFrame, FRAME_POINTS);
      ButtonText.Draw(SdlRenderer);
   }
}


short Button::CheckClick(int xClick, int yClick)
{
   return (xClick > xPos && xClick < xPos + xLen && yClick > yPos && yClick < yPos + yLen);
}
