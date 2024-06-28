#pragma once
#include "MyWriterFont.h"
#include "ResourceHandler.h"

namespace MyProject
{
	class MyFontHandler : public ResourceHandler<MyWriterFont, FONT_KEY>
	{
	public:
		bool CreateFontResource(const FONT_KEY _key, const FontDesc& _desc);
		void DrawTextAsKey(FONT_KEY _key, wstringV _msg, RECT_F _rect, COLOR_F _color);

#ifdef _DEBUG
		void DrawTextForDebugging(const wchar_t* format, ...);
#endif
	};
}
