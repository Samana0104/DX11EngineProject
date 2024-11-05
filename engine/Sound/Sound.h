/*
author : 변한빛
description : 사운드의 정의를 하기 위해 만든 헤더 파일

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include "pch.h"
#include "FmodSystem.h"

namespace HBSoft
{
    class Sound
    {
    private:
        FmodSystem     m_fmodSys;
        FMOD::Sound*   m_sound;
        FMOD::Channel* m_soundChannel;

        std::wstring m_soundPath;
        float        m_soundVolume;

        // wchar_t			m_soundTimer[MAX_PATH];
        // unsigned int	m_soundSizeInMS;

    private:
        bool CreateSound(const wstringV _filePath);

    public:
        Sound(const wstringV _filePath);
        ~Sound();

        bool IsPlaying() const;
        bool Play(bool _loop = false);
        void Stop();
        void Paused();
        void VolumeUp(float _volume);
        void VolumneDown(float _volume);

        void Update();

        void InitSound();
    };
}  // namespace HBSoft