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
}

void MyCore::GameRender()
{
	GamePreRender();
	mSceneManager.Render();
	GamePostRender();
}

void MyCore::GamePostRender()
{
	mDevice.mSwapChain->Present(0, 0);
}

void MyCore::GameInit()
{
	mTimer.Reset();
	mSceneManager.Init();
}

void MyCore::GameRelease()
{
	mSceneManager.Release();
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
