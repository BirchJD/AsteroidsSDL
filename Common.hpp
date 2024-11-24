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


#ifndef __COMMON_HPP
#define __COMMON_HPP


#include <SDL2/SDL.h>


#define BUFF_SIZE             255

#define WINDOW_WIDTH          640
#define WINDOW_HEIGHT         480

#define COLOUR_BUTTON         0x3F3F3F
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

#define TEXT_SCALE            5
#define MAX_BUTTONS           7
#define BUTTON_WIDTH          128
#define BUTTON_HEIGHT         128
#define BUTTON_HIDE           0
#define BUTTON_START          1
#define BUTTON_ROTATE_LEFT    2
#define BUTTON_ROTATE_RIGHT   3
#define BUTTON_FIRE           4
#define BUTTON_THRUST         5
#define BUTTON_HYPER          6


static const char* GameOverText = "GAME OVER";
static const char* InsertCoinText = "INSERT COIN";

static const char* ButtonText[] =
{
   "", "START", "LEFT", "RIGHT", "FIRE", "THRUST", "HYPER",
};


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


#endif
