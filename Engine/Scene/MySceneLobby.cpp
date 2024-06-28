#include "pch.h"
#include "MySceneLobby.h"
using namespace MyProject;

void MySceneLobby::Init()
{
	mObject->SetScale({ 30.f, 30.f });
	mObject2->SetScale({ 40.f, 10.f });
	mObject2->SetLocation({ 50.f, 0.f });
	mObject.SetColor({ 1.f, 1.f, 0.f, 0.7f });
}

void MySceneLobby::Update(float _deltaTime)
{
	if (mInput.GetCurrentKeyState(VK_UP) == KeyState::KEY_HOLD)
	{
		mCamera->AddLocation({ 0.f, 100.f * _deltaTime });
	}
	if (mInput.GetCurrentKeyState(VK_RIGHT) == KeyState::KEY_HOLD)
	{
		mCamera->AddLocation({ 100.f * _deltaTime,  0.f });
	}
	if (mInput.GetCurrentKeyState(VK_LEFT) == KeyState::KEY_HOLD)
	{
		mCamera->AddLocation({ 100.f * -_deltaTime,  0.f });
	}
	if (mInput.GetCurrentKeyState(VK_DOWN) == KeyState::KEY_HOLD)
	{
		mCamera->AddLocation({ 0.f, 100.f * -_deltaTime});
		mSceneManager.SetCurrentScene(L"SETTING");
	}

	if (mInput.GetCurrentKeyState(VK_F1) == KeyState::KEY_HOLD)
		mCamera.ZoomIn(0.01f);
	else if (mInput.GetCurrentKeyState(VK_F2) == KeyState::KEY_HOLD)
		mCamera.ZoomOut(0.01f);

	mObject->AddRotation(0.1f);
	mObject2->AddRotation(0.5f);
	mObject.Update(_deltaTime);
	//mCamera.LookAtObject(mObject2);
}

void MySceneLobby::Render()
{
	mObject.Render(mCamera.GetViewMat());
	mObject2.Render(mCamera.GetViewMat());
	//DrawTextForDebugging(L"카메라 좌표계 : %f %f\n 마우스 좌표계 :  %f %f",
	//	mCamera.mTransform.GetLocation().x,
	//	mCamera.mTransform.GetLocation().y,
	//	MyTransformer2D::PixelToCartesian(mInput.GetCurrentMousePosVec2()).x,
	//	MyTransformer2D::PixelToCartesian(mInput.GetCurrentMousePosVec2()).y);
	//DrawTextForDebugging(mTimer.m_csBuffer.c_str());
	//DrawTextForDebugging(L"[%f %f] [%f %f]\n[%f %f]",
	//	mObject->GetLocation().x,
	//	mObject->GetLocation().y,
	//	mObject2->GetLocation().x,
	//	mObject2->GetLocation().y,
	//	mCamera->GetLocation().x,
	//	mCamera->GetLocation().y);
}

void MySceneLobby::Release()
{
}

void MySceneLobby::Reset()
{
}

void MySceneLobby::Execute()
{
}
