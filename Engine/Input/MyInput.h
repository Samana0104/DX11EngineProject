#pragma once
#include "MyCoreAPI.h"
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

	class MyInput : public Singleton<MyInput>
	{
	private:
		static inline const UINT KEY_COUNT = 256;

		KeyState	mCurrentKeyState[KEY_COUNT];
		POINT_L		mMousePos;

	protected:
		inline static MyWindow& mWindow = MyWindow::GetInstance();

	private:
		friend class Singleton<MyInput>;
		MyInput();

		void UpdateKeyState(UINT _key);
	
	public:

		KeyState GetCurrentKeyState(const UINT _key);
		POINT_L	 GetCurrentMousePos() const;
		POINT_F	 GetCurrentMousePosF() const;
		vec2	 GetCurrentMousePosVec2() const;

		bool IsKeyUp(const UINT _key) const;
		bool IsKeyDown(const UINT _key) const;
		bool IsKeyFree(const UINT _key) const;
		bool IsKeyHold(const UINT _key) const;
		bool IsKeyPressed(const SHORT _key);

		void SetKeyUp(const UINT _key);
		void SetKeyDown(const UINT _key);
		void SetKeyFree(const UINT _key);
		void SetKeyHold(const UINT _key);

		virtual void UpdateComponent();
		virtual void RenderComponent();
	};
}
