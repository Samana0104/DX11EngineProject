#include "pch.h"
#include "Button.h"
using namespace HBSoft;

Button::Button()
{
    m_onMouseMoveID = m_input.RegisterCallBackOnMouseMove(
    std::bind(&Button::OnMouseMove, this, std::placeholders::_1, std::placeholders::_2));

    m_onMousePushID = m_input.RegisterCallBackOnMousePush(
    std::bind(&Button::OnMousePush, this, std::placeholders::_1, std::placeholders::_2));

    m_onMouseUpID = m_input.RegisterCallBackOnMouseUP(
    std::bind(&Button::OnMouseUp, this, std::placeholders::_1, std::placeholders::_2));
}

Button::~Button()
{
    m_input.DeleteCallBack(m_onMouseMoveID);
    m_input.DeleteCallBack(m_onMousePushID);
    m_input.DeleteCallBack(m_onMouseUpID);
}

SelectState Button::GetCurrentState() const
{
    return m_currentState;
}

void Button::SetMovable(bool _isMovable)
{
    m_isMovable = _isMovable;
}

void Button::SetDisable(bool _isDisable)
{
    m_isDisable = _isDisable;
}

void Button::SetSelectedBtn(std::function<void()> _func)
{
    mCallSelectedBtn = _func;
}

void Button::SetCurrentState(SelectState _state)
{
    m_currentState = _state;

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
    if (m_isDisable)
        return;

    vec2 toFloatPost   = {static_cast<float>(_postPos.x), static_cast<float>(_postPos.y)};
    vec2 cartesianPost = Transform2D::PixelToCartesian(toFloatPost);

    if (m_currentState == SelectState::ACTIVE)
    {
        if (m_isMovable)
        {
            vec2 toFloatPre   = {static_cast<float>(_prePos.x), static_cast<float>(_prePos.y)};
            vec2 cartesianPre = Transform2D::PixelToCartesian(toFloatPre);
            vec2 offPre       = m_transform.GetLocation() - cartesianPre;

            m_transform.AddLocation(cartesianPost - cartesianPre);
            // m_transform.AddLocation(offPre);
        }
    }

    if (CollisionComponent::IsPointInRect(m_transform.GetCartesianRectF(), cartesianPost))
    {
        if (m_currentState == SelectState::DEFAULT || m_currentState == SelectState::FOCUS)
        {
            m_currentState = SelectState::HOVER;
            return;
        }
    }
    else
    {
        if (m_currentState == SelectState::HOVER)
        {
            m_currentState = SelectState::DEFAULT;
            return;
        }
    }
}

void Button::OnMousePush(vec2 _pos, MOUSE_FLAGS _flag)
{
    if (m_isDisable)
        return;

    vec2 cartesianMousePos = Transform2D::PixelToCartesian(_pos);
    if (CollisionComponent::IsPointInRect(m_transform.GetCartesianRectF(), cartesianMousePos))
    {
        if (m_input.GetLBState() == KeyState::KEY_DOWN)
            m_currentState = SelectState::ACTIVE;
    }
}

void Button::OnMouseUp(vec2 _pos, MOUSE_FLAGS _flag)
{
    if (m_isDisable)
        return;

    vec2 cartesianMousePos = Transform2D::PixelToCartesian(_pos);

    if (m_currentState == SelectState::ACTIVE)
    {
        if (CollisionComponent::IsPointInRect(m_transform.GetCartesianRectF(), cartesianMousePos))
        {
            m_currentState = SelectState::SELECTED;
        }
        else
        {
            m_currentState = SelectState::FOCUS;
        }
    }
}

void Button::SetDefaultMode()
{
    // SetTextureKey(L"btn_default.png");
}

void Button::SetHoverMode()
{
    // SetTextureKey(L"btn_hover.png");
}

void Button::SetFocusMode()
{
    // SetTextureKey(L"btn_focus.png");
}

void Button::SetActiveMode()
{
    // SetTextureKey(L"btn_active.png");
}

void Button::SetSelectedMode()
{
    // SetTextureKey(L"btn_selected.png");
    if (mCallSelectedBtn != nullptr)
        mCallSelectedBtn();
}

void Button::Update(const float _deltaTime)
{
    SetCurrentState(m_currentState);
}

void Button::Render()
{
    Object2D::Render();
}
