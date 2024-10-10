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


#include <string.h>
#include <ctype.h>
#include <SDL2/SDL.h>
#include "Text.hpp"
#include "Asteroids.hpp"



Text::Text()
{
   TextString[0] = '\0';
   xOffset = 0;
   yOffset = 0;
   Scale = 0;
   TextColour = 0;
   Visible = false;
   LastVisible = false;
   FlashVisible = false;
   Active = false;
   Frames = INFINATE_FRAMES;
   FrameCount = 0;
   Flash = false;
}



Text::~Text()
{
}



void Text::Draw(SDL_Renderer* SdlRenderer)
{
   short Digit;

   if (Active)
   {
  /********************************************/
 /* Display only for given number of frames. */
/********************************************/
      if (FrameCount != INFINATE_FRAMES)
         --FrameCount;

  /*****************************/
 /* Flash text if flagged to. */
/*****************************/
      if (!FrameCount && Flash)
      {
         FrameCount = Frames;
         FlashVisible = !FlashVisible;
      }
      else if (!FrameCount)
         Active = false;

  /**************************/
 /* Draw the current Text. */
/**************************/
      SDL_SetRenderDrawColor(SdlRenderer, (TextColour >> 16) & 0xFF, (TextColour >> 8) & 0xFF, TextColour & 0xFF, 255);
      for (Digit = 0; Digit < MAX_TEXT && TextString[Digit]; ++Digit)
         if (Active && Visible && FlashVisible && TextString[Digit] >= '!' && TextString[Digit] <= 'Z')
				SDL_RenderDrawLines(SdlRenderer, DisplayFrame[Digit], DisplayFrame[Digit][MAX_POINTS].x);
   }
}



void Text::SetLocation(int NewxOffset, int NewyOffset, int NewScale, int NewFrames, bool NewFlash, const char* NewText, long NewTextColour)
{
   short Count;
	short Length;
   short Digit;
   short xOffsetOrig;

   xOffsetOrig = NewxOffset;
   xOffset = NewxOffset;
   yOffset = NewyOffset;
   Scale = NewScale;
   TextColour = NewTextColour;
   Frames = NewFrames;
   Flash = NewFlash;
   strncpy(TextString, NewText, MAX_TEXT);
	Length = strlen(TextString);
	for (Count = 0; Count < Length; ++Count)
	   TextString[Count] = toupper(TextString[Count]);

  /**************************************************/
 /* Create text caracter shapes at requested size. */
/**************************************************/
// !
   Letter[0][MAX_POINTS].x = 2;
   Letter[0][0].x = 2*Scale;
   Letter[0][0].y = 0*Scale;
   Letter[0][1].x = 2*Scale;
   Letter[0][1].y = 3*Scale;
// "
   Letter[1][MAX_POINTS].x = 4;
   Letter[1][0].x = 1*Scale;
   Letter[1][0].y = 1*Scale;
   Letter[1][1].x = 1*Scale;
   Letter[1][1].y = 0*Scale;
   Letter[1][2].x = 2*Scale;
   Letter[1][2].y = 0*Scale;
   Letter[1][3].x = 2*Scale;
   Letter[1][3].y = 1*Scale;
// #
   Letter[2][MAX_POINTS].x = 11;
   Letter[2][0].x = 1*Scale;
   Letter[2][0].y = 0*Scale;
   Letter[2][1].x = 1*Scale;
   Letter[2][1].y = 4*Scale;
   Letter[2][2].x = 1*Scale;
   Letter[2][2].y = 3*Scale;
   Letter[2][3].x = 0*Scale;
   Letter[2][3].y = 3*Scale;
   Letter[2][4].x = 3*Scale;
   Letter[2][4].y = 3*Scale;
   Letter[2][5].x = 2*Scale;
   Letter[2][5].y = 3*Scale;
   Letter[2][6].x = 2*Scale;
   Letter[2][6].y = 4*Scale;
   Letter[2][7].x = 2*Scale;
   Letter[2][7].y = 0*Scale;
   Letter[2][8].x = 2*Scale;
   Letter[2][8].y = 1*Scale;
   Letter[2][9].x = 3*Scale;
   Letter[2][9].y = 1*Scale;
   Letter[2][10].x = 0*Scale;
   Letter[2][10].y = 1*Scale;
// $
   Letter[3][MAX_POINTS].x = 9;
   Letter[3][0].x = 3*Scale;
   Letter[3][0].y = 1*Scale;
   Letter[3][1].x = 1*Scale;
   Letter[3][1].y = 1*Scale;
   Letter[3][2].x = 0*Scale;
   Letter[3][2].y = 2*Scale;
   Letter[3][3].x = 3*Scale;
   Letter[3][3].y = 2*Scale;
   Letter[3][4].x = 2*Scale;
   Letter[3][4].y = 3*Scale;
   Letter[3][5].x = 0*Scale;
   Letter[3][5].y = 3*Scale;
   Letter[3][6].x = 1*Scale;
   Letter[3][6].y = 3*Scale;
   Letter[3][7].x = 0*Scale;
   Letter[3][7].y = 4*Scale;
   Letter[3][8].x = 3*Scale;
   Letter[3][8].y = 0*Scale;
// %
   Letter[4][MAX_POINTS].x = 11;
   Letter[4][0].x = 0*Scale;
   Letter[4][0].y = 0*Scale;
   Letter[4][1].x = 0*Scale;
   Letter[4][1].y = 1*Scale;
   Letter[4][2].x = 1*Scale;
   Letter[4][2].y = 1*Scale;
   Letter[4][3].x = 1*Scale;
   Letter[4][3].y = 0*Scale;
   Letter[4][4].x = 0*Scale;
   Letter[4][4].y = 0*Scale;
   Letter[4][5].x = 3*Scale;
   Letter[4][5].y = 0*Scale;
   Letter[4][6].x = 0*Scale;
   Letter[4][6].y = 4*Scale;
   Letter[4][7].x = 3*Scale;
   Letter[4][7].y = 4*Scale;
   Letter[4][8].x = 3*Scale;
   Letter[4][8].y = 3*Scale;
   Letter[4][9].x = 2*Scale;
   Letter[4][9].y = 3*Scale;
   Letter[4][10].x = 2*Scale;
   Letter[4][10].y = 4*Scale;
// &
   Letter[5][MAX_POINTS].x = 7;
   Letter[5][0].x = 3*Scale;
   Letter[5][0].y = 4*Scale;
   Letter[5][1].x = 0*Scale;
   Letter[5][1].y = 1*Scale;
   Letter[5][2].x = 1*Scale;
   Letter[5][2].y = 0*Scale;
   Letter[5][3].x = 2*Scale;
   Letter[5][3].y = 1*Scale;
   Letter[5][4].x = 0*Scale;
   Letter[5][4].y = 3*Scale;
   Letter[5][5].x = 1*Scale;
   Letter[5][5].y = 4*Scale;
   Letter[5][6].x = 3*Scale;
   Letter[5][6].y = 2*Scale;
// '
   Letter[6][MAX_POINTS].x = 2;
   Letter[6][0].x = 2*Scale;
   Letter[6][0].y = 0*Scale;
   Letter[6][1].x = 1*Scale;
   Letter[6][1].y = 1*Scale;
// (
   Letter[7][MAX_POINTS].x = 6;
   Letter[7][0].x = 2*Scale;
   Letter[7][0].y = 0*Scale;
   Letter[7][1].x = 1*Scale;
   Letter[7][1].y = 0*Scale;
   Letter[7][2].x = 0*Scale;
   Letter[7][2].y = 1*Scale;
   Letter[7][3].x = 0*Scale;
   Letter[7][3].y = 3*Scale;
   Letter[7][4].x = 1*Scale;
   Letter[7][4].y = 4*Scale;
   Letter[7][5].x = 2*Scale;
   Letter[7][5].y = 4*Scale;
// )
   Letter[8][MAX_POINTS].x = 6;
   Letter[8][0].x = 1*Scale;
   Letter[8][0].y = 0*Scale;
   Letter[8][1].x = 2*Scale;
   Letter[8][1].y = 0*Scale;
   Letter[8][2].x = 3*Scale;
   Letter[8][2].y = 1*Scale;
   Letter[8][3].x = 3*Scale;
   Letter[8][3].y = 3*Scale;
   Letter[8][4].x = 2*Scale;
   Letter[8][4].y = 4*Scale;
   Letter[8][5].x = 1*Scale;
   Letter[8][5].y = 4*Scale;
// *
   Letter[9][MAX_POINTS].x = 11;
   Letter[9][0].x = 0*Scale;
   Letter[9][0].y = 1*Scale;
   Letter[9][1].x = 2*Scale;
   Letter[9][1].y = 3*Scale;
   Letter[9][2].x = 1*Scale;
   Letter[9][2].y = 2*Scale;
   Letter[9][3].x = 0*Scale;
   Letter[9][3].y = 3*Scale;
   Letter[9][4].x = 2*Scale;
   Letter[9][4].y = 1*Scale;
   Letter[9][5].x = 1*Scale;
   Letter[9][5].y = 2*Scale;
   Letter[9][6].x = 0*Scale;
   Letter[9][6].y = 2*Scale;
   Letter[9][7].x = 2*Scale;
   Letter[9][7].y = 2*Scale;
   Letter[9][8].x = 1*Scale;
   Letter[9][8].y = 2*Scale;
   Letter[9][9].x = 1*Scale;
   Letter[9][9].y = 1*Scale;
   Letter[9][10].x = 1*Scale;
   Letter[9][10].y = 3*Scale;
// +
   Letter[10][MAX_POINTS].x = 5;
   Letter[10][0].x = 1*Scale;
   Letter[10][0].y = 1*Scale;
   Letter[10][1].x = 1*Scale;
   Letter[10][1].y = 3*Scale;
   Letter[10][2].x = 1*Scale;
   Letter[10][2].y = 2*Scale;
   Letter[10][3].x = 0*Scale;
   Letter[10][3].y = 2*Scale;
   Letter[10][4].x = 2*Scale;
   Letter[10][4].y = 2*Scale;
// ,
   Letter[11][MAX_POINTS].x = 2;
   Letter[11][0].x = 2*Scale;
   Letter[11][0].y = 3*Scale;
   Letter[11][1].x = 1*Scale;
   Letter[11][1].y = 4*Scale;
// -
   Letter[12][MAX_POINTS].x = 2;
   Letter[12][0].x = 0*Scale;
   Letter[12][0].y = 2*Scale;
   Letter[12][1].x = 2*Scale;
   Letter[12][1].y = 2*Scale;
// .
   Letter[13][MAX_POINTS].x = 2;
   Letter[13][0].x = 2*Scale;
   Letter[13][0].y = 4*Scale;
   Letter[13][1].x = 2*Scale;
   Letter[13][1].y = 4*Scale;
// /
   Letter[14][MAX_POINTS].x = 2;
   Letter[14][0].x = 0*Scale;
   Letter[14][0].y = 4*Scale;
   Letter[14][1].x = 3*Scale;
   Letter[14][1].y = 0*Scale;
// 0
   Letter[15][MAX_POINTS].x = 9;
   Letter[15][0].x = 1*Scale;
   Letter[15][0].y = 0*Scale;
   Letter[15][1].x = 2*Scale;
   Letter[15][1].y = 0*Scale;
   Letter[15][2].x = 3*Scale;
   Letter[15][2].y = 1*Scale;
   Letter[15][3].x = 3*Scale;
   Letter[15][3].y = 3*Scale;
   Letter[15][4].x = 2*Scale;
   Letter[15][4].y = 4*Scale;
   Letter[15][5].x = 1*Scale;
   Letter[15][5].y = 4*Scale;
   Letter[15][6].x = 0*Scale;
   Letter[15][6].y = 3*Scale;
   Letter[15][7].x = 0*Scale;
   Letter[15][7].y = 1*Scale;
   Letter[15][8].x = 1*Scale;
   Letter[15][8].y = 0*Scale;
// 1
   Letter[16][MAX_POINTS].x = 2;
   Letter[16][0].x = 2*Scale;
   Letter[16][0].y = 0*Scale;
   Letter[16][1].x = 2*Scale;
   Letter[16][1].y = 4*Scale;
// 2
   Letter[17][MAX_POINTS].x = 9;
   Letter[17][0].x = 0*Scale;
   Letter[17][0].y = 1*Scale;
   Letter[17][1].x = 1*Scale;
   Letter[17][1].y = 0*Scale;
   Letter[17][2].x = 2*Scale;
   Letter[17][2].y = 0*Scale;
   Letter[17][3].x = 3*Scale;
   Letter[17][3].y = 1*Scale;
   Letter[17][4].x = 2*Scale;
   Letter[17][4].y = 2*Scale;
   Letter[17][5].x = 1*Scale;
   Letter[17][5].y = 2*Scale;
   Letter[17][6].x = 0*Scale;
   Letter[17][6].y = 3*Scale;
   Letter[17][7].x = 0*Scale;
   Letter[17][7].y = 4*Scale;
   Letter[17][8].x = 3*Scale;
   Letter[17][8].y = 4*Scale;
// 3
   Letter[18][MAX_POINTS].x = 9;
   Letter[18][0].x = 0*Scale;
   Letter[18][0].y = 0*Scale;
   Letter[18][1].x = 2*Scale;
   Letter[18][1].y = 0*Scale;
   Letter[18][2].x = 3*Scale;
   Letter[18][2].y = 1*Scale;
   Letter[18][3].x = 2*Scale;
   Letter[18][3].y = 2*Scale;
   Letter[18][4].x = 1*Scale;
   Letter[18][4].y = 2*Scale;
   Letter[18][5].x = 2*Scale;
   Letter[18][5].y = 2*Scale;
   Letter[18][6].x = 3*Scale;
   Letter[18][6].y = 3*Scale;
   Letter[18][7].x = 2*Scale;
   Letter[18][7].y = 4*Scale;
   Letter[18][8].x = 0*Scale;
   Letter[18][8].y = 4*Scale;
// 4
   Letter[19][MAX_POINTS].x = 4;
   Letter[19][0].x = 2*Scale;
   Letter[19][0].y = 4*Scale;
   Letter[19][1].x = 2*Scale;
   Letter[19][1].y = 0*Scale;
   Letter[19][2].x = 0*Scale;
   Letter[19][2].y = 3*Scale;
   Letter[19][3].x = 3*Scale;
   Letter[19][3].y = 3*Scale;
// 5
   Letter[20][MAX_POINTS].x = 7;
   Letter[20][0].x = 3*Scale;
   Letter[20][0].y = 0*Scale;
   Letter[20][1].x = 0*Scale;
   Letter[20][1].y = 0*Scale;
   Letter[20][2].x = 0*Scale;
   Letter[20][2].y = 2*Scale;
   Letter[20][3].x = 2*Scale;
   Letter[20][3].y = 2*Scale;
   Letter[20][4].x = 3*Scale;
   Letter[20][4].y = 3*Scale;
   Letter[20][5].x = 2*Scale;
   Letter[20][5].y = 4*Scale;
   Letter[20][6].x = 0*Scale;
   Letter[20][6].y = 4*Scale;
// 6
   Letter[21][MAX_POINTS].x = 9;
   Letter[21][0].x = 3*Scale;
   Letter[21][0].y = 0*Scale;
   Letter[21][1].x = 1*Scale;
   Letter[21][1].y = 0*Scale;
   Letter[21][2].x = 0*Scale;
   Letter[21][2].y = 1*Scale;
   Letter[21][3].x = 0*Scale;
   Letter[21][3].y = 3*Scale;
   Letter[21][4].x = 1*Scale;
   Letter[21][4].y = 4*Scale;
   Letter[21][5].x = 2*Scale;
   Letter[21][5].y = 4*Scale;
   Letter[21][6].x = 3*Scale;
   Letter[21][6].y = 3*Scale;
   Letter[21][7].x = 3*Scale;
   Letter[21][7].y = 2*Scale;
   Letter[21][8].x = 0*Scale;
   Letter[21][8].y = 2*Scale;
// 7
   Letter[22][MAX_POINTS].x = 3;
   Letter[22][0].x = 0*Scale;
   Letter[22][0].y = 0*Scale;
   Letter[22][1].x = 3*Scale;
   Letter[22][1].y = 0*Scale;
   Letter[22][2].x = 0*Scale;
   Letter[22][2].y = 4*Scale;
// 8
   Letter[23][MAX_POINTS].x = 9;
   Letter[23][0].x = 0*Scale;
   Letter[23][0].y = 1*Scale;
   Letter[23][1].x = 1*Scale;
   Letter[23][1].y = 0*Scale;
   Letter[23][2].x = 2*Scale;
   Letter[23][2].y = 0*Scale;
   Letter[23][3].x = 3*Scale;
   Letter[23][3].y = 1*Scale;
   Letter[23][4].x = 0*Scale;
   Letter[23][4].y = 3*Scale;
   Letter[23][5].x = 1*Scale;
   Letter[23][5].y = 4*Scale;
   Letter[23][6].x = 2*Scale;
   Letter[23][6].y = 4*Scale;
   Letter[23][7].x = 3*Scale;
   Letter[23][7].y = 3*Scale;
   Letter[23][8].x = 0*Scale;
   Letter[23][8].y = 1*Scale;
// 9
   Letter[24][MAX_POINTS].x = 9;
   Letter[24][0].x = 0*Scale;
   Letter[24][0].y = 4*Scale;
   Letter[24][1].x = 2*Scale;
   Letter[24][1].y = 4*Scale;
   Letter[24][2].x = 3*Scale;
   Letter[24][2].y = 3*Scale;
   Letter[24][3].x = 3*Scale;
   Letter[24][3].y = 1*Scale;
   Letter[24][4].x = 2*Scale;
   Letter[24][4].y = 0*Scale;
   Letter[24][5].x = 1*Scale;
   Letter[24][5].y = 0*Scale;
   Letter[24][6].x = 0*Scale;
   Letter[24][6].y = 1*Scale;
   Letter[24][7].x = 0*Scale;
   Letter[24][7].y = 2*Scale;
   Letter[24][8].x = 3*Scale;
   Letter[24][8].y = 2*Scale;
// :
   Letter[25][MAX_POINTS].x = 2;
   Letter[25][0].x = 2*Scale;
   Letter[25][0].y = 1*Scale;
   Letter[25][1].x = 2*Scale;
   Letter[25][1].y = 3*Scale;
// ;
   Letter[26][MAX_POINTS].x = 3;
   Letter[26][0].x = 2*Scale;
   Letter[26][0].y = 1*Scale;
   Letter[26][1].x = 2*Scale;
   Letter[26][1].y = 3*Scale;
   Letter[26][2].x = 1*Scale;
   Letter[26][2].y = 4*Scale;
// <
   Letter[27][MAX_POINTS].x = 3;
   Letter[27][0].x = 3*Scale;
   Letter[27][0].y = 1*Scale;
   Letter[27][1].x = 0*Scale;
   Letter[27][1].y = 2*Scale;
   Letter[27][2].x = 3*Scale;
   Letter[27][2].y = 3*Scale;
// =
   Letter[28][MAX_POINTS].x = 4;
   Letter[28][0].x = 3*Scale;
   Letter[28][0].y = 1*Scale;
   Letter[28][1].x = 0*Scale;
   Letter[28][1].y = 1*Scale;
   Letter[28][2].x = 0*Scale;
   Letter[28][2].y = 3*Scale;
   Letter[28][3].x = 3*Scale;
   Letter[28][3].y = 3*Scale;
// >
   Letter[29][MAX_POINTS].x = 3;
   Letter[29][0].x = 0*Scale;
   Letter[29][0].y = 1*Scale;
   Letter[29][1].x = 3*Scale;
   Letter[29][1].y = 2*Scale;
   Letter[29][2].x = 0*Scale;
   Letter[29][2].y = 3*Scale;
// ?
   Letter[30][MAX_POINTS].x = 7;
   Letter[30][0].x = 0*Scale;
   Letter[30][0].y = 1*Scale;
   Letter[30][1].x = 1*Scale;
   Letter[30][1].y = 0*Scale;
   Letter[30][2].x = 2*Scale;
   Letter[30][2].y = 0*Scale;
   Letter[30][3].x = 3*Scale;
   Letter[30][3].y = 1*Scale;
   Letter[30][4].x = 3*Scale;
   Letter[30][4].y = 2*Scale;
   Letter[30][5].x = 2*Scale;
   Letter[30][5].y = 3*Scale;
   Letter[30][6].x = 2*Scale;
   Letter[30][6].y = 4*Scale;
// @
   Letter[31][MAX_POINTS].x = 12;
   Letter[31][0].x = 3*Scale;
   Letter[31][0].y = 4*Scale;
   Letter[31][1].x = 1*Scale;
   Letter[31][1].y = 4*Scale;
   Letter[31][2].x = 0*Scale;
   Letter[31][2].y = 3*Scale;
   Letter[31][3].x = 0*Scale;
   Letter[31][3].y = 1*Scale;
   Letter[31][4].x = 1*Scale;
   Letter[31][4].y = 0*Scale;
   Letter[31][5].x = 2*Scale;
   Letter[31][5].y = 0*Scale;
   Letter[31][6].x = 3*Scale;
   Letter[31][6].y = 1*Scale;
   Letter[31][7].x = 3*Scale;
   Letter[31][7].y = 2*Scale;
   Letter[31][8].x = 2*Scale;
   Letter[31][8].y = 3*Scale;
   Letter[31][9].x = 1*Scale;
   Letter[31][9].y = 2*Scale;
   Letter[31][10].x = 2*Scale;
   Letter[31][10].y = 1*Scale;
   Letter[31][11].x = 3*Scale;
   Letter[31][11].y = 1*Scale;
// A
   Letter[32][MAX_POINTS].x = 6;
   Letter[32][0].x = 0*Scale;
   Letter[32][0].y = 4*Scale;
   Letter[32][1].x = 0*Scale;
   Letter[32][1].y = 0*Scale;
   Letter[32][2].x = 3*Scale;
   Letter[32][2].y = 0*Scale;
   Letter[32][3].x = 3*Scale;
   Letter[32][3].y = 4*Scale;
   Letter[32][4].x = 3*Scale;
   Letter[32][4].y = 2*Scale;
   Letter[32][5].x = 0*Scale;
   Letter[32][5].y = 2*Scale;
// B
   Letter[33][MAX_POINTS].x = 8;
   Letter[33][0].x = 0*Scale;
   Letter[33][0].y = 0*Scale;
   Letter[33][1].x = 0*Scale;
   Letter[33][1].y = 4*Scale;
   Letter[33][2].x = 3*Scale;
   Letter[33][2].y = 4*Scale;
   Letter[33][3].x = 3*Scale;
   Letter[33][3].y = 3*Scale;
   Letter[33][4].x = 0*Scale;
   Letter[33][4].y = 2*Scale;
   Letter[33][5].x = 3*Scale;
   Letter[33][5].y = 1*Scale;
   Letter[33][6].x = 3*Scale;
   Letter[33][6].y = 0*Scale;
   Letter[33][7].x = 0*Scale;
   Letter[33][7].y = 0*Scale;
// C
   Letter[34][MAX_POINTS].x = 6;
   Letter[34][0].x = 3*Scale;
   Letter[34][0].y = 0*Scale;
   Letter[34][1].x = 1*Scale;
   Letter[34][1].y = 0*Scale;
   Letter[34][2].x = 0*Scale;
   Letter[34][2].y = 1*Scale;
   Letter[34][3].x = 0*Scale;
   Letter[34][3].y = 3*Scale;
   Letter[34][4].x = 1*Scale;
   Letter[34][4].y = 4*Scale;
   Letter[34][5].x = 3*Scale;
   Letter[34][5].y = 4*Scale;
// D
   Letter[35][MAX_POINTS].x = 6;
   Letter[35][0].x = 0*Scale;
   Letter[35][0].y = 0*Scale;
   Letter[35][1].x = 0*Scale;
   Letter[35][1].y = 4*Scale;
   Letter[35][2].x = 1*Scale;
   Letter[35][2].y = 4*Scale;
   Letter[35][3].x = 3*Scale;
   Letter[35][3].y = 2*Scale;
   Letter[35][4].x = 1*Scale;
   Letter[35][4].y = 0*Scale;
   Letter[35][5].x = 0*Scale;
   Letter[35][5].y = 0*Scale;
// E
   Letter[36][MAX_POINTS].x = 7;
   Letter[36][0].x = 3*Scale;
   Letter[36][0].y = 0*Scale;
   Letter[36][1].x = 0*Scale;
   Letter[36][1].y = 0*Scale;
   Letter[36][2].x = 0*Scale;
   Letter[36][2].y = 2*Scale;
   Letter[36][3].x = 2*Scale;
   Letter[36][3].y = 2*Scale;
   Letter[36][4].x = 0*Scale;
   Letter[36][4].y = 2*Scale;
   Letter[36][5].x = 0*Scale;
   Letter[36][5].y = 4*Scale;
   Letter[36][6].x = 3*Scale;
   Letter[36][6].y = 4*Scale;
// F
   Letter[37][MAX_POINTS].x = 6;
   Letter[37][0].x = 3*Scale;
   Letter[37][0].y = 0*Scale;
   Letter[37][1].x = 0*Scale;
   Letter[37][1].y = 0*Scale;
   Letter[37][2].x = 0*Scale;
   Letter[37][2].y = 2*Scale;
   Letter[37][3].x = 2*Scale;
   Letter[37][3].y = 2*Scale;
   Letter[37][4].x = 0*Scale;
   Letter[37][4].y = 2*Scale;
   Letter[37][5].x = 0*Scale;
   Letter[37][5].y = 4*Scale;
// G
   Letter[38][MAX_POINTS].x = 6;
   Letter[38][0].x = 3*Scale;
   Letter[38][0].y = 0*Scale;
   Letter[38][1].x = 0*Scale;
   Letter[38][1].y = 0*Scale;
   Letter[38][2].x = 0*Scale;
   Letter[38][2].y = 4*Scale;
   Letter[38][3].x = 3*Scale;
   Letter[38][3].y = 4*Scale;
   Letter[38][4].x = 3*Scale;
   Letter[38][4].y = 2*Scale;
   Letter[38][5].x = 1*Scale;
   Letter[38][5].y = 2*Scale;
// H
   Letter[39][MAX_POINTS].x = 6;
   Letter[39][0].x = 0*Scale;
   Letter[39][0].y = 0*Scale;
   Letter[39][1].x = 0*Scale;
   Letter[39][1].y = 4*Scale;
   Letter[39][2].x = 0*Scale;
   Letter[39][2].y = 2*Scale;
   Letter[39][3].x = 3*Scale;
   Letter[39][3].y = 2*Scale;
   Letter[39][4].x = 3*Scale;
   Letter[39][4].y = 0*Scale;
   Letter[39][5].x = 3*Scale;
   Letter[39][5].y = 4*Scale;
// I
   Letter[40][MAX_POINTS].x = 6;
   Letter[40][0].x = 1*Scale;
   Letter[40][0].y = 0*Scale;
   Letter[40][1].x = 3*Scale;
   Letter[40][1].y = 0*Scale;
   Letter[40][2].x = 2*Scale;
   Letter[40][2].y = 0*Scale;
   Letter[40][3].x = 2*Scale;
   Letter[40][3].y = 4*Scale;
   Letter[40][4].x = 1*Scale;
   Letter[40][4].y = 4*Scale;
   Letter[40][5].x = 3*Scale;
   Letter[40][5].y = 4*Scale;
// J
   Letter[41][MAX_POINTS].x = 6;
   Letter[41][0].x = 1*Scale;
   Letter[41][0].y = 0*Scale;
   Letter[41][1].x = 3*Scale;
   Letter[41][1].y = 0*Scale;
   Letter[41][2].x = 2*Scale;
   Letter[41][2].y = 0*Scale;
   Letter[41][3].x = 2*Scale;
   Letter[41][3].y = 4*Scale;
   Letter[41][4].x = 0*Scale;
   Letter[41][4].y = 4*Scale;
   Letter[41][5].x = 0*Scale;
   Letter[41][5].y = 3*Scale;
// K
   Letter[42][MAX_POINTS].x = 6;
   Letter[42][0].x = 0*Scale;
   Letter[42][0].y = 0*Scale;
   Letter[42][1].x = 0*Scale;
   Letter[42][1].y = 4*Scale;
   Letter[42][2].x = 0*Scale;
   Letter[42][2].y = 2*Scale;
   Letter[42][3].x = 3*Scale;
   Letter[42][3].y = 0*Scale;
   Letter[42][4].x = 0*Scale;
   Letter[42][4].y = 2*Scale;
   Letter[42][5].x = 3*Scale;
   Letter[42][5].y = 4*Scale;
// L
   Letter[43][MAX_POINTS].x = 3;
   Letter[43][0].x = 0*Scale;
   Letter[43][0].y = 0*Scale;
   Letter[43][1].x = 0*Scale;
   Letter[43][1].y = 4*Scale;
   Letter[43][2].x = 3*Scale;
   Letter[43][2].y = 4*Scale;
// M
   Letter[44][MAX_POINTS].x = 6;
   Letter[44][0].x = 0*Scale;
   Letter[44][0].y = 4*Scale;
   Letter[44][1].x = 0*Scale;
   Letter[44][1].y = 0*Scale;
   Letter[44][2].x = 1*Scale;
   Letter[44][2].y = 2*Scale;
   Letter[44][3].x = 2*Scale;
   Letter[44][3].y = 2*Scale;
   Letter[44][4].x = 3*Scale;
   Letter[44][4].y = 0*Scale;
   Letter[44][5].x = 3*Scale;
   Letter[44][5].y = 4*Scale;
// N
   Letter[45][MAX_POINTS].x = 4;
   Letter[45][0].x = 0*Scale;
   Letter[45][0].y = 4*Scale;
   Letter[45][1].x = 0*Scale;
   Letter[45][1].y = 0*Scale;
   Letter[45][2].x = 3*Scale;
   Letter[45][2].y = 4*Scale;
   Letter[45][3].x = 3*Scale;
   Letter[45][3].y = 0*Scale;
// O
   Letter[46][MAX_POINTS].x = 9;
   Letter[46][0].x = 0*Scale;
   Letter[46][0].y = 1*Scale;
   Letter[46][1].x = 0*Scale;
   Letter[46][1].y = 3*Scale;
   Letter[46][2].x = 1*Scale;
   Letter[46][2].y = 4*Scale;
   Letter[46][3].x = 2*Scale;
   Letter[46][3].y = 4*Scale;
   Letter[46][4].x = 3*Scale;
   Letter[46][4].y = 3*Scale;
   Letter[46][5].x = 3*Scale;
   Letter[46][5].y = 1*Scale;
   Letter[46][6].x = 2*Scale;
   Letter[46][6].y = 0*Scale;
   Letter[46][7].x = 1*Scale;
   Letter[46][7].y = 0*Scale;
   Letter[46][8].x = 0*Scale;
   Letter[46][8].y = 1*Scale;
// P
   Letter[47][MAX_POINTS].x = 5;
   Letter[47][0].x = 0*Scale;
   Letter[47][0].y = 4*Scale;
   Letter[47][1].x = 0*Scale;
   Letter[47][1].y = 0*Scale;
   Letter[47][2].x = 3*Scale;
   Letter[47][2].y = 0*Scale;
   Letter[47][3].x = 3*Scale;
   Letter[47][3].y = 2*Scale;
   Letter[47][4].x = 0*Scale;
   Letter[47][4].y = 2*Scale;
// Q
   Letter[48][MAX_POINTS].x = 6;
   Letter[48][0].x = 2*Scale;
   Letter[48][0].y = 3*Scale;
   Letter[48][1].x = 3*Scale;
   Letter[48][1].y = 4*Scale;
   Letter[48][2].x = 0*Scale;
   Letter[48][2].y = 4*Scale;
   Letter[48][3].x = 0*Scale;
   Letter[48][3].y = 0*Scale;
   Letter[48][4].x = 3*Scale;
   Letter[48][4].y = 0*Scale;
   Letter[48][5].x = 3*Scale;
   Letter[48][5].y = 4*Scale;
// R
   Letter[49][MAX_POINTS].x = 6;
   Letter[49][0].x = 0*Scale;
   Letter[49][0].y = 4*Scale;
   Letter[49][1].x = 0*Scale;
   Letter[49][1].y = 0*Scale;
   Letter[49][2].x = 3*Scale;
   Letter[49][2].y = 0*Scale;
   Letter[49][3].x = 3*Scale;
   Letter[49][3].y = 2*Scale;
   Letter[49][4].x = 0*Scale;
   Letter[49][4].y = 2*Scale;
   Letter[49][5].x = 3*Scale;
   Letter[49][5].y = 4*Scale;
// S
   Letter[50][MAX_POINTS].x = 8;
   Letter[50][0].x = 3*Scale;
   Letter[50][0].y = 0*Scale;
   Letter[50][1].x = 1*Scale;
   Letter[50][1].y = 0*Scale;
   Letter[50][2].x = 0*Scale;
   Letter[50][2].y = 1*Scale;
   Letter[50][3].x = 1*Scale;
   Letter[50][3].y = 2*Scale;
   Letter[50][4].x = 2*Scale;
   Letter[50][4].y = 2*Scale;
   Letter[50][5].x = 3*Scale;
   Letter[50][5].y = 3*Scale;
   Letter[50][6].x = 2*Scale;
   Letter[50][6].y = 4*Scale;
   Letter[50][7].x = 0*Scale;
   Letter[50][7].y = 4*Scale;
// T
   Letter[51][MAX_POINTS].x = 4;
   Letter[51][0].x = 1*Scale;
   Letter[51][0].y = 0*Scale;
   Letter[51][1].x = 3*Scale;
   Letter[51][1].y = 0*Scale;
   Letter[51][2].x = 2*Scale;
   Letter[51][2].y = 0*Scale;
   Letter[51][3].x = 2*Scale;
   Letter[51][3].y = 4*Scale;
// U
   Letter[52][MAX_POINTS].x = 6;
   Letter[52][0].x = 0*Scale;
   Letter[52][0].y = 0*Scale;
   Letter[52][1].x = 0*Scale;
   Letter[52][1].y = 3*Scale;
   Letter[52][2].x = 1*Scale;
   Letter[52][2].y = 4*Scale;
   Letter[52][3].x = 2*Scale;
   Letter[52][3].y = 4*Scale;
   Letter[52][4].x = 3*Scale;
   Letter[52][4].y = 3*Scale;
   Letter[52][5].x = 3*Scale;
   Letter[52][5].y = 0*Scale;
// V
   Letter[53][MAX_POINTS].x = 4;
   Letter[53][0].x = 0*Scale;
   Letter[53][0].y = 0*Scale;
   Letter[53][1].x = 1*Scale;
   Letter[53][1].y = 4*Scale;
   Letter[53][2].x = 2*Scale;
   Letter[53][2].y = 4*Scale;
   Letter[53][3].x = 3*Scale;
   Letter[53][3].y = 0*Scale;
// W
   Letter[54][MAX_POINTS].x = 6;
   Letter[54][0].x = 0*Scale;
   Letter[54][0].y = 0*Scale;
   Letter[54][1].x = 0*Scale;
   Letter[54][1].y = 4*Scale;
   Letter[54][2].x = 1*Scale;
   Letter[54][2].y = 3*Scale;
   Letter[54][3].x = 2*Scale;
   Letter[54][3].y = 3*Scale;
   Letter[54][4].x = 3*Scale;
   Letter[54][4].y = 4*Scale;
   Letter[54][5].x = 3*Scale;
   Letter[54][5].y = 0*Scale;
// X
   Letter[55][MAX_POINTS].x = 7;
   Letter[55][0].x = 1*Scale;
   Letter[55][0].y = 0*Scale;
   Letter[55][1].x = 2*Scale;
   Letter[55][1].y = 2*Scale;
   Letter[55][2].x = 3*Scale;
   Letter[55][2].y = 0*Scale;
   Letter[55][3].x = 2*Scale;
   Letter[55][3].y = 2*Scale;
   Letter[55][4].x = 1*Scale;
   Letter[55][4].y = 4*Scale;
   Letter[55][5].x = 2*Scale;
   Letter[55][5].y = 2*Scale;
   Letter[55][6].x = 3*Scale;
   Letter[55][6].y = 4*Scale;
// Y
   Letter[56][MAX_POINTS].x = 5;
   Letter[56][0].x = 1*Scale;
   Letter[56][0].y = 0*Scale;
   Letter[56][1].x = 2*Scale;
   Letter[56][1].y = 2*Scale;
   Letter[56][2].x = 3*Scale;
   Letter[56][2].y = 0*Scale;
   Letter[56][3].x = 2*Scale;
   Letter[56][3].y = 2*Scale;
   Letter[56][4].x = 2*Scale;
   Letter[56][4].y = 4*Scale;
// Z
   Letter[57][MAX_POINTS].x = 4;
   Letter[57][0].x = 0*Scale;
   Letter[57][0].y = 0*Scale;
   Letter[57][1].x = 3*Scale;
   Letter[57][1].y = 0*Scale;
   Letter[57][2].x = 0*Scale;
   Letter[57][2].y = 4*Scale;
   Letter[57][3].x = 3*Scale;
   Letter[57][3].y = 4*Scale;

  /**************************/
 /* Render text requested. */
/**************************/
   for (Digit = 0; Digit < MAX_TEXT && TextString[Digit]; ++Digit)
   {
      if (TextString[Digit] == '\n')
      {
         xOffset = xOffsetOrig;
         yOffset += 5*Scale + 2;
      }
      else if (TextString[Digit] >= '!' && TextString[Digit] <= 'Z')
      {
         for (Count = 0; Count < Letter[TextString[Digit]-'!'][MAX_POINTS].x; ++Count)
         {
            DisplayFrame[Digit][Count].x = Letter[TextString[Digit]-'!'][Count].x + xOffset;
            DisplayFrame[Digit][Count].y = Letter[TextString[Digit]-'!'][Count].y + yOffset;
         }
         DisplayFrame[Digit][MAX_POINTS].x = Letter[TextString[Digit]-'!'][MAX_POINTS].x;
         xOffset += 4*Scale;
      }
      else
         xOffset += 4*Scale;
   }
}



void Text::SetVisible(short NewVisible)
{
   if (NewVisible != LastVisible)
   {
      Visible = NewVisible;
      LastVisible = Visible;
      FlashVisible = Visible;
      Active = true;
      FrameCount = Frames;
   }
}



short Text::GetVisible()
{
   return Active;
}
