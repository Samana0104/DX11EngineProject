/*
author : 변한빛
description : 시스템 타이머를 관리하기 위해 만든 헤더 파일
여기서 fps나 델타 타임을 정의한다

version: 1.0.0
date: 2024-11-07
*/

#pragma once

namespace HBSoft
{
    using namespace std::chrono;

    class SystemTimer
    {
    private:
        time_point<steady_clock> m_startTimeTick;
        time_point<steady_clock> m_currentTimeTick;
        duration<double>         m_oneSecond;
        duration<double>         m_secondTime;
        duration<double>         m_frameDuration;
        duration<double>         m_elapsedTime;
        duration<double>         m_deltaTime;

        int m_fps;
        int m_fps2;

    public:
        std::wstring m_csBuffer;

    public:
        SystemTimer();

        float GetDeltaTime() const;
        float GetElapsedTime() const;

        void Update();
        void Reset();
    };
}  // namespace HBSoft
