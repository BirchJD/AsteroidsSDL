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


#ifndef __ASTRO_UFO_HPP
#define __ASTRO_UFO_HPP


class AstroUFO
{
   public:
      enum
      {
         INACTIVE = 3,
         FRAMES = 2,
         FRAME_POINTS = 12,
         UFO_WIDTH = 16,
         UFO_HEIGHT = 6,
         HYPERSPACE = -512,
      };

      AstroUFO();
      ~AstroUFO();
      void Draw(SDL_Renderer* SdlRenderer);
      void Move();
      void SetArea(SDL_Rect* ClientRect);
      short Collide(int xPos, int yPos, int Width, int Height);
      short GetSize();
      void Destroy();
      short GetXOffset();
      short GetYOffset();
      short Active();
      AstroShot& GetShot();

   private:
      int xMax;
      int yMax;
      int Size;
      int xOffset;
      int yOffset;
      int xVelocity;
      int yVelocity;
      AstroShot Shot;
      SDL_Point Frame[FRAMES][FRAME_POINTS];
      SDL_Point DisplayFrame[FRAME_POINTS];
};


#endif
