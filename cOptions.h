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
#ifndef COPTIONS_H
    #define COPTIONS_H

#include "cGlobals.h"
#include "cDefines.h"
#include "cFont.h"

class cOptions {
    public:
        cOptions();
        virtual ~cOptions();
        /// Main methods
        bool OnInitOpt(SDL_Surface* Display);
        void OnEventOpt(SDL_Event* Event);
        void OnLoopOpt();
        void OnRenderOpt();
        void OnCleanUpOpt();
        /// Setting running status flag
        void SetOptionsRunning(bool blnRunning);
        /// Get running status flag
        bool GetOptionsRunning();
        /// Setting exit status flag
        void SetOptionsExit(bool blnExit);
        /// Get exit status flag
        bool GetOptionsExit();
        
    private:
        /// Flag status
        bool opt_Running;
        bool opt_Exit;
        /// Main surfaces
        SDL_Surface*  opt_SurfDisplay;
//        SDL_Surface*  opt_SurfLogos;
        SDL_Surface*  opt_SurfBackground;
        /// Vector of HUD bitmap fonts
        std::vector<cFont> opt_Font;
        /// Animation object
};
#endif	/* COPTIONS_H */