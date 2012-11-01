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
#ifndef CGAME_H
    #define CGAME_H

#include "cGlobals.h"
#include "cFiles.h"
#include "cMap.h"
//#include "cAudio.h"

class cGame {
    public:
        cGame();
        virtual ~cGame();
        
        bool OnInitGame(SDL_Surface* Display);
        void OnRenderGame();
        void OnEventGame(SDL_Event* Event);
        void OnLoopGame();
        //void OnExitGame();
        
        bool GetGameExit();
        void SetGameExit(bool blnExit);
        
    private:
        std::string gam_MapName;
        std::string gam_MapPath;
        bool gam_Exit;
        bool gam_Loaded;
        
        
        cFiles gam_Files;
        cMap   gam_Map;
        //std::vector<cAudio> gam_Audio;
        
        
        SDL_Surface* gam_SurfDisplay;
        
        struct GAME_STATE_T
        {
            int gameState;
        } GAME_STATE;
};
#endif	/* CGAME_H */