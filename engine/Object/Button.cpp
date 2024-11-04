/*
author : 변한빛
description : GUI 버튼을 정의하기 위한 소스 파일 오브젝트2D를 상속하여 구현 한다.

version: 1.0.0
date: 2024-11-04
*/

#include "pch.h"
#include "Button.h"
using namespace HBSoft;

Button::Button() {}

Button::~Button() {}

SelectState Button::GetState() const
{
    return m_state;
}

void Button::SetMovable(bool isMovable)
{
    m_isMovable = isMovable;
}

void Button::SetDisable(bool isDisable)
{
    m_isDisable = isDisable;
}

void Button::SetState(SelectState state)
{
    m_state = state;

    switch (state)
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

void Button::SetSelectedMode() {}

void Button::Update(const float _deltaTime)
{
    SetState(m_state);
}

void Button::Render()
{
    Object2D::Render();
}
