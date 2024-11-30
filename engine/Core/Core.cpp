/*
author : 변한빛
description : 메인 엔진 소스파일

version: 1.0.5
date: 2024-11-12
*/

#include "pch.h"
#include "Core.h"
using namespace HBSoft;

Core::Core(HINSTANCE hInstance, HPoint windowSize)
{
    m_window = std::make_shared<Window>(hInstance, windowSize);
    m_device = std::make_shared<D3Device>(m_window);
    m_input  = std::make_unique<Input>(m_window);
    m_assets = std::make_unique<AssetsMgr>(m_device);
    m_timer.Reset();

    assert(InitImGui());
}

bool Core::InitImGui()
{
    // 환경설정
    HPoint windowSize = m_window->GetSize();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

    io.DisplaySize = ImVec2(float(windowSize.x), float(windowSize.y));
    ImGui::StyleColorsLight();

    if (!ImGui_ImplWin32_Init(m_window->GetHandle()))
        return false;

    if (!ImGui_ImplDX11_Init(m_device->m_d3dDevice.Get(), m_device->m_context.Get()))
        return false;

    return true;
}

void Core::Update()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("HBSoft");

    m_timer.Update();
    m_input->Update();
    m_assets->Update();
    m_sceneMgr.Update(m_timer.GetDeltaTime());

    ImGui::End();
}

void Core::Render()
{
    float clearColor[] = {0.f, 0.f, 0.f, 1.0f};
    m_device->m_context->ClearDepthStencilView(m_device->m_dsv.Get(),
                                               D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
                                               1.0f,
                                               0);
    m_device->m_context->ClearRenderTargetView(m_device->m_rtv.Get(), clearColor);


    m_sceneMgr.Render();
    m_assets->m_fonts[L"DEBUG_FONT"]->DrawTexts(m_device,
                                                m_timer.m_csBuffer,
                                                {10.f, 10.f, 1000.f, 1000.f});

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    m_device->m_swapChain->Present(0, 0);
}

void Core::Release()
{
    m_sceneMgr.Release();

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
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

void Core::Create(HINSTANCE hInstance, HPoint windowSize)
{
    if (engine == nullptr)
        engine = std::make_unique<Core>(hInstance, windowSize);
}

void Core::Delete()
{
    if (engine != nullptr)
        engine.reset();
}
