#include "pch.h"
#include "Core.h"
using namespace HBSoft;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    Core::ENGINE_BEGIN(hInstance, 960, 720);
    std::shared_ptr<Core> core = std::make_shared<Core>();
    core->GameRun();

    core.reset();  // 메모리 초기화 순서가 있기에 무조건 리셋 해야함
    // 나중에 begin end에서 자동 처리 하게 만들예정
    Core::ENGINE_END();
    return 0;
}