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
#include <ctime>
#include <cstdlib>
#include <string>
#include <algorithm>

#include "cGlobals.h"

/// Screen Dimensions
int  g_ScreenW;
int  g_ScreenH;
/// Screen Flags (internal)
Uint32 g_Flags;
/// Screen Bits Per Pixel
int  g_Bpp;
/// Toggle Fullscreen Mode (True=On, False=Off)
bool g_FullScreen;
/// Sound flag
bool g_PlaySound;
/// Music flag
bool g_PlayMusic;
/// Show fps counter
bool g_ShowFps;
/// Tile Dimensions
int  g_TileW;
int  g_TileH;
/// Language File Total Strings
int  g_LangTotal;
/// Tileset Information
string g_TileSurface;
string g_MainSurface;
/// Language File Type
string g_LangType;
/// Language File Object
cLang g_LangStrings;
/// Editor Level File Information
string g_Title;
string g_Author;
string g_Collection;
string g_AuthorMail;
string g_AuthorPage;
string g_Level;
string g_Date;
string g_Comment;
/// Path of puzzles (maps)
string g_XsbPath;

/*!
 * Find an specific string in another string.
 * 
 * @param[out] true if strfind found at strtarget, false otherwise.
 * @param[in] strtarget String to parse.
 * @param[in] strfind String sequence to find in strtarget
*/
bool FindString(const string& strtarget, const string& strfind)
{
    size_t found;
    
    found = strtarget.find(strfind);
    if (found != string::npos)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*!
 * Verify if file already exists.
 * 
 * @param[out] true if strfind found at strtarget, false otherwise.
 * @param[in] filename Name of file to check if exists.
*/
bool FileExists(const string& filename)
{
    struct stat info;
    int ret = -1;

    //get the file attributes
    ret = stat(filename.c_str(), &info);
    if (ret == 0) 
    {
        //stat() is able to get the file attributes,
        //so the file obviously exists
        return true;
    } 
    else 
    {
        //stat() is not able to get the file attributes,
        //so the file obviously does not exist or
        //more capabilities is required
        return false;
    }
}

std::string FormatTime(int H, int M, int S)
{
    std::stringstream tmpTimeH;
    std::stringstream tmpTimeM;
    std::stringstream tmpTimeS;
    
    std::string tmpTimeT;
    
    if (H < 10)
    {
        tmpTimeH << "0" << H << ":";
    } else {
        tmpTimeH << H << ":";
    }
    if (M < 10)
    {
        tmpTimeM << "0" << M << ":";
    } else {
        tmpTimeM << M << ":";
    }
    if (S < 10)
    {
        tmpTimeS << "0" << S;
    } else {
        tmpTimeS << S;
    }
    tmpTimeT.append(tmpTimeH.str());
    tmpTimeT.append(tmpTimeM.str());
    tmpTimeT.append(tmpTimeS.str());
    
    return tmpTimeT;
}

std::string FormatNumber(int Level)
{
    std::stringstream tmpLevel;
    std::string       tmpLevelReturn;
    
    if (Level < 10)
    {
        tmpLevel << "00" << Level;
    }
    else if (Level < 100)
    {
        tmpLevel << "0" << Level;
    }
    else if (Level < 1000)
    {
        tmpLevel << Level;
    }
    tmpLevelReturn.append(tmpLevel.str());
    
    return tmpLevelReturn;
}

/*!
 * Get an specific information inside of map file.
 * 
 * @param[out] string with information ready.
 * @param[in] File Name of file to parse.
 * @param[in] Key Key to find and return in map file.
*/
std::string GetMapInfo(const string& File, const string& Key)
{
    std::string tmpString;
    
    ifstream inFile(File.c_str());
    if (inFile.fail())
    {
        tmpString = "Unable to open file for reading.";
        return tmpString;
    }
    while (!inFile.eof())
    {
        std::getline(inFile, tmpString);
        if (FindString(tmpString, Key.c_str()))
        {
            return tmpString;
        }
        tmpString.clear();
    }
}

int GetMapLines(const string& File, int Type)
{
    std::string tmpString = "";
    int totLines = 0;
    
    ifstream tmpHandle(File.c_str());
    if (!tmpHandle)
    {
        return -1;
    }
    while (!tmpHandle.eof())
    {
        size_t found;
        std::getline(tmpHandle, tmpString);
        switch (Type)
        {
            case MAP_FILE_MAP:
            {
                found = tmpString.find_first_of(":");
                break;
            }
            case MAP_FILE_XSB:
            {
                found = tmpString.find_first_of("#");
                break;
            }
        }
        if (found != string::npos)
        {
            totLines++;
        }
        tmpString.clear();
    }
    
    return totLines;
}

int GetMapColumns(const string& File, int Type)
{
    std::string tmpString = "";
    int totCols = 0;
    int tmpCols = 0;
    
    ifstream tmpHandle(File.c_str());
    
    if (!tmpHandle)
    {
        return -1;
    }
    while (!tmpHandle.eof())
    {
        size_t found;
        std::getline(tmpHandle, tmpString);
        switch (Type)
        {
            case MAP_FILE_MAP:
            {
                for (int i=0; i<tmpString.size(); i++)
                {
                    if (tmpString[i] == ':')
                    {
                        tmpCols++;
                    }
                }
                if (totCols < tmpCols)
                {
                    totCols = tmpCols;
                }
                tmpCols = 0;
                break;
            }
            case MAP_FILE_XSB:
            {
                found = tmpString.find_first_of("#");
                if (found != string::npos)
                {
                    tmpCols = tmpString.size();
                    if (totCols < tmpCols)
                    {
                        totCols = tmpCols;
                    }
                    tmpCols = 0;
                }
                break;
            }
        }
        tmpString.clear();
    }
    
    return totCols;
}

int GetMapType(std::string File)
{
    std::string tmpMapName;
    
    for (int i=File.length()-3; i<File.length(); i++)
    {
        tmpMapName = tmpMapName + File[i];
    }
    if (StringToLowerCase(tmpMapName) == "map")
    {
        return MAP_FILE_MAP;
    }
    else
    {
        return MAP_FILE_XSB;
    }
}

std::string StringToLowerCase(std::string strInput)
{
    std::string tmpStringOut;
    
    std::transform(strInput.begin(), strInput.end(), strInput.begin(), ::tolower);
    tmpStringOut = strInput;
    
    return tmpStringOut;
}

std::string IntToString(int Value)
{
    std::stringstream tmp_InfoString;
    
    tmp_InfoString << Value;
    
    return tmp_InfoString.str();
}

int GetRandomInt(int Lowest, int Highest)
{
    int tmpRandomInt;
    int tmpRange = (Highest-Lowest)+1;
    
    tmpRandomInt = Lowest+int(tmpRange*rand()/(RAND_MAX+1.0));
    
    return tmpRandomInt;
}

void ConvertXSBToMap(std::string File, int NumCols)
{
    std::string tmpMapName;
    
    std::string tmpLineIn;
    std::string tmpLineOut;
    
    ifstream pFileIn;
    ofstream pFileOut;
    
    /// Temporary map name
    tmpMapName.append(g_XsbPath);
    tmpMapName.append("tempmap.tmp");
    /// Read/Write operations
    pFileIn.open(File.c_str());
    pFileOut.open(tmpMapName.c_str());
    
    while (!pFileIn.eof())
    {
        std::getline(pFileIn, tmpLineIn);
        if (ValidateMapLine(tmpLineIn))
        {
            for (int i=0; i<tmpLineIn.size(); i++)
            {
                switch (tmpLineIn[i])
                {
                    case '@':
                    {
                        tmpLineOut = tmpLineOut + "1:0 ";
                        break;
                    }
                    case '+':
                    {
                        tmpLineOut = tmpLineOut + "1:1 ";
                        break;
                    }
                    case '#':
                    {
                        tmpLineOut = tmpLineOut + "1:2 ";
                        break;
                    }
                    case '.':
                    {
                        tmpLineOut = tmpLineOut + "1:3 ";
                        break;
                    }
                    case '$':
                    {
                        tmpLineOut = tmpLineOut + "1:4 ";
                        break;
                    }
                    case '*':
                    {
                        tmpLineOut = tmpLineOut + "1:5 ";
                        break;
                    }
                    case ' ':
                    {
                        tmpLineOut = tmpLineOut + "1:6 ";
                        break;
                    }
                }
            }
            for (int i=(tmpLineOut.length()/4); i<NumCols; i++)
            {
                tmpLineOut.append("0:0");
                tmpLineOut.append(" ");
            }
            if (pFileOut.is_open())
            {
                pFileOut << tmpLineOut << endl;
            }
            tmpLineOut = "";
        }
    }
    pFileIn.close();
    pFileOut.close();
}

std::string ConvertMapToXSB(int TileID, int Type)
{
    std::string tmpStringOut;
    
    if (TileID == 1)
    {
        switch (Type)
        {
            case TILE_PLAYER:
            {
                tmpStringOut = "@";
                break;
            }
            case TILE_PLAYER_ON_GOAL:
            {
                tmpStringOut = "+";
                break;
            }
            case TILE_WALL:
            {
                tmpStringOut = "#";
                break;
            }
            case TILE_GOAL:
            {
                tmpStringOut = ".";
                break;
            }
            case TILE_BOX:
            {
                tmpStringOut = "$";
                break;
            }
            case TILE_BOX_ON_GOAL:
            {
                tmpStringOut = "*";
                break;
            }
            case TILE_FLOOR:
            {
                tmpStringOut = " ";
                break;
            }
        }
    }
    
    return tmpStringOut;
}

/// Verifica se a string passada possui caracteres diferentes do padrão
/// esperado para um mapa do tipo .XSB (i.e. verifica se a string contém letras)
bool ValidateMapLine(std::string Text)
{
    int  tmpFlag   = 0;
    bool tmpReturn = false;
    
    if (Text.length() == 0)
    {
        return tmpReturn;
    }
    for (int k=0; k<Text.length(); k++)
    {
        if (isalpha(Text[k]))
        {
            tmpFlag++;
        }
    }
    if (tmpFlag > 0)
    {
        tmpReturn = false;
    }
    else
    {
        tmpReturn = true;
    }
    
    return tmpReturn;
}

std::string GetSystemDate()
{
    std::stringstream tmpStringInt;
    std::string       tmpStringDate;
    
    time_t t = time(0);      // Get time now
    struct tm * now = localtime(&t);
    
    tmpStringInt << (now->tm_year+1900) << "-" << (now->tm_mon+1) << "-" << (now->tm_mday) << endl;
    tmpStringDate.append(tmpStringInt.str());
    
    return tmpStringDate;
}

std::string GetSDLVersionCompile()
{
    std::string tmpSDLVersion;
    
    SDL_version compiled;
    SDL_VERSION(&compiled);
    
    tmpSDLVersion.append("SDL ");
    tmpSDLVersion.append(IntToString(compiled.major));
    tmpSDLVersion.append(".");
    tmpSDLVersion.append(IntToString(compiled.minor));
    tmpSDLVersion.append(".");
    tmpSDLVersion.append(IntToString(compiled.patch));
    
    return tmpSDLVersion;
}

bool SetVideoMode(int Width, int Height, int Bpp, SDL_Surface* Surface)
{
    bool tmpReturn = true;
    
    if ((Surface = SDL_SetVideoMode(Width, Height, Bpp, g_Flags)) == NULL)
    {
        tmpReturn = false;
    }
    
    return tmpReturn;
}

void ToggleFullScreen(SDL_Surface* Surface)
{
    g_FullScreen = !g_FullScreen;
    
    if (Surface != NULL)
    {
        if (!g_FullScreen)
        {
            Surface = SDL_SetVideoMode(g_ScreenW, g_ScreenH, g_Bpp, g_Flags|SDL_FULLSCREEN);
        }
        else
        {
            Surface = SDL_SetVideoMode(g_ScreenW, g_ScreenH, g_Bpp, g_Flags);
        }
    }
}