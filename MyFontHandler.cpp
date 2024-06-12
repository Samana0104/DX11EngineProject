#include "MyFontHandler.h"
using namespace MyProject;

MyFontHandler::MyFontHandler()
{
	CreateDefaultFonts();
}

void MyFontHandler::CreateDefaultFonts()
{
	CreateTextComponent(DefaultFont::DEBUG, L"¸¼Àº °íµñ", 25);
}

void MyFontHandler::CreateTextComponent(
			const std::string _key, 
			const std::wstring _fontName, 
			const FLOAT _fontSize, 
			const std::wstring _localName,
			const DWRITE_FONT_WEIGHT _fontWeight, 
			const DWRITE_FONT_STYLE _fontStyle,
			const DWRITE_FONT_STRETCH _fontStrech)
{
	auto _font = std::make_shared<MyWriterFont>(_fontName, _fontSize, _localName, _fontWeight, _fontStyle, _fontStrech);
	AddComponent(_key, _font);
}

void MyFontHandler::AddTextComponent(const std::string _key, std::shared_ptr<MyWriterFont>& _font)
{
	if (!AddComponent(_key, _font))
	{
		MessageBoxA(NULL,
			"exist Font[Key Error]",
			"Font Error", MB_OK);
	}
}

void MyFontHandler::DrawTextAsKey(const std::string _key, wstringV _msg, POINT_F _pos, COLOR_F _color)
{
	GetComponent(_key)->DrawTexts(_msg, _pos, _color);
}

std::shared_ptr<MyWriterFont>& MyFontHandler::GetTextComponent(const std::string _key)
{
	return GetComponent(_key);
}
