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

void MyCore::DebugRender()
{
	/*m_Timer.DebugTimer();
	m_Input.DebugMousePos();
	m_Input.KeyTest();*/
}

void MyCore::GameInit()
{
	mTimer.InitComponent();
	mInput.InitComponent();
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

		if (!mTimer.HasPassedFrame())
		{
			GameFrame();
			GameRender();
		}
	}
	GameRelease();
}

void MyProject::MyCore::DrawTextForDebuging() const
{
}

void MyCore::CreateTextComponent(const std::string key, std::wstring _fontName, FLOAT _fontSize, COLOR_F _color)
{
	AddTextComponent(key, std::make_shared<MyWriterFont>(_fontName, _fontSize, _color));
}

void MyCore::AddTextComponent(const std::string _key, std::shared_ptr<MyWriterFont> _fonts)
{
	mGameFonts.insert(std::make_pair(_key, _fonts));
}

MyWriterFont& MyCore::GetTextComponent(const std::string _key)
{
	return *mGameFonts[_key];
}

D3D11_VIEWPORT&	MyCore::GetViewPort()
{
	return mViewPort;
}

