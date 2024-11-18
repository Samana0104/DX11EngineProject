#pragma once

#include "pch.h"
#include "Sound/HSound.h"

namespace HBSoft
{
    class SoundFactory
    {
    private:
        inline static const int MAX_CHANNELS = 32;
        inline static FMOD_SYS* m_fmodSys    = nullptr;

    private:
        static void InitFmodSystem();  // fmod system °ü¸®¿ë

    public:
        static std::shared_ptr<HSound> Create(wstringV path);

        static bool IsSoundFormat(const wstringV ext);
        static void ReleaseFmodSystem();
    };
}  // namespace HBSoft
