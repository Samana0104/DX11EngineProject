#include "pch.h"
#include "TestObj.h"
using namespace MyProject;

TestObj::TestObj() :
	mSprite(*this)
{
	SetTextureKey(L"bitmap1.bmp");
	SetMeshKey(L"BOX2D_MESH");
	mSprite.SetSpriteKey(L"test.sprite");
	mSprite.SetChangeTime(0.1f);
}

void TestObj::Update(const float _deltaTime)
{
	mSprite.Update(_deltaTime);
}

void TestObj::Render()
{
	mManager.mShader[L"PixelShader.hlsl"]->SetUpConfiguration();
	mSprite.Render();

	if(mCamera != nullptr)
		mManager.mMesh[mMeshKey]->Draw(mCamera->GetViewMat() * mTransform.GetModelMat(), mColor);
	else
		mManager.mMesh[mMeshKey]->Draw(mTransform.GetModelMat(), mColor);
}
