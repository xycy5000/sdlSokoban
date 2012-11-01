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
#include "cApp.h"
#include "cEvent.h"
#include "cDefines.h"

cApp::cApp()
{
    app_Frame       = 0;
    app_Display     = NULL;
    app_Running     = true;
    app_GameInit    = false;
    app_EditorInit  = false;
    app_OptionsInit = false;
    app_CreditsInit = false;
}

cApp::~cApp()
{
}

bool cApp::OnInit()
{
    if (sysInitVideo())
    {
        app_Display = sysGetDisplaySurface();
    }
    else
    {
        return false;
    }
    if (!app_Menu.OnInitMenu(app_Display))
    {
        return false;
    }
    /// Load Sound Bank
    app_Sounds.clear();
    std::string tmpSoundBank[3] = {"./media/astryingvoyages.s3m", "./media/menu_select.wav", "./media/menu_step.wav"};
    for (int k=0; k<3; k++)
    {
        cSound tmpSound;
        if (!tmpSound.OnInitSnd())
        {
            fprintf(stdout, "ERROR: unable to initialize soundbank ..");
            return false;
        }
        if (!tmpSound.OnLoadSnd(tmpSoundBank[k]))
        {
            fprintf(stdout, "ERROR: unable to load sounds ..");
            return false;
        }
        app_Sounds.push_back(tmpSound);
    }
    /// Hide cursor mouse
    SDL_ShowCursor(SDL_DISABLE);
    /// Set window caption
    SDL_WM_SetCaption("sdlSokoban 0.6", 0);
    
    return true;
}

void cApp::OnEvent(SDL_Event* Event)
{
    switch (APP_STATE.appState)
    {
        case STATE_MENU:
        {
            app_Menu.OnEventMenu(Event);
            break;
        }
        case STATE_GAME:
        {
            app_Game.OnEventGame(Event);
            break;
        }
        case STATE_MAP_EDITOR:
        {
            app_Editor.OnEventEdt(Event);
            break;
        }
        case STATE_OPTIONS:
        {
            app_Options.OnEventOpt(Event);
            break;
        }
        case STATE_CREDITS:
        {
            app_Credits.OnEventCred(Event);
            break;
        }
        case STATE_QUIT:
        {
            break;
        }
    }
}

void cApp::OnLoop()
{
    APP_STATE.appState = app_Menu.GetMenuOption();
    
    switch (APP_STATE.appState)
    {
        case STATE_MENU:
        {
            if (!app_Menu.GetMenuExit())
            {
                app_Menu.OnLoopMenu();
            }
            else
            {
                app_Running = false;
            }
            break;
        }
        case STATE_GAME:
        {
            if (!app_GameInit)
            {
                if (!app_Game.OnInitGame(app_Display))
                {
                    fprintf(stdout, "ERROR: unable to initialize game ..");
                    exit(1);
                }
                app_GameInit = true;
            }
            if (!app_Game.GetGameExit())
            {
                app_Game.OnLoopGame();
            }
            else
            {
                app_GameInit       = false;
                APP_STATE.appState = STATE_MENU;
                app_Menu.SetMenuOption(STATE_MENU);
            }
            break;
        }
        case STATE_MAP_EDITOR:
        {
            if (!app_EditorInit)
            {
                if (!app_Editor.OnInitEdt(app_Display))
                {
                    fprintf(stdout, "ERROR: unable to initialize editor ..");
                    exit(1);
                }
                app_EditorInit = true;
            }
            if (!app_Editor.GetEditorExit())
            {
                app_Editor.OnLoopEdt();
            }
            else
            {
                app_EditorInit     = false;
                APP_STATE.appState = STATE_MENU;
                app_Menu.SetMenuOption(STATE_MENU);
            }
            break;
        }
        case STATE_OPTIONS:
        {
            if (!app_OptionsInit)
            {
                if (!app_Options.OnInitOpt(app_Display))
                {
                    fprintf(stdout, "ERROR: unable to initialize credits ..");
                    exit(1);
                }
                else
                {
                    app_OptionsInit = true;
                }
            }
            if (!app_Options.GetOptionsExit())
            {
                app_Options.OnLoopOpt();
            }
            else
            {
                app_OptionsInit    = false;
                APP_STATE.appState = STATE_MENU;
                app_Menu.SetMenuOption(STATE_MENU);
            }
            break;
        }
        case STATE_CREDITS:
        {
            if (!app_CreditsInit)
            {
                if (!app_Credits.OnInitCred(app_Display))
                {
                    fprintf(stdout, "ERROR: unable to initialize credits ..");
                    exit(1);
                }
                else
                {
                    app_CreditsInit = true;
                }
            }
            if (!app_Credits.GetCreditsExit())
            {
                app_Credits.OnLoopCred();
            }
            else
            {
                app_CreditsInit    = false;
                APP_STATE.appState = STATE_MENU;
                app_Menu.SetMenuOption(STATE_MENU);
            }
            break;
        }
        case STATE_QUIT:
        {
            app_Running = false;
            break;
        }
    }
}

void cApp::OnRender()
{
    switch (APP_STATE.appState)
    {
        case STATE_MENU:
        {
            app_Menu.OnRenderMenu();
            break;
        }
        case STATE_GAME:
        {
            app_Game.OnRenderGame();
            break;
        }
        case STATE_MAP_EDITOR:
        {
            app_Editor.OnRenderEdt();
            break;
        }
        case STATE_OPTIONS:
        {
            app_Options.OnRenderOpt();
            break;
        }
        case STATE_CREDITS:
        {
            app_Credits.OnRenderCred();
            break;
        }
        case STATE_QUIT:
        {
            break;
        }
    }
    /// Calculates and display max. FPS
    if (g_ShowFps)
    {
        app_Frame++;
        if (app_FPSUpdate.GetTicks() > 1000)
        {
            app_MaxFPS.clear();
            app_MaxFPS.append("sdlSokoban 0.5 [FPS: ");
            app_MaxFPS.append(IntToString((app_Frame/(app_FPS.GetTicks()/1000.f))));
            app_MaxFPS.append("]");
            app_FPSUpdate.Start();
        }
        SDL_WM_SetCaption(app_MaxFPS.c_str(), 0);
    }

    SDL_Flip(app_Display);
}

void cApp::OnCleanup()
{
    SDL_FreeSurface(app_Display);

    SDL_Quit();
}

void cApp::OnExit()
{
    app_Running = false;
}

int cApp::OnExecute()
{
    if (OnInit() == false)
    {
        fprintf(stderr, "ERROR: %s\n", SDL_GetError());
        return -1;
    }
    if (g_ShowFps)
    {
        app_FPS.Start();
        app_FPSUpdate.Start();
    }
    while (app_Running)
    {
        while (SDL_PollEvent(&app_Event))
        {
            OnEvent(&app_Event);
        }
        OnLoop();
        OnRender();
    }
    OnCleanup();
    
    return 0;
}