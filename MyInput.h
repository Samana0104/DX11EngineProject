#pragma once
#include "Component.h"
#include "MyWindow.h"

namespace MyProject
{
	enum class KeyState
	{
		KEY_FREE = 0,
		KEY_UP,
		KEY_DOWN,
		KEY_HOLD
	};

	class MyInput : protected Component
	{
	private:
		static const int PUSHED_KEY = 0x8000;
		KeyState	mCurrentKeyState[256];
		POINT_L		mMousePos;
	
	public:
		MyInput();

		KeyState	GetCurrentKeyState(UINT _key);
		POINT_L		GetCurrentMousePos() const;

		virtual void InitComponent() override;
		virtual void UpdateComponent() override;
		virtual void RenderComponent() override;
		virtual void ReleaseComponent() override;
	};
}
