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
#include "cFont.h"

//
// Default constructor
//
cFont::cFont()
{
    fnt_FontSurface  = NULL;
    fnt_FirstChar    = 0;
    fnt_LastChar     = 0;
    fnt_Lines        = 0;
    fnt_Cols         = 0;
    fnt_Direction    = FONT_HORIZONTAL;
    fnt_PixelSpace   = 0;
    fnt_R            = 0;
    fnt_G            = 0;
    fnt_B            = 0;
    fnt_Width        = 0;
    fnt_Height       = 0;
    fnt_IsFontSquare = false;
}

//
// Default destructor
//
cFont::~cFont()
{
}

//
// Load font from a SDL_image file format compatible
//
bool cFont::OnLoadDefaults(std::string File)
{
    if ((fnt_FontSurface = cSurface::OnLoad(File.c_str())) == NULL)
    {
        fprintf(stderr, "ERROR: %s\n", SDL_GetError());
        return false;
    }
    fnt_FirstChar    = 33;
    fnt_LastChar     = 130;
    fnt_Width        = 16;
    fnt_Height       = 16;
    fnt_Direction    = FONT_HORIZONTAL;
    fnt_RectSource.x = 0;
    fnt_RectSource.y = 0;
    fnt_RectSource.w = 16;
    fnt_RectSource.h = 16;
    fnt_RectTarget.x = 0;
    fnt_RectTarget.y = 0;
    fnt_RectTarget.w = 16;
    fnt_RectTarget.h = 16;
    fnt_Lines        = 8;
    fnt_Cols         = 10;
    fnt_IsFontSquare = false;
    
    return true;
}

//
// Load font from a SDL_image file format compatible
//
bool cFont::OnLoad(std::string File, int First, int Last, int Witdh, int Height, int Direction)
{
    if ((fnt_FontSurface = cSurface::OnLoad(File.c_str())) == NULL)
    {
        fprintf(stderr, "ERROR: %s\n", SDL_GetError());
        return false;
    }
    fnt_FirstChar    = First;
    fnt_LastChar     = Last;
    fnt_Direction    = Direction;
    fnt_Width        = Witdh;
    fnt_Height       = Height;
    fnt_RectSource.x = 0;
    fnt_RectSource.y = 0;
    fnt_RectSource.w = Witdh;
    fnt_RectSource.h = Height;
    fnt_RectTarget.x = 0;
    fnt_RectTarget.y = 0;
    fnt_RectTarget.w = Witdh;
    fnt_RectTarget.h = Height;
    fnt_IsFontSquare = false;
    
    return true;
}

//
// Load BMP font from a SDL_image file format compatible (Square type)
//
bool cFont::OnLoadSquare(std::string File, int First, int Lines, int Cols, int Witdh, int Height)
{
    if ((fnt_FontSurface = cSurface::OnLoad(File.c_str())) == NULL)
    {
        fprintf(stderr, "ERROR: %s\n", SDL_GetError());
        return false;
    }
    fnt_FirstChar    = First;
    fnt_Lines        = Lines;
    fnt_Cols         = Cols;
    fnt_Width        = Witdh;
    fnt_Height       = Height;
    fnt_RectSource.x = 0;
    fnt_RectSource.y = 0;
    fnt_RectSource.w = Witdh;
    fnt_RectSource.h = Height;
    fnt_RectTarget.x = 0;
    fnt_RectTarget.y = 0;
    fnt_RectTarget.w = Witdh;
    fnt_RectTarget.h = Height;
    fnt_IsFontSquare = true;
    
    return true;
}

//
// Set transparency
//
void cFont::SetRGB(int R, int G, int B)
{
    fnt_R = R;
    fnt_G = G;
    fnt_B = B;
}

//
// Set font parameters
//
void cFont::SetFontParameters(int First, int Last, int Witdh, int Height, int Direction)
{
    fnt_FirstChar    = First;
    fnt_LastChar     = Last;
    fnt_Direction    = Direction;
    fnt_Width        = Witdh;
    fnt_Height       = Height;
    fnt_RectSource.x = 0;
    fnt_RectSource.y = 0;
    fnt_RectSource.w = Witdh;
    fnt_RectSource.h = Height;
    fnt_RectTarget.x = 0;
    fnt_RectTarget.y = 0;
    fnt_RectTarget.w = Witdh;
    fnt_RectTarget.h = Height;
    fnt_IsFontSquare = false;
}

//
// Set font parameters (square type)
//
void cFont::SetFontSquareParameters(int First, int NumLin, int NumCol, int Witdh, int Height)
{
    fnt_FirstChar    = First;
    fnt_Lines        = NumLin;
    fnt_Cols         = NumCol;
    fnt_Width        = Witdh;
    fnt_Height       = Height;
    fnt_RectSource.x = 0;
    fnt_RectSource.y = 0;
    fnt_RectSource.w = Witdh;
    fnt_RectSource.h = Height;
    fnt_RectTarget.x = 0;
    fnt_RectTarget.y = 0;
    fnt_RectTarget.w = Witdh;
    fnt_RectTarget.h = Height;
    fnt_IsFontSquare = true;
}

//
// Defines space between characters in a text
//
void cFont::SetPixelSpace(int PixelSpace)
{
    if (PixelSpace < 0)
    {
        fnt_PixelSpace = 0;
    } else {
        fnt_PixelSpace = PixelSpace;
    }
}

//
// Clear a surface area with X, Y, W and H dimensions
//
void cFont::SetFillArea(SDL_Surface* Display, int X, int Y, int W, int H, int R, int G, int B)
{
    SDL_Rect srf_Temp;
    
    srf_Temp.x = X;
    srf_Temp.y = Y;
    srf_Temp.w = W;
    srf_Temp.h = H;
    
    SDL_FillRect(Display, &srf_Temp, SDL_MapRGB(fnt_FontSurface->format, R, G, B));
}

//
// Writes a char in a surface
//
void cFont::DrawChar(char Character, SDL_Surface* Display, int FontType)
{
    switch (FontType)
    {
        case FONT_DEFAULT:
        {
            int _k = 0;

            for (int _x = fnt_FirstChar; _x <= fnt_LastChar; _x++)
            {
                if (_x == Character)
                {
                    if (fnt_Direction == FONT_HORIZONTAL)
                    {
                        fnt_RectSource.x = _k*fnt_RectSource.w;
                        fnt_RectSource.y = 0;
                    } else {
                        fnt_RectSource.x = 0;
                        fnt_RectSource.y = _k*fnt_RectSource.h;
                    }
                    //break;
                } else {
                    _k++;
                }
            }
            break;
        }
        case FONT_SQUARE:
        {
            int _z = 0;

            for (int _lin = 0; _lin < fnt_Lines; _lin++)
            {
                for (int _col = 0; _col < fnt_Cols; _col++)
                {
                    if ((_z + fnt_FirstChar) == Character)
                    {
                        fnt_RectSource.x = _col*fnt_RectSource.w;
                        fnt_RectSource.y = _lin*fnt_RectSource.h;
                    }
                    _z++;
                }
            }
            break;
        }
    }
    Transparent(fnt_FontSurface, fnt_R, fnt_G, fnt_B);
    OnDraw(Display, fnt_FontSurface, fnt_RectTarget.x, fnt_RectTarget.y, fnt_RectSource.x, fnt_RectSource.y, fnt_RectSource.w, fnt_RectSource.h);
}

//
// Writes a char in a @param _xpos int
//                    @param _ypos int
// especified of the surface
//
void cFont::DrawChar(char Character, int _xpos, int _ypos, SDL_Surface* Display, int FontType)
{
    switch (FontType)
    {
        case FONT_DEFAULT:
        {
            int _k = 0;
            for (int _x = fnt_FirstChar; _x <= fnt_LastChar; _x++)
            {
                if (_x == Character)
                {
                    if (fnt_Direction == FONT_HORIZONTAL)
                    {
                        fnt_RectSource.x = _k*fnt_RectSource.w;
                        fnt_RectSource.y = 0;
                    //break;
                    } else {
                        fnt_RectSource.x = 0;
                        fnt_RectSource.y = _k*fnt_RectSource.h;
                    }
                } else {
                    _k++;
                }
            }
            fnt_RectTarget.x = _xpos;
            fnt_RectTarget.y = _ypos;
            break;
        }
        case FONT_SQUARE:
        {
            int _z = 0;

            for (int _lin = 0; _lin < fnt_Lines; _lin++)
            {
                for (int _col = 0; _col < fnt_Cols; _col++)
                {
                    if ((_z + fnt_FirstChar) == Character)
                    {
                        fnt_RectSource.x = _col*fnt_RectSource.w;
                        fnt_RectSource.y = _lin*fnt_RectSource.h;
                    }
                    _z++;
                }
            }
            fnt_RectTarget.x = _xpos;
            fnt_RectTarget.y = _ypos;
            break;
        }
    }
    
    Transparent(fnt_FontSurface, fnt_R, fnt_G, fnt_B);
    OnDraw(Display, fnt_FontSurface, fnt_RectTarget.x, fnt_RectTarget.y, fnt_RectSource.x, fnt_RectSource.y, fnt_RectSource.w, fnt_RectSource.h);
}

//
// Writes a text on the surface
//
void cFont::DrawTextString(std::string Text, SDL_Surface* Display, int FontType)
{
    switch (FontType)
    {
        case FONT_DEFAULT:
        {
            int _i = 0;

            fnt_RectTarget.x = 0;
            fnt_RectTarget.y = 0;
            while (Text[_i] != '\0')
            {
                if (Text[_i] == 32)
                {
                    fnt_RectTarget.x += fnt_PixelSpace+(fnt_RectSource.w);
                    _i++;
                } else {
                    this->DrawChar(Text[_i], Display, FontType);
                    fnt_RectTarget.x += fnt_PixelSpace+(fnt_RectSource.w);
                    _i++;
                }
            }
            break;
        }
        case FONT_SQUARE:
        {
            int _i = 0;

            fnt_RectTarget.x = 0;
            fnt_RectTarget.y = 0;
            while (Text[_i] != '\0')
            {
                if (Text[_i] == 32)
                {
                    fnt_RectTarget.x += fnt_PixelSpace+(fnt_RectSource.w);
                    _i++;
                } else {
                    this->DrawChar(Text[_i], Display, FontType);
                    fnt_RectTarget.x += fnt_PixelSpace+(fnt_RectSource.w);
                    _i++;
                }
            }
            break;
        }
    }
}

//
// Writes a text on the surface
//
void cFont::DrawTextString(std::string Text, int _ypos, bool Center, SDL_Surface* Display, int FontType)
{
    switch (FontType)
    {
        case FONT_DEFAULT:
        {
            int _i = 0;

            fnt_RectTarget.x = 0;
            fnt_RectTarget.y = _ypos;
            if (Center) {
                fnt_RectTarget.x = (Display->w-(fnt_PixelSpace*(Text.size())+(Text.size())*fnt_RectSource.w))/2;
            } else {
                fnt_RectTarget.x = 0;
            }
            while (Text[_i] != '\0')
            {
                if (Text[_i] == 32)
                {
                    fnt_RectTarget.x += fnt_PixelSpace+(fnt_RectSource.w);
                    _i++;
                } else {
                    this->DrawChar(Text[_i], fnt_RectTarget.x, fnt_RectTarget.y, Display, FontType);
                    fnt_RectTarget.x += fnt_PixelSpace+(fnt_RectSource.w);
                    _i++;
                }
            }
            break;
        }
        case FONT_SQUARE:
        {
            int _i = 0;

            fnt_RectTarget.x = 0;
            fnt_RectTarget.y = _ypos;
            if (Center)
            {
                fnt_RectTarget.x = (Display->w - ((fnt_PixelSpace*Text.size())+(Text.size()*fnt_RectSource.w)))/2;
            } else {
                fnt_RectTarget.x = 0;
            }
            while (Text[_i] != '\0')
            {
                if (Text[_i] == 32)
                {
                    fnt_RectTarget.x += fnt_PixelSpace+(fnt_RectSource.w);
                    _i++;
                } else {
                    this->DrawChar(Text[_i], fnt_RectTarget.x, fnt_RectTarget.y, Display, FontType);
                    fnt_RectTarget.x += fnt_PixelSpace+(fnt_RectSource.w);
                    _i++;
                }
            }
            break;
        }
    }
    
}

//
// Writes a text on the surface
//
void cFont::DrawTextString(std::string Text, int _xpos, int _ypos, SDL_Surface* Display, int FontType)
{
    switch (FontType)
    {
        case FONT_DEFAULT:
        {
            int _i = 0;

            fnt_RectTarget.x = _xpos;
            fnt_RectTarget.y = _ypos;
            while (Text[_i] != '\0')
            {
                if (Text[_i] == 32)
                {
                    fnt_RectTarget.x += fnt_PixelSpace+(fnt_RectSource.w);
                    _i++;
                } else {
                    this->DrawChar(Text[_i], fnt_RectTarget.x, fnt_RectTarget.y, Display, FontType);
                    fnt_RectTarget.x += fnt_PixelSpace+(fnt_RectSource.w);
                    _i++;
                }
            }
            break;
        }
        case FONT_SQUARE:
        {
            int _i = 0;

            fnt_RectTarget.x = _xpos;
            fnt_RectTarget.y = _ypos;
            while (Text[_i] != '\0')
            {
                if (Text[_i] == 32)
                {
                    fnt_RectTarget.x += fnt_PixelSpace+(fnt_RectSource.w);
                    _i++;
                } else {
                    this->DrawChar(Text[_i], fnt_RectTarget.x, fnt_RectTarget.y, Display, FontType);
                    fnt_RectTarget.x += fnt_PixelSpace+(fnt_RectSource.w);
                    _i++;
                }
            }
            break;
        }
    }
}

int cFont::GetFontWidth()
{
    return fnt_Width;
}

int cFont::GetFontHeight()
{
    return fnt_Height;
}

bool cFont::IsFontSquare()
{
    return fnt_IsFontSquare;
}

void cFont::ClearFontArea(SDL_Surface* Display, int X, int Y, int W, int H, int R, int G, int B)
{
    cSurface::FillArea(Display, fnt_FontSurface, X, Y, W, H, R, G, B);
}