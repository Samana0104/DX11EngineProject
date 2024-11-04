/*
author : 변한빛
description : 메인 엔진 헤더파일

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include "pch.h"
#include "SystemTimer.h"
#include "SceneManager.h"
#include "ResourceManger.h"
#include "Input.h"

namespace HBSoft
{
    class Core
    {
    public:
        SceneManager m_sceneManager;
        SystemTimer  m_timer;

        Input&           m_input   = Input::GetInstance();
        Window&          m_window  = Window::GetInstance();
        D3Device&        m_device  = D3Device::GetInstance();
        ResourceManager& m_manager = ResourceManager::GetInstance();

    private:
        Core(Core&&)                 = delete;
        Core& operator=(const Core&) = delete;
        Core& operator=(Core&&)      = delete;

    protected:
        void Init();
        void Update();
        void Render();
        void Release();

    public:
        virtual ~Core() = default;
        Core(HINSTANCE hInstance, UINT windowWidth, UINT windowHeight);

        void Run();
    };
}  // namespace HBSoft
