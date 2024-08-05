#include "pch.h"
#include "MyStageInterface.h"
using namespace MyProject;

void MyStageInterface::Render()
{
	mObjManager.Render();
	if (isPause)
	{
		mPauseBackground.Render();
		for (int i = 0; i < 3; i++)
			mButtons[i].Render();
	}
	//mManager.mFont.DrawTextForDebugging(L"%f %f", MyTransformer2D::PixelToCartesian(mInput.GetCurrentMousePosVec2()).x,
	//	MyTransformer2D::PixelToCartesian(mInput.GetCurrentMousePosVec2()).y);
}

void MyStageInterface::Release()
{
	mManager.mSound[L"ashrams.ogg"]->Stop();

	mObjManager.ClearObject();
}
