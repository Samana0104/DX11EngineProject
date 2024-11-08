/*
author : 변한빛
description : Fmod 시스템을 스마트 포인터화 시키기 위해 만든 헤더 파일

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include "pch.h"

namespace HBSoft
{
    using FMOD_SYS = FMOD::System;

    class FmodSystem
    {
    private:
        inline static const int MAX_CHANNELS = 32;

        inline static UINT      m_refSysCount = 0;
        inline static FMOD_SYS* m_fmodSys     = nullptr;

    private:
        bool CreateFmodSystem();
        void DeleteFmodSystem();

        FmodSystem(const FmodSystem&)            = delete;
        FmodSystem(FmodSystem&&)                 = delete;
        FmodSystem& operator=(FmodSystem&&)      = delete;
        FmodSystem& operator=(const FmodSystem&) = delete;

    public:
        FmodSystem();
        ~FmodSystem();

        UINT            GetRefCount() const;
        FMOD_SYS* const operator->();
    };
}  // namespace HBSoft
