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
#ifndef CMENU_H
    #define CMENU_H

#include "cGlobals.h"
#include "cFont.h"
#include "cSound.h"

class cMenu {
    public:
        cMenu();
        virtual ~cMenu();
        /// Initializes menu class
        bool OnInitMenu(SDL_Surface* Display);
        /// Render method
        void OnRenderMenu();
        /// Parse events
        void OnEventMenu(SDL_Event* Event);
        /// Check menu status and other adjusts
        void OnLoopMenu();
        /// Setting running status flag
        void SetMenuRunning(bool blnRunning);
        /// Get running status flag
        bool GetMenuRunning();
        /// Setting exit status flag
        void SetMenuExit(bool blnExit);
        /// Get exit status flag
        bool GetMenuExit();
        /// Setting active menu option
        void SetMenuOption(int Value);
        /// Get menu option active
        int  GetMenuOption();
        /// Reload Surfaces
        bool ReloadSurfaces();
        
    private:
        /// Misc controls
        int mnu_TotalFonts;
        int mnu_IdMenu;
        int mnu_Option;
        /// Flag status
        bool mnu_Running;
        bool mnu_Exit;
        /// Flag for reload status
        bool mnu_ReloadSurfaces;
        /// Application version
        std::string mnu_AppVersion;
        /// Main surfaces
        SDL_Surface*  mnu_SurfBackground;
        SDL_Surface*  mnu_SurfDisplay;
        /// Vector of HUD bitmap fonts
        vector<cFont> mnu_Font;
        /// Vector sound bank
        vector<cSound> mnu_Sounds;
        /// Menu status flag
        enum
        {
            FONT_MENU_OUTFOCUS,
            FONT_MENU_ONFOCUS,
            FONT_MENU_TOOLTIP,
            FONT_SYSTEM_1,
            FONT_SYSTEM_2
        };
        /// Menu status flag
        struct MENU_STATE_T
        {
            int menuState;
        } MENU_STATE;
        
};
#endif	/* CMENU_H */