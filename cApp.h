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
#ifndef CAPP_H
    #define CAPP_H

#include "cTime.h"
#include "cSystems.h"
#include "cGame.h"
#include "cEditor.h"
#include "cMenu.h"
#include "cCredits.h"
#include "cOptions.h"
#include "cSound.h"

class cApp: public cSystems {
    public:
        cApp();
        ~cApp();

        bool OnInit();
        int  OnExecute();
        void OnEvent(SDL_Event* Event);
        void OnRender();
        void OnLoop();
        void OnCleanup();
        void OnExit();
        
    private:
        /// Menu object
        cMenu app_Menu;
        /// Game object
        cGame app_Game;
        /// Map editor object
        cEditor app_Editor;
        /// Game options
        cOptions app_Options;
        /// Game credits screen
        cCredits app_Credits;
        /// App Sound Bank
        std::vector<cSound> app_Sounds;
        /// FPS controls
        cTime app_FPS;
        cTime app_FPSUpdate;
        string app_MaxFPS;
        int   app_Frame;
        /// State Controls
        bool app_Running;
        bool app_GameInit;
        bool app_EditorInit;
        bool app_OptionsInit;
        bool app_CreditsInit;
        /// Main Surface
        SDL_Surface* app_Display;
        SDL_Event    app_Event;
        
        struct APP_STATE_T
        {
            int appState;
        } APP_STATE;
};
#endif /* CAPP_H */