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
#include "cMenu.h"

cMenu::cMenu()
{
    mnu_TotalFonts       = 5;
    mnu_IdMenu           = MENU_PLAY;
    mnu_Option           = STATE_MENU;
    mnu_Running          = false;
    mnu_Exit             = false;
    mnu_ReloadSurfaces   = false;
    mnu_AppVersion       = "";
    mnu_SurfDisplay      = NULL;
    mnu_SurfBackground   = NULL;
    MENU_STATE.menuState = MENU_PLAY;
}

cMenu::~cMenu()
{
    SDL_FreeSurface(mnu_SurfBackground);
}

bool cMenu::OnInitMenu(SDL_Surface* Display)
{
    /// Load Fonts
    std::string Files[5] = {"./fonts/font1_16x16.png", "./fonts/font2_16x16.png", "./fonts/font6_08x08.png", "./fonts/font0_6x8.png", "./fonts/font9_8x17.png"};
    for (int TotalFonts = 0; TotalFonts<mnu_TotalFonts; TotalFonts++)
    {
        cFont m_tmpFont;
        if (!m_tmpFont.OnLoadDefaults(Files[TotalFonts].c_str()))
        {
            return false;
        }
        mnu_Font.push_back(m_tmpFont);
    }
    if ((mnu_SurfBackground = cSurface::OnLoadResolution("./gfx/", "msurface_", g_ScreenW, g_ScreenH)) == NULL)
    {
        return false;
    }
    /// Font menu out focus
    mnu_Font[FONT_MENU_OUTFOCUS].SetFontParameters(33, 131, 16, 16, FONT_HORIZONTAL);
    /// Font menu on focus
    mnu_Font[FONT_MENU_ONFOCUS].SetFontParameters(33, 131, 16, 16, FONT_HORIZONTAL);
    /// Font menu tooltip
    mnu_Font[FONT_MENU_TOOLTIP].SetFontParameters(33, 131, 8, 8, FONT_HORIZONTAL);
    /// Font menu system 1 (full ascii)
    mnu_Font[FONT_SYSTEM_1].SetFontParameters(33, 254, 6, 8, FONT_HORIZONTAL);
    /// Font menu system 2
    mnu_Font[FONT_SYSTEM_2].SetFontParameters(33, 90, 8, 17, FONT_HORIZONTAL);
    /// Load Sound Bank
    mnu_Sounds.clear();
    std::string tmpSoundBank[2] = {"./media/menu_step.wav", "./media/menu_select.wav"};
    for (int k=0; k<2; k++)
    {
        cSound tmpSound;
        if (!tmpSound.OnInitSnd())
        {
            fprintf(stdout, "ERROR: unable to initialize soundbank ..");
            return false;
        }
        if (!tmpSound.OnLoadSnd(tmpSoundBank[k]))
        {
            fprintf(stdout, "ERROR: unable to load sounds ..");
            return false;
        }
        mnu_Sounds.push_back(tmpSound);
    }
    /// Get display surface
    mnu_SurfDisplay = Display;
    mnu_Running     = true;
    
    return true;
}

void cMenu::OnRenderMenu()
{
    int posY, posH;
    
    posY = ((g_ScreenH-mnu_Font[FONT_MENU_ONFOCUS].GetFontHeight())/2)-(2*mnu_Font[FONT_MENU_ONFOCUS].GetFontHeight());
    posH = mnu_Font[FONT_MENU_ONFOCUS].GetFontHeight()+10;
    
    mnu_Font[FONT_MENU_OUTFOCUS].SetRGB(0, 0, 0);
    mnu_Font[FONT_MENU_ONFOCUS].SetRGB(0, 0, 0);
    mnu_Font[FONT_MENU_TOOLTIP].SetRGB(0, 0, 0);
    
    cSurface::OnDraw(mnu_SurfDisplay, mnu_SurfBackground, 0, 0);
    
    /// Writes version info on bottom display
    mnu_Font[FONT_SYSTEM_1].DrawTextString(GetSDLVersionCompile(), 8, g_ScreenH-16, mnu_SurfDisplay);
    
    switch (MENU_STATE.menuState)
    {
        case MENU_PLAY:
        {
            mnu_Font[FONT_MENU_ONFOCUS].DrawTextString(g_LangStrings.ReadLabel(0), posY-(2*posH), true, mnu_SurfDisplay);
            mnu_Font[FONT_MENU_OUTFOCUS].DrawTextString(g_LangStrings.ReadLabel(2), posY-posH, true, mnu_SurfDisplay);
            mnu_Font[FONT_MENU_OUTFOCUS].DrawTextString(g_LangStrings.ReadLabel(4), posY, true, mnu_SurfDisplay);
            mnu_Font[FONT_MENU_OUTFOCUS].DrawTextString(g_LangStrings.ReadLabel(6), posY+posH, true, mnu_SurfDisplay);
            mnu_Font[FONT_MENU_OUTFOCUS].DrawTextString(g_LangStrings.ReadLabel(8), posY+(2*posH), true, mnu_SurfDisplay);
            mnu_Font[FONT_MENU_TOOLTIP].DrawTextString(g_LangStrings.ReadLabel(1), g_ScreenH-16, true, mnu_SurfDisplay);
            break;
        }
        case MENU_MAP_EDITOR:
        {
            mnu_Font[FONT_MENU_OUTFOCUS].DrawTextString(g_LangStrings.ReadLabel(0), posY-(2*posH), true, mnu_SurfDisplay);
            mnu_Font[FONT_MENU_ONFOCUS].DrawTextString(g_LangStrings.ReadLabel(2), posY-posH, true, mnu_SurfDisplay);
            mnu_Font[FONT_MENU_OUTFOCUS].DrawTextString(g_LangStrings.ReadLabel(4), posY, true, mnu_SurfDisplay);
            mnu_Font[FONT_MENU_OUTFOCUS].DrawTextString(g_LangStrings.ReadLabel(6), posY+posH, true, mnu_SurfDisplay);
            mnu_Font[FONT_MENU_OUTFOCUS].DrawTextString(g_LangStrings.ReadLabel(8), posY+(2*posH), true, mnu_SurfDisplay);
            mnu_Font[FONT_MENU_TOOLTIP].DrawTextString(g_LangStrings.ReadLabel(3), g_ScreenH-16, true, mnu_SurfDisplay);
            break;
        }
        case MENU_OPTIONS:
        {
            mnu_Font[FONT_MENU_OUTFOCUS].DrawTextString(g_LangStrings.ReadLabel(0), posY-(2*posH), true, mnu_SurfDisplay);
            mnu_Font[FONT_MENU_OUTFOCUS].DrawTextString(g_LangStrings.ReadLabel(2), posY-posH, true, mnu_SurfDisplay);
            mnu_Font[FONT_MENU_ONFOCUS].DrawTextString(g_LangStrings.ReadLabel(4), posY, true, mnu_SurfDisplay);
            mnu_Font[FONT_MENU_OUTFOCUS].DrawTextString(g_LangStrings.ReadLabel(6), posY+posH, true, mnu_SurfDisplay);
            mnu_Font[FONT_MENU_OUTFOCUS].DrawTextString(g_LangStrings.ReadLabel(8), posY+(2*posH), true, mnu_SurfDisplay);
            mnu_Font[FONT_MENU_TOOLTIP].DrawTextString(g_LangStrings.ReadLabel(5), g_ScreenH-16, true, mnu_SurfDisplay);
            break;
        }
        case MENU_CREDITS:
        {
            mnu_Font[FONT_MENU_OUTFOCUS].DrawTextString(g_LangStrings.ReadLabel(0), posY-(2*posH), true, mnu_SurfDisplay);
            mnu_Font[FONT_MENU_OUTFOCUS].DrawTextString(g_LangStrings.ReadLabel(2), posY-posH, true, mnu_SurfDisplay);
            mnu_Font[FONT_MENU_OUTFOCUS].DrawTextString(g_LangStrings.ReadLabel(4), posY, true, mnu_SurfDisplay);
            mnu_Font[FONT_MENU_ONFOCUS].DrawTextString(g_LangStrings.ReadLabel(6), posY+posH, true, mnu_SurfDisplay);
            mnu_Font[FONT_MENU_OUTFOCUS].DrawTextString(g_LangStrings.ReadLabel(8), posY+(2*posH), true, mnu_SurfDisplay);
            mnu_Font[FONT_MENU_TOOLTIP].DrawTextString(g_LangStrings.ReadLabel(7), g_ScreenH-16, true, mnu_SurfDisplay);
            break;
        }
        case MENU_QUIT:
        {
            mnu_Font[FONT_MENU_OUTFOCUS].DrawTextString(g_LangStrings.ReadLabel(0), posY-(2*posH), true, mnu_SurfDisplay);
            mnu_Font[FONT_MENU_OUTFOCUS].DrawTextString(g_LangStrings.ReadLabel(2), posY-posH, true, mnu_SurfDisplay);
            mnu_Font[FONT_MENU_OUTFOCUS].DrawTextString(g_LangStrings.ReadLabel(4), posY, true, mnu_SurfDisplay);
            mnu_Font[FONT_MENU_OUTFOCUS].DrawTextString(g_LangStrings.ReadLabel(6), posY+posH, true, mnu_SurfDisplay);
            mnu_Font[FONT_MENU_ONFOCUS].DrawTextString(g_LangStrings.ReadLabel(8), posY+(2*posH), true, mnu_SurfDisplay);
            mnu_Font[FONT_MENU_TOOLTIP].DrawTextString(g_LangStrings.ReadLabel(9), g_ScreenH-16, true, mnu_SurfDisplay);
            break;
        }
    }
}

void cMenu::OnEventMenu(SDL_Event* Event)
{
    switch (Event->type) {
        case SDL_KEYDOWN:
        {
            switch (Event->key.keysym.sym)
            {
                case SDLK_UP:
                {
                    if (mnu_IdMenu > MENU_PLAY)
                    {
                        mnu_Sounds[0].PlaySnd();
                        mnu_IdMenu--;
                    }
                    MENU_STATE.menuState = mnu_IdMenu;
                    break;
                }
                case SDLK_DOWN:
                {
                    if (mnu_IdMenu < MENU_QUIT)
                    {
                        mnu_Sounds[0].PlaySnd();
                        mnu_IdMenu++;
                    }
                    MENU_STATE.menuState = mnu_IdMenu;
                    break;
                }
                case SDLK_ESCAPE:
                {
                    mnu_Exit    = true;
                    mnu_Running = false;
                    mnu_Option  = STATE_MENU;
                    break;
                }
                case SDLK_RETURN:
                {
                    mnu_Sounds[1].PlaySnd();
                    mnu_Running = false;
                    mnu_Option  = MENU_STATE.menuState;
                    break;
                }
                case SDLK_F5:
                {
                    mnu_ReloadSurfaces = true;
                }
                
            }
            break;
        }
    }
}

void cMenu::OnLoopMenu()
{
    if (mnu_ReloadSurfaces)
    {
        ReloadSurfaces();
        mnu_ReloadSurfaces = false;
    }
}

void cMenu::SetMenuExit(bool blnExit)
{
    mnu_Exit = blnExit;
}

bool cMenu::GetMenuExit()
{
    return mnu_Exit;
}

void cMenu::SetMenuRunning(bool blnRunning)
{
    mnu_Running = blnRunning;
}

bool cMenu::GetMenuRunning()
{
    return mnu_Running;
}

int cMenu::GetMenuOption()
{
    return mnu_Option;
}

void cMenu::SetMenuOption(int Value)
{
    mnu_Option = Value;
}

bool cMenu::ReloadSurfaces()
{
    if ((mnu_SurfBackground = cSurface::OnLoadResolution("./gfx/", "msurface_", g_ScreenW, g_ScreenH)) == NULL)
    {
        fprintf(stdout, "ERROR: unable to reload background surface .. %s", SDL_GetError());
        return false;
    }
    
    return true;
}