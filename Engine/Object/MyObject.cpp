#include "pch.h"
#include "MyObject.h"
using namespace MyProject;

MyObject::MyObject()
	: mTextureKey(L"KGCA1.png"), mMeshKey(L"CIRCLE2D_MESH")
{
	mManager.mMesh[mMeshKey]->SetUVVertexAsRect(
		{239.f, 145.f, 866.f, 462.f}, 
		*mManager.mTexture[mTextureKey]);
}

MyTransformer2D* MyObject::operator->()
{
	return &mTransform;
}

void MyObject::Update(float _deltaTime)
{
}

void MyObject::Render(const mat3 _viewMat)
{
	mManager.mTexture[mTextureKey]->RenderComponent();
	mManager.mMesh[mMeshKey]->Render(_viewMat * mTransform.GetModelMat());
}
