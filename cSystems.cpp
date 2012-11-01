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
#include "cSystems.h"
#include "cIni.h"

cSystems::cSystems()
{
    sys_WindowTitle = "2D ENGINE v0.5b";
    sys_Flags       = SDL_DOUBLEBUF;
    sys_Display     = NULL;
    sys_Flags       = 0;
}

cSystems::~cSystems()
{
}

void cSystems::sysReadIni(std::string filename)
{
    struct stat info;
    int    ret = -1;

    ret = stat(filename.c_str(), &info);
    if (ret != 0)
    {
        /// If ini file not found, write default values
        cIni sys_IniW;
        sys_IniW.Load("./config.ini");
        /// Write default values
        sys_IniW.WriteString("Settings",  "Language", "ENU");
        sys_IniW.WriteString("Settings", "XsbPath", "./maps/");
        sys_IniW.WriteInteger("Settings", "Strings", 20);
        sys_IniW.WriteInteger("Settings", "Shot", 0);
        sys_IniW.WriteBoolean("Settings", "PlaySound", false);
        sys_IniW.WriteBoolean("Settings", "PlayMusic", false);
        sys_IniW.WriteBoolean("Settings", "ShowFps", false);
        sys_IniW.WriteInteger("Display",  "Width", 800);
        sys_IniW.WriteInteger("Display",  "Height", 600);
        sys_IniW.WriteInteger("Display",  "BPP", 32);
        sys_IniW.WriteBoolean("Display",  "Fullscreen", false);
        sys_IniW.WriteString("Surfaces",  "TileSurface", "./tilesets/tileset01_224.png");
        sys_IniW.WriteInteger("Surfaces", "TileW", 32);
        sys_IniW.WriteInteger("Surfaces", "TileH", 32);
        /// Write Editor Default Values
        sys_IniW.WriteString("Editor", "Title",      "SDL Sokoban");
        sys_IniW.WriteString("Editor", "Author",     "sdlSokoban");
        sys_IniW.WriteString("Editor", "Collection", "Introduction");
        sys_IniW.WriteString("Editor", "AuthorMail", "sdlsokoban@gmail.com");
        sys_IniW.WriteString("Editor", "AuthorPage", "sdlSokoban.com");
        sys_IniW.WriteString("Editor", "Level",      "1");
        sys_IniW.WriteString("Editor", "Date",       "2012/01");
        sys_IniW.WriteString("Editor", "Comment",    "No comments");
    }
    else
    {
        /// Open and read values from .ini file
        cIni sys_IniR;
        sys_IniR.Load("./config.ini");
        /// Display parameters
        g_ScreenW     = sys_IniR.ReadInteger("Display", "Width",      800);
        g_ScreenH     = sys_IniR.ReadInteger("Display", "Height",     600);
        g_Bpp         = sys_IniR.ReadInteger("Display", "BPP",        32);
        g_FullScreen  = sys_IniR.ReadBoolean("Display", "Fullscreen", false);
        /// Sound and Music flags
        g_PlaySound   = sys_IniR.ReadBoolean("Settings", "PlaySound", false);
        g_PlayMusic   = sys_IniR.ReadBoolean("Settings", "PlayMusic", false);
        /// Show fps counter
        g_ShowFps     = sys_IniR.ReadBoolean("Settings", "ShowFps", false);
        /// Tileset specifications
        switch (g_ScreenW)
        {
            case 800:
            {
                g_MainSurface = "./gfx/msurface_800_600.png";
                break;
            }
            case 1024:
            {
                if (g_ScreenH == 600)
                {
                    g_MainSurface = "./gfx/msurface_1024_600.png";
                }
                else if (g_ScreenH == 768)
                {
                    g_MainSurface = "./gfx/msurface_1024_768.png";
                }
                break;
            }
            case 1152:
            {
                g_MainSurface = "./gfx/msurface_1152_864.png";
                break;
            }
            case 1280:
            {
                if (g_ScreenH == 720)
                {
                    g_MainSurface = "./gfx/msurface_1280_720.png";
                }
                else if (g_ScreenH == 800)
                {
                    g_MainSurface = "./gfx/msurface_1280_800.png";
                }
                else if (g_ScreenH == 1024)
                {
                    g_MainSurface = "./gfx/msurface_1280_1024.png";
                }
                break;
            }
            case 1366:
            {
                g_MainSurface = "./gfx/msurface_1366_768.png";
                break;
            }
            case 1440:
            {
                g_MainSurface = "./gfx/msurface_1440_900.png";
                break;
            }
            case 1600:
            {
                g_MainSurface = "./gfx/msurface_1600_900.png";
                break;
            }
            case 1680:
            {
                g_MainSurface = "./gfx/msurface_1680_1050.png";
                break;
            }
            case 1920:
            {
                g_MainSurface = "./gfx/msurface_1920_1080.png";
                break;
            }
            default:
            {
                g_ScreenW = 800;
                g_ScreenH = 600;
                g_MainSurface = "./gfx/msurface_800_600.png";
                fprintf(stdout, "ERROR: screen resolution does not supported ..\n");
                fprintf(stdout, "Supported Resolutions are: 800x600, 1024x600, 1024x768,\n");
                fprintf(stdout, "     1152x864, 1280x720, 1280x800, 1280x1024, 1366x768,\n");
                fprintf(stdout, "     1440x900, 1600x900, 1680x1050 and 1920x1080.\n");
            }
        }
        /// Tile Information
        g_TileSurface = sys_IniR.ReadString("Surfaces",  "TileSurface", "./tilesets/tileset01_224.png");
        g_TileW       = sys_IniR.ReadInteger("Surfaces", "TileW",       32);
        g_TileH       = sys_IniR.ReadInteger("Surfaces", "TileH",       32);
        g_LangType    = sys_IniR.ReadString("Settings",  "Language",    "ENU");
        g_LangTotal   = sys_IniR.ReadInteger("Settings", "Strings",     15);
        /// Read Path of Puzzles (Xsb Maps)
        g_XsbPath     = sys_IniR.ReadString("Settings", "XsbPath", "./maps/");
        /// Read Editor Informations
        g_Title       = sys_IniR.ReadString("Editor", "Title",      "SDL Sokoban");
        g_Author      = sys_IniR.ReadString("Editor", "Author",     "sdlSokoban");
        g_Collection  = sys_IniR.ReadString("Editor", "Collection", "Introduction");
        g_AuthorMail  = sys_IniR.ReadString("Editor", "AuthorMail", "sdlsokoban@gmail.com");
        g_AuthorPage  = sys_IniR.ReadString("Editor", "AuthorPage", "sdlSokoban.com");
        g_Level       = sys_IniR.ReadString("Editor", "Level",      "1");
        g_Date        = sys_IniR.ReadString("Editor", "Date",       "2012/01");
        g_Comment     = sys_IniR.ReadString("Editor", "Comment",    "No comments");
    }
    if (!FileExists("./language.ini"))
    {
        fprintf(stdout, "ERROR: language file not found ..");
        exit(1);
    }
    else
    {
        g_LangStrings.LoadLanguageFile("./language.ini", g_LangType, g_LangTotal);
    }
}

bool cSystems::sysInitVideo()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        return false;
    }
    
    sysReadIni("./config.ini");
    
    const SDL_VideoInfo* videoInfo = SDL_GetVideoInfo();
    if (videoInfo->hw_available)
    {
        sys_Flags |= SDL_HWSURFACE;
    } else {
        sys_Flags |= SDL_SWSURFACE;
    }
    if (videoInfo->blit_hw)
    {
        sys_Flags |= SDL_HWACCEL;
    }
    atexit(SDL_Quit);
    
    putenv("SDL_VIDEO_WINDOW_POS=center");
    putenv("SDL_VIDEO_CENTERED=1");
    
    if (g_FullScreen)
    {
        sys_Flags |= SDL_FULLSCREEN;
    }
    if ((sys_Display = SDL_SetVideoMode(g_ScreenW, g_ScreenH, g_Bpp, sys_Flags)) == NULL)
    {
        return false;
    }
    SDL_WM_SetCaption(sys_WindowTitle.c_str(), NULL);
    
    return true;    
}

int cSystems::sysGetWidth()
{
    return g_ScreenW;
}

int cSystems::sysGetHeight()
{
    return g_ScreenH;
}

void cSystems::sysToggleFullScreen()
{
    g_FullScreen = !g_FullScreen;
    
    if (sys_Display != NULL)
    {
        if (!g_FullScreen)
        {
            sys_Display = SDL_SetVideoMode(g_ScreenW, g_ScreenH, g_Bpp, sys_Flags|SDL_FULLSCREEN);
        }
        else
        {
            sys_Display = SDL_SetVideoMode(g_ScreenW, g_ScreenH, g_Bpp, sys_Flags);
        }
    }
}

void cSystems::sysClearScreen()
{
}

bool cSystems::sysResizeWindow(int Width, int Height)
{
    if (Height == 0)
    {
        Height = 1;
    }
    sys_Display = SDL_SetVideoMode(Width, Height, g_Bpp, sys_Flags);

    if (sys_Display == NULL)
    {
        return false;
    }
    return true;
}

SDL_Surface* cSystems::sysGetDisplaySurface()
{
    return sys_Display;
}