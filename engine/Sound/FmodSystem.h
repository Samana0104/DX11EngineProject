#pragma once
#include "CoreAPI.h"

/*
    FMOD SYSTEM SMART POINTER
*/

namespace HBSoft
{
    using FMOD_SYS = FMOD::System;

    class FmodSystem
    {
    private:
        inline static const int MAX_CHANNELS = 32;

        inline static UINT      mRefSysCount = 0;
        inline static FMOD_SYS* mFmodSys     = nullptr;

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
