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
#include <unistd.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "Number.hpp"
#include "Text.hpp"
#include "Asteroids.hpp"
#include "AstroShot.hpp"
#include "AstroShip.hpp"
#include "Astro_UFO.hpp"
#include "AstroRock.hpp"



  /****************/
 /* Game sounds. */
/****************/
SDL_AudioDeviceID SdlAudioDevice;
SdlAudioWavType WavFiles[MAX_WAV_FILES];

  /*****************/
 /* Game objects. */
/*****************/
short FirstRock;
short NextRock;
AstroShip Ship;
AstroUFO UFO;
AstroRock Rock[MAX_ROCKS];
Number HiScore;
Text GameOver;
Text InsertCoin;



int WinMain(int argc, char* argv[])
{
   return main(argc, argv);
}



int main(int argc, char* argv[])
{
   unsigned char Flags = false;
	int Count;
   SDL_Event SdlEvent;
   SDL_Window* SdlWindow = NULL;
   SDL_Renderer* SdlRenderer = NULL;
   SDL_Rect Desktop = { 0, 0, 640, 480 };    // Window size.

  /********************/
 /* Set random seed. */
/********************/
   srand(time(NULL));

  /*******************************/
 /* Initialise SDL environment. */
/*******************************/
   if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
   {
      printf("FAILED TO INITIALISE SDL2\r\n");
      exit(0);
   }

  /**********************/
 /* Create SDL Window. */
/**********************/
   if (!(SdlWindow = SDL_CreateWindow("SDL Asteroids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Desktop.w, Desktop.h, 0)))
   {
      printf("FAILED TO CREATE SDL2 WINDOW\r\n");
      exit(0);
   }
   SdlRenderer = SDL_CreateRenderer(SdlWindow, -1, SDL_RENDERER_ACCELERATED);
   SDL_RenderSetLogicalSize(SdlRenderer, Desktop.w, Desktop.h);

  /********************/
 /* Load sound data. */
/********************/
	SDL_LoadWAV("Rock.wav", &(WavFiles[WAV_ROCK].WavSpec), &(WavFiles[WAV_ROCK].WavBuffer), &(WavFiles[WAV_ROCK].WavLength));
	SDL_LoadWAV("HyperSpace.wav", &(WavFiles[WAV_HYPER_SPACE].WavSpec), &(WavFiles[WAV_HYPER_SPACE].WavBuffer), &(WavFiles[WAV_HYPER_SPACE].WavLength));
	SDL_LoadWAV("Shot.wav", &(WavFiles[WAV_SHOT].WavSpec), &(WavFiles[WAV_SHOT].WavBuffer), &(WavFiles[WAV_SHOT].WavLength));
	SDL_LoadWAV("Thrust.wav", &(WavFiles[WAV_THRUST].WavSpec), &(WavFiles[WAV_THRUST].WavBuffer), &(WavFiles[WAV_THRUST].WavLength));
	SDL_LoadWAV("UFO.wav", &(WavFiles[WAV_UFO].WavSpec), &(WavFiles[WAV_UFO].WavBuffer), &(WavFiles[WAV_UFO].WavLength));
	SDL_LoadWAV("UFOShot.wav", &(WavFiles[WAV_UFO_SHOT].WavSpec), &(WavFiles[WAV_UFO_SHOT].WavBuffer), &(WavFiles[WAV_UFO_SHOT].WavLength));
	SDL_LoadWAV("Belt.wav", &(WavFiles[WAV_BELT].WavSpec), &(WavFiles[WAV_BELT].WavBuffer), &(WavFiles[WAV_BELT].WavLength));

  /****************************/
 /* Create SDL Audio Device. */
/****************************/
   SdlAudioDevice = SDL_OpenAudioDevice(NULL, 0, &(WavFiles[WAV_ROCK].WavSpec), NULL, 0);

  /*******************************/
 /* Initialise game components. */
/*******************************/
   GameOver.SetLocation((Desktop.w - Desktop.x) / 2 - GAMEOVER_XOFFSET, (Desktop.h - Desktop.y) / 2 - GAMEOVER_YOFFSET, 5, 200, false, "GAME OVER", COLOUR_GAME_OVER);
   InsertCoin.SetLocation((Desktop.w - Desktop.x) / 2 - INSERTCOIN_XOFFSET, (Desktop.h - Desktop.y) / 2 - INSERTCOIN_YOFFSET, 5, 15, true, "INSERT COIN", COLOUR_INSERT_COIN);
   HiScore.SetLocation((Desktop.w - Desktop.x) / 2 - HISCORE_XOFFSET, HISCORE_YOFFSET, HISCORE_SCALE, COLOUR_HIGH_SCORE);
   Ship.SetArea(&Desktop, COLOUR_SCORE);
   UFO.SetArea(&Desktop);
   FirstRock = START_ROCKS;
   NextRock = FirstRock;
   for (Count = 0; Count < FirstRock; ++Count)
      Rock[Count].SetArea(&Desktop);

  /**************************************************************/
 /* Process application messages until the ESC key is pressed. */
/**************************************************************/
   do
   {
  /*****************************************/
 /* Yeald 50ms for every frame displayed. */
/*****************************************/
      SDL_Delay(50);
		DoFrame(SdlRenderer, &Desktop, Flags);

  /*******************************/
 /* Poll for user input events. */
/*******************************/
      while (SDL_PollEvent(&SdlEvent) > 0)
      {
         switch (SdlEvent.type)
         {
            case SDL_QUIT:
               Flags |= FLAG_EXIT;
               break;

            case SDL_KEYUP:
               switch (SdlEvent.key.keysym.sym)
               {
			         case SDLK_UP:
   				      Flags &= ~FLAG_THRUST;
                     break;
			         case SDLK_LEFT:
   				      Flags &= ~FLAG_ROTATE_LEFT;
                     break;
   			      case SDLK_RIGHT:
   				      Flags &= ~FLAG_ROTATE_RIGHT;
                     break;
               }
               break;

            case SDL_KEYDOWN:
               switch (SdlEvent.key.keysym.sym)
               {
                  case SDLK_ESCAPE:
                     Flags |= FLAG_EXIT;
                     break;
			         case SDLK_1:
  /*****************************************************************/
 /* When 1 key pressed, if player has no lives, start a new game. */
/*****************************************************************/
                     if (Ship.GetLives() == false)
                     {
                        SDL_QueueAudio(SdlAudioDevice, WavFiles[WAV_BELT].WavBuffer, WavFiles[WAV_BELT].WavLength);
                        SDL_PauseAudioDevice(SdlAudioDevice, false);
                        if (Ship.GetScore() > HiScore.GetNumber())
                           HiScore.SetNumber(Ship.GetScore());
                        Ship.Reset();
                        UFO.Destroy();
                        UFO.GetShot().Destroy();
                        FirstRock = START_ROCKS;
                        NextRock = FirstRock;
                        for (Count = 0; Count < MAX_ROCKS; ++Count)
                           Rock[Count].Destroy();
                        for (Count = 0; Count < FirstRock; ++Count)
                           Rock[Count].SetArea(&Desktop);
                     }
                     break;
			         case SDLK_LSHIFT:
                  case SDLK_RSHIFT:
   	               Ship.Shoot();
                     break;
			         case SDLK_UP:
   				      Flags |= FLAG_THRUST;
                     break;
			         case SDLK_LEFT:
   				      Flags |= FLAG_ROTATE_LEFT;
                     break;
   			      case SDLK_RIGHT:
   				      Flags |= FLAG_ROTATE_RIGHT;
                     break;
   			      case SDLK_DOWN:
                     Ship.Hyperspace();
                     break;
               }
               break;
   		}
		};
   } while (!(Flags & FLAG_EXIT));

  /***************************/
 /* Close SDL Audio Device. */
/***************************/
   SDL_CloseAudioDevice(SdlAudioDevice);
  /********************/
 /* Free sound data. */
/********************/
   for (Count = 0; Count < MAX_WAV_FILES; ++Count)
      SDL_FreeWAV(WavFiles[Count].WavBuffer);
  /***********************************/
 /* Destroy application SDL Window. */
/***********************************/
   if (SdlWindow)
      SDL_DestroyWindow(SdlWindow);
  /**************************/
 /* Close SDL environment. */
/**************************/
   SDL_Quit();

  /*************************************/
 /* Exit application with value zero. */
/*************************************/
   return 0;
}



void DoFrame(SDL_Renderer* SdlRenderer, SDL_Rect* Desktop, unsigned char Flags)
{
	int Count;
	int ShotCount;
   bool RockFound;

  /**********************/
 /* Move game objects. */
/**********************/
	if (Flags & FLAG_THRUST)
		Ship.Thrust();
	else if (Flags & FLAG_ROTATE_LEFT)
	{
		Ship.IncAngle(false);
		Ship.IncAngle(false);
	}
	else if (Flags & FLAG_ROTATE_RIGHT)
	{
      Ship.IncAngle(true);
      Ship.IncAngle(true);
	}
	Ship.Move();
	UFO.Move();

  /**************************************/
 /* Check for ship collision with UFO. */
/**************************************/
	if (!Ship.GetCrash() && UFO.Collide(Ship.GetXOffset(), Ship.GetYOffset(), Ship.GetWidth(), Ship.GetHeight()))
		Ship.SetCrash(true);
	if (UFO.GetShot().Active() && Ship.Collide(UFO.GetShot().GetXOffset(), UFO.GetShot().GetYOffset(), 2, 2))
		Ship.SetCrash(true);
  /***********************/
 /* Check for shot UFO. */
/***********************/
   if (UFO.Active())
   {
      for (ShotCount = 0; ShotCount < Ship.GetShotCount(); ++ShotCount)
      {
	      if (Ship.GetShot(ShotCount).Active() && UFO.Collide(Ship.GetShot(ShotCount).GetXOffset(), Ship.GetShot(ShotCount).GetYOffset(), 2, 2))
         {
		      Ship.SetScore(Ship.GetScore() + 100);
		      Ship.GetShot(ShotCount).Destroy();
         }
      }
   }

  /************************************/
 /* Check for collisions with rocks. */
/************************************/
	RockFound = false;
	for (Count = 0; Count < MAX_ROCKS; ++Count)
   {
	   if (Rock[Count].GetSize() != AstroRock::INACTIVE)
      {
			RockFound = true;
  /****************************************/
 /* Check for ship collision with rocks. */
/****************************************/
		   if (!Ship.GetCrash() && Rock[Count].Collide(Ship.GetXOffset(), Ship.GetYOffset(), Ship.GetWidth(), Ship.GetHeight()))
         {
			   Ship.SetCrash(true);
		      if (NextRock+1 < MAX_ROCKS)
   			   Rock[++NextRock].SetArea(Desktop, Ship.GetXOffset(), Ship.GetYOffset(), Rock[Count].GetSize());
         }
  /*************************/
 /* Check for shot rocks. */
/*************************/
		   for (ShotCount = 0; ShotCount < Ship.GetShotCount(); ++ShotCount)
         {
			   if (Ship.GetShot(ShotCount).Active() && Rock[Count].Collide(Ship.GetShot(ShotCount).GetXOffset(), Ship.GetShot(ShotCount).GetYOffset(), 2, 2))
            {
				   Ship.SetScore(Ship.GetScore() + 5*(1+Rock[Count].GetSize()));
				   Ship.GetShot(ShotCount).Destroy();
  /*******************************************/
 /* Spilt shot rock into two smaller rocks. */
/*******************************************/
				   if (NextRock+1 < MAX_ROCKS)
					   Rock[++NextRock].SetArea(Desktop, Rock[Count].GetXOffset(), Rock[Count].GetYOffset(), Rock[Count].GetSize());
            }
         }
   		Rock[Count].Move();
		}
   }
  /*********************************************************/
 /* If end of level, start next level with an extra rock. */
/*********************************************************/
   if (!RockFound)
   {
//      if (!SDL_GetQueuedAudioSize(SdlAudioDevice))
      {
         SDL_ClearQueuedAudio(SdlAudioDevice);
         SDL_QueueAudio(SdlAudioDevice, WavFiles[WAV_BELT].WavBuffer, WavFiles[WAV_BELT].WavLength);
         SDL_PauseAudioDevice(SdlAudioDevice, false);
      }
	   if (FirstRock+1 < MAX_ROCKS)
	      ++FirstRock;
		NextRock = FirstRock;
		for (Count = 0; Count < FirstRock; ++Count)
			Rock[Count].SetArea(Desktop);
   }
  /*******************************************/
 /* If end of game, display Game Over text. */
/*******************************************/
	GameOver.SetVisible(!Ship.GetLives());
  /**************************************************************/
 /* After Game Over text disappears, display Insert Coin text. */
/**************************************************************/
	InsertCoin.SetVisible(!GameOver.GetVisible() && !Ship.GetLives());

  /*************************/
 /* Draw grapgic objects. */
/*************************/
	InsertCoin.Draw(SdlRenderer);
   GameOver.Draw(SdlRenderer);
   HiScore.Draw(SdlRenderer);
   Ship.Draw(SdlRenderer);
	UFO.Draw(SdlRenderer);
	for (Count = 0; Count < MAX_ROCKS; ++Count)
		Rock[Count].Draw(SdlRenderer);

  /***************************************************************************/
 /* Render display frame, then clear to start rendering next display frame. */
/***************************************************************************/
   SDL_RenderPresent(SdlRenderer);
   SDL_SetRenderDrawColor(SdlRenderer, 0x00, 0x00, 0x00, 255);
   SDL_RenderClear(SdlRenderer);
}