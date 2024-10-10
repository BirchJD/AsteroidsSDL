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


#ifndef __ASTROSHIP_HPP
#define __ASTROSHIP_HPP


class AstroShip
{
   public:
      enum
      {
         FRAMES = 63,
         ERASE_FRAME = FRAMES+1,
         FRAME_POINTS = 5,
         THRUST_POINTS = 8,
         SHIP_WIDTH = 25,
         SHIP_HEIGHT = 25,
         SHIP_START_ANGLE = 31,
         MAX_EXPLODE_FRAME = 40,
         LIFE_XGAP = 30,
         LIFE_XOFFSET = 150,
         LIFE_YOFFSET = 35,
         LIVES_HEIGHT = 34,
         LIVES_WIDTH = 100,
         MAX_LIVES = 3,
         SCORE_XOFFSET = 20,
         SCORE_YOFFSET = 20,
         SCORE_SCALE = 5,
         MAX_SHOTS = 10,
         HYPERSPACE = -512,
         HYPER_FRAMES = 20,
      };

      AstroShip();
      ~AstroShip();
      void Draw(SDL_Renderer* SdlRenderer);
      void IncAngle(short Direction);
      void Thrust();
      void Shoot();
      void Move();
      void Reset();
      void Hyperspace();
      void SetArea(SDL_Rect* ClientRect, long NewTextColour);
      short Collide(int xPos, int yPos, int Width, int Height);
      void SetCrash(short NewCrash);
      short GetCrash();
      short GetXOffset();
      short GetYOffset();
      short GetWidth();
      short GetHeight();
      long GetScore();
      void SetScore(long NewScore);
      short GetLives();
      AstroShot& GetShot(short ShotCount);
      short GetShotCount();

   private:
      double OneDegree;
      double FrameStep;

      short Lives;
      short Crash;
      short ThrustFlag;
      short Fade;
      short xMax;
      short yMax;
      short Angle;
      short xOffset;
      short yOffset;
      short ShotIndex;
      float xVelocity;
      float yVelocity;
      short ExplodeFrame;
      short HyperCount;
      Number PlayerScore;
      AstroShot Shots[MAX_SHOTS];
      SDL_Point LifeFrame[FRAME_POINTS];
      SDL_Point LifeDisplayFrame[FRAME_POINTS];
      SDL_Point Frame[FRAMES][FRAME_POINTS];
      SDL_Point DisplayFrame[FRAME_POINTS*2];
      SDL_Point ExplodeDirection[FRAME_POINTS*2];
      SDL_Point ThrustTrail[THRUST_POINTS];
};

#endif
