/*
author : 변한빛
description : 폰트 리소스를 정의하기 위해 만든 헤더 파일

version: 1.1.0
date: 2024-12-02
*/

#pragma once
#include "pch.h"

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

    class Font;

    struct FontMsgQueue
    {
        Font*    font;
        wstringV msg;
    };

    class Font : public Observer
    {
    protected:
        ComPtr<IDWriteFactory>       m_writeFactory;
        ComPtr<IDWriteTextFormat>    m_textFormat;
        ComPtr<ID2D1SolidColorBrush> m_brush;

        FontDesc m_fontDesc;

        DWRITE_PARAGRAPH_ALIGNMENT m_horizontalAlign;
        DWRITE_TEXT_ALIGNMENT      m_verticalAlign;
        COLOR_F                    m_color;
        HRect                      m_textRect;

        inline static std::queue<FontMsgQueue> m_msgQueue;

    protected:
        bool CreateComponent(const D3Device* device);  // 이벤트에서 디바이스 넘길려고 포인터로 바꿈
        bool CreateDWriteFactory();
        bool CreateTextFormat();
        bool CreateBrush(const D3Device* device);

        virtual void OnNotice(EventList event, void* entity) override;
        virtual void Render(std::shared_ptr<D3Device> device, const FontMsgQueue& msgQueue);

    public:
        Font(std::shared_ptr<D3Device> device, const FontDesc& desc);
        virtual ~Font();

        void DrawMsg(const wstringV msg);
        void SetColor(const COLOR_F& color);

        void ResetComponent(const D3Device* device);

        virtual void SetHorizontalAlignment(DWRITE_PARAGRAPH_ALIGNMENT horizontalAlign);
        virtual void SetVerticalAlignment(DWRITE_TEXT_ALIGNMENT verticalAlign);
        virtual void SetRect(const HRect& rect);

        static void ProcessQueue(std::shared_ptr<D3Device> device);

        const FontDesc& GetDesc() const;
    };
}  // namespace HBSoft
