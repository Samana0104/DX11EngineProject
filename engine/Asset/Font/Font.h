/*
author : 변한빛
description : 폰트 리소스를 정의하기 위해 만든 헤더 파일

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include "pch.h"
#include "2D/Transform2D.h"

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

        FontDesc m_fontDesc;

    private:
        bool CreateComponent(const D3Device* device);  // 이벤트에서 디바이스 넘길려고 포인터로 바꿈
        bool CreateDWriteFactory();
        bool CreateTextFormat();
        bool CreateBrush(const D3Device* device);

        virtual void OnNotice(EventList event, void* entity);

    public:
        Font(std::shared_ptr<D3Device> device, const FontDesc& desc);
        virtual ~Font();

        void DrawGeneralText(std::shared_ptr<D3Device> device, const wstringV msg, HRect rect,
                             DWRITE_TEXT_ALIGNMENT align);
        void DrawUnderlineText(std::shared_ptr<D3Device> device, const wstringV msg, HRect rect);
        void SetColor(const COLOR_F& color);
        void SetBold(bool bold);

        const FontDesc& GetDesc() const;
    };
}  // namespace HBSoft
