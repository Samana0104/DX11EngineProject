#pragma once
#include "Timer.h"

namespace HBSoft
{
    class SystemTimer : public Timer
    {
    private:
        double mOneSecond;
        double mMaxFPSTime;
        double mSecondPerMaxFPS;
        double mDeltaTime;

        int mMaxFPS;
        int mFPS;
        int mCurrentFPS;

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
