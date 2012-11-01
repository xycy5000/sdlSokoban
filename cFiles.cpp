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
#include <SDL/SDL_video.h>

#include "cFiles.h"
#include "cSurface.h"

cFiles::cFiles()
{
    /// Header information dimensions
    fil_RecHeader.x    = 0;
    fil_RecHeader.y    = 0;
    fil_RecHeader.w    = 372;
    fil_RecHeader.h    = 88;
    /// Cursor dimensions
    fil_RecCursor.x    = 0;
    fil_RecCursor.y    = 514;
    fil_RecCursor.w    = 364;
    fil_RecCursor.h    = 19;
    /// Main browse list dimensions
    fil_RecFileList.x  = 0;
    fil_RecFileList.y  = 88;
    fil_RecFileList.w  = 372;
    fil_RecFileList.h  = 426;
    /// Map File Informations
    fil_RecMapInfo.x   = 0;
    fil_RecMapInfo.y   = 0;
    fil_RecMapInfo.w   = 376;
    fil_RecMapInfo.h   = 300;
    /// Main surface
    fil_SurfBrowse     = NULL;
    fil_SurfMapInfo    = NULL;
    fil_SurfBackground = NULL;
    fil_SurfDisplay    = NULL;
}

cFiles::~cFiles()
{
    SDL_FreeSurface(fil_SurfBrowse);
}

bool cFiles::OnInitFil(SDL_Surface* Display, std::string Path, int PosX, int PosY)
{
    if ((fil_SurfBrowse = cSurface::OnLoad("./gfx/surface01_533.png")) == NULL)
    {
        fprintf(stdout, "ERROR: unable to load surface file ..");
        return false;
    }
    if ((fil_SurfBackground = cSurface::OnLoadResolution("./gfx/", "bkg_", g_ScreenW, g_ScreenH)) == NULL)
    {
        fprintf(stdout, "ERROR: unable to load surface file ..");
        return false;
    }
    if ((fil_SurfMapInfo = cSurface::OnLoad("./gfx/surface05_376.png")) == NULL)
    {
        fprintf(stdout, "ERROR: unable to load surface file ..");
        return false;
    }
    /// Getting directory information
    GetListFiles(Path);
    /// Browse Screen Position
    fil_BrowseX     = PosX;
    fil_BrowseY     = PosY;
    /// File list
    fil_TotalFiles  = GetTotalFiles();
    //fprintf(stdout, "%d", fil_TotalFiles);
    fil_FilesX      = 0;
    fil_FilesY      = 0;
    /// Setting first and last files in the list
    fil_FirstFile   = 0;
    /// Check total files in folder and setting fil_LastFile flag
    if (fil_TotalFiles < 20)
    {
        fil_LastFile = fil_TotalFiles;
    }
    else
    {
        fil_LastFile = 20;
    }
    /// Setting first and last lines in the list
    fil_FirstLine   = 0;
    /// Check total files in folder and setting fil_LastLine flag
    if (fil_TotalFiles < 20)
    {
        fil_LastLine = fil_TotalFiles;
    }
    else
    {
        fil_LastLine = 20;
    }
    /// Setting actual line
    fil_ActualLine  = 0;
    fil_TotalLines  = 0;
    /// Initial Cursor Position
    fil_CursorX     = PosX+4;
    fil_CursorY     = PosY+34;
    /// Status Flags
    fil_Running     = true;
    fil_Exit        = false;
    fil_ActiveFont  = 0;
    /// Main Surface Display
    fil_SurfDisplay = Display;
    /// Enable Key Repeat on Browse
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
    
    return true;
}

/*!
 * Load an Vector of Font Objects.
 * 
 * @param[out] true if Load is successfull and false if an error ocurred.
 * @param[in] File      Path and filename of Bitmap font (e.g.: ./fonts/font.png)
 * @param[in] First     First character in the font (e.g.: '!' or 33)
 * @param[in] Last      Last character in the font (e.g.: 'Z' or 90)
 * @param[in] Width     Width of character in the font
 * @param[in] Height    Height of character in the font
 * @param[in] Direction Type of font. Uses: FONT_HORIZONTAL or FONT_VERTICAL
*/
bool cFiles::OnLoadFontBrowser(std::string File, int First, int Last, int Width, int Height, int Direction)
{
    fil_FontFiles.clear();
    cFont tmp_FontBrowser;
    fil_FontFiles.push_back(tmp_FontBrowser);
    
    return fil_FontFiles[fil_ActiveFont].OnLoad(File, First, Last, Width, Height, Direction);
}

void cFiles::OnRenderFil()
{
    std::string tmpFileName;
    
    DrawFileListBox(255, 0, 255);
    for (int i=fil_FirstFile; i<fil_TotalFiles; i++)
    {
        if (i <= (fil_LastFile-1))
        {
            if (fil_FilesY < fil_LastLine)
            {
                if ((GetFileName(i).length()*fil_FontFiles[fil_ActiveFont].GetFontWidth()) > (fil_RecFileList.w-36))
                {
                    tmpFileName = GetFileName(i).substr(0, (fil_RecFileList.w-116)/fil_FontFiles[fil_ActiveFont].GetFontWidth());
                    tmpFileName.append(" .. ");
                    tmpFileName.append(GetFileName(i).substr(GetFileName(i).length()-3, 3));
                }
                else
                {
                    tmpFileName = GetFileName(i);
                }
                fil_FontFiles[fil_ActiveFont].DrawTextString(tmpFileName, fil_BrowseX+22, (fil_BrowseY+138)+(19*fil_FilesY), fil_SurfDisplay, FONT_DEFAULT);
                fil_FilesY++;
            }
            else
            {
                if ((GetFileName(i).length()*fil_FontFiles[fil_ActiveFont].GetFontWidth()) > (fil_RecFileList.w-36))
                {
                    tmpFileName = GetFileName(i).substr(0, (fil_RecFileList.w-116)/fil_FontFiles[fil_ActiveFont].GetFontWidth());
                    tmpFileName.append(" .. ");
                    tmpFileName.append(GetFileName(i).substr(GetFileName(i).length()-3, 3));
                }
                else
                {
                    tmpFileName = GetFileName(i);
                }
                fil_FontFiles[fil_ActiveFont].DrawTextString(tmpFileName, fil_BrowseX+22, (fil_BrowseY+138)+(19*fil_FilesY), fil_SurfDisplay, FONT_DEFAULT);
            }
        }
        tmpFileName.clear();
    }
    fil_TotalLines = GetTotalFiles();
    if (fil_TotalLines < fil_LastLine)
    {
        fil_LastLine = fil_TotalLines;
        fil_LastFile = fil_TotalLines;
    }
    fil_FilesY = 0;
}

void cFiles::OnEventFil(SDL_Event* Event)
{
    switch (Event->type)
    {
        case SDL_KEYDOWN:
        {
            switch (Event->key.keysym.sym)
            {
                case SDLK_UP:
                {
                    MoveFileListUP();
                    UpdateFileInfo();
                    break;
                }
                case SDLK_DOWN:
                {
                    MoveFileListDOWN();
                    UpdateFileInfo();
                    break;
                }
                case SDLK_RETURN:
                {
                    fil_Running       = false;
                    fil_MapNameReturn = fil_ListFiles[fil_ActualLine].fid_FileName.c_str();
                    break;
                }
                case SDLK_ESCAPE:
                {
                    fil_Running = false;
                    fil_Exit    = true;
                    SDL_EnableKeyRepeat(0, SDL_DEFAULT_REPEAT_INTERVAL);
                    break;
                }
            }
            break;
        }
    }
}

void cFiles::MoveFileListUP()
{
    if (fil_CursorY > (fil_BrowseY+34))
    {
        fil_CursorY -= fil_RecCursor.h;
    }
    else
    {
        if (fil_FirstFile > fil_FirstLine)
        {
            fil_FirstFile--;
            fil_LastFile--;
        }
    }
    
    if (fil_ActualLine > fil_FirstFile)
    {
        fil_ActualLine--;
    }
}

void cFiles::MoveFileListDOWN()
{
    if (fil_ActualLine < fil_LastFile)
    {
        if ((fil_TotalLines-fil_ActualLine) > 1)
        {
            fil_ActualLine++;
        }
    }
    
    //if (fil_CursorY < (fil_BrowseY+380))
    if (fil_CursorY < (fil_BrowseY+(fil_RecCursor.h*fil_LastLine)))
    {
        fil_CursorY += fil_RecCursor.h;
    }
    else
    {
        if (fil_LastFile < fil_TotalLines)
        {
            fil_FirstFile++;
            fil_LastFile++;
        }
    }
}
void cFiles::SetFontRGB(int R, int G, int B)
{
    fil_FontFiles[fil_ActiveFont].SetRGB(R, G, B);
}

void cFiles::GetListFiles(std::string Path)
{
    UINT tmp_Counter(0);
    fil_ListFiles.clear();
    
    std::string tmp_Buffer;
    std::string tmp_FileName[10000];
    
    bool tmp_Working(true);
    
    WIN32_FIND_DATA tmp_MyImage;
    HANDLE tmp_MyHandle = FindFirstFile(Path.c_str(), &tmp_MyImage);
    
    int tmp_fCounter = 0;
    
    if (tmp_MyHandle != INVALID_HANDLE_VALUE)
    {
        tmp_Buffer = tmp_MyImage.cFileName;
        tmp_FileName[tmp_Counter] = tmp_Buffer;
        tmp_Buffer = tmp_MyImage.cFileName;
        cFilesID tmp_FileListID;
        tmp_FileListID.fid_FileID   = tmp_fCounter;
        tmp_FileListID.fid_FileName = tmp_Buffer;
        fil_ListFiles.push_back(tmp_FileListID);
        tmp_fCounter++;
        while (tmp_Working)
        {
            FindNextFile(tmp_MyHandle, &tmp_MyImage);
            if (tmp_MyImage.cFileName != tmp_Buffer)
            {
                tmp_Buffer = tmp_MyImage.cFileName;
                ++tmp_Counter;
                tmp_FileName[tmp_Counter] = tmp_Buffer;
                cFilesID tmp_FileListID;
                tmp_FileListID.fid_FileID   = tmp_fCounter;
                tmp_FileListID.fid_FileName = tmp_Buffer;
                fil_ListFiles.push_back(tmp_FileListID);
                tmp_fCounter++;
            }
            else
            {
                tmp_Working = false;
            }
        }
    }
}

std::string cFiles::GetFileName(int Index)
{
    return fil_ListFiles[Index].fid_FileName;
}

int cFiles::GetTotalFiles()
{
    return fil_ListFiles.size();
}

void cFiles::SetBrowseRunning(bool blnRunning)
{
    fil_Running = blnRunning;
}

bool cFiles::GetBrowseRunning()
{
    return fil_Running;
}

void cFiles::SetBrowseExit(bool blnExit)
{
    fil_Exit = blnExit;
}

bool cFiles::GetBrowseExit()
{
    return fil_Exit;
}

int cFiles::GetBrowseWidth()
{
    return fil_RecFileList.w;
}

int cFiles::GetBrowseHeight(int Type)
{
    int tmpReturn;
    
    switch (Type)
    {
        case 0:
        {
            tmpReturn = fil_RecHeader.h;
            break;
        }
        case 1:
        {
            tmpReturn = fil_RecFileList.h;
            break;
        }
    }
    
    return tmpReturn;
}

void cFiles::DrawFileListBox(int R, int G, int B)
{
    int tmpPosY;
    std::string tmpTotalFiles;
    /// Draw Boxes
    cSurface::OnDraw(fil_SurfDisplay, fil_SurfBackground, 0, 0);
    cSurface::Transparent(fil_SurfBrowse, R, G, B);
    cSurface::OnDraw(fil_SurfDisplay, fil_SurfBrowse, fil_BrowseX, fil_BrowseY, fil_RecHeader.x, fil_RecHeader.y, fil_RecHeader.w, fil_RecHeader.h);
    cSurface::OnDraw(fil_SurfDisplay, fil_SurfBrowse, fil_BrowseX, fil_BrowseY+100, fil_RecFileList.x, fil_RecFileList.y, fil_RecFileList.w, fil_RecFileList.h);
    cSurface::OnDraw(fil_SurfDisplay, fil_SurfBrowse, fil_CursorX, fil_CursorY+100, fil_RecCursor.x, fil_RecCursor.y, fil_RecCursor.w, fil_RecCursor.h);
    /// Draw Map Info Box
    cSurface::OnDraw(fil_SurfDisplay, fil_SurfMapInfo, fil_BrowseX+fil_RecFileList.w+12, fil_BrowseY+100, fil_RecMapInfo.x, fil_RecMapInfo.y, fil_RecMapInfo.w, fil_RecMapInfo.h);
    /// File Browser List
    fil_FontFiles[fil_ActiveFont].DrawTextString(g_LangStrings.ReadLabel(20), 28, g_ScreenH-20, fil_SurfDisplay);
    fil_FontFiles[fil_ActiveFont].DrawTextString(g_LangStrings.ReadLabel(21), (g_LangStrings.LenghtLabel(20)*fil_FontFiles[fil_ActiveFont].GetFontWidth())+50, g_ScreenH-20, fil_SurfDisplay);
    /// Header Information
    tmpPosY = (g_ScreenH-(fil_RecHeader.h+fil_RecFileList.h))/2;
    fil_FontFiles[fil_ActiveFont].DrawTextString(g_LangStrings.ReadLabel(22), 28, tmpPosY+20, fil_SurfDisplay, FONT_DEFAULT);
    fil_FontFiles[fil_ActiveFont].DrawTextString(g_LangStrings.ReadLabel(23), 28, tmpPosY+40, fil_SurfDisplay, FONT_DEFAULT);
    fil_FontFiles[fil_ActiveFont].DrawTextString(g_LangStrings.ReadLabel(24), 28, tmpPosY+60, fil_SurfDisplay, FONT_DEFAULT);
    /// Total Files on Folder
    tmpTotalFiles.append(g_LangStrings.ReadLabel(25));
    tmpTotalFiles.append(" ");
    tmpTotalFiles.append(IntToString(fil_TotalFiles));
    tmpTotalFiles.append(" ");
    tmpTotalFiles.append(g_LangStrings.ReadLabel(26));
    fil_FontFiles[fil_ActiveFont].DrawTextString(tmpTotalFiles, 28, tmpPosY+110, fil_SurfDisplay, FONT_DEFAULT);
    tmpTotalFiles.clear();
    /// Map Additional Information
    fil_FontFiles[fil_ActiveFont].DrawTextString(g_LangStrings.ReadLabel(19),  412, tmpPosY+110, fil_SurfDisplay, FONT_DEFAULT);
    fil_FontFiles[fil_ActiveFont].DrawTextString(fil_Author,  412, g_ScreenH-419, fil_SurfDisplay, FONT_DEFAULT);
    fil_FontFiles[fil_ActiveFont].DrawTextString(fil_Comment, 412, g_ScreenH-379, fil_SurfDisplay, FONT_DEFAULT);
    fil_FontFiles[fil_ActiveFont].DrawTextString(fil_Date,    412, g_ScreenH-339, fil_SurfDisplay, FONT_DEFAULT);
    fil_FontFiles[fil_ActiveFont].DrawTextString(fil_Contact, 412, g_ScreenH-299, fil_SurfDisplay, FONT_DEFAULT);
    fil_FontFiles[fil_ActiveFont].DrawTextString(fil_Level,   412, g_ScreenH-249, fil_SurfDisplay, FONT_DEFAULT);
}

void cFiles::UpdateFileInfo()
{
    std::string tmpFileName;
    
    tmpFileName.append(g_XsbPath);
    tmpFileName = tmpFileName+fil_ListFiles[fil_ActualLine].fid_FileName;
    
    fil_Title      = GetMapInfo(tmpFileName, "Title");
    fil_Author     = GetMapInfo(tmpFileName, "Author");
    fil_Date       = GetMapInfo(tmpFileName, "Date");
    fil_Level      = GetMapInfo(tmpFileName, "Level");
    fil_Difficulty = GetMapInfo(tmpFileName, "Difficulty");
    fil_Contact    = GetMapInfo(tmpFileName, "AuthorMail");
    fil_Comment    = GetMapInfo(tmpFileName, "Collection");
}

std::string cFiles::GetActualFileName()
{
//    std::string tmpFileName;
//    
//    tmpFileName.append("./maps/");
//    tmpFileName = tmpFileName+fil_ListFiles[fil_ActualLine].fid_FileName;
    
//    return tmpFileName;
    return fil_ListFiles[fil_ActualLine].fid_FileName;
}

void cFiles::SetNextMapFile()
{
    if (fil_ActualLine > fil_TotalFiles)
    {
        fil_ActualLine = 0;
    }
    else
    {
        fil_ActualLine++;
    }
}

void cFiles::DisplayMapPreview(std::string File, int PosX, int PosY)
{
    
}

std::vector<cFilesID> cFiles::GetFileList()
{
    return fil_ListFiles;
}