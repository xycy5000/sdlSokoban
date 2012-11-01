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
#include "cOptions.h"

cOptions::cOptions()
{
}

cOptions::~cOptions()
{
}

bool cOptions::OnInitOpt(SDL_Surface* Display)
{
    std::string Files[1] = {"./fonts/font3_12x12.png"};
    /// Load Fonts
    for (int TotalFonts = 0; TotalFonts<1; TotalFonts++)
    {
        cFont m_tmpFont;
        if (!m_tmpFont.OnLoadDefaults(Files[TotalFonts].c_str()))
        {
            fprintf(stdout, "ERROR: unable to register font surface %s ..", Files[TotalFonts].c_str());
            return false;
        }
        opt_Font.push_back(m_tmpFont);
    }
    /// Initializes Font
    opt_Font[FONT_FAST].SetFontParameters(33, 131, 12, 12, FONT_VERTICAL);
    /// Load Surfaces
    if ((opt_SurfBackground = cSurface::OnLoadResolution("./gfx/", "bkg_", g_ScreenW, g_ScreenH)) == NULL)
    {
        fprintf(stdout, "ERROR: unable to load surface ..");
        return false;
    }
//    if ((opt_SurfLogos = cSurface::OnLoad("./gfx/logo03_600.png")) == NULL)
//    {
//        fprintf(stdout, "ERROR: unable to load surface ..");
//        return false;
//    }
    /// Enable key repeat
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
    /// Flag options
    opt_Running     = true;
    opt_Exit        = false;
    /// Stores main display surface
    opt_SurfDisplay = Display;
    
    return true;
}

void cOptions::OnRenderOpt()
{
    int tmpPosY;
    int tmpPosZ;
    
    /// Draw surfaces
    cSurface::OnDraw(opt_SurfDisplay, opt_SurfBackground, 0, 0);
//    cSurface::OnDraw(crd_SurfDisplay, crd_SurfSokoban, 50, 50, 0, 0, 288, 320);
    /// First Y position
    tmpPosY = 80;
    /// Increment line
    tmpPosZ = opt_Font[FONT_FAST].GetFontHeight()+5;
    /// Draw credit text
    opt_Font[FONT_FAST].DrawTextString("SDL SOKOBAN - The Sokoban Game Clone Write in C++/SDL", tmpPosY+(0*tmpPosZ), true, opt_SurfDisplay);
    opt_Font[FONT_FAST].DrawTextString("Copyright (C) 2012 Ericson Norberto <sdlsokoban@gmail.com>", tmpPosY+(1*tmpPosZ), true, opt_SurfDisplay);
    opt_Font[FONT_FAST].DrawTextString("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", tmpPosY+(2*tmpPosZ), true, opt_SurfDisplay);
    opt_Font[FONT_FAST].DrawTextString("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", tmpPosY+(3*tmpPosZ), true, opt_SurfDisplay);
    opt_Font[FONT_FAST].DrawTextString("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", tmpPosY+(4*tmpPosZ), true, opt_SurfDisplay);
    opt_Font[FONT_FAST].DrawTextString("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", tmpPosY+(5*tmpPosZ), true, opt_SurfDisplay);
    opt_Font[FONT_FAST].DrawTextString("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", tmpPosY+(6*tmpPosZ), true, opt_SurfDisplay);
    opt_Font[FONT_FAST].DrawTextString("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", tmpPosY+(7*tmpPosZ), true, opt_SurfDisplay);
    opt_Font[FONT_FAST].DrawTextString("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", tmpPosY+(8*tmpPosZ), true, opt_SurfDisplay);
    opt_Font[FONT_FAST].DrawTextString("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", tmpPosY+(9*tmpPosZ), true, opt_SurfDisplay);
    opt_Font[FONT_FAST].DrawTextString("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", tmpPosY+(10*tmpPosZ), true, opt_SurfDisplay);
    opt_Font[FONT_FAST].DrawTextString("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", tmpPosY+(11*tmpPosZ), true, opt_SurfDisplay);
    opt_Font[FONT_FAST].DrawTextString("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", tmpPosY+(12*tmpPosZ), true, opt_SurfDisplay);
    opt_Font[FONT_FAST].DrawTextString("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", tmpPosY+(13*tmpPosZ), true, opt_SurfDisplay);
    opt_Font[FONT_FAST].DrawTextString("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", tmpPosY+(14*tmpPosZ), true, opt_SurfDisplay);
    opt_Font[FONT_FAST].DrawTextString("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", tmpPosY+(15*tmpPosZ), true, opt_SurfDisplay);
}

void cOptions::OnEventOpt(SDL_Event* Event)
{
    switch (Event->type)
    {
        case SDL_KEYDOWN:
        {
            switch (Event->key.keysym.sym)
            {
                case SDLK_ESCAPE:
                {
                    opt_Running = false;
                    opt_Exit    = true;
                    OnCleanUpOpt();
                    break;
                }
                case SDLK_F5:
                {
                    if (!SetVideoMode(1280, 720, 32, opt_SurfDisplay))
                    {
                    }
                    g_ScreenW = 1280;
                    g_ScreenH = 720;
                    g_Bpp     = 32;
                    break;
                }
                case SDLK_F8:
                {
                    ToggleFullScreen(opt_SurfDisplay);
                    break;
                }
            }
        }
    }
}

void cOptions::OnLoopOpt()
{
}

void cOptions::SetOptionsRunning(bool blnRunning)
{
    opt_Running = blnRunning;
}

bool cOptions::GetOptionsRunning()
{
    return opt_Running;
}

void cOptions::SetOptionsExit(bool blnExit)
{
    opt_Exit = blnExit;
}

bool cOptions::GetOptionsExit()
{
    return opt_Exit;
}

void cOptions::OnCleanUpOpt()
{
//    SDL_FreeSurface(opt_SurfLogos);
    SDL_FreeSurface(opt_SurfBackground);
}