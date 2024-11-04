/*
author : 변한빛
description : 폰트 리소스를 정의하기 위해 만든 소스 파일

version: 1.0.0
date: 2024-11-04
*/

#include "pch.h"
#include "Font.h"
using namespace HBSoft;

Font::Font(const FontDesc& _desc)
    : m_fontDesc(_desc)
{
#ifdef _DEBUG
    _ASSERT(CreateFontComponent());
#else
    CreateFontComponent();
#endif
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
                                                  m_fontDesc.m_fontLocalName.c_str(),
                                                  m_textFormat.GetAddressOf());

    return SUCCEEDED(hr);
}

bool Font::CreateBrush()
{
    COLOR_F color = {1.f, 1.f, 1.f, 1.f};
    HRESULT hr    = m_device.m_d2dRT->CreateSolidColorBrush(color, m_brush.GetAddressOf());
    return SUCCEEDED(hr);
}

void Font::DrawBegin()
{
    D2D1_MATRIX_3X2_F convertMat;
    mat3              trsMat = m_transform->GetViewMat();

    m_device.m_d2dRT->GetTransform(&m_tempMat);

    convertMat.m11 = trsMat[0][0];
    convertMat.m12 = trsMat[0][1];
    convertMat.m21 = trsMat[1][0];
    convertMat.m22 = trsMat[1][1];
    convertMat.dx  = trsMat[2][0];
    convertMat.dy  = trsMat[2][1];

    m_device.m_d2dRT->SetTransform(convertMat);
}

void Font::DrawEnd()
{
    m_device.m_d2dRT->SetTransform(m_tempMat);
}

void Font::DrawTexts(const wstringV _msg, RECT_F _rect, COLOR_F _color)
{
    DrawBegin();
    m_device.m_d2dRT->BeginDraw();
    m_brush->SetColor(_color);
    // m_device.m_d2dRT->DrawRectangle(rc, mDefaultColor.Get());
    // m_device.m_d2dRT->DrawText(_msg.data(), _msg.size(), mWriteFont.Get(),&rc, mDefaultColor.Get());
    // m_device.m_d2dRT->SetTransform(D2D1::Matrix3x2F::Rotation(-10.f));
    m_device.m_d2dRT->DrawText(_msg.data(),
                               static_cast<UINT32>(_msg.size()),
                               m_textFormat.Get(),
                               &_rect,
                               m_brush.Get());
    m_device.m_d2dRT->EndDraw();
    DrawEnd();
}

const ComPtr<ID2D1SolidColorBrush>& Font::GetBrush() const
{
    return m_brush;
}

void Font::SetBold()
{
    if (isBold())
    {
        m_textFormat->Release();
        m_fontDesc.m_fontWeight = DWRITE_FONT_WEIGHT_NORMAL;
        CreateTextFormat();
    }
    else
    {
        m_textFormat->Release();
        m_fontDesc.m_fontWeight = DWRITE_FONT_WEIGHT_BOLD;
        CreateTextFormat();
    }
}

bool Font::isBold() const
{
    if (m_fontDesc.m_fontWeight == DWRITE_FONT_WEIGHT_BOLD)
        return true;
    else
        return false;
}

float Font::GetFontSize() const
{
    return m_fontDesc.m_fontSize;
}

vec2 Font::GetTextSize(const wstringV _text) const
{
    ComPtr<IDWriteTextLayout> textLayout;
    DWRITE_TEXT_METRICS       textMetrics;

    m_writeFactory->CreateTextLayout(_text.data(),
                                     static_cast<UINT32>(_text.size()),
                                     m_textFormat.Get(),
                                     FLT_MAX,  // Max width
                                     FLT_MAX,  // Max height
                                     textLayout.GetAddressOf());

    textLayout->GetMetrics(&textMetrics);

    return {textMetrics.width, textMetrics.height};
}

Transform2D* Font::operator->()
{
    return &m_transform;
}
