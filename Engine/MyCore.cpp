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
	mShader.RenderComponent();
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

    mManager.mFontHandler.DrawTextAsKey(
		"DEBUG_FONT",
		formattedMessage, 
		{10, 10}, 
		{1.f, 1.f, 1.f, 1.f});
}

void MyCore::INITIAL_SETUP(HINSTANCE _hinstance, LONG _width, LONG _height)
{
	MyWindow::GetInstance().SetHinstance(_hinstance);
	_ASSERT(MyWindow::GetInstance().CreateWin(_width, _height));
	_ASSERT(D3Device::GetInstance().CreateDevice());
	MyResourceManager::GetInstance().CreateDafultResource();

}
