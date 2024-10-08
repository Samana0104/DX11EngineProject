#include "pch.h"
#include "FontHandler.h"
using namespace HBSoft;

FontHandler::~FontHandler()
{
    for (auto& fontPath : externalFontNames)
        RemoveFontResource(fontPath.data());

    PostMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);
}

bool FontHandler::CreateFontResource(const FONT_KEY _key, const FontDesc& _desc)
{
    auto font = std::make_shared<Font>(_desc);
    return Add(_key, font);
}

bool FontHandler::LoadExternalFont(const wstringV fontPath)
{
    auto fileInfo = CoreAPI::GetFileNameAndExt(fontPath);

    if (fileInfo.second.compare(L".ttf") != 0)
        return false;

    if (AddFontResource(fontPath.data()) == 0)
        return false;

    externalFontNames.push_back(fontPath);
    PostMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);
    return true;
}

void FontHandler::LoadExternalFontsAsFolder(const wstringV fontFolder)
{
    std::filesystem::directory_iterator iter(fontFolder);

    while (iter != std::filesystem::end(iter))
    {
        const auto& currentFile = *(iter++);

        if (currentFile.is_directory())
            LoadExternalFontsAsFolder(currentFile.path().wstring());
        else
            LoadExternalFont(currentFile.path().wstring());
    }
}

void FontHandler::DrawTextAsKey(FONT_KEY key, wstringV msg, RECT_F rect, COLOR_F color)
{
    auto data = Get(key);
    data->DrawTexts(msg, rect, color);
}

#ifdef _DEBUG

void FontHandler::AddRectAreaForDebugging(UINT _key, RECT_F _rect)
{
    RECT_F rt         = Transform2D::CartesianToPixelRect(_rect);
    m_debugRect[_key] = rt;
}

void FontHandler::DrawTextForDebugging(const wchar_t* format, ...)
{
    va_list args;
    va_start(args, format);
    // 필요한 버퍼 크기를 계산
    int          size = _vscwprintf(format, args) + 1;  // 서식 문자열의 길이 계산
    std::wstring formattedMessage(size, L'\0');

    // 서식 문자열을 처리하여 formattedMessage에 저장
    vswprintf_s(&formattedMessage[0], size, format, args);
    va_end(args);

    vec2   mySize = Window::GetInstance().GetWindowSizeVec2();
    RECT_F rc1    = {mySize.x * 0.1f, mySize.y * 0.7f, mySize.x * 0.6f, mySize.y * 0.95f};
    RECT_F rc2    = {rc1.left + rc1.left * 0.1f, rc1.top + rc1.top * 0.05f, rc1.right, rc1.bottom};

    std::shared_ptr<Font> brush = Get(L"DEBUG_FONT");

    D3Device::GetInstance().m_d2dRT->BeginDraw();
    brush->GetBrush()->SetColor({1.f, 1.f, 1.f, 0.3f});
    D3Device::GetInstance().m_d2dRT->FillRectangle(rc1, brush->GetBrush().Get());
    brush->GetBrush()->SetColor({1.f, 0.1f, 0.1f, 1.f});
    D3Device::GetInstance().m_d2dRT->DrawRectangle(rc1, brush->GetBrush().Get(), 1.f);
    D3Device::GetInstance().m_d2dRT->EndDraw();
    DrawTextAsKey(L"DEBUG_FONT", L" [DEBUG Window]", rc1, {0.f, 0.f, 0.f, 1.f});
    DrawTextAsKey(L"DEBUG_FONT", formattedMessage, rc2, {0.f, 0.f, 0.f, 1.f});
}

void FontHandler::DrawRectForDebugging()
{
    auto a = Get(L"DEBUG_FONT")->GetBrush();

    for (auto& rect : m_debugRect)
    {
        D3Device::GetInstance().m_d2dRT->BeginDraw();
        D3Device::GetInstance().m_d2dRT->DrawRectangle(&(rect.second), a.Get());
        D3Device::GetInstance().m_d2dRT->EndDraw();
    }
}
#endif
