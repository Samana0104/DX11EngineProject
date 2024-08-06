#include "pch.h"
#include "MySceneSetting.h"
using namespace MyProject;

void MySceneSetting::Init()
{
}

void MySceneSetting::Update(float _deltaTime)
{
	if (mInput.GetCurrentKeyState(VK_UP) == KeyState::KEY_DOWN)
		mSceneManager.SetCurrentScene(L"LOBBY");
}

void MySceneSetting::Render()
{
	//mManager.mFont.DrawTextForDebugging(L"%f %f ->\n %f %f ->\n %f %f",
	//	mInput.GetCurrentMousePosVec2().x,
	//	mInput.GetCurrentMousePosVec2().y,
	//	MyTransformer2D::PixelToCartesian(mInput.GetCurrentMousePosVec2()).x,
	//	MyTransformer2D::PixelToCartesian(mInput.GetCurrentMousePosVec2()).y,
	//	MyTransformer2D::CartesianToPixel(MyTransformer2D::PixelToCartesian(mInput.GetCurrentMousePosVec2())).x,
	//	MyTransformer2D::CartesianToPixel(MyTransformer2D::PixelToCartesian(mInput.GetCurrentMousePosVec2())).y);
	//mManager.mFont.DrawTextForDebugging(L"¾Æ Èûµé´Ù¾Æ");
}

void MySceneSetting::Release()
{
}

void MySceneSetting::Reset()
{
}

void MySceneSetting::Start()
{
}

void MySceneSetting::End()
{
}
