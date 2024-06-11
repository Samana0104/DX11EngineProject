#include "MyFontHandler.h"
using namespace MyProject;

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
	mFonts.insert(std::make_pair(_key, _font));
}

void MyFontHandler::AddTextComponent(const std::string _key, std::shared_ptr<MyWriterFont> _font)
{
	mFonts.insert(std::make_pair(_key, _font));
}

void MyFontHandler::DrawTextAsKey(std::string _key, std::wstring _msg, POINT_F _pos, COLOR_F _color)
{
	mFonts.at(_key)->DrawTexts(_msg, _pos, _color);
}

std::shared_ptr<MyWriterFont>& MyFontHandler::GetTextComponent(const std::string _key)
{
	return mFonts.at(_key);
}

void MyProject::MyFontHandler::UpdateComponent()
{
}

void MyProject::MyFontHandler::RenderComponent()
{
}

void MyProject::MyFontHandler::ReleaseComponent()
{
}
