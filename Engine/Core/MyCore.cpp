#include "pch.h"
#include "MyCore.h"
using namespace MyProject;

void MyCore::GamePreFrame()
{ 
}

void MyCore::GameFrame()
{
	mTimer.UpdateComponent();
	mInput.UpdateComponent();
	UpdateComponent();
}

void MyCore::GamePostFrame()
{
}

void MyCore::GamePreRender()
{
	float clearColor[] = { 0.f, 0.f, 0.f, 1.0f };
	mDevice.mContext->ClearRenderTargetView(mDevice.mRTV.Get(), clearColor);
}

void MyCore::GameRender()
{
	GamePreRender();
	RenderComponent();
	GamePostRender();
}

void MyCore::GamePostRender()
{
	mDevice.mSwapChain->Present(0, 0);
}

void MyCore::GameInit()
{
	mTimer.ResetTimer();
	InitComponent();
}

void MyCore::GameRelease()
{
	ReleaseComponent();
}

void MyCore::GameRun()
{
	GameInit();
	while (1)
	{
		if (!mWindow.WindowRun())
			break;

		if (mTimer.HasPassedTime())
		{
			GameFrame();
			GameRender();
		}
	}
	GameRelease();
}

#ifdef _DEBUG
void MyCore::DrawTextForDebugging(const wchar_t* format, ...)
{
    va_list args;
    va_start(args, format);
    // 필요한 버퍼 크기를 계산
    int size = _vscwprintf(format, args) + 1; // 서식 문자열의 길이 계산
    std::wstring formattedMessage(size, L'\0');

    // 서식 문자열을 처리하여 formattedMessage에 저장
    vswprintf_s(&formattedMessage[0], size, format, args);
    va_end(args);

	vec2 mySize = mWindow.GetWindowSizeVec2();
	RECT_F rc1 = { mySize.x*0.1f, mySize.y*0.7f, mySize.x*0.6f, mySize.y-10.f };
	RECT_F rc2 = { rc1.left + rc1.left*0.1f, rc1.top + rc1.top*0.05f, rc1.right, rc1.bottom };

	std::shared_ptr<MyWriterFont> brush = mManager.mFontHandler.GetResource(L"DEBUG_FONT");

	mDevice.mD2dRT->BeginDraw();
	brush->GetBrush()->SetColor({ 1.f, 1.f, 1.f, 0.3f });
	mDevice.mD2dRT->FillRectangle(rc1, brush->GetBrush().Get());
	brush->GetBrush()->SetColor({ 1.f, 0.1f, 0.1f, 1.f });
	mDevice.mD2dRT->DrawRectangle(rc1, brush->GetBrush().Get(), 1.f);
	mDevice.mD2dRT->EndDraw();
	mManager.mFontHandler.DrawTextAsKey(
		L"DEBUG_FONT",
		L" [DEBUG WINDOW]",
		rc1,
		{ 0.f, 0.f, 0.f, 1.f });
	mManager.mFontHandler.DrawTextAsKey(
		L"DEBUG_FONT",
		formattedMessage,
		rc2,
		{ 0.f, 0.f, 0.f, 1.f });
}
#endif

void MyCore::INITIAL_SETUP(HINSTANCE _hinstance, LONG _width, LONG _height)
{
	MyWindow::GetInstance().SetHinstance(_hinstance);
	_ASSERT(MyWindow::GetInstance().CreateWin(_width, _height));
	_ASSERT(D3Device::GetInstance().CreateDevice());
	MyResourceManager::GetInstance().CreateDafultResource();

}
