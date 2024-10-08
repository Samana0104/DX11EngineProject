#pragma once
#include "pch.h"
#include "SystemTimer.h"
#include "Input.h"
#include "Window.h"
#include "ResourceManger.h"
#include "SceneManager.h"
#include "ObjectManager.h"

namespace HBSoft
{
    class Core : public CoreAPI
    {
    protected:
        SceneManager m_sceneManager;
        SystemTimer  m_timer;
        Object2D     m_wideScreen;

        Input&           m_input   = Input::GetInstance();
        Window&          m_window  = Window::GetInstance();
        D3Device&        m_device  = D3Device::GetInstance();
        ResourceManager& m_manager = ResourceManager::GetInstance();

    private:
        Core(const Core&)           = delete;
        void operator=(const Core&) = delete;

        void GameFrame();
        void GamePreRender();
        void GameRender();
        void GamePostRender();
        void GameInit();
        void GameRelease();

    public:
        Core() = default;
        void GameRun();

        static void ENGINE_BEGIN(HINSTANCE _hinstance, LONG _width, LONG _height);
        static void ENGINE_END();
    };
}  // namespace HBSoft
