/*
author : 변한빛, 이지혁
description : GUI 버튼을 정의하기 위한 소스 파일
              v1.0.6 사운드 추가 (이지혁)

version: 1.0.6
date: 2024-11-30
*/

#include "pch.h"
#include "Button.h"
using namespace HBSoft;

Button::Button()
{
    FontDesc desc;
    {
        desc.m_fontName       = L"NotoSansCJKkr-Bold";
        desc.m_fontLocaleName = L"ko-kr";
        desc.m_fontSize       = 35.f;
        desc.m_fontStretch    = DWRITE_FONT_STRETCH_NORMAL;
        desc.m_fontStyle      = DWRITE_FONT_STYLE_NORMAL;
        desc.m_fontWeight     = DWRITE_FONT_WEIGHT_EXTRA_BOLD;
    }
    m_font = FontFactory::CreateLayoutFont(HDEVICE, desc);
    m_font->SetHorizontalAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    m_font->SetVerticalAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

    m_boxMesh = MeshFactory::Create(HDEVICE, MeshShape::BOX2D);
    m_state   = ButtonState::DEFAULT;
    m_texture = nullptr;
    m_clickSound = HASSET->m_sounds[L"uiMouseClick.wav"];
    m_easyRender.SetVSShader(L"2DBasicVS.hlsl");
    m_easyRender.SetPSShader(L"2DBasicPS.hlsl");
    m_easyRender.SetDSS(ERDepthStencilState::DISABLE);
    m_easyRender.SetMesh(m_boxMesh);
    m_easyRender.SetSS(ERSamplerState::LINEAR);

    EventHandler::GetInstance().AddEvent(EventList::DEVICE_CHANGE, this);
}

Button::~Button()
{
    EventHandler::GetInstance().DeleteEvent(EventList::DEVICE_CHANGE, this);
}

void Button::SetArea(const HRect& rect)
{
    HPoint windowSize = HWINDOW->GetWindowSize();

    HPoint v1 = Transform2D::ConvertScreenToNDC(windowSize, {rect.left, rect.top});
    HPoint v2 = Transform2D::ConvertScreenToNDC(windowSize, {rect.right, rect.top});
    HPoint v3 = Transform2D::ConvertScreenToNDC(windowSize, {rect.right, rect.bottom});
    HPoint v4 = Transform2D::ConvertScreenToNDC(windowSize, {rect.left, rect.bottom});

    m_collisionArea = {v1.x, v1.y, v3.x, v3.y};

    m_boxMesh->m_vertices[0].p.x = v1.x;
    m_boxMesh->m_vertices[0].p.y = v1.y;
    m_boxMesh->m_vertices[0].c   = {1.f, 1.f, 1.f, 1.f};

    m_boxMesh->m_vertices[1].p.x = v2.x;
    m_boxMesh->m_vertices[1].p.y = v2.y;
    m_boxMesh->m_vertices[1].c   = {1.f, 1.f, 1.f, 1.f};

    m_boxMesh->m_vertices[2].p.x = v3.x;
    m_boxMesh->m_vertices[2].p.y = v3.y;
    m_boxMesh->m_vertices[2].c   = {1.f, 1.f, 1.f, 1.f};

    m_boxMesh->m_vertices[3].p.x = v4.x;
    m_boxMesh->m_vertices[3].p.y = v4.y;
    m_boxMesh->m_vertices[3].c   = {1.f, 1.f, 1.f, 1.f};

    m_boxMesh->UpdateVertices(HDEVICE);
    m_font->SetRect(rect);
}

void Button::SetImage(const TEXTURE_KEY textureKey)
{
    m_texture = HASSET->m_textures[textureKey];
    m_easyRender.SetTexture(m_texture);
}

void Button::SetOnClickCallback(std::function<void()> callback)
{
    m_onClickCallback = callback;
}

void Button::SetText(const wstringV text, const COLOR_F& color)
{
    m_font->SetColor(color);
    m_font->SetText(text);
}

bool Button::IsCursorInRect()
{
    HPoint cursorPos = HINPUT->GetNDCMousePos();

    if (m_collisionArea.left <= cursorPos.x && m_collisionArea.top >= cursorPos.y &&
        m_collisionArea.right >= cursorPos.x && m_collisionArea.bottom <= cursorPos.y)
        return true;

    return false;
}

void Button::Update(const float deltaTime)
{
    m_state = ButtonState::DEFAULT;

    if (IsCursorInRect())
    {
        /*if (!m_hoverSound->IsPlaying())
        {
            m_hoverSound->Play();
        }*/

        if (HINPUT->IsKeyDown(VK_LBUTTON))
        {
            m_clickSound->Play();
        }

        SetCursor(LoadCursor(nullptr, IDC_HAND));
        m_font->SetUnderline(true);

        if (HINPUT->IsKeyUp(VK_LBUTTON))
        {
            m_state = ButtonState::SELECTED;
            m_onClickCallback();
        }
        else
        {
            m_state = ButtonState::HOVER;
        }
    }
    else
    {
        m_font->SetUnderline(false);
    }

    UpdateDefaultCB();
}

void Button::Render()
{
    m_easyRender.Draw();
    m_font->DrawMsg();
}

void Button::Release() {}

void Button::Init() {}

void Button::OnNotice(EventList event, void* entity)
{
    HPoint windowSize = HWINDOW->GetWindowSize();
    HRect  textRect;

    textRect = Transform2D::ConvertNDCToScreen(windowSize, m_collisionArea);

    m_font->SetRect(textRect);
}
