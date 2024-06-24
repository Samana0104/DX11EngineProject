#include "pch.h"
#include "MyObject.h"
using namespace MyProject;

MyObject::MyObject() : 
	mTextureKey(L"Default.jpg"), 
	mMeshKey(L"DEFAULT_MESH")
{
}

void MyObject::SetTextureKey(TEXTURE_KEY _key)
{
	mTextureKey = _key;
}

void MyObject::SetMeshKey(MESH_KEY _key)
{
	mMeshKey = _key;
}

const MyTransformer2D& MyProject::MyObject::GetTransform() const
{
	return mTransform;
}

MyTransformer2D* MyObject::operator->()
{
	return &mTransform;
}
