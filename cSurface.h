/*
  SDL SOKOBAN - The Sokoban Game Clone write in C++/SDL
  Copyright (C) 2012 Ericson Norberto <sdlsokoban@gmail.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#ifndef CSURFACE_H
    #define CSURFACE_H

#include "cDefines.h"
#include "cGlobals.h"

class cSurface {
   public:
       cSurface();
       ~cSurface();

   public:
       static SDL_Surface* OnLoad(std::string File);
       static SDL_Surface* OnLoadResolution(std::string Path, std::string PrefixName, int ScreenW = g_ScreenW, int ScreenH = g_ScreenH);
       static bool OnDraw(SDL_Surface* Destination, SDL_Surface* Source, int X, int Y);
       static bool OnDraw(SDL_Surface* Destination, SDL_Surface* Source, int dX, int dY, int sX, int sY, int sW, int sH);
       static bool Transparent(SDL_Surface* Destination, int R = 0, int G = 0, int B = 0);
       static bool FillArea(SDL_Surface* Destination, SDL_Surface* Source, int X, int Y, int W, int H, int R = 0, int G = 0, int B = 0);
};
#endif
/* CSURFACE_H */