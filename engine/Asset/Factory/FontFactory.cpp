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

std::shared_ptr<Font> FontFactory::CreateFromDesc(std::shared_ptr<D3Device>& device,
                                                  const FontDesc&            desc)
{
    auto font = std::make_shared<Font>(device, desc);
    return font;
}

bool FontFactory::IsFontFormat(const wstringV ext)
{
    if (ext.compare(L".ttf") == 0)
        return true;

    return false;
}
