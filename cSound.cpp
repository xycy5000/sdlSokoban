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
#include "cSound.h"

cSound::cSound()
{
    snd_Position  = 0;
    snd_Length    = 0;
    snd_IsPlaying = 0;
    snd_IsPaused  = 0;
    snd_Version   = FMOD_VERSION;
}

cSound::~cSound()
{
}

/// Initializes fmod Sound Engine
bool cSound::OnInitSnd()
{
    bool b_Return = true;
    
    snd_Result = FMOD_System_Create(&snd_fmodSystem);
    if (snd_Result != FMOD_OK)
    {
        b_Return = false;
    }
    
    snd_Result = FMOD_System_GetVersion(snd_fmodSystem, &snd_Version);
    if (snd_Version < FMOD_VERSION)
    {
        printf("Error! You are using an old version of FMOD %08x. This program requires %08x\n", snd_Version, FMOD_VERSION);
        return false;
    }
    
    snd_Result = FMOD_System_Init(snd_fmodSystem, 1, FMOD_INIT_NORMAL, NULL);
    if (snd_Result != FMOD_OK)
    {
        b_Return = false;
    }
    
    return b_Return;
}

/// Load a Soundfile
bool cSound::OnLoadSnd(std::string File, int LoopType)
{
    bool b_Return = true;
    
    snd_currentSound  = File;
    snd_FlagLoopSound = LoopType;
    
    switch (LoopType)
    {
        case SOUND_LOOP_OFF:
        {
            snd_Result = FMOD_System_CreateStream(snd_fmodSystem, snd_currentSound.c_str(), FMOD_HARDWARE|FMOD_LOOP_OFF|FMOD_2D, 0, &snd_Sound);
            break;
        }
        case SOUND_LOOP_ON:
        {
            snd_Result = FMOD_System_CreateStream(snd_fmodSystem, snd_currentSound.c_str(), FMOD_HARDWARE|FMOD_LOOP_NORMAL|FMOD_2D, 0, &snd_Sound);
            break;
        }
    }
    if (snd_Result != FMOD_OK)
    {
        b_Return = false;
    }
    
    return b_Return;
}

/// Play Sound Stream
bool cSound::PlaySnd()
{
    bool b_Return = true;
    
    if (snd_IsPlaying == 0)
    {
        snd_Result = FMOD_System_PlaySound(snd_fmodSystem, FMOD_CHANNEL_FREE, snd_Sound, 0, &snd_Channel);
        if (snd_Result != FMOD_OK)
        {
            b_Return = false;
        }
        else
        {
            if (snd_FlagLoopSound == SOUND_LOOP_ON)
            {
                snd_IsPlaying = 1;
            }
        }
    }
    else
    {
        b_Return = false;
    }
    
    return b_Return;
}

/// Pause/Unpause the Sound
bool cSound::setPauseResumeSnd()
{
    bool b_Return = true;
    
    FMOD_Channel_SetPaused(snd_Channel, !IsPausedSnd());
    
    return b_Return;
}

/// Return Play Song Status
bool cSound::IsPlayingSnd()
{
    snd_Result = FMOD_Channel_IsPlaying(snd_Channel, &snd_IsPlaying);
    if (snd_Result != FMOD_OK)
    {
        snd_IsPlaying = 0;
    }
    
    return snd_IsPlaying;
}

/// Return Paused Song Status
bool cSound::IsPausedSnd()
{
    snd_Result = FMOD_Channel_GetPaused(snd_Channel, &snd_IsPaused);
    if ((snd_Result != FMOD_OK) && (snd_Result != FMOD_ERR_INVALID_HANDLE) && (snd_Result != FMOD_ERR_CHANNEL_STOLEN))
    {
        if (snd_Result != FMOD_OK)
        {
            snd_IsPaused = 0;
        }
    }
    
    return snd_IsPaused;
}

/// Return Actual Position on Stream
int cSound::GetPositionSnd()
{
    snd_Result = FMOD_Channel_GetPosition(snd_Channel, &snd_Position, FMOD_TIMEUNIT_MS);
    if ((snd_Result != FMOD_OK) && (snd_Result != FMOD_ERR_INVALID_HANDLE) && (snd_Result != FMOD_ERR_CHANNEL_STOLEN))
    {
        if (snd_Result != FMOD_OK)
        {
            snd_Position = 0;
        }
    }
    
    return snd_Position;
}

/// Return Length of Sound
int cSound::GetLengthSnd()
{
    snd_Result = FMOD_Sound_GetLength(snd_Sound, &snd_Length, FMOD_TIMEUNIT_MS);
    if ((snd_Result != FMOD_OK) && (snd_Result != FMOD_ERR_INVALID_HANDLE) && (snd_Result != FMOD_ERR_CHANNEL_STOLEN))
    {
        if (snd_Result != FMOD_OK)
        {
            snd_Length = 0;
        }
    }
    
    return snd_Length;
}

/// Sets the Actual Playing Sound's Volume
void cSound::setVolume(float Volume)
{
    if (snd_IsPlaying && Volume >= 0.0f && Volume <= 1.0f)
    {
        FMOD_Channel_SetVolume(snd_Channel, Volume);
    }
}

/// Update fmod Sound System
void cSound::UpdateSoundSystem()
{
    FMOD_System_Update(snd_fmodSystem);
}

/// Unloads a Soundfile (Frees the Sound Object)
void cSound::UnloadSnd()
{
    snd_Result = FMOD_Sound_Release(snd_Sound);
    if (snd_Result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", snd_Result, FMOD_ErrorString(snd_Result));
        exit(-1);
    }
}

/// Shutdown fmod Sound System
void cSound::ShutDownSoundSystem()
{
    snd_Result = FMOD_System_Close(snd_fmodSystem);
    if (snd_Result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", snd_Result, FMOD_ErrorString(snd_Result));
        exit(-1);
    }
    snd_Result = FMOD_System_Release(snd_fmodSystem);
    if (snd_Result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", snd_Result, FMOD_ErrorString(snd_Result));
        exit(-1);
    }
}