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
#include "cEvent.h"
#include "cDefines.h"
 
cEvent::cEvent()
{
}
 
cEvent::~cEvent()
{
}

void cEvent::OnEvent(SDL_Event* Event)
{
    switch (Event->type)
    {
        case SDL_KEYDOWN:
        {
            OnKeyDown(Event->key.keysym.sym, Event->key.keysym.mod, Event->key.keysym.unicode);
            break;
        }
        case SDL_KEYUP:
        {
            OnKeyUp(Event->key.keysym.sym, Event->key.keysym.mod, Event->key.keysym.unicode);
            break;
        }
        case SDL_QUIT:
        {
            OnExit();
            break;
        }
    }
}

void cEvent::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    switch (sym)
    {
        case SDLK_ESCAPE:
        {
            OnExit();
            break;
        }
        case SDLK_RETURN:
        {
            if ((SDLK_RETURN) && ((mod & KMOD_ALT)))
            {
                sysToggleFullScreen();
            }
            break;
        }
    }
}
 
void cEvent::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
}
 
void cEvent::OnExit()
{
}

void cEvent::OnKeyPress(Uint16 Key)
{
}

void cEvent::sysToggleFullScreen()
{
}