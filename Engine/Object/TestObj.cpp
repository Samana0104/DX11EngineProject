#include "pch.h"
#include "TestObj.h"
using namespace MyProject;

TestObj::TestObj() :
	mSprite(*this)
{
	SetTextureKey(L"bitmap1.bmp");
	SetMeshKey(L"BOX2D_MESH");
}

void TestObj::Update(const float _deltaTime)
{
}

void TestObj::Render(const mat3& _viewMat)
{
	vec4 color = { mColor.r, mColor.g, mColor.b, mColor.a };
	mManager.mTexture[mTextureKey]->Render();
	mManager.mMesh[mMeshKey]->Draw(_viewMat * mTransform.GetModelMat(), color);
}
