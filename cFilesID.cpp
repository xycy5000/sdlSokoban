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
#include "cFilesID.h"

cFilesID::cFilesID()
{
    fid_FileID       = 0;
    fid_FileName     = "";
    fid_MapName      = 0;
    fid_MapAutor     = 0;
    fid_MapDate      = 0;
    fid_MapDificulty = 0;
    fid_MapLines     = 0;
    fid_MapCols      = 0;
}

cFilesID::~cFilesID()
{
}

cUndo::cUndo()
{
    /// Player Position
    und_PlayerX  = 0;
    und_PlayerY  = 0;
    /// Box Position
    und_BoxX     = 0;
    und_BoxY     = 0;
    und_BoxID    = 0;
    und_BoxType  = 0;
    und_BoxHome  = 0;
    /// Box Position (before)
    und_BoxXb    = 0;
    und_BoxYb    = 0;
    und_BoxIDb   = 0;
    und_BoxTypeb = 0;
    und_BoxHomeb = 0;
}

cUndo::~cUndo()
{
}