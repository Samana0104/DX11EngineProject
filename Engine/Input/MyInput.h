#pragma once
#include "MyCoreAPI.h"
#include "MyWindow.h"

namespace MyProject
{
	//enum class MouseState
	//{
	//	DEFAULT = 0,  // 커서가 위에 없을 때(T_FOCUS상태에서 다른 곳을 T_ACTIVE하면 전환된다.)
	//	HOVER = 1,	// 커서가 위에 있을 때
	//	FOCUS = 2,	// T_ACTIVE상태에서 왼쪽 버튼을 다른 곳에서 놓았을 때(취소)
	//	ACTIVE = 3,	// 마우스 왼쪽 버튼 누르고 있을 때
	//	SELECTED = 4, // T_ACTIVE 상태에서 왼쪽버튼 놓았을 때
	//};

	enum class KeyState
	{
		KEY_FREE = 0,
		KEY_UP,
		KEY_DOWN,
		KEY_HOLD
	};

	using MOUSE_FLAGS = UINT;
	using ONMOUSEMOVE_FUNC = std::function<void(POINT_L, POINT_L)> ;
	using ONMOUSEPUSH_FUNC = std::function<void(vec2, MOUSE_FLAGS)> ;
	using ONMOUSEUP_FUNC = std::function<void(vec2, MOUSE_FLAGS)> ;

	class MyInput : public Singleton<MyInput>
	{
	private:
		static inline const UINT KEY_COUNT = 256;

		CALLBACK_ID registerCallbackID = 0;
		std::map<CALLBACK_ID, ONMOUSEMOVE_FUNC> mCallbackOnMouseMove;
		std::map<CALLBACK_ID, ONMOUSEPUSH_FUNC> mCallbackOnMousePush;
		std::map<CALLBACK_ID, ONMOUSEUP_FUNC> mCallbackOnMouseUP;

		KeyState	mCurrentKeyState[KEY_COUNT];
		POINT_L		mMousePos;
		POINT_L		mPreMousePos;

	protected:
		MyWindow& mWindow = MyWindow::GetInstance();

	private:
		friend class Singleton<MyInput>;
		MyInput();

		void UpdateKeyState(UINT _key);
	
		void SetKeyUp(const UINT _key);
		void SetKeyDown(const UINT _key);
		void SetKeyFree(const UINT _key);
		void SetKeyHold(const UINT _key);

		void CallEventOnMouseMove();
		void CallEventOnMousePush(MOUSE_FLAGS _mouseFlags);
		void CallEventOnMouseUP(MOUSE_FLAGS _mouseFlags);
		bool DeleteCallbackMouseMove(CALLBACK_ID _id);
		bool DeleteCallbackMousePush(CALLBACK_ID _id);
		bool DeleteCallbackMouseUP(CALLBACK_ID _id);

		void CheckMouseMove();
		void CheckMousePush();
		void CheckMouseUP();

	public:

		KeyState GetCurrentKeyState(const UINT _key) const;
		POINT_L	 GetCurrentMousePos() const;
		POINT_F	 GetCurrentMousePosF() const;
		vec2	 GetCurrentMousePosVec2() const;

		KeyState GetLBState() const;
		KeyState GetRBState() const;
		KeyState GetMBState() const;

		bool IsKeyUp(const UINT _key) const;
		bool IsKeyDown(const UINT _key) const;
		bool IsKeyFree(const UINT _key) const;
		bool IsKeyHold(const UINT _key) const;
		bool IsKeyPressed(const SHORT _key);

		CALLBACK_ID	RegisterCallBackOnMouseMove(ONMOUSEMOVE_FUNC _func);
		CALLBACK_ID	RegisterCallBackOnMousePush(ONMOUSEPUSH_FUNC _func);
		CALLBACK_ID	RegisterCallBackOnMouseUP(ONMOUSEUP_FUNC _func);
		bool DeleteCallBack(CALLBACK_ID _id);

		void Update();
	};
}
