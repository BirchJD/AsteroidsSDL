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


#ifndef __ASTROSHOT_HPP
#define __ASTROSHOT_HPP


#include "Common.hpp"


class AstroShot
{
   public:     
      enum
      {
         SMALL_SHOT = 0,
         LARGE_SHOT = 1,
         SMALL_SHOT_FRAMES = 40,
         LARGE_SHOT_FRAMES = 20,
         HYPERSPACE = -512,
      };

      AstroShot();
      ~AstroShot();
      void Draw(SDL_Renderer* SdlRenderer);
      void Move();
      void SetArea(int NewxMax, int NewyMax, int NewxOffset, int NewyOffset, float NewxVelocity, float NewyVelocity, int Size = SMALL_SHOT);
      short GetXOffset();
      short GetYOffset();
      void Destroy();
      short Active();

   private:
      int xMax;
      int yMax;
      int xOffset;
      int yOffset;
      float xVelocity;
      float yVelocity;
      int Size;
      short FrameCount;
};


#endif
