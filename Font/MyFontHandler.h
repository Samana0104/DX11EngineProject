#pragma once
#include "MyWriterFont.h"
#include "MyDefaultFontKey.h"
#include "Handler.h"

namespace MyProject
{
	class MyFontHandler : 
		public Handler<MyWriterFont, std::string, std::map<std::string, std::shared_ptr<MyWriterFont>>>
	{
	public:
		MyFontHandler();

		void CreateDefaultFonts();
		void CreateTextComponent(const std::string _key, const std::wstring _fontName, const FLOAT _fontSize, const std::wstring _localName = L"ko-kr",
			const DWRITE_FONT_WEIGHT _fontWeight = DWRITE_FONT_WEIGHT_THIN, 
			const DWRITE_FONT_STYLE _fontStyle = DWRITE_FONT_STYLE_NORMAL,
			const DWRITE_FONT_STRETCH _fontStrech = DWRITE_FONT_STRETCH_NORMAL);

		void AddTextComponent(const std::string _key, std::shared_ptr<MyWriterFont>& _font);
		void DrawTextAsKey(const std::string _key, wstringV _msg, POINT_F _pos, COLOR_F _color);
	};
}
