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

        std::map<UINT, HRect> m_debugRect;

    public:
        ~FontHandler();

        bool CreateFontResource(const FONT_KEY _key, const FontDesc& _desc);
        void DrawTextAsKey(FONT_KEY _key, wstringV _msg, HRect _rect, COLOR_F _color);
        bool LoadExternalFont(const wstringV _fontPath);
        void LoadExternalFontsAsFolder(const wstringV _fontFolder);
    };
}  // namespace HBSoft
