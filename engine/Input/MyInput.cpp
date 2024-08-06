#include "pch.h"
#include "MyInput.h"
using namespace MyProject;

MyInput::MyInput()
{
	ZeroMemory(&mCurrentKeyState, sizeof(KeyState) * 256);
}

void MyInput::UpdateKeyState(const UINT _key)
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

bool MyInput::IsKeyPressed(const SHORT _key) const
{
	return mCurrentKeyState[_key] == KeyState::KEY_DOWN ||
		mCurrentKeyState[_key] == KeyState::KEY_HOLD;
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

void MyInput::CallEventOnMouseMove()
{
	for (auto& obj : mCallbackOnMouseMove)
	{
		obj.second(mPreMousePos, mMousePos);
	}
}

void MyInput::CallEventOnMousePush(MOUSE_FLAGS _mouseFlags)
{
	for (auto& obj : mCallbackOnMousePush)
	{
		obj.second(
			GetCurrentMousePosVec2(), 
			_mouseFlags);
	}
}

void MyInput::CallEventOnMouseUP(MOUSE_FLAGS _mouseFlags)
{
	for (auto& obj : mCallbackOnMouseUP)
	{
		obj.second(
			GetCurrentMousePosVec2(), 
			_mouseFlags);
	}
}

CALLBACK_ID MyInput::RegisterCallBackOnMouseMove(ONMOUSEMOVE_FUNC _func)
{
	registerCallbackID++;
	mCallbackOnMouseMove.insert(std::make_pair(registerCallbackID, _func));
	return registerCallbackID;
}

CALLBACK_ID MyInput::RegisterCallBackOnMousePush(ONMOUSEPUSH_FUNC _func)
{
	registerCallbackID++;
	mCallbackOnMousePush.insert(std::make_pair(registerCallbackID, _func));
	return registerCallbackID;
}

CALLBACK_ID MyInput::RegisterCallBackOnMouseUP(ONMOUSEUP_FUNC _func)
{
	registerCallbackID++;
	mCallbackOnMouseUP.insert(std::make_pair(registerCallbackID, _func));
	return registerCallbackID;
}

bool MyInput::DeleteCallbackMouseMove(CALLBACK_ID _id)
{
	if (mCallbackOnMouseMove.contains(_id))
	{
		mCallbackOnMouseMove.erase(_id);
		return true;
	}

	return false;
}

bool MyInput::DeleteCallbackMousePush(CALLBACK_ID _id)
{
	if (mCallbackOnMousePush.contains(_id))
	{
		mCallbackOnMousePush.erase(_id);
		return true;
	}

	return false;
}

bool MyInput::DeleteCallbackMouseUP(CALLBACK_ID _id)
{
	if (mCallbackOnMouseUP.contains(_id))
	{
		mCallbackOnMouseUP.erase(_id);
		return true;
	}

	return false;
}

bool MyInput::DeleteCallBack(CALLBACK_ID _id)
{
	bool isDeleted = false;

	if (DeleteCallbackMouseMove(_id))
		isDeleted = true;
	
	if (DeleteCallbackMousePush(_id))
		isDeleted = true;

	if (DeleteCallbackMouseUP(_id))
		isDeleted = true;

		//MessageBoxA(NULL, "Not existed event id[id Error]", "[OnMouse event]", MB_OK);
	return isDeleted;
}

void MyInput::CheckMouseMove()
{
		// mouse move
	//if (mPreMousePos.x - mMousePos.x != 0L && mPreMousePos.y - mMousePos.y != 0L)
	//{
		CallEventOnMouseMove();
	//}
}

void MyInput::CheckMousePush()
{
	MOUSE_FLAGS mouseFlags = 0;
	bool isPushed = false;

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
	
	if(isPushed)
		CallEventOnMousePush(mouseFlags);
}

void MyInput::CheckMouseUP()
{
	MOUSE_FLAGS mouseFlags = 0;
	bool isUp = false;

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
	
	if(isUp)
		CallEventOnMouseUP(mouseFlags);
}


void MyInput::Update()
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
