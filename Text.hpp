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


#ifndef __TEXT_HPP
#define __TEXT_HPP


class Text
{
   public:
      enum 
      {
         MAX_LETTERS = 58,
         MAX_POINTS = 12,
         MAX_TEXT = 2048,
         INFINATE_FRAMES = -1
      };

      Text();
      ~Text();
      void Draw(SDL_Renderer* SdlRenderer);
      void SetLocation(int NewxOffset, int NewyOffset, int NewScale, int NewFrames, bool NewFlash, const char* NewText, long NewTextColour);
      void SetVisible(short NewVisible);
      short GetVisible();

   private:
      short xOffset;
      short yOffset;
      short Scale;
	   short Width;
      long TextColour;
      bool Visible;
      bool LastVisible;
      bool FlashVisible;
      short Active;
      short Frames;
      short FrameCount;
      bool Flash;
      char TextString[MAX_TEXT+1];
      SDL_Point Letter[MAX_LETTERS+1][MAX_POINTS+1];
      SDL_Point DisplayFrame[MAX_TEXT+1][MAX_POINTS+1];
};


#endif
