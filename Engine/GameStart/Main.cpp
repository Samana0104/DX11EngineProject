#include "pch.h"
#include "MyCore.h"
using namespace MyProject;

class Sample : public MyCore 
{
private:
	POINT_F myPos;
	//Box2D	myBox;
	//Box2D	myBox2;
	MyObject mObject;
	MyCamera mCamera;

public:
	Sample()
		: myPos({ 0, 0 }),
		  mObject(L"KGCA1.png", L"BOX2D_MESH")
		//myBox({ 200, 200 }, L"KGCA1.png"),
		//myBox2({ 300, 200 }, L"KGCA1.png"),
	{

	}

	virtual void InitComponent() override
	{
	}
	virtual void UpdateComponent() override
	{
		if (mInput.GetCurrentKeyState(VK_UP) == KeyState::KEY_HOLD)
		{
			mCamera.mTransform.AddMovement({0.f, 100.f* mTimer.GetDeltaTime() });
		}
		if (mInput.GetCurrentKeyState(VK_RIGHT) == KeyState::KEY_HOLD)
		{
			mCamera.mTransform.AddMovement({100.f* mTimer.GetDeltaTime(), 0.f});
		}
		if (mInput.GetCurrentKeyState(VK_LEFT) == KeyState::KEY_HOLD)
		{
			mCamera.mTransform.AddMovement({ 100.f*-mTimer.GetDeltaTime(), 0.f});
		}
		if (mInput.GetCurrentKeyState(VK_DOWN) == KeyState::KEY_HOLD)
		{
			mCamera.mTransform.AddMovement({ 0.f, 100.f*-mTimer.GetDeltaTime()});
		}

		if(mInput.GetCurrentKeyState(VK_F1) == KeyState::KEY_HOLD)
			mCamera.ZoomInCamera(0.1f);
		else if(mInput.GetCurrentKeyState(VK_F2) == KeyState::KEY_HOLD)
			mCamera.ZoomOutCamera(0.1f);

	}

	virtual void RenderComponent() override
	{
		mObject.RenderObject(mCamera.GetViewMat());
		//DrawTextForDebugging(L"카메라 좌표계 : %f %f\n 마우스 좌표계 :  %f %f",
		//	mCamera.mTransform.GetLocation().x,
		//	mCamera.mTransform.GetLocation().y,
		//	MyTransformer2D::PixelToCartesian(mInput.GetCurrentMousePosVec2()).x,
		//	MyTransformer2D::PixelToCartesian(mInput.GetCurrentMousePosVec2()).y);
		DrawTextForDebugging(mTimer.m_csBuffer.c_str());
	}

	virtual void ReleaseComponent() override
	{
	}
};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR
	pCmdLine, int nCmdShow)
{
	MyCore::INITIAL_SETUP(hInstance, 1200, 800);
	Sample sample;

	sample.GameRun();
	return 0;
}