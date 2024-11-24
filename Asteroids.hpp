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


#include <stdio.h>
#include <time.h>
#include "Common.hpp"
#include "Text.hpp"
#include "Button.hpp"
#include "AstroShip.hpp"
#include "Astro_UFO.hpp"
#include "AstroRock.hpp"


int WinMain(int argc, char* argv[]);
int main(int argc, char* argv[]);
void NewGame(SDL_Rect& Desktop);
void DoFrame(SDL_Renderer* SdlRenderer, SDL_Rect* Desktop, unsigned char Flags);
void DrawGraphics(SDL_Renderer* SdlRenderer);


#endif
