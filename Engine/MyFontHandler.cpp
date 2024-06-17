#include "pch.h"
#include "MyFontHandler.h"
using namespace MyProject;

bool MyFontHandler::CreateFontComponent(const FONT_KEY _key, const FontDesc& _desc)
{
	if (IsKeyContained(_key))
		return false;

	auto font = std::make_shared<MyWriterFont>(_desc);
	return AddResource(_key, font);
}

bool MyFontHandler::CreateFontComponent(
	const FONT_KEY _key,
	const std::wstring _fontName,
	const FLOAT _fontSize,
	const std::wstring _localName,
	const DWRITE_FONT_WEIGHT _fontWeight,
	const DWRITE_FONT_STYLE _fontStyle,
	const DWRITE_FONT_STRETCH _fontStretch)
{
	FontDesc desc;
	{
		desc.mFontName = _fontName;
		desc.mFontLocalName = _localName;
		desc.mFontSize = _fontSize;
		desc.mFontWeight = _fontWeight;
		desc.mFontStyle = _fontStyle;
		desc.mFontStretch = _fontStretch;
	}

	return CreateFontComponent(_key, desc);
}

void MyFontHandler::DrawTextAsKey(FONT_KEY _key, wstringV _msg, RECT_F _rect, COLOR_F _color)
{
	auto data = GetResource(_key);
	data->DrawTexts(_msg, _rect, _color);
}
