#include "pch.h"
#include "MyButton.h"
using namespace MyProject;

MyButton::MyButton()
{
	mOnMouseMoveID = mInput.RegisterCallBackOnMouseMove(
		std::bind(
			&MyButton::OnMouseMove,
			this,
			std::placeholders::_1,
			std::placeholders::_2
		));

	mOnMousePushID = mInput.RegisterCallBackOnMousePush(
		std::bind(
			&MyButton::OnMousePush,
			this,
			std::placeholders::_1,
			std::placeholders::_2
		));

	mOnMouseUpID = mInput.RegisterCallBackOnMouseUP(
		std::bind(
			&MyButton::OnMouseUp,
			this,
			std::placeholders::_1,
			std::placeholders::_2
		));

}

MyButton::~MyButton()
{
	mInput.DeleteCallBack(mOnMouseMoveID);
	mInput.DeleteCallBack(mOnMousePushID);
	mInput.DeleteCallBack(mOnMouseUpID);
}

SelectState MyButton::GetCurrentState() const
{
	return mCurrentState;
}

void MyButton::SetMovable(bool _isMovable)
{
	mIsMovable = _isMovable;
}

void MyButton::SelectMouseState(SelectState _state)
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

void MyButton::OnMouseMove(POINT_L _prePos, POINT_L _postPos)
{
	vec2 toFloatPost = { static_cast<float>(_postPos.x), static_cast<float>(_postPos.y) };
	vec2 cartesianPost = MyTransformer2D::PixelToCartesian(toFloatPost);
		
	if (mCurrentState == SelectState::ACTIVE)
	{
		if (mIsMovable)
		{
			vec2 toFloatPre = { static_cast<float>(_prePos.x), static_cast<float>(_prePos.y) };
			vec2 cartesianPre = MyTransformer2D::PixelToCartesian(toFloatPre);
			vec2 offPre = mTransform.GetLocation()-cartesianPre;

			mTransform.SetLocation(cartesianPost);
			mTransform.AddLocation(offPre);
		}
	}

	if(CollisionComponent::IsPointInRect(
		mTransform.GetCartesianRectF(), cartesianPost))
	{ 
		if (mCurrentState == SelectState::DEFAULT)
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

void MyButton::OnMousePush(vec2 _pos, MOUSE_FLAGS _flag)
{
	vec2 cartesianMousePos = MyTransformer2D::PixelToCartesian(_pos);
	if(CollisionComponent::IsPointInRect(
		mTransform.GetCartesianRectF(), cartesianMousePos))
	{ 
		if (mInput.GetLBState() == KeyState::KEY_DOWN)
			mCurrentState = SelectState::ACTIVE;
	}
}

void MyButton::OnMouseUp(vec2 _pos, MOUSE_FLAGS _flag)
{
	if (mCurrentState == SelectState::ACTIVE)
	{
		mCurrentState = SelectState::DEFAULT;
		return;
	}
}

void MyButton::SetDefaultMode()
{
	SetTextureKey(L"main_start_1.png");
}

void MyButton::SetHoverMode()
{
	SetTextureKey(L"main_start_2.png");
}

void MyButton::SetFocusMode()
{
	SetTextureKey(L"main_start_3.png");
}

void MyButton::SetActiveMode()
{
	SetTextureKey(L"main_start_3.png");
}

void MyButton::SetSelectedMode()
{
	SetTextureKey(L"main_start_1.png");
}

void MyButton::Update(const float _deltaTime)
{
	SelectMouseState(mCurrentState);
}

void MyButton::Render()
{
	MyObject::Render();
}
