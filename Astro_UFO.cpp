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


#include "Astro_UFO.hpp"


AstroUFO::AstroUFO()
{
   xMax = 0;
   yMax = 0;
   xOffset = HYPERSPACE;
   yOffset = HYPERSPACE;
   xVelocity = 0;
   yVelocity = 0;

  /*********************/
 /* Define UFO shape. */
/*********************/
   for (Size = 0; Size < FRAMES; ++Size)
   {
      Frame[Size][0].x = -(8 + (Size+1)*3);
      Frame[Size][0].y = -(0 + (Size+1));
      Frame[Size][1].x = -(0 + (Size+1));
      Frame[Size][1].y = -(3 + (Size+1)*3);
      Frame[Size][2].x = +(0 + (Size+1));
      Frame[Size][2].y = -(3 + (Size+1)*3);
      Frame[Size][3].x = +(8 + (Size+1)*3);
      Frame[Size][3].y = -(0 + (Size+1));
      Frame[Size][4].x = -(8 + (Size+1)*3);
      Frame[Size][4].y = -(0 + (Size+1));
      Frame[Size][5].x = -(8 + (Size+1)*3);
      Frame[Size][5].y = +(0 + (Size+1));
      Frame[Size][6].x = +(8 + (Size+1)*3);
      Frame[Size][6].y = +(0 + (Size+1));
      Frame[Size][7].x = +(8 + (Size+1)*3);
      Frame[Size][7].y = -(0 + (Size+1));
      Frame[Size][8].x = +(8 + (Size+1)*3);
      Frame[Size][8].y = +(0 + (Size+1));
      Frame[Size][9].x = +(0 + (Size+1));
      Frame[Size][9].y = +(3 + (Size+1)*3);
      Frame[Size][10].x = -(0 + (Size+1));
      Frame[Size][10].y = +(3 + (Size+1)*3);
      Frame[Size][11].x = -(8 + (Size+1)*3);
      Frame[Size][11].y = +(0 + (Size+1));
   }
   Size = INACTIVE;
}



AstroUFO::~AstroUFO()
{
}



void AstroUFO::Draw(SDL_Renderer* SdlRenderer)
{
   short Count;

   Shot.Draw(SdlRenderer);
   if (Size < INACTIVE)
   {
      for (Count = 0; Count < FRAME_POINTS; ++Count)
      {
         DisplayFrame[Count].x = Frame[Size][Count].x + xOffset;
         DisplayFrame[Count].y = Frame[Size][Count].y + yOffset;
      }
      SDL_SetRenderDrawColor(SdlRenderer, (COLOUR_UFO >> 16) & 0xFF, (COLOUR_UFO >> 8) & 0xFF, COLOUR_UFO & 0xFF, 255);
		SDL_RenderDrawLines(SdlRenderer, DisplayFrame, FRAME_POINTS);
   }
}



void AstroUFO::Move()
{
   short ShotDirection;

   Shot.Move();
   if (Size != INACTIVE)
   {
  /***************************************************************/
 /* If UFO shot not active, shoot new shot in random direction. */
/***************************************************************/
      if (!Shot.Active())
      {
//         if (!SDL_GetQueuedAudioSize(SdlAudioDevice))
         {
//            SDL_ClearQueuedAudio(SdlAudioDevice);
            SDL_QueueAudio(SdlAudioDevice, WavFiles[WAV_UFO].WavBuffer, WavFiles[WAV_UFO].WavLength);
            SDL_PauseAudioDevice(SdlAudioDevice, false);
         }
         ShotDirection = (short)((float)rand()/RAND_MAX * 4);
         if (ShotDirection == 0)
            Shot.SetArea(xMax, yMax, xOffset, yOffset, (float)-8, (float)-8, AstroShot::LARGE_SHOT);
         else if (ShotDirection == 1)
            Shot.SetArea(xMax, yMax, xOffset, yOffset, (float)-8, (float)+8, AstroShot::LARGE_SHOT);
         else if (ShotDirection == 2)
            Shot.SetArea(xMax, yMax, xOffset, yOffset, (float)+8, (float)-8, AstroShot::LARGE_SHOT);
         else if (ShotDirection == 3)
            Shot.SetArea(xMax, yMax, xOffset, yOffset, (float)+8, (float)+8, AstroShot::LARGE_SHOT);
      }
  /********************************************/
 /* Randomly change UFO direction of travel. */
/********************************************/
      if ((short)((float)rand()/RAND_MAX * 10) == false)
         yVelocity = (short)((float)rand()/RAND_MAX * ((Size+2)*10)) - ((Size+2)*5);
      if (xOffset < 0 - UFO_WIDTH)
         Size = INACTIVE;
      else if (xOffset > xMax + UFO_WIDTH)
         Size = INACTIVE;
      if (yOffset < 0)
         yOffset = 0;
      else if (yOffset > yMax)
         yOffset = yMax;
      xOffset += xVelocity;
      yOffset += yVelocity;
   }
  /********************************************************************/
 /* If UFO not active, generate a new UFO at a random time interval. */
/********************************************************************/
   else if ((short)((float)rand()/RAND_MAX * 500) == false)
   {
      Size = (short)((float)rand()/RAND_MAX * FRAMES);
      yOffset = (short)((float)rand()/RAND_MAX * yMax);
      if ((short)((float)rand()/RAND_MAX * 2) == false)
      {
         xOffset = 0 - UFO_WIDTH;
         xVelocity = 3 * (2 - Size+1);
      }
      else
      {
         xOffset = xMax + UFO_WIDTH;
         xVelocity = -3 * (2 - Size+1);
      }
      yVelocity = (short)((float)rand()/RAND_MAX * 5) - 3;
   }
}



void AstroUFO::SetArea(SDL_Rect* ClientRect)
{
   xMax = (short)(ClientRect->w - ClientRect->x);
   yMax = (short)(ClientRect->h - ClientRect->y);
}



short AstroUFO::Collide(int xPos, int yPos, int Width, int Height)
{
   if (Size < INACTIVE && xPos + Width/2 > xOffset - UFO_WIDTH / (Size*Size+1) && xPos - Width/2 < xOffset + UFO_WIDTH / (Size*Size+1) && yPos + Height/2 > yOffset - UFO_HEIGHT / (Size*Size+1) && yPos - Height/2 < yOffset + UFO_HEIGHT / (Size*Size+1))
   {
      Destroy();
      return true;
   }
   else
      return  false;
}



void AstroUFO::Destroy()
{
   xOffset = HYPERSPACE;
   yOffset = HYPERSPACE;
}



short AstroUFO::GetSize()
{
   return Size;
}



short AstroUFO::GetXOffset()
{
   return xOffset;
}



short AstroUFO::GetYOffset()
{
   return yOffset;
}



short AstroUFO::Active()
{
   return (Size != INACTIVE);
}



AstroShot& AstroUFO::GetShot()
{
   return Shot;
}
