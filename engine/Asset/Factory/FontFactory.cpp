/*
author : 변한빛
description : 외부 폰트 관리 및 폰트를 생성하는 소스파일

version: 1.0.0
date: 2024-11-17
*/
#include "pch.h"
#include "FontFactory.h"
using namespace HBSoft;

void FontFactory::RegisterExternalFont(const wstringV fontPath)
{
    if (!m_loadedFonts.contains(fontPath))
    {
        AddFontResourceEx(fontPath.data(), FR_PRIVATE, 0);
        m_loadedFonts.insert(fontPath);
    }
}

void FontFactory::ClearExternalAllFonts()
{
    for (auto& font : m_loadedFonts)
        RemoveFontResourceEx(font.data(), FR_PRIVATE, 0);
}

std::shared_ptr<Font> FontFactory::CreateFontFromDesc(std::shared_ptr<D3Device> device,
                                                      const FontDesc&           desc)
{
    auto font = std::make_shared<Font>(device, desc);
    return font;
}

std::shared_ptr<LayoutFont> FontFactory::CreateLayoutFont(std::shared_ptr<D3Device> device,
                                                          const FontDesc&           desc)
{
    auto layoutFont = std::make_shared<LayoutFont>(device, desc);
    return layoutFont;
}

bool FontFactory::IsFontFormat(const wstringV ext)
{
    if (ext.compare(L".ttf") == 0)
        return true;
    if (ext.compare(L".otf") == 0)
        return true;

    return false;
}
