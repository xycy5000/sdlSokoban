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
#include "cTime.h"

cTime::cTime()
{
    tim_StartTicks  = 0;
    tim_PausedTicks = 0;
    tim_Paused      = false;
    tim_Started     = false;
}

cTime::~cTime()
{
}

void cTime::Start()
{
    tim_Started    = true;
    tim_Paused     = false;
    tim_StartTicks = SDL_GetTicks();
}

void cTime::Stop()
{
    tim_Started = false;
    tim_Paused  = false;
}

void cTime::Pause()
{
    if ((tim_Started == true) && (tim_Paused == false))
    {
        tim_Paused      = true;
        tim_PausedTicks = SDL_GetTicks()-tim_StartTicks;
    }
}

void cTime::UnPause()
{
    if (tim_Paused == true)
    {
        tim_Paused      = false;
        tim_StartTicks  = SDL_GetTicks() - tim_PausedTicks;
        tim_PausedTicks = 0;
    }
}

int cTime::GetTicks()
{
    if (tim_Started == true)
    {
        if (tim_Paused == true)
        {
            return tim_PausedTicks;
        } else {
            return SDL_GetTicks() - tim_StartTicks;
        }
    }
    return 0;
}

bool cTime::IsStarted()
{
    return tim_Started;
}

bool cTime::IsPaused()
{
    return tim_Paused;
}

void cTime::Reset()
{
    tim_StartTicks = SDL_GetTicks();
}