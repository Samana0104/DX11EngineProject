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

	class MyInput : public Component
	{
	private:
		KeyState	mCurrentKeyState[256];
		POINT_L		mMousePos;

	private:
		void UpdateKeyState(UINT _key);
	
	public:
		MyInput();

		KeyState	GetCurrentKeyState(UINT _key);
		POINT_L		GetCurrentMousePos() const;

		bool IsKeyUp(UINT _key) const;
		bool IsKeyDown(UINT _key) const;
		bool IsKeyFree(UINT _key) const;
		bool IsKeyHold(UINT _key) const;
		bool IsKeyPushed(SHORT _key);

		virtual void UpdateComponent() override;
		virtual void RenderComponent() override;
	};
}
