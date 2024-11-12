/*
author : ���Ѻ�
description : ������ ���Ǹ� �ϱ� ���� ���� ��� ����

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include "pch.h"
#include "FmodSystem.h"

namespace HBSoft
{
    class HSound
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
        bool CreateSound(const wstringV filePath);

    public:
        HSound(const wstringV filePath);
        ~HSound();

        bool IsPlaying() const;
        bool Play(bool _loop = false);
        void Stop();
        void Paused();
        void VolumeUp(float volume);
        void VolumneDown(float _volume);

        void Update();

        void InitSound();
    };
}  // namespace HBSoft