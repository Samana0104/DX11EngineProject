#include "pch.h"
#include "Core.h"
using namespace HBSoft;

void Core::GameFrame()
{
    m_input.Update();
    m_sceneManager.Update(m_timer.GetDeltaTime());
    m_manager.mSound.Update();
}

void Core::GamePreRender()
{
    float clearColor[] = {0.f, 0.f, 0.f, 1.0f};
    m_device.mContext->ClearRenderTargetView(m_device.mRTV.Get(), clearColor);
}

void Core::GameRender()
{
    GamePreRender();
    m_sceneManager.Render();
    GamePostRender();
}

void Core::GamePostRender()
{
#ifdef _DEBUG
    m_manager.mFont.DrawRectForDebugging();
#endif

    m_device.mSwapChain->Present(1, 0);
}

void Core::GameInit()
{
    m_timer.Reset();
    m_sceneManager.Init();
}

void Core::GameRelease()
{
    m_sceneManager.Release();
}

void Core::GameRun()
{
    GameInit();
    while (1)
    {
        if (!m_window.WindowRun())
            break;

        if (m_timer.HasPassedTime())
        {
            GameFrame();
            GameRender();
        }
    }
    GameRelease();
}

void Core::ENGINE_BEGIN(HINSTANCE _hinstance, LONG _width, LONG _height)
{
    Window::GetInstance().SetHinstance(_hinstance);
#ifdef _DEBUG
    _ASSERT(Window::GetInstance().CreateWin(_width, _height));
    _ASSERT(D3Device::GetInstance().CreateDevice());
#else
    MyWindow::GetInstance().CreateWin(_width, _height);
    D3Device::GetInstance().CreateDevice();
#endif

    MyResourceManager::GetInstance().CreateDafultResource();
}

void Core::ENGINE_END()
{
    MyResourceManager::GetInstance().Release();
    Input::GetInstance().Release();
    D3Device::GetInstance().Release();
    MyWindow::GetInstance().Release();
}
