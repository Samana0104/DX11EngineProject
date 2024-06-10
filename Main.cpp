#include "MyCore.h"
using namespace MyProject;

class Sample : public MyCore 
{
public:
	POINT_F myPos;
	Box2D	myBox;
	Box2D	myBox2;
	float	test;

	Sample()
		: myPos({ 0, 0 }),
		myBox({ 200, 200 }, L"KGCA1.png"),
		myBox2({ 300, 200 }, L"KGCA1.png"),
		test(1)
	{
		
	}

	virtual void InitComponent() override
	{
		myBox.InitComponent();
		myBox2.InitComponent();
		myBox2.SetPosition({ 300, 500 });
		CreateTextComponent("font_1", L"πŸ≈¡", 30.f, { 1.f, 0.f, 0.f, 1.f });
		CreateTextComponent("font_2", L"±º∏≤", 100.f, { 1.f, 0.f, 1.f, 1.f });
		test = 1;
	}
	virtual void UpdateComponent() override
	{
		if (mInput.GetCurrentKeyState(VK_UP) == KeyState::KEY_HOLD)
		{
			myPos.y -= 1;
			if (myPos.y < 0)
				myPos.y = 0;
		}
		if (mInput.GetCurrentKeyState(VK_RIGHT) == KeyState::KEY_HOLD)
		{
			myPos.x += 1;
			if (myPos.x > mWindow.GetWindowSizeF().x)
				myPos.x = mWindow.GetWindowSizeF().x;
		}
		if (mInput.GetCurrentKeyState(VK_LEFT) == KeyState::KEY_HOLD)
		{
			myPos.x -= 1;
			if (myPos.x < 0)
				myPos.x = 0;
		}
		if (mInput.GetCurrentKeyState(VK_DOWN) == KeyState::KEY_HOLD)
		{
			myPos.y += 1;
			if (myPos.y > mWindow.GetWindowSizeF().y)
				myPos.y = mWindow.GetWindowSizeF().y;
		}

		test += 1;

		myBox.Rotate(0.01f);
		myBox.SetPosition({myPos.x, myPos.y});
		myBox2.Scale({ glm::sin(test), glm::sin(test) });
		myBox2.Rotate(test);
	}

	virtual void RenderComponent() override
	{
		//if (GetInputComponent().GetCurrentKeyState(VK_F1) == KeyState::KEY_HOLD)
		//{
		//	GetTextComponent("font_1").DrawTextW(GetTimerComponent().m_csBuffer, { 10, 10, 1024, 1024 });
		//}
		myBox.RenderComponent();
		myBox2.RenderComponent();
		GetTextComponent("font_1").DrawTexts(mTimer.m_csBuffer, {myPos.x, myPos.y, mWindow.GetWindowSizeF().x, mWindow.GetWindowSizeF().y});
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