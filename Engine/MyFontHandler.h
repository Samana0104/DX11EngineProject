#pragma once
#include "MyWriterFont.h"
#include "ResourceHandler.h"

namespace MyProject
{
	class MyFontHandler : 
		public ResourceHandler<MyWriterFont, FONT_KEY, std::map<FONT_KEY, std::shared_ptr<MyWriterFont>>>
	{
	public:
		bool CreateFontComponent(const FONT_KEY _key, const FontDesc& _desc);
		bool CreateFontComponent(
			const FONT_KEY _key,
			const std::wstring _fontName, 
			const FLOAT _fontSize, 
			const std::wstring _localName = L"ko-kr",
			const DWRITE_FONT_WEIGHT _fontWeight = DWRITE_FONT_WEIGHT_THIN, 
			const DWRITE_FONT_STYLE _fontStyle = DWRITE_FONT_STYLE_NORMAL,
			const DWRITE_FONT_STRETCH _fontStretch = DWRITE_FONT_STRETCH_NORMAL);

		bool DrawTextAsKey(FONT_KEY _key, wstringV _msg, POINT_F _pos, COLOR_F _color);
	};
}
