#pragma once
#include "MyWriterFont.h"
#include "ResourceHandler.h"

namespace HBSoft
{
    class FontHandler : public ResourceHandler<MyWriterFont, FONT_KEY>
    {
    private:
        std::vector<wstringV> externalFontNames;

        std::map<UINT, RECT_F> mDebugRect;

    public:
        ~FontHandler();

        bool CreateFontResource(const FONT_KEY _key, const FontDesc& _desc);
        void DrawTextAsKey(FONT_KEY _key, wstringV _msg, RECT_F _rect, COLOR_F _color);
        bool LoadExternalFont(const wstringV _fontPath);
        void LoadExternalFontsAsFolder(const wstringV _fontFolder);

#ifdef _DEBUG
        // ���� ��ǥ�� ����
        void AddRectAreaForDebugging(UINT _key, RECT_F _rect);
        void DrawRectForDebugging();
        void DrawTextForDebugging(const wchar_t* format, ...);
        void DrawRectForDebugging(RECT_F& _rect);
#endif
    };
}  // namespace HBSoft
