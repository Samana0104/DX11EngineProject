#include "pch.h"
#include "Timer.h"
using namespace HBSoft;

float Timer::GetElapsedTime() const
{
    return static_cast<float>(m_elapsedTime.count());
}

float Timer::GetDeltaTime() const
{
    return static_cast<float>(m_secondPerFrame.count());
}

void Timer::Reset()
{
    m_startTimeTick  = steady_clock::now();
    m_elapsedTime    = duration<double>(0);
    m_frameDuration  = duration<double>(0);
    m_secondPerFrame = duration<double>(0);
}

void Timer::Start()
{
    Reset();
}

void Timer::Update()
{
    m_currentTimeTick = steady_clock::now();
    m_frameDuration   = m_currentTimeTick - m_startTimeTick;
    m_secondPerFrame  = m_frameDuration - m_elapsedTime;
    m_elapsedTime     = m_frameDuration;
}
