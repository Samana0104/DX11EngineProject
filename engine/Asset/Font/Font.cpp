/*
author : 변한빛
description : 폰트 리소스를 정의하기 위해 만든 소스 파일

version: 1.0.2
date: 2024-11-07
*/

#include "pch.h"
#include "Font.h"
using namespace HBSoft;

Font::Font(std::shared_ptr<D3Device> device, const FontDesc& desc)
    : m_fontDesc(desc)
{
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

    m_writeFactory->Release();
    m_textFormat->Release();
    m_brush->Release();

    assert(CreateComponent(device));
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

    return SUCCEEDED(hr);
}

bool Font::CreateBrush(const D3Device* device)
{
    COLOR_F color = {1.f, 1.f, 1.f, 1.f};
    HRESULT hr    = device->m_2dRtv->CreateSolidColorBrush(color, m_brush.GetAddressOf());
    return SUCCEEDED(hr);
}

void Font::DrawGeneralText(std::shared_ptr<D3Device> device, const wstringV msg, HRect rect,
                           DWRITE_TEXT_ALIGNMENT align)
{
    m_textFormat->SetTextAlignment(align);
    device->m_2dRtv->BeginDraw();
    device->m_2dRtv->DrawText(msg.data(),
                              static_cast<UINT32>(msg.size()),
                              m_textFormat.Get(),
                              static_cast<const D2D1_RECT_F>(rect),
                              m_brush.Get());
    device->m_2dRtv->EndDraw();
}

void Font::DrawUnderlineText(std::shared_ptr<D3Device> device, const wstringV msg, HRect rect)
{
    ComPtr<IDWriteTextLayout> textLayout;

    device->m_2dRtv->BeginDraw();
    HRESULT hr = m_writeFactory->CreateTextLayout(msg.data(),              // 텍스트
                                                  (UINT32)msg.size(),      // 텍스트 길이
                                                  m_textFormat.Get(),      // 텍스트 포맷
                                                  rect.right - rect.left,  // 너비
                                                  rect.bottom - rect.top,  // 높이
                                                  &textLayout              // 출력 레이아웃
    );

    if (FAILED(hr))
        return;

    DWRITE_TEXT_RANGE textRange = {0, (UINT32)msg.size()};  // 전체 텍스트 범위
    textLayout->SetUnderline(TRUE, textRange);

    device->m_2dRtv->DrawTextLayout({rect.left, rect.top}, textLayout.Get(), m_brush.Get());
    device->m_2dRtv->EndDraw();
}

void Font::SetColor(const COLOR_F& color)
{
    if (m_brush != nullptr)
        m_brush->SetColor(color);
}

void Font::SetBold(bool bold)
{
    if (bold)
    {
        m_textFormat->Release();
        m_fontDesc.m_fontWeight = DWRITE_FONT_WEIGHT_BOLD;
        CreateTextFormat();
    }
    else
    {
        m_textFormat->Release();
        m_fontDesc.m_fontWeight = DWRITE_FONT_WEIGHT_NORMAL;
        CreateTextFormat();
    }
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
