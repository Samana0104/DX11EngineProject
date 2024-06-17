#include "pch.h"
#include "MyCore.h"
using namespace MyProject;

class Sample : public MyCore 
{
private:
	POINT_F myPos;
	//Box2D	myBox;
	//Box2D	myBox2;
	float	test;
	MyObject mObject;
	MyObject mObject2;
	MyCamera mCamera;

public:
	Sample()
		: myPos({ 0, 0 }),
		  mObject("KGCA_01_IMG", "BOX2D_MESH"),
		  mObject2("KGCA_01_IMG", "BOX2D_MESH"),
		//myBox({ 200, 200 }, L"KGCA1.png"),
		//myBox2({ 300, 200 }, L"KGCA1.png"),
		test(1)
	{
	}

	virtual void InitComponent() override
	{
		test = 1;
	}
	virtual void UpdateComponent() override
	{
		POINTFLOAT size = MyWindow::GetInstance().GetWindowSizeF();

		if (mInput.GetCurrentKeyState(VK_UP) == KeyState::KEY_HOLD)
		{
			myPos.y -= 400 * mTimer.GetDeltaTime();
			if (myPos.y < 0)
				myPos.y = 0;
			mCamera.mTransform.AddTranslationInMat({ 0.f, 100.f* mTimer.GetDeltaTime()});
		}
		if (mInput.GetCurrentKeyState(VK_RIGHT) == KeyState::KEY_HOLD)
		{
			myPos.x += 400 * mTimer.GetDeltaTime();
			if (myPos.x > mWindow.GetWindowSizeF().x)
				myPos.x = mWindow.GetWindowSizeF().x;
			mCamera.mTransform.AddTranslationInMat({100.f* mTimer.GetDeltaTime(), 0.f});
		}
		if (mInput.GetCurrentKeyState(VK_LEFT) == KeyState::KEY_HOLD)
		{
			myPos.x -= 400 * mTimer.GetDeltaTime();
			if (myPos.x < 0)
				myPos.x = 0;
			mCamera.mTransform.AddTranslationInMat({ 100.f*-mTimer.GetDeltaTime(), 0.f});
		}
		if (mInput.GetCurrentKeyState(VK_DOWN) == KeyState::KEY_HOLD)
		{
			myPos.y += 400 * mTimer.GetDeltaTime();
			if (myPos.y > mWindow.GetWindowSizeF().y)
				myPos.y = mWindow.GetWindowSizeF().y;
			mCamera.mTransform.AddTranslationInMat({ 0.f, 100.f*-mTimer.GetDeltaTime()});
		}
		
		test = 101 * mTimer.GetDeltaTime();
	}

	virtual void RenderComponent() override
	{
		//mFont.DrawTextAsKey("font_1", mTimer.m_csBuffer, {myPos.x, myPos.y}, {0.f, 1.f, 1.f, 1.f});
		//mFont.DrawTextAsKey("font_1", std::to_wstring(mTimer.GetElapsedTime()), {myPos.x, myPos.y}, {0.f, 1.f, 1.f, 1.f});
		//DrawTextForDebugging(L"%d", 1234567);
		mObject.RenderObject(mCamera.GetViewMat());
		mObject2.RenderObject(mCamera.GetViewMat());
		DrawTextForDebugging(L"카메라 좌표계 : %f %f",
			mCamera.mTransform.GetLocation().x,
			mCamera.mTransform.GetLocation().y);
	}

	virtual void ReleaseComponent() override
	{
	}
};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR
	pCmdLine, int nCmdShow)
{
	MyProject::MyCore::INITIAL_SETUP(hInstance, 1200, 800);
	Sample sample;

	sample.GameRun();
	return 0;
}