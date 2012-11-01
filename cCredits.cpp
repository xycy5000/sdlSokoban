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
#include "cCredits.h"

cCredits::cCredits()
{
    crd_SurfDisplay    = NULL;
    crd_SurfBackground = NULL;
//    crd_SurfLogos      = NULL;
//    crd_SurfSokoban    = NULL;
}

cCredits::~cCredits()
{
}

bool cCredits::OnInitCred(SDL_Surface* Display)
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
        crd_Font.push_back(m_tmpFont);
    }
    /// Initializes Font
    crd_Font[FONT_FAST].SetFontParameters(33, 131, 12, 12, FONT_VERTICAL);
    /// Load Surfaces
    if ((crd_SurfBackground = cSurface::OnLoadResolution("./gfx/", "bkg_", g_ScreenW, g_ScreenH)) == NULL)
    {
        fprintf(stdout, "ERROR: unable to load surface ..");
        return false;
    }
//    if ((crd_SurfLogos = cSurface::OnLoad("./gfx/logo03_600.png")) == NULL)
//    {
//        fprintf(stdout, "ERROR: unable to load surface ..");
//        return false;
//    }
//    if ((crd_SurfSokoban = cSurface::OnLoad("./gfx/sokoban_01.png")) == NULL)
//    {
//        fprintf(stdout, "ERROR: unable to load surface ..");
//        return false;
//    }
    /// Enable key repeat
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
    crd_AlphaBlend  = SDL_ALPHA_OPAQUE;
    crd_Running     = true;
    crd_Exit        = false;
    crd_SurfDisplay = Display;
    
    return true;
}

void cCredits::OnRenderCred()
{
    int tmpPosY;
    int tmpPosZ;
    
    /// Draw surfaces
    cSurface::OnDraw(crd_SurfDisplay, crd_SurfBackground, 0, 0);
//    cSurface::OnDraw(crd_SurfDisplay, crd_SurfSokoban, 50, 50, 0, 0, 288, 320);
    /// First Y position
    tmpPosY = 80;
    /// Increment line
    tmpPosZ = crd_Font[FONT_FAST].GetFontHeight()+5;
    /// Draw credit text
    crd_Font[FONT_FAST].DrawTextString("SDL SOKOBAN - The Sokoban Game Clone Write in C++/SDL", tmpPosY+(0*tmpPosZ), true, crd_SurfDisplay);
    crd_Font[FONT_FAST].DrawTextString("Copyright (C) 2012 Ericson Norberto <sdlsokoban@gmail.com>", tmpPosY+(1*tmpPosZ), true, crd_SurfDisplay);
    crd_Font[FONT_FAST].DrawTextString("Sokoban e um tipo de quebra-cabecas, no qual o jogador empurra", tmpPosY+(5*tmpPosZ), true, crd_SurfDisplay);
    crd_Font[FONT_FAST].DrawTextString("caixas em torno de um deposito, tentando leva-los a locais  de", tmpPosY+(6*tmpPosZ), true, crd_SurfDisplay);
    crd_Font[FONT_FAST].DrawTextString("armazenamento.", tmpPosY+(7*tmpPosZ), true, crd_SurfDisplay);
    crd_Font[FONT_FAST].DrawTextString("Sokoban foi criado em 1981 por Hiroyuki Imabayashi e publicado", tmpPosY+(10*tmpPosZ), true, crd_SurfDisplay);
    crd_Font[FONT_FAST].DrawTextString("em 1982 por Thinking Rabbit, uma software-house  com  sede  em", tmpPosY+(11*tmpPosZ), true, crd_SurfDisplay);
    crd_Font[FONT_FAST].DrawTextString("Takarazuka no Japao.", tmpPosY+(12*tmpPosZ), true, crd_SurfDisplay);
    crd_Font[FONT_FAST].DrawTextString("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", tmpPosY+(15*tmpPosZ)+4, true, crd_SurfDisplay);
    crd_Font[FONT_FAST].DrawTextString("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", tmpPosY+(16*tmpPosZ)+4, true, crd_SurfDisplay);
    crd_Font[FONT_FAST].DrawTextString("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", tmpPosY+(17*tmpPosZ)+4, true, crd_SurfDisplay);
    crd_Font[FONT_FAST].DrawTextString("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", tmpPosY+(18*tmpPosZ)+4, true, crd_SurfDisplay);
    crd_Font[FONT_FAST].DrawTextString("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", tmpPosY+(19*tmpPosZ)+4, true, crd_SurfDisplay);
    crd_Font[FONT_FAST].DrawTextString("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", tmpPosY+(20*tmpPosZ)+4, true, crd_SurfDisplay);
    crd_Font[FONT_FAST].DrawTextString("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", tmpPosY+(21*tmpPosZ)+4, true, crd_SurfDisplay);
    crd_Font[FONT_FAST].DrawTextString("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", tmpPosY+(22*tmpPosZ)+4, true, crd_SurfDisplay);
    /// Defines alpha for surface
//    SDL_SetAlpha(crd_SurfSokoban, SDL_SRCALPHA, crd_AlphaBlend);
}

void cCredits::OnEventCred(SDL_Event* Event)
{
    switch (Event->type)
    {
        case SDL_KEYDOWN:
        {
            switch (Event->key.keysym.sym)
            {
                case SDLK_ESCAPE:
                {
                    crd_Running = false;
                    crd_Exit    = true;
                    OnCleanUpCred();
                    break;
                }
                case SDLK_PAGEUP:
                {
                    if (crd_AlphaBlend < SDL_ALPHA_OPAQUE)
                    {
                        crd_AlphaBlend++;
                    }
                    break;
                }
                case SDLK_PAGEDOWN:
                {
                    if (crd_AlphaBlend > SDL_ALPHA_TRANSPARENT)
                    {
                        crd_AlphaBlend--;
                    }
                    break;
                }
            }
        }
    }
}

void cCredits::OnLoopCred()
{
}

void cCredits::SetCreditsRunning(bool blnRunning)
{
    crd_Running = blnRunning;
}

bool cCredits::GetCreditsRunning()
{
    return crd_Running;
}

void cCredits::SetCreditsExit(bool blnExit)
{
    crd_Exit = blnExit;
}

bool cCredits::GetCreditsExit()
{
    return crd_Exit;
}

void cCredits::OnCleanUpCred()
{
//    SDL_FreeSurface(crd_SurfLogos);
//    SDL_FreeSurface(crd_SurfSokoban);
    SDL_FreeSurface(crd_SurfBackground);
}