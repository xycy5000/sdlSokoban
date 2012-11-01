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
#ifndef CFILES_H
     #define CFILES_H

#include "cFont.h"
#include "cGlobals.h"
#include "cLang.h"
#include "cFilesID.h"

class cFiles {
    public:
        cFiles();
        virtual ~cFiles();
        /// Main class methods
        bool OnInitFil(SDL_Surface* Display, std::string Path, int PosX, int PosY);
        void OnRenderFil();
        void OnEventFil(SDL_Event* Event);
        /// Font Methods
        bool OnLoadFontBrowser(std::string File, int First, int Last, int Width, int Height, int Direction);
        void SetFontRGB(int R = 255, int G = 0, int B = 255);
        /// State class flags
        void SetBrowseRunning(bool blnRunning);
        bool GetBrowseRunning();
        void SetBrowseExit(bool blnExit);
        bool GetBrowseExit();
        int  GetBrowseWidth();
        int  GetBrowseHeight(int Type);
        /// File class information
        void GetListFiles(std::string Path);
        int  GetTotalFiles();
        std::string GetFileName(int Index);
        std::string GetActualFileName();
        void UpdateFileInfo();
        void SetNextMapFile();
        
        /// Draw boxes
        void DrawFileListBox(int R = 255, int G = 0, int B = 255);
        void MoveFileListUP();
        void MoveFileListDOWN();
        
        /// Display an Map Preview
        void DisplayMapPreview(std::string File, int PosX, int PosY);
        
        /// Return vector file list generated
        std::vector<cFilesID> GetFileList();

    private:
        /// Browse surface dimensions
        SDL_Rect fil_RecFileList;
        SDL_Rect fil_RecCursor;
        SDL_Rect fil_RecHeader;
        SDL_Rect fil_RecMapInfo;
        /// Browse Position
        int fil_BrowseX;
        int fil_BrowseY;
        /// List files Position
        int fil_FilesX;
        int fil_FilesY;
        /// List file browse control
        int fil_FirstFile;
        int fil_LastFile;
        int fil_FirstLine;
        int fil_LastLine;
        int fil_ActualLine;
        int fil_TotalLines;
        /// Cursor position
        int fil_CursorX;
        int fil_CursorY;
        /// Misc controls
        int fil_ActiveFont;
        int fil_TotalFiles;
        /// Status flags
        bool fil_Running;
        bool fil_Exit;
        /// ***************************************************** ///
        std::string fil_MapNameReturn;
        std::string fil_SurfaceFiles[4];
        /// Map File Informations
        std::string fil_Title;
        std::string fil_Author;
        std::string fil_Date;
        std::string fil_Level;
        std::string fil_Difficulty;
        std::string fil_Contact;
        std::string fil_Comment;
        /// ****************************************************** ///
        
        /// Main browse surface
        SDL_Surface* fil_SurfDisplay;
        SDL_Surface* fil_SurfBrowse;
        SDL_Surface* fil_SurfBackground;
        SDL_Surface* fil_SurfMapInfo;
        /// File list vector
        std::vector<cFilesID> fil_ListFiles;
        /// File list font object
        std::vector<cFont>    fil_FontFiles;
};
#endif	/* CFILES_H */