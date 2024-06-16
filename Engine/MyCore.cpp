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

//void MyCore::DrawTextForDebugging(const wstringV format, auto&&... args)
//{
//    std::wstring formattedMessage = 
//		std::vformat(format, std::make_wformat_args(std::forward<decltype(args)>(args)...));
//

//	mFont.DrawTextAsKey(DefaultFont::DEBUG, formattedMessage, { 10, 10 }, { 1.f, 1.f, 1.f, 1.f });
//}

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

    mFont.DrawTextAsKey(DefaultFont::DEBUG, formattedMessage, { 10, 10 }, { 1.f, 1.f, 1.f, 1.f });
}
