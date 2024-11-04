#include "pch.h"
#include "SystemTimer.h"
using namespace HBSoft;

SystemTimer::SystemTimer()
{
    Reset();
}

// #ifdef _DEBUG
//     TCHAR msgKey[MAX_PATH] = {
//         0,
//     };
//     _stprintf_s(msgKey,
//                 L" FPS=%ld \n FPS=%ld \n %.10f \n GameTimer=%10.10f \n SPF=%10.10f\n",
//                 m_currentFPS,
//                 m_fps,
//                 m_deltaTime,
//                 m_elapsedTime.count(),
//                 m_oneSecond);
//     m_csBuffer = msgKey;
// #endif

float SystemTimer::GetDeltaTime() const
{
    return static_cast<float>(m_deltaTime);
}

float SystemTimer::GetElapsedTime() const
{
    return static_cast<float>(m_elapsedTime.count());
}

void SystemTimer::Update()
{
    m_currentTimeTick = steady_clock::now();
    m_frameDuration   = m_currentTimeTick - m_startTimeTick;
    m_secondPerFrame  = m_frameDuration - m_elapsedTime;
    m_elapsedTime     = m_frameDuration;
}

void SystemTimer::Reset()
{
    m_startTimeTick  = steady_clock::now();
    m_elapsedTime    = duration<double>(0);
    m_frameDuration  = duration<double>(0);
    m_secondPerFrame = duration<double>(0);
    m_deltaTime      = 0.0;
    m_fps            = 0;
    m_oneSecond      = 0.0;
}

void SystemTimer::Start() {}
