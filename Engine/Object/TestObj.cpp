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

void TestObj::Render(const mat3& _viewMat)
{
	vec4 color = { mColor.r, mColor.g, mColor.b, mColor.a };
	//mManager.mTexture[mTextureKey]->Render();
	mSprite.Render();
	mManager.mMesh[mMeshKey]->Draw(_viewMat * mTransform.GetModelMat(), color);
}
