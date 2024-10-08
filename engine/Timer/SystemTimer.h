#pragma once
#include "Timer.h"

namespace HBSoft
{
    class SystemTimer : public Timer
    {
    private:
        double m_oneSecond;
        double m_maxFPSTime;
        double m_secondPerMaxFPS;
        double m_deltaTime;

        int m_maxFPS;
        int m_fps;
        int m_currentFPS;

    public:
        std::wstring m_csBuffer;

    private:
        bool CanExecuteFrame();

    public:
        SystemTimer(int _maxFPS = 60);

        bool HasPassedTime();

        void SetMaxFPS(int _fps);
        int  GetMaxFPS() const;

        virtual float GetDeltaTime() const override;
        virtual void  Reset() override;
        virtual void  Start() override;
    };
}  // namespace HBSoft
