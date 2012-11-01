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
#ifndef CDEFINES_H
    #define CDEFINES_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime> 
#include <stdio.h>
#include <sys/stat.h>

#ifdef WIN32
    #include <windows.h>
#endif

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <fmod/fmod.h>
#include <fmod/fmod_errors.h>

using namespace std;

#define uint unsigned int

/// Font Class Defines
#define FONT_HORIZONTAL         1
#define FONT_VERTICAL           2
#define FONT_DEFAULT            3
#define FONT_SQUARE             4

/// Font Names
#define FONT_FAST               0
#define FONT_KROMASKY           1
#define FONT_BRINGER            2
#define FONT_GEEBEE             3
#define FONT_BLAZING            4

/// Cursor Constants
#define CURSOR_ARROW            0
#define CURSOR_LINK             1
#define CURSOR_PAINT            2

/// MAP Game Constants
#define MAP_FILE_MAP            0
#define MAP_FILE_XSB            1

/// MAP Tile Types
#define TILE_NONE              -1
#define TILE_PLAYER             0
#define TILE_PLAYER_ON_GOAL     1
#define TILE_WALL               2
#define TILE_GOAL               3
#define TILE_BOX                4
#define TILE_BOX_ON_GOAL        5
#define TILE_FLOOR              6
/// MAP draw types
#define TILE_ID_EMPTY           0
#define TILE_ID_DRAW            1
#define TILE_ID_HOME            3

/// Supported screen resolutions
#define SCR_800                 0
#define SCR_1024                1
#define SCR_1152                2
#define SCR_1280                3
#define SCR_1366                4
#define SCR_1440                5
#define SCR_1600                6
#define SCR_1680                7
#define SCR_1920                8

/// Main States
#define STATE_MENU              0
#define STATE_GAME              1
#define STATE_MAP_EDITOR        2
#define STATE_OPTIONS           3
#define STATE_CREDITS           4
#define STATE_QUIT              5

/// Editor State
#define MAP_EDIT_RENDER         0
#define MAP_EDIT_SAVEFILE       1
#define MAP_EDIT_LOADFILE       2
#define MAP_EDIT_OVERWRITE      3

/// Game State
#define GAME_BROWSE_MAP         0
#define GAME_RUN_MAP            1
#define GAME_EXIT               2

/// Map State
#define MAP_RUN                 0
#define MAP_HELP                1
#define MAP_WIN                 2
#define MAP_DIMENSIONS          3

/// Menu State
#define MENU_PLAY               1
#define MENU_MAP_EDITOR         2
#define MENU_OPTIONS            3
#define MENU_CREDITS            4
#define MENU_QUIT               5

/// Undo Movements
#define UNDO_UP                 0
#define UNDO_DOWN               1
#define UNDO_LEFT               2
#define UNDO_RIGHT              3

/// Sound Define
#define SOUND_LOOP_OFF          0
#define SOUND_LOOP_ON           1

/// Application version
#define APP_VERSION             0.5.0

#endif	/* CDEFINES_H */