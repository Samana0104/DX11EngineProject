#include "pch.h"
#include "Input.h"
using namespace HBSoft;

Input::Input()
{
    ZeroMemory(&mCurrentKeyState, sizeof(KeyState) * 256);
}

void Input::UpdateKeyState(const UINT _key)
{
    if (_key >= KEY_COUNT)
        return;

    SHORT currentKey = GetAsyncKeyState(_key);

    if (currentKey & PRESSED_KEY)
    {
        (IsKeyFree(_key) || IsKeyUp(_key)) ? SetKeyDown(_key) : SetKeyHold(_key);
    }
    else
    {
        (IsKeyDown(_key) || IsKeyHold(_key)) ? SetKeyUp(_key) : SetKeyFree(_key);
    }
}

KeyState Input::GetCurrentKeyState(const UINT _key) const
{
    return mCurrentKeyState[_key];
}

POINT_L Input::GetCurrentMousePos() const
{
    return mMousePos;
}

POINT_F Input::GetCurrentMousePosF() const
{
    return {static_cast<float>(mMousePos.x), static_cast<float>(mMousePos.y)};
}

vec2 Input::GetCurrentMousePosVec2() const
{
    return {static_cast<float>(mMousePos.x), static_cast<float>(mMousePos.y)};
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
    return mCurrentKeyState[_key] == KeyState::KEY_UP;
}

bool Input::IsKeyDown(const UINT _key) const
{
    return mCurrentKeyState[_key] == KeyState::KEY_DOWN;
}

bool Input::IsKeyFree(const UINT _key) const
{
    return mCurrentKeyState[_key] == KeyState::KEY_FREE;
}

bool Input::IsKeyHold(const UINT _key) const
{
    return mCurrentKeyState[_key] == KeyState::KEY_HOLD;
}

bool Input::IsKeyPressed(const SHORT _key) const
{
    return mCurrentKeyState[_key] == KeyState::KEY_DOWN ||
           mCurrentKeyState[_key] == KeyState::KEY_HOLD;
}

void Input::SetKeyUp(const UINT _key)
{
    mCurrentKeyState[_key] = KeyState::KEY_UP;
}

void Input::SetKeyDown(const UINT _key)
{
    mCurrentKeyState[_key] = KeyState::KEY_DOWN;
}

void Input::SetKeyFree(const UINT _key)
{
    mCurrentKeyState[_key] = KeyState::KEY_FREE;
}

void Input::SetKeyHold(const UINT _key)
{
    mCurrentKeyState[_key] = KeyState::KEY_HOLD;
}

void Input::CallEventOnMouseMove()
{
    for (auto& obj : mCallbackOnMouseMove)
    {
        obj.second(mPreMousePos, mMousePos);
    }
}

void Input::CallEventOnMousePush(MOUSE_FLAGS _mouseFlags)
{
    for (auto& obj : mCallbackOnMousePush)
    {
        obj.second(GetCurrentMousePosVec2(), _mouseFlags);
    }
}

void Input::CallEventOnMouseUP(MOUSE_FLAGS _mouseFlags)
{
    for (auto& obj : mCallbackOnMouseUP)
    {
        obj.second(GetCurrentMousePosVec2(), _mouseFlags);
    }
}

CALLBACK_ID Input::RegisterCallBackOnMouseMove(ONMOUSEMOVE_FUNC _func)
{
    registerCallbackID++;
    mCallbackOnMouseMove.insert(std::make_pair(registerCallbackID, _func));
    return registerCallbackID;
}

CALLBACK_ID Input::RegisterCallBackOnMousePush(ONMOUSEPUSH_FUNC _func)
{
    registerCallbackID++;
    mCallbackOnMousePush.insert(std::make_pair(registerCallbackID, _func));
    return registerCallbackID;
}

CALLBACK_ID Input::RegisterCallBackOnMouseUP(ONMOUSEUP_FUNC _func)
{
    registerCallbackID++;
    mCallbackOnMouseUP.insert(std::make_pair(registerCallbackID, _func));
    return registerCallbackID;
}

bool Input::DeleteCallbackMouseMove(CALLBACK_ID _id)
{
    if (mCallbackOnMouseMove.contains(_id))
    {
        mCallbackOnMouseMove.erase(_id);
        return true;
    }

    return false;
}

bool Input::DeleteCallbackMousePush(CALLBACK_ID _id)
{
    if (mCallbackOnMousePush.contains(_id))
    {
        mCallbackOnMousePush.erase(_id);
        return true;
    }

    return false;
}

bool Input::DeleteCallbackMouseUP(CALLBACK_ID _id)
{
    if (mCallbackOnMouseUP.contains(_id))
    {
        mCallbackOnMouseUP.erase(_id);
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
    // if (mPreMousePos.x - mMousePos.x != 0L && mPreMousePos.y - mMousePos.y != 0L)
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
        isPushed = true;
        mouseFlags |= VK_LBUTTON;
    }
    if (GetMBState() == KeyState::KEY_DOWN)
    {
        isPushed = true;
        mouseFlags |= VK_MBUTTON;
    }

    if (GetRBState() == KeyState::KEY_DOWN)
    {
        isPushed = true;
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
        isUp = true;
        mouseFlags |= VK_LBUTTON;
    }
    if (GetMBState() == KeyState::KEY_UP)
    {
        isUp = true;
        mouseFlags |= VK_MBUTTON;
    }

    if (GetRBState() == KeyState::KEY_UP)
    {
        isUp = true;
        mouseFlags |= VK_RBUTTON;
    }

    if (isUp)
        CallEventOnMouseUP(mouseFlags);
}

void Input::Update()
{
    if (!mWindow.IsActivate())
        return;

    mPreMousePos = mMousePos;

    for (UINT key = 0; key < KEY_COUNT; key++)
    {
        UpdateKeyState(key);
    }

    GetCursorPos(&mMousePos);
    ScreenToClient(mWindow.GetWindowHandle(), &mMousePos);

    CheckMouseMove();
    CheckMousePush();
    CheckMouseUP();
}
