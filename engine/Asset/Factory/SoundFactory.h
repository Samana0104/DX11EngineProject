/*
author : 변한빛
description : 사운드를 생성 및 FmodSystem를 관리하는 헤더파일

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
        static void InitFmodSystem();  // fmod system 관리용

    public:
        static std::shared_ptr<HSound> Create(wstringV path);

        static bool IsSoundFormat(const wstringV ext);
        static void ReleaseFmodSystem();
    };
}  // namespace HBSoft
