#include "pch.h"
#include "Button.h"
using namespace HBSoft;

Button::Button()
{
	mOnMouseMoveID = mInput.RegisterCallBackOnMouseMove(
		std::bind(
			&Button::OnMouseMove,
			this,
			std::placeholders::_1,
			std::placeholders::_2
		));

	mOnMousePushID = mInput.RegisterCallBackOnMousePush(
		std::bind(
			&Button::OnMousePush,
			this,
			std::placeholders::_1,
			std::placeholders::_2
		));

	mOnMouseUpID = mInput.RegisterCallBackOnMouseUP(
		std::bind(
			&Button::OnMouseUp,
			this,
			std::placeholders::_1,
			std::placeholders::_2
		));

}

Button::~Button()
{
	mInput.DeleteCallBack(mOnMouseMoveID);
	mInput.DeleteCallBack(mOnMousePushID);
	mInput.DeleteCallBack(mOnMouseUpID);
}

SelectState Button::GetCurrentState() const
{
	return mCurrentState;
}

void Button::SetMovable(bool _isMovable)
{
	mIsMovable = _isMovable;
}

void Button::SetDisable(bool _isDisable)
{
	mIsDisable = _isDisable;
}

void Button::SetSelectedBtn(std::function<void()> _func)
{
	mCallSelectedBtn = _func;
}

void Button::SetCurrentState(SelectState _state)
{
	mCurrentState = _state;

	switch (_state)
	{
	case SelectState::DEFAULT:
		SetDefaultMode();
		break;

	case SelectState::HOVER:
		SetHoverMode();
		break;

	case SelectState::FOCUS:
		SetFocusMode();
		break;

	case SelectState::ACTIVE:
		SetActiveMode();
		break;

	case SelectState::SELECTED:
		SetSelectedMode();
		break;
	}
}

void Button::OnMouseMove(POINT_L _prePos, POINT_L _postPos)
{
	if (mIsDisable)
		return;

	vec2 toFloatPost = { static_cast<float>(_postPos.x), static_cast<float>(_postPos.y) };
	vec2 cartesianPost = Transform2D::PixelToCartesian(toFloatPost);
		
	if (mCurrentState == SelectState::ACTIVE)
	{
		if (mIsMovable)
		{
			vec2 toFloatPre = { static_cast<float>(_prePos.x), static_cast<float>(_prePos.y) };
			vec2 cartesianPre = Transform2D::PixelToCartesian(toFloatPre);
			vec2 offPre = mTransform.GetLocation()-cartesianPre;

			mTransform.AddLocation(cartesianPost-cartesianPre);
			//mTransform.AddLocation(offPre);
		}
	}

	if(CollisionComponent::IsPointInRect(
		mTransform.GetCartesianRectF(), cartesianPost))
	{ 
		if (mCurrentState == SelectState::DEFAULT || mCurrentState == SelectState::FOCUS )
		{
			mCurrentState = SelectState::HOVER;
			return;
		}
	}
	else
	{
		if (mCurrentState == SelectState::HOVER)
		{
			mCurrentState = SelectState::DEFAULT;
			return;
		}
	}
}

void Button::OnMousePush(vec2 _pos, MOUSE_FLAGS _flag)
{
	if (mIsDisable)
		return;

	vec2 cartesianMousePos = Transform2D::PixelToCartesian(_pos);
	if(CollisionComponent::IsPointInRect(
		mTransform.GetCartesianRectF(), cartesianMousePos))
	{ 
		if (mInput.GetLBState() == KeyState::KEY_DOWN)
			mCurrentState = SelectState::ACTIVE;
	}
}

void Button::OnMouseUp(vec2 _pos, MOUSE_FLAGS _flag)
{
	if (mIsDisable)
		return;

	vec2 cartesianMousePos = Transform2D::PixelToCartesian(_pos);

	if (mCurrentState == SelectState::ACTIVE)
	{
		if(CollisionComponent::IsPointInRect(
			mTransform.GetCartesianRectF(), cartesianMousePos))
		{ 
			mCurrentState = SelectState::SELECTED;
		}
		else
		{
			mCurrentState = SelectState::FOCUS;
		}
	}
}

void Button::SetDefaultMode()
{
	//SetTextureKey(L"btn_default.png");
}

void Button::SetHoverMode()
{
	//SetTextureKey(L"btn_hover.png");
}

void Button::SetFocusMode()
{
	//SetTextureKey(L"btn_focus.png");
}

void Button::SetActiveMode()
{
	//SetTextureKey(L"btn_active.png");
}

void Button::SetSelectedMode()
{
	//SetTextureKey(L"btn_selected.png");
	if(mCallSelectedBtn != nullptr)
		mCallSelectedBtn();
}

void Button::Update(const float _deltaTime)
{
	SetCurrentState(mCurrentState);
}

void Button::Render()
{
	Object::Render();
}
