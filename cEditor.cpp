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
#include "cEditor.h"

cEditor::cEditor()
{
    edt_PosX              = 0;
    edt_PosY              = 0;
    edt_RctBackground.x   = 0;
    edt_RctBackground.y   = 0;
    edt_RctBackground.w   = 0;
    edt_RctBackground.h   = 0;
    edt_RctTextBox.x      = 0;
    edt_RctTextBox.y      = 0;
    edt_RctTextBox.w      = 0;
    edt_RctTextBox.h      = 0;
    edt_RctCurMouse.x     = 0;
    edt_RctCurMouse.y     = 0;
    edt_RctCurMouse.w     = 18;
    edt_RctCurMouse.h     = 25;
    edt_MouseX            = 0;
    edt_MouseY            = 0;
    edt_CursorType        = CURSOR_ARROW;
    edt_MouseDownUp       = false;
    edt_Running           = true;
    edt_Exit              = false;
    edt_TileR             = 0;
    edt_TileG             = 0;
    edt_TileB             = 0;
    edt_TileType          = TILE_FLOOR;
    edt_TilePlayer        = TILE_FLOOR;
    edt_TypeOfMap         = MAP_FILE_XSB;
    edt_TotalBlocksOnGoal = 0;
    edt_SrfTileSet        = NULL;
    edt_SrfDisplay        = NULL;
    edt_SrfTextBox        = NULL;
    edt_SrfHUD            = NULL;
    edt_SrfBackground     = NULL;
    edt_SrfCurMouse       = NULL;
    
    MAP_EDIT_STATE.editState = MAP_EDIT_RENDER;
}

cEditor::~cEditor()
{
    SDL_FreeSurface(edt_SrfHUD);
    SDL_FreeSurface(edt_SrfTileSet);
    SDL_FreeSurface(edt_SrfTextBox);
    SDL_FreeSurface(edt_SrfBackground);
    SDL_FreeSurface(edt_SrfCurMouse);

    SDL_EnableUNICODE(SDL_DISABLE);
}

bool cEditor::OnInitEdt(SDL_Surface* Display)
{
    edt_TileList.clear();
    if ((edt_SrfBackground = cSurface::OnLoadResolution("./gfx/", "bkg_", g_ScreenW, g_ScreenH)) == NULL)
    {
        fprintf(stdout, "ERROR: unable to load background surface ..");
        return false;
    }
    if ((edt_SrfTileSet = cSurface::OnLoad("./tilesets/tileset02_768.png")) == NULL)
    {
        fprintf(stdout, "ERROR: unable to load tileset surface ..");
        return false;
    }
    if ((edt_SrfTextBox = cSurface::OnLoad("./gfx/textbox01_368.png")) == NULL)
    {
        fprintf(stdout, "ERROR: unable to load textbox surface ..");
        return false;
    }
    if ((edt_SrfHUD = cSurface::OnLoad("./gfx/surface02_248.png")) == NULL)
    {
        fprintf(stdout, "ERROR: unable to load HUD surface ..");
        return false;
    }
    if ((edt_SrfToolBox = cSurface::OnLoad("./gfx/surface06_488.png")) == NULL)
    {
        fprintf(stdout, "ERROR: unable to load tool surface ..");
        return false;
    }
    if ((edt_SrfCurMouse = cSurface::OnLoad("./gfx/cursor03_68.png")) == NULL)
    {
        fprintf(stdout, "ERROR: unable to load cursor surface ..");
        return false;
    }
    if (!edt_Font.OnLoad("./fonts/font3_12x12.png", 33, 131, 12, 12, FONT_VERTICAL))
    {
        fprintf(stdout, "ERROR: unable to load font surface ..");
        return false;
    }
    /// Load default values
    edt_RctTileset.x    = 0;
    edt_RctTileset.y    = 0;
    edt_RctTileset.w    = g_TileW;
    edt_RctTileset.h    = g_TileH;
    edt_RctBackground.x = 0;
    edt_RctBackground.y = 0;
    edt_RctBackground.w = edt_SrfBackground->w;
    edt_RctBackground.h = edt_SrfBackground->h;
    edt_RctTextBox.x    = 0;
    edt_RctTextBox.y    = 0;
    edt_RctTextBox.w    = edt_SrfTextBox->w;
    edt_RctTextBox.h    = edt_SrfTextBox->h;
    edt_NumLin          = (g_ScreenH-56)/g_TileH;
    edt_NumCol          = (g_ScreenW-160)/g_TileW;
    edt_PlayerX         = 0;
    edt_PlayerY         = 0;
    edt_SrfDisplay      = Display;
    /// Setting map path and file name
    edt_FileName.clear();
    edt_FileName.append(g_XsbPath);
    edt_FileName.append("untitled.xsb");
    /// Load Empty map
    PaintAreaMap(TILE_ID_EMPTY, TILE_NONE);
    /// Setting map screen position
    SetMapXY(1, 1);
    /// Reset map exit status
    SetEditorExit(false);
    /// Setting map running status
    SetEditorRunnig(true);
    /// Enable UNICODE
    SDL_EnableUNICODE(SDL_ENABLE);
    /// Enable Key Repeat on Browse
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
    /// Turns SDL Cursor Off
    SDL_ShowCursor(0);
    
    return true;
}

void cEditor::OnRenderEdt()
{
    int _sX = edt_PosX;
    int _sY = edt_PosY;
    int _sW = 0;
    
    switch (MAP_EDIT_STATE.editState)
    {
        case MAP_EDIT_RENDER:
        {
            /// Draw Background Surface
            cSurface::OnDraw(edt_SrfDisplay, edt_SrfBackground, 0, 0, edt_RctBackground.x, edt_RctBackground.y, edt_RctBackground.w, edt_RctBackground.h);
            /// Draw black selected tile area
            edt_RctBlackArea.x = g_ScreenW-120;
            edt_RctBlackArea.y = g_ScreenH-132;
            edt_RctBlackArea.w = 112;
            edt_RctBlackArea.h = 112;
            SDL_FillRect(edt_SrfDisplay, &edt_RctBlackArea, SDL_MapRGB(edt_SrfDisplay->format, 0, 0, 0));
            /// Draw black game area
            edt_RctBlackArea.x = edt_PosX;
            edt_RctBlackArea.y = edt_PosY;
            edt_RctBlackArea.w = g_ScreenW-160;
            edt_RctBlackArea.h = g_ScreenH-54;
            SDL_FillRect(edt_SrfDisplay, &edt_RctBlackArea, SDL_MapRGB(edt_SrfDisplay->format, 0, 0, 0));
            /// Draw tileset on map area
            for (int _pZ=0; _pZ<edt_TileList.size(); _pZ++)
            {
                if (edt_TileList[_pZ].m_ID == 0)
                {
                    continue;
                }
                _sW = (edt_TileList[_pZ].m_Type)*edt_RctTileset.w;
                _sX = edt_PosX + (edt_TileList[_pZ].m_Col*edt_RctTileset.w);
                _sY = edt_PosY + (edt_TileList[_pZ].m_Lin*edt_RctTileset.h);

                cSurface::Transparent(edt_SrfTileSet, 255, 255, 255);
                cSurface::OnDraw(edt_SrfDisplay, edt_SrfTileSet, _sX, _sY, _sW, 0, edt_RctTileset.w, edt_RctTileset.h);
            }
            /// Change Cursor
            cSurface::Transparent(edt_SrfTileSet, 255, 255, 255);
            cSurface::OnDraw(edt_SrfDisplay, edt_SrfTileSet, (edt_PlayerX+(edt_PosX/edt_RctTileset.w))*edt_RctTileset.w, (edt_PlayerY+(edt_PosY/edt_RctTileset.h))*edt_RctTileset.h, edt_TilePlayer*edt_RctTileset.w, 0, edt_RctTileset.w, edt_RctTileset.h);
            /// Draw Selected Tile
            cSurface::OnDraw(edt_SrfDisplay, edt_SrfTileSet, g_ScreenW-80, g_ScreenH-92, edt_TilePlayer*edt_RctTileset.w, 0, edt_RctTileset.w, edt_RctTileset.h);
            /// Draw Frame HUD
            DrawFrameHUD();
            /// Draw Cursor Mouse
            cSurface::Transparent(edt_SrfCurMouse, 255, 0, 255);
            if (edt_CursorType == CURSOR_PAINT)
            {
                cSurface::OnDraw(edt_SrfDisplay, edt_SrfCurMouse, edt_MouseX, edt_MouseY, edt_RctCurMouse.x, edt_RctCurMouse.y, g_TileW, g_TileH);
            }
            else
            {
                cSurface::OnDraw(edt_SrfDisplay, edt_SrfCurMouse, edt_MouseX, edt_MouseY, edt_RctCurMouse.x, edt_RctCurMouse.y, edt_RctCurMouse.w, edt_RctCurMouse.h);
            }
            /// Actual Tile Selected
            edt_Font.DrawTextString("TILE", g_ScreenW-88, g_ScreenH-155, edt_SrfDisplay);
            break;
        }
        case MAP_EDIT_SAVEFILE:
        {
            //cSurface::FillArea(edt_SrfDisplay, edt_SrfDisplay, 0, g_ScreenH-(edt_Font.GetFontHeight()+5), g_ScreenW, edt_Font.GetFontHeight()+5);
            cSurface::OnDraw(edt_SrfDisplay, edt_SrfTextBox, (g_ScreenW-edt_SrfTextBox->w)/2, (g_ScreenH-edt_SrfTextBox->h)/2);
            if (edt_FileName.length() > 0)
            {
                edt_Font.DrawTextString("ENTER MAP NAME TO SAVE:", 264, 269, edt_SrfDisplay);
                edt_Font.FillArea(edt_SrfDisplay, edt_SrfDisplay, 220, 289, 360, 35);
                edt_Font.DrawTextString(edt_FileName, 220, 301, edt_SrfDisplay);
            }
            /// Draw Cursor Mouse
            cSurface::Transparent(edt_SrfCurMouse, 255, 0, 255);
            if (edt_CursorType == CURSOR_PAINT)
            {
                cSurface::OnDraw(edt_SrfDisplay, edt_SrfCurMouse, edt_MouseX, edt_MouseY, edt_RctCurMouse.x, edt_RctCurMouse.y, g_TileW, g_TileH);
            }
            else
            {
                cSurface::OnDraw(edt_SrfDisplay, edt_SrfCurMouse, edt_MouseX, edt_MouseY, edt_RctCurMouse.x, edt_RctCurMouse.y, edt_RctCurMouse.w, edt_RctCurMouse.h);
            }
            break;
        }
        case MAP_EDIT_LOADFILE:
        {
            //cSurface::FillArea(edt_SrfDisplay, edt_SrfDisplay, 0, g_ScreenH-(edt_Font.GetFontHeight()+5), g_ScreenW, edt_Font.GetFontHeight()+5);
            cSurface::OnDraw(edt_SrfDisplay, edt_SrfTextBox, (g_ScreenW-edt_SrfTextBox->w)/2, (g_ScreenH-edt_SrfTextBox->h)/2);
            if (edt_FileName.length() > 0)
            {
                edt_Font.DrawTextString("ENTER MAP NAME TO LOAD:", 264, 269, edt_SrfDisplay);
                edt_Font.FillArea(edt_SrfDisplay, edt_SrfDisplay, 220, 289, 360, 35);
                edt_Font.DrawTextString(edt_FileName, 220, 301, edt_SrfDisplay);
            }
            /// Draw Cursor Mouse
            cSurface::Transparent(edt_SrfCurMouse, 255, 0, 255);
            if (edt_CursorType == CURSOR_PAINT)
            {
                cSurface::OnDraw(edt_SrfDisplay, edt_SrfCurMouse, edt_MouseX, edt_MouseY, edt_RctCurMouse.x, edt_RctCurMouse.y, g_TileW, g_TileH);
            }
            else
            {
                cSurface::OnDraw(edt_SrfDisplay, edt_SrfCurMouse, edt_MouseX, edt_MouseY, edt_RctCurMouse.x, edt_RctCurMouse.y, edt_RctCurMouse.w, edt_RctCurMouse.h);
            }
            break;
        }
    }
}

void cEditor::OnEventEdt(SDL_Event* Event)
{
    switch (Event->type)
    {
        case SDL_KEYDOWN:
        {
            switch (MAP_EDIT_STATE.editState)
            {
                case MAP_EDIT_RENDER:
                {
                    KeyDownRender(Event->key.keysym.sym, Event->key.keysym.mod, Event->key.keysym.unicode);
                    break;
                }
                case MAP_EDIT_SAVEFILE:
                {
                    KeyDownSaveFile(Event->key.keysym.sym, Event->key.keysym.mod, Event->key.keysym.unicode);
                    break;
                }
                case MAP_EDIT_LOADFILE:
                {
                    KeyDownLoadFile(Event->key.keysym.sym, Event->key.keysym.mod, Event->key.keysym.unicode);
                    break;
                }
                case MAP_EDIT_OVERWRITE:
                {
                    KeyDownOverwrite(Event->key.keysym.sym, Event->key.keysym.mod, Event->key.keysym.unicode);
                    break;
                }
            }
            break;
        }
        case SDL_MOUSEMOTION:
        {
            switch (MAP_EDIT_STATE.editState)
            {
                case MAP_EDIT_RENDER:
                {
                    MouseCursorMove(Event->motion.x, Event->motion.y);
                    if (edt_MouseDownUp)
                    {
                        if ((edt_MouseX >= edt_RctBlackArea.x) && (edt_MouseX <= (edt_RctBlackArea.x+edt_RctBlackArea.w)) && (edt_MouseY >= edt_RctBlackArea.y) & (edt_MouseY <= (edt_RctBlackArea.y+edt_RctBlackArea.h)))
                        {
                            /// Deslocate Mouse Pointer to Center of Tile and Draw Tile in area
                            SetTileType(((edt_MouseX+(g_TileW/2))/g_TileH)-1, ((edt_MouseY+(g_TileH/2))/g_TileW)-1, 3, TILE_ID_DRAW);
                            SetTileType(((edt_MouseX+(g_TileW/2))/g_TileH)-1, ((edt_MouseY+(g_TileH/2))/g_TileW)-1, 4, edt_TileType);
                            /// Update Player Position
                            edt_PlayerX = ((edt_MouseX+(g_TileW/2))/g_TileH)-1;
                            edt_PlayerY = ((edt_MouseY+(g_TileH/2))/g_TileW)-1;
                        }
                    }
                    break;
                }
            }
            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            switch (MAP_EDIT_STATE.editState)
            {
                case MAP_EDIT_RENDER:
                {
                    if (Event->button.button == SDL_BUTTON_LEFT)
                    {
                        MouseButtonDown(Event->button.x, Event->button.y);
                        if ((edt_MouseX >= edt_RctBlackArea.x) && (edt_MouseX <= (edt_RctBlackArea.x+edt_RctBlackArea.w)) && (edt_MouseY >= edt_RctBlackArea.y) & (edt_MouseY <= (edt_RctBlackArea.y+edt_RctBlackArea.h)))
                        {
                            /// Deslocate Mouse Pointer to Center of Tile and Draw Tile in area
                            SetTileType(((edt_MouseX+(g_TileW/2))/g_TileH)-1, ((edt_MouseY+(g_TileH/2))/g_TileW)-1, 3, TILE_ID_DRAW);
                            SetTileType(((edt_MouseX+(g_TileW/2))/g_TileH)-1, ((edt_MouseY+(g_TileH/2))/g_TileW)-1, 4, edt_TileType);
                            /// Update Player Position
                            edt_PlayerX = ((edt_MouseX+(g_TileW/2))/g_TileH)-1;
                            edt_PlayerY = ((edt_MouseY+(g_TileH/2))/g_TileW)-1;
                        }
                        edt_MouseDownUp = true;
                    }
                    break;
                }
            }
            break;
        }
        case SDL_MOUSEBUTTONUP:
        {
            edt_MouseDownUp = false;
            break;
        }
    }
}

void cEditor::OnLoopEdt()
{
    switch (MAP_EDIT_STATE.editState)
    {
        case MAP_EDIT_RENDER:
        {
            break;
        }
        case MAP_EDIT_SAVEFILE:
        {
            break;
        }
        case MAP_EDIT_LOADFILE:
        {
            break;
        }
    }
}

void cEditor::KeyDownRender(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    switch (sym)
    {
        case SDLK_UP:
        {
            MoveKeyUP();
            break;
        }
        case SDLK_DOWN:
        {
            MoveKeyDOWN();
            break;
        }
        case SDLK_LEFT:
        {
            MoveKeyLEFT();
            break;
        }
        case SDLK_RIGHT:
        {
            MoveKeyRIGHT();
            break;
        }
        case SDLK_ESCAPE:
        {
            edt_Running = false;
            edt_Exit    = true;
            SDL_EnableKeyRepeat(0, SDL_DEFAULT_REPEAT_INTERVAL);
            break;
        }
        case SDLK_F5:
        {
            MAP_EDIT_STATE.editState = MAP_EDIT_SAVEFILE;;
            break;
        }
        case SDLK_F6:
        {
            MAP_EDIT_STATE.editState = MAP_EDIT_LOADFILE;
            break;
        }
        case SDLK_F7:
        {
            PaintAreaMap(TILE_ID_EMPTY, TILE_NONE);
            break;
        }
        case SDLK_F8:
        {
            if (edt_TilePlayer != TILE_PLAYER)
            {
                PaintAreaMap(TILE_ID_DRAW, edt_TilePlayer);
            }
            break;
        }
        case SDLK_SPACE:
        {
            SetTileType(edt_PlayerX, edt_PlayerY, 3, TILE_ID_DRAW);
            SetTileType(edt_PlayerX, edt_PlayerY, 4, edt_TileType);
            break;
        }
    }
}

void cEditor::MoveKeyUP()
{
    if (edt_PlayerY > 0)
    {
        edt_PlayerY--;
    }
}

void cEditor::MoveKeyDOWN()
{
    if (edt_PlayerY < ( edt_NumLin-1))
    {
        edt_PlayerY++;
    }
}

void cEditor::MoveKeyLEFT()
{
    if (edt_PlayerX > 0)
    {
        edt_PlayerX--;
    }
}

void cEditor::MoveKeyRIGHT()
{
    if (edt_PlayerX < (edt_NumCol-1))
    {
        edt_PlayerX++;
    }
}

void cEditor::KeyDownSaveFile(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    switch (sym)
    {
        case SDLK_ESCAPE:
        {
            MAP_EDIT_STATE.editState = MAP_EDIT_RENDER;
            break;
        }
        case SDLK_RETURN:
        {
            if (edt_FileName.length() > 8)
            {
                if (!FindString(edt_FileName, ".xsb"))
                {
                    edt_FileName.append(".xsb");
                }
                if (!FileExists(edt_FileName.c_str()))
                {
                    if (!SaveMapFile(edt_FileName.c_str()))
                    {
                        edt_Font.ClearFontArea(edt_SrfDisplay, 0, g_ScreenH-(edt_Font.GetFontHeight()+5), g_ScreenW, edt_Font.GetFontHeight()+5);
                        edt_Font.DrawTextString("ERROR: Unable to save file ..", g_ScreenH-edt_Font.GetFontHeight(), true, edt_SrfDisplay);
                    }
                    else
                    {
                        edt_FileName.clear();
                        edt_FileName.append(g_XsbPath);
                        edt_FileName.append("untitled.xsb");
                        MAP_EDIT_STATE.editState = MAP_EDIT_RENDER;
                    }
                }
                else
                {
                    edt_Font.ClearFontArea(edt_SrfDisplay, 0, g_ScreenH-(edt_Font.GetFontHeight()+5), g_ScreenW, edt_Font.GetFontHeight()+5, 255, 255, 255);
                    edt_Font.DrawTextString("ERROR: file already exists .. overwrite? [Y/N]", g_ScreenH-edt_Font.GetFontHeight(), true, edt_SrfDisplay);
                    MAP_EDIT_STATE.editState = MAP_EDIT_OVERWRITE;
                }
            }
            break;
        }
        case SDLK_BACKSPACE:
        {
            if (edt_FileName.length() > 7)
            {
                edt_FileName.erase(edt_FileName.size()-1);
            }
            break;
        }
        default:
        {
            if (edt_FileName.length() <= 30)
            {
                if (unicode == (Uint16)' ')
                {
                    edt_FileName += (char)unicode;
                }
                else if ((unicode >= (Uint16)'!') && (unicode <= (Uint16)'@'))
                {
                    edt_FileName += (char)unicode;
                }
                else if ((unicode >= (Uint16)'A') && (unicode <= (Uint16)'Z'))
                {
                    edt_FileName += (char)unicode;
                }
                else if ((unicode >= (Uint16)'a') && (unicode <= (Uint16)'z'))
                {
                    edt_FileName += (char)unicode;
                }
            }
            break;
        }
    }
}

void cEditor::MouseCursorMove(int mX, int mY)
{
    edt_MouseX = mX;
    edt_MouseY = mY;
    
    /// First button position in toolbox
    C_POS.PosUx = g_ScreenW-116;
    C_POS.PosUy = 32;
    C_POS.PosDx = C_POS.PosUx+g_TileW;
    C_POS.PosDy = C_POS.PosUy+g_TileH;
    /// Check coordinates of mouse click
    if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= C_POS.PosUy) && (edt_MouseY <= C_POS.PosDy))
    {
        edt_CursorType = CURSOR_LINK;
    }
    else if ((edt_MouseX >= (C_POS.PosUx+36)) && (edt_MouseX <= (C_POS.PosDx+36)) && (edt_MouseY >= C_POS.PosUy) && (edt_MouseY <= C_POS.PosDy))
    {
        edt_CursorType = CURSOR_LINK;
    }
    else if ((edt_MouseX >= (C_POS.PosUx+72)) && (edt_MouseX <= (C_POS.PosDx+72)) && (edt_MouseY >= C_POS.PosUy) && (edt_MouseY <= C_POS.PosDy))
    {
        edt_CursorType = CURSOR_LINK;
    }
    else
    {
        edt_CursorType = CURSOR_ARROW;
    }
    /// Corrdinates of First toolbox column
    C_POS.PosUx = g_ScreenW-116;
    C_POS.PosUy = 76;
    C_POS.PosDx = C_POS.PosUx+g_TileW;
    C_POS.PosDy = C_POS.PosUy+g_TileH;
    /// Check coordinates of mouse click
    if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= C_POS.PosUy) && (edt_MouseY <= C_POS.PosDy))
    {
        edt_CursorType = CURSOR_LINK;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+36)) && (edt_MouseY <= (C_POS.PosDy+36)))
    {
        edt_CursorType = CURSOR_LINK;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+72)) && (edt_MouseY <= (C_POS.PosDy+72)))
    {
        edt_CursorType = CURSOR_LINK;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+108)) && (edt_MouseY <= (C_POS.PosDy+108)))
    {
        edt_CursorType = CURSOR_LINK;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+144)) && (edt_MouseY <= (C_POS.PosDy+144)))
    {
        edt_CursorType = CURSOR_LINK;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+180)) && (edt_MouseY <= (C_POS.PosDy+180)))
    {
        edt_CursorType = CURSOR_LINK;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+216)) && (edt_MouseY <= (C_POS.PosDy+216)))
    {
        edt_CursorType = CURSOR_LINK;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+252)) && (edt_MouseY <= (C_POS.PosDy+252)))
    {
        edt_CursorType = CURSOR_LINK;
    }
    /// Corrdinates of second toolbox column
    C_POS.PosUx = g_ScreenW-80;
    C_POS.PosUy = 76;
    C_POS.PosDx = C_POS.PosUx+g_TileW;
    C_POS.PosDy = C_POS.PosUy+g_TileH;
    /// Check coordinates of mouse click
    if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= C_POS.PosUy) && (edt_MouseY <= C_POS.PosDy))
    {
        edt_CursorType = CURSOR_LINK;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+36)) && (edt_MouseY <= (C_POS.PosDy+36)))
    {
        edt_CursorType = CURSOR_LINK;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+72)) && (edt_MouseY <= (C_POS.PosDy+72)))
    {
        edt_CursorType = CURSOR_LINK;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+108)) && (edt_MouseY <= (C_POS.PosDy+108)))
    {
        edt_CursorType = CURSOR_LINK;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+144)) && (edt_MouseY <= (C_POS.PosDy+144)))
    {
        edt_CursorType = CURSOR_LINK;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+180)) && (edt_MouseY <= (C_POS.PosDy+180)))
    {
        edt_CursorType = CURSOR_LINK;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+216)) && (edt_MouseY <= (C_POS.PosDy+216)))
    {
        edt_CursorType = CURSOR_LINK;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+252)) && (edt_MouseY <= (C_POS.PosDy+252)))
    {
        edt_CursorType = CURSOR_LINK;
    }
    /// Corrdinates of third toolbox column
    C_POS.PosUx = g_ScreenW-44;
    C_POS.PosUy = 76;
    C_POS.PosDx = C_POS.PosUx+g_TileW;
    C_POS.PosDy = C_POS.PosUy+g_TileH;
    /// Check coordinates of mouse click
    if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= C_POS.PosUy) && (edt_MouseY <= C_POS.PosDy))
    {
        edt_CursorType = CURSOR_LINK;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+36)) && (edt_MouseY <= (C_POS.PosDy+36)))
    {
        edt_CursorType = CURSOR_LINK;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+72)) && (edt_MouseY <= (C_POS.PosDy+72)))
    {
        edt_CursorType = CURSOR_LINK;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+108)) && (edt_MouseY <= (C_POS.PosDy+108)))
    {
        edt_CursorType = CURSOR_LINK;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+144)) && (edt_MouseY <= (C_POS.PosDy+144)))
    {
        edt_CursorType = CURSOR_LINK;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+180)) && (edt_MouseY <= (C_POS.PosDy+180)))
    {
        edt_CursorType = CURSOR_LINK;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+216)) && (edt_MouseY <= (C_POS.PosDy+216)))
    {
        edt_CursorType = CURSOR_LINK;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+252)) && (edt_MouseY <= (C_POS.PosDy+252)))
    {
        edt_CursorType = CURSOR_LINK;
    }
    /// Area Map Draw
    if ((edt_MouseX >= edt_RctBlackArea.x) && (edt_MouseX <= (edt_RctBlackArea.x+edt_RctBlackArea.w)) && (edt_MouseY >= edt_RctBlackArea.y) & (edt_MouseY <= (edt_RctBlackArea.y+edt_RctBlackArea.h)))
    {
        edt_CursorType = CURSOR_PAINT;
    }
    /// Change Mouse Cursor
    edt_RctCurMouse.x = edt_CursorType*edt_RctCurMouse.w;
}

void cEditor::MouseButtonDown(int mX, int mY)
{
    edt_MouseX = mX;
    edt_MouseY = mY;
    
    /// First button position in toolbox
    C_POS.PosUx = g_ScreenW-116;
    C_POS.PosUy = 32;
    C_POS.PosDx = C_POS.PosUx+g_TileW;
    C_POS.PosDy = C_POS.PosUy+g_TileH;
    /// Check coordinates of mouse click
    if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= C_POS.PosUy) && (edt_MouseY <= C_POS.PosDy))
    {
        edt_TileType = TILE_FLOOR;
    }
    else if ((edt_MouseX >= (C_POS.PosUx+36)) && (edt_MouseX <= (C_POS.PosDx+36)) && (edt_MouseY >= C_POS.PosUy) && (edt_MouseY <= C_POS.PosDy))
    {
        edt_TileType = TILE_GOAL;
    }
    else if ((edt_MouseX >= (C_POS.PosUx+72)) && (edt_MouseX <= (C_POS.PosDx+72)) && (edt_MouseY >= C_POS.PosUy) && (edt_MouseY <= C_POS.PosDy))
    {
        edt_TileType = TILE_PLAYER;
    }
    /// Corrdinates of First toolbox column
    C_POS.PosUx = g_ScreenW-116;
    C_POS.PosUy = 76;
    C_POS.PosDx = C_POS.PosUx+g_TileW;
    C_POS.PosDy = C_POS.PosUy+g_TileH;
    /// Check coordinates of mouse click
    if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= C_POS.PosUy) && (edt_MouseY <= C_POS.PosDy))
    {
        edt_TileType = 0;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+36)) && (edt_MouseY <= (C_POS.PosDy+36)))
    {
        edt_TileType = 1;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+72)) && (edt_MouseY <= (C_POS.PosDy+72)))
    {
        edt_TileType = 2;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+108)) && (edt_MouseY <= (C_POS.PosDy+108)))
    {
        edt_TileType = 3;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+144)) && (edt_MouseY <= (C_POS.PosDy+144)))
    {
        edt_TileType = 4;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+180)) && (edt_MouseY <= (C_POS.PosDy+180)))
    {
        edt_TileType = 5;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+216)) && (edt_MouseY <= (C_POS.PosDy+216)))
    {
        edt_TileType = 6;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+252)) && (edt_MouseY <= (C_POS.PosDy+252)))
    {
        edt_TileType = 7;
    }
    /// Corrdinates of second toolbox column
    C_POS.PosUx = g_ScreenW-80;
    C_POS.PosUy = 76;
    C_POS.PosDx = C_POS.PosUx+g_TileW;
    C_POS.PosDy = C_POS.PosUy+g_TileH;
    /// Check coordinates of mouse click
    if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= C_POS.PosUy) && (edt_MouseY <= C_POS.PosDy))
    {
        edt_TileType = 8;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+36)) && (edt_MouseY <= (C_POS.PosDy+36)))
    {
        edt_TileType = 9;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+72)) && (edt_MouseY <= (C_POS.PosDy+72)))
    {
        edt_TileType = 10;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+108)) && (edt_MouseY <= (C_POS.PosDy+108)))
    {
        edt_TileType = 11;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+144)) && (edt_MouseY <= (C_POS.PosDy+144)))
    {
        edt_TileType = 12;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+180)) && (edt_MouseY <= (C_POS.PosDy+180)))
    {
        edt_TileType = 13;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+216)) && (edt_MouseY <= (C_POS.PosDy+216)))
    {
        edt_TileType = 14;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+252)) && (edt_MouseY <= (C_POS.PosDy+252)))
    {
        edt_TileType = 15;
    }
    /// Corrdinates of third toolbox column
    C_POS.PosUx = g_ScreenW-44;
    C_POS.PosUy = 76;
    C_POS.PosDx = C_POS.PosUx+g_TileW;
    C_POS.PosDy = C_POS.PosUy+g_TileH;
    /// Check coordinates of mouse click
    if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= C_POS.PosUy) && (edt_MouseY <= C_POS.PosDy))
    {
        edt_TileType = 16;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+36)) && (edt_MouseY <= (C_POS.PosDy+36)))
    {
        edt_TileType = 17;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+72)) && (edt_MouseY <= (C_POS.PosDy+72)))
    {
        edt_TileType = 18;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+108)) && (edt_MouseY <= (C_POS.PosDy+108)))
    {
        edt_TileType = 19;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+144)) && (edt_MouseY <= (C_POS.PosDy+144)))
    {
        edt_TileType = 20;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+180)) && (edt_MouseY <= (C_POS.PosDy+180)))
    {
        edt_TileType = 21;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+216)) && (edt_MouseY <= (C_POS.PosDy+216)))
    {
        edt_TileType = 22;
    }
    else if ((edt_MouseX >= C_POS.PosUx) && (edt_MouseX <= C_POS.PosDx) && (edt_MouseY >= (C_POS.PosUy+252)) && (edt_MouseY <= (C_POS.PosDy+252)))
    {
        edt_TileType = 23;
    }
    edt_TilePlayer    = edt_TileType;
}

void cEditor::KeyDownLoadFile(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    switch (sym)
    {
        case SDLK_ESCAPE:
        {
            MAP_EDIT_STATE.editState = MAP_EDIT_RENDER;
            break;
        }
        case SDLK_RETURN:
        {
            if (edt_FileName.length() > 8)
            {
                if (!FindString(edt_FileName, ".xsb"))
                {
                    edt_FileName.append(".xsb");
                }
                if (!FileExists(edt_FileName.c_str()))
                {
                    edt_Font.DrawTextString("ERROR: file not found ..", g_ScreenH-edt_Font.GetFontHeight(), true, edt_SrfDisplay);
                }
                else
                {
                    LoadMap(edt_FileName, MAP_FILE_XSB);
                    MAP_EDIT_STATE.editState = MAP_EDIT_RENDER;
                }
            }
            break;
        }
        case SDLK_BACKSPACE:
        {
            if (edt_FileName.length() > 7)
            {
                edt_FileName.erase(edt_FileName.size()-1);
            }
            break;
        }
        default:
        {
            if (edt_FileName.length() <= 30)
            {
                if (unicode == (Uint16)' ')
                {
                    edt_FileName += (char)unicode;
                }
                else if ((unicode >= (Uint16)'!') && (unicode <= (Uint16)'@'))
                {
                    edt_FileName += (char)unicode;
                }
                else if ((unicode >= (Uint16)'A') && (unicode <= (Uint16)'Z'))
                {
                    edt_FileName += (char)unicode;
                }
                else if ((unicode >= (Uint16)'a') && (unicode <= (Uint16)'z'))
                {
                    edt_FileName += (char)unicode;
                }
            }
            break;
        }
    }
}

void cEditor::KeyDownOverwrite(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    if ((unicode == (Uint16)'Y') || (unicode == (Uint16)'y'))
    {
        if (!SaveMapFile(edt_FileName.c_str()))
        {
            edt_Font.DrawTextString("ERROR: Unable to save file ..", g_ScreenH-edt_Font.GetFontHeight(), true, edt_SrfDisplay);
        }
        edt_FileName.clear();
        edt_FileName.append(g_XsbPath);
        edt_FileName.append("untitled.xsb");
        MAP_EDIT_STATE.editState = MAP_EDIT_RENDER;
    }
    else if ((unicode == (Uint16)'N') || (unicode == (Uint16)'n'))
    {
        edt_Font.DrawTextString("WARNING: file not saved ..", g_ScreenH-edt_Font.GetFontHeight(), true, edt_SrfDisplay);
        MAP_EDIT_STATE.editState = MAP_EDIT_RENDER;
    }
}

void cEditor::PaintAreaMap(int TileID, int TileType)
{
    edt_TileList.clear();
    
    for (int Y=0; Y<edt_NumLin; Y++)
    {
        for (int X=0; X<edt_NumCol; X++)
        {
            cTile tempTile;
            tempTile.m_Lin  = Y;
            tempTile.m_Col  = X;
            tempTile.m_ID   = TileID;
            tempTile.m_Type = TileType;
            tempTile.m_Home = 0;
            edt_TileList.push_back(tempTile);
        }
    }
}

void cEditor::SetEditorRunnig(bool bStatus)
{
    edt_Running = bStatus;
}

bool cEditor::GetEditorRunnig()
{
    return edt_Running;
}

void cEditor::SetEditorExit(bool bExit)
{
    edt_Exit = bExit;
}

bool cEditor::GetEditorExit()
{
    return edt_Exit;
}

void cEditor::SetMapXY(int X, int Y)
{
    edt_PosX = X*edt_RctTileset.w;
    edt_PosY = Y*edt_RctTileset.h;
}

void cEditor::SetTileWH(int Width, int Height)
{
    edt_RctTileset.w = Width;
    edt_RctTileset.h = Height;
}

void cEditor::SetPlayerXY(int X, int Y)
{
    edt_PlayerX = X;
    edt_PlayerY = Y;
}

void cEditor::SetMapLC(int Lines, int Columns)
{
    edt_NumLin = Lines;
    edt_NumCol = Columns;
}

void cEditor::SetTileType(int X, int Y, int Type, int Value)
{
    int edt_TempID;
    
    if (Y > 0)
    {
        edt_TempID = (Y*edt_NumCol) + X;
    }
    else
    {
        edt_TempID = X;
    }
    switch (Type)
    {
        case 1:         //Lin
        {
            edt_TileList[edt_TempID].m_Lin = Value;
            break;
        }
        case 2:         //Col
        {
            edt_TileList[edt_TempID].m_Col = Value;
            break;
        }
        case 3:         //ID
        {
            edt_TileList[edt_TempID].m_ID = Value;
            break;
        }
        case 4:         //TypeID
        {
            edt_TileList[edt_TempID].m_Type = Value;
            break;
        }
        case 5:         //m_HomeBlock
        {
            edt_TileList[edt_TempID].m_Home = Value;
            break;
        }
    }
}

int cEditor::GetTileType(int X, int Y, int Type)
{
    int edt_TempID;
    
    if (Y > 0)
    {
        edt_TempID = (Y*edt_NumCol) + X;
    }
    else
    {
        edt_TempID = X;
    }
    switch (Type)
    {
        case 1:         //Lin
        {
            return edt_TileList[edt_TempID].m_Lin;
            break;
        }
        case 2:         //Col
        {
            return edt_TileList[edt_TempID].m_Col;
            break;
        }
        case 3:         //ID
        {
            return edt_TileList[edt_TempID].m_ID;
            break;
        }
        case 4:         //TypeID
        {
            return edt_TileList[edt_TempID].m_Type;
            break;
        }
        case 5:         //m_HomeBlock
        {
            return edt_TileList[edt_TempID].m_Home;
            break;
        }
    }
}

void cEditor::DrawFrameHUD()
{
    std::string tmpStringInfo;
    
    /// Header Information
    tmpStringInfo.append(g_LangStrings.ReadLabel(28));
    tmpStringInfo.append("     ");
    tmpStringInfo.append(g_LangStrings.ReadLabel(29));
    tmpStringInfo.append("  ");
    tmpStringInfo.append(g_LangStrings.ReadLabel(30));
    tmpStringInfo.append("  ");
    tmpStringInfo.append(g_LangStrings.ReadLabel(31));
    edt_Font.DrawTextString(tmpStringInfo, 28, 8, edt_SrfDisplay);
    /// Line, column and map name information
    tmpStringInfo.clear();
    tmpStringInfo.append("Lin: ");
    tmpStringInfo.append(IntToString(edt_PlayerY+1));
    tmpStringInfo.append(" Col: ");
    tmpStringInfo.append(IntToString(edt_PlayerX+1));
    tmpStringInfo.append(" Map: ");
    tmpStringInfo.append(edt_FileName);
    tmpStringInfo.append("  ");
    tmpStringInfo.append(g_LangStrings.ReadLabel(32));
    tmpStringInfo.append("  ");
    tmpStringInfo.append(g_LangStrings.ReadLabel(33));
    edt_Font.DrawTextString(tmpStringInfo, 32, g_ScreenH-edt_Font.GetFontHeight()-2, edt_SrfDisplay);
    /// Mouse Position Information
    tmpStringInfo.clear();
    tmpStringInfo.append("X: ");
    tmpStringInfo.append(IntToString(edt_MouseX));
    edt_Font.DrawTextString(tmpStringInfo, g_ScreenW-116, g_ScreenH-220, edt_SrfDisplay);
    tmpStringInfo.clear();
    tmpStringInfo.append("Y: ");
    tmpStringInfo.append(IntToString(edt_MouseY));
    edt_Font.DrawTextString(tmpStringInfo, g_ScreenW-116, g_ScreenH-200, edt_SrfDisplay);
    /// Draw Tool Surface Box
    cSurface::Transparent(edt_SrfToolBox, 255, 255, 255);
    cSurface::OnDraw(edt_SrfDisplay, edt_SrfToolBox, g_ScreenW-120, 28, 0, 0, 112, 336);
    cSurface::OnDraw(edt_SrfDisplay, edt_SrfToolBox, g_ScreenW-120, g_ScreenH-168, 0, 340, 112, 148);
    /// Draw Toolbox Buttons
    cSurface::OnDraw(edt_SrfDisplay, edt_SrfTileSet, g_ScreenW-116, 32, g_TileW*TILE_FLOOR,  0, g_TileW, g_TileH);
    cSurface::OnDraw(edt_SrfDisplay, edt_SrfTileSet, g_ScreenW-80,  32, g_TileW*TILE_GOAL,   0, g_TileW, g_TileH);
    cSurface::OnDraw(edt_SrfDisplay, edt_SrfTileSet, g_ScreenW-44,  32, g_TileW*TILE_PLAYER, 0, g_TileW, g_TileH);
    for (int tmpTileId=0; tmpTileId<8; tmpTileId++)
    {
        cSurface::OnDraw(edt_SrfDisplay, edt_SrfTileSet, g_ScreenW-116, 76+(tmpTileId*g_TileH)+(tmpTileId*4), g_TileW*tmpTileId, 0, g_TileW, g_TileH);
        cSurface::OnDraw(edt_SrfDisplay, edt_SrfTileSet, g_ScreenW-80, 76+(tmpTileId*g_TileH)+(tmpTileId*4), g_TileW*(tmpTileId+8), 0, g_TileW, g_TileH);
        cSurface::OnDraw(edt_SrfDisplay, edt_SrfTileSet, g_ScreenW-44, 76+(tmpTileId*g_TileH)+(tmpTileId*4), g_TileW*(tmpTileId+16), 0, g_TileW, g_TileH);
    }
    /// Draw Frame Game Area
    for (int x=0; x<(((edt_NumCol*g_TileW)+8)/4); x++)
    {
        cSurface::OnDraw(edt_SrfDisplay, edt_SrfHUD, 28+(4*x), 28, 0, 0, 4, 4);
        cSurface::OnDraw(edt_SrfDisplay, edt_SrfHUD, 28+(4*x), (edt_NumLin*g_TileH)+g_TileH, 0, 0, 4, 4);
    }
    for (int y=0; y<(((edt_NumLin*g_TileH)+4)/4); y++)
    {
        cSurface::OnDraw(edt_SrfDisplay, edt_SrfHUD, 28, 32+(4*y), 0, 0, 4, 4);
        cSurface::OnDraw(edt_SrfDisplay, edt_SrfHUD, (edt_NumCol*g_TileW)+g_TileW, 32+(4*y), 0, 0, 4, 4);
    }
}

bool cEditor::CheckMapFile()
{
    int  mGoal   = 0;
    int  mBox    = 0;
    int  mPlayer = 0;
    bool mReturn = false;
    
    
    for (int Y=0; Y<edt_TileList.size(); Y++)
    {
        if (edt_TileList[Y].m_Type == TILE_PLAYER)
        {
            mPlayer++;
        }
        else if (edt_TileList[Y].m_Type == TILE_GOAL)
        {
            mGoal++;
        }
        else if (edt_TileList[Y].m_Type == TILE_BOX)
        {
            mBox++;
        }
        else if (edt_TileList[Y].m_Type == TILE_PLAYER_ON_GOAL)
        {
            mGoal++;
        }
        else if (edt_TileList[Y].m_Type == TILE_BOX_ON_GOAL)
        {
            mGoal++;
            mBox++;
        }
    }
    if (mPlayer == 1)
    {
        mReturn = true;
    }
    else
    {
        mReturn = false;
    }
    if (mGoal == mBox)
    {
        mReturn = true;
    }
    else
    {
        mReturn = false;
    }
    
    return mReturn;
}

bool cEditor::LoadMap(std::string File, int Type)
{
    /// Temporary converter file
    string tmpmapfile;
    /// Path and name of temp file
    tmpmapfile.append(g_XsbPath);
    tmpmapfile.append("tempmap.tmp");
    /// Clear vector of tiles
    edt_TileList.clear();
    
    switch (Type)
    {
        case MAP_FILE_MAP:
        {
            /// Stores a new file name
            edt_FileName = File;
            FILE* FileHandleTiles = fopen(File.c_str(), "r");
            if (FileHandleTiles == NULL)
            {
                return false;
            }
            for (int Y=0; Y<edt_NumLin; Y++)
            {
                for (int X=0; X<edt_NumCol; X++)
                {
                    cTile tempTile;
                    fscanf(FileHandleTiles, "%d:%d", &tempTile.m_ID, &tempTile.m_Type);
                    tempTile.m_Lin = Y;
                    tempTile.m_Col = X;
                    if ((tempTile.m_ID == TILE_ID_DRAW) && (tempTile.m_Type == TILE_PLAYER))
                    {
                        edt_PlayerX = X;
                        edt_PlayerY = Y;
                        tempTile.m_Type = TILE_FLOOR;
                    }
                    if ((tempTile.m_ID == TILE_ID_DRAW) && (tempTile.m_Type == TILE_GOAL))
                    {
                        tempTile.m_Home = 1;
                        edt_TotalBlocksOnGoal++;
                    }
                    else if ((tempTile.m_ID == TILE_ID_DRAW) && (tempTile.m_Type == TILE_BOX_ON_GOAL))
                    {
                        tempTile.m_Home = 1;
                        edt_TotalBlocksOnGoal++;
                    }
                    else
                    {
                        tempTile.m_Home = 0;
                    }
                    edt_TileList.push_back(tempTile);
                }
                fscanf(FileHandleTiles, "\n");
            }
            fclose(FileHandleTiles);
            break;
        }
        case MAP_FILE_XSB:
        {
            /// Stores a new file name
            edt_FileName = File;
            ConvertXSBToMap(File, edt_NumCol);
            FILE* FileHandleTiles = fopen(tmpmapfile.c_str(), "r");
            if (FileHandleTiles == NULL)
            {
                return false;
            }
            for (int Y=0; Y<edt_NumLin; Y++)
            {
                for (int X=0; X<edt_NumCol; X++)
                {
                    cTile tempTile;
                    fscanf(FileHandleTiles, "%d:%d", &tempTile.m_ID, &tempTile.m_Type);
                    tempTile.m_Lin = Y;
                    tempTile.m_Col = X;
                    if ((tempTile.m_ID == TILE_ID_DRAW) && (tempTile.m_Type == TILE_PLAYER))
                    {
                        edt_PlayerX = X;
                        edt_PlayerY = Y;
                        tempTile.m_Type = TILE_FLOOR;
                    }
                    else if ((tempTile.m_ID == TILE_ID_DRAW) && (tempTile.m_Type == TILE_PLAYER_ON_GOAL))
                    {
                        edt_PlayerX = X;
                        edt_PlayerY = Y;
                        tempTile.m_Type = TILE_GOAL;
                    }
                    if ((tempTile.m_ID == TILE_ID_DRAW) && (tempTile.m_Type == TILE_GOAL))
                    {
                        tempTile.m_Home = 1;
                        edt_TotalBlocksOnGoal++;
                    }
                    else if ((tempTile.m_ID == TILE_ID_DRAW) && (tempTile.m_Type == TILE_BOX_ON_GOAL))
                    {
                        tempTile.m_Home = 1;
                        edt_TotalBlocksOnGoal++;
                    }
                    else
                    {
                        tempTile.m_Home = 0;
                    }
                    edt_TileList.push_back(tempTile);
                }
                fscanf(FileHandleTiles, "\n");
            }
            fclose(FileHandleTiles);
            break;
        }
    }
    if (FileExists(tmpmapfile))
    {
        if (std::remove(tmpmapfile.c_str()) == -1)
        {
            fprintf(stdout, "WARNING: unable to delete temporary map file ..");
        }
    }
    
    return true;
}

bool cEditor::SaveMapFile(std::string File)
{
    //std::string tmpCharString;
    FILE * pFile;
    
    pFile = fopen(File.c_str(), "w");
    if (pFile == NULL)
    {
        return false;
    }
    int k=0;
    for (int l=0; l<edt_NumLin; l++)
    {
        for (int c=0; c<edt_NumCol; c++)
        {
            if (edt_TileList[k].m_ID == TILE_ID_DRAW)
            {
                fprintf(pFile, "%s", ConvertMapToXSB(edt_TileList[k].m_ID, edt_TileList[k].m_Type).c_str());
            }
            k++;
        }
        if (edt_TileList[k].m_ID == TILE_ID_DRAW)
        {
            fprintf(pFile, "\n");
        }
    }
    /// Printing level information
    fprintf(pFile, "\nTitle: %s\n", g_Title.c_str());
    fprintf(pFile, "Author: %s\n", g_Author.c_str());
    fprintf(pFile, "Collection: %s\n", g_Collection.c_str());
    fprintf(pFile, "AuthorMail: %s\n", g_AuthorMail.c_str());
    fprintf(pFile, "AuthorPage: %s\n", g_AuthorPage.c_str());
    fprintf(pFile, "Level: %s\n", g_Level.c_str());
    fprintf(pFile, "Date: %s", GetSystemDate().c_str());
    fprintf(pFile, "Comment: %s", g_Comment.c_str());
    fclose(pFile);
    
    return true;
}