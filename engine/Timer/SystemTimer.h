#pragma once

namespace HBSoft
{
    using namespace std::chrono;

    class SystemTimer
    {
    private:
        time_point<steady_clock> m_startTimeTick;
        time_point<steady_clock> m_currentTimeTick;
        duration<double>         m_frameDuration;
        duration<double>         m_elapsedTime;
        duration<double>         m_secondPerFrame;

        double m_oneSecond;
        double m_deltaTime;

        int m_fps;

    public:
        std::wstring m_csBuffer;

    public:
        SystemTimer();

        float GetDeltaTime() const;
        float GetElapsedTime() const;

        void Update();
        void Reset();
        void Start();
    };
}  // namespace HBSoft
