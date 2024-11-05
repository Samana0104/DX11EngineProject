/*
author : ���Ѻ�
description : ��Ʈ ���ҽ��� �����ϱ� ���� ���� ��� ����

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
        ComPtr<IDWriteFactory>       m_writeFactory;
        ComPtr<IDWriteTextFormat>    m_textFormat;
        ComPtr<ID2D1SolidColorBrush> m_brush;

        FontDesc          m_fontDesc;
        D2D1_MATRIX_3X2_F m_tempMat;

    public:
        Transform2D m_transform;

    private:
        bool CreateFontComponent();
        bool CreateDWriteFactory();
        bool CreateTextFormat();
        bool CreateBrush();

        void OnWm_size(UINT weight, UINT height);

    public:
        Font(const FontDesc& _desc);
        ~Font();

        void DrawTexts(const wstringV msg, HRect rect, COLOR_F color);

        const ComPtr<ID2D1SolidColorBrush>& GetBrush() const;

        void SetBold(bool bold);

        float GetFontSize() const;
        vec2  GetTextSize(const wstringV _text) const;
    };
}  // namespace HBSoft
