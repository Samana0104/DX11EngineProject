/*
author : 변한빛
description : 외부 폰트 관리 및 폰트를 생성하는 헤더파일

version: 1.0.4
date: 2024-12-02
*/
#pragma once

#include "pch.h"
#include "Font/Font.h"
#include "Font/LayoutFont.h"

namespace HBSoft
{
    class FontFactory
    {
    private:
        inline static std::set<wstringV> m_loadedFonts;

    public:
        static void RegisterExternalFont(const wstringV fontPath);
        static void ClearExternalAllFonts();

        static std::shared_ptr<Font>       CreateFontFromDesc(std::shared_ptr<D3Device> device,
                                                              const FontDesc&           desc);
        static std::shared_ptr<LayoutFont> CreateLayoutFont(std::shared_ptr<D3Device> device,
                                                            const FontDesc&           desc);

        static bool IsFontFormat(const wstringV ext);
    };
}  // namespace HBSoft
