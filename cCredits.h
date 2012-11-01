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
#ifndef CCREDITS_H
    #define CCREDITS_H

#include "cDefines.h"
#include "cGlobals.h"
#include "cFont.h"

class cCredits {
    public:
        cCredits();
        virtual ~cCredits();
        
        bool OnInitCred(SDL_Surface* Display);
        void OnEventCred(SDL_Event* Event);
        void OnLoopCred();
        void OnRenderCred();
        void OnCleanUpCred();
        /// Setting running status flag
        void SetCreditsRunning(bool blnRunning);
        /// Get running status flag
        bool GetCreditsRunning();
        /// Setting exit status flag
        void SetCreditsExit(bool blnExit);
        /// Get exit status flag
        bool GetCreditsExit();
        
    private:
        /// Alpha Blend
        int  crd_AlphaBlend;
        /// Flag status
        bool crd_Running;
        bool crd_Exit;
        /// Main surfaces
        SDL_Surface*  crd_SurfDisplay;
//        SDL_Surface*  crd_SurfLogos;
//        SDL_Surface*  crd_SurfSokoban;
        SDL_Surface*  crd_SurfBackground;
        /// Vector of HUD bitmap fonts
        std::vector<cFont> crd_Font;
};
#endif	/* CCREDITS_H */