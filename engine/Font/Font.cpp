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
    : m_device(device), m_fontDesc(desc)
{
    assert(CreateFontComponent());
}

Font::~Font() {}

void Font::OnWm_size(UINT _weight, UINT _height)
{
    m_writeFactory->Release();
    m_textFormat->Release();
    m_brush->Release();

    CreateFontComponent();
}

bool Font::CreateFontComponent()
{
    if (!CreateDWriteFactory())
        return false;

    if (!CreateBrush())
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

bool Font::CreateBrush()
{
    COLOR_F color = {1.f, 1.f, 1.f, 1.f};
    HRESULT hr    = m_device->m_d2dRT->CreateSolidColorBrush(color, m_brush.GetAddressOf());
    return SUCCEEDED(hr);
}

void Font::DrawTexts(const wstringV msg, HRect rect, COLOR_F color)
{
    m_device->m_d2dRT->BeginDraw();
    m_brush->SetColor(color);
    // m_device.m_d2dRT->DrawRectangle(rc, mDefaultColor.Get());
    // m_device.m_d2dRT->DrawText(_msg.data(), _msg.size(), mWriteFont.Get(),&rc, mDefaultColor.Get());
    // m_device.m_d2dRT->SetTransform(D2D1::Matrix3x2F::Rotation(-10.f));
    m_device->m_d2dRT->DrawText(msg.data(),
                                static_cast<UINT32>(msg.size()),
                                m_textFormat.Get(),
                                static_cast<const D2D1_RECT_F>(rect),
                                m_brush.Get());
    m_device->m_d2dRT->EndDraw();
}

const ComPtr<ID2D1SolidColorBrush>& Font::GetBrush() const
{
    return m_brush;
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

float Font::GetFontSize() const
{
    return m_fontDesc.m_fontSize;
}

vec2 Font::GetTextSize(const wstringV text) const
{
    ComPtr<IDWriteTextLayout> textLayout;
    DWRITE_TEXT_METRICS       textMetrics;

    m_writeFactory->CreateTextLayout(text.data(),
                                     static_cast<UINT32>(text.size()),
                                     m_textFormat.Get(),
                                     FLT_MAX,  // Max width
                                     FLT_MAX,  // Max height
                                     textLayout.GetAddressOf());

    textLayout->GetMetrics(&textMetrics);

    return {textMetrics.width, textMetrics.height};
}

void Font::AddExternalFont(const wstringV path)
{
    if (!m_loadedFonts.contains(path))
    {
        AddFontResourceEx(path.data(), FR_PRIVATE, 0);
        m_loadedFonts.insert(path);
    }
}
