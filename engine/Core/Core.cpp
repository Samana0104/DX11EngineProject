/*
author : 변한빛
description : 메인 엔진 소스파일

version: 1.0.0
date: 2024-11-04
*/

#include "pch.h"
#include "Core.h"
using namespace HBSoft;

Core::Core(HINSTANCE hInstance, HPoint windowSize)
{
    m_window = std::make_shared<Window>(hInstance, windowSize);
    m_device = std::make_shared<D3Device>(m_window);
    m_input  = std::make_shared<Input>(m_window);
    m_assets = std::make_unique<AssetsMgr>(m_window, m_device);
    m_timer.Reset();
}

void Core::Update()
{
    m_timer.Update();
    m_input.Update();
    m_sceneMgr.Update(m_timer.GetDeltaTime());
    m_assets->m_sound.Update();
}

void Core::Render()
{
    float clearColor[] = {0.f, 0.f, 0.f, 1.0f};
    m_device->m_context->ClearRenderTargetView(m_device->m_rtv.Get(), clearColor);
    m_sceneMgr.Render();
    m_device->m_swapChain->Present(1, 0);
}

void Core::Release()
{
    m_sceneMgr.Release();
}

void Core::Run()
{
    if (m_isRunning)  // 두번 호출 하지 말라고 안전문 걸어둠
        return;
    else
        m_isRunning = true;

    while (1)
    {
        if (!m_window->Run())
            break;

        Update();
        Render();
    }
    Release();
}

void Core::CreateEngine(HINSTANCE hInstance, HPoint windowSize)
{
    if (engine != nullptr)
        engine = std::make_unique<Core>(hInstance, windowSize);
}
