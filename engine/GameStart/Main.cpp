#include "pch.h"
#include "Core.h"
using namespace HBSoft;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    Core::ENGINE_BEGIN(hInstance, 960, 720);
    std::shared_ptr<Core> core = std::make_shared<Core>();
    core->GameRun();

    core.reset();  // �޸� �ʱ�ȭ ������ �ֱ⿡ ������ ���� �ؾ���
    // ���߿� begin end���� �ڵ� ó�� �ϰ� ���鿹��
    Core::ENGINE_END();
    return 0;
}