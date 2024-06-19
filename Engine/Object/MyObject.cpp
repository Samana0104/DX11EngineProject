#include "pch.h"
#include "MyObject.h"
using namespace MyProject;

MyObject::MyObject(TEXTURE_KEY _textureKey, MESH_KEY _meshKey)
	: mTextureKey(_textureKey), mMeshKey(_meshKey)
{
	mTransform.SetScale({100.f, 100.f});
	//mTransform.SetMovement({100.f, 100.f});
	//mTransform.AddRotationInMat(60.f);
	//mTransform.SetRotation(90.f);
	mManager.mMeshHandler[mMeshKey]->SetUVVertexAsRange(
		{239.f, 145.f, 866.f, 462.f}, 
		*mManager.mTextureHandler[mTextureKey]);
}

void MyObject::UpdateObject(float _deltaTime)
{
}

void MyObject::RenderObject(const mat3 _viewMat)
{
	mManager.mTextureHandler[mTextureKey]->RenderComponent();
	mManager.mMeshHandler[mMeshKey]->Render(_viewMat * mTransform.GetModelMat(), {1.f, 1.f, 0.3f, 0.7f});
}
