#include "pch.h"
#include "MyCore.h"
using namespace MyProject;

void MyCore::GameFrame()
{
	mInput.Update();
	mSceneManager.Update(mTimer.GetDeltaTime());
	mManager.mSound.Update();
}

void MyCore::GamePreRender()
{
	float clearColor[] = { 0.f, 0.f, 0.f, 1.0f };
	mDevice.mContext->ClearRenderTargetView(mDevice.mRTV.Get(), clearColor);
	SetClientRangeViewport();
}

void MyCore::GameRender()
{
	GamePreRender();
	mSceneManager.Render();
	GamePostRender();
}

void MyCore::GamePostRender()
{
#ifdef _DEBUG
	mManager.mFont.DrawRectForDebugging();
#endif

	mDevice.mSwapChain->Present(1, 0);
}

void MyCore::GameInit()
{
	mWideScreen.SetTextureKey(L"widescreen.png");
	mWideScreen->SetScale(mWindow.GetWindowSizeVec2());
	mTimer.Reset();
	mSceneManager.Init();
}

void MyCore::GameRelease()
{
	mSceneManager.Release();
}

void MyCore::SetClientRangeViewport()
{
	auto windowSize = mWindow.GetWindowSizeVec2();
	
	mDevice.SetViewportSizeOnLeftTop(windowSize);
	mWideScreen.SetImageScale();
	mWideScreen.SetColor({ 11.f, 10.f, 13.f, 1.f });
	mWideScreen.Render();

	if (windowSize.x >= 1280.f && windowSize.y >= 960.f)
		windowSize = { 1280.f, 960.f };
	else if (windowSize.x >= 960.f && windowSize.y >= 720.f)
		windowSize = { 960.f, 720.f };
	else if (windowSize.x >= 640.f && windowSize.y >= 480.f)
		windowSize = { 640.f, 480.f };
	else if (windowSize.x >= 320.f && windowSize.y >= 240.f)
		windowSize = { 320.f, 240.f };
	else
		windowSize = { 0.f, 0.f };

	mDevice.SetViewportSizeOnCenter(windowSize);
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

void MyCore::ENGINE_BEGIN(HINSTANCE _hinstance, LONG _width, LONG _height)
{
	MyWindow::GetInstance().SetHinstance(_hinstance);
#ifdef _DEBUG
	_ASSERT(MyWindow::GetInstance().CreateWin(_width, _height));
	_ASSERT(D3Device::GetInstance().CreateDevice());
#else
	MyWindow::GetInstance().CreateWin(_width, _height);
	D3Device::GetInstance().CreateDevice();
#endif

	MyResourceManager::GetInstance().CreateDafultResource();

}

void MyCore::ENGINE_END()
{
	MyResourceManager::GetInstance().Release();
	MyInput::GetInstance().Release();
	D3Device::GetInstance().Release();
	MyWindow::GetInstance().Release();
}
