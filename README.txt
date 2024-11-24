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


Install Packages Required To Make Application
=============================================

Asteroids game written in C++ using SDL to provide cross platform builds for
Linux, Apple, Windows and Android.

YouTube: https://youtube.com/DevelopIT/
GitHub: https://github.com/BirchJD/AsteroidsSDL


# REDHAT LINUX INSTALL REQUIRED PACKAGES:
yum install make
yum install gcc
yum install g++
yum install libsdl2-dev

# DEBIAN LINUX INSTALL REQUIRED PACKAGES:
apt-get install make
apt-get install gcc
apt-get install g++
apt-get install libsdl2-dev

# APPLE OSX INSTALL GCODE FROM APPLE STORE
# DRAG SDL2 FRAMEWORK INTO /Library/frameworks/

# ANDROID INSTALL REQUIRED PACKAGES:
c4droid >= V8.0


Make Application
================
make clean

# MAKE FOR LINUX
make linux

# MAKE FOR WINDOWS
make windows

# MAKE FOR APPLE
make apple


Run Application
===============
./Asteroids

Keys:
ESC		Exit Application
1			New Game
UP			Thrust
DOWN		Hyperspace
LEFT		Rotate Counter Clockwise
RIGHT		Rotate Clockwise
SHIFT		Fire

Mouse/Touchpad implemented for Android operation, touch/click High Score on
the display (top center) to display on screen controls.
