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
#ifndef CFONT_H
    #define CFONT_H

#include "cSurface.h"
#include "cDefines.h"

using namespace std;

class cFont: public cSurface {

private:
    SDL_Surface* fnt_FontSurface;
    
private:
    SDL_Rect fnt_RectSource;
    SDL_Rect fnt_RectTarget;

private:
    int fnt_FirstChar;
    int fnt_LastChar;
    int fnt_Lines;
    int fnt_Cols;
    int fnt_Direction;
    int fnt_R;
    int fnt_G;
    int fnt_B;
    int fnt_PixelSpace;
    int fnt_Width;
    int fnt_Height;
    
    bool fnt_IsFontSquare;
    
public:
    cFont();
    virtual ~cFont();
    
    bool OnLoadDefaults(std::string File);
    bool OnLoad(std::string File, int First, int Last, int Witdh, int Height, int Direction = FONT_HORIZONTAL);
    bool OnLoadSquare(std::string File, int First, int Lines, int Cols, int Witdh, int Height);
    
    void SetPixelSpace(int PixelSpace);
    void SetRGB(int R, int G, int B);
    void SetFillArea(SDL_Surface* Display, int X, int Y, int W, int H, int R = 0, int G = 0, int B = 0);
    void SetFontParameters(int First, int Last, int Witdh, int Height, int Direction = FONT_HORIZONTAL);
    void SetFontSquareParameters(int First, int NumLin, int NumCol, int Witdh, int Height);

    void DrawChar(char Character, SDL_Surface* Display, int FontType = FONT_DEFAULT);
    void DrawChar(char Character, int _xpos, int _ypos, SDL_Surface* Display, int FontType = FONT_DEFAULT);
    
    void DrawTextString(std::string Text, SDL_Surface* Display, int FontType = FONT_DEFAULT);
    void DrawTextString(std::string Text, int _ypos, bool Center, SDL_Surface* Display, int FontType = FONT_DEFAULT);
    void DrawTextString(std::string Text, int _xpos, int _ypos, SDL_Surface* Display, int FontType = FONT_DEFAULT);
    
    int  GetFontWidth();
    int  GetFontHeight();
    bool IsFontSquare();
    
    void ClearFontArea(SDL_Surface* Display, int X, int Y, int W, int H, int R = 255, int G = 255, int B = 255);
};
#endif
/* CFONT_H */