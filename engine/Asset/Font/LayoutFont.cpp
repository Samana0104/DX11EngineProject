/*
author : 변한빛
description :
    레이아웃 폰트(텍스트가 고정된거)를 관리하는 클래스의 소스파일

version: 1.1.0
date: 2024-12-02
*/

#include "pch.h"
#include "LayoutFont.h"
using namespace HBSoft;

LayoutFont::LayoutFont(std::shared_ptr<D3Device> device, const FontDesc& desc)
    : Font(device, desc)
{
    m_text        = L"Default";
    m_textRect    = {0.f, 0.f, 0.f, 0.f};
    m_textPos     = HPoint(0.f, 0.f);
    m_isUnderline = false;

#ifdef _DEBUG
    assert(CreateLayout());
#else
    CreateLayout();
#endif
}

void LayoutFont::OnNotice(EventList event, void* entity)
{
    Font::OnNotice(event, entity);
    CreateLayout();
}

void LayoutFont::Render(std::shared_ptr<D3Device> device, const FontMsgQueue& msgQueue)
{
    device->m_2dRtv->DrawTextLayout(static_cast<const D2D1_POINT_2F>(m_textPos),
                                    m_layout.Get(),
                                    m_brush.Get());
}

bool LayoutFont::CreateLayout()
{
    if (m_layout)
        m_layout->Release();

    m_textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
    m_textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);

    HRESULT hr = m_writeFactory->CreateTextLayout(m_text.data(),          // 텍스트
                                                  (UINT32)m_text.size(),  // 텍스트 길이
                                                  m_textFormat.Get(),     // 텍스트 포맷
                                                  FLT_MAX,                // 너비
                                                  FLT_MAX,                // 높이
                                                  m_layout.GetAddressOf());

    if (FAILED(hr))
        return false;

    SetUnderline(m_isUnderline);
    SetHorizontalAlignment(m_horizontalAlign);
    SetVerticalAlignment(m_verticalAlign);
    return true;
}

void LayoutFont::SetText(const wstringV text)
{
    m_text = text;
    CreateLayout();
}

void LayoutFont::SetRect(const HRect& rect)
{
    m_textRect = rect;

    SetHorizontalAlignment(m_horizontalAlign);
    SetVerticalAlignment(m_verticalAlign);
}

void LayoutFont::SetUnderline(bool isUnderline)
{
    m_isUnderline = isUnderline;

    DWRITE_TEXT_RANGE textRange = {0, (UINT32)m_text.size()};
    m_layout->SetUnderline(m_isUnderline, textRange);
}

void LayoutFont::SetHorizontalAlignment(DWRITE_PARAGRAPH_ALIGNMENT horizontalAlign)
{
    DWRITE_TEXT_METRICS textMetrics = {};

    m_horizontalAlign = horizontalAlign;
    m_layout->GetMetrics(&textMetrics);

    switch (horizontalAlign)
    {
    case DWRITE_PARAGRAPH_ALIGNMENT_CENTER:
        m_textPos.y = (m_textRect.bottom + m_textRect.top) * 0.5f - textMetrics.height * 0.5f;
        break;
    case DWRITE_PARAGRAPH_ALIGNMENT_NEAR:
        m_textPos.y = m_textRect.top;
        break;

    case DWRITE_PARAGRAPH_ALIGNMENT_FAR:
        m_textPos.y = m_textRect.bottom - textMetrics.height;
        break;
    }
}

void LayoutFont::SetVerticalAlignment(DWRITE_TEXT_ALIGNMENT verticalAlign)
{
    DWRITE_TEXT_METRICS textMetrics = {};

    m_layout->GetMetrics(&textMetrics);
    m_verticalAlign = verticalAlign;

    switch (verticalAlign)
    {
    case DWRITE_TEXT_ALIGNMENT_CENTER:
        m_textPos.x = (m_textRect.left + m_textRect.right) * 0.5f - textMetrics.width * 0.5f;
        break;

    case DWRITE_TEXT_ALIGNMENT_LEADING:
        m_textPos.x = m_textRect.left;
        break;

    case DWRITE_TEXT_ALIGNMENT_TRAILING:
        m_textPos.x = m_textRect.right - textMetrics.width;
        break;
    }
}

void LayoutFont::DrawMsg()
{
    FontMsgQueue msgQueue;
    msgQueue.font = this;
    msgQueue.msg;

    m_msgQueue.push(msgQueue);
}
