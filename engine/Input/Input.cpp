#include "pch.h"
#include "Input.h"
using namespace HBSoft;

Input::Input()
{
    ZeroMemory(&m_currentKeyState, sizeof(KeyState) * 256);
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

KeyState Input::GetCurrentKeyState(const UINT _key) const
{
    return m_currentKeyState[_key];
}

POINT_L Input::GetCurrentMousePos() const
{
    return m_mousePos;
}

POINT_F Input::GetCurrentMousePosF() const
{
    return {static_cast<float>(m_mousePos.x), static_cast<float>(m_mousePos.y)};
}

vec2 Input::GetCurrentMousePosVec2() const
{
    return {static_cast<float>(m_mousePos.x), static_cast<float>(m_mousePos.y)};
}

KeyState Input::GetLBState() const
{
    return GetCurrentKeyState(VK_LBUTTON);
}

KeyState Input::GetRBState() const
{
    return GetCurrentKeyState(VK_RBUTTON);
}

KeyState Input::GetMBState() const
{
    return GetCurrentKeyState(VK_MBUTTON);
}

bool Input::IsKeyUp(const UINT _key) const
{
    return m_currentKeyState[_key] == KeyState::KEY_UP;
}

bool Input::IsKeyDown(const UINT _key) const
{
    return m_currentKeyState[_key] == KeyState::KEY_DOWN;
}

bool Input::IsKeyFree(const UINT _key) const
{
    return m_currentKeyState[_key] == KeyState::KEY_FREE;
}

bool Input::IsKeyHold(const UINT _key) const
{
    return m_currentKeyState[_key] == KeyState::KEY_HOLD;
}

bool Input::IsKeyPressed(const SHORT _key) const
{
    return m_currentKeyState[_key] == KeyState::KEY_DOWN ||
           m_currentKeyState[_key] == KeyState::KEY_HOLD;
}

void Input::SetKeyUp(const UINT _key)
{
    m_currentKeyState[_key] = KeyState::KEY_UP;
}

void Input::SetKeyDown(const UINT _key)
{
    m_currentKeyState[_key] = KeyState::KEY_DOWN;
}

void Input::SetKeyFree(const UINT _key)
{
    m_currentKeyState[_key] = KeyState::KEY_FREE;
}

void Input::SetKeyHold(const UINT _key)
{
    m_currentKeyState[_key] = KeyState::KEY_HOLD;
}

void Input::CallEventOnMouseMove()
{
    for (auto& obj : m_callbackOnMouseMove)
    {
        obj.second(m_preMousePos, m_mousePos);
    }
}

void Input::CallEventOnMousePush(MOUSE_FLAGS _mouseFlags)
{
    for (auto& obj : m_callbackOnMousePush)
    {
        obj.second(GetCurrentMousePosVec2(), _mouseFlags);
    }
}

void Input::CallEventOnMouseUP(MOUSE_FLAGS _mouseFlags)
{
    for (auto& obj : m_callbackOnMouseUP)
    {
        obj.second(GetCurrentMousePosVec2(), _mouseFlags);
    }
}

CALLBACK_ID Input::RegisterCallBackOnMouseMove(ONMOUSEMOVE_FUNC _func)
{
    m_registerCallbackID++;
    m_callbackOnMouseMove.insert(std::make_pair(m_registerCallbackID, _func));
    return m_registerCallbackID;
}

CALLBACK_ID Input::RegisterCallBackOnMousePush(ONMOUSEPUSH_FUNC _func)
{
    m_registerCallbackID++;
    m_callbackOnMousePush.insert(std::make_pair(m_registerCallbackID, _func));
    return m_registerCallbackID;
}

CALLBACK_ID Input::RegisterCallBackOnMouseUP(ONMOUSEUP_FUNC _func)
{
    m_registerCallbackID++;
    m_callbackOnMouseUP.insert(std::make_pair(m_registerCallbackID, _func));
    return m_registerCallbackID;
}

bool Input::DeleteCallbackMouseMove(CALLBACK_ID _id)
{
    if (m_callbackOnMouseMove.contains(_id))
    {
        m_callbackOnMouseMove.erase(_id);
        return true;
    }

    return false;
}

bool Input::DeleteCallbackMousePush(CALLBACK_ID _id)
{
    if (m_callbackOnMousePush.contains(_id))
    {
        m_callbackOnMousePush.erase(_id);
        return true;
    }

    return false;
}

bool Input::DeleteCallbackMouseUP(CALLBACK_ID _id)
{
    if (m_callbackOnMouseUP.contains(_id))
    {
        m_callbackOnMouseUP.erase(_id);
        return true;
    }

    return false;
}

bool Input::DeleteCallBack(CALLBACK_ID _id)
{
    bool isDeleted = false;

    if (DeleteCallbackMouseMove(_id))
        isDeleted = true;

    if (DeleteCallbackMousePush(_id))
        isDeleted = true;

    if (DeleteCallbackMouseUP(_id))
        isDeleted = true;

    // MessageBoxA(NULL, "Not existed event id[id Error]", "[OnMouse event]", MB_OK);
    return isDeleted;
}

void Input::CheckMouseMove()
{
    // mouse move
    // if (m_preMousePos.x - m_mousePos.x != 0L && m_preMousePos.y - m_mousePos.y != 0L)
    //{
    CallEventOnMouseMove();
    //}
}

void Input::CheckMousePush()
{
    MOUSE_FLAGS mouseFlags = 0;
    bool        isPushed   = false;

    if (GetLBState() == KeyState::KEY_DOWN)
    {
        isPushed    = true;
        mouseFlags |= VK_LBUTTON;
    }
    if (GetMBState() == KeyState::KEY_DOWN)
    {
        isPushed    = true;
        mouseFlags |= VK_MBUTTON;
    }

    if (GetRBState() == KeyState::KEY_DOWN)
    {
        isPushed    = true;
        mouseFlags |= VK_RBUTTON;
    }

    if (isPushed)
        CallEventOnMousePush(mouseFlags);
}

void Input::CheckMouseUP()
{
    MOUSE_FLAGS mouseFlags = 0;
    bool        isUp       = false;

    if (GetLBState() == KeyState::KEY_UP)
    {
        isUp        = true;
        mouseFlags |= VK_LBUTTON;
    }
    if (GetMBState() == KeyState::KEY_UP)
    {
        isUp        = true;
        mouseFlags |= VK_MBUTTON;
    }

    if (GetRBState() == KeyState::KEY_UP)
    {
        isUp        = true;
        mouseFlags |= VK_RBUTTON;
    }

    if (isUp)
        CallEventOnMouseUP(mouseFlags);
}

void Input::Update()
{
    if (!mWindow.IsActivate())
        return;

    m_preMousePos = m_mousePos;

    for (UINT key = 0; key < KEY_COUNT; key++)
    {
        UpdateKeyState(key);
    }

    GetCursorPos(&m_mousePos);
    ScreenToClient(mWindow.GetWindowHandle(), &m_mousePos);

    CheckMouseMove();
    CheckMousePush();
    CheckMouseUP();
}
