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
#ifndef CGLOBALS_H
    #define CGLOBALS_H

#include "cDefines.h"
#include "cLang.h"

/// Screen Resolution
extern int  g_ScreenW;
extern int  g_ScreenH;
/// Screen Bits Per Pixel
extern int  g_Bpp;
/// Toggle Fullscreen mode
extern bool g_FullScreen;
/// Sound and Music flags
extern bool g_PlaySound;
extern bool g_PlayMusic;
/// Window flags (Internal)
extern Uint32 g_Flags;
/// Show fps counter
extern bool g_ShowFps;
/// Tile Size
extern int  g_TileW;
extern int  g_TileH;
/// Total Language Strings
extern int  g_LangTotal;
/// Surface Files
extern string g_TileSurface;
extern string g_MainSurface;
/// Language Files
extern string g_LangType;
/// Language File
extern cLang g_LangStrings;
/// Path of Xsb files
extern string g_XsbPath;
/// Map Information
extern string g_Title;
extern string g_Author;
extern string g_Collection;
extern string g_AuthorMail;
extern string g_AuthorPage;
extern string g_Level;
extern string g_Date;
extern string g_Comment;
/// Find String in another String
bool FindString(const string& strtarget, const string& strfind);
/// Verify if File Exists in disk
bool FileExists(const string& filename);
/// Check if an Map Line is a .XSB valid line
bool ValidateMapLine(std::string Text);
/// Return Number of lines in map file
int  GetMapLines(const string& File, int Type = MAP_FILE_MAP);
/// Return Number of columns in map file
int  GetMapColumns(const string& File, int Type = MAP_FILE_MAP);
/// Return Type of Map (.XSB or .MAP)
int  GetMapType(std::string File);
/// Generates Random number, used to load random puzzle
int  GetRandomInt(int Lowest, int Highest);
/// Internal method used to convert .xsb file into .map before to load
void ConvertXSBToMap(std::string File, int NumCols);
/// Convert from .map To .XSB file format
std::string ConvertMapToXSB(int TileID, int Type);
/// Get an specific information inside of map file (Title, Author, etc)
std::string GetMapInfo(const string& File, const string& Key);
/// Format Time String (used in game time)
std::string FormatTime(int H, int M, int S);
/// Adding zeros to Integer Numbers and convert to String
std::string FormatNumber(int Level);
/// Convert an String to Lowercase
std::string StringToLowerCase(std::string strInput);
/// Convert an Integer value into String
std::string IntToString(int Value);
/// Return Actual System Date
std::string GetSystemDate();
/// Return an string with SDL version used to build this application
std::string GetSDLVersionCompile();
/// Setting the video mode at anytime
bool SetVideoMode(int Width, int Height, int Bpp, SDL_Surface* Surface);
/// Toggle Fullscreen mode
void ToggleFullScreen(SDL_Surface* Surface);

#endif	/* CGLOBALS_H */