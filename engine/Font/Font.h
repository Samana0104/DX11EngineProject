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

    class Font
    {
    private:
        ComPtr<IDWriteFactory>       m_writeFactory;
        ComPtr<IDWriteTextFormat>    m_textFormat;
        ComPtr<ID2D1SolidColorBrush> m_brush;

        FontDesc          m_fontDesc;
        D2D1_MATRIX_3X2_F m_tempMat;

        std::shared_ptr<D3Device> m_device;

        inline static std::set<wstringV> m_loadedFonts;

    public:
        Transform2D m_transform;  // 혹시 회전할 일 있으면 추가하려함

    private:
        bool CreateFontComponent();
        bool CreateDWriteFactory();
        bool CreateTextFormat();
        bool CreateBrush();

        void OnWm_size(UINT weight, UINT height);

    public:
        Font(std::shared_ptr<D3Device> device, const FontDesc& desc);
        ~Font();

        void DrawTexts(const wstringV msg, HRect rect, COLOR_F color);

        const ComPtr<ID2D1SolidColorBrush>& GetBrush() const;

        void  SetBold(bool bold);
        float GetFontSize() const;
        vec2  GetTextSize(const wstringV text) const;

        static void AddExternalFont(const wstringV path);
    };
}  // namespace HBSoft
