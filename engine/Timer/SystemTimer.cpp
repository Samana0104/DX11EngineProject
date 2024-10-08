#include "pch.h"
#include "SystemTimer.h"
using namespace HBSoft;

SystemTimer::SystemTimer(int _maxFPS)
{
    m_maxFPS     = _maxFPS;
    m_maxFPSTime = 1.0 / _maxFPS;
    Reset();
}

bool SystemTimer::CanExecuteFrame()
{
    if (m_secondPerMaxFPS <= m_maxFPSTime)
        return false;

    m_deltaTime       = m_secondPerMaxFPS;
    m_secondPerMaxFPS = 0.;

#ifdef _DEBUG
    TCHAR msgKey[MAX_PATH] = {
        0,
    };
    _stprintf_s(msgKey,
                L" FPS=%ld \n FPS=%ld \n %.10f \n GameTimer=%10.10f \n SPF=%10.10f\n",
                m_currentFPS,
                m_fps,
                m_deltaTime,
                m_elapsedTime.count(),
                m_oneSecond);
    m_csBuffer = msgKey;
#endif

    return true;
}

bool SystemTimer::HasPassedTime()
{
    Timer::Update();
    m_oneSecond       += Timer::GetDeltaTime();
    m_secondPerMaxFPS += Timer::GetDeltaTime();

    if (!CanExecuteFrame())  // 프레임 제어를 위해 추가
        return false;

    m_fps++;
    if (m_oneSecond >= 1.)
    {
        m_oneSecond  = 0.;
        m_currentFPS = m_fps;
        m_fps        = 0;
    }

    return true;
}

void SystemTimer::SetMaxFPS(int _fps)
{
    m_maxFPSTime = 1.0 / _fps;
    m_maxFPS     = _fps;
}

int SystemTimer::GetMaxFPS() const
{
    return m_maxFPS;
}

float SystemTimer::GetDeltaTime() const
{
    // 모니터 끌어 당기기로 인해 너무 클 때를 방지함
    if (m_deltaTime >= m_maxFPSTime * 2)
        return static_cast<float>(m_maxFPSTime);
    else
        return static_cast<float>(m_deltaTime);
}

void SystemTimer::Reset()
{
    Timer::Reset();

    m_deltaTime       = 0.0;
    m_currentFPS      = 0;
    m_fps             = 0;
    m_secondPerMaxFPS = 0.0;
    m_oneSecond       = 0.0;
}

void SystemTimer::Start()
{
    Timer::Start();
}
