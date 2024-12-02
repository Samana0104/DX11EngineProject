#include "pch.h"
#include "LobbyButton.h"
using namespace HBSoft;

LobbyButton::LobbyButton()
{
    SetStartBtn();
    SetEndBtn();
    SetSettingBtn();
}

void LobbyButton::SetStartBtn()
{
    HPoint windowSize = HWINDOW->GetWindowSize();

    m_startBtn.SetArea({windowSize.x * 0.5f - 90.f,
                        windowSize.y * 0.5f + 20.f,
                        windowSize.x * 0.5f + 90.f,
                        windowSize.y * 0.5f + 80.f});
    m_startBtn.SetText(L"시작", {1.f, 1.f, 1.f, 1.f});
    m_startBtn.SetImage(L"투명.png");
    m_startBtn.SetOnClickCallback([](void) { HSCENE.SetCurrentScene(L"Game"); });
}

void LobbyButton::SetEndBtn()
{
    HPoint windowSize = HWINDOW->GetWindowSize();

    m_endBtn.SetArea({windowSize.x * 0.5f - 90.f,
                      windowSize.y * 0.5f + 100.f,
                      windowSize.x * 0.5f + 90.f,
                      windowSize.y * 0.5f + 160.f});
    m_endBtn.SetText(L"옵션", {1.f, 1.f, 1.f, 1.f});
    m_endBtn.SetImage(L"투명.png");
    m_endBtn.SetOnClickCallback([](void) {});
}

void LobbyButton::SetSettingBtn()
{
    HPoint windowSize = HWINDOW->GetWindowSize();

    m_settingBtn.SetArea({windowSize.x * 0.5f - 90.f,
                          windowSize.y * 0.5f + 180.f,
                          windowSize.x * 0.5f + 90.f,
                          windowSize.y * 0.5f + 240.f});
    m_settingBtn.SetText(L"종료", {1.f, 1.f, 1.f, 1.f});
    m_settingBtn.SetImage(L"투명.png");
    m_settingBtn.SetOnClickCallback([](void) { PostQuitMessage(0); });
}

void LobbyButton::Init() {}

void LobbyButton::Release() {}

void LobbyButton::Update(const float deltaTime)
{
    m_startBtn.Update(deltaTime);
    m_settingBtn.Update(deltaTime);
    m_endBtn.Update(deltaTime);
}

void LobbyButton::Render()
{
    m_startBtn.Render();
    m_settingBtn.Render();
    m_endBtn.Render();
}
