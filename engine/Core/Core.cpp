#include "pch.h"
#include "Core.h"
using namespace HBSoft;

void Core::InternalUpdate()
{
    m_timer.Update();
    m_input.Update();
    m_sceneManager.Update(m_timer.GetDeltaTime());
    m_manager.m_sound.Update();
    Update();
}

void Core::InternalRender()
{
    float clearColor[] = {0.f, 0.f, 0.f, 1.0f};
    m_device.m_context->ClearRenderTargetView(m_device.m_rtv.Get(), clearColor);
    m_sceneManager.Render();
    m_device.m_swapChain->Present(1, 0);
    Render();
}

void Core::InternalRelease()
{
    m_sceneManager.Release();
    ResourceManager::GetInstance().Release();
    Input::GetInstance().Release();
    D3Device::GetInstance().Release();
    Window::GetInstance().Release();
    Release();
}

void Core::InternalInit()
{
    m_timer.Reset();
    Init();
}

void Core::Run()
{
    InternalInit();
    while (1)
    {
        if (!m_window.WindowRun())
            break;

        InternalUpdate();
        InternalRender();
    }
    InternalRelease();
}
