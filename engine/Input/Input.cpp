/*
author : 변한빛
description : 인풋 처리를 위한 소스 파일

version: 1.0.0
date: 2024-11-04
*/

#include "pch.h"
#include "Input.h"
using namespace HBSoft;

Input::Input()
{
    ZeroMemory(&m_keyState, sizeof(KeyState) * 256);
}

void Input::UpdateKeyState(const UINT key)
{
    if (key >= KEY_COUNT)
        return;

    SHORT currentKey = GetAsyncKeyState(key);

    if (currentKey & PRESSED_KEY)
    {
        (IsKeyFree(key) || IsKeyUp(key)) ? SetKeyDown(key) : SetKeyHold(key);
    }
    else
    {
        (IsKeyDown(key) || IsKeyHold(key)) ? SetKeyUp(key) : SetKeyFree(key);
    }
}

KeyState Input::GetKeyState(const UINT key) const
{
    return m_keyState[key];
}

POINT_L Input::GetMousePos() const
{
    return m_mousePos;
}

POINT_F Input::GetMousePosF() const
{
    return {static_cast<float>(m_mousePos.x), static_cast<float>(m_mousePos.y)};
}

vec2 Input::GetMousePosVec2() const
{
    return {static_cast<float>(m_mousePos.x), static_cast<float>(m_mousePos.y)};
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
    if (!m_window.IsActivate())
        return;

    m_preMousePos = m_mousePos;

    for (UINT key = 0; key < KEY_COUNT; key++)
    {
        UpdateKeyState(key);
    }

    GetCursorPos(&m_mousePos);
    ScreenToClient(m_window.GetWindowHandle(), &m_mousePos);
}
