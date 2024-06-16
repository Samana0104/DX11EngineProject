#include "pch.h"
#include "MyFontHandler.h"
using namespace MyProject;

MyFontHandler::MyFontHandler()
{
	CreateDefaultFonts();
}

void MyFontHandler::CreateDefaultFonts()
{
	CreateFontComponent(L"¸¼Àº °íµñ", 25);
}

FONT_KEY MyFontHandler::CreateFontComponent(
			const std::wstring _fontName, 
			const FLOAT _fontSize, 
			const std::wstring _localName,
			const DWRITE_FONT_WEIGHT _fontWeight, 
			const DWRITE_FONT_STYLE _fontStyle,
			const DWRITE_FONT_STRETCH _fontStrech)
{
	auto font = std::make_shared<MyWriterFont>(_fontName, _fontSize, _localName, _fontWeight, _fontStyle, _fontStrech);
	return AddFontComponent(font);
}

FONT_KEY MyFontHandler::AddFontComponent(std::shared_ptr<MyWriterFont>& _font)
{
	if (!AddComponent(_key, _font))
		MessageBoxA(NULL, "exist Font[Key Error]", "Font Error", MB_OK);
	// throw ´øÁú±î À½...
}

void MyFontHandler::DrawTextAsKey(const std::string _key, wstringV _msg, POINT_F _pos, COLOR_F _color)
{
	auto data = GetComponent(_key);

	if(data != nullptr)
		data->DrawTexts(_msg, _pos, _color);
	else
		MessageBoxA(NULL, "Not existed Font[Key Error]", "Font Error", MB_OK);
}
