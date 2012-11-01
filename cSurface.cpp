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
#include "cSurface.h"

using namespace std;
 
cSurface::cSurface()
{
}

cSurface::~cSurface()
{
}
 
SDL_Surface* cSurface::OnLoad(string File)
{
    SDL_Surface *srf_Temp   = NULL;
    SDL_Surface *srf_Return = NULL;
    
    if ((srf_Temp = IMG_Load(File.c_str())) == NULL)
    {
        return NULL;
    }
    srf_Return = SDL_DisplayFormat(srf_Temp);
    SDL_FreeSurface(srf_Temp);
    
    return srf_Return;
}

SDL_Surface* cSurface::OnLoadResolution(std::string Path, std::string PrefixName, int ScreenW, int ScreenH)
{
    std::string       tmpFileName_a;
    std::string       tmpFileName_b;
    std::stringstream tmpFileStream;
    
    tmpFileStream << ScreenW << "x" << ScreenH << ".png";
    tmpFileName_a = tmpFileStream.str();
    tmpFileName_b.append(Path);
    tmpFileName_b.append(PrefixName);
    tmpFileName_b.append(tmpFileName_a);
    if (!FileExists(tmpFileName_b))
    {
        tmpFileName_b.clear();
        tmpFileName_b.append(Path);
        tmpFileName_b.append(PrefixName);
        tmpFileName_b.append("800x600.png");
    }
    
    SDL_Surface *srf_Temp   = NULL;
    SDL_Surface *srf_Return = NULL;
    
    if ((srf_Temp = IMG_Load(tmpFileName_b.c_str())) == NULL)
    {
        return NULL;
    }
    srf_Return = SDL_DisplayFormat(srf_Temp);
    SDL_FreeSurface(srf_Temp);
    
    return srf_Return;
}

bool cSurface::OnDraw(SDL_Surface* Destination, SDL_Surface* Source, int X, int Y)
{
    if (Destination == NULL || Source == NULL)
    {
        return false;
    }
    SDL_Rect srf_Destination;
    
    srf_Destination.x = X;
    srf_Destination.y = Y;
    
    SDL_BlitSurface(Source, NULL, Destination, &srf_Destination);
    
    return true;
}

bool cSurface::OnDraw(SDL_Surface* Destination, SDL_Surface* Source, int dX, int dY, int sX, int sY, int sW, int sH)
{
    if (Destination == NULL || Source == NULL)
    {
        return false;
    }
    
    SDL_Rect srf_Destination;
    srf_Destination.x = dX;
    srf_Destination.y = dY;
    
    SDL_Rect srf_Source;
    srf_Source.x = sX;
    srf_Source.y = sY;
    srf_Source.w = sW;
    srf_Source.h = sH;
    
    SDL_BlitSurface(Source, &srf_Source, Destination, &srf_Destination);
    
    return true;
}

bool cSurface::Transparent(SDL_Surface* Destination, int R, int G, int B)
{
    if (Destination == NULL)
    {
        return false;
    }
    SDL_SetColorKey(Destination, SDL_SRCCOLORKEY|SDL_RLEACCEL, SDL_MapRGB(Destination->format, R, G, B));
    
    return true;
}

bool cSurface::FillArea(SDL_Surface* Destination, SDL_Surface* Source, int X, int Y, int W, int H, int R, int G, int B)
{
    SDL_Rect srf_Temp;
    
    srf_Temp.x = X;
    srf_Temp.y = Y;
    srf_Temp.w = W;
    srf_Temp.h = H;
    
    SDL_FillRect(Destination, &srf_Temp, SDL_MapRGB(Source->format, R, G, B));
}