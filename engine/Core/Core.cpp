/*
author : 변한빛
description : 메인 엔진 소스파일

version: 1.0.0
date: 2024-11-04
*/

#include "pch.h"
#include "Core.h"
using namespace HBSoft;

Core::Core(HINSTANCE hInstance, UINT windowWidth, UINT windowHeight)
{
    Window::GetInstance().SetHinstance(hInstance);
    assert(Window::GetInstance().CreateWin(windowWidth, windowHeight));
    assert(D3Device::GetInstance().CreateDevice());
    ResourceManager::GetInstance().CreateDafultResource();
}

void Core::Init()
{
    m_timer.Reset();
}

void Core::Update()
{
    m_timer.Update();
    m_input.Update();
    m_sceneManager.Update(m_timer.GetDeltaTime());
    m_manager.m_sound.Update();
}

void Core::Render()
{
    float clearColor[] = {0.f, 0.f, 0.f, 1.0f};
    m_device.m_context->ClearRenderTargetView(m_device.m_rtv.Get(), clearColor);
    m_sceneManager.Render();
    m_device.m_swapChain->Present(1, 0);
}

void Core::Release()
{
    m_sceneManager.Release();
    ResourceManager::GetInstance().Release();
    Input::GetInstance().Release();
    D3Device::GetInstance().Release();
    Window::GetInstance().Release();
}

void Core::Run()
{
    Init();
    while (1)
    {
        if (!m_window.WindowRun())
            break;

        Update();
        Render();
    }
    Release();
}
