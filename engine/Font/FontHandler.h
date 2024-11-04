/*
author : 변한빛
description : 폰트를 관리하기 위한 매니징 헤더 파일

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include "Font.h"
#include "MgrTemplate.h"

namespace HBSoft
{
    class FontHandler : public MgrTemplate<Font, FONT_KEY>
    {
    private:
        std::vector<wstringV> externalFontNames;

        std::map<UINT, RECT_F> m_debugRect;

    public:
        ~FontHandler();

        bool CreateFontResource(const FONT_KEY _key, const FontDesc& _desc);
        void DrawTextAsKey(FONT_KEY _key, wstringV _msg, RECT_F _rect, COLOR_F _color);
        bool LoadExternalFont(const wstringV _fontPath);
        void LoadExternalFontsAsFolder(const wstringV _fontFolder);

#ifdef _DEBUG
        // 직각 좌표계 기준
        void AddRectAreaForDebugging(UINT _key, RECT_F _rect);
        void DrawRectForDebugging();
        void DrawTextForDebugging(const wchar_t* format, ...);
        void DrawRectForDebugging(RECT_F& _rect);
#endif
    };
}  // namespace HBSoft
