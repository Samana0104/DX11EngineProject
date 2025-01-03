/*
author : 변한빛
description : 인풋 처리를 위한 소스 파일

version: 1.0.0
date: 2024-11-30
*/

#include "pch.h"
#include "Input.h"
using namespace HBSoft;

Input::Input(std::shared_ptr<Window> window)
    : m_window(window)
{
    ZeroMemory(&m_keyState, sizeof(KeyState) * 256);
}

Input::~Input() {}

void Input::UpdateKeyState(const UINT key)
{
    if (key >= KEY_COUNT)
        return;

    SHORT currentKey = GetAsyncKeyState(key);

    if (currentKey & PRESSED_KEY)
        (IsKeyFree(key) || IsKeyUp(key)) ? SetKeyDown(key) : SetKeyHold(key);
    else
        (IsKeyDown(key) || IsKeyHold(key)) ? SetKeyUp(key) : SetKeyFree(key);
}

KeyState Input::GetKeyState(const UINT key) const
{
    return m_keyState[key];
}

const HPoint& Input::GetScreenMousePos() const
{
    return m_mousePos;
}

const HPoint Input::GetNDCMousePos() const
{
    HPoint windowSize = m_window->GetWindowSize();
    return {2.f * m_mousePos.x / windowSize.x - 1.f, -2.f * m_mousePos.y / windowSize.y + 1.f};
}

const HPoint Input::GetCartesianMousePos() const
{
    HPoint windowSize = m_window->GetWindowSize();
    return {m_mousePos.x - windowSize.x * 0.5f, -m_mousePos.y + windowSize.y * 0.5f};
}

bool Input::IsKeyUp(const UINT key) const
{
    return m_keyState[key] == KeyState::KEY_UP;
}

bool Input::IsKeyDown(const UINT key) const
{
    return m_keyState[key] == KeyState::KEY_DOWN;
}

bool Input::IsKeyFree(const UINT key) const
{
    return m_keyState[key] == KeyState::KEY_FREE;
}

bool Input::IsKeyHold(const UINT key) const
{
    return m_keyState[key] == KeyState::KEY_HOLD;
}

bool Input::IsKeyPressed(const SHORT key) const
{
    return m_keyState[key] == KeyState::KEY_DOWN || m_keyState[key] == KeyState::KEY_HOLD;
}

void Input::SetKeyUp(const UINT key)
{
    m_keyState[key] = KeyState::KEY_UP;
}

void Input::SetKeyDown(const UINT key)
{
    m_keyState[key] = KeyState::KEY_DOWN;
}

void Input::SetKeyFree(const UINT key)
{
    m_keyState[key] = KeyState::KEY_FREE;
}

void Input::SetKeyHold(const UINT key)
{
    m_keyState[key] = KeyState::KEY_HOLD;
}

void Input::Update()
{
    POINT mousePos;

    if (!m_window->IsActivate())  // 게임 윈도우가 켜져있으면 ( 활성화 될 때 )
        return;

    for (UINT key = 0; key < KEY_COUNT; key++)
        UpdateKeyState(key);

    GetCursorPos(&mousePos);
    ScreenToClient(m_window->GetHandle(), &mousePos);
    m_mousePos = mousePos;
}
