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
        std::wstring m_fontName;
        std::wstring m_fontLocalName;
        FLOAT        m_fontSize;

        DWRITE_FONT_WEIGHT  m_fontWeight;
        DWRITE_FONT_STYLE   m_fontStyle;
        DWRITE_FONT_STRETCH m_fontStretch;
    };

    class Font
    {
    private:
        D3Device& m_device = D3Device::GetInstance();

        ComPtr<IDWriteFactory>       m_writeFactory;
        ComPtr<IDWriteTextFormat>    m_textFormat;
        ComPtr<ID2D1SolidColorBrush> m_brush;

        FontDesc          m_fontDesc;
        Transform2D       m_transform;
        D2D1_MATRIX_3X2_F m_tempMat;

    private:
        void DrawBegin();
        void DrawEnd();
        bool CreateFontComponent();
        bool CreateDWriteFactory();
        bool CreateTextFormat();
        bool CreateBrush();

        void OnWm_size(UINT weight, UINT height);

    public:
        Font(const FontDesc& _desc);
        ~Font();

        void                                DrawTexts(const wstringV _msg, RECT_F _rect, COLOR_F _color);
        const ComPtr<ID2D1SolidColorBrush>& GetBrush() const;

        void SetBold();
        bool isBold() const;

        float GetFontSize() const;
        vec2  GetTextSize(const wstringV _text) const;

        Transform2D* operator->();
    };
}  // namespace HBSoft
