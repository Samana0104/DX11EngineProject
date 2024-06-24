#include "pch.h"
#include "MyFontHandler.h"
using namespace MyProject;

bool MyFontHandler::CreateFontResource(const FONT_KEY _key, const FontDesc& _desc)
{
	auto font = std::make_shared<MyWriterFont>(_desc);
	return AddResource(_key, font);
}

void MyFontHandler::DrawTextAsKey(FONT_KEY _key, wstringV _msg, RECT_F _rect, COLOR_F _color)
{
	auto data = GetResource(_key);
	data->DrawTexts(_msg, _rect, _color);
}
