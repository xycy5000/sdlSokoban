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
#ifndef CEDITOR_H
    #define CEDITOR_H

#include "cGlobals.h"
#include "cFont.h"
#include "cTile.h"

class cEditor {
    public:
        cEditor();
        virtual ~cEditor();
        /// Initializes Editor
        bool OnInitEdt(SDL_Surface* Display);
        /// Render the Map in editor
        void OnRenderEdt();
        /// Parse Map events (Keys, etc)
        void OnEventEdt(SDL_Event* Event);
        /// Check Editor status
        void OnLoopEdt();
        /// Set Map running flag
        void SetEditorRunnig(bool bStatus);
        /// Get Map running flag
        bool GetEditorRunnig();
        /// Set Map exit status flag
        void SetEditorExit(bool bExit);
        /// Get Map exit status flag
        bool GetEditorExit();
        /// Configure Map number of lines and columns
        void SetMapLC(int Lines, int Columns);
        /// Configure initial Map position
        void SetMapXY(int X, int Y);
        /// Configure Map tile dimensions
        void SetTileWH(int Width, int Height);
        /// Setting initial position of player
        void SetPlayerXY(int X, int Y);
        /// Paint all area map
        void PaintAreaMap(int TileID = TILE_ID_DRAW, int TileType = TILE_FLOOR);
        /// Get Tile Type
        void SetTileType(int X, int Y, int Type, int Value);
        /// Get Tile Type
        int GetTileType(int X, int Y, int Type);
        /// Draw Editor HUD
        void DrawFrameHUD();
        /// Check if map file is valid
        bool CheckMapFile();
        /// Load/Reload Map file
        bool LoadMap(std::string File, int Type = MAP_FILE_MAP);
        /// Player movement
        void MoveKeyUP();
        void MoveKeyDOWN();
        void MoveKeyLEFT();
        void MoveKeyRIGHT();
        /// Event Keys and Mouse
        void KeyDownRender(SDLKey sym, SDLMod mod, Uint16 unicode);
        /// Check Key Down event at save file message box
        void KeyDownSaveFile(SDLKey sym, SDLMod mod, Uint16 unicode);
        /// Check Key Down Event at Load File message box
        void KeyDownLoadFile(SDLKey sym, SDLMod mod, Uint16 unicode);
        /// Check Key Down Event at overwrite File message box
        void KeyDownOverwrite(SDLKey sym, SDLMod mod, Uint16 unicode);
        /// Check Mouse Cursor Movement
        void MouseCursorMove(int mX, int mY);
        /// Check Mouse Button Down Event
        void MouseButtonDown(int mX, int mY);
        /// Saves an map file on disk
        bool SaveMapFile(std::string File);
        
    private:
        /// Map initial positioning
        int edt_PosX;
        int edt_PosY;
        /// Map total lines and columns
        int edt_NumLin;
        int edt_NumCol;
        /// Tileset Surface dimensions
        SDL_Rect edt_RctTileset;
        /// Background surface dimensions
        SDL_Rect edt_RctBackground;
        /// Cursor surface dimensions
        SDL_Rect edt_RctTextBox;
        /// Black Game Area
        SDL_Rect edt_RctBlackArea;
        /// Cursor Mouse
        SDL_Rect edt_RctCurMouse;
        /// Flag controls of editor state
        bool edt_Running;
        bool edt_Exit;
        /// Tileset R, G, B
        int edt_TileR;
        int edt_TileG;
        int edt_TileB;
        /// Player position and tile type on map vector
        int edt_PlayerX;
        int edt_PlayerY;
        int edt_TileType;
        int edt_TilePlayer;
        /// Record mouse position in map surface
        int edt_MouseX;
        int edt_MouseY;
        int edt_CursorType;
        /// Internal use for button down/up mouse controls (paint)
        bool edt_MouseDownUp;
        /// Type of map file: .XSB or .MAP
        int edt_TypeOfMap;
        /// Name of map file
        std::string edt_FileName;
        /// Total goals in map
        int edt_TotalBlocksOnGoal;
        /// General surfaces
        SDL_Surface* edt_SrfTileSet;
        SDL_Surface* edt_SrfDisplay;
        SDL_Surface* edt_SrfTextBox;
        SDL_Surface* edt_SrfHUD;
        SDL_Surface* edt_SrfBackground;
        SDL_Surface* edt_SrfToolBox;
        SDL_Surface* edt_SrfCurMouse;
        /// Tilelist map vector
        std::vector<cTile> edt_TileList;
        /// Font HUD object
        cFont edt_Font;
        /// Positions of tool buttons
        struct TMP_CURSOR_POS_T
        {
            int PosUx;
            int PosUy;
            int PosDx;
            int PosDy;
        } C_POS;
        /// State flag control
        struct MAP_EDIT_STATE_T
        {
            int editState;
        } MAP_EDIT_STATE;

};
#endif	/* CEDITOR_H */