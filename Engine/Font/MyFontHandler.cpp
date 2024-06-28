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

#ifdef _DEBUG
void MyFontHandler::DrawTextForDebugging(const wchar_t* format, ...)
{
    va_list args;
    va_start(args, format);
    // 필요한 버퍼 크기를 계산
    int size = _vscwprintf(format, args) + 1; // 서식 문자열의 길이 계산
    std::wstring formattedMessage(size, L'\0');

    // 서식 문자열을 처리하여 formattedMessage에 저장
    vswprintf_s(&formattedMessage[0], size, format, args);
    va_end(args);

	vec2 mySize = MyWindow::GetInstance().GetWindowSizeVec2();
	RECT_F rc1 = { mySize.x*0.1f, mySize.y*0.7f, mySize.x*0.6f, mySize.y*0.95f };
	RECT_F rc2 = { rc1.left + rc1.left*0.1f, rc1.top + rc1.top*0.05f, rc1.right, rc1.bottom };

	std::shared_ptr<MyWriterFont> brush = GetResource(L"DEBUG_FONT");

	D3Device::GetInstance().mD2dRT->BeginDraw();
	brush->GetBrush()->SetColor({ 1.f, 1.f, 1.f, 0.3f });
	D3Device::GetInstance().mD2dRT->FillRectangle(rc1, brush->GetBrush().Get());
	brush->GetBrush()->SetColor({ 1.f, 0.1f, 0.1f, 1.f });
	D3Device::GetInstance().mD2dRT->DrawRectangle(rc1, brush->GetBrush().Get(), 1.f);
	D3Device::GetInstance().mD2dRT->EndDraw();
	DrawTextAsKey( L"DEBUG_FONT", L" [DEBUG WINDOW]", rc1, { 0.f, 0.f, 0.f, 1.f });
	DrawTextAsKey( L"DEBUG_FONT", formattedMessage, rc2, { 0.f, 0.f, 0.f, 1.f });
}
#endif

