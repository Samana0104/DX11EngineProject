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
    protected:
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

        void InternalUpdate();
        void InternalRender();
        void InternalInit();
        void InternalRelease();

    protected:
        virtual void Update() {}

        virtual void Render() {}

        virtual void Init() {}

        virtual void Release() {}

    public:
        virtual ~Core() = default;
        Core()          = default;

        void Run();
    };
}  // namespace HBSoft
