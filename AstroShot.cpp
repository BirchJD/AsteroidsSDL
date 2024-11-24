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


#include "AstroShot.hpp"


AstroShot::AstroShot()
{
   xMax = 0;
   yMax = 0;
   xOffset = HYPERSPACE;
   yOffset = HYPERSPACE;
   xVelocity = (float)0;
   yVelocity = (float)0;
   Size = SMALL_SHOT;
   FrameCount = 0;
}



AstroShot::~AstroShot()
{
}



void AstroShot::Draw(SDL_Renderer* SdlRenderer)
{
   SDL_Rect Rect;

   if (FrameCount)
   {
      if (Size == SMALL_SHOT)
         Rect = (SDL_Rect){ xOffset, yOffset, 2, 2 };
      else
         Rect = (SDL_Rect){ xOffset, yOffset, 4, 4 };
      SDL_SetRenderDrawColor(SdlRenderer, (COLOUR_SHOT >> 16) & 0xFF, (COLOUR_SHOT >> 8) & 0xFF, COLOUR_SHOT & 0xFF, 255);
      SDL_RenderFillRect(SdlRenderer, &Rect);
   }
}



void AstroShot::Move()
{
   if (FrameCount)
   {
      if (xOffset < 0)
         xOffset = xMax;
      else if (xOffset > xMax)
         xOffset = 0;
      if (yOffset < 0)
         yOffset = yMax;
      else if (yOffset > yMax)
         yOffset = 0;
      xOffset += (short)xVelocity;
      yOffset += (short)yVelocity;
      --FrameCount;
   }
}



void AstroShot::SetArea(int NewxMax, int NewyMax, int NewxOffset, int NewyOffset, float NewxVelocity, float NewyVelocity, int NewSize)
{
   xMax = NewxMax;
   yMax = NewyMax;
   xOffset = NewxOffset;
   yOffset = NewyOffset;
   xVelocity = NewxVelocity;
   yVelocity = NewyVelocity;
   Size = NewSize;
   if (Size == LARGE_SHOT)
      FrameCount = LARGE_SHOT_FRAMES;
   else
      FrameCount = SMALL_SHOT_FRAMES;
}



short AstroShot::GetXOffset()
{
   return xOffset;
}



short AstroShot::GetYOffset()
{
   return yOffset;
}



void AstroShot::Destroy()
{
   FrameCount = false;
   xOffset = HYPERSPACE;
   yOffset = HYPERSPACE;
}



short AstroShot::Active()
{
   return FrameCount;
}
