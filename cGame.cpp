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
#include "cGame.h"

cGame::cGame()
{
    gam_MapName = "";
    gam_MapPath = "";
    gam_Exit    = false;
    gam_Loaded  = false;
    GAME_STATE.gameState = GAME_BROWSE_MAP;
}

cGame::~cGame()
{
}

bool cGame::OnInitGame(SDL_Surface* Display)
{
    /// Get Main Surface
    gam_SurfDisplay = Display;
    /// Initializes Sound
    /// Setting Map Path
    gam_MapPath.clear();
    gam_MapPath.append(g_XsbPath);
    gam_MapPath.append("*.xsb");
    /// Initializes File Browse
    if (!gam_Files.OnInitFil(Display, gam_MapPath, 20, (g_ScreenH-(gam_Files.GetBrowseHeight(0)+gam_Files.GetBrowseHeight(1)))/2))
    {
        return false;
    }
    if (!gam_Files.OnLoadFontBrowser("./fonts/font8_12x12.png", 33, 131, 12, 12, FONT_VERTICAL))
    {
        return false;
    }
    /// Passes Generated File list to cMap Class
    gam_Map.SetFileList(gam_Files.GetFileList());
    /// Miscellaneus adjusts
    gam_Files.SetFontRGB(255, 0, 255);
    gam_Exit   = false;
    gam_Loaded = false;
    
    return true;
}

void cGame::OnEventGame(SDL_Event* Event)
{
    switch (GAME_STATE.gameState)
    {
        case GAME_BROWSE_MAP:
        {
            gam_Files.OnEventFil(Event);
            break;
        }
        case GAME_RUN_MAP:
        {
            gam_Map.OnEventMap(Event);
            break;
        }
    }
}

void cGame::OnRenderGame()
{
    switch (GAME_STATE.gameState)
    {
        case GAME_BROWSE_MAP:
        {
            gam_Files.OnRenderFil();
            break;
        }
        case GAME_RUN_MAP:
        {
            gam_Map.OnRenderMap(gam_SurfDisplay);
            break;
        }
    }
}

void cGame::OnLoopGame()
{
    switch (GAME_STATE.gameState)
    {
        case GAME_BROWSE_MAP:
        {
            if (!gam_Files.GetBrowseRunning())
            {
                if (!gam_Files.GetBrowseExit())
                {
                    gam_MapName.append(g_XsbPath);
                    gam_MapName.append(gam_Files.GetActualFileName());
                    GAME_STATE.gameState = GAME_RUN_MAP;
                }
                else
                {
                    gam_Exit = gam_Files.GetBrowseExit();
                }
            }
            break;
        }
        case GAME_RUN_MAP:
        {
            if (!gam_Loaded)
            {
                if (!gam_Map.OnInitMap(gam_MapName))
                {
                    fprintf(stdout, "ERROR: unable to load map %s ..", gam_MapName.c_str());
                    exit(1);
                }
                gam_Loaded = true;
            }
            else
            {
                gam_Map.OnLoopMap();
            }
            if (gam_Map.GetMapExit())
            {
                gam_Loaded  = false;
                gam_MapName = "";
                gam_Files.SetBrowseRunning(true);
                gam_Map.ClearMapVector();
                GAME_STATE.gameState = GAME_BROWSE_MAP;
            }
            break;
        }
    }
}

void cGame::SetGameExit(bool blnExit)
{
    gam_Exit = blnExit;
}

bool cGame::GetGameExit()
{
    return gam_Exit;
}