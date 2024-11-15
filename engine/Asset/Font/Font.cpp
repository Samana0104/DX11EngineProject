/*
author : 변한빛
description : 폰트 리소스를 정의하기 위해 만든 소스 파일

version: 1.0.2
date: 2024-11-07
*/

#include "pch.h"
#include "Font.h"
using namespace HBSoft;

Font::Font(std::shared_ptr<D3Device>& device, const FontDesc& desc)
    : m_fontDesc(desc)
{
    assert(CreateFontComponent(device));
    EventHandler::GetInstance().AddEvent(EventList::DEVICE_CHANGE, this);
}

Font::~Font()
{
    EventHandler::GetInstance().DeleteEvent(EventList::DEVICE_CHANGE, this);
}

void Font::OnNotice(void* entity)
{
    D3Device* device = reinterpret_cast<D3Device*>(entity);

    std::shared_ptr<D3Device> sharedDevice(device);

    m_writeFactory->Release();
    m_textFormat->Release();
    m_brush->Release();
    m_d2dRT->Release();
    m_d2dFactory->Release();

    CreateFontComponent(sharedDevice);
}

bool Font::CreateFontComponent(std::shared_ptr<D3Device>& device)
{
    if (!Create2DRenderTarget(device))
        return false;

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
    HRESULT hr    = m_d2dRT->CreateSolidColorBrush(color, m_brush.GetAddressOf());
    return SUCCEEDED(hr);
}

bool Font::Create2DRenderTarget(std::shared_ptr<D3Device>& device)
{
    HRESULT              hr;
    ComPtr<IDXGISurface> dxgiSurface;

    hr = device->m_swapChain->GetBuffer(0, IID_PPV_ARGS(dxgiSurface.GetAddressOf()));

    if (FAILED(hr))
        return false;

    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, m_d2dFactory.GetAddressOf());

    if (FAILED(hr))
        return false;

    D2D1_RENDER_TARGET_PROPERTIES rtp;
    {
        rtp.type                  = D2D1_RENDER_TARGET_TYPE_DEFAULT;
        rtp.pixelFormat.format    = DXGI_FORMAT_UNKNOWN;
        rtp.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
        rtp.dpiX                  = 0;
        rtp.dpiY                  = 0;
        rtp.usage                 = D2D1_RENDER_TARGET_USAGE_NONE;
        rtp.minLevel              = D2D1_FEATURE_LEVEL_DEFAULT;
    }

    hr = m_d2dFactory->CreateDxgiSurfaceRenderTarget(dxgiSurface.Get(), &rtp, m_d2dRT.GetAddressOf());

    return SUCCEEDED(hr);
}

void Font::DrawTexts(const wstringV msg, HRect rect, COLOR_F color)
{
    m_d2dRT->BeginDraw();
    m_brush->SetColor(color);
    // m_device.m_d2dRT->DrawRectangle(rc, mDefaultColor.Get());
    // m_device.m_d2dRT->DrawText(_msg.data(), _msg.size(), mWriteFont.Get(),&rc, mDefaultColor.Get());
    // m_device.m_d2dRT->SetTransform(D2D1::Matrix3x2F::Rotation(-10.f));
    m_d2dRT->DrawText(msg.data(),
                      static_cast<UINT32>(msg.size()),
                      m_textFormat.Get(),
                      static_cast<const D2D1_RECT_F>(rect),
                      m_brush.Get());
    m_d2dRT->EndDraw();
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
