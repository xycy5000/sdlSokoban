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
#ifndef CFILESID_H
    #define CFILESID_H

#include "cDefines.h"

class cFilesID {
    public:
        cFilesID();
        ~cFilesID();
        
        std::string fid_FileName;
        int fid_FileID;
        int fid_MapName;
        int fid_MapAutor;
        int fid_MapDate;
        int fid_MapDificulty;
        int fid_MapLines;
        int fid_MapCols;
};

/// Used to store last movements (undo movement)
class cUndo {
public:
    cUndo();
    ~cUndo();
    /// Player positon
    int und_PlayerX;
    int und_PlayerY;
    /// Box position
    int und_BoxX;
    int und_BoxY;
    int und_BoxID;
    int und_BoxType;
    int und_BoxHome;
    /// Box position (before)
    int und_BoxXb;
    int und_BoxYb;
    int und_BoxIDb;
    int und_BoxTypeb;
    int und_BoxHomeb;
};
#endif	/* CFILESID_H */