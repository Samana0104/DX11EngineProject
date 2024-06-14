#include "pch.h"
#include "MyCore.h"
using namespace MyProject;

class Sample : public MyCore 
{
public:
	POINT_F myPos;
	//Box2D	myBox;
	//Box2D	myBox2;
	float	test;

	Sample()
		: myPos({ 0, 0 }),
		//myBox({ 200, 200 }, L"KGCA1.png"),
		//myBox2({ 300, 200 }, L"KGCA1.png"),
		test(1)
	{
	}

	virtual void InitComponent() override
	{
		//myBox2.SetPosition({ 300, 500 });
		mFont.CreateTextComponent("font_1", L"πŸ≈¡", 30.f);
		mFont.CreateTextComponent("font_2", L"±º∏≤", 100.f);
		test = 1;
	}
	virtual void UpdateComponent() override
	{
		if (mInput.GetCurrentKeyState(VK_UP) == KeyState::KEY_HOLD)
		{
			myPos.y -= 400 * mTimer.GetDeltaTime();
			if (myPos.y < 0)
				myPos.y = 0;
			mTimer.SetMasFPS(100);
		}
		if (mInput.GetCurrentKeyState(VK_RIGHT) == KeyState::KEY_HOLD)
		{
			myPos.x += 400 * mTimer.GetDeltaTime();
			if (myPos.x > mWindow.GetWindowSizeF().x)
				myPos.x = mWindow.GetWindowSizeF().x;
			mTimer.SetMasFPS(120);
		}
		if (mInput.GetCurrentKeyState(VK_LEFT) == KeyState::KEY_HOLD)
		{
			myPos.x -= 400 * mTimer.GetDeltaTime();
			if (myPos.x < 0)
				myPos.x = 0;
			mTimer.SetMasFPS(50);
		}
		if (mInput.GetCurrentKeyState(VK_DOWN) == KeyState::KEY_HOLD)
		{
			myPos.y += 400 * mTimer.GetDeltaTime();
			if (myPos.y > mWindow.GetWindowSizeF().y)
				myPos.y = mWindow.GetWindowSizeF().y;
			mTimer.SetMasFPS(30);
		}

		test = 101 * mTimer.GetDeltaTime();

		//myBox.Rotate(0.5f);
		//myBox.SetPosition({myPos.x, myPos.y});
		//myBox2.SetScale({ glm::cos(mTimer.GetDeltaTime()) * 5, glm::sin(mTimer.GetDeltaTime() * 5) });
		//myBox2.Rotate(test);
	}

	virtual void RenderComponent() override
	{
		//if (GetInputComponent().GetCurrentKeyState(VK_F1) == KeyState::KEY_HOLD)
		//{
		//	GetTextComponent("font_1").DrawTextW(GetTimerComponent().m_csBuffer, { 10, 10, 1024, 1024 });
		//}
		//myBox.RenderComponent();
		//myBox2.RenderComponent();
		//mFont.DrawTextAsKey("font_1", mTimer.m_csBuffer, {myPos.x, myPos.y}, {0.f, 1.f, 1.f, 1.f});
		//mFont.DrawTextAsKey("font_1", std::to_wstring(mTimer.GetElapsedTime()), {myPos.x, myPos.y}, {0.f, 1.f, 1.f, 1.f});
		DrawTextForDebuging(mTimer.m_csBuffer);
	}

	virtual void ReleaseComponent() override
	{

	}
};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR
	pCmdLine, int nCmdShow)
{
	MyProject::INITIALIZE_DEVICE(hInstance, 1920, 1080);
	Sample sample;

	sample.GameRun();
	return 0;
}