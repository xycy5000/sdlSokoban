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
#ifndef CMAP_H
    #define CMAP_H

#include "cTile.h"
#include "cFont.h"
#include "cTime.h"
#include "cLang.h"
#include "cFilesID.h"

class cMap {
    public:
        cMap();
        virtual ~cMap();
        /// Initializes Map file
        bool OnInitMap(std::string Map);
        /// Render the Map
        void OnRenderMap(SDL_Surface* Display);
        /// Parse Map events (Keys, etc)
        void OnEventMap(SDL_Event* Event);
        /// Check Map game status
        void OnLoopMap();
        /// Load/Reload Map file
        bool LoadMap(std::string File, int Type = MAP_FILE_MAP);
        /// Load map filelist (passed by cFile class at cGame::OnInitGam()
        void SetFileList(std::vector<cFilesID> FileList);
        /// Setting Map tile type
        void SetTileType(int X, int Y, int Type, int Value);
        /// Get Map tile type
        int  GetTileType(int X, int Y, int Type);
        /// Block movement methods
        void MoveBlockUP();
        void MoveBlockDOWN();
        void MoveBlockLEFT();
        void MoveBlockRIGHT();
        /// Check if player won the game
        void ValidateGameStatus();
        /// Internal method to check Map dimensions and screen dimensions
        bool CheckMapDimensions();
        /// Setting game win flag
        void SetMapWin(bool bWin);
        /// Get game win flag
        bool GetMapWin();
        /// Set Map running flag
        void SetMapRunnig(bool bStatus);
        /// Get Map running flag
        bool GetMapRunnig();
        /// Set Map exit status flag
        void SetMapExit(bool bExit);
        /// Get Map exit status flag
        bool GetMapExit();
        /// Configure Map number of lines and columns
        void SetMapLC(int Lines, int Columns);
        /// Configure initial Map position
        void SetMapXY(int X, int Y);
        /// Configure Map tile dimensions
        void SetTileWH(int Width, int Height);
        /// Setting initial position of player
        void SetPlayerXY(int X, int Y);
        /// Get total player move
        int  GetTotalMoves();
        /// Draw in game information and statistics
        void DrawStatistics();
        /// Draw screen frames and boxes
        void DrawGameHUD(SDL_Surface* Display);
        /// Clear Map vector list
        void ClearMapVector();
        /// Takes a snapshot
        bool SaveScreenShot();
        /// Get Random map file name
        std::string GetRandomMapName();
        
        /// Undo movements
        void SavePlayerPosition(int Direiction);
        void RestoreLastPlayerPosition();
        void ClearAllSavedPositions();
        
    private:
        /// Map initial positioning
        int map_PosX;
        int map_PosY;
        /// Map total lines and columns
        int map_NumLin;
        int map_NumCol;
        /// Tileset Surface dimensions
        SDL_Rect map_RctTileset;
        /// Background surface dimensions
        SDL_Rect map_RctBackground;
        /// Message box surface dimensions
        SDL_Rect map_RctMessageBox;
        /// Black Game Area
        SDL_Rect map_RctBlackArea;
        /// Flag controls of game state (game win, show msgbox, game running and game exit)
        bool map_Win;
        bool map_ShowMsgBox;
        bool map_Running;
        bool map_Exit;
        /// Player position in game
        int map_PlayerX;
        int map_PlayerY;
        /// Total goals in game
        int map_TotalBlocksOnGoal;
        /// Total of moves in game
        int map_TotalMoves;
        /// Total Box Pushes
        int map_TotalPushes;
        /// Type of map file: .XSB or .MAP
        int map_TypeOfMap;
        /// Total game time
        int map_TimeH;
        int map_TimeM;
        int map_TimeS;
        /// List files information
        int map_TotalFiles;
        /// Map Informations
        std::string map_Title;
        std::string map_Author;
        std::string map_Date;
        std::string map_Level;
        std::string map_Difficulty;
        std::string map_Contact;
        std::string map_Comment;
        /// General surfaces
        SDL_Surface* map_SrfTileSet;
        SDL_Surface* map_SrfBackground;
        SDL_Surface* map_SrfMessageBox;
        SDL_Surface* map_SrfDisplay;
        SDL_Surface* map_SrfHUD;
        SDL_Surface* map_SrfHelpScreen;
        /// Tilelist map vector
        std::vector<cTile> map_TileList;
        /// Stores map name running
        std::string map_MapName;
        /// Game time object
        cTime map_Time;
        /// File list vector (passed by cFile class. For internal use only)
        std::vector<cFilesID> map_ListFiles;
        /// Save player movement
        std::vector<cUndo>    map_UndoList;
        /// Font List Files
        std::vector<cFont>    map_FontList;
        /// Map State
        struct MAP_STATE_T
        {
            int mapState;
        } MAP_STATE;
};
#endif	/* CMAP_H */