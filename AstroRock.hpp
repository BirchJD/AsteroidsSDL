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


#ifndef __ASTROROCK_HPP
#define __ASTROROCK_HPP


#include "Asteroids.hpp"


extern SDL_AudioDeviceID SdlAudioDevice;
extern SdlAudioWavType WavFiles[];


class AstroRock
{
   public:
      enum
      {
         INACTIVE = 3,
         FRAMES = 3,
         FRAME_POINTS = 9,
         ROCK_WIDTH = 36,
         ROCK_HEIGHT = 36,
         NEW_POSITION = -1,
         HYPERSPACE = -512,
      };

      AstroRock();
      ~AstroRock();
      void Draw(SDL_Renderer* SdlRenderer);
      void Move();
      void SetArea(SDL_Rect* ClientRect, int NewxOffset = NEW_POSITION, int NewyOffset = NEW_POSITION, int NewSize = NEW_POSITION);
      short Collide(int xPos, int yPos, int Width, int Height);
      short GetSize();
      void Destroy();
      short GetXOffset();
      short GetYOffset();

   private:
      short xMax;
      short yMax;
      short Size;
      short xOffset;
      short yOffset;
      short xVelocity;
      short yVelocity;
      SDL_Point Frame[FRAMES][FRAME_POINTS];
      SDL_Point DisplayFrame[FRAME_POINTS];
};


#endif
