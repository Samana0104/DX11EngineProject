#include "pch.h"
#include "MyObject.h"
using namespace MyProject;

MyObject::MyObject() : 
	mTextureKey(L"Default.jpg"), 
	mMeshKey(L"DEFAULT_MESH"),
	mColor({ 1.f, 1.f, 1.f, 1.f })
{
}

void MyObject::SetColor(vec4 _color)
{
	mColor = _color;
}

void MyObject::SetTextureKey(TEXTURE_KEY _key)
{
	mTextureKey = _key;
}

void MyObject::SetMeshKey(MESH_KEY _key)
{
	mMeshKey = _key;
}


const vec4& MyObject::GetColor() const
{
	return mColor;
}

const MESH_KEY& MyProject::MyObject::GetMeshKey() const
{
	return mMeshKey;
}

const TEXTURE_KEY& MyObject::GetTextureKey() const
{
	return mTextureKey;
}

const MyTransformer2D& MyObject::GetTransform() const
{
	return mTransform;
}

MyTransformer2D* MyObject::operator->()
{
	return &mTransform;
}

void MyObject::Update(const float _deltaTime)
{
}

void MyObject::Render()
{
	mManager.mShader[L"PixelShader.hlsl"]->SetUpConfiguration();
	mManager.mTexture[mTextureKey]->Render();
	mManager.mMesh[mMeshKey]->Draw(mTransform.GetModelMat(), mColor);
}
