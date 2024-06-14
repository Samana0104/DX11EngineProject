#include "pch.h"
#include "MyInput.h"
using namespace MyProject;

MyInput::MyInput()
{
	ZeroMemory(&mCurrentKeyState, sizeof(KeyState) * 256);
	mMousePos = { 0, 0 };
}

KeyState MyInput::GetCurrentKeyState(UINT _key)
{
	return mCurrentKeyState[_key];
}

POINT_L MyInput::GetCurrentMousePos() const
{
	return mMousePos;
}

void MyInput::UpdateKeyState(UINT _key)
{
	SHORT currentKey = GetAsyncKeyState(_key);

	if (IsKeyPushed(currentKey))
	{
		if (IsKeyFree(_key) || IsKeyUp(_key))
		{
			mCurrentKeyState[_key] = KeyState::KEY_DOWN;
		}
		else
		{
			mCurrentKeyState[_key] = KeyState::KEY_HOLD;
		}
	}
	else
	{
		if (IsKeyDown(_key) || IsKeyHold(_key))
		{
			mCurrentKeyState[_key] = KeyState::KEY_UP;
		}
		else
		{
			mCurrentKeyState[_key] = KeyState::KEY_FREE;
		}
	}
}

void MyInput::UpdateComponent()
{
	GetCursorPos(&mMousePos);
	ScreenToClient(mWindow.GetWindowHandle(), &mMousePos);

	for (UINT key = 0; key < 255; key++)
	{
		UpdateKeyState(key);
	}
}

bool MyInput::IsKeyUp(UINT _key) const
{
	return mCurrentKeyState[_key] == KeyState::KEY_UP;
}

bool MyInput::IsKeyDown(UINT _key) const
{
	return mCurrentKeyState[_key] == KeyState::KEY_DOWN;
}

bool MyInput::IsKeyFree(UINT _key) const
{
	return mCurrentKeyState[_key] == KeyState::KEY_FREE;
}

bool MyInput::IsKeyHold(UINT _key) const 
{
	return mCurrentKeyState[_key] == KeyState::KEY_HOLD;
}

bool MyInput::IsKeyPushed(SHORT _key)
{
	static const SHORT PUSHED_KEY = 0x8000;
	return _key & PUSHED_KEY;
}

void MyInput::RenderComponent()
{
}
