/*
author : 변한빛
description : 폰트 리소스를 정의하기 위해 만든 소스 파일

version: 1.1.0
date: 2024-12-02
*/

#include "pch.h"
#include "Font.h"
using namespace HBSoft;

Font::Font(std::shared_ptr<D3Device> device, const FontDesc& desc)
    : m_fontDesc(desc)
{
    m_horizontalAlign = DWRITE_PARAGRAPH_ALIGNMENT_NEAR;
    m_verticalAlign   = DWRITE_TEXT_ALIGNMENT_LEADING;
    m_color           = {1.f, 1.f, 1.f, 1.f};

    assert(CreateComponent(device.get()));
    EventHandler::GetInstance().AddEvent(EventList::DEVICE_CHANGE, this);
}

Font::~Font()
{
    EventHandler::GetInstance().DeleteEvent(EventList::DEVICE_CHANGE, this);
}

void Font::OnNotice(EventList event, void* entity)
{
    D3Device* device = reinterpret_cast<D3Device*>(entity);
    ResetComponent(device);
}

bool Font::CreateComponent(const D3Device* device)
{
    if (!CreateDWriteFactory())
        return false;

    if (!CreateBrush(device))
        return false;

    if (!CreateTextFormat())
        return false;

    return true;
}

bool Font::CreateDWriteFactory()
{
    HRESULT hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
                                     __uuidof(IDWriteFactory),
                                     reinterpret_cast<IUnknown**>(m_writeFactory.GetAddressOf()));

    return SUCCEEDED(hr);
}

bool Font::CreateTextFormat()
{
    HRESULT hr = m_writeFactory->CreateTextFormat(m_fontDesc.m_fontName.c_str(),
                                                  nullptr,
                                                  m_fontDesc.m_fontWeight,
                                                  m_fontDesc.m_fontStyle,
                                                  m_fontDesc.m_fontStretch,
                                                  m_fontDesc.m_fontSize,
                                                  m_fontDesc.m_fontLocaleName.c_str(),
                                                  m_textFormat.GetAddressOf());
    if (FAILED(hr))
        return false;

    m_textFormat->SetParagraphAlignment(m_horizontalAlign);
    m_textFormat->SetTextAlignment(m_verticalAlign);
    return true;
}

bool Font::CreateBrush(const D3Device* device)
{
    HRESULT hr = device->m_2dRtv->CreateSolidColorBrush(m_color, m_brush.GetAddressOf());
    return SUCCEEDED(hr);
}

void Font::DrawMsg(std::shared_ptr<D3Device> device, const wstringV msg, HRect rect)
{
    device->m_2dRtv->DrawText(msg.data(),
                              static_cast<UINT32>(msg.size()),
                              m_textFormat.Get(),
                              static_cast<const D2D1_RECT_F>(rect),
                              m_brush.Get());
}

void Font::SetColor(const COLOR_F& color)
{
    m_color = color;
    if (m_brush != nullptr)
        m_brush->SetColor(color);
}

void Font::ResetComponent(const D3Device* device)
{
    if (m_writeFactory)
        m_writeFactory->Release();

    if (m_textFormat)
        m_textFormat->Release();

    if (m_brush)
        m_brush->Release();

    assert(CreateComponent(device));
}

void Font::SetHorizontalAlignment(DWRITE_PARAGRAPH_ALIGNMENT horizontalAlign)
{
    m_horizontalAlign = horizontalAlign;
    m_textFormat->SetParagraphAlignment(m_horizontalAlign);
}

void Font::SetVerticalAlignment(DWRITE_TEXT_ALIGNMENT verticalAlign)
{
    m_verticalAlign = verticalAlign;
    m_textFormat->SetTextAlignment(m_verticalAlign);
}

const FontDesc& Font::GetDesc() const
{
    return m_fontDesc;
}

// vec2 Font::GetTextSize(const wstringV text) const
//{
//     ComPtr<IDWriteTextLayout> textLayout;
//     DWRITE_TEXT_METRICS       textMetrics;
//
//     m_writeFactory->CreateTextLayout(text.data(),
//                                      static_cast<UINT32>(text.size()),
//                                      m_textFormat.Get(),
//                                      FLT_MAX,  // Max width
//                                      FLT_MAX,  // Max height
//                                      textLayout.GetAddressOf());
//
//     textLayout->GetMetrics(&textMetrics);
//
//     return {textMetrics.width, textMetrics.height};
// }
