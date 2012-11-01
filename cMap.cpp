/*
 * SDL SOKOBAN - The Sokoban Game Clone write in C++/SDL
 * Copyright (C) 2012 Ericson Norberto <sdlsokoban@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 * 
 * ============= XSB File Format | Cell Characters: ============= 
 *  
 *     ' ' (white space) - Floor
 *     @ - Player
 *     + - Player on target
 *     # - Wall
 *     $ - Box
 *     . - Target
 *     * - Box on target
 *  
 *  =============================================================
*/
#include "cMap.h"
#include "cGlobals.h"

cMap::cMap()
{
    map_PosX              = 0;
    map_PosY              = 0;
    map_NumLin            = 15;
    map_NumCol            = 20;
    map_RctTileset.x      = 0;
    map_RctTileset.y      = 0;
    map_RctTileset.w      = 32;
    map_RctTileset.h      = 32;
    map_RctBackground.x   = 0;
    map_RctBackground.y   = 0;
    map_RctBackground.w   = 0;
    map_RctBackground.h   = 0;
    map_RctMessageBox.x   = 0;
    map_RctMessageBox.y   = 0;
    map_RctMessageBox.w   = 0;
    map_RctMessageBox.h   = 0;
    map_PlayerX           = 0;
    map_PlayerY           = 0;
    map_TimeH             = 0;
    map_TimeM             = 0;
    map_TimeS             = 0;
    map_Win               = false;
    map_ShowMsgBox        = false;
    map_Running           = false;
    map_Exit              = false;
    map_TotalMoves        = 0;
    map_TotalPushes       = 0;
    map_TotalBlocksOnGoal = 0;
    map_TypeOfMap         = MAP_FILE_MAP;
    map_Title             = "";
    map_Author            = "";
    map_Date              = "";
    map_Level             = "";
    map_Difficulty        = "";
    map_Contact           = "";
    map_Comment           = "";
    map_SrfTileSet        = NULL;
    map_SrfBackground     = NULL;
    map_SrfMessageBox     = NULL;
    map_SrfDisplay        = NULL;
    map_SrfHUD            = NULL;
    map_SrfHelpScreen     = NULL;
}

cMap::~cMap()
{
}

bool cMap::OnInitMap(std::string Map)
{
    /// Resetting main variables
    map_PlayerX            = 0;
    map_PlayerY            = 0;
    map_TimeH              = 0;
    map_TimeM              = 0;
    map_TimeS              = 0;
    map_TotalMoves         = 0;
    map_TotalPushes        = 0;
    map_TotalBlocksOnGoal  = 0;
    map_Title              = GetMapInfo(Map, "Title");
    map_Author             = GetMapInfo(Map, "Author");
    map_Date               = GetMapInfo(Map, "Date");
    map_Level              = GetMapInfo(Map, "Level");
    map_Difficulty         = GetMapInfo(Map, "Difficulty");
    map_Contact            = GetMapInfo(Map, "Contact");
    map_Comment            = GetMapInfo(Map, "Comment");
    map_TypeOfMap          = GetMapType(Map);
    map_MapName            = Map;
    map_RctTileset.w       = g_TileW;
    map_RctTileset.h       = g_TileH;
    map_RctBackground.w    = g_ScreenW;
    map_RctBackground.h    = g_ScreenH;
    map_RctMessageBox.w    = 378;
    map_RctMessageBox.h    = 266;
    map_RctMessageBox.x    = (g_ScreenW-map_RctMessageBox.w)/2;
    map_RctMessageBox.y    = (g_ScreenH-map_RctMessageBox.h)/2;
    /// Black Area Dimensions
    map_RctBlackArea.x     = 0;
    map_RctBlackArea.y     = 0;
    map_RctBlackArea.w     = 0;
    map_RctBlackArea.h     = 0;
    /// Name of font surfaces
    /// Total Files information
    map_TotalFiles         = map_ListFiles.size();
    /// Initial Map State
    MAP_STATE.mapState     = MAP_RUN;
    /// Initializes Random number generator
    srand((unsigned)time(0));
    /// Path and name of surface files
    std::string map_SurfaceFiles[3] = {"./gfx/msgbox01_378.png", "./gfx/surface02_248.png", "./gfx/shelp01_500.png"};
    /// Load background surface
    if ((map_SrfBackground = cSurface::OnLoadResolution("./gfx/", "bkg_", g_ScreenW, g_ScreenH)) == NULL)
    {
        fprintf(stdout, "ERROR: unable to load surface ..");
        return false;
    }
    /// Load map Tileset surface
    if ((map_SrfTileSet = cSurface::OnLoad(g_TileSurface)) == NULL)
    {
        fprintf(stdout, "ERROR: unable to load surface %s ..", g_TileSurface.c_str());
        return false;
    }
    /// Load Message box surface
    if ((map_SrfMessageBox = cSurface::OnLoad(map_SurfaceFiles[0])) == NULL)
    {
        fprintf(stdout, "ERROR: unable to load surface %s ..", map_SurfaceFiles[0].c_str());
        return false;
    }
    /// Load HUD surfaces
    if ((map_SrfHUD = cSurface::OnLoad(map_SurfaceFiles[1].c_str())) == NULL)
    {
        fprintf(stdout, "ERROR: unable to load surface %s ..", map_SurfaceFiles[1].c_str());
        return false;
    }
    /// Load Help Screen Surface
    if ((map_SrfHelpScreen = cSurface::OnLoad(map_SurfaceFiles[2].c_str())) == NULL)
    {
        fprintf(stdout, "ERROR: unable to load surface %s ..", map_SurfaceFiles[2].c_str());
        return false;
    }
    /// Initializes all fonts
    std::string map_NameFonts[5] = {"./fonts/font3_12x12.png", "./fonts/font5_16x16.png", "./fonts/font6_08x08.png", "./fonts/font7_08x16.png", "./fonts/font9_8x17.png"};
    for (int TotalFonts = 0; TotalFonts<5; TotalFonts++)
    {
        cFont m_tmpFont;
        if (!m_tmpFont.OnLoadDefaults(map_NameFonts[TotalFonts].c_str()))
        {
            return false;
        }
        map_FontList.push_back(m_tmpFont);
    }
    /// Font menu out focus
    map_FontList[FONT_FAST].SetFontParameters(33, 131, 12, 12, FONT_VERTICAL);
    /// Setting RGB pattern
    map_FontList[FONT_FAST].SetRGB(0, 0, 0);
    /// Font menu on focus
    map_FontList[FONT_KROMASKY].SetFontParameters(33, 131, 16, 16, FONT_HORIZONTAL);
    /// Setting RGB pattern
    map_FontList[FONT_KROMASKY].SetRGB(255, 0, 255);
    /// Font menu tooltip
    map_FontList[FONT_BRINGER].SetFontParameters(33, 131, 8, 8, FONT_HORIZONTAL);
    /// Setting RGB pattern
    map_FontList[FONT_BRINGER].SetRGB(255, 0, 255);
    /// Font menu system 1 (full ascii)
    map_FontList[FONT_GEEBEE].SetFontParameters(33, 90, 8, 16, FONT_HORIZONTAL);
    /// Setting RGB pattern
    map_FontList[FONT_GEEBEE].SetRGB(255, 0, 255);
    /// Font menu system 2
    map_FontList[FONT_BLAZING].SetFontParameters(33, 90, 8, 17, FONT_HORIZONTAL);
    /// Setting RGB pattern
    map_FontList[FONT_BLAZING].SetRGB(255, 0, 255);
    /// Load MAP file and creates vector tiles
    if (!LoadMap(Map, map_TypeOfMap))
    {
        fprintf(stdout, "ERROR: unable to load surface %s ..", Map.c_str());
        return false;
    }
    /// Verify map dimensions
    if (!CheckMapDimensions())
    {
        MAP_STATE.mapState = MAP_DIMENSIONS;
    }
    /// Clear undo list
    ClearAllSavedPositions();
    /// Stats game time
    map_Time.Start();
    /// Setting map screen position
    SetMapXY(1, 1);
    /// Reset map exit status
    SetMapExit(false);
    /// Setting map running status
    SetMapRunnig(true);
    
    return true;
}

void cMap::OnRenderMap(SDL_Surface* Display)
{
    map_SrfDisplay = Display;
    
    switch (MAP_STATE.mapState)
    {
        case MAP_RUN:
        {
            if (map_SrfTileSet == NULL)
            {
                return;
            }
            int _sX = map_PosX;
            int _sY = map_PosY;
            int _sW = 0;
            cSurface::OnDraw(map_SrfDisplay, map_SrfBackground, 0, 0, map_RctBackground.x, map_RctBackground.y, map_RctBackground.w, map_RctBackground.h);
            /// Draw Black Game Area
            map_RctBlackArea.x = 32;
            map_RctBlackArea.y = 32;
            map_RctBlackArea.w = g_ScreenW-158;
            map_RctBlackArea.h = g_ScreenH-54;
            SDL_FillRect(Display, &map_RctBlackArea, SDL_MapRGB(Display->format, 0, 0, 0));
            /// Game time area
            map_RctBlackArea.x = g_ScreenW-120;
            map_RctBlackArea.y = 64;
            map_RctBlackArea.w = 112;
            map_RctBlackArea.h = 40;
            SDL_FillRect(Display, &map_RctBlackArea, SDL_MapRGB(Display->format, 0, 0, 0));
            /// Game level area
            map_RctBlackArea.x = g_ScreenW-120;
            map_RctBlackArea.y = g_ScreenH-132;
            map_RctBlackArea.w = 112;
            map_RctBlackArea.h = 112;
            SDL_FillRect(Display, &map_RctBlackArea, SDL_MapRGB(Display->format, 0, 0, 0));
            /// Draw map area surface
            for (int _pZ=0; _pZ<map_TileList.size(); _pZ++)
            {
                if (map_TileList[_pZ].m_ID == 0)
                {
                    continue;
                }
                _sW = (map_TileList[_pZ].m_Type)*map_RctTileset.w;
                _sX = map_PosX + (map_TileList[_pZ].m_Col*map_RctTileset.w);
                _sY = map_PosY + (map_TileList[_pZ].m_Lin*map_RctTileset.h);

                cSurface::Transparent(map_SrfTileSet, 255, 0, 255);
                cSurface::OnDraw(map_SrfDisplay, map_SrfTileSet, _sX, _sY, _sW, 0, map_RctTileset.w, map_RctTileset.h);
            }
            /// Gets first Player position
            if (GetTileType(map_PlayerX, map_PlayerY, 4) == TILE_GOAL)
            {
                cSurface::OnDraw(map_SrfDisplay, map_SrfTileSet, (map_PlayerX+(map_PosX/map_RctTileset.w))*map_RctTileset.w, (map_PlayerY+(map_PosY/map_RctTileset.h))*map_RctTileset.h, TILE_PLAYER_ON_GOAL*map_RctTileset.w, 0, map_RctTileset.w, map_RctTileset.h);
            }
            else
            {
                cSurface::OnDraw(map_SrfDisplay, map_SrfTileSet, (map_PlayerX+(map_PosX/map_RctTileset.w))*map_RctTileset.w, (map_PlayerY+(map_PosY/map_RctTileset.h))*map_RctTileset.h, TILE_PLAYER*map_RctTileset.w, 0, map_RctTileset.w, map_RctTileset.h);
            }
            /// Draw Game HUD Area
            DrawGameHUD(Display);
            /// Draw game statistics (game time, total moves, etc)
            DrawStatistics();
            /// Check if puzzle is solved (player win)
            if (map_Win)
            {
                MAP_STATE.mapState = MAP_WIN;
                //map_ShowMsgBox = true;
            }
            break;
        }
        case MAP_HELP:
        {
            int hlpX = (g_ScreenW-500)/2;
            int hlpY = (g_ScreenH-250)/2;
            /// In game help screen
            cSurface::OnDraw(map_SrfDisplay, map_SrfHelpScreen, hlpX, hlpY, 0, 0, 500, 250);
            /// Text help
            map_FontList[FONT_FAST].DrawTextString(g_LangStrings.ReadLabel(40), hlpY+10,  true, map_SrfDisplay);
            map_FontList[FONT_FAST].DrawTextString(g_LangStrings.ReadLabel(34), hlpY+70,  true, map_SrfDisplay);
            map_FontList[FONT_FAST].DrawTextString(g_LangStrings.ReadLabel(35), hlpY+100, true, map_SrfDisplay);
            map_FontList[FONT_FAST].DrawTextString(g_LangStrings.ReadLabel(36), hlpY+130, true, map_SrfDisplay);
            map_FontList[FONT_FAST].DrawTextString(g_LangStrings.ReadLabel(37), hlpY+160, true, map_SrfDisplay);
            map_FontList[FONT_FAST].DrawTextString(g_LangStrings.ReadLabel(38), hlpY+190, true, map_SrfDisplay);
            map_FontList[FONT_FAST].DrawTextString(g_LangStrings.ReadLabel(39), hlpY+220, true, map_SrfDisplay);
//            map_FontList[FONT_FAST].DrawTextString(g_LangStrings.ReadLabel(34), hlpY+70,  true, map_SrfDisplay);
//            map_FontList[FONT_FAST].DrawTextString(g_LangStrings.ReadLabel(35), hlpY+100, true, map_SrfDisplay);
//            map_FontList[FONT_FAST].DrawTextString(g_LangStrings.ReadLabel(36), hlpY+130, true, map_SrfDisplay);
//            map_FontList[FONT_FAST].DrawTextString(g_LangStrings.ReadLabel(37), hlpY+160, true, map_SrfDisplay);
//            map_FontList[FONT_FAST].DrawTextString(g_LangStrings.ReadLabel(38), hlpY+190, true, map_SrfDisplay);
//            map_FontList[FONT_FAST].DrawTextString(g_LangStrings.ReadLabel(39), hlpY+220, true, map_SrfDisplay);
            break;
        }
        case MAP_WIN:
        {
            /// Draw game win message box information
            std::string tmpTotalTime;
            std::string tmpTotalMoves;
            /// Total moves/pushes information
            tmpTotalMoves.append(g_LangStrings.ReadLabel(27));
            tmpTotalMoves.append(" ");
            tmpTotalMoves.append(IntToString(map_TotalMoves));
            tmpTotalMoves.append("/");
            tmpTotalMoves.append(IntToString(map_TotalPushes));
            /// Game total time information
            tmpTotalTime.append(g_LangStrings.ReadLabel(12));
            tmpTotalTime.append(" ");
            tmpTotalTime.append(FormatTime(map_TimeH, map_TimeM, map_TimeS));
            /// Draw congratulations Surface
            cSurface::OnDraw(map_SrfDisplay, map_SrfMessageBox, map_RctMessageBox.x, map_RctMessageBox.y, 0, 0, map_RctMessageBox.w, map_RctMessageBox.h);
            /// Display text information
            map_FontList[FONT_FAST].DrawTextString(g_LangStrings.ReadLabel(15), map_RctMessageBox.y+23, true, map_SrfDisplay);
            map_FontList[FONT_FAST].DrawTextString(tmpTotalMoves, map_RctMessageBox.y+90, true, map_SrfDisplay);
            map_FontList[FONT_FAST].DrawTextString(tmpTotalTime, map_RctMessageBox.y+120, true, map_SrfDisplay);
            map_FontList[FONT_FAST].DrawTextString(g_LangStrings.ReadLabel(16), map_RctMessageBox.y+180, true, map_SrfDisplay);
            map_FontList[FONT_FAST].DrawTextString(g_LangStrings.ReadLabel(17), map_RctMessageBox.y+200, true, map_SrfDisplay);
            map_FontList[FONT_FAST].DrawTextString(g_LangStrings.ReadLabel(18), map_RctMessageBox.y+220, true, map_SrfDisplay);
            break;
        }
        case MAP_DIMENSIONS:
        {
            /// Draw congratulations Surface
            cSurface::OnDraw(map_SrfDisplay, map_SrfMessageBox, map_RctMessageBox.x, map_RctMessageBox.y, 0, 0, map_RctMessageBox.w, map_RctMessageBox.h);
            /// Display text information
            map_FontList[FONT_FAST].DrawTextString("WARNING", map_RctMessageBox.y+23, true, map_SrfDisplay);
            map_FontList[FONT_FAST].DrawTextString("", map_RctMessageBox.y+90, true, map_SrfDisplay);
            map_FontList[FONT_FAST].DrawTextString("", map_RctMessageBox.y+120, true, map_SrfDisplay);
            map_FontList[FONT_FAST].DrawTextString("", map_RctMessageBox.y+180, true, map_SrfDisplay);
            map_FontList[FONT_FAST].DrawTextString("", map_RctMessageBox.y+200, true, map_SrfDisplay);
            map_FontList[FONT_FAST].DrawTextString("", map_RctMessageBox.y+220, true, map_SrfDisplay);
            break;
        }
    }
}

void cMap::OnEventMap(SDL_Event* Event)
{
    switch (Event->type)
    {
        case SDL_KEYDOWN:
        {
            switch (Event->key.keysym.sym)
            {
                case SDLK_UP:
                {
                    if (MAP_STATE.mapState == MAP_RUN)
                    {
                        MoveBlockUP();
                    }
                    break;
                }
                case SDLK_DOWN:
                {
                    if (MAP_STATE.mapState == MAP_RUN)
                    {
                        MoveBlockDOWN();
                    }
                    break;
                }
                case SDLK_LEFT:
                {
                    if (MAP_STATE.mapState == MAP_RUN)
                    {
                        MoveBlockLEFT();
                    }
                    break;
                }
                case SDLK_RIGHT:
                {
                    if (MAP_STATE.mapState == MAP_RUN)
                    {
                        MoveBlockRIGHT();
                    }
                    break;
                }
                case SDLK_F1:
                {
                    if (MAP_STATE.mapState == MAP_RUN)
                    {
                        MAP_STATE.mapState = MAP_HELP;
                    }
                    break;
                }
                case SDLK_F5:
                {
                    if ((MAP_STATE.mapState == MAP_RUN) || (MAP_STATE.mapState == MAP_WIN))
                    {
                        map_PlayerX           = 0;
                        map_PlayerY           = 0;
                        map_TotalBlocksOnGoal = 0;
                        map_TotalMoves        = 0;
                        map_TotalPushes       = 0;
                        map_TimeH             = 0;
                        map_TimeM             = 0;
                        map_TimeS             = 0;
                        map_Win               = false;
                        map_Running           = true;
                        map_Exit              = false;
                        map_ShowMsgBox        = false;
                        ClearAllSavedPositions();
                        LoadMap(map_MapName, map_TypeOfMap);
                        map_Time.Reset();
                    }
                    break;
                }
                case SDLK_F8:
                {
                    if (MAP_STATE.mapState == MAP_RUN)
                    {
                        SaveScreenShot();
                    }
                    break;
                }
                case SDLK_F9:
                {
                    if (MAP_STATE.mapState == MAP_RUN)
                    {
                        /// Clear main map variables
                        map_PlayerX           = 0;
                        map_PlayerY           = 0;
                        map_TotalBlocksOnGoal = 0;
                        map_TotalMoves        = 0;
                        map_TotalPushes       = 0;
                        map_TimeH             = 0;
                        map_TimeM             = 0;
                        map_TimeS             = 0;
                        map_Win               = false;
                        map_Running           = true;
                        map_Exit              = false;
                        map_ShowMsgBox        = false;
                        /// Generates new map
                        map_MapName.clear();
                        map_MapName.append(g_XsbPath);
                        map_MapName.append(GetRandomMapName());
                        /// Clear saved positions
                        ClearAllSavedPositions();
                        /// Load new map
                        LoadMap(map_MapName, map_TypeOfMap);
                        /// Reset game time counter
                        map_Time.Reset();
                    }
                    break;
                }
                case SDLK_F12:
                {
                    if (MAP_STATE.mapState == MAP_RUN)
                    {
                        RestoreLastPlayerPosition();
                    }
                    break;
                }
                case SDLK_RETURN:
                {
                    if (MAP_STATE.mapState == MAP_WIN)
                    {
                        /// Clear main map variables
                        map_PlayerX           = 0;
                        map_PlayerY           = 0;
                        map_TotalBlocksOnGoal = 0;
                        map_TotalMoves        = 0;
                        map_TotalPushes       = 0;
                        map_TimeH             = 0;
                        map_TimeM             = 0;
                        map_TimeS             = 0;
                        map_Win               = false;
                        map_Running           = true;
                        map_Exit              = false;
                        MAP_STATE.mapState    = MAP_RUN;
                        /// Generates new map
                        map_MapName.clear();
                        map_MapName.append(g_XsbPath);
                        map_MapName.append(GetRandomMapName());
                        /// Clear saved positions
                        ClearAllSavedPositions();
                        /// Load new map
                        LoadMap(map_MapName, map_TypeOfMap);
                        /// Reset game time counter
                        map_Time.Reset();
                    }
                    else if (MAP_STATE.mapState == MAP_DIMENSIONS)
                    {
                        MAP_STATE.mapState = MAP_RUN;
                    }
                    break;
                }
                case SDLK_ESCAPE:
                {
                    switch (MAP_STATE.mapState)
                    {
                        case MAP_RUN:
                        {
                            map_Exit       = true;
                            map_Win        = false;
                            map_Running    = false;
                            map_ShowMsgBox = false;
                            SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
                            break;
                        }
                        case MAP_HELP:
                        {
                            MAP_STATE.mapState = MAP_RUN;
                            break;
                        }
                        case MAP_WIN:
                        {
                            map_Exit       = true;
                            map_Win        = false;
                            map_Running    = false;
                            map_ShowMsgBox = false;
                            SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
                            break;
                        }
                    }
                    break;
                }
            }
            break;
        }
    }
}

void cMap::OnLoopMap()
{
    switch (MAP_STATE.mapState)
    {
        case MAP_RUN:
        {
            if (map_TimeS > 59)
            {
                map_TimeS = 0;
                map_Time.Reset();
                if (map_TimeM > 59)
                {
                    map_TimeM = 0;
                    if (map_TimeH > 23)
                    {
                        map_TimeH = 0;
                    }
                    else
                    {
                        map_TimeH++;
                    }
                }
                else
                {
                    map_TimeM++;
                }
            }
            else
            {
                map_TimeS = (map_Time.GetTicks()/1000);
            }
            break;
        }
        case MAP_HELP:
        {
            break;
        }
        case MAP_WIN:
        {
            break;
        }
    }
}

bool cMap::LoadMap(std::string File, int Type)
{
    /// Temporary converter file
    string tmpmapfile;
    /// Path and name of temp file
    tmpmapfile.append(g_XsbPath);
    tmpmapfile.append("tempmap.tmp");
    /// Gets Total Lines and Columns of Map
    map_NumLin = GetMapLines(File, Type);
    map_NumCol = GetMapColumns(File, Type);
    /// Clear vector of tiles
    map_TileList.clear();
    
    switch (Type)
    {
        case MAP_FILE_MAP:
        {
            FILE* FileHandleTiles = fopen(File.c_str(), "r");
            if (FileHandleTiles == NULL)
            {
                return false;
            }
            for (int Y=0; Y<map_NumLin; Y++)
            {
                for (int X=0; X<map_NumCol; X++)
                {
                    cTile tempTile;
                    fscanf(FileHandleTiles, "%d:%d", &tempTile.m_ID, &tempTile.m_Type);
                    tempTile.m_Lin = Y;
                    tempTile.m_Col = X;
                    if ((tempTile.m_ID == TILE_ID_DRAW) && (tempTile.m_Type == TILE_PLAYER))
                    {
                        map_PlayerX = X;
                        map_PlayerY = Y;
                        tempTile.m_Type = TILE_FLOOR;
                    }
                    if ((tempTile.m_ID == TILE_ID_DRAW) && (tempTile.m_Type == TILE_GOAL))
                    {
                        tempTile.m_Home = 1;
                        map_TotalBlocksOnGoal++;
                    }
                    else if ((tempTile.m_ID == TILE_ID_DRAW) && (tempTile.m_Type == TILE_BOX_ON_GOAL))
                    {
                        tempTile.m_Home = 1;
                        map_TotalBlocksOnGoal++;
                    }
                    else
                    {
                        tempTile.m_Home = 0;
                    }
                    map_TileList.push_back(tempTile);
                }
                fscanf(FileHandleTiles, "\n");
            }
            fclose(FileHandleTiles);
            break;
        }
        case MAP_FILE_XSB:
        {
            /// Open for read/write
            ConvertXSBToMap(File, map_NumCol);
            FILE* FileHandleTiles = fopen(tmpmapfile.c_str(), "r");
            if (FileHandleTiles == NULL)
            {
                return false;
            }
            for (int Y=0; Y<map_NumLin; Y++)
            {
                for (int X=0; X<map_NumCol; X++)
                {
                    cTile tempTile;
                    fscanf(FileHandleTiles, "%d:%d", &tempTile.m_ID, &tempTile.m_Type);
                    tempTile.m_Lin = Y;
                    tempTile.m_Col = X;
                    if ((tempTile.m_ID == TILE_ID_DRAW) && (tempTile.m_Type == TILE_PLAYER))
                    {
                        map_PlayerX = X;
                        map_PlayerY = Y;
                        tempTile.m_Type = TILE_FLOOR;
                    }
                    else if ((tempTile.m_ID == TILE_ID_DRAW) && (tempTile.m_Type == TILE_PLAYER_ON_GOAL))
                    {
                        map_PlayerX = X;
                        map_PlayerY = Y;
                        tempTile.m_Type = TILE_GOAL;
                    }
                    if ((tempTile.m_ID == TILE_ID_DRAW) && (tempTile.m_Type == TILE_GOAL))
                    {
                        tempTile.m_Home = 1;
                        map_TotalBlocksOnGoal++;
                    }
                    else if ((tempTile.m_ID == TILE_ID_DRAW) && (tempTile.m_Type == TILE_BOX_ON_GOAL))
                    {
                        tempTile.m_Home = 1;
                        map_TotalBlocksOnGoal++;
                    }
                    else
                    {
                        tempTile.m_Home = 0;
                    }
                    map_TileList.push_back(tempTile);
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

void cMap::SetTileType(int X, int Y, int Type, int Value)
{
    int map_TempID;
    
    if (Y > 0)
    {
        map_TempID = (Y*map_NumCol) + X;
    }
    else
    {
        map_TempID = X;
    }
    switch (Type)
    {
        case 1:         //Lin
        {
            map_TileList[map_TempID].m_Lin = Value;
            break;
        }
        case 2:         //Col
        {
            map_TileList[map_TempID].m_Col = Value;
            break;
        }
        case 3:         //ID
        {
            map_TileList[map_TempID].m_ID = Value;
            break;
        }
        case 4:         //Type
        {
            map_TileList[map_TempID].m_Type = Value;
            break;
        }
        case 5:         //m_Home
        {
            map_TileList[map_TempID].m_Home = Value;
            break;
        }
    }
}

int cMap::GetTileType(int X, int Y, int Type)
{
    int map_TempID;
    
    if (Y > 0)
    {
        map_TempID = (Y*map_NumCol) + X;
    }
    else
    {
        map_TempID = X;
    }
    switch (Type)
    {
        case 1:         //Lin
        {
            return map_TileList[map_TempID].m_Lin;
            break;
        }
        case 2:         //Col
        {
            return map_TileList[map_TempID].m_Col;
            break;
        }
        case 3:         //ID
        {
            return map_TileList[map_TempID].m_ID;
            break;
        }
        case 4:         //TypeID
        {
            return map_TileList[map_TempID].m_Type;
            break;
        }
        case 5:         //m_HomeBlock
        {
            return map_TileList[map_TempID].m_Home;
            break;
        }
    }
}

void cMap::MoveBlockUP()
{
    switch (GetTileType(map_PlayerX, map_PlayerY-1, 4))
    {
        case TILE_FLOOR:
        {
            SavePlayerPosition(UNDO_UP);
            map_TotalMoves++;
            map_PlayerY--;
            break;
        }
        case TILE_GOAL:
        {
            SavePlayerPosition(UNDO_UP);
            map_TotalMoves++;
            map_PlayerY--;
            break;
        }
        case TILE_BOX:
        {
            if ((GetTileType(map_PlayerX, map_PlayerY-2, 4) == TILE_FLOOR))
            {
                SavePlayerPosition(UNDO_UP);
                map_TotalMoves++;
                map_TotalPushes++;
                map_PlayerY--;
                SetTileType(map_PlayerX, map_PlayerY-1, 4, TILE_BOX);
                SetTileType(map_PlayerX, map_PlayerY, 4, TILE_FLOOR);
            }
            else if ((GetTileType(map_PlayerX, map_PlayerY-2, 4) == TILE_GOAL))
            {
                SavePlayerPosition(UNDO_UP);
                map_TotalMoves++;
                map_TotalPushes++;
                map_PlayerY--;
                SetTileType(map_PlayerX, map_PlayerY-1, 4, TILE_BOX_ON_GOAL);
                SetTileType(map_PlayerX, map_PlayerY, 4, TILE_FLOOR);
            }
            ValidateGameStatus();
            break;
        }
        case TILE_BOX_ON_GOAL:
        {
            if ((GetTileType(map_PlayerX, map_PlayerY-2, 4) == TILE_FLOOR))
            {
                SavePlayerPosition(UNDO_UP);
                map_TotalMoves++;
                map_TotalPushes++;
                map_PlayerY--;
                SetTileType(map_PlayerX, map_PlayerY-1, 4, TILE_BOX);
                SetTileType(map_PlayerX, map_PlayerY, 4, TILE_GOAL);
            }
            else if ((GetTileType(map_PlayerX, map_PlayerY-2, 4) == TILE_GOAL))
            {
                SavePlayerPosition(UNDO_UP);
                map_TotalMoves++;
                map_TotalPushes++;
                map_PlayerY--;
                SetTileType(map_PlayerX, map_PlayerY-1, 4, TILE_BOX_ON_GOAL);
                SetTileType(map_PlayerX, map_PlayerY, 4, TILE_GOAL);
            }
            ValidateGameStatus();
            break;
        }
    }
}

void cMap::MoveBlockDOWN()
{
    switch (GetTileType(map_PlayerX, map_PlayerY+1, 4))
    {
        case TILE_FLOOR:
        {
            SavePlayerPosition(UNDO_DOWN);
            map_TotalMoves++;
            map_PlayerY++;
            break;
        }
        case TILE_GOAL:
        {
            SavePlayerPosition(UNDO_DOWN);
            map_TotalMoves++;
            map_PlayerY++;
            break;
        }
        case TILE_BOX:
        {
            if ((GetTileType(map_PlayerX, map_PlayerY+2, 4) == TILE_FLOOR))
            {
                SavePlayerPosition(UNDO_DOWN);
                map_TotalMoves++;
                map_TotalPushes++;
                map_PlayerY++;
                SetTileType(map_PlayerX, map_PlayerY+1, 4, TILE_BOX);
                SetTileType(map_PlayerX, map_PlayerY, 4, TILE_FLOOR);
            }
            else if ((GetTileType(map_PlayerX, map_PlayerY+2, 4) == TILE_GOAL))
            {
                SavePlayerPosition(UNDO_DOWN);
                map_TotalMoves++;
                map_TotalPushes++;
                map_PlayerY++;
                SetTileType(map_PlayerX, map_PlayerY+1, 4, TILE_BOX_ON_GOAL);
                SetTileType(map_PlayerX, map_PlayerY, 4, TILE_FLOOR);
            }
            ValidateGameStatus();
            break;
        }
        case TILE_BOX_ON_GOAL:
        {
            if ((GetTileType(map_PlayerX, map_PlayerY+2, 4) == TILE_FLOOR))
            {
                SavePlayerPosition(UNDO_DOWN);
                map_TotalMoves++;
                map_TotalPushes++;
                map_PlayerY++;
                SetTileType(map_PlayerX, map_PlayerY+1, 4, TILE_BOX);
                SetTileType(map_PlayerX, map_PlayerY, 4, TILE_GOAL);
            }
            else if ((GetTileType(map_PlayerX, map_PlayerY+2, 4) == TILE_GOAL))
            {
                SavePlayerPosition(UNDO_DOWN);
                map_TotalMoves++;
                map_TotalPushes++;
                map_PlayerY++;
                SetTileType(map_PlayerX, map_PlayerY+1, 4, TILE_BOX_ON_GOAL);
                SetTileType(map_PlayerX, map_PlayerY, 4, TILE_GOAL);
            }
            ValidateGameStatus();
            break;
        }
    }
}

void cMap::MoveBlockLEFT()
{
    switch (GetTileType(map_PlayerX-1, map_PlayerY, 4))
    {
        case TILE_FLOOR:
        {
            SavePlayerPosition(UNDO_LEFT);
            map_TotalMoves++;
            map_PlayerX--;
            break;
        }
        case TILE_GOAL:
        {
            SavePlayerPosition(UNDO_LEFT);
            map_TotalMoves++;
            map_PlayerX--;
            break;
        }
        case TILE_BOX:
        {
            if ((GetTileType(map_PlayerX-2, map_PlayerY, 4) == TILE_FLOOR))
            {
                SavePlayerPosition(UNDO_LEFT);
                map_TotalMoves++;
                map_TotalPushes++;
                map_PlayerX--;
                SetTileType(map_PlayerX-1, map_PlayerY, 4, TILE_BOX);
                SetTileType(map_PlayerX, map_PlayerY, 4, TILE_FLOOR);
            }
            else if ((GetTileType(map_PlayerX-2, map_PlayerY, 4) == TILE_GOAL))
            {
                SavePlayerPosition(UNDO_LEFT);
                map_TotalMoves++;
                map_TotalPushes++;
                map_PlayerX--;
                SetTileType(map_PlayerX-1, map_PlayerY, 4, TILE_BOX_ON_GOAL);
                SetTileType(map_PlayerX, map_PlayerY, 4, TILE_FLOOR);
            }
            ValidateGameStatus();
            break;
        }
        case TILE_BOX_ON_GOAL:
        {
            if ((GetTileType(map_PlayerX-2, map_PlayerY, 4) == TILE_FLOOR))
            {
                SavePlayerPosition(UNDO_LEFT);
                map_TotalMoves++;
                map_TotalPushes++;
                map_PlayerX--;
                SetTileType(map_PlayerX-1, map_PlayerY, 4, TILE_BOX);
                SetTileType(map_PlayerX, map_PlayerY, 4, TILE_GOAL);
            }
            else if ((GetTileType(map_PlayerX-2, map_PlayerY, 4) == TILE_GOAL))
            {
                SavePlayerPosition(UNDO_LEFT);
                map_TotalMoves++;
                map_TotalPushes++;
                map_PlayerX--;
                SetTileType(map_PlayerX-1, map_PlayerY, 4, TILE_BOX_ON_GOAL);
                SetTileType(map_PlayerX, map_PlayerY, 4, TILE_GOAL);
            }
            ValidateGameStatus();
            break;
        }
    }
}

void cMap::MoveBlockRIGHT()
{
    switch (GetTileType(map_PlayerX+1, map_PlayerY, 4))
    {
        case TILE_FLOOR:
        {
            SavePlayerPosition(UNDO_RIGHT);
            map_TotalMoves++;
            map_PlayerX++;
            break;
        }
        case TILE_GOAL:
        {
            SavePlayerPosition(UNDO_RIGHT);
            map_TotalMoves++;
            map_PlayerX++;
            break;
        }
        case TILE_BOX:
        {
            if ((GetTileType(map_PlayerX+2, map_PlayerY, 4) == TILE_FLOOR))
            {
                SavePlayerPosition(UNDO_RIGHT);
                map_TotalMoves++;
                map_TotalPushes++;
                map_PlayerX++;
                SetTileType(map_PlayerX+1, map_PlayerY, 4, TILE_BOX);
                SetTileType(map_PlayerX, map_PlayerY, 4, TILE_FLOOR);
            }
            else if ((GetTileType(map_PlayerX+2, map_PlayerY, 4) == TILE_GOAL))
            {
                SavePlayerPosition(UNDO_RIGHT);
                map_TotalMoves++;
                map_TotalPushes++;
                map_PlayerX++;
                SetTileType(map_PlayerX+1, map_PlayerY, 4, TILE_BOX_ON_GOAL);
                SetTileType(map_PlayerX, map_PlayerY, 4, TILE_FLOOR);
            }
            ValidateGameStatus();
            break;
        }
        case TILE_BOX_ON_GOAL:
        {
            if ((GetTileType(map_PlayerX+2, map_PlayerY, 4) == TILE_FLOOR))
            {
                SavePlayerPosition(UNDO_RIGHT);
                map_TotalMoves++;
                map_TotalPushes++;
                map_PlayerX++;
                SetTileType(map_PlayerX+1, map_PlayerY, 4, TILE_BOX);
                SetTileType(map_PlayerX, map_PlayerY, 4, TILE_GOAL);
            }
            else if ((GetTileType(map_PlayerX+2, map_PlayerY, 4) == TILE_GOAL))
            {
                SavePlayerPosition(UNDO_RIGHT);
                map_TotalMoves++;
                map_TotalPushes++;
                map_PlayerX++;
                SetTileType(map_PlayerX+1, map_PlayerY, 4, TILE_BOX_ON_GOAL);
                SetTileType(map_PlayerX, map_PlayerY, 4, TILE_GOAL);
            }
            ValidateGameStatus();
            break;
        }
    }
}

void cMap::ValidateGameStatus()
{
    int map_WinLost = 0;
    for (int _zX=0; _zX<map_TileList.size(); _zX++)
    {
        if ((map_TileList[_zX].m_Home == 1) && (map_TileList[_zX].m_Type == TILE_BOX_ON_GOAL))
        {
            map_WinLost++;
        } 
    }
    if (map_WinLost == map_TotalBlocksOnGoal)
    {
        fprintf(stdout, "You Win\n");
        map_Win = true;
    }
}

void cMap::SetMapWin(bool bWin)
{
    map_Win = bWin;
}

bool cMap::GetMapWin()
{
    return map_Win;
}

void cMap::SetMapRunnig(bool bStatus)
{
    map_Running = bStatus;
}

bool cMap::GetMapRunnig()
{
    return map_Running;
}

void cMap::SetMapExit(bool bExit)
{
    map_Exit = bExit;
}

bool cMap::GetMapExit()
{
    return map_Exit;
}

void cMap::SetMapXY(int X, int Y)
{
    map_PosX = X*map_RctTileset.w;
    map_PosY = Y*map_RctTileset.h;
}

void cMap::SetTileWH(int Width, int Height)
{
    map_RctTileset.w = Width;
    map_RctTileset.h = Height;
}

void cMap::SetPlayerXY(int X, int Y)
{
    map_PlayerX = X;
    map_PlayerY = Y;
}

void cMap::SetMapLC(int Lines, int Columns)
{
    map_NumLin = Lines;
    map_NumCol = Columns;
}

int cMap::GetTotalMoves()
{
    return map_TotalMoves;
}

void cMap::DrawStatistics()
{
    /// General border in game information
    std::string tmpBorderInfo;
    tmpBorderInfo.append("Lin: ");
    tmpBorderInfo.append(IntToString(map_PlayerY+1));
    tmpBorderInfo.append("  Col: ");
    tmpBorderInfo.append(IntToString(map_PlayerX+1));
    tmpBorderInfo.append("  Moves/Pushes: ");
    tmpBorderInfo.append(IntToString(map_TotalMoves));
    tmpBorderInfo.append("/");
    tmpBorderInfo.append(IntToString(map_TotalPushes));
    tmpBorderInfo.append("  Map: ");
    tmpBorderInfo.append(map_MapName.substr(7));
    
    map_FontList[FONT_FAST].DrawTextString(tmpBorderInfo, 32, g_ScreenH-map_FontList[FONT_FAST].GetFontHeight()-2, map_SrfDisplay);
}

bool cMap::CheckMapDimensions()
{
    bool tmpReturn = true;
    
    if (((map_NumLin*g_TileH) > (g_ScreenH-52)) || ((map_NumCol*g_TileW) > (g_ScreenW-160)))
    {
        fprintf(stdout, "WARNING: the screen resolution is too small for %s.\nTry resolution greater than: %dx%d\n\n", map_MapName.c_str(), (map_NumCol*g_TileW)+160, (map_NumLin*g_TileH)+52);
        tmpReturn = false;
    }
    
    return tmpReturn;
}

void cMap::DrawGameHUD(SDL_Surface* Display)
{
    std::string tmpStringInfo;
    
    cSurface::Transparent(map_SrfHUD, 255, 255, 255);
    cSurface::OnDraw(Display, map_SrfHUD, g_ScreenW-120, 28, 112, 0, 112, 76);
    cSurface::OnDraw(Display, map_SrfHUD, g_ScreenW-120, g_ScreenH-168, 0, 0, 112, 148);
    /// Display game time
    map_FontList[FONT_FAST].DrawTextString(g_LangStrings.ReadLabel(13), g_ScreenW-88, 46, map_SrfDisplay);
    map_FontList[FONT_FAST].DrawTextString(FormatTime(map_TimeH, map_TimeM, map_TimeS), g_ScreenW-112, 82, map_SrfDisplay);
    /// Display map level
    map_FontList[FONT_FAST].DrawTextString(g_LangStrings.ReadLabel(14), g_ScreenW-93, g_ScreenH-153, map_SrfDisplay);
    tmpStringInfo = GetMapInfo(map_MapName, "Level");
    if (tmpStringInfo.length() > 0)
    {
        map_FontList[FONT_FAST].DrawTextString(tmpStringInfo.substr(7), g_ScreenW-88, g_ScreenH-81, map_SrfDisplay);
    }
    else
    {
        map_FontList[FONT_FAST].DrawTextString("N/A", g_ScreenW-81, g_ScreenH-81, map_SrfDisplay);
    }
    /// Display Map keys
    tmpStringInfo.clear();
    tmpStringInfo.append(g_LangStrings.ReadLabel(10));
    tmpStringInfo.append("  ");
    tmpStringInfo.append(g_LangStrings.ReadLabel(11));
    map_FontList[FONT_FAST].DrawTextString(tmpStringInfo, 34, 12, map_SrfDisplay);
    for (int x=0; x<((g_ScreenW-152)/4); x++)
    {
        cSurface::OnDraw(Display, map_SrfHUD, 28+(4*x), 28, 0, 0, 4, 4);
        cSurface::OnDraw(Display, map_SrfHUD, 28+(4*x), g_ScreenH-24, 0, 0, 4, 4);
    }
    for (int y=0; y<((g_ScreenH-52)/4); y++)
    {
        cSurface::OnDraw(Display, map_SrfHUD, 28, 32+(4*y), 0, 0, 4, 4);
        cSurface::OnDraw(Display, map_SrfHUD, g_ScreenW-128, 32+(4*y), 0, 0, 4, 4);
    }
}

void cMap::ClearMapVector()
{
    map_TileList.clear();
}

bool cMap::SaveScreenShot()
{
    SDL_Surface* tmpSurfaceShot;
    SDL_Surface* tmpSurfaceLogo;
    
    std::string  tmpShotName = "./shots/Img";
    char tmpSeqFile[10];
    
    /// Read values from .ini file
    cIni map_tmpIni;
    map_tmpIni.Load("./config.ini");
    int map_SeqShot = map_tmpIni.ReadInteger("Settings", "Shot", 0);
    /// Generates screenshot file name
    map_SeqShot++;
    sprintf(tmpSeqFile, "%05d", map_SeqShot);
    tmpShotName = tmpShotName + tmpSeqFile + ".bmp";
    /// Update .ini file
    map_tmpIni.WriteInteger("Settings", "Shot", map_SeqShot);
    /// Takes as screenshot
    if ((tmpSurfaceShot = cSurface::OnLoadResolution("./gfx/", "bkg_", g_ScreenW, g_ScreenH)) == NULL)
    {
        fprintf(stdout, "ERROR: unable to save screenshot .. can't load surface");
        return false;
    }
    if ((tmpSurfaceLogo = cSurface::OnLoad("./gfx/logo02_800.png")) == NULL)
    {
        fprintf(stdout, "ERROR: unable to save screenshot .. can't load logo surface");
        return false;
    }
    /// Position
    int shotX = 0;
    int shotY = 0;
    /// Draw logo surface
    shotX = ((tmpSurfaceShot->w)-(tmpSurfaceLogo->w))/2;
    shotY = ((tmpSurfaceShot->h)-(tmpSurfaceLogo->h))/2;
    SDL_SetAlpha(tmpSurfaceLogo, SDL_SRCALPHA, 38);
    cSurface::Transparent(tmpSurfaceLogo, 0, 0, 0);
    cSurface::OnDraw(tmpSurfaceShot, tmpSurfaceLogo, shotX, shotY, 0, 0, 693, 48);
    /// Draw Background surface
    shotX = ((tmpSurfaceShot->w)-((map_NumCol*g_TileW)-4))/2;
    shotY = ((tmpSurfaceShot->h)-((map_NumLin*g_TileH)-4))/2;
    cSurface::OnDraw(tmpSurfaceShot, map_SrfDisplay, shotX, shotY, map_PosX+4, map_PosY+4, (map_NumCol*g_TileW)-4, (map_NumLin*g_TileH)-4);
    /// Save screenshot
    if (SDL_SaveBMP(tmpSurfaceShot, tmpShotName.c_str()) == -1)
    {
        return false;
    }
    SDL_FreeSurface(tmpSurfaceLogo);
    SDL_FreeSurface(tmpSurfaceShot);
    
    return true;
}

void cMap::SetFileList(std::vector<cFilesID> FileList)
{
    map_ListFiles = FileList;
}

std::string cMap::GetRandomMapName()
{
    /// Não cometa o erro de chamar srand() toda vez que for gerar um número aleatório,
    /// chame-o apenas uma vez antes da primeira chamada a rand() gerando um numero em um
    /// intervalo específico.
    /// srand((unsigned)time(0));
    /// chamada movida para o método cMap::OnIniMap();
    
    int Index;
    /// Generates Random integer
    Index = GetRandomInt(0, (map_ListFiles.size()-1));
    
    return map_ListFiles[Index].fid_FileName;
}

void cMap::SavePlayerPosition(int Direiction)
{
    cUndo tmpUndoList;
    switch (Direiction)
    {
        case UNDO_UP:
        {
            /// First
            tmpUndoList.und_BoxY      = GetTileType(map_PlayerX, map_PlayerY-1, 1);
            tmpUndoList.und_BoxX      = GetTileType(map_PlayerX, map_PlayerY-1, 2);
            tmpUndoList.und_BoxID     = GetTileType(map_PlayerX, map_PlayerY-1, 3);
            tmpUndoList.und_BoxType   = GetTileType(map_PlayerX, map_PlayerY-1, 4);
            tmpUndoList.und_BoxHome   = GetTileType(map_PlayerX, map_PlayerY-1, 5);
            /// Second
            tmpUndoList.und_BoxYb     = GetTileType(map_PlayerX, map_PlayerY-2, 1);
            tmpUndoList.und_BoxXb     = GetTileType(map_PlayerX, map_PlayerY-2, 2);
            tmpUndoList.und_BoxIDb    = GetTileType(map_PlayerX, map_PlayerY-2, 3);
            tmpUndoList.und_BoxTypeb  = GetTileType(map_PlayerX, map_PlayerY-2, 4);
            tmpUndoList.und_BoxHomeb  = GetTileType(map_PlayerX, map_PlayerY-2, 5);
            //fprintf(stdout, "X: %d  Y: %d  ID: %d  Type: %d  Home: %d\n", GetTileType(map_PlayerX, map_PlayerY+1, 1), GetTileType(map_PlayerX, map_PlayerY+1, 2), GetTileType(map_PlayerX, map_PlayerY+1, 3), GetTileType(map_PlayerX, map_PlayerY+1, 4), GetTileType(map_PlayerX, map_PlayerY+1, 5));
            break;
        }
        case UNDO_DOWN:
        {
            /// First
            tmpUndoList.und_BoxY      = GetTileType(map_PlayerX, map_PlayerY+1, 1);
            tmpUndoList.und_BoxX      = GetTileType(map_PlayerX, map_PlayerY+1, 2);
            tmpUndoList.und_BoxID     = GetTileType(map_PlayerX, map_PlayerY+1, 3);
            tmpUndoList.und_BoxType   = GetTileType(map_PlayerX, map_PlayerY+1, 4);
            tmpUndoList.und_BoxHome   = GetTileType(map_PlayerX, map_PlayerY+1, 5);
            /// Second
            tmpUndoList.und_BoxYb     = GetTileType(map_PlayerX, map_PlayerY+2, 1);
            tmpUndoList.und_BoxXb     = GetTileType(map_PlayerX, map_PlayerY+2, 2);
            tmpUndoList.und_BoxIDb    = GetTileType(map_PlayerX, map_PlayerY+2, 3);
            tmpUndoList.und_BoxTypeb  = GetTileType(map_PlayerX, map_PlayerY+2, 4);
            tmpUndoList.und_BoxHomeb  = GetTileType(map_PlayerX, map_PlayerY+2, 5);
            break;
        }
        case UNDO_LEFT:
        {
            /// First
            tmpUndoList.und_BoxY      = GetTileType(map_PlayerX-1, map_PlayerY, 1);
            tmpUndoList.und_BoxX      = GetTileType(map_PlayerX-1, map_PlayerY, 2);
            tmpUndoList.und_BoxID     = GetTileType(map_PlayerX-1, map_PlayerY, 3);
            tmpUndoList.und_BoxType   = GetTileType(map_PlayerX-1, map_PlayerY, 4);
            tmpUndoList.und_BoxHome   = GetTileType(map_PlayerX-1, map_PlayerY, 5);
            /// Second
            tmpUndoList.und_BoxYb     = GetTileType(map_PlayerX-2, map_PlayerY, 1);
            tmpUndoList.und_BoxXb     = GetTileType(map_PlayerX-2, map_PlayerY, 2);
            tmpUndoList.und_BoxIDb    = GetTileType(map_PlayerX-2, map_PlayerY, 3);
            tmpUndoList.und_BoxTypeb  = GetTileType(map_PlayerX-2, map_PlayerY, 4);
            tmpUndoList.und_BoxHomeb  = GetTileType(map_PlayerX-2, map_PlayerY, 5);
            break;
        }
        case UNDO_RIGHT:
        {
            /// First
            tmpUndoList.und_BoxY      = GetTileType(map_PlayerX+1, map_PlayerY, 1);
            tmpUndoList.und_BoxX      = GetTileType(map_PlayerX+1, map_PlayerY, 2);
            tmpUndoList.und_BoxID     = GetTileType(map_PlayerX+1, map_PlayerY, 3);
            tmpUndoList.und_BoxType   = GetTileType(map_PlayerX+1, map_PlayerY, 4);
            tmpUndoList.und_BoxHome   = GetTileType(map_PlayerX+1, map_PlayerY, 5);
            /// Second
            tmpUndoList.und_BoxYb     = GetTileType(map_PlayerX+2, map_PlayerY, 1);
            tmpUndoList.und_BoxXb     = GetTileType(map_PlayerX+2, map_PlayerY, 2);
            tmpUndoList.und_BoxIDb    = GetTileType(map_PlayerX+2, map_PlayerY, 3);
            tmpUndoList.und_BoxTypeb  = GetTileType(map_PlayerX+2, map_PlayerY, 4);
            tmpUndoList.und_BoxHomeb  = GetTileType(map_PlayerX+2, map_PlayerY, 5);
            break;
        }
    }
    /// Saves player position
    tmpUndoList.und_PlayerX  = map_PlayerX;
    tmpUndoList.und_PlayerY  = map_PlayerY;
    /// Register saved positions
    map_UndoList.push_back(tmpUndoList);
}

void cMap::RestoreLastPlayerPosition()
{
    if (!map_UndoList.empty())
    {
        int tmpLastItem = map_UndoList.size()-1;
        /// Restores player position
        map_PlayerX = map_UndoList[tmpLastItem].und_PlayerX;
        map_PlayerY = map_UndoList[tmpLastItem].und_PlayerY;
        /// Restores box positions (first)
        SetTileType(map_UndoList[tmpLastItem].und_BoxX, map_UndoList[tmpLastItem].und_BoxY, 3, map_UndoList[tmpLastItem].und_BoxID);
        SetTileType(map_UndoList[tmpLastItem].und_BoxX, map_UndoList[tmpLastItem].und_BoxY, 4, map_UndoList[tmpLastItem].und_BoxType);
        /// Restores box positions (second)
        SetTileType(map_UndoList[tmpLastItem].und_BoxXb, map_UndoList[tmpLastItem].und_BoxYb, 3, map_UndoList[tmpLastItem].und_BoxIDb);
        SetTileType(map_UndoList[tmpLastItem].und_BoxXb, map_UndoList[tmpLastItem].und_BoxYb, 4, map_UndoList[tmpLastItem].und_BoxTypeb);
        SetTileType(map_UndoList[tmpLastItem].und_BoxXb, map_UndoList[tmpLastItem].und_BoxYb, 5, map_UndoList[tmpLastItem].und_BoxHomeb);
        /// Decrease move counter
        if ((map_UndoList[tmpLastItem].und_BoxType == TILE_BOX) || (map_UndoList[tmpLastItem].und_BoxType == TILE_BOX_ON_GOAL))
        {
            map_TotalPushes--;
        }
        map_TotalMoves--;
        /// Remove restored elements from undo vector
        map_UndoList.pop_back();
    }
}

void cMap::ClearAllSavedPositions()
{
    if (!map_UndoList.empty())
    {
        map_UndoList.clear();
    }
}