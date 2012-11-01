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
#ifndef CSOUND_H
    #define CSOUND_H

#include "cDefines.h"

using namespace std;

class cSound {
    private:
        /// Main class variables
        unsigned int snd_Version;
        unsigned int snd_Position;
        unsigned int snd_Length;
        FMOD_BOOL    snd_IsPlaying;
        FMOD_BOOL    snd_IsPaused;
        std::string  snd_currentSound;
        
        /// Sound type flag
        int snd_FlagLoopSound;
        
        /// FMOD-specific stuff
        FMOD_RESULT snd_Result;
        FMOD_SYSTEM* snd_fmodSystem;
        FMOD_SOUND* snd_Sound;
        FMOD_CHANNEL * snd_Channel;
        
    public:
        cSound();
        virtual ~cSound();
        /// Initializes fmod Sound Engine
        bool OnInitSnd();
        /// Load a Soundfile
        bool OnLoadSnd(std::string File, int LoopType = SOUND_LOOP_OFF);
        /// Play Sound Stream
        bool PlaySnd();
        /// Update fmod Sound System
        void UpdateSoundSystem();
        /// Pause/Unpause the Sound
        bool setPauseResumeSnd();
        /// Return Play Song Status
        bool IsPlayingSnd();
        /// Return Paused Song Status
        bool IsPausedSnd();
        /// Return Actual Position on Stream
        int GetPositionSnd();
        /// Return Length of Sound
        int GetLengthSnd();
        /// Sets the Actual Playing Sound's Volume
        void setVolume(float Volume);
        /// Unloads a Soundfile (Frees the Sound Object)
        void UnloadSnd();
        /// Shutdown fmod Sound System
        void ShutDownSoundSystem();
        /// Get Paused Status
};
#endif	/* CSOUND_H */