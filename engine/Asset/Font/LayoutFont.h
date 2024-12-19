/*
author : 변한빛
description :
    레이아웃 폰트(텍스트가 고정된거)를 관리하는 클래스의 헤더파일

version: 1.1.0
date: 2024-12-02
*/

#pragma once

#include "Font\Font.h"

namespace HBSoft
{
    class LayoutFont : public Font
    {
    private:
        std::wstring m_text;
        bool         m_isUnderline;

        HRect  m_textRect;
        HPoint m_textPos;

        ComPtr<IDWriteTextLayout> m_layout;


    private:
        bool CreateLayout();

        virtual void OnNotice(EventList event, void* entity) override;
        virtual void Render(std::shared_ptr<D3Device> device, const FontMsgQueue& msgQueue) override;

    public:
        LayoutFont(std::shared_ptr<D3Device> device, const FontDesc& desc);

        void SetText(const wstringV text);
        void SetUnderline(bool isUnderline);

        void DrawMsg();

        virtual void SetHorizontalAlignment(DWRITE_PARAGRAPH_ALIGNMENT horizontalAlign) override;
        virtual void SetVerticalAlignment(DWRITE_TEXT_ALIGNMENT verticalAlign) override;
        virtual void SetRect(const HRect& rect) override;
    };
}  // namespace HBSoft
