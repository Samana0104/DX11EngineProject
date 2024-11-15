/*
author : 변한빛
description : 폰트 리소스를 정의하기 위해 만든 헤더 파일

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include "pch.h"
#include "Transform2D.h"

namespace HBSoft
{
    struct FontDesc
    {
        std::wstring        m_fontName;
        std::wstring        m_fontLocaleName;
        FLOAT               m_fontSize;
        DWRITE_FONT_WEIGHT  m_fontWeight;
        DWRITE_FONT_STYLE   m_fontStyle;
        DWRITE_FONT_STRETCH m_fontStretch;
    };

    class Font : public Observer
    {
    private:
        ComPtr<IDWriteFactory>       m_writeFactory;
        ComPtr<IDWriteTextFormat>    m_textFormat;
        ComPtr<ID2D1SolidColorBrush> m_brush;
        ComPtr<ID2D1RenderTarget>    m_d2dRT;
        ComPtr<ID2D1Factory>         m_d2dFactory;

        FontDesc m_fontDesc;

    public:
        Transform2D m_transform;  // 혹시 회전할 일 있으면 추가하려함

    private:
        bool CreateFontComponent(std::shared_ptr<D3Device>& device);
        bool Create2DRenderTarget(std::shared_ptr<D3Device>& device);
        bool CreateDWriteFactory();
        bool CreateTextFormat();
        bool CreateBrush();

        virtual void OnNotice(void* entity);

    public:
        Font(std::shared_ptr<D3Device>& device, const FontDesc& desc);
        virtual ~Font();

        void DrawTexts(const wstringV msg, HRect rect, COLOR_F color);

        const ComPtr<ID2D1SolidColorBrush>& GetBrush() const;

        void  SetBold(bool bold);
        float GetFontSize() const;
        vec2  GetTextSize(const wstringV text) const;
    };
}  // namespace HBSoft
