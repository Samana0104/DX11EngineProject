#include "pch.h"
#include "MyObject.h"
using namespace MyProject;

MyObject::MyObject(TEXTURE_KEY _textureKey, MESH_KEY _meshKey)
	: mTextureKey(_textureKey), mMeshKey(_meshKey)
{
	mTransform.SetScaleInMat({100.f, 100.f});
	//mTransform.SetTranslationInMat({100.f, 100.f});
	//mTransform.AddRotationInMat(60.f);
	//mTransform.SetRotationInMat(90.f);
}

void MyObject::UpdateObject(float _deltaTime)
{
}

void MyObject::RenderObject(const mat3x3 _viewMat)
{
	mManager.mMeshHandler.GetResource(mMeshKey)->UpdateRenderVertices(_viewMat*mTransform.GetModelMat());
	mManager.mTextureHandler.GetResource(mTextureKey)->RenderComponent();
	mManager.mMeshHandler.GetResource(mMeshKey)->RenderComponent();
}
