#pragma once
#include "MyWriterFont.h"
#include "MyDefaultFontKey.h"
#include "ResourceHandler.h"

namespace MyProject
{
	class MyFontHandler : 
		public ResourceHandler<MyWriterFont, UINT, std::map<std::string, std::shared_ptr<MyWriterFont>>>
	{
	public:
		MyFontHandler();

		void CreateDefaultFonts();
		FONT_KEY CreateFontComponent(
			const std::wstring _fontName, 
			const FLOAT _fontSize, 
			const std::wstring _localName = L"ko-kr",
			const DWRITE_FONT_WEIGHT _fontWeight = DWRITE_FONT_WEIGHT_THIN, 
			const DWRITE_FONT_STYLE _fontStyle = DWRITE_FONT_STYLE_NORMAL,
			const DWRITE_FONT_STRETCH _fontStrech = DWRITE_FONT_STRETCH_NORMAL);

		FONT_KEY AddFontComponent(std::shared_ptr<MyWriterFont>& _font);
		void DrawTextAsKey(const std::string _key, wstringV _msg, POINT_F _pos, COLOR_F _color);
	};
}
