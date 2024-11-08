/*
author : 변한빛
description : 메인 엔진 헤더파일 전역변수로 자유롭게 접근 가능하다

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include "pch.h"
#include "SystemTimer.h"
#include "SceneMgr.h"
#include "AssetsMgr.h"
#include "Input.h"

#define HENGINE HBSoft::Core::engine
#define HWINDOW HBSoft::Core::engine->m_window
#define HDEVICE HBSoft::Core::engine->m_device
#define HINPUT  HBSoft::Core::engine->m_input
#define HASSET  HBSoft::Core::engine->m_assets
#define HTIMER  HBSoft::Core::engine->m_timer

namespace HBSoft
{
    class Core
    {
    private:
        bool m_isRunning = false;

    public:
        inline static std::unique_ptr<Core> engine = nullptr;

        SceneMgr    m_sceneMgr;
        SystemTimer m_timer;

        std::unique_ptr<AssetsMgr> m_assets;
        std::unique_ptr<Input>     m_input;
        std::shared_ptr<D3Device>  m_device;
        std::shared_ptr<Window>    m_window;

    private:
        Core(Core&&)                 = delete;
        Core& operator=(const Core&) = delete;
        Core& operator=(Core&&)      = delete;

    protected:
        void Update();
        void Render();
        void Release();

    public:
        Core(HINSTANCE hInstance, HPoint windowSize);
        // 접근 지시 제어자가 퍼블릭이라고 해서 코어 또 만들지 않겠지??
        // 일반 포인터는 너무 불안해서 일단 스마트 포인터로 코어 만듬
        ~Core() = default;

        void Run();

        static void Create(HINSTANCE hInstance, HPoint windowSize);
        // 시작 종료 확실하게 하기 스마트포인터로 제작하게 만듬
        static void Delete();
    };
}  // namespace HBSoft
