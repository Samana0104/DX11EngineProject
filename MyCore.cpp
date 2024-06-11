#include "MyCore.h"
using namespace MyProject;

void MyCore::InitViewPort()
{
	auto windowSize = mWindow.GetWindowSizeF();

	mViewPort.TopLeftX = 0;
	mViewPort.TopLeftY = 0;
	mViewPort.Width = windowSize.x;
	mViewPort.Height = windowSize.y;
	mViewPort.MinDepth = 0;
	mViewPort.MaxDepth = 1;
}

void MyCore::GamePreFrame()
{ 
}

void MyCore::GameFrame()
{
	mTimer.UpdateComponent();

	if(mWindow.IsActivate())
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

	mDevice.mContext->OMSetRenderTargets(1, mDevice.mRTV.GetAddressOf(), nullptr);
	mDevice.mContext->RSSetViewports(1, &mViewPort);
	mShader.RenderComponent();
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
	mTimer.InitTimer();
	InitViewPort();
	InitComponent();
}

void MyCore::GameRelease()
{
	mTimer.ReleaseComponent();
	mInput.ReleaseComponent();
	mShader.ReleaseComponent();
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

void MyCore::DrawTextForDebuging() const
{
	/* 작성예정 */
}


D3D11_VIEWPORT&	MyCore::GetViewPort()
{
	return mViewPort;
}
