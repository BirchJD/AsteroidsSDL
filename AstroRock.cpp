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
#include "Asteroids.hpp"
#include "AstroRock.hpp"



extern SDL_AudioDeviceID SdlAudioDevice;
extern SdlAudioWavType WavFiles[];



AstroRock::AstroRock()
{
   xMax = 0;
   yMax = 0;
   xOffset = HYPERSPACE;
   yOffset = HYPERSPACE;
   xVelocity = 0;
   yVelocity = 0;

  /**********************/
 /* Create rock shape. */
/**********************/
   for (Size = 0; Size < FRAMES; ++Size)
   {
      Frame[Size][0].x = -30 / (Size*Size+1);
      Frame[Size][0].y = -22 / (Size*Size+1);
      Frame[Size][1].x = -5 / (Size*Size+1);
      Frame[Size][1].y = -32 / (Size*Size+1);
      Frame[Size][2].x = +35 / (Size*Size+1);
      Frame[Size][2].y = -17 / (Size*Size+1);
      Frame[Size][3].x = +25 / (Size*Size+1);
      Frame[Size][3].y = +28 / (Size*Size+1);
      Frame[Size][4].x = +12 / (Size*Size+1);
      Frame[Size][4].y = -2 / (Size*Size+1);
      Frame[Size][5].x = +10 / (Size*Size+1);
      Frame[Size][5].y = +28 / (Size*Size+1);
      Frame[Size][6].x = -20 / (Size*Size+1);
      Frame[Size][6].y = +33 / (Size*Size+1);
      Frame[Size][7].x = -37 / (Size*Size+1);
      Frame[Size][7].y = +5 / (Size*Size+1);
      Frame[Size][8].x = -30 / (Size*Size+1);
      Frame[Size][8].y = -22 / (Size*Size+1);
   }
   Size = INACTIVE;
}



AstroRock::~AstroRock()
{
}



void AstroRock::Draw(SDL_Renderer* SdlRenderer)
{
   short Count;

   if (Size < INACTIVE)
   {
      for (Count = 0; Count < FRAME_POINTS; ++Count)
      {
         DisplayFrame[Count].x = Frame[Size][Count].x + xOffset;
         DisplayFrame[Count].y = Frame[Size][Count].y + yOffset;
      }
      SDL_SetRenderDrawColor(SdlRenderer, (COLOUR_ROCK >> 16) & 0xFF, (COLOUR_ROCK >> 8) & 0xFF, COLOUR_ROCK & 0xFF, 255);
		SDL_RenderDrawLines(SdlRenderer, DisplayFrame, FRAME_POINTS);
   }
}



void AstroRock::Move()
{
   if (Size < INACTIVE)
   {
      if (xOffset < 0 - ROCK_WIDTH)
         xOffset = xMax + ROCK_WIDTH;
      else if (xOffset > xMax + ROCK_WIDTH)
         xOffset = 0 - ROCK_WIDTH;
      if (yOffset < 0 - ROCK_HEIGHT)
         yOffset = yMax + ROCK_HEIGHT;
      else if (yOffset > yMax + ROCK_HEIGHT)
         yOffset = 0 - ROCK_HEIGHT;
      xOffset += xVelocity;
      yOffset += yVelocity;
   }
}



void AstroRock::SetArea(SDL_Rect* ClientRect, int NewxOffset, int NewyOffset, int NewSize)
{
   xMax = (short)(ClientRect->w - ClientRect->x);
   yMax = (short)(ClientRect->h - ClientRect->y);
   if (NewxOffset == NEW_POSITION)
   {
      Size = 0;
      if (!((float)rand()/RAND_MAX * 2))
      {
         xOffset = (short)((float)rand()/RAND_MAX * xMax);
         yOffset = yMax * (short)((float)rand()/RAND_MAX * 2);
      }
      else
      {
         yOffset = (short)((float)rand()/RAND_MAX * yMax);
         xOffset = xMax * (short)((float)rand()/RAND_MAX * 2);
      }
   }
   else
   {
      Size = NewSize;
      xOffset = NewxOffset;
      yOffset = NewyOffset;
   }
   do
   {
      xVelocity = (short)((float)rand()/RAND_MAX*6*(Size+1) - 3*(Size+1));
      yVelocity = (short)((float)rand()/RAND_MAX*6*(Size+1) - 3*(Size+1));
   } while(!xVelocity || !yVelocity);
}



short AstroRock::Collide(int xPos, int yPos, int Width, int Height)
{
   if (Size < INACTIVE && xPos + Width/2 > xOffset - ROCK_WIDTH / (Size*Size+1) && xPos - Width/2 < xOffset + ROCK_WIDTH / (Size*Size+1) && yPos + Height/2 > yOffset - ROCK_HEIGHT / (Size*Size+1) && yPos - Height/2 < yOffset + ROCK_HEIGHT / (Size*Size+1))
   {
//      if (!SDL_GetQueuedAudioSize(SdlAudioDevice))
      {
         SDL_ClearQueuedAudio(SdlAudioDevice);
         SDL_QueueAudio(SdlAudioDevice, WavFiles[WAV_ROCK].WavBuffer, WavFiles[WAV_ROCK].WavLength);
         SDL_PauseAudioDevice(SdlAudioDevice, false);
      }
      ++Size;
      do
      {
         xVelocity = (short)((float)rand()/RAND_MAX*6*(Size+1) - 3*(Size+1));
         yVelocity = (short)((float)rand()/RAND_MAX*6*(Size+1) - 3*(Size+1));
      } while(xVelocity == 0 || yVelocity == 0);

      return true;
   }
   else
      return  false;
}



void AstroRock::Destroy()
{
   Size = INACTIVE;
   xOffset = HYPERSPACE;
   yOffset = HYPERSPACE;
}



short AstroRock::GetSize()
{
   return Size;
}



short AstroRock::GetXOffset()
{
   return xOffset;
}



short AstroRock::GetYOffset()
{
   return yOffset;
}
