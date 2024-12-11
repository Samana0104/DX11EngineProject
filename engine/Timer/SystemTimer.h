/*
author : ���Ѻ�
description : �ý��� Ÿ�̸Ӹ� �����ϱ� ���� ���� ��� ����
���⼭ fps�� ��Ÿ Ÿ���� �����Ѵ�

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
