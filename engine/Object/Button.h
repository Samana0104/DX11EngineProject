#pragma once
#include "Object.h"
#include "CollisionComponent.h"

namespace HBSoft
{
	enum SelectState
	{
		DEFAULT = 0,  // Ŀ���� ���� ���� ��(T_FOCUS���¿��� �ٸ� ���� T_ACTIVE�ϸ� ��ȯ�ȴ�.)
		HOVER = 1,	// Ŀ���� ���� ���� ��
		FOCUS = 2,	// T_ACTIVE���¿��� ���� ��ư�� �ٸ� ������ ������ ��(���)
		ACTIVE = 3,	// ���콺 ���� ��ư ������ ���� ��
		SELECTED = 4, // T_ACTIVE ���¿��� ���ʹ�ư ������ ��
	};

	class Button : public Object
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
		Button();
		virtual ~Button();

		SelectState GetCurrentState() const;
		void SetCurrentState(SelectState _state);
		void SetMovable(bool _isMovable);
		void SetDisable(bool _isDisable);
		void SetSelectedBtn(std::function<void()> _func);

		virtual void Update(const float _deltaTime) override;
		virtual void Render() override;
	};
}

