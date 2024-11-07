/*
author : ���Ѻ�
description : Fmod �ý����� ����Ʈ ������ȭ ��Ű�� ���� ���� ��� ����

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
