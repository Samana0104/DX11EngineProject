/*
author : ���Ѻ�
description : ���带 ���� �� FmodSystem�� �����ϴ� �������

version: 1.0.0
date: 2024-11-17
*/

#pragma once

#include "pch.h"
#include "Sound/HSound.h"

namespace HBSoft
{
    class SoundFactory
    {
    private:
        inline static const int MAX_CHANNELS = 16;
        inline static FMOD_SYS* m_fmodSys    = nullptr;

    private:
        static void InitFmodSystem();  // fmod system ������

    public:
        static std::shared_ptr<HSound> Create(wstringV path);

        static bool IsSoundFormat(const wstringV ext);
        static void ReleaseFmodSystem();
    };
}  // namespace HBSoft
