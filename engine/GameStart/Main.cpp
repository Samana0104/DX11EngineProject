#include "pch.h"
#include "Core.h"
#include "SceneLobby.h"

namespace HBSoft
{
    class Sample : public Core
    {
    private:
        virtual void Init() override
        {
            auto lobbyScene = std::make_unique<SceneLobby>();

            m_sceneManager.Add(L"Lobby", std::move(lobbyScene));
            m_sceneManager.SetCurrentScene(L"Lobby");
        }

        virtual void Update() override {}

        virtual void Render() override {}

        virtual void Release() override {}

    public:
        Sample(HINSTANCE hInstance, UINT width, UINT height)
        {
            Window::GetInstance().SetHinstance(hInstance);
            assert(Window::GetInstance().CreateWin(width, height));
            assert(D3Device::GetInstance().CreateDevice());
            ResourceManager::GetInstance().CreateDafultResource();
        }
    };

}  // namespace HBSoft

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
#ifdef DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);  // 메모리 누수 확인
#endif                                                             // DEBUG

    HBSoft::Sample s(hInstance, 1280, 960);
    s.Run();

#ifdef DEBUG
    _CrtCheckMemory();
#endif  // DEBUG
    return 0;
}