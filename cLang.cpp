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
#include "cLang.h"
#include "cGlobals.h"

cLang::cLang()
{
}

cLang::~cLang()
{
}

bool cLang::LoadLanguageFile(std::string File, std::string Language, int TotalLabels)
{
    lng_Label.clear();
    
    char tmpLabelID[20];
    std::string       tmpLabelString;
    
    if (!FileExists(File))
    {
        fprintf(stdout, "ERROR: language file not found ..");
        return false;
    }
    else
    {
        lng_IniLanguage.Load(File.c_str());
    }
    for (int i=1; i<=TotalLabels; i++)
    {
        sprintf(tmpLabelID, "Msg%03d", i);
        tmpLabelString.append(tmpLabelID);
        lng_Label.push_back(lng_IniLanguage.ReadString(Language.c_str(), tmpLabelString.c_str(), "Unknown"));
        tmpLabelString.clear();
    }
    
    return true;
}

std::string cLang::ReadLabel(int MessageID)
{
    return lng_Label[MessageID];
}

int cLang::LenghtLabel(int MessageID)
{
    return lng_Label[MessageID].length();
}