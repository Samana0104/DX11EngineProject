#pragma once
#include "MyObject.h"
#include "CollisionComponent.h"

namespace MyProject
{
	enum SelectState
	{
		DEFAULT = 0,  // 커서가 위에 없을 때(T_FOCUS상태에서 다른 곳을 T_ACTIVE하면 전환된다.)
		HOVER = 1,	// 커서가 위에 있을 때
		FOCUS = 2,	// T_ACTIVE상태에서 왼쪽 버튼을 다른 곳에서 놓았을 때(취소)
		ACTIVE = 3,	// 마우스 왼쪽 버튼 누르고 있을 때
		SELECTED = 4, // T_ACTIVE 상태에서 왼쪽버튼 놓았을 때
	};

	class MyButton : public MyObject
	{
	private:
		SelectState mCurrentState = SelectState::DEFAULT;

		bool mIsMovable = false;
		bool mIsDisable = true;

		CALLBACK_ID mOnMouseMoveID;
		CALLBACK_ID mOnMousePushID;
		CALLBACK_ID mOnMouseUpID;
		
		std::function<void()> mCallSelectedBtn;

	private:
		virtual void OnMouseMove(POINT_L _prePos, POINT_L _postPos);
		virtual void OnMousePush(vec2 _pos, MOUSE_FLAGS _flag);
		virtual void OnMouseUp(vec2 _pos, MOUSE_FLAGS _flag);
		
	protected:
		virtual void SetDefaultMode();
		virtual void SetHoverMode();
		virtual void SetFocusMode();
		virtual void SetActiveMode();
		virtual void SetSelectedMode();

	public:
		MyButton();
		virtual ~MyButton();

		SelectState GetCurrentState() const;
		void SetCurrentState(SelectState _state);
		void SetMovable(bool _isMovable);
		void SetDisable(bool _isDisable);
		void SetSelectedBtn(std::function<void()> _func);

		virtual void Update(const float _deltaTime) override;
		virtual void Render() override;
	};
}

