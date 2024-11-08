/*
author : 변한빛
description : 시스템 타이머를 관리하기 위해 만든 소스 파일
여기서 fps나 델타 타임을 정의한다

version: 1.0.0
date: 2024-11-04
*/

#include "pch.h"
#include "SystemTimer.h"
using namespace HBSoft;

SystemTimer::SystemTimer()
{
    Reset();
}

float SystemTimer::GetDeltaTime() const
{
    return static_cast<float>(m_deltaTime.count());
}

float SystemTimer::GetElapsedTime() const
{
    return static_cast<float>(m_elapsedTime.count());
}

void SystemTimer::Update()
{
    m_currentTimeTick  = steady_clock::now();
    m_frameDuration    = m_currentTimeTick - m_startTimeTick;
    m_deltaTime        = m_frameDuration - m_elapsedTime;
    m_secondTime      += m_deltaTime;
    m_elapsedTime      = m_frameDuration;


    if (m_secondTime >= m_oneSecond)
    {
        m_fps2        = m_fps;
        m_fps         = 0;
        m_secondTime -= m_oneSecond;
    }

    m_fps++;

#ifdef _DEBUG
    TCHAR msgKey[MAX_PATH] = {
        0,
    };
    _stprintf_s(msgKey, L"FPS=%ld GameTimer=%10.10f", m_fps2, m_elapsedTime.count());
    m_csBuffer = msgKey;
#endif
}

void SystemTimer::Reset()
{
    m_startTimeTick = steady_clock::now();
    m_oneSecond     = std::chrono::seconds(1);
    m_secondTime    = duration<double>(0);
    m_elapsedTime   = duration<double>(0);
    m_frameDuration = duration<double>(0);
    m_deltaTime     = duration<double>(0);
    m_fps           = 0;
}

void SystemTimer::Start()
{
    Reset();
}
