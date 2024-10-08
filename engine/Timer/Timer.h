#pragma once
#include "CoreAPI.h"

namespace HBSoft
{
    using namespace std::chrono;

    class Timer
    {
    protected:
        time_point<steady_clock> m_startTimeTick;
        time_point<steady_clock> m_currentTimeTick;
        duration<double>         m_frameDuration;
        duration<double>         m_elapsedTime;
        duration<double>         m_secondPerFrame;

    public:
        float GetElapsedTime() const;

        virtual float GetDeltaTime() const;
        virtual void  Reset();
        virtual void  Start();
        void          Update();
    };
}  // namespace HBSoft