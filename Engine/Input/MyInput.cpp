#include "pch.h"
#include "MyInput.h"
using namespace MyProject;

MyInput::MyInput()
{
	ZeroMemory(&mCurrentKeyState, sizeof(KeyState) * 256);
	mMousePos = { 0, 0 };
}

void MyInput::UpdateKeyState(const UINT _key)
{
	if (_key >= KEY_COUNT)
		return;

	SHORT currentKey = GetAsyncKeyState(_key);

	if (IsKeyPressed(currentKey))
	{
		(IsKeyFree(_key) || IsKeyUp(_key)) ? SetKeyDown(_key) : SetKeyHold(_key);
	}
	else
	{
		(IsKeyDown(_key) || IsKeyHold(_key)) ? SetKeyUp(_key) : SetKeyFree(_key);
	}
}

KeyState MyInput::GetCurrentKeyState(const UINT _key) const
{
	return mCurrentKeyState[_key];
}

POINT_L MyInput::GetCurrentMousePos() const
{
	return mMousePos;
}

POINT_F MyInput::GetCurrentMousePosF() const
{
	return { static_cast<float>(mMousePos.x), static_cast<float>(mMousePos.y) };
}

vec2 MyInput::GetCurrentMousePosVec2() const
{
	return { static_cast<float>(mMousePos.x), static_cast<float>(mMousePos.y) };
}

bool MyInput::IsKeyUp(const UINT _key) const
{
	return mCurrentKeyState[_key] == KeyState::KEY_UP;
}

bool MyInput::IsKeyDown(const UINT _key) const
{
	return mCurrentKeyState[_key] == KeyState::KEY_DOWN;
}

bool MyInput::IsKeyFree(const UINT _key) const
{
	return mCurrentKeyState[_key] == KeyState::KEY_FREE;
}

bool MyInput::IsKeyHold(const UINT _key) const 
{
	return mCurrentKeyState[_key] == KeyState::KEY_HOLD;
}

bool MyInput::IsKeyPressed(const SHORT _key)
{
	static const SHORT PRESSED_KEY = static_cast<SHORT>(0x8000);
	return _key & PRESSED_KEY;
}

KeyState MyInput::GetLBState() const
{
	return GetCurrentKeyState(VK_LBUTTON);
}

KeyState MyInput::GetRBState() const
{
	return GetCurrentKeyState(VK_RBUTTON);
}

KeyState MyInput::GetMBState() const
{
	return GetCurrentKeyState(VK_MBUTTON);
}

void MyInput::SetKeyUp(const UINT _key)
{
	mCurrentKeyState[_key] = KeyState::KEY_UP;
}

void MyInput::SetKeyDown(const UINT _key)
{
	mCurrentKeyState[_key] = KeyState::KEY_DOWN;
}

void MyInput::SetKeyFree(const UINT _key)
{
	mCurrentKeyState[_key] = KeyState::KEY_FREE;
}

void MyInput::SetKeyHold(const UINT _key)
{
	mCurrentKeyState[_key] = KeyState::KEY_HOLD;
}

void MyInput::Update()
{
	if (!mWindow.IsActivate())
		return;

	GetCursorPos(&mMousePos);
	ScreenToClient(mWindow.GetWindowHandle(), &mMousePos);

	for (UINT key = 0; key < KEY_COUNT; key++)
	{
		UpdateKeyState(key);
	}
}
