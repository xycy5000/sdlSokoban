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
#ifndef CSYSTEMS_H
    #define CSYSTEMS_H

#include "cEvent.h"
#include "cDefines.h"
#include "cGlobals.h"

class cSystems: public cEvent {
    public:
        cSystems();
        ~cSystems();
        
        void sysReadIni(std::string filename);
        bool sysInitVideo();
        bool sysInitAudio();

        void sysToggleFullScreen();
        void sysClearScreen();
        bool sysResizeWindow(int Width, int Height);
        
        int sysGetWidth();
        int sysGetHeight();
    
        SDL_Surface* sysGetDisplaySurface();
        
    private:
        SDL_Surface* sys_Display;
        
        std::string sys_WindowTitle;
        Uint32      sys_Flags;
};
#endif
/* CSYSTEMS_H */