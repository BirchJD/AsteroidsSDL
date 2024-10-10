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


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "Number.hpp"
#include "Asteroids.hpp"
#include "AstroShot.hpp"
#include "AstroShip.hpp"



extern SDL_AudioDeviceID SdlAudioDevice;
extern SdlAudioWavType WavFiles[];



AstroShip::AstroShip()
{
   OneDegree = (double)6.3 / (double)360;
   FrameStep = (double)0.1;
   
   xMax = 0;
   yMax = 0;
   xOffset = HYPERSPACE;
   yOffset = HYPERSPACE;
   xVelocity = (short)0;
   yVelocity = (short)0;
   Crash = false;
   ThrustFlag = false;
   Fade = 0;
   Lives = MAX_LIVES;
   ExplodeFrame = 0;
   ShotIndex = 0;
   HyperCount = false;

  /***************************/
 /* Create ship life shape. */
/***************************/
   Angle = SHIP_START_ANGLE;
   LifeFrame[0].x = (long)(19 * sin(FrameStep*Angle + OneDegree*0));
   LifeFrame[0].y = (long)(19 * cos(FrameStep*Angle + OneDegree*0));
   LifeFrame[1].x = (long)(16 * sin(FrameStep*Angle + OneDegree*140));
   LifeFrame[1].y = (long)(16 * cos(FrameStep*Angle + OneDegree*140));
   LifeFrame[2].x = (long)(8 * sin(FrameStep*Angle + OneDegree*180));
   LifeFrame[2].y = (long)(8 * cos(FrameStep*Angle + OneDegree*180));
   LifeFrame[3].x = (long)(16 * sin(FrameStep*Angle + OneDegree*220));
   LifeFrame[3].y = (long)(16 * cos(FrameStep*Angle + OneDegree*220));
   LifeFrame[4].x = (long)(19 * sin(FrameStep*Angle + OneDegree*0));
   LifeFrame[4].y = (long)(19 * cos(FrameStep*Angle + OneDegree*0));

  /********************************************/
 /* Create ship shapes at all roated angles. */
/********************************************/
   for (Angle = 0; Angle < FRAMES; ++Angle)
   {
      Frame[Angle][0].x = (long)(16 * sin(FrameStep*Angle + OneDegree*0));
      Frame[Angle][0].y = (long)(16 * cos(FrameStep*Angle + OneDegree*0));
      Frame[Angle][1].x = (long)(13 * sin(FrameStep*Angle + OneDegree*140));
      Frame[Angle][1].y = (long)(13 * cos(FrameStep*Angle + OneDegree*140));
      Frame[Angle][2].x = (long)(5 * sin(FrameStep*Angle + OneDegree*180));
      Frame[Angle][2].y = (long)(5 * cos(FrameStep*Angle + OneDegree*180));
      Frame[Angle][3].x = (long)(13 * sin(FrameStep*Angle + OneDegree*220));
      Frame[Angle][3].y = (long)(13 * cos(FrameStep*Angle + OneDegree*220));
      Frame[Angle][4].x = (long)(16 * sin(FrameStep*Angle + OneDegree*0));
      Frame[Angle][4].y = (long)(16 * cos(FrameStep*Angle + OneDegree*0));
   }

   Angle = SHIP_START_ANGLE;
}



AstroShip::~AstroShip()
{
}



void AstroShip::Draw(SDL_Renderer* SdlRenderer)
{
   short Count;
   short LifeCount;

  /****************************/
 /* Display remaining lives. */
/****************************/
      for (LifeCount = 0; LifeCount < MAX_LIVES; ++LifeCount)
      {
  /********************************/
 /* Plot ships current position. */
/********************************/
         for (Count = 0; Count < FRAME_POINTS; ++Count)
         {
            LifeDisplayFrame[Count].x = LifeFrame[Count].x + (xMax - LIFE_XOFFSET) + (LifeCount+1)*LIFE_XGAP;
            LifeDisplayFrame[Count].y = LifeFrame[Count].y + LIFE_YOFFSET;
         }
  /******************************************/
 /* Draw the ship in the current position. */
/******************************************/
         if (Lives > LifeCount)
         {
            SDL_SetRenderDrawColor(SdlRenderer, (COLOUR_SHIP_LIFE >> 16) & 0xFF, (COLOUR_SHIP_LIFE >> 8) & 0xFF, COLOUR_SHIP_LIFE & 0xFF, 255);
				SDL_RenderDrawLines(SdlRenderer, LifeDisplayFrame, FRAME_POINTS);
         }
      }

  /***************************/
 /* Draw this player score. */
/***************************/
   PlayerScore.Draw(SdlRenderer);

  /***************************/
 /* Draw this player shots. */
/***************************/
   for (Count = 0; Count < MAX_SHOTS; ++Count)
      Shots[Count].Draw(SdlRenderer);

  /**************************/
 /* Draw this player ship. */
/**************************/
   if (Lives || ExplodeFrame != MAX_EXPLODE_FRAME)
   {
  /*********************/
 /* Draw intact ship. */
/*********************/
      if (!Crash)
      {
  /********************************/
 /* Plot ships current position. */
/********************************/
         for (Count = 0; Count < FRAME_POINTS; ++Count)
         {
            DisplayFrame[Count].x = Frame[Angle][Count].x + xOffset;
            DisplayFrame[Count].y = Frame[Angle][Count].y + yOffset;
         }
         if (ExplodeFrame >= ERASE_FRAME)
            ExplodeFrame = false;
  /******************************************/
 /* Draw the ship in the current position. */
/******************************************/
         SDL_SetRenderDrawColor(SdlRenderer, (COLOUR_SHIP >> 16) & 0xFF, (COLOUR_SHIP >> 8) & 0xFF, COLOUR_SHIP & 0xFF, 255);
			SDL_RenderDrawLines(SdlRenderer, DisplayFrame, FRAME_POINTS);
  /*****************************************/
 /* Add thrust point if currently active. */
/*****************************************/
         if (ThrustFlag)
         {
            for (Count = 0; Count < THRUST_POINTS; ++Count)
            {
               ThrustTrail[Count].x = xOffset + (short)((float)rand()/RAND_MAX * 7)-3 + (long)(15 * sin(FrameStep*Angle + OneDegree*180));
               ThrustTrail[Count].y = yOffset + (short)((float)rand()/RAND_MAX * 7)-3 + (long)(15 * cos(FrameStep*Angle + OneDegree*180));
               SDL_SetRenderDrawColor(SdlRenderer, 0x7F + (float)rand()/RAND_MAX * 0x7F, (float)rand()/RAND_MAX * 0xFF, (float)rand()/RAND_MAX * 0xFF, 255);
					SDL_RenderDrawLine(SdlRenderer, ThrustTrail[Count].x, ThrustTrail[Count].y, ThrustTrail[Count].x + 1, ThrustTrail[Count].y + 1);
            }
            ThrustFlag = false;
         }
      }
      else
      {
         if (ExplodeFrame == false)
         {
            --Lives;
  /**************************************************/
 /* Set direction of individual lines of the ship. */
/**************************************************/
            for (Count = 0; Count < FRAME_POINTS*2; Count += 2)
            {
               do
               {
                  ExplodeDirection[Count].x = (short)((float)rand()/RAND_MAX * 10)-5;
               } while (ExplodeDirection[Count].x == 0);
               do
               {
                  ExplodeDirection[Count].y = (short)((float)rand()/RAND_MAX * 10)-5;
               } while (ExplodeDirection[Count].y == 0);
               ExplodeDirection[Count+1].x = ExplodeDirection[Count].x;
               ExplodeDirection[Count+1].y = ExplodeDirection[Count].y;
            }
  /********************************************/
 /* Split polygon shape into seperate lines. */
/********************************************/
            DisplayFrame[0].x = Frame[Angle][FRAME_POINTS-1].x + xOffset;
            DisplayFrame[0].y = Frame[Angle][FRAME_POINTS-1].y + yOffset;
            DisplayFrame[FRAME_POINTS*2-1].x = Frame[Angle][FRAME_POINTS-1].x + xOffset;
            DisplayFrame[FRAME_POINTS*2-1].y = Frame[Angle][FRAME_POINTS-1].y + yOffset;
            for (Count = 0; Count < FRAME_POINTS-1; ++Count)
            {
               DisplayFrame[Count*2+1].x = Frame[Angle][Count].x + xOffset;
               DisplayFrame[Count*2+1].y = Frame[Angle][Count].y + yOffset;
               DisplayFrame[Count*2+2].x = Frame[Angle][Count].x + xOffset;
               DisplayFrame[Count*2+2].y = Frame[Angle][Count].y + yOffset;
            }
         }
  /******************************************/
 /* Draw the ship in the current position. */
/******************************************/
         if (ExplodeFrame < MAX_EXPLODE_FRAME -1)
         {
            for (Count = 0; Count < FRAME_POINTS*2; Count += 2)
            {
               DisplayFrame[Count].x += ExplodeDirection[Count].x;
               DisplayFrame[Count].y += ExplodeDirection[Count].y;
               DisplayFrame[Count+1].x += ExplodeDirection[Count+1].x;
               DisplayFrame[Count+1].y += ExplodeDirection[Count+1].y;
               SDL_SetRenderDrawColor(SdlRenderer, 0x7F + (float)rand()/RAND_MAX * 0x7F, (float)rand()/RAND_MAX * 0xFF, (float)rand()/RAND_MAX * 0xFF, 255);
					SDL_RenderDrawLine(SdlRenderer, DisplayFrame[Count].x, DisplayFrame[Count].y, DisplayFrame[Count+1].x, DisplayFrame[Count+1].y);               
            }
         }
  /************************/
 /* Reset for next life. */
/************************/
         ++ExplodeFrame;
         if (Lives != false && ExplodeFrame == MAX_EXPLODE_FRAME)
         {
            ExplodeFrame = false;
            Crash = false;
            ThrustFlag = false;
            Angle = SHIP_START_ANGLE;
            xOffset = xMax/2;
            yOffset = yMax/2;
            xVelocity = (short)0;
            yVelocity = (short)0;
         }
      }
   }
}



void AstroShip::IncAngle(short Direction)
{
   if (Crash == false)
   {
      if (Direction == false)
      {
         ++Angle;
         if (Angle >= FRAMES)
            Angle = 0;
      }
      else
      {
         --Angle;
         if (Angle < 0)
            Angle = FRAMES-1;
      }
   }
}



void AstroShip::Thrust()
{
   if (Crash == false)
   {
//      if (!SDL_GetQueuedAudioSize(SdlAudioDevice))
      {
         SDL_ClearQueuedAudio(SdlAudioDevice);
         SDL_QueueAudio(SdlAudioDevice, WavFiles[WAV_THRUST].WavBuffer, WavFiles[WAV_THRUST].WavLength);
         SDL_PauseAudioDevice(SdlAudioDevice, false);
      }
      ThrustFlag = true;
      xVelocity += (float)sin(FrameStep*Angle + OneDegree*0);
      yVelocity += (float)cos(FrameStep*Angle + OneDegree*0);
   }
}



void AstroShip::Shoot()
{
   if (Crash == false)
   {
      if (!SDL_GetQueuedAudioSize(SdlAudioDevice))
      {
         SDL_ClearQueuedAudio(SdlAudioDevice);
         SDL_QueueAudio(SdlAudioDevice, WavFiles[WAV_SHOT].WavBuffer, WavFiles[WAV_SHOT].WavLength);
         SDL_PauseAudioDevice(SdlAudioDevice, false);
      }
      Shots[ShotIndex].SetArea(xMax, yMax, xOffset, yOffset, xVelocity + 10*(float)sin(FrameStep*Angle + OneDegree*0), yVelocity + 10*(float)cos(FrameStep*Angle + OneDegree*0));
      if (++ShotIndex == MAX_SHOTS)
         ShotIndex = 0;
   }
}



void AstroShip::Move()
{
   short Count;

   if (HyperCount != false)
   {
      --HyperCount;
      if (HyperCount == false)
      {
         xOffset = (short)((float)rand()/RAND_MAX * (xMax - 2*SHIP_WIDTH));
         yOffset = (short)((float)rand()/RAND_MAX * (yMax - 2*SHIP_HEIGHT));
      }
   }
   for (Count = 0; Count < MAX_SHOTS; ++Count)
      Shots[Count].Move();
   if (Crash == false)
   {
      if (xOffset < 0 - SHIP_WIDTH)
         xOffset = xMax + SHIP_WIDTH;
      else if (xOffset > xMax + SHIP_WIDTH)
         xOffset = 0 - SHIP_WIDTH;
      if (yOffset < 0 - SHIP_HEIGHT)
         yOffset = yMax + SHIP_HEIGHT;
      else if (yOffset > yMax + SHIP_HEIGHT)
         yOffset = 0 - SHIP_HEIGHT;
      xOffset += (short)xVelocity;
      yOffset += (short)yVelocity;
   }
}



void AstroShip::Reset()
{
   if (Lives == false)
   {
      ExplodeFrame = ERASE_FRAME;
      Crash = false;
      ThrustFlag = false;
      Fade = 0;
      Angle = SHIP_START_ANGLE;
      xOffset = xMax/2;
      yOffset = yMax/2;
      xVelocity = (short)0;
      yVelocity = (short)0;
      Lives = MAX_LIVES;
      PlayerScore.SetNumber(0);
   }
}



void AstroShip::SetArea(SDL_Rect* ClientRect, long NewTextColour)
{
   xMax = (short)(ClientRect->w - ClientRect->x);
   yMax = (short)(ClientRect->h - ClientRect->y);
   xOffset = xMax/2;
   yOffset = yMax/2;
   PlayerScore.SetLocation(SCORE_XOFFSET, SCORE_YOFFSET, SCORE_SCALE, NewTextColour);
}



void AstroShip::Hyperspace()
{
   if (Crash == false && HyperCount == false)
   {
//      if (!SDL_GetQueuedAudioSize(SdlAudioDevice))
      {
         SDL_ClearQueuedAudio(SdlAudioDevice);
         SDL_QueueAudio(SdlAudioDevice, WavFiles[WAV_HYPER_SPACE].WavBuffer, WavFiles[WAV_HYPER_SPACE].WavLength);
         SDL_PauseAudioDevice(SdlAudioDevice, false);
      }
      HyperCount = HYPER_FRAMES;
      xOffset = HYPERSPACE;
      yOffset = HYPERSPACE;
      xVelocity = (float)0;
      yVelocity = (float)0;
   }
}



short AstroShip::Collide(int xPos, int yPos, int Width, int Height)
{
   short Collision = false;

   if (Crash == false)
      if ((Collision = xPos + Width/2 > xOffset - SHIP_WIDTH && xPos - Width/2 < xOffset + SHIP_WIDTH && yPos + Height/2 > yOffset - SHIP_HEIGHT && yPos - Height/2 < yOffset + SHIP_HEIGHT) == true)
         Crash = true;
   return  Collision;
}



void AstroShip::SetCrash(short NewCrash)
{
   Crash = NewCrash;
}



short AstroShip::GetCrash()
{
   return Crash;
}



short AstroShip::GetXOffset()
{
   return xOffset;
}



short AstroShip::GetYOffset()
{
   return yOffset;
}



short AstroShip::GetWidth()
{
   return SHIP_WIDTH;
}



short AstroShip::GetHeight()
{
   return SHIP_HEIGHT;
}



long AstroShip::GetScore()
{
   return PlayerScore.GetNumber();
}



void AstroShip::SetScore(long NewScore)
{
   PlayerScore.SetNumber(NewScore);
}



short AstroShip::GetLives()
{
   return Lives;
}



AstroShot& AstroShip::GetShot(short ShotCount)
{
   return Shots[ShotCount];
}



short AstroShip::GetShotCount()
{
   return MAX_SHOTS;
}
