/*
author : 변한빛
description : 폰트를 관리하기 위한 매니징 소스 파일

version: 1.0.0
date: 2024-11-04
*/

#include "pch.h"
#include "FontHandler.h"
using namespace HBSoft;

FontHandler::~FontHandler()
{
    for (auto& fontPath : externalFontNames)
        RemoveFontResource(fontPath.data());

    PostMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);
}

bool FontHandler::CreateFontResource(const FONT_KEY _key, const FontDesc& _desc)
{
    auto font = std::make_unique<Font>(_desc);
    return Add(_key, std::move(font));
}

bool FontHandler::LoadExternalFont(const wstringV fontPath)
{
    auto fileInfo = HBSoft::GetFileNameAndExt(fontPath);

    if (fileInfo.second.compare(L".ttf") != 0)
        return false;

    if (AddFontResource(fontPath.data()) == 0)
        return false;

    externalFontNames.push_back(fontPath);
    PostMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);
    return true;
}

void FontHandler::LoadExternalFontsAsFolder(const wstringV fontFolder)
{
    std::filesystem::directory_iterator iter(fontFolder);

    while (iter != std::filesystem::end(iter))
    {
        const auto& file = *(iter++);

        if (file.is_directory())
            LoadExternalFontsAsFolder(file.path().wstring());
        else
            LoadExternalFont(file.path().wstring());
    }
}

void FontHandler::DrawTextAsKey(FONT_KEY key, wstringV msg, HRect rect, COLOR_F color)
{
    auto& data = Get(key);
    data->DrawTexts(msg, rect, color);
}
