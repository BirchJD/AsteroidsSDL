# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.


MAKEFLAGS += --silent

EXE = Asteroids

CC = g++

LINUX_INCDIRS = -I/usr/local/include
LINUX_LIBDIRS = -L/usr/local/lib
LINUX_LIBS = -lSDL2
LINUX_CFLAGS = $(LINUX_INCDIRS)

WIN_INCDIRS = 
WIN_LIBDIRS = -L/usr/local/lib -L./
WIN_LIBS = -lSDL2
WIN_CFLAGS = $(WIN_INCDIRS)

APPLE_INCDIRS = -w -F /Library/Frameworks -framework SDL2
APPLE_LIBDIRS = 
APPLE_LIBS = 
APPLE_CFLAGS = $(APPLE_INCDIRS)


linux: clean $(EXE).o ; printf ">>> BUILDING FOR $@ <<<\n"
	   $(CC) $(LINUX_CFLAGS) -c *.cpp
	   $(CC) $(LINUX_CFLAGS) -o $(EXE) $(LINUX_LIBDIRS) *.o $(LINUX_LIBS)

windows: clean $(EXE).o ; printf ">>> BUILDING FOR $@ <<<\n"
	   $(CC) $(WIN_CFLAGS) -c *.cpp
	   $(CC) $(WIN_CFLAGS) -o $(EXE) $(WIN_LIBDIRS) *.o $(WIN_LIBS)

apple: clean ; printf ">>> BUILDING FOR $@ <<<\n"
	   $(CC) $(APPLE_CFLAGS) -c *.cpp
	   $(CC) $(APPLE_CFLAGS) -o $(EXE) $(APPLE_LIBDIRS) *.o $(APPLE_LIBS)

clean:
	rm -f *.o

