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


#ifndef __ASTERIODS_HPP
#define __ASTERIODS_HPP


#define BUFF_SIZE             255

#define COLOUR_SCORE          0x5F5FFF
#define COLOUR_GAME_OVER      0xFF7F7F
#define COLOUR_INSERT_COIN    0x8FFF8F
#define COLOUR_HIGH_SCORE     0xFFFFFF
#define COLOUR_SHOT           0xFFFFFF
#define COLOUR_SHIP_LIFE      0x3F3FFF
#define COLOUR_SHIP           0x7F7FFF
#define COLOUR_ROCK           0xAF00AF
#define COLOUR_UFO            0xFFFF00

#define FLAG_EXIT             0b00000001
#define FLAG_THRUST           0b00000010
#define FLAG_ROTATE_LEFT      0b00000100
#define FLAG_ROTATE_RIGHT     0b00001000


enum
{
   WAV_ROCK = 0,
   WAV_HYPER_SPACE = 1,
   WAV_SHOT = 2,
   WAV_THRUST = 3,
   WAV_UFO = 4,
   WAV_UFO_SHOT = 5,
   WAV_BELT = 6,
   MAX_WAV_FILES = 7
};

enum
{
   START_ROCKS = 5,
   MAX_ROCKS = 100,
   HISCORE_XOFFSET = 55,
   HISCORE_YOFFSET = 20,
   GAMEOVER_XOFFSET = 90,
   GAMEOVER_YOFFSET = 20,
   INSERTCOIN_XOFFSET = 110,
   INSERTCOIN_YOFFSET = 20,
   HISCORE_SCALE = 3
};


typedef struct 
{
   SDL_AudioSpec WavSpec;
   Uint32 WavLength;
   Uint8 *WavBuffer;
} SdlAudioWavType;


int WinMain(int argc, char* argv[]);
int main(int argc, char* argv[]);
void DoFrame(SDL_Renderer* SdlRenderer, SDL_Rect* Desktop, unsigned char Flags);
void DrawGraphics(SDL_Renderer* SdlRenderer);


#endif
