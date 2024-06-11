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

void MyInput::UpdateComponent()
{
	GetCursorPos(&mMousePos);
	ScreenToClient(mWindow.GetWindowHandle(), &mMousePos);

	for (UINT key = 0; key < 255; key++)
	{
		SHORT currentKey = GetAsyncKeyState(key);


		if (currentKey & PUSHED_KEY)
		{
			if (mCurrentKeyState[key] == KeyState::KEY_FREE ||
				mCurrentKeyState[key] == KeyState::KEY_UP)
			{
				mCurrentKeyState[key] = KeyState::KEY_DOWN;
			}
			else
			{
				mCurrentKeyState[key] = KeyState::KEY_HOLD;
			}
		}
		else
		{
			if (mCurrentKeyState[key] == KeyState::KEY_DOWN ||
				mCurrentKeyState[key] == KeyState::KEY_HOLD)
			{
				mCurrentKeyState[key] = KeyState::KEY_UP;
			}
			else
			{
				mCurrentKeyState[key] = KeyState::KEY_FREE;
			}
		}
	}
}

void MyInput::RenderComponent()
{
}

void MyInput::ReleaseComponent()
{
}
